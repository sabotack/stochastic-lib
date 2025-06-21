function(add_example_executable name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE stochastic)
endfunction()

# RQ5: Demonstrate the application of the library on the three examples (shown in Fig. 1, 2, 3).
add_example_executable(abc abc.cpp)
add_example_executable(circadian circadian_rhythm.cpp)
add_example_executable(seihr seihr.cpp)

add_example_executable(seihr_estimation seihr_estimation.cpp)
add_example_executable(seihr_multiple.cpp seihr_multiple.cpp)
