#ifndef __FANTACY_THREAD_H__
#define __FANTACY_THREAD_H__


class IRunnable
{
public:
	virtual s32 Run() = 0;
};



class FANTACY_API FThread
{
public:
	FThread();
	FThread(IRunnable* InRunnable);
	~FThread();

	bool Start();

	void Wait(u32 uWaitTime);
private:
	static s32 __ThreadProc(void* lParam);
private:
	IRunnable* mRunnable;
	u64 mThreadHandle;
	u32 mThreadId;
};

#endif	//__FANTACY_THREAD_H__
