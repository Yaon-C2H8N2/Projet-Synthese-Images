//
// Created by yaon on 19/10/22.
//

#ifndef PROJET_SYNTHESE_IMAGES_CUBE_H
#define PROJET_SYNTHESE_IMAGES_CUBE_H

#include <GL/glut.h>
#include "Point.h"

class Cube {
public:
    Point *pCube;
    int fCube[6][4] = {
            {0, 3, 2, 1},
            {0, 1, 5, 4},
            {1, 2, 6, 5},
            {2, 3, 7, 6},
            {0, 4, 7, 3},
            {4, 5, 6, 7}};

    Cube(double hauteur, double largeur, double profondeur);

    void draw();

    void draw()
};


#endif //PROJET_SYNTHESE_IMAGES_CUBE_H
