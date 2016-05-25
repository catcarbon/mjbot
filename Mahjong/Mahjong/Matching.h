#pragma once

// ���̿��ƣ������ʹ�÷�����ο����̡�

#include "PublicFunction.h"
#include "EventBus.h"
#include "YamaControl.h"
#include "SyanTen.h"
#include "TenpaiAkariJudge.h"

#define make_p1_start(x,y,z) (x)&((y)<<8)&((z)<<16)

class match : public MatchingUser
{
private:
	bool running = false;
	int changbang = 0, riichibang = 0;
	int syan_id = 1; //1= EAST 1
	int status = 0; //���ĵ�
	int oya = 0, cpos = 0;
	bool toufuu = false;
	pai tepai[4][13], current;
	char paidata[13];
	int waitPending = 4;
	int tepaicnt[4] = { 13,13,13,13 };
	int fulucnt[4] = { 0,0,0,0 };
	mentsu fulu[4][4];
	int clientStatus[4] = { -1,-1,-1,-1 };
	unsigned int clientResponse[4] = { 0,0,0,0 };
	int clientSyanTen[4] = { 9,9,9,9 };
	pai clientTenpai[4][13];
	int clientTenpaiCnt[4];
	char akarijyouhuun;
	bool norelease[4] = { false,false,false,false };
	int akariflags[4] = { 0,0,0,0 };
	const char akarijihuun[4] = { 'D','N','X','B' };
	bool furiten[4] = { false,false,false,false };
	int clientRiichi[4] = { 0,0,0,0 };
	bool clientIhatsu[4] = { false,false,false,false };
	bool waitForIncomingEvent = false;
	int whoIsWaiting = 0;
	int waitingType = 0;
	int waitingPai = 0;
	bool clientHaidei = false, clientHoudei = false, clientRinsyou = false, clientTyankan = false;
	pai paiout;
	int score[4] = { 0 };
	bool lianzhuang = false;
	bool juststart = true;
	pai paiKawa[4][32];
	int paiKawaCnt[4];

	int waitCnt = 0;

	// ���������ƺӣ�����������״̬�ȣ��������������ٺͿ����Եļ��㣬��Ҫ�Ǵ���������Լ��Դ�������������ͼ��������������
	void pushbackKawa(int pos, pai& paiout);

	// ��������״̬����ÿ�����Ʒ����仯�����������������ƣ�����ã����㵱ǰ����������������ƵĻ�����������
	void stTenpaiStatus(int pos);

	// ����ȡ��������
	int roundPoint(int rp);

	// �ȴ����������Ӧ��ÿ��һλ�����Ӧ�����ñ����̣����������Ӧ�󣬽���ʼ��һ��
	void waitEvent();

	// �����µķ�������㲥���ͻ��ˣ��������ɵ����⡣Ӧ����ÿһ�η��������仯����ã�������ֱ�ȣ�
	void scoreChange();

	// �ͻ��˷���������غϵĶ���������غ�Ϊ�����ڳԡ����ģ�����Ҫ���Ƽ����ƵĹ��̡�
	void specialTurn(unsigned int response);

	// ��ȫ���������������˱��ɺ󣬽�����Ϸ��Ҫǿ����ֹ��Ϸ����ʹ�� eb::abort() ������
	void finishMatch();

	// �յ�������ֹ��ĳһ���Ʋ���������û�б��͡����ܵȣ���ִ�еĺ�����������ִ�����Ʋ���
	void minEventFinish();

	// ����ͻ��˷����������ƿ����ԡ�����Ϣ������ͻ��˻�Ӧ�ĺ���
	void minEvent(int clientId, unsigned int response);

	// ��Ҫ����ͻ��˻�Ӧ����һ�Ҵ���ƣ�ʱ�ķ��ƹ���
	void nextTurn_state2(unsigned int response);

	// ����Ҫ����ͻ��˻�Ӧʱ�ķ��ƹ��̣�����ÿ�ֵ�һ���ƣ��ϼ��Ѿ������ˣ�
	void nextTurn_state1();

	// ׼��һ�ֵ���Ϸ�ı�Ҫ��Ѷ��������һ����
	void nextMatch();

	// ��һ�ֽ�������ã������ȴ���Ϣ���ȴ��ļҶ���ʼ��Ϸ
	void startMatchMid();

	// ������һ�����̶����غ���ã���Ҫ�������һ�̵����ݣ�֮����Զ����� nextMatch
	void startMatchMid2();

	// ����һ����ׯ��һ����ׯ����
	void startMatch();

public:
	
	// �� EventBus ���յ���Ϣ��������Ϣ������ο�Դ����
	void receiveEvent(int clientId, unsigned int response);

	match();
	~match();

	Yama yama;
	Syanten st;
	taj tajcore;
	eb evcore;
	eb* core = &evcore;
};