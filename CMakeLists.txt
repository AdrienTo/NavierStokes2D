cmake_minimum_required (VERSION 2.6)
project (NavierStokes2D)
add_executable(NavierStokes2D main.cpp matrix.hpp matrix.cpp Mesh1D.hpp Mesh1D.cpp Discretization.hpp Discretization.cpp)