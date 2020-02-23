#pragma once
#include  <vector>


class Matrix final {
private:
	typedef unsigned long size_t;
	bool multithreading=false;
	friend class CalculationManager;
	std::vector<std::vector<double>> matrix;
	size_t cols{};
	size_t rows{};
	size_t size() const { return cols * rows; };
	const size_t max_rows_sum{ 300 };
	const size_t max_rows_mult{ 200 };
	const size_t max_rows_det{ 2 };
	
public:																		   
	Matrix() = default;														   
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	Matrix(size_t rank);
	Matrix(size_t _rows, size_t _cols);
	Matrix(size_t _rows, size_t _cols, double value);
	
	Matrix& operator=(const Matrix& mat) = default;
	Matrix& operator=(Matrix&& mat) = default;
	~Matrix()=default;

	void multithreading_on();
	void multithreading_off();
	static Matrix create_diagonal(size_t rank, double value);
	void fill(double value);
	size_t get_rows() const { return rows; }
	Matrix substract_with(const Matrix& another) const;
	Matrix fast_substract_with(const Matrix& another, size_t num_of_threads) const;
	
	Matrix sum_with(const Matrix& another) const;
	Matrix fast_sum_with(const Matrix& another, size_t num_of_threads) const;
	
	Matrix multiply_with(const Matrix& another) const;
	Matrix fast_multiply_with(const Matrix& another, size_t num_of_threads) const;

	double det() const;
	double simple_det(const Matrix& mat) const ;
	double fast_det(const Matrix& mat, size_t num_of_threads) const;
	
	Matrix minor(const Matrix& mat, size_t row_index, size_t col_index) const;
	friend Matrix operator+(const Matrix& first, const Matrix& second);
	friend Matrix operator-(const Matrix& first, const Matrix& second);
	friend Matrix operator*(const Matrix& first, const Matrix& second);
	bool operator==(const Matrix& another) const
	{
		if (rows != another.rows || cols != another.cols) return false;
		for (size_t i = 0; i < rows; i++)
		{
			if (matrix[i] != another.matrix[i]) return false;
		}
		return true;
	}
};

class CalculationManager
{
public:
	
	CalculationManager(const Matrix& _m1, const Matrix& _m2, size_t _count_of_threads) :count_of_threads(_count_of_threads), m1(_m1), m2(_m2) {};
	CalculationManager(const Matrix& _m1, size_t _count_of_threads) :count_of_threads(_count_of_threads), m1(_m1), m2(_m1) {};
	~CalculationManager() = default;
	Matrix sum();
	Matrix multiply();
	Matrix substract();
	double determinant();
private:
	size_t count_of_threads;
	const Matrix& m1;
	const Matrix& m2;
	std::vector<std::pair<size_t, size_t>> make_intervals_for_det() const;
	std::vector<std::pair<size_t, size_t>> make_intervals() const;
	Matrix calculate(void (CalculationManager::* f)(std::pair<size_t, size_t>&, Matrix*));
	void sub_sum(std::pair<size_t, size_t>& interval, Matrix* result);
	void sub_multi(std::pair<size_t, size_t>& interval, Matrix* result);
	void sub_substr(std::pair<size_t, size_t>& interval, Matrix* result);
	double sub_det(std::pair<size_t, size_t>& interval);
	double calculate_det();
};

