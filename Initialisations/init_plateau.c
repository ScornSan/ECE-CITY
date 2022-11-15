#include "../structures.h"
#include "../prototypes.h"

void chargement_partie(int matrice_map[35][45]){
    FILE *ifs = fopen("../Fichier_map.txt", "r"); // ouverture du fichier pour recup une sauvegarde

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    //// récuperation d'une map existante ( ou non a faire avec condition)
    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            fscanf(ifs, "%d", &matrice_map[i][j]);
        }
    }
    fclose(ifs);
    ifs = NULL;
}

void sauvegarde(int matrice_map[35][45]){
    FILE *ifs = fopen("../fichier_map.txt", "w"); /// ouvertue du fichier en mode ecriture
    /// On écrase l'ancienne map et on sauvegarde la nouvelle (celle de notre partie déjà commencée
    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            fprintf(ifs, "%d ", matrice_map[i][j]);
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
    ifs = NULL;
    /// si on veut continuer la partie après sauvegarde ou juste quitter après sauvegarde
    //return plateau;
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
            plateau->matrice[j][k].x_bloc = 38 +k*13 +j*11;
            plateau->matrice[j][k].y_bloc = 478 -k*8 +j*7;
            for(int i = 0; i< 6; i++)
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
            putpixel(plateau->buffer_pixels, x4 , y4 +7 , makecol(red,green,blue));
        }
    }
    return plateau;
}

t_plateau* init_plateau() {
    BITMAP *buffer_pixel = create_bitmap(SCREEN_W, SCREEN_H);
    t_plateau *plateau = (t_plateau *) malloc(sizeof(t_plateau));
    plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_1.5.bmp", 0);
    plateau->terraingris = load_bitmap("../BITMAPS/Affichage/MAP_1.5grise.bmp", 0);
    plateau->buffer_pixels = buffer_pixel;
    chargement_partie(plateau->matrice_map);
    distribution_couleur_blocs(plateau);
}

void quadrillage_test(BITMAP * buffer)
{
    for( int i = 0; i<36; i++){
        line(buffer, 26 +i*11, 478 +i*7, 612 +i*11, 118+i*7, makecol(255,0,0)); //horizontale
    }
    for ( int i = 0; i < 46; i++){
        line(buffer, 26 +i*13, 478 -i*8, 410 +i*13, 723 -i*8, makecol(255,0,0)); // verticale
    }
}
