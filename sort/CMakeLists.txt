add_executable(quick_sort_test quick_sort_test.cpp)
add_test(NAME quick_sort_test COMMAND quick_sort_test)

add_executable(heap_sort_test heap_sort_test.cpp)
add_test(NAME heap_sort_test COMMAND heap_sort_test)

add_executable(merge_sort_test merge_sort_test.cpp)
add_test(NAME merge_sort_test COMMAND merge_sort_test)

add_executable(insertion_sort_test insertion_sort_test.cpp)
add_test(NAME insertion_sort_test COMMAND insertion_sort_test)
