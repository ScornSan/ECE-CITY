#include "../structures.h"
#include "../prototypes.h"

void dessin_bloc_unique(BITMAP *buffer, int k, int l, t_plateau *plateau, int red, int green, int blue) {
    if (k >= 0 && k <= 34 && l <= 44 && l >= 0) {
        int x1 = 26 + 11 * k + l * 13;
        int y1 = 478 + 7 * k - l * 8;
        /// triangle en bas a droitee
        int x4 = 38 + 11 * k + l * 13;     // x de base + largeur du bas +1  donc 26 + 11 + 1 = 38
        int y4 = 477 + 7 * k - l * 8;      // y de base - 1 donc 477
        /// triangle en haut a gauche
        int x2 = 26 + 13 * l + k * 11;
        int y2 = 478 - 8 * l + k * 7;
        /// triangle en haut Ã  droite
        int x3 = 40 + 13 * l + k * 11;   // x de base + largeur du haut +1  donc 26 + 14 = 40
        int y3 = 477 - 8 * l + k * 7;
        for (int i = 0; i < 6; i++) {
            line(buffer, x1 + 2 * i, y1 + i, x1 + 12, y1 + i, makecol(red, green, blue));
        }
        putpixel(buffer, x1 + 11, y1 + 6, makecol(red, green, blue));
        for (int i = 0; i < 7; i++) {
            line(buffer, x2 + 2 * i, y2 - i, x2 + 14, y2 - i, makecol(red, green, blue));
        }
        putpixel(buffer, x2 + 13, y1 + 7, makecol(red, green, blue));
        for (int i = 0; i < 6; i++) {
            line(buffer, x3 - 1, y3 - i, x3 + 12 - 2 * i, y3 - i, makecol(red, green, blue));
        }
        putpixel(buffer, x3, y3 - 6, makecol(red, green, blue));
        for (int i = 0; i < 7; i++) {
            line(buffer, x4 - 1, y4 + i, x4 + 14 - 2 * i, y4 + i, makecol(red, green, blue));
        }
        putpixel(buffer, x4, y4 + 7, makecol(red, green, blue));
    }
}