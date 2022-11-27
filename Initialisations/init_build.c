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
    build->style_noir[0] = load_bitmap("../BITMAPS/BUILDS/Nruine.bmp", 0);
    build->style_noir[1] = load_bitmap("../BITMAPS/BUILDS/Nchantier.bmp", 0);
    build->style_noir[2] = load_bitmap("../BITMAPS/BUILDS/Ncabane.bmp", 0);
    build->style_noir[3] = load_bitmap("../BITMAPS/BUILDS/Nmaison.bmp", 0);
    build->style_noir[4] = load_bitmap("../BITMAPS/BUILDS/Nbuilding.bmp", 0);
    build->style_noir[5] = load_bitmap("../BITMAPS/BUILDS/Ngratteciel.bmp", 0);
    return build;
}

t_batiment *init_batiments(){
    t_batiment *batiment = (t_batiment *) malloc(sizeof(t_batiment));
    batiment->style_noir[0] = load_bitmap("../BITMAPS/BUILDS/Nchateau.bmp", 0);     /// Nchateau
    batiment->style[0] = load_bitmap("../BITMAPS/BUILDS/chateau.bmp", 0);     /// chateau
    batiment->style_noir[1] = load_bitmap("../BITMAPS/BUILDS/Ncentrale.bmp", 0);     /// Ncentrale
    batiment->style[1] = load_bitmap("../BITMAPS/BUILDS/centrale.bmp", 0);     /// centrale
    batiment->style_noir[2] = load_bitmap("../BITMAPS/BUILDS/Ncaserne.bmp", 0);     /// Ncaserne
    batiment->style[2] = load_bitmap("../BITMAPS/BUILDS/caserne.bmp", 0);     /// caserne
    batiment->style_noir[3] = load_bitmap("../BITMAPS/BUILDS/Nbanque.bmp", 0);     /// Necole  // Nbanque
    batiment->style[3] = load_bitmap("../BITMAPS/BUILDS/ecole.bmp", 0);     /// ecole
    batiment->quantite_ressource = 5000;
    batiment->indice_ordre = 0;
    return batiment;
}
