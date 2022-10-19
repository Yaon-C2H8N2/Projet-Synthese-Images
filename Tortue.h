//
// Created by yaon on 19/10/22.
//

#ifndef PROJET_SYNTHESE_IMAGES_TORTUE_H
#define PROJET_SYNTHESE_IMAGES_TORTUE_H


class Tortue {
public:
    double posX, posY, posZ;
    double frameAnim;

    Tortue(double posX, double posY, double posZ);

    void draw();

    void IdleAnimation();
};


#endif //PROJET_SYNTHESE_IMAGES_TORTUE_H
