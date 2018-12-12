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
	}
	else if (argc == 1)
		argument = "normal";
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
			if (argument == "naive")
				h = fibonacci_heap::naive_heap();
			else
				h = fibonacci_heap::heap();
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