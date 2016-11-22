/**
@file SceneNode.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "SceneNode.h"
#include <cassert>
#include "Category.h"
#include "Utility.h"

namespace GEX {

	SceneNode::SceneNode(Category::Type category) : 
	_parent(nullptr),
	_defaultCategory(category)
	{}


	void SceneNode::onCommand(const Command & command, sf::Time dt)
	{
		if (command.category & getCategory())
			command.action(*this, dt);
		for (auto& child : _children)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return _defaultCategory;
	}

	void SceneNode::attachChild(Ptr child)
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(_children.begin(), _children.end(), [&](Ptr& p)->bool {return p.get() == &node;});
		assert(found == _children.end());
		Ptr result = std::move(*found);
		result->_parent = nullptr;
		_children.erase(found);
		return result;
	}

	void SceneNode::update(sf::Time dt, CommandQueue& commands)
	{
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform()* sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
			transform = node->getTransform() * transform;
		return transform;
	}

	sf::FloatRect SceneNode::getBoundingRect() const
	{
		return sf::FloatRect();
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	void SceneNode::checkSceneCollision(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		this->checkNodeCollision(node, collisionPairs);

		for (auto& child : node._children)
			this->checkSceneCollision(*child, collisionPairs);
	}

	void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
			collisionPairs.insert(std::minmax(this, &node));

		for (auto& child : _children)
			child->checkNodeCollision(node, collisionPairs);
	}

	void SceneNode::removeWrecks()
	{
		auto wreckFieldBegin = std::remove_if(_children.begin(), _children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
		_children.erase(wreckFieldBegin, _children.end());
		std::for_each(_children.begin(), _children.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	bool SceneNode::isMarkedForRemoval()
	{
		return isDestroyed();
	}

	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates state) const
	{
		//apply transform
		state.transform *= getTransform();
		drawCurrent(target, state);
		drawBoundingRect(target, state);
		drawChildren(target, state);
	}

	void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		//do nothing by default
	}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates state) const
	{
		for (const Ptr& child : _children)
		{
			child->draw(target, state);
		}
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		//do nothing by default
	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (const Ptr& child : _children)
		{
			child->update(dt, commands);
		}
	}

	void SceneNode::drawBoundingRect(sf::RenderTarget & target, sf::RenderStates  state) const
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);
		target.draw(shape);
		
	}

	float distance(const SceneNode & lhs, const SceneNode & rhs)
	{
		return length(lhs.getWorldPosition()-rhs.getWorldPosition());
	}

	bool collision(const SceneNode& lhs, const SceneNode& rhs)
	{
		return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}
}