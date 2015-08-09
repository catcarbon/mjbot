#pragma once

// ��ɽ��ع���

#include "PublicFunction.h"

class Yama
{
	private:
		void initalize_internal_func(int paiCnt);

	public:

		// ���ɽ��ָ�롣����������Ҫ���벻Ҫֱ���޸ġ���һ��������Ϊ [135]
		// ����ֵ : Ϊһ pai �����顣
		pai* getYama();

		// ��ʼ����ɽ������������������֮ǰ����ɽ�Ļ���״̬�ᱻ���á�
		// ����ֵ : ��
		void init();

		// �ͷ���ɽ��Դ��
		// ����ֵ : ��
		void finalize();

		// ��ĳ���ƶ�Ϊ�������ƣ����������޷��ܵ����Һ�����Ӱ�졣
		// id : Ҫ������������ɽ��λ��
		// ����ֵ : ��
		void open_pai(int id);

		// ������ɽ�е�������
		// id1,id2 : Ҫ������������ɽ��λ��
		// ����ֵ : �ɹ��������Ʋ��ڿɻ���Χ�ڻ�ʧ�ܡ�
		bool swap(int ID1, int ID2);

		// �����һ�������ơ�
		// receive : ����Ҫ������һ����
		// ����ֵ : �ɹ���������ɽ�Ѿ����귵�ط񣬴�ʱ receive ��ֵ�����塣
		bool next(pai* receive);

		// �����ɽ��ʣ�������������
		// ����ֵ : ���ϡ�
		int get_remaining();

		// �����һ������Ҫ�Ƶ�λ�á�
		// type : �ƵĻ�ɫ
		// fig : �Ƶ�����
		// ����ֵ : ���ظ���������ɽ�е�λ�ã��Ҳ����򷵻� -1��
		int next_swapable_pai(int type, int fig);

		// �ܡ�
		// receive : ���������
		// kandora : ��ѡ������µĸܱ���
		// ����ֵ : �Ѿ��ĸܺ��򷵻� false
		bool kang(pai* receive, pai* kandora);
};
