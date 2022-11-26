#include "../structures.h"
#include "../prototypes.h"

t_construction* init_build(){
    t_construction *build = (t_construction *) malloc(sizeof(t_construction));
    build->niveau = 1;
    build->nb_residents = 0;
    build->eau = true;
    build->quantite_eau = 0;
    build->elec = true;
    build->incendie = true;
    build->style[0] = load_bitmap("../BITMAPS/BUILDS/ruine.bmp", 0);
    build->style[1] = load_bitmap("../BITMAPS/BUILDS/chantier.bmp", 0);
    build->style[2] = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
    build->style[3] = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
    build->style[4] = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
    build->style[5] = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
    return build;
}

void init_batiments_et_constructions(t_affichage* hud){
    t_batiment *batiment = (t_batiment *) malloc(sizeof(t_batiment));
    hud->construction[4][0] = load_bitmap("../BITMAPS/HUD/Nchantier.bmp", 0);     /// Nterrain vague/chantier
    hud->construction[4][1] = load_bitmap("../BITMAPS/HUD/chantier.bmp", 0);     /// terrain vague/chantier
    hud->construction[4][2] = load_bitmap("../BITMAPS/HUD/Schantier.bmp", 0);     /// select_terrain vague/chantier
    hud->construction[5][1] = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);     /// cabane
    hud->construction[6][1] = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);     /// maison
    hud->construction[7][1] = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);     /// immeuble
    hud->construction[8][1] = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);     /// gratte_ciel
    batiment->quantite_ressource = 0;
    batiment->indice_ordre = 0;
    batiment->id_batiment = 0;
}
