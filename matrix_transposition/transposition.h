#pragma once
#include <iostream>

//bounds of matrix/submatrix
class bounds
{
public:
	bounds(size_t start_row, size_t start_column, size_t rows, size_t columns) : start_row(start_row), start_column(start_column), end_row(rows), end_column(columns) { }
	size_t start_column = 0;
	size_t start_row = 0;
	size_t end_column = 0;
	size_t end_row = 0;
};

//array representation of matrix
class marray
{
public:
	marray(bounds b) : b(b) { arr = new int[b.end_column*b.end_row]; columns_ = b.end_column; };
	~marray() { delete[] arr; };
	//gets value (i,j)
	int get(size_t i, size_t j);
	//sets value to (i,j)
	void set(size_t i, size_t j, int value);
	size_t rows();
	size_t columns();
private:
	int * arr;
	bounds b;
	size_t columns_;
};

//one element of matrix
using element = std::pair<size_t, size_t>;


//general purpose class for matrix transposes
class matrix
{
public:
	//classic real constructor
	matrix(std::ostream * output, marray &arr) :output(output), arr(arr) {};
	//only swap contructor
	matrix(std::ostream * output, bool swap, marray &mock) :output(output), swap_(swap), arr(mock) {};
	~matrix() { };
	void trivial_transpose(bounds b, bool swap_different = false);
	void co_transpose(bounds b, size_t z);
	//output
	void out();
private:
	void swap(element swap1, element swap2);
	void transpose_on_diagonal(bounds b);
	void transpose_and_swap(bounds b1, bounds b2);
	std::ostream * output;
	size_t small_size;
	marray &arr;
	bool swap_ = false;
};