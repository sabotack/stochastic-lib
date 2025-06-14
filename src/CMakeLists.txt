add_library(stochastic simulator.cpp vessel.cpp utils.cpp reaction_rule.cpp)
target_include_directories(stochastic PUBLIC ../include ../external/matplotlibcpp)

target_link_libraries(stochastic PRIVATE ${Python3_LIBRARIES})