#include "../structures.h"
#include "../prototypes.h"


int bouton(BITMAP* bitmap, int x, int y) {
    if (mouse_x > x && mouse_x < x + bitmap->w && mouse_y > y && mouse_y < y + bitmap->h) {
        return 1;
    }
    return 0;
}

void affichage_hud_et_clic(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    int clic = 0;
    clear_bitmap(buffer);
    affichage_elements(hud, buffer, joueur, plateau);

    //Habitants
    masked_blit(hud->habitants, buffer, 0, 0, 100, 16, SCREEN_W, SCREEN_H);
    if (bouton(hud->habitants, 100, 16)){
        masked_blit(hud->habitants_outline, buffer, 0, 0, 100, 16, SCREEN_W, SCREEN_H);
    }
    textprintf_ex(buffer,font,170,16+24,makecol(255,255,255),-1,"%d", joueur->habitants);

    //Constructions
    masked_blit(hud->bg, buffer, 0, 0, 10, 701, SCREEN_W, SCREEN_H);
    if (bouton(hud->construct, 10, 700)){
        masked_blit(hud->construct_outline, buffer, 0, 0, 10, 700, SCREEN_W, SCREEN_H);
    }
    masked_blit(hud->construct, buffer, 0, 0, 10, 700, SCREEN_W, SCREEN_H);

    // Eau
    masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
    if (bouton(hud->eau, 500, 20)){
        masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
    }
    else {
        masked_blit(hud->eau, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
    }

    // Elec
    masked_blit(hud->bg, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
    if (bouton(hud->elec, 700, 20)){
        masked_blit(hud->elec_outline, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
    }
    masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);

    // Argent
    masked_blit(hud->argent, buffer, 0, 0, 300, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);

    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
}



