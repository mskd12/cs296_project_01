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
	bool fuelContactBool = false;
	bool exhaustContactBool = false;
	class MyContactListener : public b2ContactListener
	{
		public : 
		void EndContact (b2Contact* contact)
		{
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			int* a = (int*)(bodyUserDataA);
			int* b = (int*)(bodyUserDataB);
			if (a != NULL && b != NULL) {
				if (((*a == 1) && (*b == 2)) || ((*a == 2) && (*b == 1))) {
					fuelContactBool = true;
				}
			}
			if (a != NULL && b != NULL) {
				if (((*a == 3) && (*b == 2)) || ((*a == 2) && (*b == 3))) {
					exhaustContactBool = true;
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
    
    void step(settings_t* settings1);
    const int static nBalls = 100;
    b2Body* ball_array[nBalls];
    b2Body* pistonSphere;
    b2Body* fuelPlank;
    b2Body* exhaustPlank;
    b2RevoluteJoint* fuelPlankJoint;
    b2RevoluteJoint* exhaustPlankJoint;
    b2Body* fuelControl;
    b2Body* fuelRod1;
    b2Body* exhaustControl;
    b2Body* exhaustRod1;
  };
}
  
#endif
