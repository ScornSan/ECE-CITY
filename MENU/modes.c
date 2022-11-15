#include "../structures.h"
#include "../prototypes.h"

// à incruster en partie

void mode(t_construction * build, t_joueur * joueur)
{
    if (joueur->mode == 0)
    {
        // Mode capitaliste, on ne fait rien, car les constructions dépendent du temps et ne regressent pas
    }
    if (joueur->mode == 1)
    {
        // Mode communiste
        if (build->quantite_eau >= joueur->totaleau && build->quantite_elec >= joueur->totalelec && build->style[build->niveau+1] != NULL)
        {
            // Donc si on est à 15 s, qu'on peut augmenter et que on peut augmenter de niveau, on le fait
            build->niveau = build->niveau+1;
            build->style[build->niveau] = build->style[build->niveau+1];
        }
        if (build->quantite_eau < joueur->totaleau || build->quantite_elec < joueur->totalelec && build->style[build->niveau-1] != NULL)
        {
            // Donc si on est à 15 s, qu'on peut pas augmenter et que on peut regresser de niveau, on le fait
            build->niveau = build->niveau-1;
            build->style[build->niveau] = build->style[build->niveau-1];
        }
    }
}