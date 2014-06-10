#include "rlutil.h"
#include <cstdio>
#include <string>

// map defs
#define MAP_WIDTH 20
#define MAP_HEIGHT 15

// tile defs
#define PLAYER "@"
#define TILE_FLOOR 0
#define TILE_WALL 1


void status(std::string s) {
  rlutil::locate(1,16);
  std::cout << s << "       ";
}

void info(std::string s) {
  rlutil::locate(1,17);
  std::cout << s << "       ";
}

void debug(std::string s) {
  rlutil::locate(1,18);
  std::cout << s << "       ";
}



// player location
int px=1, py=1;

// the map
int map[MAP_HEIGHT][MAP_WIDTH] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void drawmap(void) {
  for( int y = 0; y < MAP_HEIGHT; y++ ) {
    rlutil::locate(1,y+1); // draw new line - locate is 1 based
    for( int x = 0; x < MAP_WIDTH; x++ ) {
      switch (map[y][x]) {
      case TILE_FLOOR:
        rlutil::setColor(7);
        std::cout << ".";
        break;
      case TILE_WALL:
        rlutil::setColor(8);
        std::cout << "#";
        break;
      }
    }
  }
}

void drawplayer(void) {
  rlutil::locate(px,py);
  std::cout << PLAYER;
}

bool movablep(int mx, int my) {
  if (mx < 1 || mx > MAP_WIDTH || my < 1 || my > MAP_HEIGHT) {
    return false;
  }
  int v = map[my-1][mx-1];
  if (v == TILE_FLOOR) {
    return true;
  }

  return false;
}

int main( void ) {
  rlutil::cls();
  rlutil::CursorHider curs;

  drawmap();
  drawplayer();

  while (true) {
    if (kbhit()) {

      int k = rlutil::getkey();
      char s [100];
      sprintf(s, "Key pressed: %d", k);
      info(s);

      switch (k) {
      case rlutil::KEY_LEFT:
        if (movablep(px-1, py)) {
          px--;
        }
        break;
      case rlutil::KEY_RIGHT:
        if (movablep(px+1, py)) {
          px++;
        }
        break;
      case rlutil::KEY_UP:
        if (movablep(px, py-1)) {
          py--;
        }
        break;
      case rlutil::KEY_DOWN:
        if (movablep(px, py+1)) {
          py++;
        }
        break;
      case 113: // q
      case rlutil::KEY_ESCAPE:
        rlutil::cls();
        return 0;
      default:
        break;
      }

      char ds [100];
      sprintf(ds, "Player: %d, %d", px, py);
      debug(ds);

      drawmap();
      drawplayer();
      fflush(stdout);
    }
  }
  return 0;
}
