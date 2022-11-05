
#ifndef ECE_CITY_PROTOTYPES_H
#define ECE_CITY_PROTOTYPES_H

#include "structures.h"

t_affichage* init_affichage();
t_plateau* init_plateau();
t_joueur* init_joueur();
void affichage_hud();
void quadrillage(BITMAP *buffer);
void affichage_global(t_affichage * hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau);
void affichage_hud_et_clic();
void reperage_bloc_souris(t_plateau* plateau);
void affichage_liste_constru();
void affichage_boutons();
void placement_construction(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int indice);
int bouton();
void usleep();

#endif //ECE_CITY_PROTOTYPES_H
