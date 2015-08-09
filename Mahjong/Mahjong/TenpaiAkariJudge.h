#pragma once

// ���ơ��۵��ж���

#include "PublicFunction.h"

class taj
{
	private:
		bool is_annkez(const mentsu* mc);

		void free_yaku(yaku* first);

		void free_yaku_table(yaku_table* first);

		void start();
	
		void reset();
	
		void finish();
	
		void add_yaku(int yaku_id, int yaku_point);
	
		void calculate_huu();
	
		void calculate_basicpoint();
	
		bool judge_ruiisou(const mentsu* mc);
	
		bool is_daiyaojiu(const mentsu* mc);
	
		int is_sansya(const mentsu* mc1, const mentsu* mc2, const mentsu* mc3); //����0���ǣ�����1��Ϊ��ɫͨ˳������2��Ϊ��ɫͬ��
	
		bool is_iitsu(const mentsu* mc1, const mentsu* mc2, const mentsu* mc3);
	
		void calculate();
	
		bool show_result(judgeResult* res);

		bool specialized_tenpai_detect(judgeRequest* rpai, judgeResult* resultEx);

		void output_tenpai(pai machi);
	
		void tenpai_detect_recur_2(pai* cpai, int cpcount);
	
		void tenpai_detect_recur(const pai* opai, int cpcount);
	
		int tenpai_detect_internal(judgeRequest* rpai, judgeResult* resultEx);
	
	public:

		// �ж��ۡ����Ƶȡ�����������ο� judgeRequest �� judgeResult �����������͵�˵����
		// rpai : ����
		// resultEx : ���
		// ����ֵ : 0 Ϊ���ɹ���ɡ�
		int tenpai_detect(const judgeRequest* rpai, judgeResult* resultEx);
	
};