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


#include "cs296_base.hpp"
#include "render.hpp"

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
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
      
     short category1 = 0x0001;
     short category2 = 0x0002;
     short category3 = 0x0003;
     
     short mask1 = -1;
     short mask2 = category1 ;
     short mask3 = category1 ;
//     {
//       b2Body* b1;
//       b2EdgeShape shape; 
//       shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
//       b2BodyDef bd; 
//       b1 = m_world->CreateBody(&bd); 
//       b1->CreateFixture(&shape, 0.0f);
//     }
    
//     {
// 		b2Body* body;
// 		b2BodyDef bodyDef;
// 		b2PolygonShape bodyPoly;
// 		b2FixtureDef bodyFix;

// 		//Setting up Vertices in an Array   
// 		b2Vec2 ver1 ( 0, 0);
// 		b2Vec2 ver2 ( 5, 2.5);
// 		b2Vec2 ver3 ( 45, 2.5);
// 		b2Vec2 ver4 ( 50, 0);

// 		//Push in order
// 		b2Vec2 vertexArray[] = {ver1, ver2, ver3, ver4};

// 		//bodyDef.type = b2_dynamicBody;
// 		//b2Vec2 Array then Vertex Count
// 		bodyPoly.Set(vertexArray, 4);
// 		bodyFix.shape = &bodyPoly;
// 		bodyFix.density = 0.5;
// 		bodyFix.friction = 0.5;
// 		bodyFix.restitution = 1.0;
// 		bodyDef.position.Set(-25, 0);
// 		body = m_world->CreateBody(&bodyDef);
// 		body->CreateFixture(&bodyFix);
    
// 	}
	
// 	{
// 		b2Body* body;
// 		b2BodyDef bodyDef;
// 		b2PolygonShape bodyPoly;
// 		b2FixtureDef bodyFix;

// 		//Setting up Vertices in an Array   
// 		b2Vec2 ver1 ( 0, 0);
// 		b2Vec2 ver2 ( 5, 2.5);
// 		b2Vec2 ver3 ( 5, 50);
// 		b2Vec2 ver4 ( 0, 50);

// 		//Push in order
// 		b2Vec2 vertexArray[] = {ver1, ver2, ver3, ver4};

// 		//bodyDef.type = b2_dynamicBody;
// 		//b2Vec2 Array then Vertex Count
// 		bodyPoly.Set(vertexArray, 4);
// 		bodyFix.shape = &bodyPoly;
// 		bodyFix.density = 0.5;
// 		bodyFix.friction = 0.5;
// 		bodyFix.restitution = 1.0;
// 		bodyDef.position.Set(-25, 0);
// 		body = m_world->CreateBody(&bodyDef);
// 		body->CreateFixture(&bodyFix);
    
// 	}
// 	{
// 		b2Body* body;
// 		b2BodyDef bodyDef;
// 		b2PolygonShape bodyPoly;
// 		b2FixtureDef bodyFix;

// 		//Setting up Vertices in an Array   
// 		b2Vec2 ver1 ( 45, 50);
// 		b2Vec2 ver2 ( 50, 50);
// 		b2Vec2 ver3 ( 45, 2.5);
// 		b2Vec2 ver4 ( 50, 0);

// 		//Push in order
// 		b2Vec2 vertexArray[] = {ver1, ver2, ver4, ver3};

// 		//bodyDef.type = b2_dynamicBody;
// 		//b2Vec2 Array then Vertex Count
// 		bodyPoly.Set(vertexArray, 4);
// 		bodyFix.shape = &bodyPoly;
// 		bodyFix.density = 0.5;
// 		bodyFix.friction = 0.5;
// 		bodyFix.restitution = 1.0;
// 		bodyDef.position.Set(-25, 0);
// 		body = m_world->CreateBody(&bodyDef);
// 		body->CreateFixture(&bodyFix);
    
// 	}

