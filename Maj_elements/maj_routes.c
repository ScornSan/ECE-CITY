#include "../structures.h"
#include "../prototypes.h"

void maj_routes(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau, int lig, int col)
{
    if (plateau->matrice[lig-1][col].b_element == plateau->routes[0] || plateau->matrice[lig + 1][col].b_element == plateau->routes[0]){
        plateau->matrice[lig][col].b_element = plateau->routes[0];
    }
    if (plateau->matrice[lig][col].element == ROUTES)
    {
        // TOUT LES COUDES
        for (int i = 0; i < 10; i++){
            if (plateau->matrice[lig-1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[3];
            }
            if (plateau->matrice[lig+1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[5];
            }
            if (plateau->matrice[lig+1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[4];
            }
            if (plateau->matrice[lig-1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[2];
            }

            // TOUT LES 3 VOIES
            if (plateau->matrice[lig-1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1] && plateau->matrice[lig+1][col].b_element == plateau->routes[i])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[9];
            }
            if (plateau->matrice[lig+1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[7];
            }
            if (plateau->matrice[lig+1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1] && plateau->matrice[lig-1][col].b_element == plateau->routes[i])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[8];
            }
            if (plateau->matrice[lig-1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[6];
            }

            //CARREFOUR
            if (plateau->matrice[lig-1][col].b_element == plateau->routes[i] && plateau->matrice[lig][col-1].b_element == plateau->routes[i + 1] && plateau->matrice[lig][col+1].b_element == plateau->routes[i + 1] && plateau->matrice[lig+1][col].b_element == plateau->routes[i])
            {
                plateau->matrice[lig][col].b_element = plateau->routes[10];
            }
        }
    }
}

void maj_trottoirs(t_affichage *hud, BITMAP *buffer, t_joueur *joueur, t_plateau *plateau, int lig, int col)
{

    if (plateau->matrice[lig][col].element == TVAGUE || plateau->matrice[lig][col].element == TVAGUE_CP || plateau->matrice[lig][col].element == TVAGUE_CP_BP) //si trottoir
    {
        if (plateau->matrice[lig + 1][col + 1].element == TVAGUE || plateau->matrice[lig + 1][col + 1].element == TVAGUE_CP || plateau->matrice[lig + 1][col + 1].element == TVAGUE_CP_BP)
        {
            if (plateau->matrice[lig - 1][col - 1].element == TVAGUE || plateau->matrice[lig - 1][col - 1].element == TVAGUE_CP || plateau->matrice[lig - 1][col - 1].element == TVAGUE_CP_BP)
            {
                if (plateau->matrice[lig][col - 1].element == TVAGUE || plateau->matrice[lig][col - 1].element == TVAGUE_CP || plateau->matrice[lig][col - 1].element == TVAGUE_CP_BP)
                {
                    if (plateau->matrice[lig - 1][col].element == TVAGUE || plateau->matrice[lig - 1][col].element == TVAGUE_CP || plateau->matrice[lig - 1][col].element == TVAGUE_CP_BP)
                    {
                        if (plateau->matrice[lig + 1][col].element == TVAGUE || plateau->matrice[lig + 1][col].element == TVAGUE_CP || plateau->matrice[lig + 1][col].element == TVAGUE_CP_BP)
                        {
                            if (plateau->matrice[lig][col + 1].element == TVAGUE || plateau->matrice[lig][col + 1].element == TVAGUE_CP || plateau->matrice[lig][col + 1].element == TVAGUE_CP_BP)
                            {
                                if (plateau->matrice[lig-1][col+1].element == TVAGUE || plateau->matrice[lig-1][col+1].element == TVAGUE_CP || plateau->matrice[lig-1][col+1].element == TVAGUE_CP_BP)
                                {
                                    if(plateau->matrice[lig-1][col+1].element == TVAGUE || plateau->matrice[lig-1][col+1].element == TVAGUE_CP || plateau->matrice[lig-1][col+1].element == TVAGUE_CP_BP){
                                        plateau->matrice[lig][col].element = TVAGUE_CP;
                                    }
                                    else
                                    {
                                        plateau->matrice[lig][col].element = TVAGUE;
                                    }
                                }
                                else
                                {
                                    plateau->matrice[lig][col].element = TVAGUE;
                                }

                            }
                            else
                            {
                                plateau->matrice[lig][col].element = TVAGUE;
                            }
                        }
                        else
                        {
                            plateau->matrice[lig][col].element = TVAGUE;
                        }
                    }
                    else
                    {
                        plateau->matrice[lig][col].element = TVAGUE;
                    }
                }
                else
                {
                    plateau->matrice[lig][col].element = TVAGUE;
                }
            }
            else
            {
                plateau->matrice[lig][col].element = TVAGUE;
            }
        }
        else
        {
            plateau->matrice[lig][col].element = TVAGUE;
        }
    }
}