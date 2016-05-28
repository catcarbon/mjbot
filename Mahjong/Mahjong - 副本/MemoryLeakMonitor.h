#pragma once

// �����ĸ��ٶ�̬�ڴ��ʹ����������� VS ����Ϊ��Debug��ʱ�ŻῪ����

namespace MemoryLeakMonitor
{
	// ��Ӹ����Ӧ������һ�鶯̬�ڴ����á�
	// pointer : ���ٵ�ָ����ʼ��
	// size : ��̬�ڴ��С
	// desc : ��ָ��ָ��Ķ���Ĺ���˵��
	// ����ֵ : ��
	void addMonitor(void* pointer, int size, const char* desc);

	// ɾ�������Ӧ���ͷ�һ�鶯̬�ڴ����á�
	// pointer : ���ٵ�ָ����ʼ��
	// ����ֵ : ��
	void removeMonitor(void* pointer);

	// ��ʾ����״̬������״̬��ֱ������� std:cerr
	// ����ֵ : 0 Ϊ���и���������ɹ����ա�-1 Ϊ����δ�ܳɹ����յ���Ŀ��
	int gc();
}