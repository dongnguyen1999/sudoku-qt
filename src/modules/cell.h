#include <stdio.h>
#include <list>
#define MAX_VALUE 10
#define EMPTY 0
#include <iostream>
using namespace std;
#define MAX_VALUE 10
#define NULL_INDEX -1

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
};
#endif // MODULE_COORD_CLASS

#ifndef MODULE_CELL_CLASS
#define MODULE_CELL_CLASS
class Cell {
  private:
    Coord position;
    int value;
    bool availableValues[MAX_VALUE];

  public:
    Cell(Coord position = Coord(), int val = EMPTY) {
      this->position = position;
      availableValues[0] = false;
      for (int i = 1; i < MAX_VALUE; i++) {
        availableValues[i] = true;
      };
      value = val;
    }

    int getValue() {
      return value;
    }

    void setValue(int val) {
      value = val;
    }

    void clearValue() {
      value = EMPTY;
    }

    bool isEmpty() {
      return value == EMPTY;
    }

    bool checkValue(int value) {
      return availableValues[value];
    }

    Coord getPosition() {
      return position;
    }

    int getNextAvailable() {
      for (int i = 0; i < MAX_VALUE; i++) {
        if (availableValues[i]) return i;
      }
      return EMPTY;
    }

    list<int> getAvailableValues() {
      list<int> l;
      for (int i = 0; i < MAX_VALUE; i++) {
        if (availableValues[i]) l.push_back(i);
      }
      return l;
    }
    
    void print() {
      cout << "Cell[" << position.x << "," << position.y << "]: " << endl;
      cout << "Value: " << value << endl;
      cout << "Available: ";
      for (int i = 0; i < MAX_VALUE; i++) {
        if (availableValues[i]) cout << i << ", ";
      }
      cout << endl;
    }

    bool limit(list<int> limitedValues) {
      for (list<int>::iterator i = limitedValues.begin(); i != limitedValues.end(); i++) {
        if (availableValues[*i]) {
          availableValues[*i] = false;
          return true;
        }
      }
      return false;
    }

    bool limit(int value) {
      if (availableValues[value]) {
        availableValues[value] = false;
        return true;
      }
      return false;
    }

    bool open(list<int> limitedValues) {
      for (list<int>::iterator i = limitedValues.begin(); i != limitedValues.end(); i++) {
        if (!availableValues[*i]) {
          availableValues[*i] = true;
          return true;
        }
      }
      return false;
    }

    bool open(int value) {
      if (!availableValues[value]) {
        availableValues[value] = true;
        return true;
      }
      return false;
    }
};

#endif // MODULE_CELL_CLASS
