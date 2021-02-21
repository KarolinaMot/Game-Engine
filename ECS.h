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
//Idk if I should just do this with classes and structs lmao this is too much for my tiny brain
//At least I understand what this does lmao 
//This part of the code is about to give me an anxiety attack no joke

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
	static ComponentID typeID = getComponentTypeID(); //kuriamas component ID naudojant funkcija
	return typeID;
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
		}
		void draw() {
			for (auto& c : components) c->draw();
		}
		bool isActive() const { return active; }
		void destroy() { active = false; }

		template <typename T> bool hasComponent() const
		{
			return componentBitSet[getComponentTypeID<T>];
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
			auto ptr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}
	};

class Manager
{
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	public:
		void update()
		{
			for (auto& e : entities) e->update();
		}
		void draw()
		{
			for (auto& e : entities) e->draw();
		}
		void refresh()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
				{
					return !mEntity->isActive();
				}),
				std::end(entities));

		}
		Entity& addEntity()
		{
			Entity* e = new Entity();
			std::unique_ptr<Entity> uPtr{ e };
			entities.emplace_back(std::move(uPtr)); 
			return *e;

		}

};
