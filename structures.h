#ifndef ECE_CITY_STRUCTURES_H
#define ECE_CITY_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#define CLIC 200000
#define CONSTRUCT 1
#define EAU 2
#define ELEC 3

typedef struct Constructions{
    int niveau;
    int nb_residents;
    int impot;
    int quantite_eau;
    bool eau;
    bool elec;
    bool incendie;
    time_t timer;
    BITMAP* style[6];
}t_construction;

typedef struct Batiment{

}t_batiment;

typedef struct Joueur{
    int argent;
    int habitants;
    int niveau;
}t_joueur;

typedef struct Bloc{
    int RGB[3];
    int x_bloc;
    int y_bloc;
    int element;    // numéro indiquant de quel bat il s'agit
    int evolution;  // chiffre montrant le niveau d'évolution de l'élément
    BITMAP *b_element;    // bitmap associé à ce batiment
    int affiche;   // booleen pour voir si l'ensemble des blocs d'un meme bat est affiché ou non
}t_bloc;

typedef struct Plateau{
    int lig;
    int lig_mouse;
    int col_mouse;
    int element;
    t_bloc matrice[35][45];
    int matrice_map[35][45];
    int col;
    BITMAP* terrain;
    BITMAP* buffer_pixels;
    t_construction batiment;
}t_plateau;

typedef struct Affichage{
    // instauration des tableaux de BITMAP a 2 dim
    // DIM1     le nombre d'image dans la partie construction (ex: chateau, ecole, caserne, centrale = 4)
    // DIM2      //1er indice les images noircis (ex: Nchateau)
    //2eme indice les images normales (ex: chateau)
    // 3eme indice les images selectionnées (ex: select_chateau)
    BITMAP * construction[4][3];
    BITMAP* argent;
    BITMAP* argent_outline;
    BITMAP* play;
    BITMAP* play_outline;
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
    BITMAP* bg_on;
    BITMAP* cursor;
    BITMAP* chantier;
    BITMAP* cabane;
    BITMAP* maison;
    BITMAP* building;
    BITMAP* gratteciel;
    BITMAP* centrale;
    BITMAP* Noncentrale;
    BITMAP* chateau;
    BITMAP* Nonchateau;
    BITMAP* caserne;
    BITMAP* Noncaserne;
    BITMAP* ecole;
    BITMAP* Nonecole;
    BITMAP* Schateau;
    BITMAP* Scaserne;
    BITMAP* Scentrale;
    BITMAP* Secole;
}t_affichage;

/*
typedef struct Affichage{
    BITMAP* argent;
    BITMAP* argent_outline;
    BITMAP* play;
    BITMAP* play_outline;
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
    BITMAP* bg_on;
    BITMAP* cursor;
    BITMAP* chantier;
    BITMAP* cabane;
    BITMAP* maison;
    BITMAP* building;
    BITMAP* gratteciel;
    BITMAP* centrale;
    BITMAP* Noncentrale;
    BITMAP* chateau;
    BITMAP* Nonchateau;
    BITMAP* caserne;
    BITMAP* Noncaserne;
    BITMAP* ecole;
    BITMAP* Nonecole;
    BITMAP* Schateau;
    BITMAP* Scaserne;
    BITMAP* Scentrale;
    BITMAP* Secole;
}t_affichage;*/

#endif //ECE_CITY_STRUCTURES_H
