add_exercise(day00_hello hello.cpp)

add_exercise(day00_ex01 exercises/ex01_edit_and_run.cpp)
add_exercise(day00_sol01 solutions/ex01_edit_and_run.cpp)

# fix_me/fix_me.cpp is deliberately NOT built here: it contains mistakes on purpose,
# and you compile it by hand with cl (see lesson Part 5). Its corrected version:
add_exercise(day00_sol02 solutions/fix_me.cpp)
