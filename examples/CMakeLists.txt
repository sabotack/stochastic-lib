add_executable(abc abc.cpp)
target_link_libraries(abc PRIVATE stochastic)

add_executable(circadian circadian_rhythm.cpp)
target_link_libraries(circadian PRIVATE stochastic)

add_executable(seihr seihr.cpp)
target_link_libraries(seihr PRIVATE stochastic)

add_executable(seihr_estimation seihr_estimation.cpp)
target_link_libraries(seihr_estimation PRIVATE stochastic)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE stochastic)
