# Day 4: a small LIBRARY (geometry) used by two programs.
#
#   add_library(...)                -> compile some .cpp files into a reusable library (.lib)
#   target_include_directories(...) -> where to find its headers. PUBLIC = users of the
#                                      library get this include path too
#   target_link_libraries(...)      -> "this program uses that library"

# --- your version (exercises/) ---
add_library(day04_geometry STATIC exercises/geometry.cpp)
target_include_directories(day04_geometry PUBLIC exercises)
course_warnings(day04_geometry STUB)

add_exercise(day04_ex01 exercises/ex01_geometry_test.cpp)
target_link_libraries(day04_ex01 PRIVATE day04_geometry)

add_exercise(day04_ex02 exercises/ex02_robot_commands.cpp)
target_link_libraries(day04_ex02 PRIVATE day04_geometry)

# --- reference solution (solutions/), same header ---
add_library(day04_geometry_sol STATIC solutions/geometry.cpp)
target_include_directories(day04_geometry_sol PUBLIC exercises)
course_warnings(day04_geometry_sol)

add_exercise(day04_sol01 exercises/ex01_geometry_test.cpp)
target_link_libraries(day04_sol01 PRIVATE day04_geometry_sol)

add_exercise(day04_sol02 solutions/ex02_robot_commands.cpp)
target_link_libraries(day04_sol02 PRIVATE day04_geometry_sol)