// {
// 		/*! \subsection a11 Train of spheres
// 		 *  Here the train of small spheres is created.
// 		 * \li variable \b "circle" defines the shape of the sphere,every sphere has the same shape.
// 		 * \li varible \b "ballfd" defines the fixture of the sphere.
// 		 * \li varible \b "ballbd" defines the body of a particular sphere.
// 		 */
//       b2Body* spherebody;
	
//       b2CircleShape circle;
//       circle.m_radius = 0.5;
	
//       b2FixtureDef ballfd;
//       ballfd.shape = &circle;
//       ballfd.density = 0.1f;
//       ballfd.friction = 0.0f;
//       ballfd.restitution = 2.0f;
	
//       for (int i = 0; i < 10; ++i)
// 	{
// 	  b2BodyDef ballbd;
// 	  ballbd.type = b2_dynamicBody;
// 	  ballbd.position.Set((rand() % 40) - 20.0f , (rand() % 20) + 10.0f);
// 	  ballbd.linearVelocity.Set((rand() % 40) - 20.0f , (rand() % 20) - 10.0f);
// 	  spherebody = m_world->CreateBody(&ballbd);
// 	  spherebody->CreateFixture(&ballfd);
// 	}
//     }

     //groundBody
     const float degtorad = 0.01745329251994f;

    b2Body* groundBody;
    {
		b2EdgeShape groundBodyShape; 
	    groundBodyShape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	    b2BodyDef bd; 
	    groundBody = m_world->CreateBody(&bd); 
	    groundBody->CreateFixture(&groundBodyShape, 0.0f);
	}
	    

    {//left piston side
    	b2Body* b1;
		b2PolygonShape bodyPoly;
		b2BodyDef bd;
		bodyPoly.SetAsBox(2.0f, 10.0f );
		b2FixtureDef fd;
			
		fd.filter.categoryBits = category1;
		fd.filter.maskBits = mask1;
		fd.shape = &bodyPoly;
		fd.restitution = 1.0;
		fd.friction = 2.0;
		bd.position.Set(-10.0f, 10.0f);
		b1 = m_world->CreateBody(&bd);
		b1->CreateFixture(&fd);
    }

    {//right piston side
    	b2Body* b1;
		b2PolygonShape bodyPoly;
		b2BodyDef bd;
		bodyPoly.SetAsBox(2.0f, 10.0f );
		b2FixtureDef fd;
		
		fd.filter.categoryBits = category1;
		fd.filter.maskBits = mask1;
		fd.shape = &bodyPoly;
		fd.restitution = 1.0;
		bd.position.Set(10.0f, 10.0f);
		b1 = m_world->CreateBody(&bd);
		b1->CreateFixture(&fd);
    }

    {//top piston side
		  b2Vec2 vertices[3];
		  vertices[0].Set(-8+2*sqrt(2), -2);
		  vertices[1].Set(-5, 1);
		  vertices[2].Set(5,  1);
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
		  myBodyDef.position.Set(0 ,25); //in the middle
		  //myBodyDef.type=b2_dynamicBody;
		  b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);
		  dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body

    }

    /*{//the fuel blocker triangle
		b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape bodyPoly;
		b2FixtureDef bodyFix;

		//Setting up Vertices in an Array   
		b2Vec2 ver1 ( 0, 0);
		b2Vec2 ver2 ( 5, 2.5);
		b2Vec2 ver3 ( 5, 50);

		//Push in order
		b2Vec2 vertexArray[] = {ver1, ver2, ver3, ver4};

		bodyDef.type = b2_dynamicBody;
		//b2Vec2 Array then Vertex Count
		bodyPoly.Set(vertexArray, 4);
		bodyFix.shape = &bodyPoly;
		bodyFix.density = 10;
		bodyFix.friction = 0.5;
		bodyFix.restitution = 2.0;
		body = m_world->CreateBody(&bodyDef);
		body->CreateFixture(&bodyFix);
    
	}*/
	{//Fuel control
		  b2Vec2 vertices[5];
		  vertices[0].Set(7/sqrt(2),  7/sqrt(2));
		  vertices[1].Set(0.2*sqrt(2), 2.2*sqrt(2));
		  vertices[2].Set(-2,-2);//(7/sqrt(2)) + sqrt(2),  sqrt(2) - 7/sqrt(2));
		  vertices[3].Set(-1,-3); //(7/sqrt(2))- sqrt(2), (-7/sqrt(2))-sqrt(2));
		  vertices[4].Set(2*sqrt(2), 0);
		  
		  //right line :- -3,23 -13,30
		  b2PolygonShape polygonShape;
		  //polygonShape.SetAsBox(7, 2);
		  polygonShape.Set(vertices, 5); //pass array to the shape
		  
		  b2FixtureDef myFixtureDef;
		  b2BodyDef myBodyDef;
		  //myBodyDef.angle = -45*degtorad;
		  myBodyDef.type=b2_dynamicBody;
		  myFixtureDef.filter.categoryBits = category1;
		  myFixtureDef.filter.maskBits = mask1;
		  myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		  myFixtureDef.density = 0.05f;
		  myFixtureDef.friction = 1000.0f;
		  myBodyDef.position.Set(8 - 2*sqrt(2),23 - 2*sqrt(2)); //in the middle
		  b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		  dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body

		  b2PrismaticJointDef prismaticJointDef;
		  b2Vec2 v;
		  v.Set(1, 1);
		  prismaticJointDef.Initialize(dynamicBody2, groundBody, dynamicBody2->GetWorldCenter(), v);
		  m_world->CreateJoint(&prismaticJointDef);
		  
	////////////////////////
	    //Fuel Control Rod left
	b2Body* fuelRod1;
    {
		b2PolygonShape fuelRod1Poly;
		b2BodyDef fuelRod1Def;
		fuelRod1Poly.SetAsBox(5, 0.6f);
		b2FixtureDef fuelRod1FixDef;

		fuelRod1FixDef.filter.categoryBits = category3;
		fuelRod1FixDef.filter.maskBits = mask3;
		fuelRod1FixDef.shape = & fuelRod1Poly;
		fuelRod1FixDef.density = 1.0f;
		fuelRod1FixDef.restitution = 1.0f;
		fuelRod1Def.position.Set(7, 29);
		fuelRod1Def.type = b2_dynamicBody;
		fuelRod1Def.angle = -30 * degtorad;
		fuelRod1 = m_world->CreateBody(&fuelRod1Def);
		fuelRod1->CreateFixture(&fuelRod1FixDef);
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = fuelRod1;
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(0,0); 
		revolutejd->localAnchorB = fuelRod1->GetWorldCenter();
		
		
		m_world->CreateJoint(revolutejd);
		
		
	}	  

	b2DistanceJointDef distancejoint;
	b2Vec2 anchor1, anchor2;
	anchor1.Set(-(-8+ 2*sqrt(2)-6*cos(45* degtorad)),23- 2*sqrt(2)+6*sin(45* degtorad));
	anchor2.Set(-(-7-5*cos(30* degtorad)), 29-5*sin(30 * degtorad) );
	distancejoint.Initialize(dynamicBody2, fuelRod1, anchor1, anchor2);
	m_world->CreateJoint(&distancejoint);
	}


	
	{//Exhaust control(have added the control rod )
		  b2Vec2 vertices[5];
		  vertices[0].Set(-7/sqrt(2),  7/sqrt(2));
		  vertices[1].Set(-0.2*sqrt(2), 2.2*sqrt(2));
		  vertices[2].Set(2,-2);//(7/sqrt(2)) + sqrt(2),  sqrt(2) - 7/sqrt(2));
		  vertices[3].Set(1,-3); //(7/sqrt(2))- sqrt(2), (-7/sqrt(2))-sqrt(2));
		  vertices[4].Set(-2*sqrt(2), 0);
		  
		  //right line :- -3,23 -13,30
		  b2PolygonShape polygonShape;
		  //polygonShape.SetAsBox(7, 2);
		  polygonShape.Set(vertices, 5); //pass array to the shape
		  
		  b2FixtureDef myFixtureDef;
		  b2BodyDef myBodyDef;
		  
		  //myBodyDef.angle = -45*degtorad;
		  myBodyDef.type=b2_dynamicBody;
		  myFixtureDef.filter.categoryBits = category1;
		  myFixtureDef.filter.maskBits = mask1;
		  myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		  myFixtureDef.density = 0.05f;
		  myFixtureDef.friction = 1000.0f;
		  myBodyDef.position.Set(-8 + 2*sqrt(2),23 - 2*sqrt(2)); //in the middle
		  b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		  dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body

		  b2PrismaticJointDef prismaticJointDef;
		  b2Vec2 v;
		  v.Set(1, -1);
		  prismaticJointDef.Initialize(dynamicBody2, groundBody, dynamicBody2->GetWorldCenter(), v);
		  m_world->CreateJoint(&prismaticJointDef);
		  
	////////////////////////
	    //Fuel Control Rod left
	b2Body* fuelRod1;
    {
		b2PolygonShape fuelRod1Poly;
		b2BodyDef fuelRod1Def;
		fuelRod1Poly.SetAsBox(5, 0.6f);
		b2FixtureDef fuelRod1FixDef;

		fuelRod1FixDef.filter.categoryBits = category2;
		fuelRod1FixDef.filter.maskBits = mask2;
		fuelRod1FixDef.shape = & fuelRod1Poly;
		fuelRod1FixDef.density = 1.0f;
		fuelRod1FixDef.restitution = 1.0f;
		fuelRod1Def.position.Set(-7, 29);
		fuelRod1Def.type = b2_dynamicBody;
		fuelRod1Def.angle = 30 * degtorad;
		fuelRod1 = m_world->CreateBody(&fuelRod1Def);
		fuelRod1->CreateFixture(&fuelRod1FixDef);
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = fuelRod1;
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(0,0); 
		revolutejd->localAnchorB = fuelRod1->GetWorldCenter();
		
		m_world->CreateJoint(revolutejd);
		
		
	}	  

	b2DistanceJointDef distancejoint;
	b2Vec2 anchor1, anchor2;
	anchor1.Set(-8+ 2*sqrt(2)-6*cos(45* degtorad),23- 2*sqrt(2)+6*sin(45* degtorad));
	anchor2.Set(-7-5*cos(30* degtorad), 29-5*sin(30 * degtorad) );
	distancejoint.Initialize(dynamicBody2, fuelRod1, anchor1, anchor2);
	m_world->CreateJoint(&distancejoint);
	}
	
	//The middle part
	{//right part
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(2, 0.1);
        //polygonShape.Set(vertices, 5); //pass array to the shape
		
		b2FixtureDef myFixtureDef;
	    b2BodyDef myBodyDef;
		myBodyDef.type=b2_dynamicBody;
		//myBodyDef.linearVelocity.Set(0,10);
		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		myFixtureDef.density = 100;
		myFixtureDef.restitution = 0.1;
		myFixtureDef.filter.categoryBits = category3;
		myFixtureDef.filter.maskBits = mask3;
		myFixtureDef.filter.groupIndex = -1;
		myBodyDef.position.Set(2,29); 
		b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = dynamicBody2;
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(-2,0); 
		revolutejd->localAnchorB.Set(0,29);
		revolutejd->enableMotor = true;
		revolutejd->motorSpeed = -2;
		revolutejd->maxMotorTorque = 1000;
		m_world->CreateJoint(revolutejd);
	}
	
	{//left part
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(2, 0.1);
        //polygonShape.Set(vertices, 5); //pass array to the shape
		
		b2FixtureDef myFixtureDef;
	    b2BodyDef myBodyDef;
		myBodyDef.type=b2_dynamicBody;
		//myBodyDef.linearVelocity.Set(0,5);
		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		myFixtureDef.density = 100;
		myFixtureDef.restitution = 0.1;
		myFixtureDef.filter.categoryBits = category2;
		myFixtureDef.filter.maskBits = mask2;
		myFixtureDef.filter.groupIndex = -1;
		myBodyDef.position.Set(-2,29); 
		b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body
		
		b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
		revolutejd->bodyA = dynamicBody2;
		revolutejd->bodyB = groundBody;
		revolutejd->collideConnected = false;
		revolutejd->localAnchorA.Set(2,0); 
		revolutejd->localAnchorB.Set(0,29);
		m_world->CreateJoint(revolutejd);
	}
	
	{//testing with small balls
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(5, 0.1);
        //polygonShape.Set(vertices, 5); //pass array to the shape
		
		b2FixtureDef myFixtureDef;
	    	b2BodyDef myBodyDef;
		//myBodyDef.type=b2_dynamicBody;
		myBodyDef.angle = 45*degtorad;
		//myBodyDef.linearVelocity.Set(0,5);
		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		myFixtureDef.density = 100;
		myFixtureDef.restitution = 0.1;
		myFixtureDef.filter.categoryBits = 0x0004;
		myFixtureDef.filter.maskBits = 0x0005;
		//myFixtureDef.filter.groupIndex = -1;
		myBodyDef.position.Set(10,29); 
		b2Body* Body = m_world->CreateBody(&myBodyDef);
		Body->CreateFixture(&myFixtureDef); //add a fixture to the body
		
		
		
		
		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(5, 0.1);
        //polygonShape.Set(vertices, 5); //pass array to the shape
		
		b2FixtureDef myFixtureDef1;
	    	b2BodyDef myBodyDef1;
		//myBodyDef1.type=b2_dynamicBody;
		myBodyDef1.angle = 45*degtorad;
		//myBodyDef.linearVelocity.Set(0,5);
		myFixtureDef1.shape = &polygonShape1; //change the shape of the fixture
		myFixtureDef1.density = 100;
		myFixtureDef1.restitution = 0.1;
		myFixtureDef1.filter.categoryBits = 0x0004;
		myFixtureDef1.filter.maskBits = 0x0005;
		//myFixtureDef.filter.groupIndex = -1;
		myBodyDef1.position.Set(14,25); 
		b2Body* Body1 = m_world->CreateBody(&myBodyDef1);
		Body1->CreateFixture(&myFixtureDef1); //add a fixture to the body
		{
		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(5, 0.1);
        //polygonShape.Set(vertices, 5); //pass array to the shape
		
		b2FixtureDef myFixtureDef1;
	    	b2BodyDef myBodyDef1;
		//myBodyDef1.type=b2_dynamicBody;
		myBodyDef1.angle = 135*degtorad;
		//myBodyDef.linearVelocity.Set(0,5);
		myFixtureDef1.shape = &polygonShape1; //change the shape of the fixture
		myFixtureDef1.density = 100;
		myFixtureDef1.restitution = 0.1;
		myFixtureDef1.filter.categoryBits = 0x0004;
		myFixtureDef1.filter.maskBits = 0x0005;
		//myFixtureDef.filter.groupIndex = -1;
		myBodyDef1.position.Set(14,32); 
		b2Body* Body1 = m_world->CreateBody(&myBodyDef1);
		Body1->CreateFixture(&myFixtureDef1); //add a fixture to the body
		}

		
		b2Body* spherebody;
		{		
			b2CircleShape circle;
			circle.m_radius = 0.1;
			
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 0.000000000000000000000000001f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 1.0f;
			
			for (int i = 0; i < 200; ++i)
			{
			  b2BodyDef ballbd;
			  ballbd.type = b2_dynamicBody;
			  ballbd.position.Set((rand() % 2) + 12.0f , (rand() % 2) + 27.0f);
			  ballbd.linearVelocity.Set((rand() % 10) - 5.0f , (rand() % 10) - 5.0f);
			  spherebody = m_world->CreateBody(&ballbd);
			  spherebody->CreateFixture(&ballfd);
			}
	}
 
}
  sim_t *sim = new sim_t("Dominos", dominos_t::create);

}
