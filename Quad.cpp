#include "Quad.h"
#include "graphics.h"

Quad::Quad() {
    fill = {1, 0, 0,1};
    center = {100, 100};
    width = 50;
    height = 50;
}

Quad::Quad(color fill, point2D center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}


unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::draw() const {
    // Set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
// glVertex2i takes a 2-D (x, y) coordinate
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());
    glEnd();
}