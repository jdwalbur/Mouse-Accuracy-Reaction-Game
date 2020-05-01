#include "graphics.h"
#include "CircleButton.h"
#include "QuadButton.h"
#include <iostream>
#include <vector>
#include <sstream>;
using namespace std;

GLdouble width, height;
int wd;

CircleButton circleButton = CircleButton({0.77,0.77,0.77,1},{250, 250},15, "");
point2D circleCenter;

QuadButton quadButton = QuadButton({0.77,0.77,0.77,1},{100,100},25,25, "");
point2D quadCenter;

int score = 0;
string shapeToSelect = "";

bool running = false;

time_t currentTime;
time_t endTime;




/*
 * if(currentTime == endTime){
 *      running = false;
 * }
 *
 * end time is +60 seconds from the start time
 * the currenttime-endtime should decrease by one every second.
 * ****int displayTime = endTime - currentTime;
 */

//Draws the circleButton at a random position
void drawCircle() {
    srand(time(0));
    circleButton.setColor(0.96,0.69,0.26,1);
    double circleX = (rand() % 450) + 30;
    double circleY = (rand() % 325) + 75;

    circleCenter = {circleX,circleY};

    circleButton.setCenter(circleCenter);
    circleButton.draw();


    glFlush();
}

//Draws the quadButton at a random position and makes sure the center is not over lapping the circleButton
void drawQuad(){
    srand(time(0));
    quadButton.setColor(0.96,0.26,0.88,1);
    double quadX = (rand() % 450) + 30;
    double quadY = (rand() % 325) + 75;

    while(circleButton.isOverlapping(quadX,quadY)){
        quadX = (rand() % 450) + 30;
        quadY = (rand() % 325) + 75;
    }

    quadCenter = {quadX, quadY};

    quadButton.setCenter(quadCenter);
    quadButton.draw();
}


//Randomly selects what shape is the correct one to get picked
void generateSelectShape(){
    srand(time(0));
    int selectType = rand() % 2;
    if(selectType == 0){
        circleButton.setSelect(true);
        quadButton.setSelect(false);
        shapeToSelect = "Click the circles for points!" ;
    } else {
        circleButton.setSelect(false);
        quadButton.setSelect(true);
        shapeToSelect = "Click the square for points!";
    }
}

void game(){
    running = true;
    score = 0;
    endTime = time(NULL) + 60;
    generateSelectShape();
    drawCircle();
    drawQuad();
}

void init() {
    width = 500;
    height = 500;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.77, 0.77, 0.77, 1); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    circleButton.draw();
    quadButton.draw();

    string label = "Score: " + to_string(score);

    glColor3f(0, 0, 0);
    glRasterPos2i(15, 25);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    Quad startRectangle = Quad({0.26,0.96,0.73,1},{250,450},255,50);
    startRectangle.draw();

    string startLabel = "Press Space to Start/Reset game";

    glColor3f(0, 0, 0);
    glRasterPos2i(125, 450);
    for (const char &letter : startLabel) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glColor3f(0, 0, 0);
    glRasterPos2i(125, 50);
    for (const char &letter : shapeToSelect) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    currentTime = time(NULL);
    if(currentTime >= endTime){
        currentTime = time(NULL);
        running = false;
        circleButton.setColor(0.77,0.77,0.77,1);
        quadButton.setColor(0.77,0.77,0.77,1);
    }

    stringstream ss;
    string timerString;
    if(running){
        ss << "Time: " << endTime - currentTime;
        timerString = ss.str();
    } else {
        ss << "Time: " << 0;
        timerString = ss.str();
    }

    glColor3f(0, 0, 0);
    glRasterPos2i(425, 25);
    for (const char &letter : timerString) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
//Space bar will drawn
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    } else if(key == 32){
        game();
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    //If the circle is the shape you want to select then check if the click within the range and highlight it green
    //Vice-versa if the quad is the shape you want to select
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && running) {

        if(circleButton.getSelect()){
            if(circleButton.isOverlapping(x,y)){
                circleButton.pressDown();
                score++;
            }
            else if(quadButton.isOverlapping(x,y)){
                quadButton.pressDown();
                score--;
            }
        }
        else if(quadButton.getSelect()){
            if(circleButton.isOverlapping(x,y)){
                circleButton.pressDown();
                score--;
            }
            else if(quadButton.isOverlapping(x,y)){
                quadButton.pressDown();
                score++;
            }
        }
    }
    //Redraw the shapes so they are in different positions.
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && running){
        drawCircle();
        drawQuad();
    }

    glutPostRedisplay();
}

void timer(int dummy) {
    
    glutPostRedisplay();
    glutTimerFunc(0, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fun with Drawing!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}
