/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
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
  /** The is the constructor
* This is the documentation block for the constructor.
*/
  
  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1
* \brief pointer to the body ground
*/
      
// {
// b2Body* b1;
// b2EdgeShape shape;
// shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
// b2BodyDef bd;
// b1 = m_world->CreateBody(&bd);
// b1->CreateFixture(&shape, 0.0f);
// }
    
// {
// b2Body* body;
// b2BodyDef bodyDef;
// b2PolygonShape bodyPoly;
// b2FixtureDef bodyFix;

// //Setting up Vertices in an Array
// b2Vec2 ver1 ( 0, 0);
// b2Vec2 ver2 ( 5, 2.5);
// b2Vec2 ver3 ( 45, 2.5);
// b2Vec2 ver4 ( 50, 0);

// //Push in order
// b2Vec2 vertexArray[] = {ver1, ver2, ver3, ver4};

// //bodyDef.type = b2_dynamicBody;
// //b2Vec2 Array then Vertex Count
// bodyPoly.Set(vertexArray, 4);
// bodyFix.shape = &bodyPoly;
// bodyFix.density = 0.5;
// bodyFix.friction = 0.5;
// bodyFix.restitution = 1.0;
// bodyDef.position.Set(-25, 0);
// body = m_world->CreateBody(&bodyDef);
// body->CreateFixture(&bodyFix);
    
// }

// {
// b2Body* body;
// b2BodyDef bodyDef;
// b2PolygonShape bodyPoly;
// b2FixtureDef bodyFix;

// //Setting up Vertices in an Array
// b2Vec2 ver1 ( 0, 0);
// b2Vec2 ver2 ( 5, 2.5);
// b2Vec2 ver3 ( 5, 50);
// b2Vec2 ver4 ( 0, 50);

// //Push in order
// b2Vec2 vertexArray[] = {ver1, ver2, ver3, ver4};

// //bodyDef.type = b2_dynamicBody;
// //b2Vec2 Array then Vertex Count
// bodyPoly.Set(vertexArray, 4);
// bodyFix.shape = &bodyPoly;
// bodyFix.density = 0.5;
// bodyFix.friction = 0.5;
// bodyFix.restitution = 1.0;
// bodyDef.position.Set(-25, 0);
// body = m_world->CreateBody(&bodyDef);
// body->CreateFixture(&bodyFix);
    
// }
// {
// b2Body* body;
// b2BodyDef bodyDef;
// b2PolygonShape bodyPoly;
// b2FixtureDef bodyFix;

// //Setting up Vertices in an Array
// b2Vec2 ver1 ( 45, 50);
// b2Vec2 ver2 ( 50, 50);
// b2Vec2 ver3 ( 45, 2.5);
// b2Vec2 ver4 ( 50, 0);

// //Push in order
// b2Vec2 vertexArray[] = {ver1, ver2, ver4, ver3};

// //bodyDef.type = b2_dynamicBody;
// //b2Vec2 Array then Vertex Count
// bodyPoly.Set(vertexArray, 4);
// bodyFix.shape = &bodyPoly;
// bodyFix.density = 0.5;
// bodyFix.friction = 0.5;
// bodyFix.restitution = 1.0;
// bodyDef.position.Set(-25, 0);
// body = m_world->CreateBody(&bodyDef);
// body->CreateFixture(&bodyFix);
    
// }

// {
// /*! \subsection a11 Train of spheres
// * Here the train of small spheres is created.
// * \li variable \b "circle" defines the shape of the sphere,every sphere has the same shape.
// * \li varible \b "ballfd" defines the fixture of the sphere.
// * \li varible \b "ballbd" defines the body of a particular sphere.
// */
// b2Body* spherebody;

// b2CircleShape circle;
// circle.m_radius = 0.5;

// b2FixtureDef ballfd;
// ballfd.shape = &circle;
// ballfd.density = 0.1f;
// ballfd.friction = 0.0f;
// ballfd.restitution = 2.0f;

// for (int i = 0; i < 10; ++i)
// {
// b2BodyDef ballbd;
// ballbd.type = b2_dynamicBody;
// ballbd.position.Set((rand() % 40) - 20.0f , (rand() % 20) + 10.0f);
// ballbd.linearVelocity.Set((rand() % 40) - 20.0f , (rand() % 20) - 10.0f);
// spherebody = m_world->CreateBody(&ballbd);
// spherebody->CreateFixture(&ballfd);
// }
// }
    

// {
// b2Body* b1;
// b2PolygonShape bodyPoly;
// b2BodyDef bd;
// bodyPoly.SetAsBox(20.f, 3.f );
// b2FixtureDef fd;

// fd.shape = &bodyPoly;
// fd.density = 0.1;
// fd.restitution = 1.0;
// bd.position.Set(0, 30);
// b1 = m_world->CreateBody(&bd);
// b1->CreateFixture(&fd);
// }

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
bodyPoly.SetAsBox(0.5f, 10.0f );
b2FixtureDef fd;

