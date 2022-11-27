#include "../structures.h"
#include "../prototypes.h"

t_joueur* init_joueur(){
    t_joueur *joueur = (t_joueur*) malloc(sizeof(t_joueur));
    joueur->argent = 500000;
    joueur->habitants = 0;
    joueur->niveau = 1;
    joueur->totaleau = 0;
    joueur->totalelec = 0;
    joueur->nb_banques = 0;
    joueur->coeff_banque = 1.0;
    return joueur;
}
