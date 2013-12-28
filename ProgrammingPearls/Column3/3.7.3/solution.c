#include <stdio.h>
#define ALPHABET_SIZE 26

char *letters[ALPHABET_SIZE] = {
"\
         X              \n\
       X   X            \n\
      X     X           \n\
     X       X          \n\
    X         X         \n\
   XXXXXXXXXXXXX        \n\
  X             X       \n\
 X               X      \n\
X                 X     \n\
",
"\
XXXXXXXXXXXX \n\
X          X \n\
X          X \n\
X          X \n\
XXXXXXXXXXXX \n\
X            \n\
XXXXXXXXXXXX \n\
X          X \n\
X          X \n\
X          X \n\
XXXXXXXXXXXX \n\
",
"\
XXXXXXXXXXXX \n\
X            \n\
X            \n\
X            \n\
X            \n\
X            \n\
X            \n\
XXXXXXXXXXXX \n\
",
"\
XXXXXXXXXXXXX \n\
  X         X \n\
  X         X \n\
  X         X \n\
  X         X \n\
  X         X \n\
  X         X \n\
  X         X \n\
  X         X \n\
XXXXXXXXXXXXX \n\
",
"\
XXXXXXXXXXXX \n\
X            \n\
X            \n\
XXXXXXXXXXXX \n\
X            \n\
X            \n\
XXXXXXXXXXXX \n\
",
"\
XXXXXXXXXXXX \n\
X            \n\
X            \n\
XXXXXXX      \n\
X            \n\
X            \n\
X            \n\
",
"\
XXXXXXXXXXXX \n\
X            \n\
X            \n\
X    XXXXXX  \n\
X         X  \n\
X         X  \n\
XXXXXXXXXXX  \n\
",
"\
XX       XX \n\
XX       XX \n\
XX       XX \n\
XXXXXXXXXXX \n\
XXXXXXXXXXX \n\
XX       XX \n\
XX       XX \n\
XX       XX \n\
XX       XX \n\
",
"\
XXXXXXXXXXX \n\
XXXXXXXXXXX \n\
    XX      \n\
    XX      \n\
    XX      \n\
    XX      \n\
    XX      \n\
XXXXXXXXXXX \n\
XXXXXXXXXXX \n\
",
"\
XXXXXXXXXX \n\
XXXXXXXXXX \n\
        XX \n\
        XX \n\
 XX    XX  \n\
 XX   XX   \n\
 XXXXXX    \n\
",
"\
X    X \n\
X   X  \n\
X  X   \n\
X X    \n\
XX     \n\
X X    \n\
X  X   \n\
X   X  \n\
",
"\
X          \n\
X          \n\
X          \n\
X          \n\
X          \n\
X          \n\
XXXXXXXXXX \n\
",
"\
XX      XX \n\
X X    X X \n\
X  X  X  X \n\
X   XX   X \n\
X        X \n\
X        X \n\
X        X \n\
",
"\
XX      X \n\
X X     X \n\
X  X    X \n\
X   X   X \n\
X    X  X \n\
X     X X \n\
X      XX \n\
",
"\
XXXXXXXXXX \n\
X        X \n\
X        X \n\
X        X \n\
X        X \n\
X        X \n\
XXXXXXXXXX \n\
",
"\
XXXXXXXXXX \n\
X        X \n\
X        X \n\
XXXXXXXXXX \n\
X          \n\
X          \n\
X          \n\
",
"\
XXXXXXXXXX \n\
X        X \n\
X        X \n\
X        X \n\
X    X   X \n\
X     X  X \n\
XXXXXXXXXX \n\
        X  \n\
         X \n\
",
"\
XXXXXXXXXX \n\
X        X \n\
X        X \n\
XXXXXXXXXX \n\
XXXXX      \n\
X    X     \n\
X     X    \n\
X      X   \n\
X       X  \n\
",
"\
XXXXXXXXXX \n\
X          \n\
X          \n\
XXXXXXXXXX \n\
         X \n\
         X \n\
XXXXXXXXXX \n\
",
"\
XXXXXXXXXX \n\
    X      \n\
    X      \n\
    X      \n\
    X      \n\
    X      \n\
",
"\
X        X \n\
X        X \n\
X        X \n\
X        X \n\
X        X \n\
XXXXXXXXXX \n\
",
"\
X       X \n\
 X     X  \n\
  X   X   \n\
   X X    \n\
    X     \n\
",
"\
X       XX       X \n\
 X     X  X     X  \n\
  X   X    X   X   \n\
   X X      X X    \n\
    X        X     \n\
",
"\
X     X \n\
 X   X  \n\
  X X   \n\
   X    \n\
  X X   \n\
 X   X  \n\
X     X \n\
",
"\
X      X \n\
 X    X  \n\
  X  X   \n\
   XX    \n\
   XX    \n\
   XX    \n\
   XX    \n\
",
"\
XXXXXXXXX \n\
       X  \n\
     X    \n\
   X      \n\
 X        \n\
XXXXXXXXX \n\
"
};

char *banner(char c) {
	return letters[c-'A'];
}

int main() {
	/* Print the alphabet! */
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		printf("%s\n", banner('A'+i));
	return 0;
}
