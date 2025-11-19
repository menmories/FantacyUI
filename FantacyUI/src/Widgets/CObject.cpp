#include "Widgets/CObject.h"

CObject::CObject(CObject* parent)
	: m_parent(parent)
{
	m_parent->addChild(this);
}

CObject::~CObject()
{

}
