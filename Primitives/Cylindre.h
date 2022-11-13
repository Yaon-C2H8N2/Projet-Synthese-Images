//
// Created by yaon on 12/11/22.
//

#ifndef PROJET_SYNTHESE_IMAGES_CYLINDRE_H
#define PROJET_SYNTHESE_IMAGES_CYLINDRE_H


#include "Point.h"

class Cylindre {
private:
    int nbFaces;
    double hauteur;
    double rayon;
    double posX, posY, posZ;

    void cotes(int nbFaces, double hauteur, double rayon);

    void disque(int nbFaces, double hauteur, double rayon);

public:
    Cylindre(int nbFaces, double hauteur, double rayon);

    void draw();

    void translate(double x, double y, double z);

    void rotate(double angle, int x, int y, int z);
};


#endif //PROJET_SYNTHESE_IMAGES_CYLINDRE_H
