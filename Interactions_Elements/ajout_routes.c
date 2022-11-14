#include "../structures.h"
#include "../prototypes.h"

void selection_ajout_routes(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau){
    int clic = 0;
    while(!clic){
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        reperage_bloc_souris(plateau);
        dessin_bloc_unique(buffer, plateau->lig_mouse, plateau->col_mouse, 200, 0, 0);
        textprintf_ex(buffer,font,170,300,makecol(255,255,255),-1,"%d et %d convertit en %d et %d", plateau->lig_mouse, plateau->col_mouse, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b&1 && plateau->lig_mouse > -1 && plateau->col_mouse > -1 &&
            plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0) {
            // On va dans le sous programme pour ajouter une route, avec
            // la position de la souris initial passé en paramètre

            if(affichage_ajout_routes(hud, buffer, joueur, plateau, plateau->lig_mouse, plateau->col_mouse)){
                clic = 1;
            }
            textprintf_ex(buffer,font,170,300,makecol(255,255,255),-1,"ZETHRYJTUDKYFIL", plateau->lig_mouse, plateau->col_mouse, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);
            masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        if (mouse_b&1 && mouse_x < 100 && mouse_y > 700){
            clic = 1;
        }

        // On a selectionne un endroit ou mettre notre route
    }
}


int affichage_ajout_routes(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int lig_init, int col_init){
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

    printf("ajout routes\n");
/// tant que le x et le y du joueur sont différents de celui de la souris ET seulement si la case est accessible la ou pointe la souris
    while((lig_init != plateau->lig_mouse || col_init != plateau->col_mouse))
    {
        textprintf_ex(buffer,font,170,300,makecol(255,0,255),-1,"%d et %d convertit en %d et %d", plateau->lig_mouse, plateau->col_mouse, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc);

        while (lig_init != plateau->lig_mouse) // le x du joueur différent de la souris, alors
        {
            // on dessine un bloc puis on augmente de 1 la valeur du x_joueur
            if (x_augmente)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, lig_init + 1, plateau->col_mouse, plateau, 200, 0, 0);
                lig_init = lig_init + 1;
            }
            else if (!x_augmente)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, lig_init - 1, plateau->col_mouse, plateau, 200, 0, 0);
                lig_init = lig_init - 1;
            }
            masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        while (col_init != plateau->col_mouse)
        {
            if (y_augmente)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, lig_init, col_init + 1, plateau, 200, 0, 0);
                col_init = col_init + 1;
            }
            else if (!y_augmente)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, lig_init, col_init - 1, plateau, 200, 0, 0);
                col_init = col_init - 1;
            }
            masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        if (compteur == 3)
        {
            break;
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    return autorisation;
}
