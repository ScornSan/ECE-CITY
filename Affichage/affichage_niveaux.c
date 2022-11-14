#include "../structures.h"
#include "../prototypes.h"

void affichage_eau(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    int annuler = 0;
    int niveau = 1;
    while(annuler != 1)
    {
        clear_bitmap(buffer);
        affichage_niveaux(hud, buffer, joueur, plateau, niveau);
        masked_blit(hud->bg, buffer, 0, 0, 800, 650, SCREEN_W, SCREEN_H);

        if (bouton(hud->bg, 830, 650)){
            masked_blit(hud->bg_on, buffer, 0, 0, 800, 650, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                annuler = 1;
            }
        }
        textprintf_ex(buffer, font, 860, 669, makecol(255,255,255), -1, "ANNULER");
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);

        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }
}

void affichage_elec(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    int annuler = 0;
    int niveau = 2;
    while(annuler != 1)
    {
        clear_bitmap(buffer);
        affichage_niveaux(hud, buffer, joueur, plateau, niveau);
        masked_blit(hud->bg, buffer, 0, 0, 800, 650, SCREEN_W, SCREEN_H);
        if (bouton(hud->bg, 830, 650)){
            masked_blit(hud->bg_on, buffer, 0, 0, 800, 650, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                annuler = 1;
            }
        }
        textprintf_ex(buffer, font, 860, 669, makecol(255,255,255), -1, "ANNULER");
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);

        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }
}

void affichage_niveaux(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau, int niveau)
{
    if (niveau == 1) // eau
    {
        for (int j = 0; j<45; j++)
        {
            for (int i = 0; i<35; i++)
            {
               if(plateau->matrice[i][j].element == 0)
               {
                   masked_blit(hud->case_eau, buffer, 0, 0, plateau->matrice[i][j].x_bloc-15, plateau->matrice[i][j].y_bloc-22, SCREEN_W, SCREEN_H);
               }
            }
        }
    }
    if (niveau == 2) // elec
    {
        for (int j = 0; j<45; j++)
        {
            for (int i = 0; i<35; i++)
            {
                if(plateau->matrice[i][j].element == 0)
                {
                   masked_blit(hud->case_elec, buffer, 0, 0, plateau->matrice[i][j].x_bloc-15, plateau->matrice[i][j].y_bloc-22, SCREEN_W, SCREEN_H);
                }
            }
        }
    }
}