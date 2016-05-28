#pragma once
#include "stdafx.h"

// ��������

#include "PublicFunction.h"

class Syanten
{
	private:
		pai tpai2st1[20];
		pai tpai2st2[20];
		const int SyantenMaxRecur = 5;

		// �����ʿ����
		int calculateKokushiSyanten(const pai* tpai, const int paicnt);

		// �����߶�������
		int calculateChiitoitsu(const pai* tpai, const int paicnt);

		// �������
		int normalCalculate3(pai* tpai, const int paicnt, int currentMenchi);

		// ����������
		int normalCalculate2(const pai* tpai, const int paicnt, int currentMenchi);

		// ��ȸͷ
		int normalCalculate(const pai* tpai, const int paicnt);

		// �����ʿ�������ݣ��������Ѿ�����������������ʹ�ã��Ѿ�ͳһ�� taj::tenpaiDetect �У�
		bool specialized_tenpai_detect(pai* pais, int paicnt, judgeResult* resultEx);
		

	public:

		// �����������÷����� TenpaiAkariJudge ���ж�Ҫ��ö࣬�ڽ���Ҫ�ж����Ƶ���״�����Ƶ���״ʱ�Ƽ�ʹ�ñ����
		// tpai : ��Ҫ������������顣���������Ϊ���ⳤ�ȡ�3n + 1 ʱ������ǵ�ǰ������3n + 2 ʱ������Ǵ��ĳ���ƺ����С������3n ʱ��������塣
		// paicnt : ���鳤��	
		// normalonly : �������׼�ͣ��������߶��Ӻ͹�ʿ��
		// ����ֵ : (��С)��������0 ��Ϊ���ƣ�-1 ��Ϊ���ơ�
		int calculateSyanten(const pai* tpai, const int paicnt, bool normalonly = false);

		// ������Ч���š�������Ҳ���Լ����������࣬����Ч�ʵ��� taj.tenpai_detect()
		// tpai : �������顣����Ҫ����paicnt : ���鳤�ȡ�
		// ���� judgeRequest : ��ͬ tenpai_detect �ĵ��ã�mode ��Ա����Ϊ 0����������ʧ�ܡ�
		// jres : cnt �� t ��Ա�ֱ�������Ч���ŵ����������;�����Ч����
		// ����ֵ : �ɹ����
		bool kouritsuDetect(pai* tpai, const int paicnt, judgeResult* jres);
		bool kouritsuDetect(judgeRequest* jreq, judgeResult* jres);
};
