#include "QuadButton.h"
#include "graphics.h"
using namespace std;

QuadButton::QuadButton(color fill, point2D center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {1,0,0};
}

void QuadButton::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

void QuadButton::changeLabel(std::string label) {
    this->label = label;
}

/* Returns true if the coordinate is inside the box */
bool QuadButton::isOverlapping(int x, int y) const {
    point2D bottomLeft {(double)(getLeftX()), (double)getBottomY()};
    point2D topRight {(double)getRightX(), (double)getTopY()};

    if((getLeftX() <= x && getRightX() >= x) && (getTopY() <= y && getBottomY() >= y)){
        return true;
    }
    return false;
}

/* Change color of the box when the user is hovering over it */
void QuadButton::hover() {
    setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void QuadButton::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void QuadButton::release() {
    setColor(originalFill);
}

bool QuadButton::getSelect() {
    return select;
}

void QuadButton::setSelect(bool select) {
    this->select = select;
    if(select){
        pressFill = {0,1,0,1};
    } else {
        pressFill = {1,0,0,1};
    }
}

