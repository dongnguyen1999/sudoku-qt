#include <iostream>
#include <list>
#include "coord.h"
using namespace std;
#ifndef MODULE_CONSTRAIN_CLASS
#define MODULE_CONSTRAIN_CLASS
class Constrains {
  private:
    int data[NB_ROWS*NB_COLUMNS][NB_ROWS*NB_COLUMNS];
    Coord positions[NB_ROWS*NB_COLUMNS];
    int n;

  public:
    Constrains(int n = NB_ROWS*NB_COLUMNS) {
      this->n = n;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          data[i][j] = 0;
        }
      }
      int count = 0;
      for (int i = 0; i < NB_ROWS; i++) {
          for (int j = 0; j < NB_COLUMNS; j++) {
              positions[count++] = Coord(i,j);
          }
      }
    }

    void addConstrain(int u, int v) {
      data[u][v] = 1;
      data[v][u] = 1;
    }

    void addConstrain(Coord pos1, Coord pos2) {
      addConstrain(indexOfCell(pos1), indexOfCell(pos2));
    }

    void removeConstrain(int u, int v) {
      data[u][v] = 0;
      data[v][u] = 0;
    }

    void removeConstrain(Coord pos1, Coord pos2) {
      removeConstrain(indexOfCell(pos1), indexOfCell(pos2));
    }

    list<int> getConstrains(int u) {
      list<int> result;
      for (int i = 0; i < n; i ++) {
        if (data[u][i] == 1) result.push_back(i);
      }
      return result;
    }

    list<int> getConstrains(Coord pos) {
      return getConstrains(indexOfCell(pos));
    }

    int indexOfCell(Coord pos) {
      return (NB_ROWS*pos.x + pos.y);
    }

    Coord getCellPosition(int index) {
        return positions[index];
    }

    void clear() {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            data[i][j] = 0;
          }
        }
    }
};

#endif // MODULE_GRAPH_CLASS
