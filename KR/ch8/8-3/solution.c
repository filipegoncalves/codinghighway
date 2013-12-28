#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

struct _flags {
	unsigned int _READ : 1;
	unsigned int _WRITE : 1;
	unsigned int _UNBUF : 1;
	unsigned int _EOF : 1;
	unsigned int _ERR : 1;
};

typedef struct _iobuf {
	int cnt;					/* character left */
	char *ptr;					/* next character position */
	char *base;					/* location of buffer */
	struct _flags flags;		/* mode of file access */
	int fd;						/* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 }
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flags._EOF) != 0)
#define ferror(p) (((p)->flags._ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
					? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
					? *(p)->ptr++ = (x) : _flushbuf((x), p))
					
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define PERMS 0666

FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;
	
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->flags._READ == 0 && fp->flags._WRITE == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;
		
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flags._UNBUF = 0;
	fp->flags._EOF = 0;
	fp->flags._ERR = 0;
	if (*mode == 'r') {
		fp->flags._READ = 1;
		fp->flags._WRITE = 0;
	}
	else {
		fp->flags._WRITE = 1;
		fp->flags._READ = 0;
	}
	return fp;
}

int _fillbuf(FILE *fp) {
	int bufsize;
	
	if (!fp->flags._READ || fp->flags._EOF || fp->flags._ERR)
		return EOF;
	bufsize = (fp->flags._UNBUF == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flags._EOF = 1;
		else
			fp->flags._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
	int bufsize;
	int flushed;
	
	if (!fp->flags._WRITE || fp->flags._EOF || fp->flags._ERR)
		return EOF;
	bufsize = (fp->flags._UNBUF == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL) {
			fp->flags._ERR = 1;
			return EOF;
		}
	}
	else {
		/* If we get here, we really need to flush the buffer
		   We're not necessarily flushing bufsize characters!
		*/
		flushed = write(fp->fd, fp->base, fp->ptr - fp->base);
		if (flushed != fp->ptr - fp->base) {
			fp->flags._ERR = 1;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	fp->cnt = bufsize-1;
	return *fp->ptr++ = (char) c;
}

int fflush(FILE *fp) {
	int flush;
	if (!fp->flags._WRITE || fp->flags._ERR || fp->flags._EOF)
		return EOF;
	flush = _flushbuf(0, fp);
	fp->ptr = fp->base;
	fp->cnt = (fp->flags._UNBUF ? 1 : BUFSIZ);
	return flush;
}

int fclose(FILE *fp) {
	int flush_res;
	
	flush_res = fflush(fp);
	
	/* fp->base will never point to NULL because the boundary case where fclose is called
	   without ever having been written will cause _flushbuf to allocate a new buffer even
	   because fflush will write a NULL byte.
	*/
	free(fp->base);
	fp->flags._READ = fp->flags._WRITE = 0;
	
	return flush_res;
}

int main(int argc, char *argv[]) { 
	/* Example usage
	   Must be passed a valid file in argv[1] 
	*/
	int c;
	FILE *test = fopen(argv[1], "r");
	while ((c = getc(test)) != EOF)
		putchar(c);
	fclose(test);
	fclose(stdout);
	return 0;
}
