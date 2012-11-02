#include <kocmoc-core/component/RigidBody.hpp>

#include <kocmoc-core/component/Transform.hpp>

using namespace kocmoc::core::component;

void RigidBody::init()
{
	transform = parent->getComponent<Transform>();
	
	btTransform bulletTransform;
	bulletTransform.setFromOpenGLMatrix(transform->toGLMatrix());
	
	btVector3 localInertia(0, 0, 0);
	if (mass > 0)
		collisionShape->calculateLocalInertia(mass, localInertia);
	
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	motionState = new btDefaultMotionState(bulletTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	
	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
}

void RigidBody::onUpdate(float deltaT, float t)
{
	UNUSED deltaT;
	UNUSED t;
	
	btTransform bulletTransform;
	motionState->getWorldTransform(bulletTransform);
	
	float m[16];
	bulletTransform.getOpenGLMatrix(m);
	transform->matrix = glm::mat4(m[0], m[1], m[2], m[3],
								  m[4], m[5], m[6], m[7],
								  m[8], m[9], m[10], m[11],
								  m[12], m[13], m[14], m[15]);


}
