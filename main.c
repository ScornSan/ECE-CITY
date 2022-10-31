#include "structures.h"
#include "prototypes.h"

int main(int argc, char *argv[])
{
    int fin;

    allegro_init();

    // pour disposer de la souris
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720 ,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    // pour voir le pointeur de la souris
    show_mouse(buffer);

    // dessiner une zone EXIT en haut à gauche de l'écran
    rectfill(buffer,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(buffer,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");

    // init. variable de sortie boucle interactive
    fin=0;

    t_affichage *bitmaps = init_affichage();
    // Boucle interactive
    while (!fin)
    {
        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
        textprintf_ex(buffer,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

        // les clics
        if (mouse_b & 1) // gauche : dessiner en rouge
            rectfill(buffer, mouse_x, mouse_y, mouse_x+20, mouse_y+20, makecol(255,0,0));

        if (mouse_b & 2) // droit : dessiner en bleu
            rectfill(buffer, mouse_x, mouse_y, mouse_x+20, mouse_y+20, makecol(0,0,255));

        if (mouse_b & 4) // mileu : fin du programme
            fin=1;


        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // prise en compte effective de la zone cliquable EXIT :
        // clic gauche en haut à gauche de l'écran -> fin du programme
        if ( mouse_b&1 && mouse_x<=40 && mouse_y<=20)
            fin=1;

    }

    return 0;
}
END_OF_MAIN();
