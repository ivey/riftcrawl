#include "rlutil.h"
#include <cstdio>
#include <algorithm>

#define PLAYER "@"
#define MAX_X 60
#define MAX_Y 25

int main( void ) {
  int nPlayerX=40, nPlayerY=12;
  rlutil::cls();
  rlutil::locate(nPlayerX,nPlayerY); std::cout << PLAYER; // Output player

  while (true) {
    if (kbhit()) {

      int k = rlutil::getkey(); // Get character

      rlutil::locate(nPlayerX,nPlayerY); std::cout << " "; // Erase player

      switch (k) {
      case rlutil::KEY_LEFT:
        --nPlayerX;
        break;
      case rlutil::KEY_RIGHT:
        ++nPlayerX;
        break;
      case rlutil::KEY_UP:
        --nPlayerY;
        break;
      case rlutil::KEY_DOWN:
        ++nPlayerY;
        break;
      case 113: // q
      case rlutil::KEY_ESCAPE:
        return 0;
      default:
        break;
      }

      nPlayerX = std::min(nPlayerX, MAX_X);
      nPlayerY = std::min(nPlayerY, MAX_Y);


      rlutil::locate(nPlayerX,nPlayerY); std::cout << PLAYER; // Output player
      fflush(stdout);
    }
  }
  return 0;
}
