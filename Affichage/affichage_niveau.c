#include "../structures.h"
#include "../prototypes.h"

void affichage_eau(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    int annuler = 0;
    while(!annuler)
    {
        clear_bitmap(buffer);
        affichage_elements(hud, buffer, joueur, plateau, plateau->terrain_noir[plateau->etape]);

        /// affichages huds  et general
        //habitants
        masked_blit(hud->habitants, buffer, 0, 0, 100, 16, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer,font,170,16+24,makecol(255,255,255),-1,"%d", joueur->habitants);
        //constructions
        masked_blit(hud->bg, buffer, 0, 0, 10, 701, SCREEN_W, SCREEN_H);
        masked_blit(hud->construct, buffer, 0, 0, 10, 700, SCREEN_W, SCREEN_H);
        /// eau
        masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
        masked_blit(hud->eau, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
        // elec
        masked_blit(hud->bg, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
        masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
        // Argent
        masked_blit(hud->argent, buffer, 0, 0, 300, 16, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);
        /// curseur
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);

        affichage_niveaux(hud, buffer, joueur, plateau, 1);

        // eau
        masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
        if (bouton(hud->eau, 500, 20)){
            masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                usleep(CLIC);
                annuler = 1;
            }
        }
        else {
            masked_blit(hud->eau, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
        }
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);

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

        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }
}

void affichage_elec(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    int annuler = 0;
    while(annuler != 1)
    {
        clear_bitmap(buffer);
        blit(plateau->terrain_noir[plateau->etape], buffer, plateau->screenx, plateau->screeny,0,0,SCREEN_W,SCREEN_H);
        affichage_niveaux(hud, buffer, joueur, plateau, 2);
        masked_blit(hud->bg, buffer, plateau->screenx, plateau->screeny, 800, 650, SCREEN_W, SCREEN_H);
        if (bouton(hud->bg, 830, 650)){
            masked_blit(hud->bg_on, buffer, plateau->screenx, plateau->screeny, 800, 650, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                annuler = 1;
            }
        }
        textprintf_ex(buffer, font, 860, 669, makecol(255,255,255), -1, "ANNULER");
        masked_blit(hud->cursor, buffer, plateau->screenx, plateau->screeny, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);

        blit(buffer, screen, plateau->screenx, plateau->screeny,0,0,SCREEN_W, SCREEN_H);
    }
}

void affichage_niveaux(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau, int niveau)
{
    set_trans_blender(100, 100, 100, 100);
    if (niveau == 1) // eau
    {
        for (int i = 0; i<35; i++)
        {
            for (int j = 0; j<45; j++)
            {
                if(plateau->matrice[i][j].element == 13)
                {
                    draw_trans_sprite(buffer, hud->case_eau,plateau->matrice[i][j].x_bloc-17 -plateau->screenx,plateau->matrice[i][j].y_bloc-17 - plateau->screeny);
                }
            }
        }
    }
    if (niveau == 2) // elec
    {
        for (int i = 0; i<35; i++)
        {
            for (int j = 0; j<45; j++)
            {
                if(plateau->matrice[i][j].element == 13)
                {
                    draw_trans_sprite(buffer, hud->case_elec,plateau->matrice[i][j].x_bloc-17 - plateau->screenx, plateau->matrice[i][j].y_bloc-17 - plateau->screeny);
                }
            }
        }
    }
}