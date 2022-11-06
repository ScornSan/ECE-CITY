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
