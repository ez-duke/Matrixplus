#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) {
  try {
    MemAlloc();
  } catch (const std::exception& err) {
    std::cerr << err.what();
  }
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Rows and columns must be > 0");
  }
  try {
    MemAlloc();
  } catch (const std::exception& err) {
    std::cerr << err.what();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  try {
    MemAlloc();
    CopyMatrix(other);
  } catch (const std::exception& err) {
    std::cerr << err.what();
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { MemFree(); }

void S21Matrix::MemAlloc() {
  if (matrix_ != nullptr) throw std::exception();

  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::MemFree() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool equal = true;
  for (int i = 0; equal && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (S21Fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-6) {
        equal = false;
      }
    }
  }
  return equal;
}

double S21Fabs(double x) {
  if (x < 0.0) x = -x;
  return x;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Can't sum matrices with different sizes\n");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Can't subtract matrices with different sizes\n");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "Can't multiply matrices with 1st matrix's columns count not being "
        "equal to 2nd matrix's rows count\n");
  }

  S21Matrix result(rows_, other.cols_);
  double sum;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      sum = 0.0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      result.matrix_[i][j] = sum;
    }
  }
  std::swap(matrix_, result.matrix_);
  rows_ = result.rows_;
  cols_ = result.cols_;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("Can't count matrix with different dimensions\n");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix temp(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[i][j] = CalcMinor(temp, i, j);
      }
    }
  }
  return result;
}

double S21Matrix::CalcMinor(S21Matrix& temp, int a, int b) {
  double det = 0;
  int count = 0, rank = rows_ - 1;

  for (int i = 0; i <= rank; i++) {
    for (int j = 0; j <= rank; j++) {
      if (i == a || j == b) continue;
      temp.matrix_[count / rank][count % rank] = matrix_[i][j];
      count++;
    }
  }

  det = temp.Determinant();
  if ((a + b) % 2 && S21Fabs(det) >= 1e-6) det *= -1;
  return det;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("Can't count matrix with different dimensions\n");
  }

  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    GaussDet(result);
  }
  return result;
}

void S21Matrix::GaussDet(double& result) {
  S21Matrix temp(rows_, cols_);
  temp.CopyMatrix(*this);
  int n = rows_, sign = 0, error = 0;

  for (int i = 0; !error && i < n; i++) {
    int bup = i;
    while (i < n && S21Fabs(temp.matrix_[i][bup]) < 1e-6) i++;
    if (i == n) {
      error = 1;
    } else if (bup != i) {
      SwapZeroPivot(temp, bup, i);
      sign = !sign;
    }
    i = bup;

    for (int k = i + 1; !error && k < n; k++) {
      double ratio = temp.matrix_[k][i] / temp.matrix_[i][i];
      for (int j = 0; i < n - 1 && j < n; j++) {
        temp.matrix_[k][j] -= temp.matrix_[i][j] * ratio;
      }
    }
  }

  if (!error) {
    result = 1;
    for (int i = 0; i < rows_; i++) result *= temp.matrix_[i][i];
    if (sign && S21Fabs(result) >= 1e-6) result *= -1;
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& A) {
  int rows, cols;

  if (rows_ < A.rows_)
    rows = rows_;
  else
    rows = A.rows_;

  if (cols_ < A.cols_)
    cols = cols_;
  else
    cols = A.cols_;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = A.matrix_[i][j];
    }
  }
}

void S21Matrix::SwapZeroPivot(S21Matrix& A, int i, int j) {
  double* temp = A.matrix_[i];
  A.matrix_[i] = A.matrix_[j];
  A.matrix_[j] = temp;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (S21Fabs(det) < 1e-6) {
    throw std::logic_error("Can't count matrix with its determinant = 0\n");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    result = CalcComplements();
    result = result.Transpose();
    result.MulNumber(1.0 / det);
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return (EqMatrix(other)); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix temp(other);
  std::swap(matrix_, temp.matrix_);
  rows_ = other.rows_;
  cols_ = other.cols_;
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double const number) {
  MulNumber(number);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix_[row][col];
}

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetRows(int rows) {
  if (rows == rows_) return;

  if (rows < 1) {
    throw std::invalid_argument("Number of rows should not be less than 1\n");
  }

  S21Matrix temp(*this);
  MemFree();
  rows_ = rows;
  MemAlloc();
  CopyMatrix(temp);
}

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetCols(int cols) {
  if (cols == cols_) return;

  if (cols < 1) {
    throw std::invalid_argument(
        "Number of columns should not be less than 1\n");
  }

  S21Matrix temp(*this);
  MemFree();
  cols_ = cols;
  MemAlloc();
  CopyMatrix(temp);
}
