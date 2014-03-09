/*
Compile with -std=c99 and -Wall

This program implements the solution for the problem described in blackbox.pdf.
The idea is that the problem can be seen as a physics problem messing with vectors. The ray
is represented by a position in the grid and an associated velocity vector with components x and y, which I
call vx and vy. 
vx and vy follow the usual orientation, where the origin is placed in the bottom left corner: x increases as we travel
left to right, and y increases as we travel from bottom to top.
The coordinates for vx and vy are such that they fully describe the next position of the ray in the grid,
given the current position. To do so, we just perform regular vector addition. Here's an example:

   T1 T2 T3 T4 T5 T6 T7 T8
L1  .  .  .  .  .  .  .  . R1
L2  .  .  .  .  .  .  .  . R2
L3  .  .  .  .  .  .  .  . R3
L4  .  .  .  .  .  .  .  . R4
L5  .  .  @  .  .  .  .  . R5
L6  .  .  .  .  .  .  .  . R6
L7  .  .  .  .  .  .  .  . R7
L8  .  .  .  .  .  .  .  . R8
   B1 B2 B3 B4 B5 B6 B7 B8

If we were to start on L5, the initial position in the grid would be (5,1), and the velocity vector would be
(1,0). Note that the vector's x axis matches with the columns axis (going left-to-right increases column number),
so vector addition may not be very intuitive at first. For the vector (x,y) and position (x',y'), the next position in the
grid is actually (x'-y,y'+x). There is a subtraction there because the vector's coordinates follow the regular convention that y increases as we go up.
However, since our grid is exactly the opposite, we invert that part of the vector to account for the different coordinates system.
This makes sense, but it's low on intuition. So, in this example, the next position will be (5,2).
And then it will be (5,3), where an atom is placed, so we have a hit.

If we were to start on B1, the initial position in the grid would be (8,1), and the velocity vector would be
(0,1). The next position would then be (7,1), then (6,1), and all the way down until (1,1).

The problem is solved with vector manipulation. Every time an atom is added at position (x,y) in the grid, not only we store
the information that (x,y) holds an atom, but we also store the physic forces that this atom places on positions near (x,y).
In particular, it will add the vector (-1,1) in (x-1,y-1); the vector (1,1) in (x-1,y+1); the vector (-1,-1) in (x+1,y-1), and the
vector (1,-1) in (x+1,y+1). The implementation uses a 2D array of 10 by 10, so that these adjacent references never yield out-of-bound accesses.

This decision also makes it easier to implement the main algorithm. As we read input, for each atom added, the appropriate vectors are placed in
its diagonal positions, as mentioned above. Note that nearby atoms will create a mix of forces in single points in the grid (this is what makes reflection
possible); it is thus crucial for correctness that each vector placed in a position is added (using usual vector arithmetic) to other possible vectors that 
may be already there. This requires that the grid is cleared to 0 on every position before reading input.

With the grid built, tracing a ray is a matter of repeatedly updating its current position with the vector that results from adding the current velocity vector
with the current position's velocity vector. However, some boundary cases must be manually tested: by definition, reflection takes place if an atom sits in an edge
position and a ray starts from one of its adjacent positions, so this case is manually tested. The other rule to keep in mind is that a hit has higher precedence than
a deflection or a reflection, so this is also tested: at each step, we only update the velocity vector with the vector from the current position if (and only if) there is
not an atom in the position that would be the next one if we were to ignore the vector forces from the current position. This works because if there is in fact an atom in
the next position (ignoring the forces from nearby atoms, that is, using only the vector from the previous iteration), then the rule says that this is more important than
the other forces around.

The algorithm stops as soon as we hit an edge position back (which means there was either a reflection or a deflection), or when we hit a position with an atom.

Keep in mind that B8 and R8 denote the same position, but the velocity vector associated with each one is different. B8 implies that the initial vector will be
(0,1); R8 implies that it will be (-1,0). The same principle applies to other corner positions.

Enjoy!
*/

#include <string.h>
#include <stdio.h>

