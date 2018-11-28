#include "transposition.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std::chrono;

int main(int argc, char ** argv)
{
	//initializing values
	bool trivial = true;
	std::string argument;
	std::ostream * output(&std::cout);
	std::ofstream file_out;
	size_t small_size = 9;
	bool swap = false;
	for (size_t i = 1; i < argc; i++)
	{
		argument = argv[i];
		//trivial run
		if (argument == "-t")
		{
			trivial = true;
		}
		//cache-oblivious run
		else if (argument == "-co")
		{
			trivial = false;
			if (argc > i+1)
				small_size = std::stoi(argv[++i]);
		}
		//output file
		else if (argument == "-i")
		{
			if (argc > i+1)
			{
				file_out.open(argv[++i]);
				output = &file_out;
			}
		}
		//only output swapping, do not actually swap
		else if (argument == "-s")
		{
			swap = true;
		}
	}

	//start from 54
	double k = 54;
	//we want real transposition
	if (!swap)
	{
		while (k < 130)
		{
			//compute size of matrix
			size_t size = std::ceil(std::pow(2, (k / 9)));
			//create matrix-array representation
			marray matrix_array({ 0,0,size,size });
			//initialize matrix class with matrix_array
			matrix m(output, matrix_array);
			//start counting
			auto start = high_resolution_clock::now();
			if (trivial)
				m.trivial_transpose({ 0,0, matrix_array.rows(),matrix_array.columns() });
			else
				m.co_transpose({ 0,0, matrix_array.rows(),matrix_array.columns() },small_size);
			//stop counting
			auto stop = high_resolution_clock::now();
			//output the size along with counter
			*output << size << " " << duration_cast<microseconds>(stop - start).count() << std::endl;
			k++;
		}
	}
	//only swapping simulation
	else
	{
		//only mock for matrix reference, will not be used
		marray matrix_array_mock({ 0,0,4,4 });
		matrix m(output, swap, matrix_array_mock);
		while (k < 120)
		{
			size_t size = std::ceil(std::pow(2, (k / 9)));
			//creates input for simulator
			*output << "N " << size << std::endl;
			//actual bounds for swap simulation
			if (trivial)
				m.trivial_transpose({ 0,0,size,size });
			else
				m.co_transpose({ 0,0,size,size }, small_size);
			*output << "E" << std::endl;
			k++;
		}
	}
	std::cin.get();
}