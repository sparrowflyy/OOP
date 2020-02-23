#include  "multithreading_matrix.hpp"
#include <thread>
#include <future>
#include <iostream>
#include <deque>
 Matrix::Matrix(size_t _rows, size_t _cols, double value)
 {
	 rows = _rows;
	 cols = _cols;
	 matrix.resize(rows);
	 for (size_t i = 0; i < rows; i++)
	 {
		 matrix[i].resize(cols);
		 for (size_t j = 0; j < cols; j++)
		 {
			 matrix[i][j] = value;
		 }
	 }
 }

void Matrix::multithreading_on()
{
	multithreading = true;
}
void Matrix::multithreading_off()
{
	multithreading = false;
}
Matrix operator+(const Matrix& first, const Matrix& second)
 {
	if (first.multithreading == false && second.multithreading == false)
	{
		return first.sum_with(second);
	}
	return first.fast_sum_with(second, std::thread::hardware_concurrency());
	
 }
Matrix operator*(const Matrix& first, const Matrix& second)
 {
	if (first.multithreading == false && second.multithreading == false)
	{
		return first.multiply_with(second);
	}
	return first.fast_multiply_with(second, std::thread::hardware_concurrency());
 }
Matrix operator-(const Matrix& first, const Matrix& second)
 {
	if (first.multithreading == false && second.multithreading == false)
	{
		return first.substract_with(second);
	}
	return first.fast_substract_with(second, std::thread::hardware_concurrency());
 }

double Matrix::det() const
{
	if (multithreading) return fast_det(*this,std::thread::hardware_concurrency());
	return simple_det(*this);
}


Matrix Matrix::create_diagonal(size_t rank, double value)
{
	Matrix* diagonal = new Matrix(rank, rank);

	for (size_t i = 0; i < rank; i++)
	{
		diagonal->matrix[i][i] = value;
	}

	return *diagonal;
}


Matrix::Matrix(size_t _rows, size_t _cols)
{
	rows = _rows;
	cols = _cols;
	matrix.resize(rows);
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i].resize(cols);
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = 0;
		}
	}
}
void Matrix::fill(double value)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = value;
		}
	}
}
Matrix Matrix::sum_with(const Matrix& another) const
{
	if (rows != another.rows || cols != another.cols) return Matrix();
	Matrix sum(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			sum.matrix[i][j] = matrix[i][j] + another.matrix[i][j];
		}
	}
	return sum;
}

