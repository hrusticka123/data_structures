#include "fib_heap_naive.h"
#include "fib_heap.h"
#include <string>
#include <iostream>
#include <fstream>

enum heap_type { naive, normal};

int main(int argc, char ** argv)
{
	fibonacci_heap::common_heap * h = nullptr;

	std::string argument;
	heap_type t = normal;
	std::ofstream decrease_output_max;
	std::ofstream delete_min_output_max;
	std::ofstream decrease_output_avg;
	std::ofstream delete_min_output_avg;

	double delete_min_avg = 0;
	size_t delete_min_max = 0;
	double decrease_avg = 0;
	size_t decrease_max = 0;
	double decrease_count = 0;
	double delete_min_count = 0;

	for (size_t i = 0; i < argc; i++)
	{
		argument = argv[i];
		if (argument == "normal")
			t = normal;
		else if (argument == "naive")
			t = naive;
		else if (argument == "uniform" || argument == "nonuni" || argument == "deep" || argument == "vicious")
		{
			decrease_output_max = std::ofstream("dec_max_" + argument + ((t == normal) ? "_normal" : "_naive"));
			delete_min_output_max = std::ofstream("del_max_" + argument + ((t == normal) ? "_normal" : "_naive"));
			decrease_output_avg = std::ofstream("dec_avg_" + argument + ((t == normal) ? "_normal" : "_naive"));
			delete_min_output_avg = std::ofstream("del_avg_" + argument + ((t == normal) ? "_normal" : "_naive"));
		}
	}

	char command;
	int identifier;
	int key;
	int no_elements;
	while (!std::cin.eof())
	{
		std::cin >> command;
		switch (command)
		{
		case '#':
			if (h != nullptr)
			{
				if (decrease_output_max.is_open()) decrease_output_max << no_elements << " " << decrease_max << std::endl;
				if (delete_min_output_max.is_open()) delete_min_output_max << no_elements << " " << delete_min_max << std::endl;
				if (decrease_output_avg.is_open()) decrease_output_avg << no_elements << " " << decrease_avg / decrease_count << std::endl;
				if (delete_min_output_avg.is_open()) delete_min_output_avg << no_elements << " " << delete_min_avg / delete_min_count << std::endl;
				decrease_max = delete_min_max = decrease_avg = delete_min_avg = decrease_count = delete_min_count = 0;
			}
			std::cin >> no_elements;
			delete h;
			if (t == naive)
				h = new fibonacci_heap::naive_heap(no_elements + 1);
			else
				h = new fibonacci_heap::heap(no_elements + 1);
			break;
		case 'I':
			std::cin >> identifier;
			std::cin >> key;
			if (h != nullptr) h->insert(identifier, key);
			break;
		case 'M':
			if (h != nullptr)
			{
				h->delete_min();
				delete_min_count++;
				if (h->delete_min_steps > delete_min_max)
					delete_min_max = h->delete_min_steps;
				delete_min_avg += h->delete_min_steps;
				h->delete_min_steps = 0;
			}
			break;
		case 'D':
			std::cin >> identifier;
			std::cin >> key;
			if (h != nullptr)
			{
				h->decrease(identifier, key);
				decrease_count++;
				if (h->decrease_steps > decrease_max)
					decrease_max = h->decrease_steps;
				decrease_avg += h->decrease_steps;
				h->decrease_steps = 0;
			}
			break;
		}
	}

	if (decrease_output_max.is_open()) decrease_output_max << no_elements << " " << decrease_max << std::endl;
	if (delete_min_output_max.is_open()) delete_min_output_max << no_elements << " " << delete_min_max << std::endl;
	if (decrease_output_avg.is_open()) decrease_output_avg << no_elements << " " << decrease_avg / decrease_count << std::endl;
	if (delete_min_output_avg.is_open()) delete_min_output_avg << no_elements << " " << delete_min_avg / delete_min_count << std::endl;
	delete h;
}