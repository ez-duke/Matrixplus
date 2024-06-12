#include "tests.hpp"

TEST(Constructors, BasicConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(3, matrix.GetRows());
  EXPECT_EQ(3, matrix.GetCols());
}

TEST(Constructors, CreateInvalid) {
  EXPECT_THROW(S21Matrix matrix(-2, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix matrix(3, -1), std::invalid_argument);
  EXPECT_THROW(S21Matrix matrix(0, 1), std::invalid_argument);
  EXPECT_THROW(S21Matrix matrix(4, 0), std::invalid_argument);
}

TEST(Constructors, ConstructorWithParams) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(3, matrix.GetRows());
  EXPECT_EQ(4, matrix.GetCols());
}

TEST(Constructors, CopyConstructor) {
  S21Matrix matrix(5, 4);
  S21Matrix matrix_copy(matrix);
  EXPECT_EQ(5, matrix.GetRows());
  EXPECT_EQ(4, matrix.GetCols());
  EXPECT_EQ(5, matrix_copy.GetRows());
  EXPECT_EQ(4, matrix_copy.GetCols());
  EXPECT_EQ(1, matrix == matrix_copy);
}

TEST(Constructors, MoveConstructor) {
  S21Matrix matrix(5, 5);
  S21Matrix matrix_copy(std::move(matrix));
  EXPECT_EQ(0, matrix.GetRows());
  EXPECT_EQ(0, matrix.GetCols());
  EXPECT_EQ(5, matrix_copy.GetRows());
  EXPECT_EQ(5, matrix_copy.GetCols());
  EXPECT_EQ(1, matrix == matrix_copy);
}

TEST(Operators, EqOperator) {
  S21Matrix matrix_3x3(3, 3);
  S21Matrix matrix2_3x3(3, 3);
  matrix2_3x3(0, 0) = 1, matrix2_3x3(0, 1) = 2, matrix2_3x3(0, 2) = 3;
  matrix2_3x3(1, 0) = 0, matrix2_3x3(1, 1) = 3, matrix2_3x3(1, 2) = 2;
  matrix2_3x3(2, 0) = 1, matrix2_3x3(2, 1) = 2, matrix2_3x3(2, 2) = 1;
  matrix_3x3(0, 0) = 1, matrix_3x3(0, 1) = 2, matrix_3x3(0, 2) = 3;
  matrix_3x3(1, 0) = 0, matrix_3x3(1, 1) = 3, matrix_3x3(1, 2) = 2;
  matrix_3x3(2, 0) = 1, matrix_3x3(2, 1) = 2, matrix_3x3(2, 2) = 1;
  EXPECT_EQ(1, (matrix_3x3) == (matrix2_3x3));
}

TEST(Operators, EqOperatorInvalid) {
  S21Matrix matrix_3x3(3, 3);
  S21Matrix matrix2_3x3(3, 3);
  matrix2_3x3(0, 0) = 1, matrix2_3x3(0, 1) = 2, matrix2_3x3(0, 2) = 0;
  matrix2_3x3(1, 0) = 0, matrix2_3x3(1, 1) = 3, matrix2_3x3(1, 2) = 2;
  matrix2_3x3(2, 0) = 1, matrix2_3x3(2, 1) = 2, matrix2_3x3(2, 2) = 1;
  matrix_3x3(0, 0) = 1, matrix_3x3(0, 1) = 2, matrix_3x3(0, 2) = 3;
  matrix_3x3(1, 0) = 0, matrix_3x3(1, 1) = 3, matrix_3x3(1, 2) = 2;
  matrix_3x3(2, 0) = 1, matrix_3x3(2, 1) = 2, matrix_3x3(2, 2) = 1;
  EXPECT_EQ(0, (matrix_3x3) == (matrix2_3x3));
}

TEST(Operators, SumAssignOperator) {
  S21Matrix matrix(2, 3);
  S21Matrix matrix_2x3(2, 3);
  matrix_2x3(0, 0) = 11, matrix_2x3(0, 1) = 11, matrix_2x3(0, 2) = 11;
  matrix_2x3(1, 0) = 11, matrix_2x3(1, 1) = 11, matrix_2x3(1, 2) = 11;
  matrix += matrix_2x3;
  EXPECT_EQ(1, matrix == matrix_2x3);
}

