#pragma once

// ʵ�����¼�����

#include "SLWNetwork.h"
#include "SimpleAI.h"
#include "MemoryLeakMonitor.h"
#include "ModernMemoryAllocator.h"
#include "PlatformAdapter.h"

class eb
{
private:
	std::default_random_engine* e1;
	int result;
	int queueDepth = 0;
	client shu[4];
	DWORD threadId;

	std::queue<ebRequest> msgQueue;
	std::queue<ebEvent> evtQueue;

	bool working = true;
	CriticalSection evt;
	
	HANDLE sema;

	int clientType[4] = { 0 };
	EventBusUser* clientHandle[4];
	MatchingUser* currentMatch;
	bool customRemoteFuncEnabled = false;
	LPVOID crfParam;

	void shuffle_internal();
	void roll_internal();
	void shuffle();

public:
	// ��ʼ�� EventBus
	// ����ֵ: ��
	void init();

	// �ͷ� EventBus
	// ����ֵ: ��
	void deinit();

	// �����Ϣ���У�������ֱ�ӵ��ã�
	// ����ֵ: ��
	void clear();

	// ����/�㲥��Ϣ��������ֱ�ӵ��ã�
	// id : �ͻ� ID���� 0 - 3
	// ���������ο� aiMessage �нӿڶ���
	// ����ֵ: ��
	void send(int id, unsigned char msgType, unsigned int par1, unsigned int par2);
	void send(int id, unsigned char msgType, unsigned int par1);
	void send(int id, unsigned char msgType);
	void send(int id, unsigned char msgType, unsigned int par1, void* payload, int lpayload);
	void broadcast(unsigned char msgType, unsigned int par1, void* payload, int lpayload);
	void broadcast(unsigned char msgType, unsigned int par1, unsigned int par2);
	void broadcast(unsigned char msgType, unsigned int par1);
	void broadcast(unsigned char msgType);

	// �յ�Զ�̷���ֵ�������뷵��ֵ������С����ⲿ���á�
	// ���͵����������Զ�̷��������ݣ������¼���
	// hClient : �ͻ����
	// response : ����ֵ
	// ����ֵ: ��
	void receiveEvent(EventBusUser* hClient, int response);

	// ��ͻ�����һ����Ϣ������������⣬������ֱ�ӵ��ã�
	// rq : ��Ϣ
	// ����ֵ: ��
	void completeRequest(const ebRequest& rq);

	// ��ʼ��Ϸ����������Ϸģʽ��Ҫ��ʼ�ŻῪʼ���ú������������ء�
	// ����ֵ: �ɹ����
	bool run();

	// ���õ�ǰ EventBus ��������£��ڲ�������
	// proceedMath : ��ǰ�����£�ʵ���� MatchingUser::receiveEvent ����������ʵ����ο� match::receiveEvent
	void setMatching(MatchingUser* proceedMatch);

	// �ȴ���ǰ��Ϸ�����󷵻ء�
	// ����ֵ : ��Ϊ�������أ���Ϊ��ǰû����Ϸ�ڽ��С�
	bool waitUntilEnd();

	// ����ת��/�����¼��Ŀͻ�
	// id : �ͻ����
	// client : ��Ӧ��ʵ���� EventBusUser �ӿڵ���
	void assignClient(int id, EventBusUser* client);

	// �ڲ������̣߳���Ҫֱ�ӵ��á�
	DWORD workingThreadInternal();

	void roll();
	void finish();
};
