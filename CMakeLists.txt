cmake_minimum_required(VERSION 3.22)
project (ECE_CITY C)

set(CMAKE_C_STANDARD 99)

add_executable(ECE_CITY main.c structures.h Initialisations/init_joueur.c prototypes.h Initialisations/init_affichage.c Affichage/affichage_continu.c Affichage/affichage_clic.c Affichage/affichage_constructions.c Initialisations/init_build.c Initialisations/init_ecriture.c Initialisations/init_plateau.c MENU/affichage_menu.c MENU/modes.c SPGM_Informations/lecture_souris.c Interactions_Elements/ajout_construction.c Affichage/affichage_secondaire.c)

target_link_libraries(ECE_CITY -lmingw32 -lalleg44)
