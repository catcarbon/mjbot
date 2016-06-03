#pragma once
#include "PublicFunction.h"
#include "YakuProvider.h"

// �ж��߶��ӡ�
// ppai : ����Ϊ 14 �������� pai ����
// nostrict : ��ѡ�����ղ����������ǲ������߶ԣ�ֻҪ������ 7 ��һ���������ƣ���������Ϊ true��
// ����ֵ : �ǻ�񣬸��Ǻͷ�Ϊ�ϸ�ֵ�������nostrict Ϊ true������ֵΪ false���������߶Ե������
bool judgeChiitoitsu(const pai* ppai, bool* nostrict = NULL);

class SysPtProvider : public BasicPtProviderBase
{
public:
	void judgeFu(const pai* pais, int paicnt, const mentsu* mentsus, int mentsucnt, const pai* janto, int jantocnt, yakuTable* yTable, void* yakuProvider);
	bool judgePt(const pai* pais, int paicnt, const mentsu* mentsus, int mentsucnt, const pai* janto, int jantocnt, yakuTable* yTable, void* yakuProvider) override;
};

// �����������ж�
YAKU_CLASS_C(YakuBasicShape)
YAKU_CLASS_C(YakuBasicShapeYM)

YAKU_CLASS_C(YakuBasicC)
YAKU_CLASS_C(YakuBasicCYM)
YAKU_CLASS_M(YakuBasicM)
YAKU_CLASS_M(YakuBasicMYM)

YAKU_CLASS_C(YakuBasicDora)