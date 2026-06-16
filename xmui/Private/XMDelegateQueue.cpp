#include "XMDelegateQueue.h"



XMDelegateQueue::XMDelegateQueue()
{
	InitializeCriticalSection(&m_cs);
}

XMDelegateQueue::~XMDelegateQueue()
{
	DeleteCriticalSection(&m_cs);
}

bool XMDelegateQueue::hasEvent()
{
	EnterCriticalSection(&m_cs);
	if (m_funcs.size() > 0)
	{
		LeaveCriticalSection(&m_cs);
		return true;
	}
	LeaveCriticalSection(&m_cs);
	return false;
}

void XMDelegateQueue::addFunc(const XMDelegateQueueData& data)
{
	EnterCriticalSection(&m_cs);
	m_funcs.push_back(data);
	LeaveCriticalSection(&m_cs);
}

void XMDelegateQueue::addToBegin(const XMDelegateQueueData& data)
{
	EnterCriticalSection(&m_cs);
	m_funcs.push_front(data);
	LeaveCriticalSection(&m_cs);
}

void XMDelegateQueue::callAndRemove()
{
	EnterCriticalSection(&m_cs);
	auto iter = m_funcs.front();
	m_funcs.pop_front();
	LeaveCriticalSection(&m_cs);
	iter.invoke();
}

void XMDelegateQueue::callAndRemoveBlock()
{
	EnterCriticalSection(&m_cs);
	auto iter = m_funcs.begin();
	iter->invoke();
	m_funcs.erase(iter);
	printf("funcs count=%d\n", m_funcs.size());
	LeaveCriticalSection(&m_cs);
}

