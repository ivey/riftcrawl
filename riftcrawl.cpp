#include "rlutil.h"
#include "tiles.h"
#include "items.h"
#include "debug.h"
#include "engine.h"
#include "items.h"
#include "tiles.h"
#include <cstdio>
#include <string>

// player location
int px=1, py=MAP_HEIGHT; // start at bottom corner
int inventory[6] = {0,0,0,0,0,0};

// the map
int map_tiles[MAP_HEIGHT][MAP_WIDTH] = {
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

int map_items[MAP_HEIGHT][MAP_WIDTH];


void drawmap(void) {
  for( int y = 0; y < MAP_HEIGHT; y++ ) {
    for( int x = 0; x < MAP_WIDTH; x++ ) {
      int clr;
      char chr;
      rlutil::locate(x+1,y+1); // locate is 1 based
      if(map_items[y][x] != ITEM_NONE) {
        int t = map_items[y][x];
        clr = items[t].color;
        chr = items[t].character;
      } else {
        int t = map_tiles[y][x];
        clr = tiles[t].color;
        chr = tiles[t].character;
      }
      rlutil::setColor(clr);
      std::cout << chr;
    }
  }
}

void drawplayer(void) {
  rlutil::locate(px,py);
  rlutil::setColor(9);
  std::cout << PLAYER;
}

void drawinv(void) {
  rlutil::locate(MAP_WIDTH+2, 1);
  std::cout << "Inventory";
  rlutil::locate(MAP_WIDTH+2, 2);
  std::cout << "---------";
  for( int i = 0; i < 6; i++ ) {
    int it = inventory[i];
    rlutil::locate(MAP_WIDTH+2, 3+i);
    std::cout << i+1 << ": " << items[it].name << "          ";
  }
}

bool movablep(int mx, int my) {
  if (mx < 1 || mx > MAP_WIDTH || my < 1 || my > MAP_HEIGHT) {
    return false;
  }
  int v = map_tiles[my-1][mx-1];
  return tiles[v].passable;
}

void inititems(void) {
  memset( map_items, 0, sizeof(items) );
  map_items[5][5] = ITEM_POTION;
  map_items[12][14] = ITEM_DORAN_BLADE;
}


// cmds.cpp ?

void cmdget(void) {
  if(map_items[py-1][px-1] == ITEM_NONE) {
    status("You're not on an item!");
    return;
  }
  for( int i = 0; i < 6; i++ ) {
    if(inventory[i] == ITEM_NONE) {
      inventory[i] = map_items[py-1][px-1];
      map_items[py-1][px-1] = ITEM_NONE;
      return;
    }
  }
  status("You don't have any free inventory slots.");
  return;
}

void cmdsell(void) {
  status("Sell which item? [1-6]");
  int slot = getch();
  slot = slot - 49;
  char s [100];
  if(slot < 0 || slot > 5) {
    status("Invalid slot");
    return;
  }
  int item = inventory[slot];
  if(item == ITEM_NONE) {
    sprintf(s, "No item in slot %d", slot+1);
    status(s);
    return;
  }
  sprintf(s, "Selling %s", items[item].name);
  status(s);
  // TODO: credit gold
  inventory[slot] = ITEM_NONE;
  return;
}

// cmds

int main( void ) {
  rlutil::cls();
  rlutil::CursorHider curs;

  inititems();

  drawmap();
  drawplayer();
  fflush(stdout);

  while (true) {
    if (kbhit()) {
      status("");

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
      case 103: // g
        cmdget();
        break;
      case 115: // s
        cmdsell();
        break;
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
      drawinv();
      fflush(stdout);
    }
  }
  return 0;
}
