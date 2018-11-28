#include "transposition.h"
#include <chrono> 
#include <thread>
using namespace std::chrono;

//trivial implementation of swap
void matrix::trivial_transpose(bounds b, bool swap_different)
{
	for (size_t i = b.start_row; i < b.end_row; i++)
	{
		for (size_t j = (swap_different) ? b.start_column : i + 1; j < b.end_column; j++)
		{
			swap({ i,j }, { j,i });
		}
	}
}

//sets small size and calls transpose_on_diagonal()
void matrix::co_transpose(bounds b, size_t z)
{
	small_size = (z < 4) ? 4 : z;
	transpose_on_diagonal(b);
}

//outputs matrix
void matrix::out()
{
	for (size_t i = 0; i < arr.rows(); i++)
	{
		for (size_t j = 0; j < arr.columns(); j++)
		{
			if (j == 0 && i != 0)
				*output << std::endl;
			*output << arr.get(i, j) << " ";
		}
	}
	*output << std::endl;
}

//swap 2 elements
void matrix::swap(element swap1, element swap2)
{
	//we simply want output what elements are going to be swapped
	if (swap_)
		*output << "X " << swap1.first << " " << swap1.second << " " << swap2.first << " " << swap2.second << std::endl;
	//actually swap them, output nothing
	else
	{
		int temp = arr.get(swap1.first, swap1.second);
		arr.set(swap1.first, swap1.second, arr.get(swap2.first, swap2.second));
		arr.set(swap2.first, swap2.second, temp);
	}
}

//diagonal transpose as proposed on lecture
void matrix::transpose_on_diagonal(bounds b)
{
	size_t rows = b.end_row - b.start_row;
	size_t columns = b.end_column - b.start_column;
	//small enough, do it trivially
	if (rows*columns <= small_size)
	{
		trivial_transpose(b);
	}
	else
	{
		//split for another diagonal transposes
		size_t first_diagonal_size = b.start_column + columns / 2;
		size_t second_diagonal_size = b.start_column + columns;
		transpose_on_diagonal({ b.start_row,b.start_column,first_diagonal_size,first_diagonal_size });
		transpose_on_diagonal({ first_diagonal_size,first_diagonal_size,second_diagonal_size,second_diagonal_size });
		transpose_and_swap({ b.start_row,first_diagonal_size,first_diagonal_size,second_diagonal_size }, { first_diagonal_size,b.start_column,second_diagonal_size,first_diagonal_size });
	}
}

//transpose and swap as proposed on lecture
void matrix::transpose_and_swap(bounds b1, bounds b2)
{
	size_t rows = b1.end_row - b1.start_row;
	size_t columns = b1.end_column - b1.start_column;
	//small enough, do it trivially
	if (rows*columns <= small_size)
	{
		trivial_transpose(b1, true);
	}
	else
	{
		//one of them is too small to be split, split only to 2
		if (columns == 1 || rows == 1)
		{
			size_t first_diagonal_size;
			size_t second_diagonal_size;
			if (columns == 1)
			{
				first_diagonal_size = b1.start_row + rows / 2;
				second_diagonal_size = b1.start_column + 1;
			}
			else
			{
				first_diagonal_size = b1.start_row + 1;
				second_diagonal_size = b1.start_column + columns / 2;
			}
			transpose_and_swap({ b1.start_row, b1.start_column,first_diagonal_size,second_diagonal_size }, { b2.start_row,b2.start_column,second_diagonal_size,first_diagonal_size });
			transpose_and_swap({ b1.start_row, b1.start_column,first_diagonal_size,second_diagonal_size }, { b2.start_row,b2.start_column,second_diagonal_size,first_diagonal_size });
		}
		//split to 4 as equally as possible
		else
		{
			size_t column_split = b1.start_column + columns / 2;
			size_t row_split = b1.start_row + rows / 2;

			transpose_and_swap({ b1.start_row,b1.start_column,row_split,column_split },
				{ b2.start_row,b2.start_column,column_split,row_split });
			transpose_and_swap({ b1.start_row,column_split,row_split,b1.end_column },
				{ column_split,b2.start_column,b2.end_row,row_split });
			transpose_and_swap({ row_split,b1.start_column,b1.end_row,column_split },
				{ b2.start_row,row_split,column_split,b2.end_column });
			transpose_and_swap({ row_split,column_split,b1.end_row,b1.end_column },
				{ column_split,row_split,b2.end_row,b2.end_column });
		}
	}
}

//computes position and returns (i,j) element
int marray::get(size_t i, size_t j)
{
	return arr[(i + b.start_row)*columns_ + j + b.start_column];
}


void marray::set(size_t i, size_t j, int value)
{
	arr[(i + b.start_row)*columns_ + j + b.start_column] = value;
}


size_t marray::rows()
{
	return b.end_row - b.start_row;
}

size_t marray::columns()
{
	return b.end_column - b.start_column;
}
