#include "../structures.h"
#include "../prototypes.h"

void selection_ajout_routes(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau) {
    int clic = 0;
    while (!clic) {
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        reperage_bloc_souris(plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        textprintf_ex(buffer, font, 170, 300, makecol(255, 255, 255), -1, "%d et %d convertit en %d et %d",
                      plateau->lig_mouse, plateau->col_mouse,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b & 1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 &&
            plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0) {
            // On va dans le sous programme pour ajouter une route, avec
            // la position de la souris initial passé en paramètre
            usleep(CLIC);
            //ajout_routes(hud, buffer, joueur, plateau, plateau->lig_mouse, plateau->col_mouse);
            ajout_routes(hud, buffer, joueur, plateau);
            usleep(CLIC);
            clic = 1;
        }
        if (mouse_b & 1 && mouse_x < 100 && mouse_y > 700) {
            clic = 1;
        }

        // On a selectionne un endroit ou mettre notre route
    }
}

int check_route(t_plateau *plateau, int lig, int col) {
    printf("%d\n", plateau->matrice[lig][col].element);
    if (plateau->matrice[lig][col].element != -1 && plateau->matrice[lig][col].element != 0 &&
        plateau->matrice[lig][col].element != 1 && plateau->matrice[lig][col].element != 2) {
        return 0;
    }
    return 1;
}

int ajout_routes(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau) {
    int clic = 0;
    int lig_augmente = 0, col_augmente = 0;
    int lig_diminue = 0, col_diminue = 0;
    int lig_ajout, col_ajout;
    while (!clic) {
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        reperage_bloc_souris(plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        textprintf_ex(buffer, font, 170, 300, makecol(255, 255, 255), -1, "%d et %d convertit en %d et %d",
                      plateau->lig_mouse, plateau->col_mouse,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b & 1 && mouse_x < 100 && mouse_y > 700) {
            clic = 1;
        }

        // On a selectionne un endroit ou mettre notre route
        if (mouse_b & 1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 &&
            plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0) {
            int lig_init = plateau->lig_mouse;
            int col_init = plateau->col_mouse;
            usleep(CLIC);
            while (!clic) {
                affichage_hud_et_clic(hud, buffer, joueur, plateau);
                if (lig_init == plateau->lig_mouse) {
                    lig_augmente = 0;
                    col_augmente = 1;
                    if (plateau->col_mouse > col_init) {
                        for (int i = col_init; i <= plateau->col_mouse; i++) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            } else
                                break;
                        }
                        col_ajout = plateau->col_mouse - col_init;
                    } else if (plateau->col_mouse < col_init) {
                        for (int i = col_init; i >= plateau->col_mouse; i--) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            } else
                                break;
                        }
                        col_ajout = plateau->col_mouse + col_init;
                    } else {
                        reperage_bloc_souris(plateau);
                        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
                    }
                }
                else if (col_init == plateau->col_mouse) {
                    lig_augmente = 1;
                    col_augmente = 0;
                    if (plateau->lig_mouse > lig_init) {
                        for (int i = lig_init; i <= plateau->lig_mouse; i++) {
                            if (check_route(plateau, i, plateau->col_mouse)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            } else
                                break;
                        }
                        lig_ajout = plateau->lig_mouse - lig_init;
                    } else if (plateau->lig_mouse < lig_init) {
                        for (int i = lig_init; i >= plateau->lig_mouse; i--) {
                            if (check_route(plateau, i, plateau->col_mouse)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            } else
                                break;
                        }
                        lig_ajout = plateau->lig_mouse + lig_init;
                    } else {
                        reperage_bloc_souris(plateau);
                        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
                    }
                } else {
                    lig_init = plateau->lig_mouse;
                    col_init = plateau->col_mouse;
                    break;
                }
                masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                if (mouse_b & 1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 &&
                    plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0) {
                    if (plateau->col_mouse > col_init) {
                        for (int i = col_init; i <= plateau->col_mouse; i++) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            }
                            col_ajout = plateau->col_mouse - col_init;
                        }
                    }
                    else if (plateau->col_mouse < col_init) {
                        for (int i = col_init; i >= plateau->col_mouse; i--) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            }
                        }
                        col_ajout = plateau->col_mouse + col_init;
                    }
                    usleep(CLIC);
                    break;
                }
            }
        }
    }
}


/*int ajout_routes(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau, int lig_init,
                           int col_init) {
    int clic = 0;
    int x_augmente;
    int y_augmente;
    int autorisation;
    int compteur = 0;

    if (lig_init <= plateau->lig_mouse)
        x_augmente = 1;
    else
        x_augmente = 0;
    if (col_init <= plateau->col_mouse)
        y_augmente = 1;
    else
        y_augmente = 0;

    int compteur_lig = lig_init;
    int compteur_col = col_init;

    printf("ajout routes lol");
    while (!clic) {
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        /// tant que le x et le y du joueur sont différents de celui de la souris ET seulement si la case est accessible la ou pointe la souris
        printf("avant while");
        //while (compteur_lig != plateau->lig_mouse && compteur_col != plateau->col_mouse) {
            printf("while euss");
            affichage_hud_et_clic(hud, buffer, joueur, plateau);
            reperage_bloc_souris(plateau);
            textprintf_ex(buffer, font, 170, 500, makecol(255, 255, 255), -1, "RGETHYJTUK");
            masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
            // on dessine un bloc puis on augmente de 1 la valeur du x_joueur
            if (x_augmente) {
                for (int i = lig_init; i < plateau->lig_mouse; i++){
                    dessin_bloc_unique(buffer, i, col_init, plateau, 200, 0, 0);
                    compteur_lig = compteur_lig + 1;
                }
            } else if (!x_augmente) {
                for (int i = lig_init; i > plateau->lig_mouse; i--){
                    dessin_bloc_unique(buffer, i, col_init, plateau, 200, 0, 0);
                    compteur_lig = compteur_lig - 1;
                }
            }
            if (y_augmente) {
                for (int i = lig_init; i < plateau->col_mouse; i++){
                    dessin_bloc_unique(buffer, compteur_lig, i, plateau, 200, 0, 0);
                    compteur_col = compteur_col + 1;
                }
            } else if (!y_augmente) {
                for (int i = lig_init; i > plateau->col_mouse; i--){
                    dessin_bloc_unique(buffer, compteur_lig, i, plateau, 200, 0, 0);
                    compteur_col = compteur_col - 1;
                }
            }
            masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        //}
        if (lig_init == plateau->lig_mouse && col_init == plateau->col_mouse && mouse_b & 1) {
            clic = 1;
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}*/
