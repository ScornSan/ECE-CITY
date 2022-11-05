#include "../structures.h"
#include "../prototypes.h"

void affichage_hud(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    clear_bitmap(buffer);
    blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    //Habitants
    masked_blit(hud->habitants, buffer, 0, 0, 100, 16, SCREEN_W, SCREEN_H);
    if (bouton(hud->habitants, 100, 16)){
        masked_blit(hud->habitants_outline, buffer, 0, 0, 100, 16, SCREEN_W, SCREEN_H);
    }
    textprintf_ex(buffer,font,170,16+24,makecol(255,255,255),-1,"%d", joueur->habitants);

    //Constructions
    masked_blit(hud->bg, buffer, 0, 0, 10, 651, SCREEN_W, SCREEN_H);
    if (bouton(hud->construct, 10, 650)){
        masked_blit(hud->construct_outline, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, buffer, joueur, plateau, CONSTRUCT);
            usleep(CLIC);
        }
    }
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);

    //Eau
    masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
    if (bouton(hud->eau, 500, 20)){
        masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, buffer, joueur, plateau, EAU);
            usleep(CLIC);
        }
    }
    else {
        masked_blit(hud->eau, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
    }

    // Elec
    masked_blit(hud->bg, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
    if (bouton(hud->elec, 700, 20)){
        masked_blit(hud->elec_outline, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, buffer, joueur, plateau, ELEC);
            usleep(CLIC);
        }
    }
    masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);

    // Argent
    masked_blit(hud->argent, buffer, 0, 0, 300, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);

    masked_blit(hud->maison, buffer, 0, 0, 500, 300, SCREEN_W, SCREEN_H);
    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
}

void affichage_boutons(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int bouton){
    int clic = 0;
    while(!clic){
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        switch (bouton){
            case 1:
                affichage_liste_constru(hud, buffer, joueur, plateau);
                break;
            case 2:
                // AFFICHAGE DE LA COUCHE EAU (mettre ces trois lignes dans le spgm)
                masked_blit(hud->bg_on, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
                masked_blit(hud->eau, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
                break;
            case 3:
                // AFFICHAGE DE LA COUCHE ELEC (mettre ces trois lignes dans le spgm)
                masked_blit(hud->bg_on, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
                masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
                break;
        }
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b&1){
            clic = 1;
            printf("sortie");
        }
        rest(20);
    }
}
/*
void affichage_liste_constru(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    masked_blit(hud->bg_on, buffer, 0, 0, 10, 651, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);
    if (joueur->argent > 100000){
        for(int i = 0; i< 3; i++){
            masked_blit(hud->construction[i][1], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
            if (bouton(hud->construction[i][1], 10, 250+i*100)){
                masked_blit(hud->construction[i][2], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
                if (mouse_b&1){
                    usleep(CLIC);
                    placement_construction(hud, buffer, joueur, plateau, i);
                    usleep(CLIC);
                }
            }
        }
    }
    else{
        for(int i = 0; i< 4; i++){
            masked_blit(hud->construction[i][0], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
        }
    }
    if (joueur->argent > 50000){
        masked_blit(hud->construction[3][1], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->construction[3][1]->w && mouse_y > 550 && mouse_y < 550 + hud->construction[3][1]->h){
            masked_blit(hud->construction[3][2], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        }
    }
    else{
        masked_blit(hud->construction[3][0], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
    }
}
*/
void affichage_liste_constru(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    masked_blit(hud->bg_on, buffer, 0, 0, 10, 651, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);
    if (joueur->argent > 100000){
        masked_blit(hud->chateau, buffer, 0, 0, 10, 250, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->chateau->w && mouse_y > 250 && mouse_y < 250 + hud->chateau->h){
            masked_blit(hud->Schateau, buffer, 0, 0, 10, 250, SCREEN_W, SCREEN_H);
        }
        masked_blit(hud->centrale, buffer, 0, 0, 10, 350, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->centrale->w && mouse_y > 350 && mouse_y < 350 + hud->centrale->h){
            masked_blit(hud->Scentrale, buffer, 0, 0, 10, 350, SCREEN_W, SCREEN_H);
        }
        masked_blit(hud->caserne, buffer, 0, 0, 10, 450, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->caserne->w && mouse_y > 450 && mouse_y < 450 + hud->caserne->h){
            masked_blit(hud->Scaserne, buffer, 0, 0, 10, 450, SCREEN_W, SCREEN_H);
        }
    }
    else{
        masked_blit(hud->Nonchateau, buffer, 0, 0, 10, 250, SCREEN_W, SCREEN_H);
        masked_blit(hud->Noncentrale, buffer, 0, 0, 10, 350, SCREEN_W, SCREEN_H);
        masked_blit(hud->Noncaserne, buffer, 0, 0, 10, 450, SCREEN_W, SCREEN_H);
    }
    if (joueur->argent > 50000){
        masked_blit(hud->ecole, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->ecole->w && mouse_y > 550 && mouse_y < 550 + hud->ecole->h){
            masked_blit(hud->Secole, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        }
    }
    else{
        masked_blit(hud->Nonecole, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
    }
}