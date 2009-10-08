//////////////////////////////////////////////////////////////////
// A basic framework designed for a monitor wall using CGLX.
//
// This file defines methods users are responsible for to animate 
// a scene.
//
// Authors: Robert C. Duvall
//          Todd Berreth
//          Duke University
// Date   : 2009
//////////////////////////////////////////////////////////////////
// Includes
//
#ifndef _THE_SCENE_H_
#define _THE_SCENE_H_
// include here so users do not have to later
#include "cglx.h"


//////////////////////////////////////////////////////////////////
// Class Decalration
//
class Scene
{
  private:
    GLint  myAngle;
    GLuint myNumRows;

  public:
    /*
     * Initialize general OpenGL values once (in place of constructor).
     *
     * This includes, for example, light and texture parameters.
     */
    virtual void init (GLfloat aspectRatio, int argc, char * argv[])
    {
        myNumRows = (argc > 1) ? atoi(argv[1]) : 1;
        myAngle = 0;
    }


    /*
     * Set camera's view of scene.
     */
    virtual void setCamera ()
    {
        gluLookAt(0, 0, 2.5,        // from position
                  0, 0, 0,          // to position
                  0, 1, 0);         // up direction
    }


    /*
     * Display all objects in the scene.
     *
     * Lighting values should generally be set first, before scene objects.
     */
    virtual void display ()
    {
        // make grid of objects to view each spinning
        GLfloat half = (myNumRows - 1) / 2.0;
        for (GLuint r = 0; r < myNumRows; r++)
        {
            for (GLuint c = 0; c < myNumRows; c++)
            {
                GLint dir = ((r + c) % 2) ? -1 : 1;
                glPushMatrix();
                {
                    glColor3f(0, 0.75, 1);
                    glTranslatef((r - half) * 2.0 / myNumRows, (c - half) * 2.0 / myNumRows, 0.0);
                    glRotatef(dir * myAngle, 0.0, 1.0, 0.0);
                    glutSolidCube(0.5 / myNumRows);
                }
                glPopMatrix();
            }
        }
    }


    /*
     * Update scene values to be reflected in next call to display.
     *
     * In this way, small changes to scene will produce smooth animation.
     */
    virtual void update ()
    {
        // animate model by spinning it
        myAngle += 5;
    }


    /*
     * Called when one or more objects have been clicked on by user.
     *
     * selectInfo format for numSelected objects is:
     *   [num names given object], [zfront], [zback], [name_0, name_1, ...]
     */
    void selectObject (GLuint numSelected, GLuint selectInfo[])
    {
        // by default, do nothing
    }


    /*
     * Called when key is pressed.
     *
     * 'key' parameter is ASCII value of the alphanumberic key, if it exists.
     * 'specialKey' is value of key that DOES NOT generate an ASCII value. 
     *     e.g.: F1-F12, Page-up, Page-down Arrow-keys, etc.
     * 'x' and 'y' parameters are current location of mouse
     *    (in window-relative coordinates)
     */
    virtual void keyPressed (unsigned char key, int specialKey, int x, int y)
    {
        // by default, do nothing
    }


    /*
     * Called when mouse moves within window.
     *
     * 'x' and 'y' parameters are current location of mouse
     *    (in window-relative coordinates)
     */
    virtual void mouseMotion (int x, int y)
    {
        // by default, do nothing
    }


    /*
     * Called when mouse moves within window and one of the buttons is pressed.
     *
     * 'x' and 'y' parameters are current location of mouse
     *    (in window-relative coordinates)
     */
    virtual void mouseDrag (int x, int y)
    {
        // by default, do nothing
    }


    /*
     * Called when a mouse button is pressed or released.
     *
     * 'button' parameter is one of:
     *    GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
     * 'state' parameter is one of:
     *    GLUT_DOWN or GLUT_UP, if button was pressed or released
     * 'x' and 'y' parameters are current location of mouse
     *    (in window-relative coordinates)
     */
    virtual void mouseButtonChanged (GLint button, GLint state, GLint x, GLint y)
    {
        // by default, do nothing
    }
};

#endif
