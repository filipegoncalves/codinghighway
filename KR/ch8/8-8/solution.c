#include <stdio.h>

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *bfree(void *p, unsigned n) {
	void my_free(void *);
	unsigned nunits;
	Header *ptr = (Header *) p;
	nunits = n/sizeof(Header);
	if (nunits <= 1) /* too small */
		return NULL;
	if (freep == NULL) {
		base.s.ptr = freep = &base;
		base.s.size = 0;
	}
	ptr->s.size = nunits;
	my_free((void *)(ptr+1));
	return (void *)(ptr+1);
}

#define NALLOC 1024
#include <unistd.h>
static Header *morecore(unsigned nu) {
	char *cp;
	Header *up;
	void my_free(void *);
	
	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	my_free((void *)(up+1));
	return freep;
}

void *my_malloc(unsigned nbytes) {
	Header *p, *prevp;
	unsigned nunits;
	
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp= p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void my_free(void *ap) {
	Header *bp, *p;
	
	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

int main() {
	/* Example usage */
	int x[512];
	int *a;
	int i;
	bfree(x, sizeof(x));
	a = (int *) my_malloc(sizeof(x));
	for (i = 0; i < 512; i++)
		a[i] = i;
	for (i = 0; i < 512; i++)
		printf("%d ", a[i]);	
	printf("\n");
	return 0; 
}
