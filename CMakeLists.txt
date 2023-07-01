cmake_minimum_required(VERSION 3.16.3)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp instructions.h instructions.h run.h initial.h order.h judgeinstype.h reg.h RS.h SLB.h ROB.h BRANCH.h ALU.h clear.h instype.h ins_to_do.h updating.h ROB_to_run.h little.h SLB_to_exu.h RS_running.h debug.h debug.h)
