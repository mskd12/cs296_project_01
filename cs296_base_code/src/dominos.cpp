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

//top piston side - 2
//fuel control - 1
//exhaust control - 3
//combustible balls - 5
//normal balls - 4
//fuel intak right - 6


#include "cs296_base.hpp"
#include "render.hpp"
#include <cmath>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  dominos_t::dominos_t()
  {
	  m_world->SetContactListener(&myListener);
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
      
     short category1 = 0x0001;
     short category2 = 0x0002;
     short category3 = 0x0003;
//category 4 and 5 used
     short groundCategory = 0x0006;
     
     short mask1 = -1;
     short mask2 = category1 ;
     short mask3 = category1 ;



     {//pistonSphere	
			b2CircleShape circle;
			circle.m_radius = 5.5;

			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 0.0001f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 1.0f;
			ballfd.filter.groupIndex = -5;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			//ballbd.angularVelocity = -12000.0f;
			ballbd.position=transform(b2Vec2(0, 0));
			pistonSphere = m_world->CreateBody(&ballbd);
			pistonSphere->CreateFixture(&ballfd);

		}
	 //float x,y,angle;

     //groundBody
     //const float degtorad = 0.01745329251994f;
		float x1[5] = {0, 10*cos(18*degtorad), 10*cos(54*degtorad), -10*cos(54*degtorad), -10*cos(18*degtorad)};
		float y1[5] = {10, 10*(sin(18*degtorad)), -10*( sin(54*degtorad)), -10*(sin(54*degtorad)), 10*(sin(18*degtorad))};
		for(int i=0; i<5; i++) {
				x = 0;
				y = 0;
				angle = 72*degtorad*i;
    b2Body* groundBody;
    {
	    b2EdgeShape groundBodyShape; 
	    b2FixtureDef groundBodyFixDef;
	    groundBodyFixDef.filter.categoryBits = groundCategory;
	    groundBodyFixDef.filter.maskBits = 0;
	    groundBodyFixDef.filter.groupIndex = -5;
	    groundBodyShape.Set(transform(b2Vec2(-0.1f, 100.0f)), transform(b2Vec2(0.1f, 100.0f)));
	    //groundBodyShape.angle = angle;
	    b2BodyDef bd; 
	    groundBody = m_world->CreateBody(&bd); 
	    groundBody->CreateFixture(&groundBodyShape, 0.0f);
	}
	    

   {//left piston side
    	b2Body* b1;
		b2PolygonShape bodyPoly;
		b2BodyDef bd;
		bodyPoly.SetAsBox(1.0f, 10.5f );
		b2FixtureDef fd;
			
		fd.filter.categoryBits = category1;
		fd.filter.maskBits = mask1;
		fd.shape = &bodyPoly;
		fd.restitution = 0.8f;
		fd.friction = 2.0;
		bd.angle=angle;
		bd.position=(transform(b2Vec2(-9,40)));
		b1 = m_world->CreateBody(&bd);
		b1->CreateFixture(&fd);
    }
    {//right piston side
    	b2Body* b1;
		b2PolygonShape bodyPoly;
		b2BodyDef bd;
		bodyPoly.SetAsBox(1.0f, 10.5f );
		b2FixtureDef fd;
		
		fd.filter.categoryBits = category1;
		fd.filter.maskBits = mask1;
		fd.shape = &bodyPoly;
		fd.restitution = 0.8f;
		fd.friction = 2.0;
		bd.angle=angle;
		bd.position=(transform(b2Vec2(9.0f,40)));
		b1 = m_world->CreateBody(&bd);
		b1->CreateFixture(&fd);
    }
    {//top piston side
		  b2Vec2 vertices[3];
		  vertices[0].Set(-8+2*sqrt(2), -2);
		  vertices[1].Set(-5, 0);
		  vertices[2].Set(5,  0);
		  vertices[3].Set(8-2*sqrt(2), -2);
		  
		  b2PolygonShape polygonShape;
		  polygonShape.Set(vertices, 4); //pass array to the shape
		  
		  b2FixtureDef myFixtureDef;
		  myFixtureDef.filter.groupIndex = -1;
		  myFixtureDef.filter.categoryBits = category1;
		  myFixtureDef.filter.maskBits = mask1;
		  b2BodyDef myBodyDef;
		  myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		  myFixtureDef.friction = 2.0;
		  myFixtureDef.restitution = 1.0;
		  myBodyDef.angle=angle;
		  myBodyDef.position=(transform(b2Vec2(0,55))); //in the middle
		  //myBodyDef.type=b2_dynamicBody;
		  b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);
		  dynamicBody1->SetUserData(new int(20 + i));
		  dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body

    }
    ///////////////
    {//Fuel control(have added the control rod )
		   b2Vec2 vertices[3];
		  vertices[0].Set(0.0f, -2.0f);
		  vertices[1].Set(2.8f, -3.7f);
		  vertices[2].Set(-2.8f, -3.7f);
		  b2PolygonShape shape;
		  shape.Set(vertices, 3); //pass array to the shape

		  b2PolygonShape shape2;
		  shape2.SetAsBox(0.3f, 2.1f);
		  b2FixtureDef *fd = new b2FixtureDef;
		  fd->shape = new b2PolygonShape;
		  fd->shape = &shape;
		  fd->density = 0.1f;
		  fd->restitution = 0.2f;
		  fd->friction = 1.0f;
		  fd->filter.categoryBits = category1;
		  fd->filter.maskBits = mask1;


		  b2BodyDef bd2;
		  bd2.position=transform(b2Vec2(8.0f, 53.0f));
		  bd2.angle = -45 * degtorad+angle;
		  bd2.type = b2_dynamicBody;
		  fuelControl[i] = m_world->CreateBody(&bd2);
		  b2FixtureDef *fd2 = new b2FixtureDef;
		  fd2->density = 0.1f;
		  fd2->shape = new b2PolygonShape;
		  fd2->shape = &shape2;
		  fd2->filter.categoryBits = category1;
		  fd2->filter.maskBits = mask1;
		  fuelControl[i]->CreateFixture(fd2);
		  fuelControl[i]->CreateFixture(fd);
		  fuelControl[i]->SetUserData(new int(10 + i));

		  b2PrismaticJointDef prismaticJointDef;
		  b2Vec2 v;
		  v.Set(cos(45*degtorad+angle),sin(45*degtorad+angle));
		  prismaticJointDef.Initialize(fuelControl[i], groundBody, fuelControl[i]->GetWorldCenter(), v);
		  m_world->CreateJoint(&prismaticJointDef);
		  
	////////////////////////
	    //Fuel Control Rod right
    {
		b2PolygonShape fuelRod1Poly;
		b2BodyDef fuelRod1Def;
		fuelRod1Poly.SetAsBox(4, 0.6f);
		b2FixtureDef fuelRod1FixDef;

		fuelRod1FixDef.filter.categoryBits = 0x0003;
		fuelRod1FixDef.filter.maskBits = 0x0001;
		fuelRod1FixDef.filter.groupIndex = -11;
		fuelRod1FixDef.shape = & fuelRod1Poly;
		fuelRod1FixDef.density = 10.0f;
		fuelRod1FixDef.restitution = 1.0f;
		fuelRod1Def.position=transform(b2Vec2(7, 57));
		fuelRod1Def.type = b2_dynamicBody;
		fuelRod1Def.angle = -35 * degtorad+angle;
		fuelRod1[i] = m_world->CreateBody(&fuelRod1Def);
		fuelRod1[i]->CreateFixture(&fuelRod1FixDef);
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = fuelRod1[i];
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(0,0); 
		revolutejd->localAnchorB = fuelRod1[i]->GetWorldCenter();
		
		
		m_world->CreateJoint(revolutejd);
		
		
	}
	b2Vec2 var1 = transform(b2Vec2(8.0f, 53.0f));
	b2Vec2 var2 = transform(b2Vec2(7,57));
	b2DistanceJointDef distancejoint;
	b2Vec2 anchor1, anchor2;
	anchor1.Set(var1.x-2.1 *sin(-45* degtorad+angle),var1.y+2.1*cos(-45* degtorad+angle));
	anchor2.Set(var2.x+4*cos(-35* degtorad+angle), var2.y+4*sin(-35 * degtorad+angle) );
	distancejoint.Initialize(fuelControl[i], fuelRod1[i], anchor1, anchor2);
	distancejoint.collideConnected = false;;
	m_world->CreateJoint(&distancejoint);	  
	}
	

	{//Exhaust control(have added the control rod )
		   b2Vec2 vertices[3];
		  vertices[0].Set(0.0f, -2.0f);
		  vertices[1].Set(-2.8f, -3.7f);
		  vertices[2].Set(2.8f, -3.7f);
		  b2PolygonShape shape;
		  shape.Set(vertices, 3); //pass array to the shape

		  b2PolygonShape shape2;
		  shape2.SetAsBox(0.3f, 2.1f);
		  b2FixtureDef *fd = new b2FixtureDef;
		  fd->shape = new b2PolygonShape;
		  fd->shape = &shape;
		  fd->density = 0.1f;
		  fd->friction = 1.0f;
		  fd->filter.categoryBits = category1;
		  fd->filter.maskBits = mask1;

		  b2BodyDef bd2;
		  bd2.position=transform(b2Vec2(-8.0f, 53.0f));
		  bd2.angle = 45 * degtorad+angle;
		  bd2.type = b2_dynamicBody;
		  exhaustControl[i] = m_world->CreateBody(&bd2);
		  b2FixtureDef *fd2 = new b2FixtureDef;
		  fd2->density = 0.1f;
		  fd2->shape = new b2PolygonShape;
		  fd2->shape = &shape2;
		  fd2->filter.categoryBits = category1;
		  fd2->filter.maskBits = mask1;
		  exhaustControl[i]->CreateFixture(fd2);
		  exhaustControl[i]->CreateFixture(fd);
		  exhaustControl[i]->SetUserData(new int(30 + i));

		  b2PrismaticJointDef prismaticJointDef;
		  b2Vec2 v;
		  v.Set(cos(135*degtorad+angle),sin(135*degtorad+angle));
		  prismaticJointDef.Initialize(exhaustControl[i], groundBody, exhaustControl[i]->GetWorldCenter(), v);
		  m_world->CreateJoint(&prismaticJointDef);
		  
	////////////////////////
	    //Exhaust Control Rod left
    {
		b2PolygonShape exhaustRod1Poly;
		b2BodyDef exhaustRod1Def;
		exhaustRod1Poly.SetAsBox(4, 0.6f);
		b2FixtureDef exhaustRod1FixDef;

		exhaustRod1FixDef.filter.categoryBits = category2;
		exhaustRod1FixDef.filter.maskBits = mask2 | category2;
		exhaustRod1FixDef.filter.groupIndex = -11;
		exhaustRod1FixDef.shape = & exhaustRod1Poly;
		exhaustRod1FixDef.density = 10.0f;
		exhaustRod1FixDef.restitution = 1.0f;
		exhaustRod1Def.position=transform(b2Vec2(-7, 57));
		exhaustRod1Def.type = b2_dynamicBody;
		exhaustRod1Def.angle = 35 * degtorad+angle;
		exhaustRod1[i] = m_world->CreateBody(&exhaustRod1Def);
		exhaustRod1[i]->CreateFixture(&exhaustRod1FixDef);
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = exhaustRod1[i];
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(0,0); 
		revolutejd->localAnchorB = exhaustRod1[i]->GetWorldCenter();
		
		
		m_world->CreateJoint(revolutejd);
		
		
	}	  
	b2Vec2 var1 = transform(b2Vec2(-8.0f, 53.0f));
	b2Vec2 var2 = transform(b2Vec2(-7,57));
	b2DistanceJointDef distancejoint;
	b2Vec2 anchor1, anchor2;
	anchor1.Set(var1.x-2.1*sin(45* degtorad+angle),var1.y+2.1*cos(45* degtorad+angle));
	anchor2.Set(var2.x-4*cos(35* degtorad+angle), var2.y-4*sin(35 * degtorad+angle) );
	distancejoint.Initialize(exhaustControl[i], exhaustRod1[i], anchor1, anchor2);
	m_world->CreateJoint(&distancejoint);
	}
		//planks in middle


	{//fuel part
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(2.5, 0.1);
        b2FixtureDef myFixtureDef;
	    b2BodyDef myBodyDef;		

		myBodyDef.type=b2_dynamicBody;
		myBodyDef.angle = (50 - 36*i)*degtorad+angle;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.restitution = 0.1;
		myFixtureDef.filter.categoryBits = category3;
		myFixtureDef.filter.maskBits = mask3;
		myFixtureDef.filter.groupIndex = -1;
		myBodyDef.position=transform(b2Vec2(2.5,59));
		//myBodyDef.angularVelocity  = -1000000.0f;
		fuelPlank[i] = m_world->CreateBody(&myBodyDef);
		fuelPlank[i]->CreateFixture(&myFixtureDef); 
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyB = fuelPlank[i];
		revolutejd->bodyA = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorB.Set(-2.5,0); 
		revolutejd->localAnchorA=(transform(b2Vec2(0,59)));
		revolutejd->enableMotor = true;
		revolutejd->motorSpeed = 2;
		revolutejd->maxMotorTorque = 10000;
		fuelPlankJoint[i] = (b2RevoluteJoint*)m_world->CreateJoint(revolutejd);
	}
	{//exhaust part
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(2.5, 0.1);
		b2FixtureDef myFixtureDef;
	        b2BodyDef myBodyDef;
		

		myBodyDef.type=b2_dynamicBody;
		myBodyDef.angle = (200 + 36*i)*degtorad+angle;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.restitution = 0.1;
		myFixtureDef.filter.categoryBits = category2;
		myFixtureDef.filter.maskBits = mask2 | category2;
		myFixtureDef.filter.groupIndex = -1;
		myBodyDef.position=transform(b2Vec2(2.5,59)); 
		exhaustPlank[i] = m_world->CreateBody(&myBodyDef);
		exhaustPlank[i]->CreateFixture(&myFixtureDef);


		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = exhaustPlank[i];
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(-2.5,0); 
		revolutejd->localAnchorB=transform(b2Vec2(0,59));
		revolutejd->enableMotor = true;
		revolutejd->motorSpeed = 2;
		revolutejd->maxMotorTorque = 10000;
		exhaustPlankJoint[i] = (b2RevoluteJoint*)m_world->CreateJoint(revolutejd);
	}
	
		{//testing with small balls
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(8, 0.1);
		b2FixtureDef myFixtureDef;
		b2BodyDef myBodyDef;
		myBodyDef.angle = 50*degtorad+angle;
		myFixtureDef.shape = &polygonShape; 
		myFixtureDef.density = 100;
		myFixtureDef.restitution = 1;
		myFixtureDef.filter.categoryBits = 0x0004;
		myFixtureDef.filter.maskBits = 0x0005;
		myBodyDef.position=transform(b2Vec2(10.5f,58.5f));
		fuelIntakeLeft = m_world->CreateBody(&myBodyDef);
		fuelIntakeLeft->CreateFixture(&myFixtureDef); //add a fixture to the body


		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(8, 0.1);
		b2FixtureDef myFixtureDef1;
		b2BodyDef myBodyDef1;
		//myBodyDef1.type=b2_dynamicBody;
		myBodyDef1.angle = 40*degtorad+angle;
		myFixtureDef1.shape = &polygonShape1; //change the shape of the fixture
		myFixtureDef1.density = 100;
		myFixtureDef1.restitution = 1;
		myFixtureDef1.filter.categoryBits = 0x0004;
		myFixtureDef1.filter.maskBits = 0x0005;
		//myFixtureDef.filter.groupIndex = -1;
		myBodyDef1.position=transform(b2Vec2(13.5f,55.5f));
		fuelIntakeRight = m_world->CreateBody(&myBodyDef1);
		fuelIntakeRight->CreateFixture(&myFixtureDef1); //add a fixture to the body
		fuelIntakeRight->SetUserData(new int(60 + i));
		{
		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(5, 0.1);
			//polygonShape.Set(vertices, 5); //pass array to the shape

		b2FixtureDef myFixtureDef1;
		b2BodyDef myBodyDef1;
		//myBodyDef1.type=b2_dynamicBody;
		myBodyDef1.angle = 135*degtorad+angle;
		//myBodyDef.linearVelocity.Set(0,5);
		myFixtureDef1.shape = &polygonShape1; //change the shape of the fixture
		myFixtureDef1.density = 100;
		myFixtureDef1.restitution = 0.1;
		myFixtureDef1.filter.categoryBits = 0x0004;
		myFixtureDef1.filter.maskBits = 0x0005;
		//myFixtureDef.filter.groupIndex = -1;
		myBodyDef1.position=transform(b2Vec2(14,62));
		b2Body* Body1 = m_world->CreateBody(&myBodyDef1);
		Body1->CreateFixture(&myFixtureDef1); //add a fixture to the body
		}

		{	
		b2CircleShape circle;
		circle.m_radius = 0.2f;

		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 0.0000007f;
		ballfd.friction = 0.0f;
		ballfd.filter.categoryBits = 0x0004;
		ballfd.filter.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0005;
		ballfd.restitution = 1.0f;
		
		for (int j = 0; j < nBalls; ++j)
		{
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position=transform(b2Vec2((rand() % 2) + 12.0f , (rand() % 2) + 57.0f));
			ballbd.linearVelocity.Set((rand() % 10) - 5.0f, (rand() % 10) - 5.0f);
			ball_array[j][i] = m_world->CreateBody(&ballbd);
			ball_array[j][i]->SetUserData(new int(40 + i));
			ball_array[j][i]->CreateFixture(&ballfd);
		}
			ballfd.density = 0.00028f;
			b2BodyDef ballbd;
			//ballbd.type = b2_dynamicBody;
			ballbd.position=transform(b2Vec2(0,50));
			//ballbd.linearVelocity.Set((rand() % 10) - 5.0f , (rand() % 10) - 5.0f);
			initialCombustibleParticle[i] = m_world->CreateBody(&ballbd);
			initialCombustibleParticle[i]->SetUserData(new int(50 + i));
			initialCombustibleParticle[i]->CreateFixture(&ballfd);
		
	}
}

b2Joint* sphereGndJoint;
	
	{
		{
			b2Vec2 vertices[4];
		  vertices[0].Set(-7.9f, -2.5f);
		  vertices[1].Set(7.9f, -2.5f);
		  vertices[2].Set(6,2.5);
		  vertices[3].Set(-6,2.5);
		  b2PolygonShape shape;
		  shape.Set(vertices, 4);

			b2FixtureDef myFixtureDef1;
			b2BodyDef myBodyDef1;
			myBodyDef1.type=b2_dynamicBody;
			//myBodyDef1.angle = 135*degtorad;
			myBodyDef1.linearVelocity.Set(0,-50);
			myFixtureDef1.shape = &shape; //change the shape of the fixture
			myFixtureDef1.density = 0.0001;
			myFixtureDef1.restitution = 0.8;
			myFixtureDef1.filter.categoryBits = 0x0004;
			myFixtureDef1.filter.groupIndex = -5;
			myBodyDef1.angle = angle;
			myBodyDef1.position=transform(b2Vec2(0,38));
			piston[i] = m_world->CreateBody(&myBodyDef1);
			piston[i]->CreateFixture(&myFixtureDef1); //add a fixture to the body
		}
		b2Body* pistonRod;
		{
			b2PolygonShape polygonShape1;
			polygonShape1.SetAsBox(1, sqrt(1469/4.0f));

			b2FixtureDef myFixtureDef1;
			b2BodyDef myBodyDef1;
			myBodyDef1.type=b2_dynamicBody;
			myBodyDef1.angle = - atan(5/38.0f) + angle;
			//myBodyDef.linearVelocity.Set(0,5);
			myFixtureDef1.shape = &polygonShape1; //change the shape of the fixture
			myFixtureDef1.density = 0.0001;
			myFixtureDef1.restitution = 1;
			//myFixtureDef1.filter.categoryBits = 0x0004;
			//myFixtureDef1.filter.maskBits = 0x0005;
			myFixtureDef1.filter.groupIndex = -5;
			myBodyDef1.position=transform(b2Vec2(-2.5f,19));
			pistonRod = m_world->CreateBody(&myBodyDef1);
			pistonRod->CreateFixture(&myFixtureDef1); //add a fixture to the body
		}
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = piston[i];
		revolutejd->bodyB = pistonRod;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(0,0); 
		revolutejd->localAnchorB.Set(0,sqrt(1469/4.0f));
		//revolutejd->collideConnected = false;
		m_world->CreateJoint(revolutejd);

		
		b2RevoluteJointDef* jointRodSphereDef = new b2RevoluteJointDef();
		jointRodSphereDef->bodyA = pistonSphere;
		jointRodSphereDef->bodyB = pistonRod;
		jointRodSphereDef->collideConnected = false;
		jointRodSphereDef->localAnchorA.Set(-5,0); 
		jointRodSphereDef->localAnchorB.Set(0,-sqrt(1469/4.0f));
		//jointRodSphereDef->collideConnected = false;
		m_world->CreateJoint(jointRodSphereDef);

		b2RevoluteJointDef* jointGndSphereDef = new b2RevoluteJointDef();
		jointGndSphereDef->bodyB = pistonSphere;
		jointGndSphereDef->bodyA = groundBody;
		jointGndSphereDef->collideConnected = false;
		jointGndSphereDef->localAnchorB.Set(0,0); 
		jointGndSphereDef->localAnchorA = pistonSphere->GetWorldCenter();
		//jointGndSphereDef->collideConnected = false;
		sphereGndJoint = m_world->CreateJoint(jointGndSphereDef);

		b2PrismaticJointDef prismaticJointDef;
 		b2Vec2 v;
		v.Set(cos(90*degtorad+angle),sin(90*degtorad+angle));
		prismaticJointDef.Initialize(piston[i], groundBody, piston[i]->GetWorldCenter(), v);
		m_world->CreateJoint(&prismaticJointDef);

	}
}//for loop
	

}
sim_t *sim = new sim_t("Dominos", dominos_t::create);


