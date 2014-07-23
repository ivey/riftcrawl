#pragma once

// item defs
#define ITEM_NONE        0
#define ITEM_POTION      1
#define ITEM_DORAN_BLADE 2

struct ITEM {
  char    character;  // ASCII character for this item type
  short   color;      // rlutil Color code for this tile type
  char    name[20];   // name of the item
  bool    active;     // active item?
};

ITEM items[] = {
  { ' ',       10, "EMPTY",         false },   // 0 ITEM_NONE
  { '!',       6,  "Health Potion", true },    // 1 ITEM_POTION
  { '/',       8,  "Doran's Blade", false },   // 2 ITEM_DORAN_BLADE
};
