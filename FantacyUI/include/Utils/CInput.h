#ifndef __CINPUT_H__
#define __CINPUT_H__

#include "PlatformDef.h"

enum class EInputType
{
	InputType_Key,
	InputType_Mouse,
};

enum class EMouseButon
{
	MouseButton_Left = 0x00000001,
	MouseButton_Right = 0x00000002,
	MouseButton_Mid = 0x00000004,
	MouseButton_X1 = 0x00000008,
	MouseButton_X2 = 0x00000010,
};

enum class EKeyboard
{
	Keyboard_W,
	Keyboard_A,
	Keyboard_S,
	Keyboard_D
};

class FANTACY_API CInput
{
public:
	CInput();
	~CInput();

	FANTACY_INLINE EInputType type()const
	{
		return m_type;
	}
private:
	EInputType m_type;
	bool  m_bDown;	//指示外部输入是否被按下
	void* params;
};



#endif	//__CINPUT_H__