TEST(Operators, SubAssignOperator) {
  S21Matrix matrix(2, 3);
  S21Matrix matrix_2x3(2, 3);
  matrix_2x3(0, 0) = 11, matrix_2x3(0, 1) = 11, matrix_2x3(0, 2) = 11;
  matrix_2x3(1, 0) = 11, matrix_2x3(1, 1) = 11, matrix_2x3(1, 2) = 11;
  S21Matrix validation(2, 3);
  validation(0, 0) = -11, validation(0, 1) = -11, validation(0, 2) = -11;
  validation(1, 0) = -11, validation(1, 1) = -11, validation(1, 2) = -11;
  matrix -= matrix_2x3;
  EXPECT_EQ(1, matrix == validation);
}

TEST(Operators, MultMatrixAssignOperator) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 2, matrix(0, 1) = 4;
  matrix(1, 0) = 5, matrix(1, 1) = 2;
  matrix(2, 0) = 8, matrix(2, 1) = 3;
  S21Matrix matrix2x3(2, 3);
  matrix2x3(0, 0) = 3, matrix2x3(0, 1) = 2, matrix2x3(0, 2) = 0;
  matrix2x3(1, 0) = 4, matrix2x3(1, 1) = 5, matrix2x3(1, 2) = 6;
  matrix *= matrix2x3;
  EXPECT_DOUBLE_EQ(22, matrix(0, 0));
  EXPECT_DOUBLE_EQ(24, matrix(0, 1));
  EXPECT_DOUBLE_EQ(24, matrix(0, 2));
  EXPECT_DOUBLE_EQ(23, matrix(1, 0));
  EXPECT_DOUBLE_EQ(20, matrix(1, 1));
  EXPECT_DOUBLE_EQ(12, matrix(1, 2));
  EXPECT_DOUBLE_EQ(36, matrix(2, 0));
  EXPECT_DOUBLE_EQ(31, matrix(2, 1));
  EXPECT_DOUBLE_EQ(18, matrix(2, 2));
}

TEST(Operators, MultNumberAssignOperator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = 2;
  matrix(1, 0) = 3, matrix(1, 1) = 4;
  matrix *= 2.56;
  EXPECT_DOUBLE_EQ(2.56, matrix(0, 0));
  EXPECT_DOUBLE_EQ(5.12, matrix(0, 1));
  EXPECT_DOUBLE_EQ(7.68, matrix(1, 0));
  EXPECT_DOUBLE_EQ(10.24, matrix(1, 1));
}

TEST(Operators, SumOperator) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2, matrix(0, 1) = 4, matrix(0, 2) = 1;
  matrix(1, 0) = 5, matrix(1, 1) = 2, matrix(1, 2) = 0;
  matrix(2, 0) = 8, matrix(2, 1) = 3, matrix(2, 2) = 2;
  S21Matrix matrix2x3(3, 3);
  matrix2x3(0, 0) = 4, matrix2x3(0, 1) = 5, matrix2x3(0, 2) = 3;
  matrix2x3(1, 0) = 2, matrix2x3(1, 1) = 5, matrix2x3(1, 2) = 1;
  matrix2x3(2, 0) = 0, matrix2x3(2, 1) = 5, matrix2x3(2, 2) = 2;
  S21Matrix res_matrix = matrix + matrix2x3;
  EXPECT_DOUBLE_EQ(6, res_matrix(0, 0));
  EXPECT_DOUBLE_EQ(9, res_matrix(0, 1));
  EXPECT_DOUBLE_EQ(4, res_matrix(0, 2));
  EXPECT_DOUBLE_EQ(7, res_matrix(1, 0));
  EXPECT_DOUBLE_EQ(7, res_matrix(1, 1));
  EXPECT_DOUBLE_EQ(1, res_matrix(1, 2));
  EXPECT_DOUBLE_EQ(8, res_matrix(2, 0));
  EXPECT_DOUBLE_EQ(8, res_matrix(2, 1));
  EXPECT_DOUBLE_EQ(4, res_matrix(2, 2));
}

TEST(Operators, SumAssignOperatorInvalid) {
  S21Matrix matrix(3, 3);
  S21Matrix tmp_matrix(2, 2);
  EXPECT_THROW((matrix) += (tmp_matrix), std::logic_error);
}

