
#ifndef ECE_CITY_PROTOTYPES_H
#define ECE_CITY_PROTOTYPES_H

#include "structures.h"

t_affichage* init_affichage();
t_joueur* init_joueur();
t_plateau* init_plateau();
void init_batiments_et_constructions();
t_file * cases_adjacentes();
void affichage_hud();
void affichage_hud_et_clic();
void affichage_liste_constru();
void affichage_menu();
void menu();
void dijkstra();
void affichage_son();
int bouton();
void usleep();
void affichage_boutons();
void placement_construction();
void reperage_bloc_souris();
int ajout_routes();
void dessin_bloc_unique();
void affichage_elements();
void selection_ajout_routes();

#endif //ECE_CITY_PROTOTYPES_H
