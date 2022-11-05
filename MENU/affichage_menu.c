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

void affichage_menu(t_affichage* hud, BITMAP* buffer, int* clic)
{
    clear_bitmap(buffer);
    blit(hud->accueil,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    affichage_son(buffer, &(*clic));
    FONT* myfont = load_font("../FONT/franklin.pcx", NULL, NULL);

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

    rectfill(buffer,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(buffer,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");

    textprintf_ex(buffer,myfont,460,88,makecol(0,0,0), -1,"ECE CITY ");

    // 4 rectangles noirs
    rectfill(buffer,400,150,635,180,makecol(0,0,0 ));
    rectfill(buffer,400,200,635,230,makecol(0,0,0 ));
    rectfill(buffer,400,260,635,290,makecol(0,0,0 ));

    textprintf_ex(buffer,font,478,165, makecol(255,255,255),-1,"STANDARD");
    textprintf_ex(buffer,font,478, 215, makecol(255,255,255),-1,"CREDIT");
    textprintf_ex(buffer,font,478, 270, makecol(255,255,255),-1,"QUITTER");

    if ( mouse_x>= 400 && mouse_x <= 635 && mouse_y >= 150 && mouse_y <= 180)
    {
        textprintf_ex(buffer,font,478,165, makecol(0,255,0),-1,"STANDARD");
    }

    if(  mouse_x>= 400 && mouse_x <= 635 && mouse_y >= 200 && mouse_y <= 230 )
    {
        textprintf_ex(buffer,font,478, 215, makecol(0,255,0),-1,"CREDIT");
    }

    if(  mouse_x>= 400 && mouse_x <= 635 && mouse_y >= 260 && mouse_y <= 290 )
    {
        textprintf_ex(buffer,font,478, 270, makecol(0,255,0),-1,"QUITTER");
    }
}

void prenom( BITMAP* buffer, char pseudo[20], int* clic, t_affichage* hud)
{
    int x = 365;
    int touche;
    char carac;
    int y = 170;
    int stop = 0;
    int  poscarac= 0;
    int place= 0;
    int nb = 0;
    int compteur = 0;
    fflush(stdin);
    poscarac = 0;
    textprintf_ex(buffer,font,365,100, makecol(0,255,0),-1, "BIENVENUE DANS UNE NOUVELLE PARTIE !");
    textprintf_ex(buffer,font,365,135, makecol(0,255,0),-1, "CHER JOUEUR, ENTREZ VOTRE PSEUDO:");

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
                pseudo[place] = carac;
                poscarac = poscarac+8;
                compteur = compteur +1;
            }

            if (key[KEY_BACKSPACE] && x+poscarac >= 373)
            {
                if(x+poscarac == 373)
                {
                    poscarac=poscarac-8;
                    pseudo[place] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                    compteur = compteur -1;
                }
                else
                {
                    nb = nb +1;
                    poscarac=poscarac-8;
                    pseudo[place-1] = ' ';
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

void menu(t_affichage* hud, t_joueur* joueur, BITMAP* buffer, char pseudo[20]) {
    int fin = 0;
    int ok = 0;
    int sortir = 0;
    int clic = 0;

    clear_bitmap(buffer);
    // Boucle interactive
    while (!fin) {
        affichage_son(buffer, &clic);

        if (clic)
        {
            rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
            draw_sprite(buffer, hud->son_off, 960, 0);
        }
        else
        {
            rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
            draw_sprite(buffer, hud->son_on, 960, 0);
        }
        affichage_menu(hud, buffer, &clic);
        masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
        textprintf_ex(buffer, font, 60, 300, makecol(0, 255, 0), makecol(0, 0, 0), "%4d %4d", mouse_x, mouse_y);

        // si on appui sur standard
        if (mouse_b & 1 && mouse_x >= 400 && mouse_x <= 635 && mouse_y >= 150 && mouse_y <= 180) {
            ok = 0;
            sortir = 0;
            install_keyboard();
            while(ok!=1 && sortir!=1) {

                if (sortir != 1) {
                    install_keyboard();
                    clear_bitmap(buffer);
                    prenom(buffer, pseudo, &clic, hud);

                    while(!(mouse_b&2))
                    {
                        clear_bitmap(buffer);
                        affichage_hud(hud, buffer, joueur);
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
        if( mouse_b & 1 && mouse_x>= 400 && mouse_x <= 635 && mouse_y >= 200 && mouse_y <= 230) {
            while (!key[KEY_ESC] && !(mouse_b & 2)) {
                clear_bitmap(buffer);
                affichage_son(buffer,&clic);
                if (clic)
                {
                    rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
                    draw_sprite(buffer, hud->son_off, 960, 0);
                }
                else
                {
                    rectfill(buffer,960,0,1024,50,makecol( 255,255,255 ));
                    draw_sprite(buffer, hud->son_on, 960, 0);
                }
                masked_blit(hud->cursor, buffer, 0, 0, mouse_x - 5, mouse_y - 5, SCREEN_W, SCREEN_H);
                textprintf_ex(buffer, font, 460, 80, makecol(255, 255, 255), -1, "  CREDITS  ");
                textprintf_ex(buffer, font, 460, 100, makecol(255, 255, 255), -1, "Yohan MARCEL");
                textprintf_ex(buffer, font, 460, 110, makecol(255, 255, 255), -1, "Clement POMPEI");
                textprintf_ex(buffer, font, 460, 120, makecol(255, 255, 255), -1, "Sarah BLIN");
                textprintf_ex(buffer, font, 460, 130, makecol(255, 255, 255), -1, "Benjamin GENDRY");

                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(20);
            }
        }
        // si on appui sur quitter
        if(mouse_b & 1  && mouse_x>= 400 && mouse_x <= 635 && mouse_y >= 260 && mouse_y <= 290 ) {
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