Matrix Matrix::substract_with(const Matrix& another) const
{
	if (rows != another.rows || cols != another.cols) return Matrix();
	Matrix substruct(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			substruct.matrix[i][j] = matrix[i][j] - another.matrix[i][j];
		}
	}
	return substruct;
}

 Matrix Matrix::multiply_with(const Matrix& another) const
{
	 Matrix result(rows, another.cols);
	for (size_t i = 0; i < result.rows; i++)
	{
		for (size_t j = 0; j < result.cols; j++)
		{
			for (size_t k = 0; k < result.cols; k++)
			{
				result.matrix[i][j] += matrix[i][k] * another.matrix[k][j];
			}
		}
	}
	return result;
}
 Matrix::Matrix(size_t rank)
{
	rows = rank;
	cols = rank;
	matrix.resize(rows);
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i].resize(cols);
	}
}


 Matrix Matrix::minor(const Matrix& mat, size_t row_index, size_t col_index) const
 {
	
	 Matrix sub_mat(mat.rows - 1);
	 for (size_t i = 1; i < mat.rows; i++)
	 {
		 const std::vector<double>& temp_row = mat.matrix[i];
		 std::copy(temp_row.begin(), temp_row.begin() + col_index, sub_mat.matrix[i - 1].begin());
		 std::copy(temp_row.begin() + col_index + 1, temp_row.end(), sub_mat.matrix[i - 1].begin() + col_index);
		
	 }
	 return sub_mat;
 }

 double Matrix::simple_det(const Matrix& mat) const
{
	double det = 0;
	int sign = 1;
	if (mat.cols == 1) return mat.matrix[0][0];
	if (mat.cols == 2) return mat.matrix[0][0] * mat.matrix[1][1] - mat.matrix[0][1] * mat.matrix[1][0];
	for (size_t i = 0; i < mat.cols; i++) {
		det = det + (sign * mat.matrix[0][i] * simple_det(minor(mat,0,i)));
		sign = -sign;
	}
	return det;
}


 double CalculationManager::sub_det(std::pair<size_t, size_t>& interval)
 {
	 double det = 0;
	 int sign;
	 if (interval.first % 2 == 0) sign = 1;
	 else sign = -1;
	 for (size_t i = interval.first; i < interval.second; i++) {
		 det = det + (sign * m1.matrix[0][i] * m1.simple_det(m1.minor(m1, 0, i)));
		 sign = -sign;
	 }
	 return det;
 }

 void CalculationManager::sub_substr(std::pair<size_t, size_t>& interval, Matrix* result)
 {
	 std::cout << "Thread (" << interval.first << ";" << interval.second << ") starts work\n";
	 for (size_t i = interval.first; i < interval.second; i++)
	 {
		 for (size_t j = 0; j < result->cols; j++)
		 {

			 result->matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		 }
	 }
	 std::cout << "Thread (" << interval.first << ";" << interval.second << ") end work\n";
 }

 void CalculationManager::sub_sum(std::pair<size_t, size_t>& interval, class Matrix* result)
 {
	 for (size_t i = interval.first; i < interval.second; i++)
	 {
		 for (size_t j = 0; j < result->cols; j++)
		 {

			 result->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		 }
	 }
 }
 void CalculationManager::sub_multi(std::pair<size_t, size_t>& interval, Matrix* result)
 {
	 for (size_t i = interval.first; i < interval.second; i++)
	 {
		 for (size_t j = 0; j < result->cols; j++)
		 {
			 for (size_t k = 0; k < result->cols; k++)
			 {
				 result->matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			 }
		 }
	 }
 }
 
 std::vector<std::pair<size_t, size_t>> CalculationManager::make_intervals() const
 {
	 std::vector<std::pair<size_t, size_t>> intervals;
	 size_t distance = m1.rows / count_of_threads;
	 size_t current_row = 0;
	 for (size_t i = 0; i < count_of_threads; i++)
	 {
		 intervals.push_back({ current_row,current_row + distance });
		 current_row += distance;

	 }
	 intervals[count_of_threads - 1].second = m1.rows;
	 return intervals;
 }
  std::vector<std::pair<size_t, size_t>> CalculationManager::make_intervals_for_det() const
  {
	std::vector<std::pair<size_t, size_t>> intervals;
    size_t distance = m1.rows / count_of_threads;
    if (distance == 0 || m1.rows % count_of_threads != 0) distance++;
    size_t current_row = 0;
    for (; current_row + distance < m1.rows; current_row += distance) {
   	 intervals.push_back({ current_row,current_row + distance });
    }
    intervals.push_back({ current_row,m1.rows });
    return intervals;
  }


 double CalculationManager::calculate_det()
 {
	 auto intervals = make_intervals_for_det();
	 std::vector<std::future<double>> all_futures;
	 for (size_t i = 0; i < intervals.size(); i++) {
		 
		 all_futures.push_back(std::async(std::launch::async, &CalculationManager::sub_det,this, std::ref(intervals[i])));
	 }
	 double det = 0;
	 for (size_t i = 0; i < intervals.size() ; i++)
	 {
		 det += all_futures[i].get();
	 }
	 return det;
 }
 
 Matrix CalculationManager::calculate(void (CalculationManager::*f)(std::pair<size_t, size_t>&, Matrix*))
 {
	 Matrix result(m1.rows, m1.cols);
	 auto intervals = make_intervals();
	 std::vector<std::future<void>> all_futures(intervals.size()-1);
	 for (size_t i = 0; i < all_futures.size();i++)
	 {
		 std::packaged_task<void(std::pair<size_t, size_t>&, Matrix*)> temp_task([&](std::pair<size_t, size_t>& a, Matrix* b) { return (this->*f)(a, b); });
		 all_futures[i] = std::async(std::launch::async, std::move(temp_task), std::ref(intervals[i]), &result);
	 }
	 (this->*f)(intervals[intervals.size() - 1], &result);
	 for (size_t i = 0; i < intervals.size() - 1; i++)
	 {
		 all_futures[i].get();
	 }
	 return result;
	
 }
 double CalculationManager::determinant()
 {
	 return calculate_det();
 }
 Matrix CalculationManager::multiply()
 {
	 return calculate(&CalculationManager::sub_multi);
 }
 Matrix CalculationManager::sum()
 {
	 return calculate(&CalculationManager::sub_sum);
 }
 Matrix CalculationManager::substract()
 {
	 return calculate(&CalculationManager::sub_substr);
 }

 Matrix Matrix::fast_multiply_with(const Matrix& another, size_t num_of_threads) const
 {
	
	 if (cols != another.rows) return Matrix();
	 size_t threads_count = rows / max_rows_mult + 1;
	 if (threads_count == 1) return multiply_with(another);
	 if (threads_count > num_of_threads) threads_count = num_of_threads;
	 CalculationManager multiplier(*this, another, threads_count);
	 return multiplier.multiply();
 }
 double Matrix::fast_det(const Matrix& mat, size_t num_of_threads) const
 {
	 size_t threads_count = rows / max_rows_det;
	 if (threads_count == 1) return simple_det(mat);
	 if (threads_count > num_of_threads) threads_count = num_of_threads;
	 CalculationManager det_calculator(mat, threads_count);
	 return det_calculator.determinant();
 }
 Matrix Matrix::fast_substract_with(const Matrix& another, size_t num_of_threads) const
 {
	 if (rows != another.rows || cols != another.cols) return Matrix();
	 size_t threads_count = rows /max_rows_sum + 1;
	 if (threads_count == 1) return substract_with(another);
	 if (threads_count > num_of_threads) threads_count = num_of_threads;
	 CalculationManager substructor(*this, another, threads_count);
	 return substructor.substract();
 }

 Matrix Matrix::fast_sum_with(const Matrix& another, size_t num_of_threads) const
 {
	 if (rows != another.rows || cols != another.cols) return Matrix();
	 size_t threads_count = rows / max_rows_sum + 1;
 	 if (threads_count==1) return sum_with(another);
	 if (threads_count > num_of_threads) threads_count = num_of_threads;
	 CalculationManager adder(*this, another,threads_count);
	 return adder.sum();
 }