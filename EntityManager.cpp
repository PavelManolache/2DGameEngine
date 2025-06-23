#include "EntityManager.h"
#include <algorithm>

std::shared_ptr<Entity> EntityManager::addEntity(std::string tag)
{
	auto entity = std::make_shared<Entity>(++m_totalEntities, tag);
	m_entitiesToAdd.push_back(entity);
	return entity;

}; 

void EntityManager::update()
{
	for(auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
		
	}
	m_entitiesToAdd.clear();
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](const std::shared_ptr<Entity>& e) 
		{
		return !e->m_active;
		}), m_entities.end());

	for(auto& [key , vec ] : m_entityMap)
	{
		vec.erase(std::remove_if(vec.begin(), vec.end(), [](const std::shared_ptr<Entity>& e) {
			return !e->m_active;
			}), vec.end());
	}


};

const EntityVector& EntityManager::getEntities()
{
	return m_entities;
}
const EntityVector& EntityManager::getEntities(std::string type)
{
	return m_entityMap[type];

}