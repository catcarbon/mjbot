#pragma once
#include "PublicFunction.h"
#include "YakuProvider.h"

// �ж��߶��ӡ�
// ppai : ����Ϊ 14 �������� pai ����
// nostrict : ��ѡ�����ղ����������ǲ������߶ԣ�ֻҪ������ 7 ��һ���������ƣ���������Ϊ true��
// ����ֵ : �ǻ�񣬸��Ǻͷ�Ϊ�ϸ�ֵ�������nostrict Ϊ true������ֵΪ false���������߶Ե������
bool judgeChiitoitsu(const pai* ppai, bool* nostrict = NULL);

// �����������ж�
YAKU_CLASS_C(YakuBasicC)
YAKU_CLASS_C(YakuBasicCYM)
YAKU_CLASS_M(YakuBasicM)
YAKU_CLASS_M(YakuBasicMYM)

YAKU_CLASS_C_DEF(YakuBasicDora)
int doraCnt = 0;
YAKU_CLASS_DEF_END()