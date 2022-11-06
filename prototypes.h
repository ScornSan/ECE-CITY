
#ifndef ECE_CITY_PROTOTYPES_H
#define ECE_CITY_PROTOTYPES_H

#include "structures.h"

t_affichage* init_affichage();
t_joueur* init_joueur();
t_plateau* init_plateau();
t_batiment* init_batiments();
void reperage_bloc_souris();
void affichage_elements();
void affichage_hud();
void affichage_global();
void quadrillage_test();
void chargement_partie();
void affichage_hud_et_clic();
void affichage_liste_constru();
void dessin_bloc_unique(BITMAP *buffer, int k, int l, t_plateau *plateau, int red, int green, int blue);
void affichage_menu();
void menu();
void placement_construction();
void affichage_son();
int bouton();
void usleep();
void affichage_boutons();

#endif //ECE_CITY_PROTOTYPES_H
