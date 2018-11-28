#include "optimal_tree.h"

using namespace splay_tree;

void optimal_tree::splay(size_t index)
{
	if (frequencies.size() <= index)frequencies.resize(index+1,0);
	frequencies[index]++;
}

void splay_tree::optimal_tree::insert(size_t index){}

double optimal_tree::get_average_path_length()
{
	size_t max_index = frequencies.size();

	std::vector<size_t> sums(max_index+1);

	size_t sum = 0;
	for (size_t i = 0; i < max_index; ++i)
	{
		sums[i] = sum;
		sum += frequencies[i];
	}
	sums[max_index] = sum;

	std::vector<std::vector<size_t>> roots(max_index);
	std::vector<std::vector<size_t>> costs(max_index);

	for (size_t i = 0; i < max_index; i++)
	{
		roots[i].resize(max_index);
		costs[i].resize(max_index);
	}

	for (size_t i = 0; i < max_index; i++)
	{
		costs[i][i] = frequencies[i];
		roots[i][i] = i;
	}

	for (size_t i = 2; i < max_index; ++i)
	{
		for (size_t j = 1; j <= max_index - i; ++j)
		{
			size_t k = j + i - 1;
			costs[j][k] = INT_MAX;
			for (size_t l = roots[j][k-1]; l <= roots[j+1][k]; ++l)
			{
				size_t temp = (l < k ? costs[l + 1][k] : 0) + (l > j ? costs[j][l-1] : 0) + sums[k + 1] - sums[j];
				if (costs[j][k] > temp)
				{
					costs[j][k] = temp;
					roots[j][k] = l;
				}
			}
		}
	}
	double divide = ((double)(sums[max_index] - sums[0]));
	return costs[1][max_index - 1] / divide;
}