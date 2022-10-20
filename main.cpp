/****************************************************************************************/
/*                     cube.cpp                    */
/****************************************************************************************/
/*         Affiche a l'ecran un cube en 3D         */
/****************************************************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else

#include <GL/glut.h>   /* Pour les autres systemes */

#endif

#include <cstdlib>
#include <iostream>
#include "Tortue.h"
#include "Primitives/Cube.h"

using namespace std;

char presse;
int anglex, angley, x, y, xold, yold;
Tortue *tortues[5] = {new Tortue(0, 0, 0),
                  new Tortue(-2, 0, -2),
                  new Tortue(2, 0, -2),
                  new Tortue(-2, 0, 2),
                  new Tortue(2, 0, 2)};
Cube *cube = new Cube(50,50,50);
double zoom = 2;

void affichage();

void clavier(unsigned char touche, int x, int y);

void reshape(int x, int y);

void idle();

void mouse(int bouton, int etat, int x, int y);

void mousemotion(int x, int y);

int main(int argc, char **argv) {
    /* initialisation de glut et creation
       de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Tortue");

    /* Mise en place de la projection perspective */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);

    /* Initialisation d'OpenGL */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void idle() {
    tortues[0]->IdleAnimation();
    tortues[1]->IdleAnimation();
    tortues[2]->IdleAnimation();
    tortues[3]->IdleAnimation();
    tortues[4]->IdleAnimation();
    glutPostRedisplay();
}

void affichage() {
    int i, j;
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0, zoom,
              0.0, 0.0, 0.0,
              0.0, zoom, 0.0);
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

    tortues[0]->draw();
    tortues[1]->draw();
    tortues[2]->draw();
    tortues[3]->draw();
    tortues[4]->draw();

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(1, 0, 0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 1, 0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 1.0);
    glEnd();

    glFlush();

    cube->draw();

    //On echange les buffers
    glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y) {
    switch (touche) {
        int trucAFaireSauter;
        case 'p': /* affichage du carre plein */
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glutPostRedisplay();
            break;
        case 'f': /* affichage en mode fil de fer */
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutPostRedisplay();
            break;
        case 's' : /* Affichage en mode sommets seuls */
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glutPostRedisplay();
            break;
        case 'd':
            glEnable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'D':
            glDisable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'a'://Les faces à l'envers s'affichent en fil de fer
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_FRONT, GL_LINE);
            glutPostRedisplay();
            break;
        case 'z':
            zoom--;
            cout << zoom << endl;
            glutPostRedisplay();
            break;
        case 'Z':
            zoom++;
            cout << zoom << endl;
            glutPostRedisplay();
            break;
        case ' ':
            trucAFaireSauter = rand()%5;
            tortues[trucAFaireSauter]->posY = 2;
            glutPostRedisplay();
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void reshape(int x, int y) {
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

void mouse(int button, int state, int x, int y) {
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold = y;
    }
    /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse = 0; /* le booleen presse passe a 0 (faux) */

    switch (button) {
        case 3:
            zoom = zoom - 0.05;
            glutPostRedisplay();
            break;
        case 4:
            zoom = zoom + 0.05;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mousemotion(int x, int y) {
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
        anglex = anglex + (x - xold);
        angley = angley + (y - yold);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold = x; /* sauvegarde des valeurs courante de le position de la souris */
    yold = y;
}
