#include "../structures.h"
#include "../prototypes.h"

t_font* init_font()
{
    t_font *font = (t_font*) malloc(sizeof(t_font));
    font->myfont = load_font("../FONT/franklin.pcx", NULL, NULL);

    return font;
}



