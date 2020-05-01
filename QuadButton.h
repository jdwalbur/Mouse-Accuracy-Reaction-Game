#ifndef GRAPHICS_STARTER_QUADBUTTON_H
#define GRAPHICS_STARTER_QUADBUTTON_H

#include "Quad.h"
#include <string>

class QuadButton : public Quad {
private:
    std::string label;
    color originalFill, hoverFill, pressFill;
    bool select;

public:
    QuadButton(color fill, point2D center, unsigned int width, unsigned int height, std::string label);
    /* Uses OpenGL to draw the box with the label on top */
    void draw() const override;

    void changeLabel(std::string label);

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the Button when the user is hovering over it */
    void hover();

    /* Change color of the Button when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    bool getSelect();

    void setSelect(bool select);
};


#endif //GRAPHICS_STARTER_QUADBUTTON_H