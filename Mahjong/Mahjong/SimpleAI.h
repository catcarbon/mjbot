#pragma once

// ʵ����һ���򵥵Ĵ���Ч AI

#include "SyanTen.h"
#include "PublicFunction.h"

class SimpleAI
{
	public:
		// ��Ϣ�������
		// �ο� EventBus �еĵ��ýӿڹ淶
		int aiMessage(unsigned char msgType, int par1, int par2, bool* hasReturn);

	private:
		int cid;
		int ciid = -1;
		char jyouhuun;
		char jihuun;
		int pcnt = 13;
		pai lastpai;
		int nSyanten;
		bool riichi = false;
		pai tepai2[14];
		int pSyanten[13];
		int xunshu = 0;
		Syanten st;
		int dbg = 0;
		pai tepai[13];
		int tickCount = 0, cnt = 0;
		int uCanSee[35];


		int calcJinZhang(const pai* tepai, const int tepaicnt, const int nSyanten);
		void outputDebug(char p);
		int toID3(int p);
};
