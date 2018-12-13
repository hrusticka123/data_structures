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
			h.reset();
			if (argument == "naive")
				h = fibonacci_heap::naive_heap();
			else
				h = fibonacci_heap::heap();
			//dev
			std::cout << std::endl << command << " " << key << std::endl;
			break;
		case 'I':
			std::cin >> identifier;
			std::cin >> key;
			//dev
			std::cout << std::endl << command << " " << identifier << " " << key << std::endl;
			h.insert(identifier, key);
			break;
		case 'M':
			//dev
			std::cout << std::endl << command << std::endl;
			h.delete_min();
			break;
		case 'D':
			std::cin >> identifier;
			std::cin >> key;
			//dev
			std::cout << std::endl << command << " " << identifier << " " << key << std::endl;
			h.decrease(identifier, key);
			break;
		}
	}
}