//////////////////////////////////////////////////////////////////
// A basic framework designed for a monitor wall using CGLX.
//
// This is the main file that sets up basic OpenGL defaults to
// make it easier for others to develop application code without
// dealing with these specifics.
//
// Authors: Robert C. Duvall
//          Todd Berreth
//          Duke University
// Date   : 2009
//////////////////////////////////////////////////////////////////
// Includes
//
#include <cstdio>            // for sprintf
#include <cstring>           // for strlen
#include <cstdlib>           // for exit
#include <sys/time.h>        // gettimeofday
#include <iostream>
#include "cglx.h"            // for CGLX or GLUT
using namespace std;
#include "scene.h"


//////////////////////////////////////////////////////////////////
// Globals
//
// Variables
//
char *       theProgramTitle;
int          theWindowWidth = 960, theWindowHeight = 200;
int          theWindowPositionX = 100, theWindowPositionY = 100;
bool         isAnimating = true;
bool         isFullScreen = false;
unsigned int currentTime;
Scene *      theScene = new Scene();

// Constants
//
const unsigned int ANIMATION_DELAY = 40;    // milliseconds between rendering
const float        NEAR_DISTANCE = 0.1;     // near plane distance
const float        FAR_DISTANCE = 500;      // far plane distance
const float        FOV_ANGLE = 45;          // angle of field of view


//////////////////////////////////////////////////////////////////
//  Utility functions
//
/*
 * Returns the current time in milliseconds.
 */
unsigned int timeGetTime ()
{
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}


/*
 * Computes frames per second and display in window's title bar
 */
void computeFPS ()
{
    static int frameCount = 0;
    static int lastFrameTime = 0;
    static char * title = new char[strlen(theProgramTitle) + 20];

    frameCount++;
    int currentFrameTime = timeGetTime();
    if (currentFrameTime - lastFrameTime > 1000)
    {
        sprintf(title, "%s [ FPS: %4.2f ]",
                theProgramTitle,
                frameCount * 1000.0 / (currentFrameTime - lastFrameTime));
        lastFrameTime = currentTime;
        frameCount = 0;
#ifndef DEF_USE_CGLX
        glutSetWindowTitle(title);
#endif
    }
}


/*
 * Reset perspective matrix based on size of viewport.
 */
void setPerspective (GLenum mode, int x = 0, int y = 0)
{
    // get info about viewport (x, y, w, h)
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // set camera to view viewport area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // check for selection
    if (mode == GL_SELECT)
    {
        // create 5x5 pixel picking region near cursor location
        gluPickMatrix(GLfloat(x), GLfloat(viewport[3] - y), 5.0, 5.0, viewport);
    }
    // view scene in perspective
#ifdef DEF_USE_CGLX
    cglx::gluPerspective(FOV_ANGLE, GLdouble(viewport[2]) / GLdouble(viewport[3]), 
                         NEAR_DISTANCE, FAR_DISTANCE);
#else 
    gluPerspective(FOV_ANGLE, GLdouble(viewport[2]) / GLdouble(viewport[3]), 
                   NEAR_DISTANCE, FAR_DISTANCE);
#endif
    // prepare to work with model again
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Determine which objects have been selected by pressing the mouse
 */
void selectObject (int x, int y)
{
    // allocate enough space to store select info
    GLuint selectBuf[512];
    glSelectBuffer(512, selectBuf);

    // prepare for selection by initializing name info (0 represents a miss)
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);

    // render to select buffer instead of color buffer
    glPushMatrix();
      setPerspective(GL_SELECT, x, y);
      theScene->setCamera();
      theScene->display();
    glPopMatrix();

    // if object hit, react
    GLuint numHits = glRenderMode(GL_RENDER);
    if (numHits > 0)
    {
        theScene->selectObject(numHits, selectBuf);
    }
    // reset camera for viewing
    setPerspective(GL_RENDER);
}


/*
 * Called when OpenGL detects an error while displaying scene.
 *
 * The last error is given as errorCode. Valid error codes are: 
 *  GL_INVALID_ENUM, GL_INVALID_VALUE, GL_INVALID_OPERATION,
 *  GL_STACK_OVERFLOW, GL_STACK_UNDERFLOW, and GL_OUT_OF_MEMORY.
 */
void reportError (GLenum errorCode)
{
    // BUGBUG: must be a better way to do this
    while (errorCode != GL_NO_ERROR)
    {
        cerr << "***ERROR***" << errorCode << endl;
        errorCode = glGetError();
    }
}


//////////////////////////////////////////////////////////////////
// Callback Functions
// These functions are registered with the glut window and called 
// when certain events occur.
//
/*
 * Inits OpenGL and scene (now that context has been correctly set).
 */
void onInit (int argc, char * argv[])
{
    // by default the back ground color is black
    glClearColor(0, 0, 0, 0.0);
    // set to draw in window based on depth 
    glEnable(GL_DEPTH_TEST);

    // get info about viewport (x, y, w, h)
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    // init scene with aspect ratio and command-line args
    theScene->init((float)viewport[2] / (float)viewport[3], argc, argv);
}


