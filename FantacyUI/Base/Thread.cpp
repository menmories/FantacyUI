#include "pch.h"
#include "Thread.h"
#include <process.h>

FThread::FThread()
	: mRunnable(nullptr)
	, mThreadId(0)
	, mThreadHandle(0)
{
}

FThread::FThread(IRunnable* InRunnable)
	: mRunnable(InRunnable)
	, mThreadId(0)
	, mThreadHandle(0)
{
}

FThread::~FThread()
{
}

bool FThread::Start()
{
	mThreadHandle = ::_beginthreadex(NULL, 0,
		(_beginthreadex_proc_type)&FThread::__ThreadProc,
		reinterpret_cast<void*>(this),
		0, &mThreadId);
	if (mThreadHandle)
	{
		return true;
	}
	return false;
}

void FThread::Wait(u32 uWaitTime)
{
	::WaitForSingleObject((HANDLE)mThreadHandle, uWaitTime);
}

s32 FThread::__ThreadProc(void* lParam)
{
	FThread* pThis = reinterpret_cast<FThread*>(lParam);
	assert(pThis);
	s32 nRet = pThis->mRunnable->Run();
	return nRet;
}
