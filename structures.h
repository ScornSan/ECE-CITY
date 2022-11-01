#ifndef ECE_CITY_STRUCTURES_H
#define ECE_CITY_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>

typedef struct Constructions{
    int niveau[5];
    int nb_residents;
    int impot;
    int quantite_eau;
    int quantite_elec;
    bool eau;
    bool elec;
    bool incendie;
    time_t timer;
    BITMAP* style[5];
}t_construction;

typedef struct Batiment{

}t_batiment;

typedef struct Joueur{
    int argent;
    int habitants;
    int niveau;
}t_joueur;

typedef struct Plateau{
    int element;
    int lig;
    int col;
    t_construction batiment;
};

typedef struct Affichage{
    BITMAP* argent;
    BITMAP* argent_outline;
    BITMAP* play;
    BITMAP* pause;
    BITMAP* pause_outline;
    BITMAP* fast;
    BITMAP* fast_outline;
    BITMAP* habitants;
    BITMAP* habitants_outline;
    BITMAP* eau;
    BITMAP* eau_outline;
    BITMAP* elec;
    BITMAP* elec_outline;
    BITMAP* construct;
    BITMAP* construct_outline;
    BITMAP* bg;
    BITMAP* cursor;
    BITMAP* chantier;
    BITMAP* cabane;
    BITMAP* maison;
    BITMAP* building;
    BITMAP* gratteciel;
}t_affichage;

#endif //ECE_CITY_STRUCTURES_H
