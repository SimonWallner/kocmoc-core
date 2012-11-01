#include <kocmoc-core/component/RigidBody.hpp>

#include <kocmoc-core/component/Gizmo.hpp>

using namespace kocmoc::core::component;

void RigidBody::init()
{
	gizmo = parent->getComponent<Gizmo>();
	
	btVector3 position(gizmo->position.x, gizmo->position.y, gizmo->position.z);
	btQuaternion orientation(gizmo->orientation.x, gizmo->orientation.y, gizmo->orientation.z, gizmo->orientation.w);

	btTransform transform;
	transform.setOrigin(position);
	transform.setRotation(orientation);
	
	
	btVector3 localInertia(0, 0, 0);
	if (mass > 0)
		collisionShape->calculateLocalInertia(mass,localInertia);
	
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	
	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
}

void RigidBody::onUpdate(float deltaT, float t)
{
	UNUSED deltaT;
	UNUSED t;
	
	btTransform transform;
	motionState->getWorldTransform(transform);
	gizmo->position = glm::vec3(transform.getOrigin().x(),
								transform.getOrigin().y(),
								transform.getOrigin().z());
	
	gizmo->orientation = glm::quat(transform.getRotation().x(),
								   transform.getRotation().y(),
								   transform.getRotation().z(),
								   transform.getRotation().w());
}
