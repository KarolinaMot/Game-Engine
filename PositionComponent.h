#pragma once
#include "ECS.h"

class PositionComponent: public Component
{
	private:
		int xpos;
		int ypos;

	public:
		void update() override {
			xpos++;
			ypos++;
		}
		PositionComponent()
		{
			xpos = 0;
			ypos = 0;
		}
		PositionComponent(int x, int y) {
			xpos = x;
			ypos = y;
		}
		int x() { return xpos; }
		void x(int x) {xpos = x;}
		int y() { return ypos; }
		void y(int y) { ypos = y; }
		void setPos(int x, int y) {xpos = x; ypos = y;}
};


/*entt::entity entity = m_Registry.create(); //create entities. An entity is an uint32
m_Registry.emplace<PositionComponent>(entity); //adds <component> to (entity)
m_Registry.remove<TransformComponent>(entity); //removes <component> from (entity)
m_Registry.clear(); //removes everything from registry
m_Registry.get<TransformComponent>(entity); //returns a referenc of the <component>*/