#include "../structures.h"
#include "../prototypes.h"
#include <time.h>

void boucle_affichage(int i, int j, int hauteur, int longueur,t_plateau * plateau, BITMAP * buffer, int position_x, int position_y, int deplacement, int type, int indice){
    for(int k = i; k< i+hauteur; k++){
        for(int l = j; l< j+longueur; l++){
            plateau->matrice[k][l].affiche = 1;
        }
    }
    switch(type){
        case 2 :   /// habitations 3x3 (Cabane maison chantier ruine)
            if (plateau->habitations[indice]->niveau <= 3){
                masked_blit(plateau->habitations[indice]->style[plateau->habitations[indice]->niveau], buffer, 0, 0, plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2 - 10 - plateau->screenx, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2 - 15 - plateau->screeny, SCREEN_W, SCREEN_H);
                break;
            }
            else if (plateau->habitations[indice]->niveau == 4){ // BUILDING
                masked_blit(plateau->habitations[indice]->style[plateau->habitations[indice]->niveau], buffer, 0, 0, plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2 - plateau->screenx - 15, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2 - plateau->screeny - 53, SCREEN_W, SCREEN_H);
                break;
            }
            else if (plateau->habitations[indice]->niveau == 5){ // GRATTE CIEL
                masked_blit(plateau->habitations[indice]->style[plateau->habitations[indice]->niveau], buffer, 0, 0, plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2 - plateau->screenx - 13, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2 - plateau->screeny - 86, SCREEN_W, SCREEN_H);
                break;
            }

        case 3:   /// batiments 4x6
            masked_blit(plateau->matrice[i][j].b_element, buffer, 0, 0 , plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2 - plateau->screenx, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2 - plateau->screeny, SCREEN_W, SCREEN_H);
            break;
    }
}

void affichage_elements(t_affichage * hud, BITMAP *buffer, t_joueur* joueur, t_plateau * plateau){

    // Position de l'écran réel dans le repère du décor...
    if (key[KEY_RIGHT]){
        plateau->screenx+=2;
        plateau->compteur_x+=2;
    }
    if (key[KEY_LEFT]){
        plateau->screenx-=2;
        plateau->compteur_x-=2;
    }
    if (key[KEY_DOWN]){
        plateau->screeny+=2;
        plateau->compteur_y+=2;
    }
    if (key[KEY_UP]){
        plateau->screeny-=2;
        plateau->compteur_y-=2;
    }

    // Bloquer le scrolling si il est ammené trop loin !
    if (plateau->screenx < 0 ) plateau->screenx=0;
    if (plateau->screenx > plateau->terrain->w - SCREEN_W )
        plateau->screenx = plateau->terrain->w - SCREEN_W;
    if (plateau->screeny < 0 ) plateau->screeny=0;
    if (plateau->screeny > plateau->terrain->h - SCREEN_H )
        plateau->screeny = plateau->terrain->h - SCREEN_H;

    if (plateau->compteur_x < 0 ) plateau->compteur_x=0;
    if (plateau->compteur_x > plateau->terrain->w - SCREEN_W )
        plateau->compteur_x = plateau->terrain->w - SCREEN_W;
    if (plateau->compteur_y < 0 ) plateau->compteur_y=0;
    if (plateau->compteur_y > plateau->terrain->h - SCREEN_H )
        plateau->compteur_y = plateau->terrain->h - SCREEN_H;

    // EFFACER BUFFER EN APPLIQUANT UNE PARTIE DU DECOR (TAILLE DE L'ECRAN)
    blit(plateau->calque_pixels, plateau->buffer_pixels, plateau->screenx, plateau->screeny, 0, 0, SCREEN_W, SCREEN_H);
    blit(plateau->terrain, buffer, plateau->screenx, plateau->screeny, 0, 0, SCREEN_W, SCREEN_H);


    /// affichage éléments sur le terrain
    for(int i = 0; i< 35; i++){
        for (int j = 0;j <45;j++){
            maj_routes(hud, buffer, joueur, plateau, i, j);
            maj_trottoirs(hud, buffer, joueur, plateau, i, j);
            if(plateau->matrice[i][j].affiche != 1){ ///pour voir si on affiche pas deux fois la meme maison en allant sur le bloc suivant
                switch(plateau->matrice[i][j].element){
                    case 0 :break;

                    case CHATEAU_EAU:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case CENTRALE:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case CASERNE:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case ECOLE:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case CHANTIER:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case CABANE:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case MAISON:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case BUILDING:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case GRATTECIEL:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case RUINE:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case TVAGUE_CP:
                        plateau->matrice[i][j].affiche = 1;
                        dessin_bloc_unique(buffer, i, j, plateau, 0, 255, 0);
                        break;
                    case ROUTES:
                        plateau->matrice[i][j].affiche = 1;
                        masked_blit(plateau->matrice[i][j].b_element, buffer, 0, 0, plateau->matrice[i][j].x_bloc - plateau->matrice[i][j].b_element->w/2 - plateau->screenx, plateau->matrice[i][j].y_bloc -plateau->matrice[i][j].b_element->h/2 - plateau->screeny, SCREEN_W, SCREEN_H);
                        break;
                    case TVAGUE:
                        plateau->matrice[i][j].affiche = 1;
                        dessin_bloc_unique(buffer, i, j, plateau, 119, 136, 153);
                        break;
                    case TVAGUE_CP_BP:
                        plateau->matrice[i][j].affiche = 1;
                        dessin_bloc_unique(buffer, i, j, plateau, 0, 0, 255);
                        break;
                }
            }
            plateau->matrice[i][j].affiche = 0;
        }
    }


    /// maj evolution des habitations
    for(int x = 0; x < plateau->indice_tab_habitations; x++) // on parcours notre tableau d'habitation
    {
        if( (int)time(NULL) - plateau->habitations[x]->timer >= TIME_CYCLE && plateau->indice_tab_habitations != 0) // on verifie si le cycle de 15 secondes d'une des habitations est fini
        {
            plateau->habitations[x]->timer = time(NULL);
            maj_habitation(x, plateau, joueur, buffer, hud);
        }
        else
        {
            rectfill(buffer, 993, 723, 993 - (int)((time(NULL)) - plateau->habitations[x]->timer) * 11, 746, makecol(255, 0, 0)); // barre de temps
        }
    }
}


