#include "../structures.h"
#include "../prototypes.h"

t_construction* init_build(){
    t_construction *build = (t_construction *) malloc(sizeof(t_construction));
    build->niveau = 1;
    build->nb_residents = 0;
    build->eau = false;
    build->quantite_eau = 0;
    build->elec = false;
    build->incendie = false;
    build->style[0] = load_bitmap("../BITMAPS/BUILDS/ruine.bmp", 0);
    build->style[1] = load_bitmap("../BITMAPS/BUILDS/chantier.bmp", 0);
    build->style[2] = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
    build->style[3] = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
    build->style[4] = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
    build->style[5] = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
    return build;
}

t_batiment * init_batiments(){
    t_batiment *batiment = (t_batiment*)malloc(sizeof(t_batiment));
    batiment->construction[0][0] = load_bitmap("../BITMAPS/HUD/Nchateau.bmp", 0);       /// NON chateau
    batiment->construction[0][1] = load_bitmap("../BITMAPS/HUD/chateau.bmp", 0);       /// chateau
    batiment->construction[0][2] = load_bitmap("../BITMAPS/HUD/chateau_selec.bmp", 0);      /// select_chateau

    batiment->construction[1][0] = load_bitmap("../BITMAPS/HUD/Ncentrale.bmp", 0);     /// NON centrale
    batiment->construction[1][1] = load_bitmap("../BITMAPS/HUD/centrale.bmp", 0);      /// centrale
    batiment->construction[1][2] = load_bitmap("../BITMAPS/HUD/centrale_selec.bmp", 0);      /// select_centrale

    batiment->construction[2][0] = load_bitmap("../BITMAPS/HUD/Ncaserne.bmp", 0);       /// NON caserne
    batiment->construction[2][1] = load_bitmap("../BITMAPS/HUD/caserne.bmp", 0);      /// caserne
    batiment->construction[2][2] = load_bitmap("../BITMAPS/HUD/caserne_selec.bmp", 0);     /// select_caserne

    batiment->construction[3][0] = load_bitmap("../BITMAPS/HUD/Necole.bmp", 0);     /// NON ecole
    batiment->construction[3][1] = load_bitmap("../BITMAPS/HUD/ecole.bmp", 0);     /// ecole
    batiment->construction[3][2] = load_bitmap("../BITMAPS/HUD/ecole_selec.bmp", 0);     /// select_ecole
    return batiment;
}
