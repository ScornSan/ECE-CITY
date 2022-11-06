#include "../structures.h"
#include "../prototypes.h"

void affichage_hud(t_affichage* hud,t_batiment *batiment, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    clear_bitmap(buffer);
    blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

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
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, batiment, buffer, joueur, plateau, CONSTRUCT);
            usleep(CLIC);
        }
    }
    masked_blit(hud->construct, buffer, 0, 0, 10, 700, SCREEN_W, SCREEN_H);

    //Eau
    masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
    if (bouton(hud->eau, 500, 20)){
        masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, batiment, buffer, joueur, plateau, EAU);
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
            affichage_boutons(hud,batiment, buffer, joueur, plateau, ELEC);
            usleep(CLIC);
        }
    }
    masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);

    // Argent
    masked_blit(hud->argent, buffer, 0, 0, 300, 16, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);

    masked_blit(hud->maison, buffer, 0, 0, 500, 300, SCREEN_W, SCREEN_H);
    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
    affichage_elements(hud,batiment,  buffer, joueur, plateau);
}

void affichage_boutons(t_affichage* hud, t_batiment *batiment, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int bouton){
    int clic = 0;
    while(!clic){
        affichage_hud_et_clic(hud,batiment, buffer, joueur, plateau);
        switch (bouton){
            case 1:
                affichage_liste_constru(hud, batiment, buffer, joueur, plateau);
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

void affichage_liste_constru(t_affichage* hud,t_batiment* batiment, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    //blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    masked_blit(hud->bg_on, buffer, 0, 0, 10, 651, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 650, SCREEN_W, SCREEN_H);
    if (joueur->argent > 100000){
        for(int i = 0; i< 3; i++){
            if(i==1){
                masked_blit(batiment->construction[i][1], buffer, 0, 0, 40, 270 +i*100, SCREEN_W, SCREEN_H);
                if (bouton(batiment->construction[i][1], 40, 270+i*100)){
                    masked_blit(batiment->construction[i][2], buffer, 0, 0, 40, 270 +i*100, SCREEN_W, SCREEN_H);
                    if (mouse_b&1){
                        usleep(CLIC);
                        placement_construction(hud, batiment, buffer, joueur, plateau, i);
                        usleep(CLIC);
                    }
                }
            }
            else{
                masked_blit(batiment->construction[i][1], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
                if (bouton(batiment->construction[i][1], 10, 260+i*100)){
                    masked_blit(batiment->construction[i][2], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
                    if (mouse_b&1){
                        usleep(CLIC);
                        placement_construction(hud, batiment, buffer, joueur, plateau, i);
                        usleep(CLIC);
                    }
                }
            }
        }
    }
    else{
        for(int i = 0; i< 4; i++){
            masked_blit(batiment->construction[i][0], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
        }
    }
    if (joueur->argent > 50000){
        masked_blit(batiment->construction[3][1], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        if (bouton(batiment->construction[3][1], 10, 260+3*100)){
            masked_blit(batiment->construction[3][2], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(batiment, buffer, joueur, plateau, 3);
                usleep(CLIC);
            }
        }
    }
    else{
        masked_blit(batiment->construction[3][0], buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
    }

    // Affichage bouton terrains
    if (joueur->argent > 1000){
        masked_blit(hud->chantier, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->route->w && mouse_y > 550 && mouse_y < 550 + hud->route->h){
            masked_blit(hud->Schantier, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
        }
    }
    else{
        masked_blit(hud->Nonchantier, buffer, 0, 0, 10, 550, SCREEN_W, SCREEN_H);
    }

    // Affichage bouton routes
    if (joueur->argent > 10){
        masked_blit(hud->route, buffer, 0, 0, 10, 625, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 10 + hud->route->w && mouse_y > 625 && mouse_y < 625 + hud->route->h){
            masked_blit(hud->Sroute, buffer, 0, 0, 10, 625, SCREEN_W, SCREEN_H);
        }
    }
    else{
        masked_blit(hud->Nonroute, buffer, 0, 0, 10, 625, SCREEN_W, SCREEN_H);
    }
}
