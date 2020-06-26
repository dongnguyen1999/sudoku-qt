#include "sudoku_generator.h"

void print(int* inputs[NB_ROWS]) {
  cout << "Board: " << endl;
  for (int i = 0; i < NB_ROWS; i++) {
    if (i % AREA_SQUARE_SIZE == 0) cout << "-------------------------" << endl;
    for (int j = 0; j < NB_COLUMNS; j++) {
      if (j % AREA_SQUARE_SIZE == 0) cout << "| ";
      cout << inputs[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << "-------------------------" << endl;
}

int main()
{
  SudokuGenerator generator;
  int** inputs = generator.generateSudoku(4000);
  int** puzzle = generator.generateSudokuPuzzleFrom(inputs);
  print(puzzle); 
}