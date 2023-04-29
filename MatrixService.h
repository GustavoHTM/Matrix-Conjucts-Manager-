#ifndef MATRIXSERVICE_H
#define MATRIXSERVICE_H

#define ROWS 8
#define COLUMNS 10

struct MatrixAttributes
{
  int matrix[ROWS][COLUMNS];
  int numberOfRowsUsed;
  int numberOfColumnsUsed[ROWS];
};

void invalid();
void option1(struct MatrixAttributes *obj);
void insertValues(struct MatrixAttributes *obj);
void removeRow(struct MatrixAttributes *obj);
void option4(struct MatrixAttributes *obj);
void option5(struct MatrixAttributes *obj);
void printRow(struct MatrixAttributes *obj);
void printMatrix(struct MatrixAttributes *obj);
void searchValue(struct MatrixAttributes *obj);

#endif