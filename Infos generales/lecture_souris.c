//
// Created by Gendry on 05/11/2022.
//
#include "../structures.h"
#include "../prototypes.h"

void lecture_pixels_buffer_map(BITMAP * buffer_map, int *red_mouse, int *green_mouse, int *blue_mouse)
{
    *green_mouse = getg(getpixel(buffer_map, mouse_x, mouse_y));
    *red_mouse = getr(getpixel(buffer_map, mouse_x, mouse_y));
    *blue_mouse = getb(getpixel(buffer_map, mouse_x, mouse_y));
}

void reperage_bloc_souris(t_plateau* plateau)
{
    int red_mouse, green_mouse, blue_mouse;
    lecture_pixels_buffer_map(plateau->buffer_pixels, &red_mouse, &green_mouse, &blue_mouse);
    if (red_mouse != 0 && green_mouse != 0 && blue_mouse != 0)
    {
        for (int j = 0; j<35; j++)
        {
            for (int k = 0; k<45; k++)
            {
                if (plateau->matrice[j][k].RGB[0] == red_mouse && plateau->matrice[j][k].RGB[1] == green_mouse && plateau->matrice[j][k].RGB[2] == blue_mouse)
                {
                    plateau->lig_mouse = j;
                    plateau->col_mouse = k;
                }
            }
        }
    }
    else{
        plateau->lig_mouse = -1;
        plateau->col_mouse = -1;

    }
}
