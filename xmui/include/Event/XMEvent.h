#ifndef XM_EVENT_H
#define XM_EVENT_H

#include "XMPlatformDef.h"



enum class MouseButton
{
	MouseButton_Left,
	MouseButton_Right,
	MouseButton_Mid,
	MouseButton_X1,
	MouseButton_X2
};


class XMUI_API XMEvent
{
public:
	XMEvent();
	~XMEvent();



	s32 type;
	void* args;
	void postEvent();
	void sendEvent();
};

class XM_INTERFACE XMDelegateInterface
{
public:
	virtual void invoke() = 0;


private:

};

typedef void(*XMEventCb)(int type, void* args);

#endif  //XM_EVENT_H

