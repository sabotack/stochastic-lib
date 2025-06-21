function(add_stochastic_test test_name source_file)
    add_executable(${test_name} ${source_file})
    target_link_libraries(${test_name} PRIVATE stochastic doctest::doctest_with_main)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

function(add_stochastic_bm bm_name source_file)
    add_executable(${bm_name} ${source_file})
    target_link_libraries(${bm_name} PRIVATE stochastic benchmark::benchmark_main)
    add_test(NAME ${bm_name} COMMAND ${bm_name})
endfunction()

# RQ9: Implement unit tests (e.g. test symbol table methods, their failure cases, pretty-printing reaction rules, etc).
add_stochastic_test(symbol_table_test symbol_table_test.cpp)
add_stochastic_test(vessel_test vessel_test.cpp)
add_stochastic_test(utils_test utils_test.cpp)
add_stochastic_test(rrule_test reaction_rule_test.cpp)

# RQ10: Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 100 simulations
# a single core, multiple cores, or improved implementation). Record the timings and make your conclusions.
add_stochastic_bm(sim_bm simulator_bm.cpp)
