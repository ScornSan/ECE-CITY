#include "../structures.h"
#include "../prototypes.h"

// doit se mettre à jour toutes les 15 sec
// mode communiste = 1
// mode capitaliste = 2


void maj_habitation(int indice, t_plateau *plateau, t_joueur* joueur, BITMAP* buffer, t_affichage* hud)
{
    // build  niveau 1 (terrain-vague)
    printf("debutt");
    if (plateau->habitations[plateau->habitations[indice]->id_element]->niveau == 1)
    {
        if(joueur->mode == 1) // mode communiste
        {
            if(plateau->habitations[plateau->habitations[indice]->id_element]->eau == true && plateau->habitations[plateau->habitations[indice]->id_element]->elec == true && plateau->habitations[plateau->habitations[indice]->id_element]->incendie == true) {
                plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 10;
                plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 2;
            }

        }
        else // mode capitaliste
        {
            plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 10;
            plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 2;
            // 0 habitants donc pas d'impots
        }
    }

        // build  niveau 2 (cabane)
    else if (plateau->habitations[plateau->habitations[indice]->id_element]->niveau == 2) {

        if(joueur->mode == 1) // communiste
        {
            printf("good");
            if(plateau->habitations[plateau->habitations[indice]->id_element]->eau == true && plateau->habitations[plateau->habitations[indice]->id_element]->elec == true && plateau->habitations[plateau->habitations[indice]->id_element]->incendie == true) {
                joueur->argent = joueur->argent + (10*plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
                plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 50;
                plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 3;}
        }
        else // capitaliste
        {
            joueur->argent = joueur->argent + (10*plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
            plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 50;
            plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 3;
        }

    }

        // build  niveau 3 (maison)
    else if (plateau->habitations[plateau->habitations[indice]->id_element]->niveau  == 3) {

        if(joueur->mode == 1)
        {
            if(plateau->habitations[plateau->habitations[indice]->id_element]->eau == true && plateau->habitations[plateau->habitations[indice]->id_element]->elec == true && plateau->habitations[plateau->habitations[indice]->id_element]->incendie == true) {
                joueur->argent = joueur->argent + (10 * plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
                plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 100;
                plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 4; }
        }
        else
        {
            joueur->argent = joueur->argent + (10 * plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
            plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 100;
            plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 4;

        }

    }

        // build  niveau 4 (immeuble)
    else if (plateau->habitations[plateau->habitations[indice]->id_element]->niveau  == 4) {

        if(joueur->mode == 1)
        {
            printf("ok");
            if(plateau->habitations[plateau->habitations[indice]->id_element]->eau == true && plateau->habitations[plateau->habitations[indice]->id_element]->elec == true && plateau->habitations[plateau->habitations[indice]->id_element]->incendie == true) {
                joueur->argent = joueur->argent + (10*plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
                plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 5;
                plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 1000;}
        }
        else
        {
            joueur->argent = joueur->argent + (10*plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
            plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 5;
            plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents = 1000;}
    }




        //build  niveau 4 (gratte-ciel) // ne peut plus évoluer
    else if (plateau->habitations[plateau->habitations[indice]->id_element]->niveau  == 5) {

        if(joueur->mode == 1)
        {
            joueur->argent = joueur->argent + (10 * plateau->habitations[plateau->habitations[indice]->id_element]->nb_residents);
            plateau->habitations[plateau->habitations[indice]->id_element]->niveau = 4;
        }
        else
        {


        }

    }
}