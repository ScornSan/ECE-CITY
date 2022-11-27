#include "../structures.h"
#include "../prototypes.h"


void affichage_son(BITMAP *buffer, SAMPLE* s, int* clic )
{
    if(mouse_b&1 && mouse_x>= 960 && mouse_x <= 1024 && mouse_y >= 0&& mouse_y <= 50 && !*clic)
    {
        rest(100);
        *clic = 1;
        adjust_sample(s, 0, 0, 1000, 1);
    }
    if (mouse_b&1 && mouse_x>= 960 && mouse_x <= 1024 && mouse_y >= 0&& mouse_y <= 50 && *clic)
    {
        rest(100);
        *clic = 0;
        adjust_sample(s, 255, 128, 1000, 1);
    }
}


void affichage_menu(t_affichage* hud, BITMAP* buffer, int* clic, FONT* myfont, SAMPLE* s)
{
    clear_bitmap(buffer);
    blit(hud->accueil,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    //textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);
    affichage_son(buffer, s, &(*clic));

    if (*clic)
    {
        draw_sprite(buffer, hud->son_off, 960, 0);
    }
    else
    {
        draw_sprite(buffer, hud->son_on, 960, 0);
    }


    textprintf_ex(buffer,myfont,475,328, makecol(0,0,0),-1,"JOUER");
    textprintf_ex(buffer,myfont, 438, 434, makecol(0,0,0),-1,"CONTINUER");
    textprintf_ex(buffer,myfont,460, 542, makecol(0,0,0),-1,"CREDITS");
    textprintf_ex(buffer,myfont, 460, 650, makecol(0,0,0),-1,"QUITTER");

    if ( mouse_x>= 400 && mouse_x <= 631 && mouse_y >= 322 && mouse_y <=377)
    {
        masked_blit(hud->bouton_menu, buffer, 0, 0, 357, 245, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer,myfont,475,328, makecol(0,0,0),-1,"JOUER");
    }

    if(  mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 428 && mouse_y <= 482)
    {
        draw_sprite(buffer, hud->bouton_menu, 357, 351);
        textprintf_ex(buffer,myfont, 438, 434, makecol(0,0,0),-1,"CONTINUER");
    }

    if(   mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 538 && mouse_y <= 590 )
    {
        draw_sprite(buffer, hud->bouton_menu, 357, 459);
        textprintf_ex(buffer,myfont,460, 542, makecol(0,0,0),-1,"CREDITS");
    }
    if(   mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 638 && mouse_y <= 700 ) {
        draw_sprite(buffer, hud->bouton_menu, 357, 567);
        textprintf_ex(buffer,myfont, 460, 650, makecol(0,0,0),-1,"QUITTER");
    }
}

void prenom( BITMAP* buffer, t_joueur* joueur, t_affichage* hud)
{
    int x = 415;
    int touche;
    char carac;
    int y = 265;
    int stop = 0;
    int  poscarac= 0;
    int place= 0;
    int nb = 0;
    int compteur = 0;
    fflush(stdin);
    poscarac = 0;
    //textprintf_ex(buffer,font,365,100, makecol(0,255,0),-1, "BIENVENUE DANS UNE NOUVELLE PARTIE !");
    //textprintf_ex(buffer,font,365,135, makecol(0,255,0),-1, "CHER JOUEUR, ENTREZ VOTRE PSEUDO:");
    rectfill(buffer,386,245,638,286,makecol(0,0,0 ));


    /// AFFICHAGE DES LETTRES QUE L'ON TAPE AU CLAVIER
    while (stop != 1)
    {
        if (keypressed())
        {
            touche=readkey();
            carac = (char)touche;

            // afficher le caractère à une position x croissante
            if( carac != '\r' && !key[KEY_BACKSPACE] && compteur != 19)
            {
                textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0), "%c",carac);
                joueur->pseudo[place] = carac;
                poscarac = poscarac+8;
                compteur = compteur +1;
            }

            if (key[KEY_BACKSPACE] && x+poscarac >= 415)
            {
                if(x+poscarac == 373)
                {
                    poscarac=poscarac-8;
                    joueur->pseudo[place] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                    compteur = compteur -1;
                }
                else
                {
                    nb = nb +1;
                    poscarac=poscarac-8;
                    joueur->pseudo[place-1] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                    compteur = compteur -1;
                }
            }

            /// RETOUR CHARIOT : ON VA A LA LIGNE
            if (carac== '\r')
            {
                clear_bitmap(buffer);
                stop=1;

            }
            place = place+1;
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    clear_bitmap(buffer);
}

int menu(t_affichage* hud, t_joueur* joueur, BITMAP* buffer, t_plateau *plateau) {
    int fin = 0;
    int ok = 0;
    int sortir = 0;
    int clic = 0;
    FONT* myfont;
    myfont = load_font("../FONT/tempus.pcx", NULL, NULL);

    clear_bitmap(buffer);
    // Boucle interactive
    int fait1 = 0;
    while (!fin) {
        if(!fait1){
            play_sample(hud->son_menu, 255, 128, 1000, 1);
            fait1 = 1;
        }
        affichage_son(buffer, hud->son_menu, &clic);

        textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);

        affichage_menu(hud, buffer, &clic, myfont, hud->son_menu);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)

        // si on appui sur jouer
        if (mouse_b & 1 && mouse_x>= 400 && mouse_x <= 631 && mouse_y >= 322 && mouse_y <=377) {
            ok = 0;
            sortir = 0;
            install_keyboard();
            fait1 = 0;
            while(ok!=1 && sortir!=1) {

                if (sortir != 1) {
                    install_keyboard();
                    clear_bitmap(buffer);
                    blit(hud->nom,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    prenom(buffer, joueur, hud);

                    while(!(mouse_b&2))
                    {
                        clear_bitmap(buffer);
                        blit(hud->mode,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        textprintf_ex(buffer,myfont,425, 289, makecol(0,0,0),-1,"CAPITALISTE");
                        textprintf_ex(buffer,myfont,430, 455, makecol(0,0,0),-1,"COMMUNISTE");
                        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                        textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);
                        if( mouse_x>= 294 && mouse_x <= 636 && mouse_y >= 281 && mouse_y <= 334) // communiste
                        {
                            draw_sprite(buffer, hud->bouton_menu2, 358, 211);
                            textprintf_ex(buffer,myfont,425, 289, makecol(255,255,255),-1,"CAPITALISTE");
                            masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                        }
                        if(mouse_x>= 389 && mouse_x <= 642 && mouse_y >= 442 && mouse_y <= 504) // capitaliste
                        {
                            draw_sprite(buffer, hud->bouton_menu, 357, 367);
                            textprintf_ex(buffer,myfont,430, 455, makecol(255,255,255),-1,"COMMUNISTE");
                            masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                        }
                        if(mouse_b & 1 && mouse_x>= 294 && mouse_x <= 636 && mouse_y >= 281 && mouse_y <= 334) // capitaliste
                        {
                            joueur->mode = 1;
                            t_joueur* joueur = init_joueur();
                            t_plateau* plateau = init_plateau();
                            t_affichage* hud = init_affichage(plateau);
                            masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                            int fait = 0;
                            while(!(mouse_b&2))
                            {
                                masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                                if(!fait){
                                    stop_sample(hud->son_menu);
                                    play_sample(hud->son_jeu, 255, 128, 1000, 1);
                                    fait = 1;
                                }
                                clear_bitmap(buffer);
                                affichage_hud(hud, buffer, joueur, plateau);

                                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            }
                            stop_sample(hud->son_jeu);
                        }
                        if(mouse_b & 1 && mouse_x>= 389 && mouse_x <= 642 && mouse_y >= 442 && mouse_y <= 505)
                        {
                            int fait = 0;
                            joueur = init_joueur();
                            joueur->mode = 2;
                            plateau = init_plateau();
                            hud = init_affichage(plateau);
                            while(!(mouse_b&2))
                            {
                                masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                                clear_bitmap(buffer);
                                if(!fait){
                                    stop_sample(hud->son_menu);
                                    play_sample(hud->son_jeu, 255, 128, 1000, 1);
                                    fait = 1;
                                }
                                affichage_hud(hud, buffer, joueur, plateau);
                                masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            }
                            stop_sample(hud->son_jeu);
                        }

                        //affichage_hud(hud, buffer, joueur);
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                }
                if(mouse_b&2)
                {
                    sortir = 1;
                    ok = 0;
                }
            }
        }
        // si on appui sur credit
        if( mouse_b & 1 &&  mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 538 && mouse_y <= 590 ) {
            while ( !(mouse_b & 1 &&  mouse_x>= 395 && mouse_x <= 635 && mouse_y >= 683 && mouse_y <= 738)) {
                clear_bitmap(buffer);
                affichage_son(buffer, hud->son_menu, &clic);
                if (clic)
                {
                    draw_sprite(buffer, hud->son_off, 960, 0);
                }
                else
                {
                    draw_sprite(buffer, hud->son_on, 960, 0);
                }
                blit(hud->credits,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

                textprintf_ex(buffer, myfont, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);
                textprintf_ex(buffer, myfont, 422, 264, makecol(0, 0, 0), -1, "Yohan MARCEL");
                textprintf_ex(buffer, myfont, 418, 371, makecol(0, 0, 0), -1, "Clement POMPEI");
                textprintf_ex(buffer, myfont, 442, 477, makecol(0, 0, 0), -1, "Sarah BLIN");
                textprintf_ex(buffer, myfont, 410, 584, makecol(0, 0, 0), -1, "Benjamin GENDRY");
                textprintf_ex(buffer, myfont, 485, 694, makecol(0, 0, 0), -1, "EXIT");

                if(mouse_x>= 395 && mouse_x <= 635 && mouse_y >= 683 && mouse_y <= 738)
                {
                    draw_sprite(buffer, hud->bouton_menu, 356, 609);
                    textprintf_ex(buffer, myfont, 485, 694, makecol(0, 0, 0), -1, "EXIT");
                }
                masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(20);
            }
        }
        // si on appui sur quitter
        if(mouse_b & 1  &&   mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 638 && mouse_y <= 700 ) {
            allegro_message("Merci d'avoir joue !");
            allegro_exit();
            exit(0);
        }

        if (mouse_b & 1 && mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 428 && mouse_y <= 482) //CONTINUER
        {
            install_keyboard();
            plateau = chargement_sauvegarde(hud, joueur, plateau);
            printf("lets go");
            printf("%d et %d et %d\n", joueur->mode, joueur->argent, joueur->habitants);
            for (int i = 0; i < 35; i++){
                for (int j = 0 ; j < 45; j++){
                    printf("%d pour %d et %d\n", plateau->matrice[i][j].element, i, j);
                }
            }
            while (!(mouse_b & 2)) {
                clear_bitmap(buffer);
                affichage_hud(hud, buffer, joueur, plateau);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }

        // clic gauche en haut à gauche de l'écran -> fin du programme
        if (mouse_b & 1 && mouse_x <= 40 && mouse_y <= 20)
            fin = 1;

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // prise en compte effective de la zone cliquable EXIT :
    }
    free(myfont);
}