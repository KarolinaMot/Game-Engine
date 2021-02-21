#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/*Manager which holds entities, which are anything drawn in the game.
Each entity has components, which give it functionality. 
Each component has it's own class, so templates and other fancy stuff are required in order to get and add components.*/
/*An Entity-Component-System – mostly encountered in video games – is a design pattern which allows you great flexibility in designing your overall software architecture[1].*/

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() //funkcija skirta kurti kiekvieno Component ID
{
	static ComponentID lastID = 0;
	return lastID++; //1 component ID bus 1; 2 component ID bus 2 ir t.t.
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentID(); //kuriamas component ID naudojant funkcija
	return typeID();
}

constexpr std::size_t maxComponents = 32;//kiek daugiausiai gali buti components

using ComponentBitSet = std::bitset<maxComponents>; //Component BitSet leidzia mums zinoti ar entity turi tam tikra component
using ComponentArray = std::array < Component*, maxComponents>; //Component pointers masyvas, kurio dydis yra maxComponents

class Component
{
	public:
		Entity* entity;
		virtual void init() {};
		virtual void update() {};
		virtual void draw() {};

		virtual ~Component(){}
};

class Entity
{
	private:
		bool active = true; //Bool naudojamas tikrinti ar Entity yra aktyvus. Jei jis nera aktyvus Entity bus panaikinama
		std::vector<std::unique_ptr<Component>> components; //sukuriamas vectoriu components. Vektoriai yra kaip masyvas be dyzžio
		ComponentArray componentArray;
		ComponentBitSet componentBitSet;

	public:
		void update() //entity loops through all components
		{
			for (auto& c : components) c->update();
			for (auto& c : components) c->draw();

		}
		void draw() {

		}
		bool isActive() const { return active; }
		void destroy() { active = false; }

		template <typename T> bool hasComponent() const
		{
			return componentBitSet[getComponentID<T>];
		}

		template <typename T, typename... TArgs>
		T& addComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));
			
			componentArray[getComponentTypeID<T>()] = c;
			componentBitSet[getComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		template<typename T> T& getComponent() const
		{
			auto ptr(componentArray[getComponentTypeID<T>()])
		}
};


