#include "../structures.h"
#include "../prototypes.h"

bool bouton(BITMAP* bitmap, int x, int y) {
    if (mouse_x > x && mouse_x < x + bitmap->w && mouse_y > y && mouse_y < y + bitmap->h) {
        return true;
    }
    return false;
}

void affichage_hud(t_affichage* hud, BITMAP* buffer, t_joueur* joueur){
    //Habitants
    masked_blit(hud->habitants, buffer, 0, 0, 140, 16, SCREEN_W, SCREEN_H);
    if (bouton(hud->habitants, 140, 16)){
        masked_blit(hud->habitants_outline, buffer, 0, 0, 140, 16, SCREEN_W, SCREEN_H);
    }
    textprintf_ex(buffer,font,140 + 105,16+34,makecol(255,255,255),-1,"%d", joueur->habitants);

    //Constructions
    if (bouton(hud->construct, 10, 650)){
        masked_blit(hud->bg, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);
        masked_blit(hud->construct_outline, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);
    }
    masked_blit(hud->bg, buffer, 0, 0, 21, 653, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);

    //Eau
    if (bouton(hud->eau, 700, 20)){
        masked_blit(hud->eau_outline, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
    }
     else {
         masked_blit(hud->bg, buffer, 0, 0, 711, 23, SCREEN_W, SCREEN_H);
         masked_blit(hud->eau, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
    }

    // Elec
    if (bouton(hud->elec, 1000, 20)){
        masked_blit(hud->bg, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);
        masked_blit(hud->elec_outline, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);
    }
    masked_blit(hud->bg, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);
    masked_blit(hud->elec, buffer, 0, 0, 1000, 20, SCREEN_W, SCREEN_H);

    // Argent
    masked_blit(hud->argent, buffer, 0, 0, 400, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,400+105,16 + 36,makecol(255,255,255),-1,"%d", joueur->argent);

    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
}

void affichage_constructions(t_affichage* construction){

}
