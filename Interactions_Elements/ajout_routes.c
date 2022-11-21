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
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x, mouse_y, SCREEN_W, SCREEN_H);
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
    //printf("%d\n", plateau->matrice[lig][col].element);
    if (plateau->matrice[lig][col].element != -1 && plateau->matrice[lig][col].element != 0 &&
        plateau->matrice[lig][col].element != 1 && plateau->matrice[lig][col].element != 2 &&
        plateau->matrice[lig][col].element != 13 && plateau->matrice[lig][col].element != 14) {
        return 0;
    }
    return 1;
}

int ajout_routes(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau) {
    int clic = 0;
    reperage_bloc_souris(plateau);
    int lig_init = plateau->lig_mouse;
    int col_init = plateau->col_mouse;

    while (!clic) {
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        reperage_bloc_souris(plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        textprintf_ex(buffer, font, 170, 300, makecol(255, 255, 255), -1, "%d et %d convertit en %d et %d",
                      plateau->lig_mouse, plateau->col_mouse,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc,
                      plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b & 1 && mouse_x < 100 && mouse_y > 700) {
            clic = 1;
        }

        // On a selectionne un endroit ou mettre notre route
        if (mouse_b & 1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 &&
            (plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0 ||
             plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 14)) {
            int lig_init = plateau->lig_mouse;
            int col_init = plateau->col_mouse;
            usleep(CLIC);
            while (!clic) {
                affichage_hud_et_clic(hud, buffer, joueur, plateau);
                if (lig_init == plateau->lig_mouse) {
                    if (plateau->col_mouse > col_init) {
                        for (int i = col_init; i <= plateau->col_mouse; i++) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            } else
                                break;
                        }
                    } else if (plateau->col_mouse < col_init) {
                        for (int i = col_init; i >= plateau->col_mouse; i--) {
                            if (check_route(plateau, plateau->lig_mouse, i)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            } else
                                break;
                        }
                    } else {
                        reperage_bloc_souris(plateau);
                        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
                    }
                } else if (col_init == plateau->col_mouse) {
                    if (plateau->lig_mouse > lig_init) {
                        for (int i = lig_init; i <= plateau->lig_mouse; i++) {
                            if (check_route(plateau, i, plateau->col_mouse)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            } else
                                break;
                        }
                    } else if (plateau->lig_mouse < lig_init) {
                        for (int i = lig_init; i >= plateau->lig_mouse; i--) {
                            if (check_route(plateau, i, plateau->col_mouse)) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            } else
                                break;
                        }
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
                    (plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0 ||
                     plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 14)) {
                    reperage_bloc_souris(plateau);
                    usleep(CLIC);
                    if (lig_init == plateau->lig_mouse) {
                        if (col_init > plateau->col_mouse) {
                            for (int i = col_init; i >= plateau->col_mouse; i--) {
                                plateau->matrice_map[lig_init][i] = 13;
                                plateau->matrice[lig_init][i].element = 13;
                                for (int k = 1; k <= 3; k++) {
                                    if (plateau->matrice[lig_init + k][i].element == 0)
                                        plateau->matrice[lig_init + k][i].element = 14;
                                    if (plateau->matrice[lig_init - k][i].element == 0)
                                        plateau->matrice[lig_init - k][i].element = 14;
                                }
                                plateau->matrice[lig_init][i].b_element = plateau->routes[1];
                            }
                        } else {
                            for (int i = col_init; i < plateau->col_mouse + 1; i++) {
                                plateau->matrice[lig_init][i].element = 13;
                                plateau->matrice_map[lig_init][i] = 13;
                                for (int k = 1; k <= 3; k++) {
                                    if (plateau->matrice[lig_init + k][i].element == 0)
                                        plateau->matrice[lig_init + k][i].element = 14;
                                    if (plateau->matrice[lig_init - k][i].element == 0)
                                        plateau->matrice[lig_init - k][i].element = 14;
                                }
                                plateau->matrice[lig_init][i].b_element = plateau->routes[1];
                            }
                        }
                    } else {
                        if (lig_init > plateau->lig_mouse) {
                            for (int i = lig_init; i >= plateau->lig_mouse; i--) {
                                plateau->matrice[i][col_init].element = 13;
                                plateau->matrice_map[i][col_init] = 13;
                                for (int k = 1; k <= 3; k++) {
                                    if (plateau->matrice[i][col_init + k].element == 0)
                                        plateau->matrice[i][col_init + k].element = 14;
                                    if (plateau->matrice[i][col_init - k].element == 0)
                                        plateau->matrice[i][col_init - k].element = 14;
                                }
                                plateau->matrice[i][col_init].b_element = plateau->routes[0];
                            }
                        } else {
                            for (int i = lig_init; i < plateau->lig_mouse + 1; i++) {
                                plateau->matrice[i][col_init].element = 13;
                                plateau->matrice_map[i][col_init] = 13;
                                for (int k = 1; k <= 3; k++) {
                                    if (plateau->matrice[i][col_init + k].element == 0)
                                        plateau->matrice[i][col_init + k].element = 14;
                                    if (plateau->matrice[i][col_init - k].element == 0)
                                        plateau->matrice[i][col_init - k].element = 14;
                                }
                                plateau->matrice[i][col_init].b_element = plateau->routes[0];
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}
