#ifndef S21_MATRIX_OOP_HPP
#define S21_MATRIX_OOP_HPP

#include <iostream>

double S21Fabs(double x);

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;
  double** matrix_;

 public:
  // Constructors and a destructor
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Methods
  void MemAlloc();
  void MemFree();
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double CalcMinor(S21Matrix& temp, int a, int b);
  double Determinant();
  void GaussDet(double& result);
  void SwapZeroPivot(S21Matrix& A, int i, int j);
  void CopyMatrix(const S21Matrix& A);
  S21Matrix InverseMatrix();

  // Overloaded operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col);

  // Accessors and mutators
  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);
};

#endif
