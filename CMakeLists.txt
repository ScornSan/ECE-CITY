cmake_minimum_required(VERSION 3.22)
project (ECE_CITY C)

set(CMAKE_C_STANDARD 99)

add_executable(ECE_CITY main.c structures.h Initialisations/init_joueur.c prototypes.h)

target_link_libraries(ECE_CITY -lmingw32 -lalleg44)
