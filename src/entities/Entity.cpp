#include "Entity.h"
#include "../renderer/Model.h"


Entity::Entity() :
m_Physics(false),
m_EntitySystem(nullptr),
m_EntityID(INVALID_ID)
{

}

Entity::~Entity()
{

}
