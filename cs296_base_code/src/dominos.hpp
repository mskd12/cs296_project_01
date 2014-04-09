/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

 # include <iostream>
#include "cs296_base.hpp"
using namespace std;
#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_
namespace cs296 
{
	bool fuelContactBool[5] = {false, false, false, false, false};
	bool exhaustContactBool[5] = {false, false, false, false, false};
	class MyContactListener : public b2ContactListener
	{
		public : 
		void EndContact (b2Contact* contact)
		{
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			int* a = (int*)(bodyUserDataA);
			int* b = (int*)(bodyUserDataB);

			for (int i = 0; i < 5; i++) {
				if (a != NULL && b != NULL) {
					if (((*a == 10 + i) && (*b == 60 + i)) || ((*a == 60 + i) && (*b == 10 + i))) {
						fuelContactBool[i] = true;
						//cout<<"fuel   "<<i<<endl;
					}
				}
				if (a != NULL && b != NULL) {
					if (((*a == 30 + i) && (*b == 20 + i)) || ((*a == 20 + i) && (*b == 30 + i))) {
						exhaustContactBool[i] = true;
						//cout<<"exhaust   "<<i<<endl;
					}
				}
			}
		}
	};
			
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
  class dominos_t : public base_sim_t
  {
  public:
    MyContactListener myListener;
    dominos_t();
    
    static base_sim_t* create()
    {
      return new dominos_t;
    }
    const float32 static degtorad = 0.01745329251994f;
    float x;
    float y;
    float angle;

    b2Vec2 transform(b2Vec2 abc)//////////////////  translation is not taken care of
	  {
		  b2Vec2 now;
		  now.x = abc.x*cos(angle)-abc.y*sin(angle)+x;
		  now.y = abc.x*sin(angle)+abc.y*cos(angle)+y;
		  return now;
	  }
    
    void step(settings_t* settings1);
    const int static nBalls = 100;
    b2Body* fuelIntakeRight;
    b2Body* fuelIntakeLeft;
    b2Body* initialCombustibleParticle[5];
    b2Body* ball_array[nBalls][5];
    b2Body* pistonSphere;
    b2Body* fuelPlank[5];
    b2Body* exhaustPlank[5];
    b2RevoluteJoint* fuelPlankJoint[5];
    b2RevoluteJoint* exhaustPlankJoint[5];
    b2Body* fuelControl[5];
    b2Body* fuelRod1[5];
    b2Body* exhaustControl[5];
    b2Body* exhaustRod1[5];
    b2Body* piston[5];
  };
}
  
#endif
