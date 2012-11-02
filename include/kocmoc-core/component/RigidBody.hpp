#ifndef KOCMOC_CORE_COMPONENT_RIGID_BODY_HPP_
#define KOCMOC_CORE_COMPONENT_RIGID_BODY_HPP_

#include <glm/glm.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "btBulletDynamicsCommon.h"
#pragma GCC diagnostic pop

namespace kocmoc
{
	namespace core
	{
		namespace component
		{
			class Transform;
			
			class RigidBody : public core::componentSystem::Component
			{
			public:
				RigidBody(btDiscreteDynamicsWorld* _dynamicsWorld,
						  btCollisionShape* _collisionShape,
						  btScalar _mass)
				: mass(_mass)
				, collisionShape(_collisionShape)
				, dynamicsWorld(_dynamicsWorld)
				{};
				
				void init();
				
				virtual void onUpdate(float deltaT, float t);
				
				void applyCentralImpulse(glm::vec3 impulse);
				
			private:
				Transform* transform;
				
				btScalar mass;
				btCollisionShape* collisionShape;
				btDiscreteDynamicsWorld* dynamicsWorld;
				btDefaultMotionState* motionState;
				btRigidBody* body;
			};
		}
	}
}


#endif
