#ifndef CONFETTIFY_QUAD_H
#define CONFETTIFY_QUAD_H

#include "shape.h"

class Quad : public Shape{
protected:
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(color fill, point2D center, unsigned int width, unsigned int height);

    int getRightX() const;
    int getLeftX() const;
    int getTopY() const;
    int getBottomY() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void draw() const override;
};

#endif //CONFETTIFY_QUAD_H