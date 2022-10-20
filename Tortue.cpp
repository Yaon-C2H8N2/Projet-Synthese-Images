//
// Created by yaon on 19/10/22.
//

#include "Tortue.h"
#include <GL/glut.h>
#include <cmath>

Tortue::Tortue(double posX, double posY, double posZ) {
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->frameAnim = 0;
}

void Tortue::draw() {
    /*
     * Proto carapace
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+0, posY+0, posZ+0);
    glScalef(0.5, 0.35, 0.6);
    glutSolidSphere(1, 18, 18);
    glPopMatrix();

    /*
     * Proto tête
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+0, posY+0, posZ+0.75);
    glutSolidSphere(0.2, 18, 18);
    glPopMatrix();

    /*
     * Yeux
     */
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(posX+0.13, posY+0.15, posZ+0.83);
    glutSolidSphere(0.03, 9, 9);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(posX+(-0.13), posY+0.15, posZ+0.83);
    glutSolidSphere(0.03, 9, 9);
    glPopMatrix();

    /*
     * Proto patte avant gauche
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+0.5, posY+0, posZ+0.4);
    glTranslatef(-0.15, 0, 0);
    glRotatef(45 * sin(frameAnim), 0, 1, 0);
    glTranslatef(0.15, 0, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.15, 0.15, 0.3);
    glutSolidSphere(1, 18, 18);
    glPopMatrix();

    /*
     * Proto patte avant droite
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+(-0.5), posY+0, posZ+0.4);
    glTranslatef(0.15, 0, 0);
    glRotatef(45 * sin(frameAnim), 0, -1, 0);
    glTranslatef(-0.15, 0, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.15, 0.15, 0.3);
    glutSolidSphere(1, 18, 18);
    glPopMatrix();

    /*
     * Proto patte arrière gauche
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+0.5, posY+0, posZ+(-0.4));
    glTranslatef(-0.15, 0, 0);
    glRotatef(45 * cos(frameAnim), 0, 1, 0);
    glTranslatef(0.15, 0, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.15, 0.15, 0.3);
    glutSolidSphere(1, 18, 18);
    glPopMatrix();

    /*
     * Proto patte arrière droite
     */
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(posX+(-0.5), posY+0, posZ+(-0.4));
    glTranslatef(0.15, 0, 0);
    glRotatef(45 * cos(frameAnim), 0, -1, 0);
    glTranslatef(-0.15, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.15, 0.15, 0.3);
    glutSolidSphere(1, 18, 18);
    glPopMatrix();
}

void Tortue::IdleAnimation() {
    frameAnim += 0.1;
    if(posY>0){
        posY -= 0.0981;
    }
}