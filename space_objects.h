#ifndef SPACE_OBJECTS_H_KBOI6R5J
#define SPACE_OBJECTS_H_KBOI6R5J

#include <string>
#include <vector>
#include "cglx.h"
#include "vector_math.h"

class SpaceObject
{
  protected:
	double myRotationAngle;
    double myRotationSpeed;
    double myDistance;
    Vector3 myRotationAxis;
    double mySize;
    string myName;
    Vector3 myOrbitAxis;
    double myOrbitTilt;
    double myRotationTilt;
    double myOrbitAngle;
    double myOrbitSpeed;
    bool myShowOrbit;
    
    SpaceObject *myOrbitCenter;
    vector<SpaceObject*> *mySatellites;
	
  public:
	SpaceObject()
	{
		myRotationAngle = 0;
		myRotationSpeed = 0;
		myDistance = 0;
		mySize = 0;
		myName = "Space Object";
        // myOrbitAxis = NULL;
		myOrbitTilt = 0;
		myRotationTilt = 0;
		myOrbitAngle = 0;
		myOrbitSpeed = 0;
		myShowOrbit = true;
		
		mySatellites = new vector<SpaceObject*>();
//		myOrbitCenter = new SpaceObject();
	}
	
	~SpaceObject()
	{
        delete mySatellites;
	    if (myOrbitCenter) {
            delete myOrbitCenter;
	    }
	}
		
	virtual void setParameters(double rot, double dist, SpaceObject *oCenter, 
	    Vector3 rAxis, double size, string name, Vector3 oAxis, double oTilt, 
	    double rTilt, double oSpeed)
	{
		myRotationSpeed = rot;
		myDistance = dist;
		myOrbitCenter = oCenter;
		myRotationAxis = rAxis;
		mySize = size;
		myName = name;
		myOrbitAxis = oAxis;
		myOrbitTilt = oTilt;
		myRotationTilt = rTilt;
		myOrbitSpeed = oSpeed;
	}
	
	virtual void add(SpaceObject *obj)
	{
		mySatellites->push_back(obj);
	}

	virtual void draw() 
	{	
		if(myShowOrbit)
		{
		    vector<SpaceObject*>::iterator it;
            for(it = mySatellites->begin(); it < mySatellites->end(); it++)
			{
				glPushMatrix();
				(*it)->drawOrbit();
				glPopMatrix();
			}
		}
		
		glPushMatrix();
		transform();
		glRotated(myRotationAngle, myRotationAxis.x, myRotationAxis.y, myRotationAxis.z);
		glutWireSphere(mySize, 20, 20);	//radius, slices, stacks
		glPopMatrix();
		
		vector<SpaceObject*>::iterator it;
	    for(it = mySatellites->begin(); it < mySatellites->end(); it++)
		{
			glPushMatrix();
			(*it)->draw();
			glPopMatrix();
		}
	}
	
	virtual void drawOrbit()
	{
		myOrbitCenter->transform();
		colorOrbit();
		glRotated(myOrbitTilt, myOrbitAxis.x, myOrbitAxis.y, myOrbitAxis.z);
		glTranslated(-myDistance, 0, 0);
		glutWireTorus(myDistance, myDistance, 100, 1);
	}
	
	virtual void transform()
	{
		myOrbitCenter->transform();
		glRotated(myOrbitTilt, myOrbitAxis.x, myOrbitAxis.y, myOrbitAxis.z);
		glRotated(myOrbitAngle, 0, 1, 0);
		glTranslated(myDistance, 0, 0);
		colorObject();
	}
	
	virtual void animate()
	{
		myRotationAngle += myRotationSpeed;
		myOrbitAngle += myOrbitSpeed;
		
	    vector<SpaceObject*>::iterator it;
        for(it = mySatellites->begin(); it < mySatellites->end(); it++)
		{
			(*it)->animate();
		}
	}

	virtual string getName() 
	{
		return myName;
	}

	virtual string getParentName() 
	{
		return myOrbitCenter->getName();
	}

	virtual Vector3 getOrbitAxis() 
	{
		return myOrbitAxis;
	}

	virtual Vector3 getRotationAxis() 
	{
		return myRotationAxis;
	}

	virtual double getRotationSpeed() 
	{
		return myRotationSpeed;
	}
	
	virtual double getRotationAngle()
	{
		return myRotationAngle;
	}

	virtual double getOrbitAngle() 
	{
		return myOrbitAngle;
	}

	virtual void toggleOrbit(bool toggle) 
	{
		myShowOrbit = toggle;
	}

	virtual void colorObject() 
	{
		
	}

	virtual void colorOrbit() 
	{
		glColor3d(255, 255, 255);
	}
};

class Moon : public SpaceObject
{
  public:

    static const Color MOON_COLOR;

	Moon() : SpaceObject()
	{
		
	}
	
    ~Moon() // should automatically call base class' destructor
	{

	}
	
	void colorObject()
	{
		glColor3d(MOON_COLOR.r, MOON_COLOR.g, MOON_COLOR.b);
	}
};

class Planet : public SpaceObject
{
  public:

      static const Color PLANET_COLOR;

    Planet() : SpaceObject()
	{

	}
	
	~Planet()  // should automatically call base class' destructor
	{
	    
	}
	
	void colorObject()
	{
		glColor3d(PLANET_COLOR.r, PLANET_COLOR.g, PLANET_COLOR.b);
	}
};

class Sun : public SpaceObject
{ 
  public:
      
    static const Color SUN_COLOR;
    
	Sun() : SpaceObject()
	{

	}
	
	void drawOrbit()
	{
		//no axis
	}
	
	void transform()
	{
		glRotated(myOrbitTilt, 1, 0, 0);
		glRotated(myOrbitAngle, myOrbitAxis.x, myOrbitAxis.y, myOrbitAxis.z);
		glTranslated(myDistance, 0, 0);
		glColor3d(SUN_COLOR.r, SUN_COLOR.g, SUN_COLOR.b);
	}
	
	void animate()
	{
		myRotationAngle += myRotationSpeed;
		
	    vector<SpaceObject*>::iterator it;
        for(it = mySatellites->begin(); it < mySatellites->end(); it++)
		{
			(*it)->animate();
		}
	}

	string getParentName() 
	{
		return "";
	}
	
	void colorObject()
	{
		glColor3d(SUN_COLOR.r, SUN_COLOR.g, SUN_COLOR.b);
	}
};

const Color Planet::PLANET_COLOR(0.1, 0.1, 1);

const Color Moon::MOON_COLOR(190, 190, 190);

const Color Sun::SUN_COLOR(240, 240, 0);

#endif /* end of include guard: SPACE_OBJECTS_H_KBOI6R5J */