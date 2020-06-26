#include <iostream>
using namespace std;
#include"coord.h"

#ifndef MODULES_SDK_GEN_CLASS
#define MODULES_SDK_GEN_CLASS
class SudokuGenerator {
  private:
  int seedCounter = 0;

  static int random(int n) {
    return rand() % n;
  }

  static void swap (int *a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
  }

  bool permutation(int *a, int i, int n, int seed) {
    if (i == n) {
      if (seedCounter >= seed) {
        return true;
      }
      else seedCounter++;
    }
    else {
      for (int j = i; j < n; j++) {
        swap(a, i, j);
        if (permutation(a, i + 1, n, seed)) return true;
        swap(a, i, j);
      }
    }
    return false;
  }

  static void shift(int* a, int n, int offset) {
    int temp[offset];
    for (int i = 0; i < offset; i++) {
      temp[i] = a[i];
    }
    for (int i = 0; i < n-offset; i++) {
      a[i] = a[i+offset];
    }
    for (int i = 0; i < offset; i++) {
      a[n-offset+i] = temp[i];
    }
  }

  public:
  SudokuGenerator() {
    seedCounter = 0;
  }

  int** generateSudoku(int seed = random(362000)) {
    int a[NB_ROWS];
    for (int i = 0; i < NB_ROWS; i++) {
      a[i] = i+1;
    }
    seedCounter = 0;
    permutation(a, 0, NB_ROWS, seed);
    int ** result;
    result = new int*[NB_ROWS];
    for (int i = 0; i < NB_ROWS; i++) {
      result[i] = new int[NB_COLUMNS];
      if (i != 0 && i%AREA_SQUARE_SIZE == 0) {
        shift(a, NB_ROWS, 1);
      } else if (i%AREA_SQUARE_SIZE == 1 || i%AREA_SQUARE_SIZE == 2) {
        shift(a, NB_ROWS, 3);
      }
      for (int j = 0; j < NB_COLUMNS; j++) result[i][j] = a[j];
    }
    return result;
  }

  int** generateSudokuPuzzleFrom(int** result, int nbInitValue = 30) {
    int** puzzle = new int*[NB_ROWS];
    for (int i = 0; i < NB_ROWS; i++) {
      puzzle[i] = new int[NB_COLUMNS];
      for (int j = 0; j < NB_COLUMNS; j++) {
        puzzle[i][j] = result[i][j];
      }
    }
    for (int i = 0; i < NB_ROWS*NB_COLUMNS-nbInitValue; i++) {
      int x, y;
      do {
        x = random(NB_ROWS);
        y = random(NB_COLUMNS);
      } while (puzzle[x][y] == EMPTY);
      puzzle[x][y] = EMPTY;
    }
    return puzzle;
  }
};
#endif // !MODULES_SDK_GEN_CLASS
