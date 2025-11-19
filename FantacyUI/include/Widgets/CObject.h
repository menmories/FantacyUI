#ifndef COBJECT_H
#define COBJECT_H

#include "PlatformDef.h"
#include <vector>

class CObject
{
public:
	CObject(CObject* parent = nullptr);
	virtual ~CObject();

	FANTACY_INLINE void setParent(CObject* parent)
	{
		m_parent = parent;
		m_parent->addChild(this);
	}

	FANTACY_INLINE CObject* parent()
	{
        return m_parent;
	}

	FANTACY_INLINE void addChild(CObject* child)
	{
		m_children.push_back(child);
	}
private:
	CObject* m_parent;
	std::vector<CObject*> m_children;
};

#endif // !
