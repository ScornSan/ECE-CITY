#include "../structures.h"
#include "../prototypes.h"
#define SRUINE 11
#define SCHANTIER 12
#define SCABANE 13
#define SMAISON 14
#define SBUILDING 15
#define SGRATTECIEL 16
#define SCHATEAU 17
#define SCENTRALE 18
#define SCASERNE 19
#define SECOLE 20

t_plateau* chargement_sauvegarde(t_affichage * hud, t_joueur* joueur, t_plateau* plateau, t_batiment* batiments) {
    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "r"); // ouverture du fichier pour recup une sauvegarde
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "r");
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "r");
    FILE *ifs_batiment = fopen("../ifs_bat.txt", "r");

    if (!ifs_plateau || !ifs_joueur || !ifs_habitation || !ifs_batiment) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    joueur = init_joueur();
    plateau = init_plateau();
    hud = init_affichage(plateau);
    batiments = init_batiments(hud);
    /// CHARGEMENT STRUCTURE JOUEUR
    fscanf(ifs_joueur, "%d\n", &(joueur->mode));
    fscanf(ifs_joueur, "%d\n", &(joueur->niveau));
    fscanf(ifs_joueur, "%d\n", &(joueur->argent));
    fscanf(ifs_joueur, "%d\n", &(joueur->habitants));
    fscanf(ifs_joueur, "%d\n", &(joueur->totaleau));
    fscanf(ifs_joueur, "%d\n", &(joueur->totalelec));
    fscanf(ifs_joueur, "%d\n", &(joueur->nb_banques));
    fscanf(ifs_joueur, "%f\n", &(joueur->coeff_banque));
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

    printf("FBIGUETGU : %d\n", plateau->id_terrain);
    switch (plateau->id_terrain) {
        case 1:
            plateau->terrain[0] = load_bitmap("../BITMAPS/Affichage/MAP_NIV1.bmp", 0);
            break;
        case 2:
            plateau->terrain[1] = load_bitmap("../BITMAPS/Affichage/MAP_NIV2.bmp", 0);
            break;
        case 3:
            plateau->terrain[2] = load_bitmap("../BITMAPS/Affichage/MAP_NIV3.bmp", 0);
            break;
        case 4:
            plateau->terrain[3] = load_bitmap("../BITMAPS/Affichage/MAP_NIV4.bmp", 0);
            break;
        case 5:
            plateau->terrain[4] = load_bitmap("../BITMAPS/Affichage/MAP_NIV5.bmp", 0);
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


    for (int i = 0; i < 35; i++) {
        /// MATRICE MAP
        for (int j = 0; j < 45; j++) {

            fscanf(ifs_plateau, "%d\n", &plateau->matrice[i][j].element);
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).id_element));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).x_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).y_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).affiche));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).ligne));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).colonne));
            for (int k = 0; k < 3; k++)
                fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).RGB[k]));

            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).id_bitmap));
            switch (plateau->matrice[i][j].id_bitmap) {
                case 0:
                    //printf("hihihiha %d et %d car %d\n", i, j, plateau->matrice[i][j].id_bitmap);
                    plateau->matrice[i][j].b_element = plateau->routes[0];
                    break;
                case 1:
                    //printf("HIHIHIHHA %d et %d\n", i, j);
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
                case SRUINE:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/ruine.bmp", 0);
                    break;
                case SCHANTIER:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/chantier.bmp", 0);
                    break;
                case SCABANE:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
                    break;
                case SMAISON:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
                    break;
                case SBUILDING:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
                    break;
                case SGRATTECIEL:
                    plateau->matrice[i][j].b_element = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
                    break;
                case SCHATEAU:
                    plateau->matrice[i][j].b_element = plateau->bitmap_bat[0];
                    break;
                case SCENTRALE:
                    plateau->matrice[i][j].b_element = plateau->bitmap_bat[1];
                    break;
                case SCASERNE:
                    plateau->matrice[i][j].b_element = plateau->bitmap_bat[2];
                    break;
                case SECOLE:
                    plateau->matrice[i][j].b_element = plateau->bitmap_bat[3];
                    break;
            }
        }
    }

    printf("plateau\n");

    /// CHARGEMENT T_CONSTRUCTION
    printf("\n\nCHARGEMENT CONSTRUCTION :\n");

    for (int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
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

        switch (plateau->habitations[i]->niveau) {
            case 0:
                plateau->habitations[i]->style[0] = load_bitmap("../BITMAPS/BUILDS/ruine.bmp", 0);
                break;
            case 1:
                plateau->habitations[i]->style[1] = load_bitmap("../BITMAPS/BUILDS/chantier.bmp", 0);
                break;
            case 2:
                plateau->habitations[i]->style[2] = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
                break;
            case 3:
                plateau->habitations[i]->style[3] = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
                break;
            case 4:
                plateau->habitations[i]->style[4] = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
                break;
            case 5:
                plateau->habitations[i]->style[5] = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
                break;
        }
    }
        //plateau->habitations[indice]->style[plateau->habitations[indice]->niveau]
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
        plateau->habitations[plateau->indice_tab_habitations] = build;
    }*/

    //affichage_elements(hud, buffer, joueur, plateau, plateau->terrain[plateau->etape]);

    printf("D\n");
    printf("CHARGEMENT BATIMENT :\n");
    printf("%d\n", plateau->indice_tab_batiment);
    plateau->batiments = realloc(plateau->batiments, sizeof (t_batiment) * (plateau->indice_tab_batiment));
    for(int i = 0; i < plateau->indice_tab_batiment; i++)            /// STRUCTURE T_BATIMENT
    {
        t_batiment * batiments = (t_batiment*)malloc(sizeof(t_batiment));
        printf("%d\n", i);
        fscanf(ifs_batiment, "%d\n", &batiments->id_batiment);
        printf("ahah");
        printf("%d et %d\n", i, batiments->id_batiment);
        fscanf(ifs_batiment, "%d\n", &batiments->indice_ordre);
        fscanf(ifs_batiment, "%d\n", &batiments->quantite_ressource);
        fscanf(ifs_batiment, "%d\n", &batiments->element);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.id_element);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.element);
        printf("%d et %d\n", i, batiments->premier_bloc.element);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.affiche);
        printf("%d et %d\n", i, batiments->premier_bloc.affiche);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.colonne);
        printf("%d et %d\n", i, batiments->premier_bloc.colonne);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.ligne);
        printf("%d et %d\n", i, batiments->premier_bloc.ligne);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.x_bloc);
        printf("%d et %d\n", i, batiments->premier_bloc.x_bloc);
        fscanf(ifs_batiment, "%d\n", &batiments->premier_bloc.y_bloc);
        printf("%d et %d\n", i, batiments->premier_bloc.y_bloc);

        printf("ahah %d\n", i);
        plateau->batiments[i]->id_batiment = 1;
        printf("ahah %d et %d\n", i, batiments->id_batiment);

        plateau->batiments[i]->id_batiment = batiments->id_batiment;
        printf("%d et %d\n", i, batiments->id_batiment);
        plateau->batiments[i]->indice_ordre = batiments->indice_ordre;
        plateau->batiments[i]->quantite_ressource = batiments->quantite_ressource;
        plateau->batiments[i]->element = batiments->element;
        printf("%d et %d\n", i, batiments->id_batiment);
        plateau->batiments[i]->premier_bloc.id_element = batiments->id_batiment;
        plateau->batiments[i]->premier_bloc.element = batiments->premier_bloc.element;
        printf("%d et %d\n", i, plateau->batiments[i]->premier_bloc.element);
        plateau->batiments[i]->premier_bloc.affiche = batiments->premier_bloc.affiche;
        plateau->batiments[i]->premier_bloc.colonne = batiments->premier_bloc.colonne;
        plateau->batiments[i]->premier_bloc.ligne = batiments->premier_bloc.ligne;
        plateau->batiments[i]->premier_bloc.x_bloc = batiments->premier_bloc.x_bloc;
        plateau->batiments[i]->premier_bloc.y_bloc = batiments->premier_bloc.y_bloc;
        printf("%d et %d\n", i, plateau->batiments[i]->premier_bloc.y_bloc);

    }
        //ifs_batiment = NULL;
        fclose(ifs_joueur);
        fclose(ifs_plateau);
        fclose(ifs_habitation);

        return plateau;
}

