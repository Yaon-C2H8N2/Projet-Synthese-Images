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
#include <cmath>
#include "Tortue.h"
#include <jpeglib.h>
#include <jerror.h>

using namespace std;
//
char presse;
int anglex, angley, x, y, xold, yold;
/*
 * Dimensions de l'image contenant la texture
 */
const unsigned int largimg = 300, hautimg = 168;
unsigned char image[largimg * hautimg * 3];
/*
 * Initialisation des tortues apparaissants dans la scène
 */
Tortue *tortues[5] = {new Tortue(0, 0, 0),
                      new Tortue(-2, 0, -2),
                      new Tortue(2, 0, -2),
                      new Tortue(-2, 0, 2),
                      new Tortue(2, 0, 2)};
double zoom = 2;

void affichage();

void clavierTouchesSpeciales(int touche, int x, int y);

void clavier(unsigned char touche, int x, int y);

void reshape(int x, int y);

void idle();

void mouse(int bouton, int etat, int x, int y);

void mousemotion(int x, int y);

void gestionLumiere();

void loadJpegImage(char *fichier);

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

    /* Parametrage du placage de textures */
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largimg, hautimg, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image);
    glEnable(GL_TEXTURE_2D);*/

    /* Initialisation d'OpenGL */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(clavierTouchesSpeciales);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

/*
 * Fonction appelée pour l'animation passive
 */
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

    /*
     * Affichage des tortues
     */
    tortues[0]->draw();
    tortues[1]->draw();
    tortues[2]->draw();
    tortues[3]->draw();
    tortues[4]->draw();

    /*
     * Affichage des lumières
     */
    gestionLumiere();

    glFlush();

    /*
     * Cube sur lequel appliquer la texture de fond marin
     */
    glutSolidCube(50);

    //On echange les buffers
    glutSwapBuffers();
}

/*
 * Fonctions des touches pour tourner la caméra
 */
void clavierTouchesSpeciales(int touche, int x, int y) {
    switch (touche) {
        case GLUT_KEY_LEFT:
            anglex = anglex - 1;
            if (anglex < 0) anglex = 360;
            break;
        case GLUT_KEY_RIGHT:
            anglex = anglex + 1;
            if (anglex > 360) anglex = 0;
            break;
        case GLUT_KEY_DOWN:
            angley = angley + 1;
            if (angley > 360) angley = 0;
            break;
        case GLUT_KEY_UP:
            angley = angley - 1;
            if (angley < 0) angley = 360;
            break;
    }
    glutPostRedisplay();
}

/*
 * Fonctions des touches alphanumériques
 */
double frameAnimTouche = 0;

void clavier(unsigned char touche, int x, int y) {
    switch (touche) {
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
            glutPostRedisplay();
            break;
        case 'Z':
            zoom++;
            glutPostRedisplay();
            break;
        case ' ':
            /*
             * Animation de nage
             */
            frameAnimTouche += 0.1;
            for (auto i: tortues) {
                i->posY = sin(frameAnimTouche) / 2;
            }
            if (frameAnimTouche > 2 * M_PI)frameAnimTouche = 0;
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)presse = 0; /* le booleen presse passe a 0 (faux) */

    /*
     * switch pour le zoom à la souris en plus du zoom au clavier
     */
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

void gestionLumiere() {
    /*
     * Lumière générale de la scène
     * Ambiance bleutée pour les fonds marins
     */
    GLfloat position_source0[] = {10.0, 10.0, 10.0, 0.0};
    GLfloat dif_0[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat amb_0[] = {0.4, 0.4, 1, 1.0};
    GLfloat spec_0[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, position_source0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_0);

    /*
     * Réflexion fond marin, bleu foncé.
     * Lumière en spot afin d'atteindre une cible restreinte.
     * Se voit particulièrement bien dans les yeux de la bête.
     */
    GLfloat position_source1[] = {0.0, -1.0, 0.0, 0.0};
    GLfloat dir[] = {0.0, 1.0, 0.0};
    GLfloat dif_1[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat spec_1[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT1, GL_POSITION, position_source1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec_1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 4.0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}

void loadJpegImage(char *fichier) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
#ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
      {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
      }
#elif __GNUC__
    if ((file = fopen(fichier, "rb")) == 0) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
#endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if ((cinfo.image_width != largimg) || (cinfo.image_height != hautimg)) {
        fprintf(stdout, "Erreur : l'image doit etre de taille %dx%d\n", largimg, hautimg);
        exit(1);
    }
    if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
        fprintf(stdout, "Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne = image;
    while (cinfo.output_scanline < cinfo.output_height) {
        ligne = image + 3 * hautimg * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}