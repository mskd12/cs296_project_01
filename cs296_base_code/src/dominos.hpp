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
	
	 //!This class can be used to change the attributes of any body when it collides with some other 
	class MyContactListener : public b2ContactListener
	{
		public :  
		/*!
		 * This gets executed after every step on every pair of bodies that are colliding in the same step
		 */ 
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
  //! This is an instance of MyContactListener class
    MyContactListener myListener;
    //!Constructor for dominos_t class
    dominos_t();
    
    static base_sim_t* create()
    {
      return new dominos_t;
    }
    const float32 static degtorad = 0.01745329251994f;
    float x;
    float y;
    float angle;
	/*!
	 * \li abc is a b2Vec2 variable that is undergoing transformation
	 * \li The transform function defined gives the transformed coordinates of abc.x and abc.y when rotated by an angle
	 */ 
    b2Vec2 transform(b2Vec2 abc)//////////////////  translation is not taken care of
	  {
		  b2Vec2 now;
		  now.x = abc.x*cos(angle)-abc.y*sin(angle)+x;
		  now.y = abc.x*sin(angle)+abc.y*cos(angle)+y;
		  return now;
	  }
    /*!
     * In this function, we evaluate certain numbers at the end of each step and make the appropriate changes
     * \li For every ball, we compute its position after the step is executed and check whether if it is in the pre-defined boundary
     * \li If its not, we re-spawn them in the fuel chamber of the engine from to which it actually belongs and make it non-combustible
     * \li We check for every ball if it is colliding with the initialCombustibleParticle 
     * \li If it is, then we change the ball from non-combustible to combustible(which basically is changing the density in this case)
     */ 
    void step(settings_t* settings1);
    /*!
     * Number of balls(fuel particles) in each engine
     */ 
    const int static nBalls = 100;
   
    b2Body* wall_top;
    /*!
     * \li This is a rod that acts as a bridge between piston and pistonSphere 
     */
    b2Body* pistonRod;
     /*!
     * \li wall_left along with wall_top and wall_right comprises the boundary of the combustion chamber
     * \li The space that is formed by the three walls is where the actual combustion and expansion of the gases haappen that makes the engine run
     */ 
    b2Body* wall_left;
    b2Body* wall_right;
    b2Body* fuelIntakeRight;
    /*!
     * \li The fuel chamber has to be guarded by some walls and that job is done by fuelIntakeLeft and fuelIntakeRight
     */ 
    b2Body* fuelIntakeLeft;
    /*!
     * \li This is a particle in the combustion chamber that we kept as stationary
     * \li When other balls collide with this particle, then they turn into combustible particles
     */ 
    b2Body* initialCombustibleParticle[5];
    /*!
     * \li The fuel in the engine is simulated using particles of small size which are by non combustible when created
     * \li These balls when ignited gain a lot of energy and push the piston down
     * \li This linear motion of the piston is then transformed to circular by "piston sphere"
     * \li Once the particles are going out of the pre-defined bounds, we re-spawn them back in the fuel chamber
     */
    b2Body* ball_array[nBalls][5];
    /*!
     * \li Piston sphere is the body that is connected to piston and the piston rod
     * \li This enables the <b> transformation </b> of the <b> rectilinear </b> motion of piston to <b> circular </b> motion of the wheels
     */
  
    b2Body* pistonSphere;
    /*!
     * \li fuelplank is a revolving body that rotates about one of its ends 
     * \li This has a pre-defined motor speed and can apply some torque when nit by any other body
     * \li  Using the above we made the fuelplank to collide with fuelRod that inturn moves fuelControl which allows the particles to move from fuel chamber to combustion chamber
     */ 
    b2Body* fuelPlank[5];
    /*!
     * \li This is similar to fuelplank, the only difference being that this collides with the exhaustRod rather than fuelRod
     */ 
    b2Body* exhaustPlank[5];
    /*!
     * \li The fuelPlankJoint is a revolute joint between the fuelPlank and ground
     */ 
    b2RevoluteJoint* fuelPlankJoint[5];
    /*!
     * \li The exhaustPlankJoint is a revolute joint between the exhaustPlank and ground
     */ 
    b2RevoluteJoint* exhaustPlankJoint[5];
    /*!
     * This acts a reference for the engine
     * Most of the revolute joints defined have one of the body as groundBody
     */ 
    b2Body* groundBody[5];
    /*!
     * \li The triangle shaped body attached with a rod in the upper left of the combustion chamber that controls the fuel input to the combustion chamber is fuelControl
     * \li The movement of the body is restricted due to its  Prismatic joint  and distance joint with ground and fuelRod1 respectively
     */ 
 
    b2Body* fuelControl[5];
    /*!
     * \li fuelRod1 is the rod that is colliding with fuelPlank and because of the distance joint between fuelRod1 and fuelControl, it inturn is responsible for the movement of fuelControl
     * \li It has a distance joint with fuelControl and a revolute joint with the ground abouut its centre
     */ 
    b2Body* fuelRod1[5];
    /*!
     * \li This is the counter part of fuelControl
     * \li It lies in the upper left of the combustion chamber and controls the exhaust
     */ 
    b2Body* exhaustControl[5];
    /*! It is the counter part of fuelRod1 at the exhaust
     */ 
    b2Body* exhaustRod1[5];
    /*!
     * \li piston is one of the important parts in the combustion chamber 
     * \li The particles (fuel) collide with the piston and create a circular motion of the wheels through pistonSphere
     */ 
    b2Body* piston[5];
  };
}
  
#endif
