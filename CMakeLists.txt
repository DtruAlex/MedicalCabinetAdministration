cmake_minimum_required(VERSION 3.24)
project(c__Project)

set(CMAKE_CXX_STANDARD 17)


add_executable(c__Project main.cpp Patient.cpp Patient.h ListPatients.cpp ListPatients.h Product.cpp Product.h Inventory.cpp Inventory.h Bill.cpp Bill.h ListBill.cpp ListBill.h)