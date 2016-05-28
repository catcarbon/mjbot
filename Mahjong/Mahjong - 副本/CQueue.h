#pragma once

// ѭ�����У���������ģ��ά�����ݰ�
// �÷��� STL �е� queue ����

template <typename T>
class CQueue
{
public:
	// ��ʼ��ѭ�����С�
	// init : ���г���
	// start : ��ʼ ID
	// ����ֵ: ��
	void init(int init, int start);

	// �ͷ�ѭ�����С�
	~CQueue();

	// ��������һ����Ա
	// ����ֵ: ��
	void push_back(const T& data);

	// ���ָ�� ID ���ĳ�Ա
	// id : ID
	// container : ���ձ���
	// ����ֵ: ��
	void get(const int id, T* container);

private:
	int size; //��������洢�ռ���Ԫ��Ϊ��λ
	int pos;
	int startId;
	T *base; //�洢�ռ��ַ

};
