#pragma once

#include<string>
#include<memory>
#include "Components.h"

class Entity
{
	friend class EntityManager;
	size_t m_id = 0;
	
	
	std::string m_tag = "deafault";

	

public:
	bool m_active = true;
	Entity(const size_t id, const std::string& tag);
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CInput> cInput;

};

