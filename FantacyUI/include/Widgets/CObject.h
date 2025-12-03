#ifndef COBJECT_H
#define COBJECT_H

#include "PlatformDef.h"

class FANTACY_API CObject
{
public:
	CObject(CObject* parent = nullptr);
	virtual ~CObject();

	virtual void setParent(CObject* parent);

	FANTACY_INLINE CObject* parent()
	{
        return m_parent;
	}

	

	
protected:
	void addChild(CObject* child);
	void removeChild(CObject* child);
private:
	CObject* m_parent;
	void* m_children;
};

#endif // !
