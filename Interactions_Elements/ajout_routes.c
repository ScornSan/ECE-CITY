#include "../structures.h"
#include "../prototypes.h"

void ajout_routes(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    int clic = 0;
    while(!clic){
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        reperage_bloc_souris(plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        textprintf_ex(buffer,font,170,300,makecol(255,255,255),-1,"%d et %d convertit en %d et %d", plateau->lig_mouse, plateau->col_mouse, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b&1 && mouse_x < 100 && mouse_y > 700){
            clic = 1;
        }

        // On a selectionne un endroit ou mettre notre route
        if (mouse_b&1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 && plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0){
            int lig_init = plateau->lig_mouse;
            int col_init = plateau->col_mouse;
            usleep(CLIC);
            while(!clic) {
                affichage_hud_et_clic(hud, buffer, joueur, plateau);
                if (lig_init == plateau->lig_mouse) {
                        if (plateau->col_mouse > col_init) {
                            for (int i = col_init; i <= plateau->col_mouse; i++) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            }
                        }
                        else if (plateau->col_mouse < col_init){
                            for (int i = col_init; i >= plateau->col_mouse; i--) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, plateau->lig_mouse, i, 200, 0, 0);
                            }
                        }
                        else{
                            reperage_bloc_souris(plateau);
                            dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
                        }
                }
                else if (col_init == plateau->col_mouse){
                        if (plateau->lig_mouse > lig_init) {
                            for (int i = lig_init; i <= plateau->lig_mouse; i++) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            }
                        }
                        else if (plateau->lig_mouse < lig_init) {
                            for (int i = lig_init; i >= plateau->lig_mouse; i--) {
                                reperage_bloc_souris(plateau);
                                dessin_bloc_unique(buffer, i, plateau->col_mouse, 200, 0, 0);
                            }
                        }
                        else {
                            reperage_bloc_souris(plateau);
                            dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
                        }
                }
                else{
                    lig_init = plateau->lig_mouse;
                    col_init = plateau->col_mouse;
                    break;
                }
                masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                if (mouse_b&1){
                    break;
                }
            }
        }
    }
}