#define CONSUME_NEWLINE() do { if (getchar() == '\r') getchar(); } while (0)
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#define NORMALIZE(x,y) do { \
    if ((x) < 0 || (x) > 0) \
      (x) = ((x) < 0 ? -1 : 1); \
    if ((y) < 0 || (y) > 0) \
      (y) = ((y) < 0 ? -1 : 1); \
  } while (0)

struct slot {
  char hasAtom;
  signed char vx;
  signed char vy;
};

struct slot grid[10][10];

void placeAtom(int line, int col) {
  for (int i = -1; i <= 1; i += 2)
    for (int j = -1; j <= 1; j += 2) {
	grid[line+i][col+j].vx += j;
	grid[line+i][col+j].vy -= i;
	/* Normalize vector */
	NORMALIZE(grid[line+i][col+j].vx, grid[line+i][col+j].vy);
    }
  grid[line][col].hasAtom = 1;
}

void clear_grid(void) {
  for (int i = 0; i < ARRAY_SIZE(grid); i++)
    for (int j = 0; j < ARRAY_SIZE(grid[0]); j++)
      grid[i][j].hasAtom = grid[i][j].vx = grid[i][j].vy = 0;
}

void read_grid(void) {
  for (int line = 1; line <= 8; line++) {
    for (int col = 1; col <= 8; col++) {
      if (getchar() == '@') {
	placeAtom(line, col);
      }
    }
    CONSUME_NEWLINE();
  }
}

void read_ray(int *line, int *col, int *vx, int *vy, char *str) {
  int c;
  int *p1 = line, *p2 = col;
  *vx = *vy = 0;
  if ((*str++ = c = getchar()) == 'L' || c == 'R') {
    *vx = (c == 'L' ? 1 : -1);
    p1 = col;
    p2 = line;
  } else {
    *vy = (c == 'T' ? -1 : 1);
  }
  if (c == 'L' || c == 'T')
    *p1 = 1;
  else
    *p1 = 8;
  *str = c = getchar();
  *p2 = c - '0';
}

char *convert_to_str(int line, int col, int vx, int vy) {
  static char str[3] = { 0 };
  if (vx == -1 || vx == 1) {
    str[0] = (vx == -1 ? 'L' : 'R');
    str[1] = line + '0';
  }
  else {
    str[0] = (vy == -1 ? 'B' : 'T');
    str[1] = col + '0';
  }
  return str;
}

void output_ray(int line, int col, int vx, int vy, char *pos) {
  if (grid[line][col].hasAtom) {
    printf("H\n");
    return;
  }
  if ((line == 1 && vy == -1) || (line == 8 && vy == 1)) {
    if (grid[line][col-1].hasAtom || grid[line][col+1].hasAtom) {
      printf("R\n");
      return;
    }
  }
  if ((col == 1 && vx == 1) || (col == 8 && vx == -1)) {
    if (grid[line-1][col].hasAtom || grid[line+1][col].hasAtom) {
      printf("R\n");
      return;
    }
  }
  int px, py;
  px = col;
  py = line;
  while (0 < px && px < 9 && 0 <  py && py < 9 && !grid[py][px].hasAtom) {
    if (!grid[py-vy][px+vx].hasAtom) {
      vx += grid[py][px].vx;
      vy += grid[py][px].vy;
    }
    NORMALIZE(vx, vy);
    px += vx;
    py -= vy;
  }
  if (grid[py][px].hasAtom)
    printf("H\n");
  else {
    char *str = convert_to_str(py, px, vx, vy);
    if (!strcmp(str, pos))
      printf("R\n");
    else
      printf("%s\n", str);
  }
}

int main(void) {
  int c;
  while ((c = getchar()) != 'X') {
    ungetc(c, stdin);
    clear_grid();
    read_grid();
    /* Perform ray tracing as per the rest of the input */
    unsigned lines;
    scanf("%u", &lines);
    for (unsigned i = 0; i < lines; i++) {
      int line, col, vx, vy;
      char str[3] = { 0 };
      CONSUME_NEWLINE();
      read_ray(&line, &col, &vx, &vy, str);
      output_ray(line, col, vx, vy, str);
    }
    CONSUME_NEWLINE();
  }
  return 0;
}
