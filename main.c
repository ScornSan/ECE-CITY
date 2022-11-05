#include "structures.h"
#include "prototypes.h"

void quadrillage_test(BITMAP * buffer)
{
    for( int i = 0; i<36; i++){
        line(buffer, 26 +i*11, 478 +i*7, 612 +i*11, 118+i*7, makecol(255,0,0)); //horizontale
    }
    for ( int i = 0; i < 46; i++){
        line(buffer, 26 +i*13, 478 -i*8, 410 +i*13, 723 -i*8, makecol(255,0,0)); // verticale
    }
}


int main(int argc, char *argv[])
{
    int fin;

    allegro_init();

    // pour disposer de la souris
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1024,768 ,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    // dessiner une zone EXIT en haut à gauche de l'écran
    rectfill(buffer,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(buffer,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");

    // init. variable de sortie boucle interactive
    fin=0;
    int clic = 0;

    t_affichage* hud = init_affichage();
    t_plateau * plateau = init_plateau();
    t_joueur* joueur = init_joueur();
    // Boucle interactive
    while (!fin)
    {
        clear_bitmap(buffer);
        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
        textprintf_ex(buffer,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

        // les clics
        if (mouse_b & 1) // gauche : dessiner en rouge
            rectfill(buffer, mouse_x, mouse_y, mouse_x+20, mouse_y+20, makecol(255,0,0));

        if (mouse_b & 2) // droit : dessiner en bleu
            rectfill(buffer, mouse_x, mouse_y, mouse_x+20, mouse_y+20, makecol(0,0,255));

        if (mouse_b & 4) // mileu : fin du programme
            fin=1;
        affichage_hud(hud, buffer, joueur, plateau);
        quadrillage_test(buffer);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // prise en compte effective de la zone cliquable EXIT :
        // clic gauche en haut à gauche de l'écran -> fin du programme
        if ( mouse_b&1 && mouse_x<=40 && mouse_y<=20)
            fin=1;

    }
    return 0;
}
END_OF_MAIN();
