#include "../structures.h"
#include "../prototypes.h"

void affichage_hud(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
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
        if (mouse_b&1){
            usleep(CLIC);
            affichage_boutons(hud, buffer, joueur, plateau, CONSTRUCT);
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

    masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);
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
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b&1){
            clic = 1;
            printf("sortie");
        }
    }
}

void affichage_liste_constru(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    affichage_elements(hud, buffer, joueur, plateau);

    masked_blit(hud->bg_on, buffer, 0, 0, 10, 701, SCREEN_W, SCREEN_H);
    masked_blit(hud->construct, buffer, 0, 0, 10, 700, SCREEN_W, SCREEN_H);

    if(mouse_b&1 && mouse_x > 800 && mouse_y < 100){
       //dijkstra(buffer, plateau);
    }

    // Affichage des boutons "chateau, centrale, caserne"
    if (joueur->argent > 100000){
        masked_blit(hud->chateau, buffer, 0, 0, 20, 300, SCREEN_W, SCREEN_H);
        // Souris sur bouton chateau
        if (mouse_x > 20 && mouse_x < 20 + hud->chateau->w && mouse_y > 300 && mouse_y < 300 + hud->chateau->h){
            masked_blit(hud->Schateau, buffer, 0, 0, 20, 300, SCREEN_W, SCREEN_H);
            reperage_bloc_souris(plateau);
            affichage_zone_constru_terrain(buffer,plateau,3);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(hud, buffer, joueur, plateau, CHATEAU_EAU - 1);
                usleep(CLIC);
            }
        }
        masked_blit(hud->centrale, buffer, 0, 0, 25, 400, SCREEN_W, SCREEN_H);
        // Souris sur bouton centrale
        if (mouse_x > 25 && mouse_x < 25 + hud->centrale->w && mouse_y > 400 && mouse_y < 400 + hud->centrale->h){
            masked_blit(hud->Scentrale, buffer, 0, 0, 25, 400, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(hud, buffer, joueur, plateau, CENTRALE - 1);
                usleep(CLIC);
            }
        }
        masked_blit(hud->caserne, buffer, 0, 0, 10, 500, SCREEN_W, SCREEN_H);
        // Souris sur bouton caserne
        if (mouse_x > 10 && mouse_x < 10 + hud->caserne->w && mouse_y > 500 && mouse_y < 500 + hud->caserne->h){
            masked_blit(hud->Scaserne, buffer, 0, 0, 10, 500, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(hud, buffer, joueur, plateau, CASERNE - 1);
                usleep(CLIC);
            }
        }
    }
    else{
        masked_blit(hud->Nonchateau, buffer, 0, 0, 5, 300, SCREEN_W, SCREEN_H);
        masked_blit(hud->Noncentrale, buffer, 0, 0, 35, 400, SCREEN_W, SCREEN_H);
        masked_blit(hud->Noncaserne, buffer, 0, 0, 10, 500, SCREEN_W, SCREEN_H);
    }

    // Affichage bouton Ecole
    if (joueur->argent > 50000){
        masked_blit(hud->ecole, buffer, 0, 0, 5, 200, SCREEN_W, SCREEN_H);
        // Souris sur bouton ecole
        if (mouse_x > 5 && mouse_x < 5 + hud->ecole->w && mouse_y > 200 && mouse_y < 200 + hud->ecole->h){
            masked_blit(hud->Secole, buffer, 0, 0, 5, 200, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(hud, buffer, joueur, plateau, ECOLE - 1);
                usleep(CLIC);
            }
        }
    }
    else{
        masked_blit(hud->Nonecole, buffer, 0, 0, 10, 200, SCREEN_W, SCREEN_H);
    }

    // Affichage bouton terrains
    if (joueur->argent > 1000){
        masked_blit(hud->chantier, buffer, 0, 0, 20, 600, SCREEN_W, SCREEN_H);
        if (mouse_x > 10 && mouse_x < 20 + hud->chantier->w && mouse_y > 600 && mouse_y < 600 + hud->chantier->h){
            masked_blit(hud->Schantier, buffer, 0, 0, 20, 600, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                placement_construction(hud, buffer, joueur, plateau, CONSTRUCT +3);
                usleep(CLIC);
            }
        }
    }
    else{
        masked_blit(hud->Nonchantier, buffer, 0, 0, 10, 600, SCREEN_W, SCREEN_H);
    }

    // Affichage bouton routes
    if (joueur->argent > 10){
        masked_blit(hud->route, buffer, 0, 0, 7, 625, SCREEN_W, SCREEN_H);
        if (mouse_x > 7 && mouse_x < 7 + hud->route->w && mouse_y > 625 && mouse_y < 625 + hud->route->h){
            masked_blit(hud->Sroute, buffer, 0, 0, 7, 625, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                selection_ajout_routes(hud, buffer, joueur, plateau);
                usleep(CLIC);
            }
        }
    }
    else{
        masked_blit(hud->Nonroute, buffer, 0, 0, 7, 625, SCREEN_W, SCREEN_H);
    }
}
