#include "../structures.h"
#include "../prototypes.h"

void affichage_eau(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    usleep(CLIC);
    usleep(CLIC);
    int annuler = 0;
    set_trans_blender(100, 100, 100, 100);
    bfs_eau(buffer, plateau, CHATEAU_EAU);
    while(!annuler)
    {
        clear_bitmap(buffer);
        affichage_elements(hud, buffer, joueur, plateau, plateau->terrain_noir[plateau->etape]);

        /// affichages huds  et general
        //habitants
        draw_trans_sprite(buffer, hud->habitants,100,16);
        textprintf_ex(buffer,font,170,16+24,makecol(255,255,255),-1,"%d", joueur->habitants);
        printf("ecrito1\n");
        //constructions
        draw_trans_sprite(buffer, hud->bg,10,701);
        draw_trans_sprite(buffer, hud->construct,10,700);
        // Argent
        draw_trans_sprite(buffer, hud->argent,300,16);
        textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);
        printf("ecrito3\n");

        t_maillon *temp;
        for(int i = 0; i <plateau->indice_tab_habitations; i++){
            if(plateau->habitations[i]->derniere_case_chemin != NULL){
                temp = plateau->habitations[i]->derniere_case_chemin;
                while(temp != NULL){
                    draw_trans_sprite(buffer, hud->case_eau,plateau->matrice[temp->ligne][temp->colonne].x_bloc-17 -plateau->screenx,plateau->matrice[temp->ligne][temp->colonne].y_bloc-17 - plateau->screeny);
                    temp = temp->predecesseur;
                }
            }
        }
        printf("fin For\n");

        // eau
        masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
        if (bouton(hud->eau, 500, 20)){
            masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                annuler = 1;
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
                annuler = 1;
                affichage_elec(hud, buffer, joueur, plateau);
                break;
            }
        }
        /// curseur
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);

        masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }
}

void affichage_elec(t_affichage * hud, BITMAP * buffer, t_joueur* joueur, t_plateau * plateau)
{
    usleep(CLIC);
    usleep(CLIC);
    int annuler = 0;
    set_trans_blender(100, 100, 100, 100);
    bfs_eau(buffer, plateau, CENTRALE);
    while(!annuler)
    {
        clear_bitmap(buffer);
        affichage_elements(hud, buffer, joueur, plateau, plateau->terrain_noir[plateau->etape]);

        /// affichages huds  et general
        //habitants
        draw_trans_sprite(buffer, hud->habitants,100,16);
        textprintf_ex(buffer,font,170,16+24,makecol(255,255,255),-1,"%d", joueur->habitants);
        printf("ecrito1\n");
        //constructions
        draw_trans_sprite(buffer, hud->bg,10,701);
        draw_trans_sprite(buffer, hud->construct,10,700);
        // Argent
        draw_trans_sprite(buffer, hud->argent,300,16);
        textprintf_ex(buffer,font,300+75,16 + 26,makecol(255,255,255),-1,"%d", joueur->argent);
        printf("ecrito3\n");

        t_maillon *temp;
        for(int i = 0; i <plateau->indice_tab_habitations; i++){
            if(plateau->habitations[i]->derniere_case_centrale != NULL){
                temp = plateau->habitations[i]->derniere_case_centrale;
                while(temp != NULL){
                    printf("aficahg\n");
                    draw_trans_sprite(buffer, hud->case_elec,plateau->matrice[temp->ligne][temp->colonne].x_bloc-17 -plateau->screenx,plateau->matrice[temp->ligne][temp->colonne].y_bloc-17 - plateau->screeny);
                    temp = temp->predecesseur;
                }
            }
        }
        printf("fin For\n");

        // eau
        masked_blit(hud->bg, buffer, 0, 0, 500, 21, SCREEN_W, SCREEN_H);
        if (bouton(hud->elec, 500, 20)){
            masked_blit(hud->eau_outline, buffer, 0, 0, 500, 20, SCREEN_W, SCREEN_H);
            if (mouse_b&1){
                annuler = 1;
                affichage_eau(hud, buffer, joueur, plateau);
                break;
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
                annuler = 1;
            }
        }
        /// curseur
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 7, SCREEN_W, SCREEN_H);

        masked_blit(hud->elec, buffer, 0, 0, 700, 20, SCREEN_W, SCREEN_H);
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
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