void dominos_t::step(settings_t* settings){
		base_sim_t::step(settings);
		
		
	
	//fuel and exhaust control
	
	for (int i = 0; i < 5; i++) {

		//set ball postions
		/*for(int j = 0; j < nBalls and ball_array[j][i] != NULL; j++) {
			b2Vec2 pos = ball_array[j][i]->GetPosition();
			b2Vec2 pistonPos = piston[i]->GetPosition();
			b2Vec2 var1 = transform(b2Vec2(-100,100));
		
			//below piston or on the +ve x side......
			if(cos(angle)*pos.y-sin(angle)*pos.x-x > var1.y ||cos(angle)*pos.x+sin(angle)*pos.y-y < var1.x) {
				ball_array[j][i]->SetTransform(transform(b2Vec2((rand() % 2) + 12.0f, (rand() % 2) + 57.0f)), 0);
				ball_array[j][i]->SetLinearVelocity(transform(b2Vec2(((rand() % 10) - 5.0f) / 2.0f , ((rand() % 10) - 5.0f) / 2.0f)));
				ball_array[j][i]->GetFixtureList()->SetDensity( 0.0000007f);
				ball_array[j][i]->SetUserData(new int(40 + i));
				//ball_array[j][i]->GetFixtureList()->GetShape()->m_radius = 0.4f;
			}

			if (cos(angle)*pos.y-sin(angle)*pos.x < cos(angle)*pistonPos.y-sin(angle)*pistonPos.x) {
				ball_array[j][i]->SetTransform(transform(b2Vec2((rand() % 2) + 12.0f, (rand() % 2) + 57.0f)), 0);
				ball_array[j][i]->SetLinearVelocity(transform(b2Vec2(((rand() % 10) - 5.0f) / 2.0f , ((rand() % 10) - 5.0f) / 2.0f)));
				ball_array[j][i]->GetFixtureList()->SetDensity( 0.0000007f);
				ball_array[j][i]->SetUserData(new int(40 + i));
			}

			/*b2Vec2 newPos = b2Vec2(cos(45*degtorad - angle)*pos.x+sin(45*degtorad - angle)*pos.y, cos(45*degtorad - angle)*pos.y-sin(45*degtorad - angle)*pos.x);
			b2Vec2 leftSidePos = fuelIntakeLeft->GetPosition();
			b2Vec2 newLeftSidePos = b2Vec2(cos(- angle + 45*degtorad)*leftSidePos.x+sin(- angle + 45*degtorad)*leftSidePos.y, cos(- angle + 45*degtorad)*leftSidePos.y-sin(- angle + 45*degtorad)*leftSidePos.x);
			b2Vec2 rightSidePos = fuelIntakeRight->GetPosition();
			b2Vec2 newRightSidePos = b2Vec2(cos(- angle + 45*degtorad)*rightSidePos.x+sin(- angle + 45*degtorad)*rightSidePos.y, cos(- angle + 45*degtorad)*rightSidePos.y-sin(- angle + 45*degtorad)*rightSidePos.x);
			
		//cout<<rightSidePos.y<<endl;

			if (newPos.x > newLeftSidePos.x && newPos.x < newRightSidePos.x && abs(newPos.y - newLeftSidePos.y) < 8) {
				ball_array[j][i]->GetFixtureList()->SetDensity( 0.0000007f);
				ball_array[j][i]->SetUserData(new int(40 + i));
			}

			//combustible collisions
			b2ContactEdge* contactEdge = ball_array[j][i]->GetContactList();
			while(contactEdge != NULL) {
				b2Body* bodyA = contactEdge->contact->GetFixtureA()->GetBody();
				b2Body* bodyB = contactEdge->contact->GetFixtureB()->GetBody();
				void* bodyUserDataA = bodyA->GetUserData();
				void* bodyUserDataB = bodyB->GetUserData();
				int* a = (int*)(bodyUserDataA);
				int* b = (int*)(bodyUserDataB);
				if (a != NULL && b != NULL && *a == 40 + i && *b == 50 + i) {
					bodyA->GetFixtureList()->SetDensity(0.0007f);
					bodyA->SetUserData(new int(50 + i));
					//bodyA->GetFixtureList()->GetShape()->m_radius = 0.2f;

				}
				if (a != NULL && b != NULL && *a == 50 + i && *b == 40 + i) {
					bodyB->GetFixtureList()->SetDensity(0.00007f);
					bodyB->SetUserData(new int(50 + i));
					//bodyB->GetFixtureList()->GetShape()->m_radius = 0.2f;
				}
				contactEdge = contactEdge->next;
			}
		//inside fuel intake pipe, no combustible
		}*/





		for (int j = 0; j < nBalls; j++) {
			if (ball_array[j][i] != NULL) {
				////////////////////////////////////////////
				b2Vec2 pos = ball_array[j][i]->GetPosition();
				///////////////////////////////////////////////
			
			
				//b2Vec2 pos = ball_array[j][i]->GetPosition();
				float ball_rad = sqrt(pos.x * pos.x + pos.y * pos.y);
				if (ball_rad > 70 || ball_rad < 35) {
					angle = 72*degtorad*i;
					x = 0;
					y = 0;
					ball_array[j][i]->SetTransform(transform(b2Vec2((rand() % 2) + 12.0f, (rand() % 2) + 57.0f)), 0);
					ball_array[j][i]->SetLinearVelocity(b2Vec2((rand() % 5)-2.5f, (rand() % 5) - 2.5f));
					ball_array[j][i]->GetFixtureList()->SetDensity( 0.0000007f);
					ball_array[j][i]->SetUserData(new int(40 + i));
				}



					b2ContactEdge* contactEdge = ball_array[j][i]->GetContactList();
					while(contactEdge != NULL) {
						b2Body* bodyA = contactEdge->contact->GetFixtureA()->GetBody();
						b2Body* bodyB = contactEdge->contact->GetFixtureB()->GetBody();
						void* bodyUserDataA = bodyA->GetUserData();
						void* bodyUserDataB = bodyB->GetUserData();
						int* a = (int*)(bodyUserDataA);
						int* b = (int*)(bodyUserDataB);
						if (a != NULL && b != NULL && *a == 40 + i && *b == 50 + i) {
							bodyA->GetFixtureList()->SetDensity(0.00028f);
							bodyA->SetUserData(new int(50 + i));
							//bodyA->GetFixtureList()->GetShape()->m_radius = 0.2f;

						}
						if (a != NULL && b != NULL && *a == 50 + i && *b == 40 + i) {
							bodyB->GetFixtureList()->SetDensity(0.00028f);
							bodyB->SetUserData(new int(50 + i));
							//bodyB->GetFixtureList()->GetShape()->m_radius = 0.2f;
						}
						contactEdge = contactEdge->next;
					}
				}
			}







		if (fuelPlankJoint[i] != NULL){
			fuelPlankJoint[i]->SetMotorSpeed(0.5f * pistonSphere->GetAngularVelocity());
		}
		if (exhaustPlankJoint[i] != NULL){
			exhaustPlankJoint[i]->SetMotorSpeed(0.5f * pistonSphere->GetAngularVelocity());
		}
		if (fuelContactBool[i]){
			fuelControl[i]->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			fuelRod1[i]->SetAngularVelocity(0.0f);
			fuelContactBool[i] = false;
		}
		
		if (exhaustContactBool[i]){
			exhaustControl[i]->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			exhaustRod1[i]->SetAngularVelocity(0.0f);
			exhaustContactBool[i] = false;
		}
	}
}

}

   
