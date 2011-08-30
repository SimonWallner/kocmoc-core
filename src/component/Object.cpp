#include <kocmoc-core/componentSystem/Object.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

using namespace kocmoc::core::componentSystem;
using std::string;

Object::Object(string _name)
	: name(_name)
{}

void Object::addComponent(Component *component)
{
	components.push_back(component);
	component->setParent(this);
}

void Object::registerRenderReceiver(Component* receiver)
{
	renderReceivers.push_back(receiver);
}

void Object::registerMessageReceiver(Component* receiver)
{
	messageReceivers.push_back(receiver);
}

void Object::registerUpdateReceiver(Component* receiver)
{
	updateReceivers.push_back(receiver);
}

void Object::sendMessage()
{
	for (ComponentList::iterator it = messageReceivers.begin();
		 it != messageReceivers.end();
		 it++)
	{
//		(*it)->sendMessage();
	}
}
