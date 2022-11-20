#ifndef __FANTACY_APPLICATION_H__
#define __FANTACY_APPLICATION_H__
class FANTACY_API FApplication
{
public:
	static bool Init(bool bRealTimeDispatch = false);

	static s32 Exec();
};

#endif	//__FANTACY_APPLICATION_H__

