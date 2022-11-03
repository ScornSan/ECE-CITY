
#ifndef ECE_CITY_PROTOTYPES_H
#define ECE_CITY_PROTOTYPES_H

#include "structures.h"

t_affichage* init_affichage();
t_plateau* init_plateau();
t_joueur* init_joueur();
void affichage_hud();
void affichage_hud_et_clic();
void affichage_liste_constru();
void affichage_boutons();
int bouton();
void usleep();

#endif //ECE_CITY_PROTOTYPES_H
