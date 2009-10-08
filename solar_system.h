#include "cglx.h"
#include <vector>
#include <string>
#include <ifstream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include "space_objects.h"
#include "vector_math.h"

using namespace std;

class SolarSystem
{
  private:
    vector<SpaceObject*> *myObjects;
	
	void add(SpaceObject *obj)
	{
		for(int k = 0; k<myObjects->size(); k++)
		{
			if((*myObjects)[k]->getName().compare(obj->getParentName()) == 0)
			{
				(*myObjects)[k]->add(obj);
			}
		}
	}
	
	SpaceObject get(string name)
	{
		for(int k = 0; k<myObjects->size(); k++)
		{
			if((*myObjects)[k]->getName().compare(name) == 0)
				return *(*myObjects)[k];
		}
	}
	
  public:
	SolarSystem()
	{
		myObjects = new vector<SpaceObject*>();
		try 
		{
			ifstream myScanner;
			myScanner.open("SolarSystem.txt");
			while(!myScanner.eof())
			{
				string line;
				getline(myScanner, line);
				
				if(line[0] == '*')
				{}
				else 
				{
					stringstream ss(line);
					vector<string> tokens = split(ss, ';');
					stringstream ss2(tokens[5]);
					stringstream ss3(tokens[7]);
					vector<string> rAxisString = split(ss2, ' ');
					vector<string> oAxisString = split(ss3, ' ');
					
					double rot = atof(tokens[2].c_str());
					double dist = atof(tokens[3].c_str());
					SpaceObject oCenter = get(tokens[4]);
					Vector3 *rAxis = new Vector3(atof(rAxisString[0].c_str()), atof(rAxisString[1].c_str()), atof(rAxisString[2].c_str()));
					double size = atof(tokens[6].c_str());
					string name = tokens[1];
					Vector3 *oAxis = new Vector3(atof(oAxisString[0].c_str()), atof(oAxisString[1].c_str()), atof(oAxisString[2].c_str()));
					double oTilt = atof(tokens[8].c_str());
					double rTilt = atof(tokens[9].c_str());
					double oSpeed = atof(tokens[10].c_str());
					
					if(tokens[0].compare("Sun") == 0)
					{
						Sun *obj = new Sun();
						obj->setParameters(rot, dist, oCenter, rAxis, size, name, oAxis, oTilt, rTilt, oSpeed);
						myObjects->insert(obj);
						if(name.compare("none"))
						{
							add(obj);
						}
					}
					else if(tokens[0].compare("Planet") == 0)
					{
						Planet *obj = new Planet();
						obj->setParameters(rot, dist, oCenter, rAxis, size, name, oAxis, oTilt, rTilt, oSpeed);
						myObjects->insert(obj);
						if(name.compare("none"))
						{
							add(obj);
						}
					}
					else 
					{
						Moon *obj = new Moon();
						obj->setParameters(rot, dist, oCenter, rAxis, size, name, oAxis, oTilt, rTilt, oSpeed);
						myObjects->insert(obj);
						if(name.compare("none"))
						{
							add(obj);
						}
					}

				}
				
			}
			
		}
		catch (char* str) 
		{
			cout << "BLAH" << endl;
		}
	}
	
	void draw()
	{
		(*myObjects)[0]->draw();
	}
	
	void animate()
	{
		(*myObjects)[0]->animate();
	}
	
	void toggleOrbit(bool toggle)
	{
		for(int k = 0; k<myObjects->size(); k++)
		{
			(*myObjects)[k]->toggleOrbit(toggle);
		}
	}
	
	~SolarSystem()
	{
		for(int k = 0; k<myObjects->size(); k++)
		{
			delete (*myObjects)[k];
		}
		delete myObjects;
	}
	
	vector<string> split (istream& input, char delimiter)
	{
		vector<string> tokens;
		string item;
		while(getline(input, item, delimiter)) {
			tokens.push_back(item);
		}
		return tokens;
	}
};