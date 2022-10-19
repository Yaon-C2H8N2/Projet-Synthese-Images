//
// Created by yaon on 19/10/22.
//

#include "Cube.h"

void Cube::draw() {
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
            glColor3f(this->pCube[this->fCube[i][j]].r, this->pCube[this->fCube[i][j]].g,
                      this->pCube[this->fCube[i][j]].b);
            glVertex3f(this->pCube[this->fCube[i][j]].x, this->pCube[this->fCube[i][j]].y,
                       this->pCube[this->fCube[i][j]].z);
        }
        glEnd();
    }
}

Cube::Cube(double hauteur, double largeur, double profondeur) {
    this->pCube = new Point[8];
    this->pCube[0] = {(-largeur / 2), (-hauteur / 2), (profondeur / 2), 1.0, 0.0, 0.0};
    this->pCube[1] = {(largeur / 2), (-hauteur / 2), (profondeur / 2), 0.0, 1.0, 0.0};
    this->pCube[2] = {(largeur / 2), (-hauteur / 2), (-profondeur / 2), 0.0, 0.0, 1.0};
    this->pCube[3] = {(-largeur / 2), (-hauteur / 2), (-profondeur / 2), 1.0, 1.0, 1.0};
    this->pCube[4] = {(-largeur / 2), (hauteur / 2), (profondeur / 2), 1.0, 0.0, 0.0};
    this->pCube[5] = {(largeur / 2), (hauteur / 2), (profondeur / 2), 0.0, 1.0, 0.0};
    this->pCube[6] = {(largeur / 2), (hauteur / 2), (-profondeur / 2), 0.0, 0.0, 1.0};
    this->pCube[7] = {(-largeur / 2), (hauteur / 2), (-profondeur / 2), 1.0, 1.0, 1.0};
}
