#include "../structures.h"
#include "../prototypes.h"

void chargement_sauvegarde(t_affichage * hud, BITMAP *buffer, t_joueur* joueur, t_plateau* plateau){
    printf("ok");
    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "r"); // ouverture du fichier pour recup une sauvegarde
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "r");
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "r");
    FILE *ifs_batiment = fopen("../ifs_batiment", "r");

    if (!ifs_plateau || !ifs_joueur || !ifs_habitation || ifs_batiment) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    /// CHARGEMENT STRUCTURE JOUEUR
    fscanf(ifs_joueur, "%d", &(joueur->mode));
    printf("mode : %d\n", joueur->mode);
    fscanf(ifs_joueur, "%d", &(joueur->niveau));
    printf("niveau : %d\n", joueur->niveau);
    fscanf(ifs_joueur, "%d", &(joueur->argent));
    printf("argent : %d\n", joueur->argent);
    fscanf(ifs_joueur, "%d", &(joueur->habitants));
    fscanf(ifs_joueur, "%d", &(joueur->totaleau));
    fscanf(ifs_joueur, "%d", &(joueur->totalelec));
    fclose(ifs_joueur);
    ifs_joueur = NULL;

    /// CHARGEMENT PLATEAU
    fscanf(ifs_plateau, "%d", &plateau->indice_tab_habitations);
    printf("indice_tab_habitation : %d", plateau->indice_tab_habitations);
    fscanf(ifs_plateau, "%d", &plateau->indice_tab_batiment);
    printf("indice_tab_batiment : %d", plateau->indice_tab_batiment);
    fscanf(ifs_plateau, "%d", &plateau->lig_mouse);
    fscanf(ifs_plateau, "%d", &plateau->col_mouse);


    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            fscanf(ifs_plateau, "%d", &plateau->matrice_map[i][j]);
        }
    }

    printf("\n\n Matrice plateau sauvegarde\n");  // POUR VERIF
    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){
            printf("%d ", plateau->matrice_map[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i< 35; i++){                                   /// MATRICE MAP
        for(int j = 0; j < 45; j++){
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).element));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).id_element));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).x_bloc));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).y_bloc));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).affiche));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).ligne));
            fscanf(ifs_plateau, "%d ", &((plateau->matrice[i][j]).colonne));
        }
    }
    printf("ok");
    fclose(ifs_plateau);
    ifs_plateau = NULL;

    /// CHARGEMENT T_CONSTRUCTION
    printf("\n\nCHARGEMENT CONSTRUCTION :\n");

    for(int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
    {
        t_construction *build = (t_construction *) malloc(sizeof(t_construction));
        fscanf(ifs_habitation, "%d", &build->niveau);
        fscanf(ifs_habitation, "%d", &build->nb_residents);
        fscanf(ifs_habitation, "%d", &build->incendie);
        fscanf(ifs_habitation, "%d", &build->eau);
        fscanf(ifs_habitation, "%d", &build->elec);
        fscanf(ifs_habitation, "%d", &build->distance_centrale);
        fscanf(ifs_habitation, "%d", &build->distance_chateau);
        fscanf(ifs_habitation, "%d", &build->quantite_eau);
        fscanf(ifs_habitation, "%d", &build->quantite_elec);
        fscanf(ifs_habitation, "%d", &build->id_element);
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).id_element));
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).element));
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).affiche));
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).colonne));
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).ligne));
        fscanf(ifs_habitation, "%d", &((build->premier_bloc).x_bloc));
        fscanf(ifs_habitation, "%d",&((build->premier_bloc).y_bloc));
        build->timer = time(NULL);
        plateau->habitations[plateau->indice_tab_habitations] = build;
    }

    //affichage_elements(hud, buffer, joueur, plateau);
    fclose(ifs_habitation);

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
}

