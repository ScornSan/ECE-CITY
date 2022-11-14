#include "../structures.h"
#include "../prototypes.h"

void affichage_son(BITMAP *buffer/*, SAMPLE* s*/, int* clic )
{
    if(mouse_b&1 && mouse_x>= 960 && mouse_x <= 1024 && mouse_y >= 0&& mouse_y <= 50 && !*clic)
    {
        rest(100);
        *clic = 1;
        //stop_sample(s);
        //adjust_sample(s, 0, 0, 1000, 1);
    }
    if (mouse_b&1 && mouse_x>= 960 && mouse_x <= 1024 && mouse_y >= 0&& mouse_y <= 50 && *clic)
    {
        rest(100);
        *clic = 0;
        //adjust_sample(s, 255, 128, 1000, 1);
        //play_sample(s, 255, 128, 1000, 1);
    }
}

void affichage_menu(t_affichage* hud, BITMAP* buffer, int* clic, FONT* myfont)
{
    clear_bitmap(buffer);
    blit(hud->accueil,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    affichage_son(buffer, &(*clic));


    if (*clic)
    {
        draw_sprite(buffer, hud->son_off, 960, 0);
    }
    else
    {
        draw_sprite(buffer, hud->son_on, 960, 0);
    }

    rectfill(buffer,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(buffer,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");

    textprintf_ex(buffer,myfont,481,321, makecol(0,0,0),-1,"PLAY");
    textprintf_ex(buffer,myfont,460, 428, makecol(0,0,0),-1,"CREDITS");
    textprintf_ex(buffer,myfont,487, 537, makecol(0,0,0),-1,"EXIT");

    if ( mouse_x>= 400 && mouse_x <= 631 && mouse_y >= 322 && mouse_y <=377)
    {
        masked_blit(hud->bouton_menu, buffer, 0, 0, 357, 245, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer,myfont,481,321, makecol(0,0,0),-1,"PLAY");
    }

    if(  mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 428 && mouse_y <= 482)
    {
        draw_sprite(buffer, hud->bouton_menu, 357, 351);
        textprintf_ex(buffer,myfont,460, 428, makecol(0,0,0),-1,"CREDITS");
    }

    if(   mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 538 && mouse_y <= 590 )
    {
        draw_sprite(buffer, hud->bouton_menu, 357, 459);
        textprintf_ex(buffer,myfont,487, 537, makecol(0,0,0),-1,"EXIT");
    }
}

void prenom( BITMAP* buffer, t_joueur* joueur, int* clic, t_affichage* hud)
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
    rectfill(buffer,400,237,620,295,makecol(0,0,0 ));
    /// AFFICHAGE DES LETTRES QUE L'ON TAPE AU CLAVIER
    while (stop != 1)
    {
        affichage_son(buffer, &(*clic));
        if (*clic)
        {
            rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
            draw_sprite(buffer, hud->son_off, 960, 0);
        }
        else
        {
            rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
            draw_sprite(buffer, hud->son_on, 960, 0);
        }
        if (keypressed())
        {
            touche=readkey();
            carac = (char)touche;

            // afficher le caractère à une position x croissante
            if( carac != '\r' && !key[KEY_BACKSPACE] && compteur != 19)
            {
                textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0),"%c",carac);
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

void menu(t_affichage* hud, t_joueur* joueur, BITMAP* buffer, t_plateau *plateau) {
    int fin = 0;
    int ok = 0;
    int sortir = 0;
    int clic = 0;
    FONT* myfont;
    myfont = load_font("../FONT/tempus.pcx", NULL, NULL);

    clear_bitmap(buffer);
    // Boucle interactive
    while (!fin) {
        affichage_son(buffer, &clic);

        textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);

        if (clic)
        {
            draw_sprite(buffer, hud->son_off, 960, 0);
        }
        else
        {
            draw_sprite(buffer, hud->son_on, 960, 0);
        }

        affichage_menu(hud, buffer, &clic, myfont);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)

        // si on appui sur standard
        if (mouse_b & 1 && mouse_x>= 400 && mouse_x <= 631 && mouse_y >= 322 && mouse_y <=377) {
            ok = 0;
            sortir = 0;
            install_keyboard();
            while(ok!=1 && sortir!=1) {

                if (sortir != 1) {
                    install_keyboard();
                    clear_bitmap(buffer);
                    blit(hud->nom,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    prenom(buffer, joueur, &clic, hud);

                    while(!(mouse_b&2))
                    {
                        clear_bitmap(buffer);
                        blit(hud->mode,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        textprintf_ex(buffer,myfont,425, 289, makecol(0,0,0),-1,"COMMUNISTE");
                        textprintf_ex(buffer,myfont,430, 455, makecol(0,0,0),-1,"CAPITALISTE");
                        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                        textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);
                        if(mouse_b & 1 && mouse_x>= 294 && mouse_x <= 636 && mouse_y >= 281 && mouse_y <= 334)
                        {
                            while(!(mouse_b&2))
                            {
                                clear_bitmap(buffer);
                                affichage_hud(hud, buffer, joueur, plateau);
                                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            }
                        }
                        if(mouse_b & 1 && mouse_x>= 389 && mouse_x <= 642 && mouse_y >= 442 && mouse_y <= 505)
                        {
                            printf("test2");
                            while(!(mouse_b&2))
                            {
                                clear_bitmap(buffer);
                                affichage_hud(hud, buffer, joueur, plateau);
                                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            }
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
        if( mouse_b & 1 &&  mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 428 && mouse_y <= 482) {
            while ( !(mouse_b & 1 &&  mouse_x>= 395 && mouse_x <= 635 && mouse_y >= 683 && mouse_y <= 738)) {
                clear_bitmap(buffer);
                affichage_son(buffer,&clic);
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
        if(mouse_b & 1  &&  mouse_x>= 395 && mouse_x <= 631 && mouse_y >= 538 && mouse_y <= 590) {
            allegro_message("Merci d'avoir joue !");
            allegro_exit();
            exit(0);
        }

        // clic gauche en haut à gauche de l'écran -> fin du programme
        if (mouse_b & 1 && mouse_x <= 40 && mouse_y <= 20)
            fin = 1;

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // prise en compte effective de la zone cliquable EXIT :
    }
}