#include "Widgets/CObject.h"
#include <unordered_set>

CObject::CObject(CObject* parent)
	: m_parent(parent)
{
	setParent(parent);
	m_children = new std::unordered_set<CObject*>();
}

CObject::~CObject()
{
	if (m_parent)
	{
		m_parent->removeChild(this);
	}
	std::unordered_set<CObject*>* childs = (std::unordered_set<CObject*>*)m_children;
	for (auto iter = childs->begin(); iter != childs->end(); iter++)
	{
		delete (*iter);
	}
	delete childs;
}

void CObject::setParent(CObject* parent)
{
	if (m_parent)
	{
		m_parent->removeChild(this);
	}
	m_parent = parent;
	if (m_parent)
	{
		m_parent->addChild(this);
	}
}

FANTACY_INLINE void CObject::addChild(CObject* child)
{
	std::unordered_set<CObject*>* childs = (std::unordered_set<CObject*>*)m_children;
	childs->insert(child);
}

void CObject::removeChild(CObject* child)
{
	std::unordered_set<CObject*>* childs = (std::unordered_set<CObject*>*)m_children;
	childs->erase(child);
}
