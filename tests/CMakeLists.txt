add_executable(tests symbol_table_test.cpp)
target_link_libraries(tests PRIVATE stochastic)
target_link_libraries(tests PRIVATE doctest::doctest_with_main)

add_test(NAME symbol_table_test COMMAND tests)