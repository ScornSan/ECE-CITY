#include "../structures.h"
#include "../prototypes.h"

void chargement_sauvegarde(t_affichage * hud, BITMAP *buffer, t_joueur* joueur, t_plateau* plateau){
    printf("1\n");
    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "r"); // ouverture du fichier pour recup une sauvegarde
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "r");
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "r");
    FILE *ifs_batiment = fopen("../ifs_batiment", "r");

    if (!ifs_plateau || !ifs_joueur || !ifs_habitation || ifs_batiment) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    /// CHARGEMENT STRUCTURE JOUEUR
    joueur = init_joueur();
    fscanf(ifs_joueur, "%d\n", &(joueur->mode));
    printf("mode : %d\n", joueur->mode);
    fscanf(ifs_joueur, "%d\n", &(joueur->niveau));
    printf("niveau : %d\n", joueur->niveau);
    fscanf(ifs_joueur, "%d\n", &(joueur->argent));
    //printf("argent : %d\n", joueur->argent);
    fscanf(ifs_joueur, "%d\n", &(joueur->habitants));
    printf("3\n");
    fscanf(ifs_joueur, "%d\n", &(joueur->totaleau));
    fscanf(ifs_joueur, "%d\n", &(joueur->totalelec));
    fclose(ifs_joueur);
    printf("joueur\n");

    /// CHARGEMENT PLATEAU
    plateau = init_plateau();
    fscanf(ifs_plateau, "%d\n", &plateau->indice_tab_habitations);
    //printf("indice_tab_habitation : %d", plateau->indice_tab_habitations);
    fscanf(ifs_plateau, "%d\n", &plateau->indice_tab_batiment);
    //printf("indice_tab_batiment : %d", plateau->indice_tab_batiment);
    fscanf(ifs_plateau, "%d\n", &plateau->lig_mouse);
    fscanf(ifs_plateau, "%d\n", &plateau->col_mouse);
    fscanf(ifs_plateau, "%d\n", &plateau->screenx);
    fscanf(ifs_plateau, "%d\n", &plateau->screeny);

    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            fscanf(ifs_plateau, "%d\n", &plateau->matrice_map[i][j]);
        }
    }

    for(int i = 0; i< 35; i++){
        /// MATRICE MAP
        for(int j = 0; j < 45; j++){
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).element));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).id_element));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).x_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).y_bloc));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).affiche));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).ligne));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).colonne));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).RGB));
            fscanf(ifs_plateau, "%d\n", &((plateau->matrice[i][j]).b_element));
        }
    }

    fclose(ifs_plateau);
    ifs_plateau = NULL;
    printf("plateau\n");

    /// CHARGEMENT T_CONSTRUCTION
    printf("\n\nCHARGEMENT CONSTRUCTION :\n");

    for(int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
    {
        t_construction *build = (t_construction *) malloc(sizeof(t_construction));
        fscanf(ifs_habitation, "%d\n", &build->niveau);
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
    }

    //affichage_elements(hud, buffer, joueur, plateau);
    fclose(ifs_habitation);
    printf("habitations\n");
    /*
    printf("CHARGEMENT BATIMENT :");
    for(int i = 0; i < plateau->indice_tab_batiment; i++)            /// STRUCTURE T_BATIMENT
    {
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->id_batiment);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->indice_ordre);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->quantite_ressource);
        fscanf(ifs_batiment, "%d", &plateau->batiments[i]->id_batiment);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).id_element);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).element);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).affiche);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).colonne);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).ligne);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).x_bloc);
        fscanf(ifs_batiment, "%d", &(plateau->batiments[i]->premier_bloc).y_bloc);
    }
    ifs_batiment = NULL;
    ifs_habitation = NULL;*/
    hud = init_affichage();
}
