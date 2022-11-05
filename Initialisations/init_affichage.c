#include "../structures.h"
#include "../prototypes.h"

t_affichage* init_affichage(){
    t_affichage *hud = (t_affichage*) malloc(sizeof(t_affichage));
    hud->argent = load_bitmap("../BITMAPS/HUD/Cash.bmp", 0);
    hud->bg = load_bitmap("../BITMAPS/HUD/Bg.bmp", 0);
    hud->bg_on = load_bitmap("../BITMAPS/HUD/BgOn.bmp", 0);
    hud->eau = load_bitmap("../BITMAPS/HUD/Water.bmp", 0);
    hud->eau_outline = load_bitmap("../BITMAPS/HUD/WaterOutline.bmp", 0);
    hud->elec = load_bitmap("../BITMAPS/HUD/Energy.bmp", 0);
    hud->elec_outline = load_bitmap("../BITMAPS/HUD/EnergyOutline.bmp", 0);
    hud->construct = load_bitmap("../BITMAPS/HUD/Construct.bmp", 0);
    hud->construct_outline = load_bitmap("../BITMAPS/HUD/ConstructOutline.bmp", 0);
    hud->habitants = load_bitmap("../BITMAPS/HUD/Habitants.bmp", 0);
    hud->habitants_outline = load_bitmap("../BITMAPS/HUD/HabitantsOutline.bmp", 0);
    hud->cursor = load_bitmap("../BITMAPS/HUD/Cursor.bmp", 0);
    hud->chantier = load_bitmap("../BITMAPS/BUILDS/chantier.bmp", 0);
    hud->cabane = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
    hud->maison = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
    hud->building = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
    hud->gratteciel = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
    hud->chateau = load_bitmap("../BITMAPS/HUD/chateau.bmp", 0);
    hud->centrale = load_bitmap("../BITMAPS/HUD/centrale.bmp", 0);
    hud->caserne = load_bitmap("../BITMAPS/HUD/caserne.bmp", 0);
    hud->ecole = load_bitmap("../BITMAPS/HUD/ecole.bmp", 0);
    hud->Nonchateau = load_bitmap("../BITMAPS/HUD/Nchateau.bmp", 0);
    hud->Noncentrale = load_bitmap("../BITMAPS/HUD/Ncentrale.bmp", 0);
    hud->Noncaserne = load_bitmap("../BITMAPS/HUD/Ncaserne.bmp", 0);
    hud->Nonecole = load_bitmap("../BITMAPS/HUD/Necole.bmp", 0);
    hud->Scaserne = load_bitmap("../BITMAPS/HUD/caserne_selec.bmp", 0);
    hud->Scentrale = load_bitmap("../BITMAPS/HUD/centrale_selec.bmp", 0);
    hud->Schateau = load_bitmap("../BITMAPS/HUD/chateau_selec.bmp", 0);
    hud->Secole = load_bitmap("../BITMAPS/HUD/ecole_selec.bmp", 0);
    return hud;
}

t_plateau* init_plateau(){
    t_plateau *plateau = (t_plateau*) malloc(sizeof(t_plateau));
    plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_1.5.bmp", 0);
}
