#pragma once

// �߶�������ж������������֡������ںʹ����ж�

#include "PublicFunction.h"


// �ж��߶��ӡ�
// ppai : ����Ϊ 14 �������� pai ����
// nostrict : ��ѡ�����ղ����������ǲ������߶ԣ�ֻҪ������ 7 ��һ���������ƣ���������Ϊ true��
// ����ֵ : �ǻ��
bool JudgeChiitoitsu(const pai* ppai, bool* nostrict = NULL);


// �ж�����������
// ppai : ����Ϊ 14 �������� pai ����
// ����ֵ : 0 Ϊ�����ǣ�����Ϊ���ļ�ͷ������ĺꡣ
int JudgeDaisyarin(const pai* ppai);