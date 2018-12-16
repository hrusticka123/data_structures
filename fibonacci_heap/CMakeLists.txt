project(fibonacci_heap)

cmake_minimum_required (VERSION 3.8)

add_executable (fibonacci_heap "main.cpp" "fib_heap.cpp" "fib_heap_common.cpp" "fib_heap_naive.cpp")