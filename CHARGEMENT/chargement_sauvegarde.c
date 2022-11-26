#include "../structures.h"
#include "../prototypes.h"

t_plateau* chargement_sauvegarde(t_affichage * hud, t_joueur* joueur, t_plateau* plateau){
    printf("1\n");
    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "r"); // ouverture du fichier pour recup une sauvegarde
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "r");
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "r");
    //FILE *ifs_batiment = fopen("../ifs_batiment.txt", "r");

    if (!ifs_plateau || !ifs_joueur || !ifs_habitation /*|| ifs_batiment*/) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    joueur = init_joueur();
    plateau = init_plateau();
    hud = init_affichage(plateau);
    init_batiments_et_constructions(hud);
    /// CHARGEMENT STRUCTURE JOUEUR

    fscanf(ifs_joueur, "%d\n", &(joueur->mode));
    printf("mode : %d\n", joueur->mode);
    fscanf(ifs_joueur, "%d\n", &(joueur->niveau));
    printf("niveau : %d\n", joueur->niveau);
    fscanf(ifs_joueur, "%d\n", &(joueur->argent));
    //printf("argent : %d\n", joueur->argent);
    fscanf(ifs_joueur, "%d\n", &(joueur->habitants));
    fscanf(ifs_joueur, "%d\n", &(joueur->totaleau));
    fscanf(ifs_joueur, "%d\n", &(joueur->totalelec));

    printf("joueur\n");

    BITMAP *buffer_pixel = create_bitmap(SCREEN_W, SCREEN_H);
    /// CHARGEMENT PLATEAU
    fscanf(ifs_plateau, "%d\n", &plateau->indice_tab_habitations);
    //printf("indice_tab_habitation : %d", plateau->indice_tab_habitations);
    fscanf(ifs_plateau, "%d\n", &plateau->indice_tab_batiment);
    //printf("indice_tab_batiment : %d", plateau->indice_tab_batiment);
    fscanf(ifs_plateau, "%d\n", &plateau->lig_mouse);
    fscanf(ifs_plateau, "%d\n", &plateau->col_mouse);
    fscanf(ifs_plateau, "%d\n", &plateau->screenx);
    fscanf(ifs_plateau, "%d\n", &plateau->screeny);
    fscanf(ifs_plateau, "%d\n", &plateau->lig);
    fscanf(ifs_plateau, "%d\n", &plateau->col);

    printf("FBIGUETGU : %d\n", plateau->id_terrain);
    switch(plateau->id_terrain){
        case 1:
            plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_NIV1.bmp", 0);
            break;
        case 2:
            plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_NIV2.bmp", 0);
            break;
        case 3:
            plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_NIV3.bmp", 0);
            break;
        case 4:
            plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_NIV4.bmp", 0);
            break;
        case 5:
            plateau->terrain = load_bitmap("../BITMAPS/Affichage/MAP_NIV5.bmp", 0);
            break;
    }
    plateau->calque_pixels = load_bitmap("../BITMAPS/Affichage/buffer_pixel_X.bmp", 0);
    plateau->buffer_pixels = buffer_pixel;
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


    for(int i = 0; i< 35; i++){
        /// MATRICE MAP
        for(int j = 0; j < 45; j++){
            fscanf(ifs_plateau, "%d\n", &plateau->matrice_map[i][j]);

            fscanf(ifs_plateau, "%d\n", &plateau->matrice[i][j].element);
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).id_element));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).x_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).y_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).affiche));
            plateau->matrice[i][j].affiche = 0;
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).ligne));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).colonne));
            for (int k = 0; k < 3; k++)
                fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).RGB[k]));

            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).id_bitmap));
            switch(plateau->matrice[i][j].id_bitmap){
                case 0:
                    printf("hihihiha\n");
                    plateau->matrice[i][j].b_element = plateau->routes[0];
                    break;
                case 1:
                    printf("HIHIHIHHA\n");
                    plateau->matrice[i][j].b_element = plateau->routes[1];
                    break;
                case 2:
                    plateau->matrice[i][j].b_element = plateau->routes[2];
                    break;
                case 3:
                    plateau->matrice[i][j].b_element = plateau->routes[3];
                    break;
                case 4:
                    plateau->matrice[i][j].b_element = plateau->routes[4];
                    break;
                case 5:
                    plateau->matrice[i][j].b_element = plateau->routes[5];
                    break;
                case 6:
                    plateau->matrice[i][j].b_element = plateau->routes[6];
                    break;
                case 7:
                    plateau->matrice[i][j].b_element = plateau->routes[7];
                    break;
                case 8:
                    plateau->matrice[i][j].b_element = plateau->routes[8];
                    break;
                case 9:
                    plateau->matrice[i][j].b_element = plateau->routes[9];
                    break;
                case 10:
                    plateau->matrice[i][j].b_element = plateau->routes[10];
                    break;
            }
        }
    }

    printf("plateau\n");

    /// CHARGEMENT T_CONSTRUCTION
    printf("\n\nCHARGEMENT CONSTRUCTION :\n");

    for(int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
    {
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->niveau);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->nb_residents);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->incendie);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->eau);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->elec);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->distance_centrale);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->distance_chateau);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->quantite_eau);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->quantite_elec);
        fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->id_element);
        //fscanf(ifs_habitation, "%d\n", &plateau->habitations[i]->timer);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).id_element);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).element);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).affiche);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).colonne);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).ligne);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).x_bloc);
        fscanf(ifs_habitation, "%d\n", &(plateau->habitations[i]->premier_bloc).y_bloc);
        /*fscanf(ifs_habitation, "%d\n", &build->niveau);
        fscanf(ifs_habitation, "%d\n", &build->nb_residents);
        fscanf(ifs_habitation, "%d\n", &build->incendie);
        fscanf(ifs_habitation, "%d\n", &build->eau);
        fscanf(ifs_habitation, "%d\n", &build->elec);
        fscanf(ifs_habitation, "%d\n", &build->distance_centrale);
        fscanf(ifs_habitation, "%d\n", &build->distance_chateau);
        fscanf(ifs_habitation, "%d\n", &build->quantite_eau);
        fscanf(ifs_habitation, "%d\n", &build->quantite_elec);
        fscanf(ifs_habitation, "%d\n", &build->id_element);
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).id_element));
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).element));
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).affiche));
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).colonne));
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).ligne));
        fscanf(ifs_habitation, "%d\n", &((build->premier_bloc).x_bloc));
        fscanf(ifs_habitation, "%d\n",&((build->premier_bloc).y_bloc));
        plateau->habitations[plateau->indice_tab_habitations] = build;*/
    }

    //affichage_elements(hud, buffer, joueur, plateau);
    printf("habitations\n");

    printf("CHARGEMENT BATIMENT :");
    /*for(int i = 0; i < plateau->indice_tab_batiment; i++)            /// STRUCTURE T_BATIMENT
    {
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->id_batiment);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->indice_ordre);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->quantite_ressource);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->element);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).id_element);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).element);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).affiche);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).colonne);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).ligne);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).x_bloc);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).y_bloc);
    }*/
    //ifs_batiment = NULL;
    fclose(ifs_joueur);
    fclose(ifs_plateau);
    fclose(ifs_habitation);

    return plateau;
}