fd.shape = &bodyPoly;
fd.restitution = 1.0;
bd.position.Set(-10.0f, 10.0f);
b1 = m_world->CreateBody(&bd);
b1->CreateFixture(&fd);
    }

    {//right piston side
     b2Body* b1;
b2PolygonShape bodyPoly;
b2BodyDef bd;
bodyPoly.SetAsBox(0.5f, 10.0f );
b2FixtureDef fd;

fd.shape = &bodyPoly;
fd.restitution = 1.0;
bd.position.Set(10.0f, 10.0f);
b1 = m_world->CreateBody(&bd);
b1->CreateFixture(&fd);
    }

    {//top piston side
     b2Body* b1;
b2PolygonShape bodyPoly;
b2BodyDef bd;
bodyPoly.SetAsBox(5.0f, 0.5f );
b2FixtureDef fd;

fd.shape = &bodyPoly;
fd.restitution = 1.0;
bd.position.Set(0, 25);
b1 = m_world->CreateBody(&bd);
b1->CreateFixture(&fd);
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
b2Vec2 vertices[3];
vertices[0].Set(5.5, 6.5);
vertices[1].Set(6.5, 5.5);
vertices[2].Set(-4, 0);
vertices[3].Set( 0, -4);

b2PolygonShape polygonShape;
polygonShape.Set(vertices, 4); //pass array to the shape

b2FixtureDef myFixtureDef;
b2BodyDef myBodyDef;
myFixtureDef.shape = &polygonShape; //change the shape of the fixture
myBodyDef.position.Set(8 ,23); //in the middle
//myBodyDef.type=b2_dynamicBody;
b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);
dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body



/*b2PrismaticJointDef prismaticJointDef;
b2Vec2 v;
v.Set(1, 1);
prismaticJointDef.Initialize(dynamicBody1, groundBody, dynamicBody1->GetWorldCenter(), v);
m_world->CreateJoint(&prismaticJointDef);*/

}

{//Exhaust control
b2Vec2 vertices[3];
vertices[0].Set(-5.5, 6.5);
vertices[1].Set(-6.5, 5.5);
vertices[2].Set(4, 0);
vertices[3].Set( 0, -4);

b2PolygonShape polygonShape;
polygonShape.Set(vertices, 4); //pass array to the shape

b2FixtureDef myFixtureDef;
b2BodyDef myBodyDef;
myFixtureDef.shape = &polygonShape; //change the shape of the fixture
myBodyDef.position.Set(-8 ,23); //in the middle
b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body

/*b2PrismaticJointDef prismaticJointDef;
b2Vec2 v;
v.Set(1, -1);
prismaticJointDef.Initialize(dynamicBody2, groundBody, dynamicBody2->GetWorldCenter(), v);
m_world->CreateJoint(&prismaticJointDef);*/

}


{//Fuel control rod
b2Body* fuelRod1;
b2PolygonShape fuelRod1Poly;
b2BodyDef fuelRod1Def;
fuelRod1Poly.SetAsBox(4, 0.6f);
b2FixtureDef fuelRod1FixDef;

fuelRod1FixDef.shape = & fuelRod1Poly;
fuelRod1FixDef.density = 1.0f;
fuelRod1Def.position.Set(5, 37);
fuelRod1Def.type = b2_dynamicBody;
fuelRod1 = m_world->CreateBody(&fuelRod1Def);
fuelRod1->CreateFixture(&fuelRod1FixDef);

b2Body* fuelRod2;
b2PolygonShape fuelRod2Poly;
b2BodyDef fuelRod2Def;
fuelRod2Poly.SetAsBox(6, 0.6f);
b2FixtureDef fuelRod2FixDef;

fuelRod2FixDef.shape = & fuelRod2Poly;
fuelRod2FixDef.density = 1.0f;
fuelRod2Def.position.Set(12.3f, 33.7f);
fuelRod2Def.type = b2_dynamicBody;
fuelRod2Def.angle = -40 * degtorad;
fuelRod2 = m_world->CreateBody(&fuelRod2Def);
fuelRod2->CreateFixture(&fuelRod2FixDef);

b2WeldJointDef fuelRodjointDef;
fuelRodjointDef.bodyA = fuelRod1;
fuelRodjointDef.bodyB = fuelRod2;
fuelRodjointDef.localAnchorA.Set(3.85f, 0.0f);
fuelRodjointDef.localAnchorB.Set(-5.85f ,0.0f);

b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
revolutejd->bodyA = fuelRod1;
revolutejd->bodyB = groundBody;
revolutejd->collideConnected = false;
revolutejd->localAnchorA.Set(4.85f, 0.3f);
revolutejd->localAnchorB.Set(9.85f, 37.0f);
revolutejd->enableLimit = true;
revolutejd->lowerAngle = 0;
revolutejd->upperAngle = 0.5f;
//revolutejd->maxMotorTorque = 1.0;
//revolutejd->enableMotor = true;

//m_world->CreateJoint(revolutejd);


}





{//arbit body
     b2Body* b1;
b2PolygonShape bodyPoly;
b2BodyDef bd;
bodyPoly.SetAsBox(5, 5);
b2FixtureDef fd;

fd.shape = &bodyPoly;
fd.restitution = 1.0;
fd.density = 1.0f;
bd.position.Set(25, 25);
bd.type = b2_dynamicBody;
b1 = m_world->CreateBody(&bd);
b1->CreateFixture(&fd);

b2RevoluteJointDef* revolutejd = new b2RevoluteJointDef();
revolutejd->bodyA = b1;
revolutejd->bodyB = groundBody;
revolutejd->collideConnected = false;
revolutejd->localAnchorA.Set(0,0);
revolutejd->localAnchorB.Set(25,25);
revolutejd->enableLimit = true;
revolutejd->lowerAngle = 0;
revolutejd->upperAngle = 0.5f;
//revolutejd->maxMotorTorque = 1.0;
//revolutejd->enableMotor = true;

m_world->CreateJoint(revolutejd);
    }

}
  sim_t *sim = new sim_t("Dominos", dominos_t::create);

}