TEST(Operators, SubOperator) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2, matrix(0, 1) = 4, matrix(0, 2) = 1;
  matrix(1, 0) = 5, matrix(1, 1) = 2, matrix(1, 2) = 0;
  matrix(2, 0) = 8, matrix(2, 1) = 3, matrix(2, 2) = 2;
  S21Matrix matrix2x3(3, 3);
  matrix2x3(0, 0) = 4, matrix2x3(0, 1) = 5, matrix2x3(0, 2) = 3;
  matrix2x3(1, 0) = 2, matrix2x3(1, 1) = 5, matrix2x3(1, 2) = 1;
  matrix2x3(2, 0) = 0, matrix2x3(2, 1) = 5, matrix2x3(2, 2) = 2;
  S21Matrix res_matrix = matrix - matrix2x3;
  EXPECT_DOUBLE_EQ(-2, res_matrix(0, 0));
  EXPECT_DOUBLE_EQ(-1, res_matrix(0, 1));
  EXPECT_DOUBLE_EQ(-2, res_matrix(0, 2));
  EXPECT_DOUBLE_EQ(3, res_matrix(1, 0));
  EXPECT_DOUBLE_EQ(-3, res_matrix(1, 1));
  EXPECT_DOUBLE_EQ(-1, res_matrix(1, 2));
  EXPECT_DOUBLE_EQ(8, res_matrix(2, 0));
  EXPECT_DOUBLE_EQ(-2, res_matrix(2, 1));
  EXPECT_DOUBLE_EQ(0, res_matrix(2, 2));
}

TEST(Operators, SubAssignOperatorInvalid) {
  S21Matrix matrix(3, 3);
  S21Matrix tmp_matrix(2, 2);
  EXPECT_THROW((matrix) -= (tmp_matrix), std::logic_error);
}

TEST(Operators, MulMatrixOperator) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 2, matrix(0, 1) = 4;
  matrix(1, 0) = 5, matrix(1, 1) = 2;
  matrix(2, 0) = 8, matrix(2, 1) = 3;
  S21Matrix matrix2x3(2, 3);
  matrix2x3(0, 0) = 3, matrix2x3(0, 1) = 2, matrix2x3(0, 2) = 0;
  matrix2x3(1, 0) = 4, matrix2x3(1, 1) = 5, matrix2x3(1, 2) = 6;
  S21Matrix res_matrix = matrix * matrix2x3;
  EXPECT_DOUBLE_EQ(22, res_matrix(0, 0));
  EXPECT_DOUBLE_EQ(24, res_matrix(0, 1));
  EXPECT_DOUBLE_EQ(24, res_matrix(0, 2));
  EXPECT_DOUBLE_EQ(23, res_matrix(1, 0));
  EXPECT_DOUBLE_EQ(20, res_matrix(1, 1));
  EXPECT_DOUBLE_EQ(12, res_matrix(1, 2));
  EXPECT_DOUBLE_EQ(36, res_matrix(2, 0));
  EXPECT_DOUBLE_EQ(31, res_matrix(2, 1));
  EXPECT_DOUBLE_EQ(18, res_matrix(2, 2));
}

TEST(Operators, MultMatrixOperatorInvalid) {
  S21Matrix matrix1x1(1, 1);
  matrix1x1(0, 0) = 1;
  S21Matrix matrix2x1(2, 1);
  matrix2x1(0, 0) = 2;
  EXPECT_THROW((matrix1x1) * (matrix2x1), std::logic_error);
}

TEST(Operators, MultNumberOperator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = 2;
  matrix(1, 0) = 3, matrix(1, 1) = 4;
  matrix = matrix * 2.56;
  EXPECT_DOUBLE_EQ(2.56, matrix(0, 0));
  EXPECT_DOUBLE_EQ(5.12, matrix(0, 1));
  EXPECT_DOUBLE_EQ(7.68, matrix(1, 0));
  EXPECT_DOUBLE_EQ(10.24, matrix(1, 1));
}

TEST(Operators, OperatorParentheses) {
  S21Matrix matrix;
  matrix(1, 2) = 3;
  EXPECT_DOUBLE_EQ(matrix(1, 2), 3);
}

TEST(Operators, OperatorParenthesesInvalid) {
  S21Matrix matrix;
  EXPECT_THROW(matrix(2, -2), std::out_of_range);
  EXPECT_THROW(matrix(3, 0), std::out_of_range);
}

