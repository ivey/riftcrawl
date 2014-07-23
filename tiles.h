#pragma once

// tile defs
#define PLAYER     "@"
#define TILE_GRASS  0
#define TILE_DIRT   1
#define TILE_WALL   2
#define TILE_WATER  3

struct TILE {
  char    character;  // ASCII character for this tile type
  short   color;      // rlutil Color code for this tile type
  bool    passable;   // Set to true if you can walk on this tile
};

TILE tiles[] = {
  { '.', 10, true },    // 0 TILE_GRASS
  { '.', 6,  true },    // 1 TILE_DIRT
  { '#', 8,  false },   // 2 TILE_WALL
  { '~', 9,  true },    // 3 TILE_WATER
};
