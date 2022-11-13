//
// Created by yaon on 12/11/22.
//

#include <cmath>
#include <GL/glut.h>
#include "Cylindre.h"

Cylindre::Cylindre(int nbFaces, double hauteur, double rayon) {
    this->nbFaces = nbFaces;
    this->hauteur = hauteur;
    this->rayon = rayon;
    this->posY = 0;
    this->posX = 0;
    this->posZ = 0;
}

void Cylindre::translate(double x, double y, double z) {
    this->posX += x;
    this->posY += y;
    this->posZ += z;
}

void Cylindre::rotate(double angle, int x, int y, int z) {

}

void Cylindre::draw() {
    disque(nbFaces, hauteur / 2, rayon);
    disque(nbFaces, -hauteur / 2, rayon);
    cotes(nbFaces, hauteur, rayon);
}

void Cylindre::cotes(int nbFaces, double hauteur, double rayon) {
    Point tabPointCotes[nbFaces * 2 + 2];
    int tabFacesCotes[nbFaces][4];

    for (int i = 0; i < nbFaces; i++) {
        tabPointCotes[i].x = this->posX + rayon * cos((2 * i * M_PI) / nbFaces);
        tabPointCotes[i].z = this->posZ + rayon * sin((2 * i * M_PI) / nbFaces);
        tabPointCotes[i].y = this->posY + (-hauteur / 2.0);

        tabPointCotes[i + nbFaces].x = this->posX + rayon * cos((2 * i * M_PI) / nbFaces);
        tabPointCotes[i + nbFaces].z = this->posZ + rayon * sin((2 * i * M_PI) / nbFaces);
        tabPointCotes[i + nbFaces].y = this->posY + hauteur / 2.0;
    }
    tabPointCotes[nbFaces * 2].x = this->posX;
    tabPointCotes[nbFaces * 2].z = this->posZ;
    tabPointCotes[nbFaces * 2].y = this->posY + (-hauteur / 2);

    tabPointCotes[nbFaces * 2 + 1].x = this->posX;
    tabPointCotes[nbFaces * 2 + 1].z = this->posZ;
    tabPointCotes[nbFaces * 2 + 1].y = this->posY + hauteur / 2;

    for (int i = 0; i < nbFaces; i++) {
        tabFacesCotes[i][0] = i;
        tabFacesCotes[i][1] = (i + 1) % nbFaces;
        tabFacesCotes[i][2] = (i + 1) % nbFaces + nbFaces;
        tabFacesCotes[i][3] = i + nbFaces;
    }

    for (int i = 0; i < nbFaces; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
            glColor3f(0.1, 0.1, 0.1);
            glVertex3f(tabPointCotes[tabFacesCotes[i][j]].x, tabPointCotes[tabFacesCotes[i][j]].y,
                       tabPointCotes[tabFacesCotes[i][j]].z);
        }
        glEnd();
    }
}

void Cylindre::disque(int nbFaces, double hauteur, double rayon) {
    Point tabPointDisque[nbFaces + 1];
    int tabFacesDisque[nbFaces][3];

    for (int i = 0; i < nbFaces; i++) {
        tabPointDisque[i].x = this->posX + rayon * cos((2 * i * M_PI) / nbFaces);
        tabPointDisque[i].z = this->posZ + rayon * sin((2 * i * M_PI) / nbFaces);
        tabPointDisque[i].y = this->posY + hauteur;
    }
    tabPointDisque[nbFaces].x = this->posX;
    tabPointDisque[nbFaces].z = this->posZ;
    tabPointDisque[nbFaces].y = this->posY + hauteur;

    for (int i = 0; i < nbFaces; i++) {
        tabFacesDisque[i][0] = i;
        tabFacesDisque[i][1] = (i + 1) % nbFaces;
        tabFacesDisque[i][2] = nbFaces;
    }

    for (int i = 0; i < nbFaces; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 3; j++) {
            glVertex3f(tabPointDisque[tabFacesDisque[i][j]].x, tabPointDisque[tabFacesDisque[i][j]].y,
                       tabPointDisque[tabFacesDisque[i][j]].z);
        }
        glEnd();
    }
}