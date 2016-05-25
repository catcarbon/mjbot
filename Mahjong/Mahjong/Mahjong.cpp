// Mahjong.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PublicFunction.h"
#include "SyanTen.h"
#include "TenpaiAkariJudge.h"
#include "YamaControl.h"
#include "MemoryLeakMonitor.h"
#include "EventBus.h"
#include "Matching.h"
using namespace std;

int main()
{
	Syanten engineSyanten;
	taj engineTaj;
	string paiStr;
	pai pais[20];
	int paiSafeLen = 16;

	bool simu = false;

	while (true)
	{
		paiSafeLen = 18;
		cin >> paiStr;
		if (paiStr == "exit")
			break;
		if (paiStr == "simu")
		{
			simu = true;
			break;
		}
		int paiLen = convertPaiStringPrepare(paiStr);
		if(paiLen <= 0 || paiLen > 14)
		{
			cerr << "�Ƿ������롣" << endl;
		}
		else {
			switch (paiLen % 3)
			{
				case 1:
					sort(pais, pais + paiLen, paiSort);
					if(convertPaiString(paiStr, pais, &paiSafeLen))
					{
						int k = engineSyanten.calculateSyanten(pais, paiLen);
						if (k > 0)
						{
							cout << k << " ������" << endl;
						}
						else {
							cout << "���ƣ�";
							judgeRequest jrq;
							judgeResult jrs;
							jrq.paicnt = paiLen;
							copy(pais, pais + paiLen, jrq.pais);
							jrq.mode = 0;
							engineTaj.tenpai_detect(&jrq, &jrs);
							for (int i = 0; i < jrs.cnt; i++)
							{
								cout << (int)jrs.t[i].fig << jrs.t[i].type << " ";
							}
							cout << endl;
						}
					}
					break;
				case 2:
				{
					bool failed = false;
					judgeRequest jrq;
					judgeResult jrs;
					jrq.mode = 1;
					convertPaiString(paiStr, pais, &paiSafeLen);
					jrq.tgtpai = pais[paiLen - 1];
					jrq.fulucnt = 4 - (paiLen - 2) / 3;
					string fulud;
					int fuludCnt = 4;
					pai fulu[4];
					jrq.paicnt = paiLen - 1;
					copy(pais, pais + paiLen - 1, jrq.pais);
					for (int i = 0; i < jrq.fulucnt; i++)
					{
						cin >> fulud;
						fuludCnt = convertPaiStringPrepare(fulud);
						if (fuludCnt != 3 && fuludCnt != 4)
						{
							cout << "��¶ " << i << " ���Ϸ���" << endl;
							failed = true;
							break;
						}
						int fuludCntReserved = fuludCnt;
						convertPaiString(fulud, fulu, &fuludCnt);
						if (fuludCntReserved == 4)
						{
							cout << "�������(y/n)";
							char p;
							cin >> p;
							jrq.fulus[i].type = (p == 'y') ? mentsu_KEZ_KANG_S : mentsu_KEZ_KANG_A;
							jrq.fulus[i].start = jrq.fulus[i].middle = jrq.fulus[i].last = fulu[0];
							cout << endl;
						}
						else {
							if (fulu[0] == fulu[1])
							{
								jrq.fulus[i].type = mentsu_KEZ_PON_A;
								jrq.fulus[i].start = jrq.fulus[i].middle = jrq.fulus[i].last = fulu[0];
							}
							else {
								jrq.fulus[i].type = mentsu_SHUNZ_CHI_A;
								jrq.fulus[i].start = fulu[0];
								jrq.fulus[i].middle = fulu[1];
								jrq.fulus[i].last = fulu[2];
							}
						}
					}
					if (failed && jrq.fulucnt != 0)
					{
						break;
					}
					cout << "�ٺ����(y/n)";
					char p;
					cin >> p;
					cout << endl;
					jrq.akari_status = (p == 'y') ? RON : TSUMO;
					engineTaj.tenpai_detect(&jrq, &jrs);
					cout << jrs.yakutotal << " �� " << jrs.huutotal << " �� " << jrs.basicpt << " ������" << endl;
					for (int i = 0; i < jrs.yakucnt; i++)
						cout << yakuname[jrs.yakuid[i]] << " " << jrs.pt[i] << " ��" << endl;
					break;
				}
				default:
					cerr << "�Ƿ������롣" << endl;
					break;
			}
		}
	}

	if (simu)
	{
		int p = GetTickCount();
		SimpleAI sai[4];
		match* testRun = new match();
		for (int i = 0; i < 4; i++)
			testRun->core->assignClient(i, &(sai[i]));
		testRun->core->run();
		testRun->core->receiveEvent(NULL, 1);
		testRun->core->waitUntilEnd();
		delete testRun;
		p = GetTickCount() - p;
		cout << endl << p << endl;
		cin >> paiSafeLen;
	}

    return MemoryLeakMonitor::gc();
}

