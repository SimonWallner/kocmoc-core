#include <kocmoc-core/componentSystem/Object.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

using namespace kocmoc::core::componentSystem;
using std::string;
using kocmoc::core::types::Symbol;
using kocmoc::core::util::Properties;
using kocmoc::core::scene::Camera;
using kocmoc::core::renderer::RenderPass;

Object::Object(string _name, Properties* _props)
	: props(_props)
	, name(_name)
{}

void Object::addComponent(Component *component)
{
	components.insert(NameComponentPair(component->getName(), component));
	component->setParent(this);
}

void Object::registerRenderReceiver(Component* receiver)
{
	renderReceivers.push_back(receiver);
}

void Object::registerUpdateReceiver(Component* receiver)
{
	updateReceivers.push_back(receiver);
}

void Object::update(float deltaT, float t)
{
	for (ComponentList::iterator it = updateReceivers.begin();
		 it != updateReceivers.end();
		 it++)
	{
		(*it)->onUpdate(deltaT, t);
	}
}

void Object::render(RenderPass pass, Camera* camera)
{
	for (ComponentList::iterator it = renderReceivers.begin();
		 it != renderReceivers.end();
		 it++)
	{
		(*it)->onRender(pass, camera);
	}
}

void Object::initComponents()
{
	for (ComponentMultimap::iterator it = components.begin();
		 it != components.end();
		 it++)
	{
		it->second->init();
	}
}

void Object::dump()
{
	std::cout << "==================== object dump ===================" << std::endl;
	for (ComponentMultimap::iterator it = components.begin();
		 it != components.end();
		 it++)
	{
//		std::cout << it->first << " (" << &(it->first) << ") | " << it->second << std::endl;
		printf("%40s (%p) | %p", it->first, it->first,  (void*)it->second);
	}
	
	std::cout << std::flush;

}
