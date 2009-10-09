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
#include "solar_system.h"
#include "vector_math.h"

//////////////////////////////////////////////////////////////////
// Class Decalration
//
class Scene
{
  private:
    SolarSystem *mySolarSystem;
    Point3 *myCamFrom;
    Point3 *myCamTo;
    Point3 *myCamUp;
    
    void setDefaultCamera() {
		myCamFrom->set(DEFAULT_CAMERA_FROM);
        myCamTo->set(DEFAULT_CAMERA_TO);
        myCamUp->set(DEFAULT_CAMERA_UP);
	}

    Vector3 getViewDir() {
    	Vector3 viewDir = Vector3();
    	viewDir.sub(*myCamFrom, *myCamTo);
    	viewDir.normalize();
    	return viewDir;
    }

  public:
    static const Point3 DEFAULT_CAMERA_FROM;
    static const Point3 DEFAULT_CAMERA_TO;
    static const Point3 DEFAULT_CAMERA_UP;
      
    /*
     * Initialize general OpenGL values once (in place of constructor).
     *
     * This includes, for example, light and texture parameters.
     */
    virtual void init (GLfloat aspectRatio, int argc, char * argv[])
    {
        mySolarSystem = new SolarSystem();
        
        myCamFrom = new Point3();
        myCamTo = new Point3();
        myCamUp = new Point3();
        
        setDefaultCamera();
    }


    /*
     * Set camera's view of scene.
     */
    virtual void setCamera ()
    {
        gluLookAt(myCamFrom->x, myCamFrom->y, myCamFrom->z,        // from position
                  myCamTo->x, myCamTo->y, myCamTo->z,          // to position
                  myCamUp->x, myCamUp->y, myCamUp->z);         // up direction
    }


    /*
     * Display all objects in the scene.
     *
     * Lighting values should generally be set first, before scene objects.
     */
    virtual void display ()
    {
        mySolarSystem->draw();
    }


    /*
     * Update scene values to be reflected in next call to display.
     *
     * In this way, small changes to scene will produce smooth animation.
     */
    virtual void update ()
    {
        mySolarSystem->animate();
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
        Vector3 viewDir = getViewDir();
    	Vector3 upDir;
        upDir.set(*myCamUp);
    	upDir.normalize();
    	
    	Vector3 rightDir;
    	rightDir.cross(viewDir, upDir);
    	rightDir.normalize();
    	
        switch (key) 
        {
		    case 'i': // Zoom In
		    	myCamFrom->sub(viewDir);
		    	break;
		    case 'o': // Zoom out;
		    	myCamFrom->add(viewDir);
		    	break;
            case 'h':
                // TODO: hide orbits
            	mySolarSystem->toggleOrbit(false);
                break;
            case 'j':
                // TODO: show orbits
            	mySolarSystem->toggleOrbit(true);
                break;
            case 'r':
            {
                // TODO: restart simulation
            	setDefaultCamera();
                SolarSystem *toDelete = mySolarSystem;
            	mySolarSystem = new SolarSystem();
                delete toDelete; // To prevent memory leak from restarting solar system
            	break;
            }
            // Reset camera view
            case 'c':
            	setDefaultCamera();
            	break;
        }
        
        switch (specialKey)
        {
            // Camera movement: Current implementation rotates around the spot.
            // case KeyEvent.VK_LEFT:
            //  myCamTo->add(rightDir);
            //  break;
            // case KeyEvent.VK_RIGHT:
            //  myCamTo->sub(rightDir);
            //  break;
            // case KeyEvent.VK_UP:
            //  myCamTo->add(upDir);
            //  break;
            // case KeyEvent.VK_DOWN:
            //  myCamTo->sub(upDir);
            //  break;
        }
        
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

const Point3 Scene::DEFAULT_CAMERA_FROM(65, 13, 3);
const Point3 Scene::DEFAULT_CAMERA_TO(0, 0, 0);
const Point3 Scene::DEFAULT_CAMERA_UP(0, 1, 0);

#endif
