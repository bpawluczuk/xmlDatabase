cmake_minimum_required(VERSION 3.12)
project(xmlDatabase)

set(CMAKE_CXX_STANDARD 17)

add_executable(xmlDatabase main.cpp xmlDatabase.h xmlDatabase.cpp column.h record.h record.cpp column.cpp dataset.h dataset.cpp icolumn.h irecord.h)