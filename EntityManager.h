#pragma once
#include <memory>
#include "Entity.h"
#include <string>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
	EntityVector m_entities;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
	EntityVector m_entitiesToAdd;

public:

	std::shared_ptr<Entity> addEntity(std::string tag);

	void update();
	const EntityVector& getEntities();
	const EntityVector& getEntities(std::string);
};

