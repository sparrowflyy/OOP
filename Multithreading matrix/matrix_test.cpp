#include "./gtest/gtest.h"
#include "..//matrix/multithreading_matrix.hpp"
#include <chrono>
static const unsigned long big_size_for_mult = 2300;
static const unsigned long big_size_for_sum = 7000;

static Matrix big_mult_matrix(big_size_for_mult, big_size_for_mult, 666);
static Matrix big_diagonal_matrix= Matrix::create_diagonal(big_size_for_mult, 1);
static Matrix big_filled_matrix(big_size_for_sum, big_size_for_sum,666);
static Matrix big_empty_matrix(big_size_for_sum, big_size_for_sum);

void time_test_sum(Matrix& A, Matrix& B, size_t thread_count)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	Matrix C = A.fast_sum_with(B, thread_count);
	std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
	std::cout << "Parallel Execution of sum " << A.get_rows()<<"x"<<A.get_rows()<<" with "<<thread_count<<" threads : "<<dur.count() << std::endl;
}
void time_test_mult(Matrix& A, Matrix& B, size_t thread_count)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	Matrix C = A.fast_multiply_with(B, thread_count);
	std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
	std::cout << "Parallel Execution of mult " << A.get_rows() << "x" << A.get_rows() << " with " << thread_count << " threads : " << dur.count() << std::endl;
}
void time_test_det(Matrix& A,size_t thread_count)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	double det = A.fast_det(A,thread_count);
	std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
	std::cout << "Parallel Execution of det " << A.get_rows() << "x" << A.get_rows() << " with " << thread_count << " threads : " << dur.count() << std::endl;
}
//TEST(time_research, sum100)
//{
//	Matrix A(100, 100, 1);
//	Matrix B(100, 100, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.sum_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_sum(A, B, i);
//	}
//}
//TEST(time_research,sum500)
//{
//	Matrix A(500, 500, 1);
//	Matrix B(500, 500, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.sum_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//	
//	for (size_t i = 2; i<=10;i++)
//	{
//		time_test_sum(A, B, i);
//	}
//}
//TEST(time_research, sum1000)
//{
//	Matrix A(1000, 1000, 1);
//	Matrix B(1000, 1000, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.sum_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_sum(A, B, i);
//	}
//}
//TEST(time_research, sum5000)
//{
//	Matrix A(5000, 5000, 1);
//	Matrix B(5000, 5000, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.sum_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_sum(A, B, i);
//	}
//}
//TEST(time_research, mult100)
//{
//	Matrix A(100, 100, 1);
//	Matrix B(100, 100, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.multiply_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_mult(A, B, i);
//	}
//}
//TEST(time_research, mult500)
//{
//	Matrix A(500, 500, 1);
//	Matrix B(500, 500, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.multiply_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of multiply " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_mult(A, B, i);
//	}
//}
//TEST(time_research, mult1000)
//{
//	Matrix A(1000, 1000, 1);
//	Matrix B(1000, 1000, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.multiply_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of multiply " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_mult(A, B, i);
//	}
//}
//TEST(time_research, mult2000)
//{
//	Matrix A(2000, 2000, 1);
//	Matrix B(2000, 2000, 1);
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	Matrix C = A.multiply_with(B);
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 10; i++)
//	{
//		time_test_mult(A, B, i);
//	}
//}
//TEST(time_research, det10x10)
//{
//	Matrix A(10, 10, 1);
//
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	double det = A.det();
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of det " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 6; i+=2)
//	{
//		time_test_det(A, i);
//	}
//}
//TEST(time_research, det11x11)
//{
//	Matrix A(11, 11, 1);
//
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	double det = A.det();
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of det " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 6; i += 2)
//	{
//		time_test_det(A, i);
//	}
//}
//TEST(time_research, det12x12)
//{
//	Matrix A(12, 12, 1);
//
//	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
//	double det = A.det();
//	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
//	std::cout << "Execution of det " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;
//
//	for (size_t i = 2; i <= 6; i += 2)
//	{
//		time_test_det(A, i);
//	}
//}
TEST(Matrix_determinant, simple) {
	Matrix identity = Matrix::create_diagonal(11, 2);											   //таблица в экселе
	double det = identity.det();																   //async
	EXPECT_TRUE(det == 2048);																				 
}
TEST(Matrix_determinant, multithreading) {
	Matrix identity = Matrix::create_diagonal(11, 2);
	identity.multithreading_on();
	double det = identity.det();
	EXPECT_TRUE(det == 2048);
}

TEST(Matrix_multiplication, simple) {

	Matrix multiplied = big_diagonal_matrix * big_mult_matrix;
	EXPECT_TRUE(multiplied == big_mult_matrix);
}
TEST(Matrix_multiplication, multithreading) {
	big_diagonal_matrix.multithreading_on();
	Matrix multiplied = big_diagonal_matrix * big_mult_matrix;
	big_diagonal_matrix.multithreading_off();
	EXPECT_TRUE(multiplied == big_mult_matrix);
}
TEST(Matrix_sum, simple) {
	
	Matrix sum = big_empty_matrix + big_filled_matrix;
	EXPECT_TRUE(sum == big_filled_matrix);
}
TEST(Matrix_sum, multithreading) {
	big_empty_matrix.multithreading_on();
	Matrix sum = big_empty_matrix + big_filled_matrix;
	big_empty_matrix.multithreading_off();
	EXPECT_TRUE(sum==big_filled_matrix);
}
TEST(Matrix_substract, simple) {
	Matrix substract = big_filled_matrix - big_empty_matrix;
	EXPECT_TRUE(substract == big_filled_matrix);
}
TEST(Matrix_substract, multithreading) {
	big_filled_matrix.multithreading_on();
	Matrix substract = big_filled_matrix - big_empty_matrix;
	EXPECT_TRUE(substract == big_filled_matrix);
	
}

TEST(pause,pause)
{
	getchar();
}