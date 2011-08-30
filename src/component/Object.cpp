#include <kocmoc-core/componentSystem/Object.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>

using namespace kocmoc::core::componentSystem;
using std::string;
using kocmoc::core::types::Symbol;

Object::Object(string _name)
	: name(_name)
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

