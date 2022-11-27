#ifndef ECE_CITY_STRUCTURES_H
#define ECE_CITY_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#define CLIC 80000
#define RIEN 0
#define CONSTRUCT 1
#define EAU 2
#define ELEC 3
#define CHATEAU_EAU 1
#define CENTRALE 2
#define CASERNE 3
#define BANQUE 4
#define CHANTIER 5
#define CABANE 6
#define MAISON 7
#define BUILDING 8
#define GRATTECIEL 9
#define RUINE 10
#define TVAGUE_CP 16
#define TVAGUE_CP_BP 15
#define ROUTES 13
#define TVAGUE 14
#define TIME_CYCLE 3

#define X 50
#define Y 10

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
    struct maillon * predecesseur;
}t_maillon;


typedef struct file{
    t_maillon * debut;
    t_maillon * fin;
}t_file;

typedef struct Bloc{
    int RGB[3];
    int x_bloc;
    int y_bloc;
    int id_element;
    int ligne;
    int colonne;
    int element;    // numéro indiquant de quel bat il s'agit
    BITMAP *b_element;    // bitmap associé à ce batiment
    int id_bitmap; // 0 a 11 pour les routes, voir pour la suite
    int affiche;   // booleen pour voir si l'ensemble des blocs d'un meme bat est affiché ou non
}t_bloc;

typedef struct Constructions{
    t_bloc premier_bloc;     //infos du premier blocs en haut a gauche de la constru (tous les blocs de la meme constru ont les meme parametres)
    int niveau;
    int nb_residents;
    int id_element;
    int element;
    t_maillon * derniere_case_chemin;
    int quantite_eau;
    int distance_chateau;
    int quantite_elec;
    int distance_centrale;
    int eau;
    int elec;
    int incendie;
    time_t timer;
    BITMAP* style[6];
    BITMAP* style_noir[6];
    int id_style;
}t_construction;

typedef struct Batiment{    // 4x6
    t_bloc premier_bloc;     //infos du premier blocs en haut a gauche de la constru (tous les blocs de la meme constru ont les meme parametres)
    int quantite_ressource;
    int id_batiment;
    int element;
    t_construction** ordre_distribution;
    int indice_ordre;
    BITMAP* style[4];  // 0 = chateau ; 1 = cenrale, 2 = caserne, 3 = ecole
    BITMAP* style_noir[4];
}t_batiment;

typedef struct Joueur{
    char pseudo[20];
    int argent;
    int habitants;
    int niveau;
    int totaleau;
    int totalelec;
    int mode;
    int nb_banques;
    float coeff_banque;
}t_joueur;


typedef struct Plateau{
    int screenx;
    int screeny;
    int lig_mouse;
    int col_mouse;
    t_bloc matrice[35][45];
    int matrice_map[35][45];
    int id_terrain;
    int etape;
    int niveau;
    BITMAP* buffer_pixels;
    BITMAP* calque_pixels;
    t_construction** habitations; // max 175 constructions 3x3 sur la map
    int indice_tab_habitations;
    t_batiment** batiments; // max 66 batiments 4x6 sur la map
    int indice_tab_batiment;
    BITMAP * routes[11];
    BITMAP* bitmap_bat[4];
    BITMAP* style_noir[4];
    BITMAP* terrain[5];
    BITMAP* terrain_noir[5];
}t_plateau;

typedef struct Affichage{
    BITMAP* argent;
    BITMAP* regles;
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
    BITMAP* banque;
    BITMAP* Nonbanque;
    BITMAP* Sbanque;
    BITMAP* route;
    BITMAP* Nonroute;
    BITMAP* Sroute;
    BITMAP* son_on;
    BITMAP* son_off;
    BITMAP* accueil;
    BITMAP* bouton_menu;
    BITMAP* bouton_menu2;
    BITMAP* credits;
    BITMAP* nom;
    BITMAP* mode;
    BITMAP* construction[9][3];
    SAMPLE * son_menu;
    SAMPLE * son_jeu;
    BITMAP * buffer2;
    BITMAP * pauseselec;
    BITMAP* terrain[5];
    BITMAP* terrain_noir[5];
    BITMAP * case_eau;
    BITMAP * case_elec;
    BITMAP * moinsun;
    BITMAP * moinsdeux;
    BITMAP * Nbanque;

}t_affichage;

#endif //ECE_CITY_STRUCTURES_H