/*
 * Updates and re-renders scene based on users code, maintaining
 * constant framework if possible.
 */
void onIdle ()
{
    static int oldTime = 0;

    if (isAnimating)
    {
        currentTime = timeGetTime();
        if ((currentTime - oldTime) > ANIMATION_DELAY)
        {
            // animate the scene
            theScene->update();
            // compute the frame rate
            oldTime = currentTime;
       	    computeFPS();
        }
        // notify window it has to be repainted
        glutPostRedisplay();
    }
}


/*
 * Displays contents of scene when window needs to be refreshed.
 */
void onDisplay ()
{
    // clears requested bits (color and depth) in glut window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw entire scene into cleared window
    glPushMatrix();
      theScene->setCamera();
      theScene->display();
    glPopMatrix();

    // check for any errors when rendering
    GLenum errorCode = glGetError();
    if (errorCode == GL_NO_ERROR)
    {
        // double-buffering - swap back and front buffers
        glFlush();
        glutSwapBuffers();
    }
    else
    {
        reportError(errorCode);
    }
}


/*
 * Allow scene to respond to key presses.
 */
void onAlphaNumericKeyPress (unsigned char key, int x, int y) 
{
    switch (key)
    {
      // toggle animation running
      case 'p':
        isAnimating = ! isAnimating;
        break;

      // step animation to next frame
      case 's':
        theScene->update();
        break;

      // quit!
      case 'Q':
      case 'q':
      case 27:   // ESC
        exit(0);
	;

      // respond to other keys
      default:
        theScene->keyPressed(key, 0, x, y);
    }

    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Allow scene to respond to special key presses (function and arrow keys).
 */
void onSpecialKeyPress (int key, int x, int y) 
{
    switch (key)
    {
      // toggle full screen mode
      case GLUT_KEY_F1:
        isFullScreen = ! isFullScreen;
        if (isFullScreen)
        {
            glutFullScreen();
        }
        else                
        {
            glutReshapeWindow(theWindowWidth, theWindowHeight);
            glutPositionWindow(theWindowPositionX, theWindowPositionY);
        }
        break;

      // respond to other keys
      default:
        theScene->keyPressed(0, key, x, y);
    }

    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Allow scene to respond to when mouse is moved.
 */
void onMouseMotion (int x, int y)
{
    // scene response
    theScene->mouseMotion(x, y);
    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Allow scene to respond to when mouse is moved while button is pressed.
 */
void onMouseDrag (int x, int y)
{
    // scene response
    theScene->mouseDrag(x, y);
    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Allow scene to respond to when mouse button is pressed.
 */
void onMouseButtonChanged (int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
       selectObject(x, y);
    }

    // scene response
    theScene->mouseButtonChanged(button, state, x, y);
    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Reset camera location and aspect to match window update.
 */
void onReshape (int width, int height)
{
    glViewport(0, 0, width, height);
    if (! isFullScreen)
    {
        theWindowWidth = width;
        theWindowHeight = height;
    }

    // set camera to view resized area
    setPerspective(GL_RENDER);
    // notify window that it has to be re-rendered
    glutPostRedisplay();
}


/*
 * Only update scene if window is visible, otherwise don't bother
 */
void onVisible (int state)
{
    if (state == GLUT_VISIBLE)
    {
        // tell glut to animate model again
        glutIdleFunc(onIdle);
    }
    else
    {
        glutIdleFunc(NULL);
    }
}


//////////////////////////////////////////////////////////////////
// Main Function
//
int main (int argc, char *argv[]) 
{
    theProgramTitle = argv[0];

    // initialize glut
    glutInit(&argc, argv);      
    // request initial window size and position on the screen
    glutInitWindowSize(theWindowWidth, theWindowHeight);
    glutInitWindowPosition(theWindowPositionX, theWindowPositionY);
    // request full color with double buffering and depth-based rendering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    // create window whose title is the name of the executable
    glutCreateWindow(theProgramTitle);

    // tell glut how to display model
    glutDisplayFunc(onDisplay);
    // tell glut what to do when it would otherwise be idle
    glutIdleFunc(onIdle);
    // tell glut how to respond to changes in window size
    glutReshapeFunc(onReshape);
    // tell glut how to handle changes in window visibility
    // if you iconify the window, stops rendering
    glutVisibilityFunc(onVisible);
    // tell glut how to handle key presses
    glutKeyboardFunc(onAlphaNumericKeyPress);
    glutSpecialFunc(onSpecialKeyPress);
    // tell glut how to handle the mouse
    glutMotionFunc(onMouseDrag);
    glutPassiveMotionFunc(onMouseMotion);
    glutMouseFunc(onMouseButtonChanged);

    // initialize model
    onInit(argc, argv);

    // give control over to glut to handle rendering and interaction
    glutMainLoop();

    // program should never get here
    return 0;
}
