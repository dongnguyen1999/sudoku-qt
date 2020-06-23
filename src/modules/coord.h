#include <stdio.h>
#include <vector>
#include <list>
#define MAX_VALUE 10
#define EMPTY 0
#include <iostream>
using namespace std;
#define MAX_VALUE 10
#define NULL_INDEX -1
#define NB_ROWS 9
#define NB_COLUMNS 9
#define AREA_SQUARE_SIZE 3
#define INF 999999

#ifndef MODULE_COORD_CLASS
#define MODULE_COORD_CLASS
class Coord {
  public:
    int x;
    int y;

    Coord(int x = NULL_INDEX, int y = NULL_INDEX) {
      this->x = x;
      this->y = y;
    }

    bool isNull() {
      return (x == NULL_INDEX || y == NULL_INDEX);
    }

    void print() {
      cout << "(" << x  << "," << y << ");" << endl;
    }
};
#endif // MODULE_COORD_CLASS
