#include "board.h"

// Board recursive(Board board, int x, int y) {
//   list<int> availableValues = board.select(x, y).getAvailableValues();
//   for (list<int>::iterator i = availableValues.begin();
//     i != availableValues.end(); i++
//   ) {
//       int value = *i;
//       board.select(x, y).setValue(value);
//       board.spreadConstrain();
//       Board result;
//       if (y < NB_COLUMNS-1) result = recursive(board, x, y+1);
//       else if (x < NB_ROWS-1) result = recursive(board, x+1, 0);
//       if (result.isFilled()) return result;
//       board.removeContrain();
//   }
//   return board;
// }

int main()
{
  int inputs[NB_ROWS][NB_COLUMNS] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
  };

  Board board(inputs);
  // Board board;
  board.print();
  
  Board result = board.solve();
  result.print();
}