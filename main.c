#include <stdlib.h>
#include <stdio.h>

#define N_MODULES 20
#define WIDTH 80
#define HEIGHT 20

struct point {
  size_t x;
  size_t y;
};

char the_map[HEIGHT][WIDTH];
struct point endpoints[N_MODULES * 2];
size_t last_endpoint;

void place_module() {
  struct point left, right;
  int direction, dx = 0, dy = 0, i;
  if (endpoints[0].x == WIDTH && endpoints[0].y == HEIGHT) {
    /* put starting module wherever */
    left.x = rand() % WIDTH;
    left.y = rand() % HEIGHT;
  } else {
    left = endpoints[rand() % last_endpoint];
  }

  while (1) {
    right = left;

    direction = rand() % 4;
    switch (direction) {
    case 0: /* north */
      right.y = left.y + 3;
      dy = 3;
      break;
    case 1: /* east */
      right.x = left.x + 3;
      dx = 3;
      break;
    case 2: /* south */
      right.y = left.y - 3;
      dy = -3;
      break;
    case 3: /* west */
      right.x = left.x - 3;
      dx = -3;
      break;
    }
    if (right.x > 0 && right.x < WIDTH && right.y > 0 && right.y < HEIGHT) {
      break;
    }
  }

  if (dx != 0) {
    for (i = 0; i < abs(dx); i++) {
      the_map[left.y][left.x + (i * (dx / abs(dx)))] = 'X';
    }
  }
  if (dy != 0) {

    for (i = 0; i < abs(dy); i++) {
      the_map[left.y + (i * (dy / abs(dy)))][left.x] = 'X';
    }
  }

  the_map[left.y][left.x] = '0';
  the_map[right.y][right.x] = '0';
  endpoints[last_endpoint++] = left;
  endpoints[last_endpoint++] = right;
}

int main() {
  int x, y, e, m;
  sranddev();

  for (x = 0; x < WIDTH; x++) {
    for (y = 0; y < HEIGHT; y++) {
      the_map[y][x] = ' ';
    }
  }

  for (e = 0; e < N_MODULES * 2; e++) {
    endpoints[e].x = WIDTH;
    endpoints[e].y = HEIGHT;
  }

  for (m = 0; m < N_MODULES; m++) {
    place_module();
  }

  for (y = 0; y < HEIGHT; y++) {
    fwrite(the_map[y], sizeof(char), WIDTH - 1, stdout);
    fwrite("\n", sizeof(char), 1, stdout);
  }

  return 0;
}