TEST(Methods, Determinant1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 21;
  EXPECT_DOUBLE_EQ(21, matrix.Determinant());
}

TEST(Methods, Determinant1x2Invalid) {
  S21Matrix matrix(1, 2);
  EXPECT_THROW(matrix.Determinant(), std::logic_error);
}

TEST(Methods, Determinant2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 14, matrix(0, 1) = 22;
  matrix(1, 0) = 31, matrix(1, 1) = 12;
  EXPECT_DOUBLE_EQ(-514, matrix.Determinant());
}

TEST(Methods, Determinant3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0, matrix(0, 1) = 12, matrix(0, 2) = 22;
  matrix(1, 0) = 1, matrix(1, 1) = 2, matrix(1, 2) = 22;
  matrix(2, 0) = 1, matrix(2, 1) = 12, matrix(2, 2) = 1;

  EXPECT_DOUBLE_EQ(472, matrix.Determinant());
}

TEST(Methods, CalcCompl4x4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1, matrix(0, 1) = 20, matrix(0, 2) = 4, matrix(0, 3) = 3;
  matrix(1, 0) = 14, matrix(1, 1) = 4, matrix(1, 2) = 21, matrix(1, 3) = 3;
  matrix(2, 0) = 22, matrix(2, 1) = 12, matrix(2, 2) = 15, matrix(2, 3) = 5;
  matrix(3, 0) = 12, matrix(3, 1) = 5, matrix(3, 2) = 12, matrix(3, 3) = 2;
  S21Matrix ref(4, 4);
  ref(0, 0) = 108, ref(0, 1) = -168, ref(0, 2) = -52, ref(0, 3) = 84;
  ref(1, 0) = 389, ref(1, 1) = 286, ref(1, 2) = -217, ref(1, 3) = -1747;
  ref(2, 0) = -23, ref(2, 1) = 214, ref(2, 2) = 219, ref(2, 3) = -1711;
  ref(3, 0) = -688, ref(3, 1) = -712, ref(3, 2) = -144, ref(3, 3) = 5168;
  EXPECT_EQ(1, matrix.CalcComplements() == ref);
}

TEST(Methods, CalcCompl1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 3;
  S21Matrix ref(1, 1);
  ref(0, 0) = 1;
  EXPECT_EQ(1, matrix.CalcComplements() == ref);
}

TEST(Methods, CalcComplInvalid) {
  S21Matrix matrix(3, 2);
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(Methods, Inverse) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2, matrix(0, 1) = 5, matrix(0, 2) = 7;
  matrix(1, 0) = 8, matrix(1, 1) = 3, matrix(1, 2) = 4;
  matrix(2, 0) = 5, matrix(2, 1) = -2, matrix(2, 2) = -3;
  S21Matrix ref(3, 3);
  ref(0, 0) = -1, ref(0, 1) = 1, ref(0, 2) = -1;
  ref(1, 0) = 44, ref(1, 1) = -41, ref(1, 2) = 48;
  ref(2, 0) = -31, ref(2, 1) = 29, ref(2, 2) = -34;
  EXPECT_EQ(1, matrix.InverseMatrix() == ref);
}

TEST(Methods, Inverse1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 4.0;
  S21Matrix ref(1, 1);
  ref(0, 0) = 1.0 / 4.0;
  EXPECT_EQ(1, matrix.InverseMatrix() == ref);
}

TEST(Methods, InverseInvalid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = 1;
  matrix(1, 0) = 1, matrix(1, 1) = 1;
  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(AccessMutate, SetColumns) {
  S21Matrix matrix(6, 12);
  matrix.SetCols(6);
  EXPECT_EQ(6, matrix.GetCols());
}

TEST(AccessMutate, SetColumnsInvalid) {
  S21Matrix matrix(6, 12);
  EXPECT_THROW(matrix.SetCols(0), std::invalid_argument);
}

TEST(AccessMutate, SetRows) {
  S21Matrix matrix(12, 6);
  matrix.SetRows(6);
  EXPECT_EQ(6, matrix.GetRows());
}

TEST(AccessMutate, SetRowsInvalid) {
  S21Matrix matrix(12, 6);
  EXPECT_THROW(matrix.SetRows(0), std::invalid_argument);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
