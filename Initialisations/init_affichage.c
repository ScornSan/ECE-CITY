#include "../structures.h"
#include "../prototypes.h"



t_affichage* init_affichage(){
    t_affichage *hud = (t_affichage*) malloc(sizeof(t_affichage));
    hud->map = load_bitmap("../BITMAPS/MAP/MAP_1.3.bmp", 0);
    hud->argent = load_bitmap("../BITMAPS/HUD/Cash.bmp", 0);
    hud->bg = load_bitmap("../BITMAPS/HUD/Bg.bmp", 0);
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
    return hud;
}
