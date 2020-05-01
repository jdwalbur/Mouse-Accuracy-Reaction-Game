#ifndef GRAPHICS_STARTER_CIRCLEBUTTON_H
#define GRAPHICS_STARTER_CIRCLEBUTTON_H

#include "circle.h"
#include <string>

class CircleButton : public Circle {
private:
    std::string label;
    color originalFill, hoverFill, pressFill;
    //True if it is the correct target, Flase if it is otherwise
    bool select;

public:
    CircleButton(color fill, point2D center, unsigned int radius, std::string label);

    CircleButton(color fill, point2D center, unsigned int radius, std::string label, bool select);

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


#endif //GRAPHICS_STARTER_CIRCLEBUTTON_H