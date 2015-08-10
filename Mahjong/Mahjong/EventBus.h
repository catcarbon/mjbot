#pragma once

// ʵ�����¼�����

#include "SLWNetwork.h"
#include "SimpleAI.h"
#include "MemoryLeakMonitor.h"
#include "ModernMemoryAllocator.h"

class eb
{
private:
	std::default_random_engine* e1;
	int result;
	SimpleAI ai[4];
	int queueDepth = 0;
	client shu[4];
	slw net;
	DWORD threadId;

	std::queue<ebRequest> msgQueue;
	std::queue<ebEvent> evtQueue;

	bool working = true;
	CRITICAL_SECTION evt;
	evtDealer evtFunc;
	LPVOID evtParam;
	HANDLE sema;

	int clientType[4] = { 0 };
	int clientHandle[4] = { 0 };

	bool customRemoteFuncEnabled = false;
	crf customRemoteFunc = NULL;
	LPVOID crfParam;

	void shuffle_internal();
	void roll_internal();
	void roll();
	void shuffle();
	void finish();

public:
	// ��ʼ�� EventBus
	// ����ֵ: ��
	void init();

	// �ͷ� EventBus
	// ����ֵ: ��
	void deinit();

	// ����Ϊ����ģʽ���� EventBus �󶨵��ĸ� AI
	// ����ֵ: ��
	void debug();

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
	// hClient : �ͻ����
	// response : ����ֵ
	// ����ֵ: ��
	void receiveEvent(int hClient, int response);

	// ��ͻ�����һ����Ϣ������������⣬������ֱ�ӵ��ã�
	// rq : ��Ϣ
	// ����ֵ: ��
	void completeRequest(const ebRequest& rq);

	// ����Ϊ������Ϸģʽ
	// uiFunc : �����Ϣ������̡��ӿڲ� aiMessage
	// ����ֵ: ��
	void startSinglePlayer(aiFunc uiFunc);

	// ����Ϊ������Ϸģʽ������ 4 �˵Ĳ��ֻ��� ai ���롣
	// uiFunc : ���������Ϣ������̡��ӿڲ� aiMessage�����Ϊ NULL����û�б������
	// playerSocket : һ�����飬�洢��Ҿ��
	// playerCount : ����ĳ���
	// ����ֵ: ��
	void startMultiPlayer(void* uiFunc, int* playerSocket, int playerCount);

	// ��ʼ��Ϸ����������Ϸģʽ��Ҫ��ʼ�ŻῪʼ���ú������������ء�
	// evtFoo : һ�� evtDealer ���͵ĺ������ο� match::receiveEvent
	// evtP : Ҫ���ݸ��ú����ĵ�һ������
	// ����ֵ: �ɹ����
	bool run(void* evtFoo, LPVOID evtP);

	// ��ʼ��Ϸ����������Ϸģʽ��Ҫ��ʼ�ŻῪʼ���ú�����ȴ�����Ϸ�����ŷ��ء�
	// evtFoo : һ�� evtDealer ���͵ĺ������ο� match::receiveEvent
	// evtP : Ҫ���ݸ��ú����ĵ�һ������
	// ����ֵ: �ɹ����
	void runAwait(void* evtFoo, LPVOID evtP);

	// �ȴ���ǰ��Ϸ�����󷵻ء�
	// ����ֵ : ��Ϊ�������أ���Ϊ��ǰû����Ϸ�ڽ��С�
	bool waitUntilEnd();

	// �����Զ��������Ϸ��������������ʱ��Ĭ��Ϊ slw::server_send
	// scrf : һ�� evtDealer ���͵ĺ���������Ϊ NULL ʱ��ȡ����
	// param : ������Ҫ���ݵĲ�����
	void eb::setCustomRemoteFunc(void* scrf, LPVOID param);

	// �ڲ������̣߳���Ҫֱ�ӵ��á�
	DWORD WINAPI workingThreadInternal();
};
