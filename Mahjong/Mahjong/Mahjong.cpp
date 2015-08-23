// Mahjong.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PublicFunction.h"
#include "SyanTen.h"
#include "TenpaiAkariJudge.h"
#include "YamaControl.h"
#include "MemoryLeakMonitor.h"
using namespace std;

int main()
{
	Syanten engineSyanten;
	taj engineTaj;
	string paiStr;
	pai pais[20];
	int paiSafeLen = 16;

	while (true)
	{
		paiSafeLen = 18;
		cin >> paiStr;
		if (paiStr == "exit")
			break;
		int paiLen = convertPaiStringPrepare(paiStr);
		if(paiLen <= 0 || paiLen > 14)
		{
			cerr << "�Ƿ������롣" << endl;
		}
		else {
			switch (paiLen % 3)
			{
				case 1:
					if(convertPaiString(paiStr, pais, &paiSafeLen))
					{
						int k = engineSyanten.calculateSyanten(pais, paiLen);
						if (k > 0)
						{
							cout << k << " ������" << endl;
						}
						else {
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
					//���жϻ�ûд
					break;
				default:
					cerr << "�Ƿ������롣" << endl;
			}
		}
	}
    return MemoryLeakMonitor::gc();
}

