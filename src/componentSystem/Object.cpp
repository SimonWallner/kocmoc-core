#include <kocmoc-core/componentSystem/Object.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

using namespace kocmoc::core::componentSystem;
using std::string;
using kocmoc::core::types::Symbol;
using kocmoc::core::util::Properties;

Object::Object(string _name, Properties* _props)
	: props(_props)
	, name(_name)
{}

void Object::addComponent(Component *component)
{
	components[component->getName()] = component;
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

void Object::update()
{
	for (ComponentList::iterator it = updateReceivers.begin();
		 it != updateReceivers.end();
		 it++)
	{
		(*it)->onUpdate();
	}
}

void Object::render()
{
	for (ComponentList::iterator it = renderReceivers.begin();
		 it != renderReceivers.end();
		 it++)
	{
		(*it)->onRender();
	}
}