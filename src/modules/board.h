#include "cell.h"
#include <iostream>
using namespace std;
#define NB_ROWS 9
#define NB_COLUMNS 9
#define AREA_SQUARE_SIZE 3

#ifndef MODULE_BOARD_CLASS
#define MODULE_BOARD_CLASS
class Board {
  private:
    Cell cells[NB_ROWS][NB_COLUMNS];
    Coord cursor;
  public:
    Board() {
      for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
          cells[i][j] = Cell(Coord(i,j));
        }
      }
    }

    Board(int inputs[NB_ROWS][NB_COLUMNS]) {
      for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
          cells[i][j] = Cell(Coord(i,j), inputs[i][j]);
        }
      }
      initConstrains();
    }

    void print() {
      cout << "Board: " << endl;
      for (int i = 0; i < NB_ROWS; i++) {
        if (i % AREA_SQUARE_SIZE == 0) cout << "-------------------------" << endl;
        for (int j = 0; j < NB_COLUMNS; j++) {
          if (j % AREA_SQUARE_SIZE == 0) cout << "| ";
          cout << cells[i][j].getValue() << " " ;
        }
        cout << "|" << endl;
      }
      cout << "-------------------------" << endl;
    }

    Cell& select(Coord position) {
      cursor = position;
      return cells[cursor.x][cursor.y];
    }

    Cell& selectNextEmptyCell() {
      for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
          if (select({i, j}).isEmpty()) {
            return select({i, j});
          }
        }
      }
    }

    void deselect() {
      cursor = Coord();
    }

    void initConstrains() {
      for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
          if (!select(Coord(i,j)).isEmpty()) spreadConstrain();
        }
      }
    }

    list<Cell> spreadConstrain() {
      list<Cell> changed;
      int currentRow = cursor.x;
      int currentColumn = cursor.y;
      if (currentRow == NULL_INDEX || currentRow == NULL_INDEX) changed;
      if (!cells[currentRow][currentColumn].isEmpty()) {
        int value = cells[currentRow][currentColumn].getValue();
        // spread constrain in row
        for (int i = 0; i < NB_COLUMNS; i++) {
          if (cells[currentRow][i].limit(value)) 
            changed.push_back(cells[currentRow][i]);
        }
        // spread constrain in row
        for (int i = 0; i < NB_ROWS; i++) {
          if (cells[i][currentColumn].limit(value))
            changed.push_back(cells[i][currentColumn]);
        }
        // spread constrain in 3x3 area
        for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
          for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
            int areaX = (currentRow/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
            int areaY = currentColumn/AREA_SQUARE_SIZE * AREA_SQUARE_SIZE;
            if (cells[areaX + i][areaY + j].limit(value))
              changed.push_back(cells[areaX+i][areaY+j]);
          }
        }
      }
      return changed;
    }

    void removeContrain(list<Cell> changed) {
      int currentRow = cursor.x;
      int currentColumn = cursor.y;
      int value = cells[currentRow][currentColumn].getValue();
      for (list<Cell>::iterator i = changed.begin(); i != changed.end(); i++) {
        Cell cell = *i;
        select(cell.getPosition()).open(value);
      }
    }

    bool isFilled() {
      for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
          if (cells[i][j].isEmpty()) return false;
        }
      }
      return true;
    }
    static bool assignValuesRecursive(Board board, Coord position, Board* result) {
      list<int> availableValues = board.select(position).getAvailableValues();
      for (list<int>::iterator i = availableValues.begin();
        i != availableValues.end(); i++
      ) {
        int value = *i;
        board.select(position).setValue(value);
        list<Cell> changed = board.spreadConstrain();
        if (board.isFilled()) {
          *result = board;
          return true;
        }
        Coord newPos = board.selectNextEmptyCell().getPosition();
        if (newPos.x != NULL_INDEX && newPos.y != NULL_INDEX) {
          if (assignValuesRecursive(board, newPos, result)) return true;
        }
        board.select(position);
        board.removeContrain(changed);
      }
      return false;
    }
    
    Board solve() {
      Coord startingPoint = selectNextEmptyCell().getPosition();
      Board result; 
      assignValuesRecursive(*this, startingPoint, &result);
      return result;
    }

    bool assignValue(Coord position, int value) {
      if (select(position).checkValue(value)) {
        select(position).setValue(value);
        spreadConstrain();
        return true;
      }
      return false;
    }

};
#endif // MODULE_BOARD_CLASS
