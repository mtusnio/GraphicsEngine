#ifndef H_HANDLE
#define H_HANDLE

#include "IEntitySystem.h"

template<class T>
class Handle
{
public:
	Handle();
	Handle(const T * entity);
	virtual ~Handle();

	const T * operator*() const { return Get(); }
	T * operator*() { return Get(); }

	Handle<T> & operator=(const T * entity);
	Handle<T> & operator=(const Handle<T> & handle);

	bool operator==(const T * entity) { return Get() == entity; }
	bool operator!=(const T * entity) { return !(*this == entity); }

	operator T*() const { return Get(); }

	void Set(const T * entity);
	T * Get() const { return m_EntitySystem->FindEntityByID(m_EntityID); }
private:
	IEntitySystem * m_EntitySystem;
	Entity::ID m_EntityID;
};

template<class T>
Handle<T>::Handle()
{
	Set(nullptr);
}


template<class T>
Handle<T>::Handle(const T * entity)
{
	Set(entity);
}

template<class T>
Handle<T>::~Handle()
{

}

template<class T>
Handle<T> & Handle<T>::operator=(const T * entity)
{
	Set(entity);
}

template<class T>
Handle<T> & Handle<T>::operator=(const Handle<T> & handle)
{
	Set(*handle);
}

template<class T>
void Handle<T>::Set(const T * entity)
{
	if (entity == nullptr)
	{
		m_EntitySystem = nullptr;
		m_EntityID = Entity::INVALID_ID;
	}
	else
	{
		m_EntitySystem = entity->GetEntitySystem();
		m_EntityID = entity->GetID();
	}
}

#endif