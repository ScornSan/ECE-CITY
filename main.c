#include "structures.h"
#include "prototypes.h"

void affichage_hud(t_affichage* hud, BITMAP* buffer){
    int money = 500000;
    int habitants = 191;
    //Habitants
    masked_blit(hud->habitants, buffer, 0, 0, 140, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,140 + 105,16+34,makecol(255,255,255),-1,"%d", habitants);
    //Constructions
    masked_blit(hud->bg, buffer, 0, 0, 21, 653, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);

    //Eau
    masked_blit(hud->bg, buffer, 0, 0, 711, 23, SCREEN_W, SCREEN_H);
    masked_blit(hud->eau, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);

    // Elec
    masked_blit(hud->bg, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);
    masked_blit(hud->elec, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);

    // Argent
    masked_blit(hud->argent, buffer, 0, 0, 400, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,400+105,16 + 36,makecol(255,255,255),-1,"%d", money);

    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
}

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

    // dessiner une zone EXIT en haut à gauche de l'écran
    rectfill(buffer,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(buffer,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");

    // init. variable de sortie boucle interactive
    fin=0;

    t_affichage* hud = init_affichage();
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

        affichage_hud(hud, buffer);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // prise en compte effective de la zone cliquable EXIT :
        // clic gauche en haut à gauche de l'écran -> fin du programme
        if ( mouse_b&1 && mouse_x<=40 && mouse_y<=20)
            fin=1;

    }

    return 0;
}
END_OF_MAIN();
