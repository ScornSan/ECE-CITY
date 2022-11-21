#ifndef ECE_CITY_STRUCTURES_H
#define ECE_CITY_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#define CLIC 200000
#define CONSTRUCT 1
#define EAU 2
#define ELEC 3
#define CHATEAU_EAU 1
#define CENTRALE 2
#define CASERNE 3
#define ECOLE 4
#define CHANTIER 5
#define CABANE 6
#define MAISON 7
#define BUILDING 8
#define GRATTECIEL 9
#define RUINE 10
#define TVAGUE_CP 11
#define TVAGUE_CP_BP 12
#define ROUTES 13
#define TVAGUE 14

/* 0 : rien
 * 1 : chateau d'eau
 * 2 : centrale
 * 3 : caserne
 * 4 : école
 * 5 : chantier
 * 6 : cabane
 * 7 : maison
 * 8 : building
 * 9 : gratte ciel
 * 10 : ruine
 * 11 : terrain vague + construction possible
 * 12 : terrain vague + construction ou batiment possible
 * 13 : routes
 * 14 : terrain vague

*/

typedef struct maillon{
    int ligne;
    int colonne;
    int compteur;
    struct maillon * suivant;
    struct maillon * precedent;
}t_maillon;

typedef struct pile{
    t_maillon * debut;
    t_maillon * fin;
}t_pile;

typedef struct Bloc{
    int RGB[3];
    int x_bloc;
    int y_bloc;
    int id_element;
    int ligne;
    int colonne;
    int element;    // numéro indiquant de quel bat il s'agit
    BITMAP *b_element;    // bitmap associé à ce batiment
    int affiche;   // booleen pour voir si l'ensemble des blocs d'un meme bat est affiché ou non
}t_bloc;

typedef struct Constructions{
    t_bloc premier_bloc;     //infos du premier blocs en haut a gauche de la constru (tous les blocs de la meme constru ont les meme parametres)
    int niveau;
    int nb_residents;
    int impot;
    int id_element;
    t_bloc surface[3][3];
    int quantite_eau;
    int distance_chateau;
    int quantite_elec;
    int distance_centrale;
    bool eau;
    bool elec;
    bool incendie;
    time_t timer;
    BITMAP* style[6];
}t_construction;

typedef struct Batiment{    // 4x6
    t_bloc premier_bloc;     //infos du premier blocs en haut a gauche de la constru (tous les blocs de la meme constru ont les meme parametres)
    int quantite_ressource;
    int id_batiment;
    t_bloc surface[4][6];
    BITMAP* style[3];
    t_construction* ordre_distribution[150];
    int indice_ordre;
}t_batiment;

typedef struct Joueur{
    char pseudo[20];
    int argent;
    int habitants;
    int niveau;
    int totaleau;
    int totalelec;
    int mode;
}t_joueur;


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
    t_construction* habitations[175]; // max 175 constructions 3x3 sur la map
    int indice_tab_habitations;
    t_batiment* batiments[66]; // max 66 batiments 4x6 sur la map
    int indice_tab_batiment;
    BITMAP * routes[11];
}t_plateau;

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
    BITMAP* Schantier;
    BITMAP* Nonchantier;
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
    BITMAP* route;
    BITMAP* Nonroute;
    BITMAP* Sroute;
    BITMAP* son_on;
    BITMAP* son_off;
    BITMAP* accueil;
    BITMAP* bouton_menu;
    BITMAP* credits;
    BITMAP* nom;
    BITMAP* mode;
    BITMAP* construction[9][3];
}t_affichage;

#endif //ECE_CITY_STRUCTURES_H
