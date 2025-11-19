#include "Utils/CEvent.h"

CEvent::CEvent()
	: m_type(0), m_data(nullptr)
{
}

CEvent::CEvent(int type, void* data)
	: m_type(type), m_data(data)
{
}

CEvent::~CEvent()
{
}


