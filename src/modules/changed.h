#include <iostream>
#include <list>
#include "coord.h"
using namespace std;

#ifndef MODULE_CHANGED_CLASS
#define MODULE_CHANGED_CLASS
class Changed {
  public:
    Coord position;
    int oldValue;
    int newValue;

    Changed(Coord pos = Coord(), int oldVal = 0, int newVal = 0) {
      position = pos;
      oldValue = oldVal;
      newValue = newVal;
    }
};

#endif // MODULE_CHANGED_CLASS