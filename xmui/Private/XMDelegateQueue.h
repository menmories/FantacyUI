#ifndef XM_DELEGATEQUEUE_H
#define XM_DELEGATEQUEUE_H

#include "Event/XMEvent.h"
#include <list>
#include <functional>


class XMDelegateQueueData
{
public:
	int type = 0;
	void* args = nullptr;
	std::function<void(int, void*)> m_func = nullptr;

	void invoke()
	{
		m_func(type, args);
	}
};

class XMDelegateQueue
{
public:
	XMDelegateQueue();
	~XMDelegateQueue();

	bool hasEvent();

	void addFunc(const XMDelegateQueueData& data);

	void addToBegin(const XMDelegateQueueData& data);

	void callAndRemove();

	void callAndRemoveBlock();
private:
	std::list<XMDelegateQueueData> m_funcs;
	CRITICAL_SECTION m_cs;
};

#endif  //XM_DELEGATEQUEUE_H

