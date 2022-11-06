
#ifndef ECE_CITY_PROTOTYPES_H
#define ECE_CITY_PROTOTYPES_H

#include "structures.h"

t_affichage* init_affichage();
t_joueur* init_joueur();
t_plateau* init_plateau();
t_batiment* init_batiments();
void affichage_hud();
void affichage_hud_et_clic();
void affichage_liste_constru();
void affichage_menu();
void menu();
void affichage_son();
int bouton();
void usleep();
void affichage_boutons();
void placement_construction();
void reperage_bloc_souris();
void ajout_routes();
void dessin_bloc_unique();
void affichage_elements();

#endif //ECE_CITY_PROTOTYPES_H
