#include "rlutil.h"
#include <cstdio>
#include <string>

// debug routines - remove/ifdef out
void status(std::string s) {
  rlutil::setColor(15);
  rlutil::locate(1,16);
  std::cout << s << "       ";
}

void info(std::string s) {
  rlutil::setColor(14);
  rlutil::locate(1,17);
  std::cout << s << "       ";
}

void debug(std::string s) {
  rlutil::setColor(12);
  rlutil::locate(1,18);
  std::cout << s << "       ";
}


// map defs
#define MAP_WIDTH 20
#define MAP_HEIGHT 15

// tile defs
#define PLAYER "@"

struct TILE {
  char    character;  // ASCII character for this tile type
  short   color;      // rlutil Color code for this tile type
  bool    passable;   // Set to true if you can walk on this tile
};

TILE tiles[] = {
  { '.', 10, true },    // 0 grass
  { '.', 6,  true },    // 1 dirt
  { '#', 8,  false },   // 2 wall
  { '~', 9,  true },    // 3 water
};


// player location
int px=1, py=MAP_HEIGHT;

// the map
int map[MAP_HEIGHT][MAP_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 3, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1 },
    { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

void drawmap(void) {
  for( int y = 0; y < MAP_HEIGHT; y++ ) {
    for( int x = 0; x < MAP_WIDTH; x++ ) {
      rlutil::locate(x+1,y+1); // locate is 1 based
      int t = map[y][x];
      rlutil::setColor(tiles[t].color);
      std::cout << tiles[t].character;
    }
  }
}

void drawplayer(void) {
  rlutil::locate(px,py);
  rlutil::setColor(9);
  std::cout << PLAYER;
}

bool movablep(int mx, int my) {
  if (mx < 1 || mx > MAP_WIDTH || my < 1 || my > MAP_HEIGHT) {
    return false;
  }
  int v = map[my-1][mx-1];
  return tiles[v].passable;
}

int main( void ) {
  rlutil::cls();
  rlutil::CursorHider curs;

  drawmap();
  drawplayer();
  fflush(stdout);

  while (true) {
    if (kbhit()) {

      int k = rlutil::getkey();
      char s [100];
      sprintf(s, "Key pressed: %d", k);
      info(s);

      int dx = 0;
      int dy = 0;

      switch (k) {
      case 104: // h
      case rlutil::KEY_LEFT:
        dx = -1;
        break;
      case 108: // l
      case rlutil::KEY_RIGHT:
        dx = 1;
        break;
      case 107: // k
      case rlutil::KEY_UP:
        dy = -1;
        break;
      case 106: // j
      case rlutil::KEY_DOWN:
        dy = 1;
        break;
      case 113: // q
      case rlutil::KEY_ESCAPE:
        rlutil::cls();
        return 0;
      default:
        break;
      }

      if (movablep(px + dx, py + dy)) {
        px += dx;
        py += dy;
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
