#pragma once

// ��������ƽ̨���죬����Ǩ�Ƶ���ͬƽ̨

class MemoryPool
{
private:
public:
	void* handle;
	void initialize(size_t size, size_t maximumSize = 0);
	void deinitialize();
	void* allocate(size_t size);
	void free(void* memblock);
};

class CriticalSection2
{
private:
public:
	volatile void* token;
	void create();
	void release();
	void enter();
	void leave();
	void waitForComplete();
};