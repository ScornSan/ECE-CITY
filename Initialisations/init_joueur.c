#include "../structures.h"
#include "../prototypes.h"

t_joueur* init_joueur(){
    t_joueur *joueur = (t_joueur*) malloc(sizeof(t_joueur));
    joueur->argent = 500000;
    joueur->habitants = 0;
    joueur->niveau = 1;
    return joueur;
}

t_affichage* init_affichage(){
    t_affichage *hud = (t_affichage*) malloc(sizeof(t_affichage));
    hud->argent = load_bitmap("BITMAPS/HUD/Cash.bmp", 0);
    hud->bg = load_bitmap("BITMAPS/HUD/Bg.bmp", 0);
    hud->eau = load_bitmap("BITMAPS/HUD/Water.bmp", 0);
    hud->eau_outline = load_bitmap("BITMAPS/HUD/WaterOutline.bmp", 0);
    hud->elec = load_bitmap("BITMAPS/HUD/Energy.bmp", 0);
    hud->elec_outline = load_bitmap("BITMAPS/HUD/EnergyOutline.bmp", 0);
    hud->construct = load_bitmap("BITMAPS/HUD/Construct.bmp", 0);
    hud->construct_outline = load_bitmap("BITMAPS/HUD/ConstructOutline.bmp", 0);
    hud->habitants = load_bitmap("BITMAPS/HUD/Habitants.bmp", 0);
    return hud;
}