# Day 3: a small LIBRARY (geometry) used by two programs.
#
#   add_library(...)                -> compile some .cpp files into a reusable library (.lib)
#   target_include_directories(...) -> where to find its headers. PUBLIC = users of the
#                                      library get this include path too
#   target_link_libraries(...)      -> "this program uses that library"

# --- your version (exercises/) ---
add_library(day03_geometry STATIC exercises/geometry.cpp)
target_include_directories(day03_geometry PUBLIC exercises)
course_warnings(day03_geometry STUB)

add_exercise(day03_ex01 exercises/ex01_geometry_test.cpp)
target_link_libraries(day03_ex01 PRIVATE day03_geometry)

add_exercise(day03_ex02 exercises/ex02_robot_commands.cpp)
target_link_libraries(day03_ex02 PRIVATE day03_geometry)

# --- reference solution (solutions/), same header ---
add_library(day03_geometry_sol STATIC solutions/geometry.cpp)
target_include_directories(day03_geometry_sol PUBLIC exercises)
course_warnings(day03_geometry_sol)

add_exercise(day03_sol01 exercises/ex01_geometry_test.cpp)
target_link_libraries(day03_sol01 PRIVATE day03_geometry_sol)

add_exercise(day03_sol02 solutions/ex02_robot_commands.cpp)
target_link_libraries(day03_sol02 PRIVATE day03_geometry_sol)
