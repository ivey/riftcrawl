#include "rlutil.h"

// debug routines - remove/ifdef out
void status(std::string s) {
  rlutil::setColor(15);
  rlutil::locate(1,16);
  std::cout << s << "              ";
}

void info(std::string s) {
  rlutil::setColor(14);
  rlutil::locate(1,17);
  std::cout << s << "              ";
}

void debug(std::string s) {
  rlutil::setColor(12);
  rlutil::locate(1,18);
  std::cout << s << "              ";
}
