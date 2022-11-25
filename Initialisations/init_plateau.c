#include "../structures.h"
#include "../prototypes.h"

void chargement_partie(t_bloc matrice[35][45]){
    FILE *ifs = fopen("../Fichier_map.txt", "r"); // ouverture du fichier pour recup une sauvegarde

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    //// récuperation d'une map existante ( ou non a faire avec condition)
    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            fscanf(ifs, "%d", &matrice[i][j].element);
        }
    }
    fclose(ifs);
    ifs = NULL;
}

t_plateau* distribution_couleur_blocs(t_plateau* plateau)
{
    for (int j = 0; j<35; j++)      // boucle pour les lignes
    {
        for (int k = 0; k<45; k++)      // boucle pour les colonnes
        {
            int red = 5+ 5*k, green = 7 +j*7, blue = 10;    // definition des couleurs pour en avoir une différente a chaque fois
            /// triangle en bas a gauche
            int x1 = 26 +11*j +k*13;
            int y1 = 478 +7*j -k*8;
            /// triangle en bas a droitee
            int x4 = 38 +11*j +k*13;     // x de base + largeur du bas +1  donc 26 + 11 + 1 = 38
            int y4 = 477 +7*j -k*8;      // y de base - 1 donc 477
            /// triangle en haut a gauche
            int x2 = 26 +13*k +j*11;
            int y2 = 478 -8*k +j*7;
            /// triangle en haut à droite
            int x3 = 40 +13*k +j*11;   // x de base + largeur du haut +1  donc 26 + 14 = 40
            int y3= 477 -8*k +j*7;   // y de base - 1 donc 477

            plateau->matrice[j][k].RGB[0] = red;
            plateau->matrice[j][k].RGB[1] = green;
            plateau->matrice[j][k].RGB[2] = blue;
            plateau->matrice[j][k].ligne = j;
            plateau->matrice[j][k].element = 0;
            plateau->matrice[j][k].id_element = -1;
            plateau->matrice[j][k].affiche = 0;
            plateau->matrice[j][k].colonne = k;
            plateau->screenx = 100;
            plateau->screeny = 100;
            plateau->compteur_x = 0;
            plateau->compteur_y = 0;
            plateau->matrice[j][k].x_bloc = 38 +k*13 +j*11 + 100;
            plateau->matrice[j][k].y_bloc = 478 -k*8 +j*7 + 100;

            /*for(int i = 0; i< 6; i++)
            {
                line(plateau->buffer_pixels, x1 +2*i , y1 +i , x1 +12 , y1 +i , makecol(red,green,blue));
            }
            putpixel(plateau->buffer_pixels, x1 +11 , y1 +6 , makecol(red,green,blue));
            for(int i = 0; i< 7; i++)
            {
                line(plateau->buffer_pixels, x2 +2*i , y2 -i , x2 +14 , y2 -i , makecol(red,green,blue));
            }
            putpixel(plateau->buffer_pixels, x2 +13 , y1 +7 , makecol(red,green,blue));
            for(int i = 0; i< 6; i++)
            {
                line(plateau->buffer_pixels, x3 -1  , y3 -i , x3 +12-2*i , y3 -i , makecol(red,green,blue));
            }
            putpixel(plateau->buffer_pixels, x3 , y3 -6 , makecol(red,green,blue));
            for(int i = 0; i< 7; i++)
            {
                line(plateau->buffer_pixels, x4-1 , y4 +i , x4 +14 -2*i , y4 +i , makecol(red,green,blue));
            }
            putpixel(plateau->buffer_pixels, x4 , y4 +7 , makecol(red,green,blue));*/
        }
    }
    return plateau;
}

t_plateau* init_plateau() {
    BITMAP *buffer_pixel = create_bitmap(SCREEN_W, SCREEN_H);
    t_plateau *plateau = (t_plateau *) malloc(sizeof(t_plateau));
    plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_agrandi.bmp", 0);
    plateau->buffer_pixels = buffer_pixel;
    plateau->calque_pixels = load_bitmap("../BITMAPS/Affichage/buffer_pixel_X.bmp", 0);
    plateau->indice_tab_batiment = 0;
    plateau->indice_tab_habitations = 0;
    plateau->routes[0] = load_bitmap("../BITMAPS/BUILDS/ROUTES/route1.bmp", 0);
    plateau->routes[1] = load_bitmap("../BITMAPS/BUILDS/ROUTES/route2.bmp", 0);
    plateau->routes[2] = load_bitmap("../BITMAPS/BUILDS/ROUTES/coude1.bmp", 0);
    plateau->routes[3] = load_bitmap("../BITMAPS/BUILDS/ROUTES/coude2.bmp", 0);
    plateau->routes[4] = load_bitmap("../BITMAPS/BUILDS/ROUTES/coude3.bmp", 0);
    plateau->routes[5] = load_bitmap("../BITMAPS/BUILDS/ROUTES/coude4.bmp", 0);
    plateau->routes[6] = load_bitmap("../BITMAPS/BUILDS/ROUTES/3voies1.bmp", 0);
    plateau->routes[7] = load_bitmap("../BITMAPS/BUILDS/ROUTES/3voies2.bmp", 0);
    plateau->routes[8] = load_bitmap("../BITMAPS/BUILDS/ROUTES/3voies3.bmp", 0);
    plateau->routes[9] = load_bitmap("../BITMAPS/BUILDS/ROUTES/3voies4.bmp", 0);
    plateau->routes[10] = load_bitmap("../BITMAPS/BUILDS/ROUTES/carrefour.bmp", 0);
    plateau->batiments = malloc(sizeof (t_batiment));
    plateau->habitations = malloc(sizeof (t_construction));
    chargement_partie(plateau->matrice);
    distribution_couleur_blocs(plateau);
}
