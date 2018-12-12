#include "fib_heap_naive.h"
#include "fib_heap.h"
#include <string>
#include <iostream>

int main(int argc, char ** argv)
{
	fibonacci_heap::common_heap h;

	std::string argument;
	if (argc == 2)
	{
		argument = argv[1];
		if (argument == "naive")
			h = fibonacci_heap::naive_heap();
		else if (argument == "normal")
			h = fibonacci_heap::heap();
		else
			throw std::exception("Unknown argument");
	}
	else if (argc == 1)
		h = fibonacci_heap::heap();
	else 
		throw std::exception("Wrong arguments");

	char command;
	int identifier;
	int key;
	while (!std::cin.eof())
	{
		std::cin >> command;
		switch (command)
		{
		case '#':
			std::cin >> key;
			h.reset();
			break;
		case 'I':
			std::cin >> identifier;
			std::cin >> key;
			h.insert(identifier, key);
			break;
		case 'M':
			h.delete_min();
			break;
		case 'D':
			std::cin >> identifier;
			std::cin >> key;
			h.decrease(identifier, key);
			break;
		}
	}
}