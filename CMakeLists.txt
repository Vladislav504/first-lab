cmake_minimum_required(VERSION 3.16)
project(First_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(First_lab main.cpp WateringRecord.cpp WateringRecord.h RecordsCollection.h RecordsCollection.cpp Record.cpp Record.h BranchRecord.cpp BranchRecord.h)