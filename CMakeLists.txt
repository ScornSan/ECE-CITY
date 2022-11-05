cmake_minimum_required(VERSION 3.22)
project (ECE_CITY C)

set(CMAKE_C_STANDARD 99)

add_executable(ECE_CITY main.c structures.h Initialisations/init_joueur.c prototypes.h Initialisations/init_affichage.c Affichage/affichage_continu.c Initialisations/init_build.c Affichage/affichage_constructions.c Affichage/affichage_clic.c Initialisations/init_plateau.c "Infos generales/lecture_souris.c")

target_link_libraries(ECE_CITY -lmingw32 -lalleg44)
