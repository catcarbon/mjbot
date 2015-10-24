#pragma once

// ���ơ��۵��ж���

#include "PublicFunction.h"

class taj
{
	private:

		bool akari_status;

		yaku_table* current = NULL;
		yaku_table* maxresult = NULL;

		int effeci_cnt = 0;
		int tepos;
		bool hule = false;
		int tenpai_mianshu = 0;
		bool sresult[34];
		bool calculate_yaku = true;
		bool targetcalculate = false;
		int paicount;
		mentsutable mentsutachi;
		bool fulu_status;
		pai janto_now[2];
		pai* tepai;
		judgeResult* resx;
		bool yakuman = false;

		int paicnt[34];

		bool norelease = false;
		bool riichi = false, ihatsu = false, wriichii = false, haidei = false, houdei = false, rinnsyo = false, tyankan = false;
		char jyouhuun = 'N', jihuun = 'N';
		bool chiitoitsu = false, pure_chiitoitsu = false;
		bool kyuurenboudo = false, pure_kyuurenboudo = false;
		bool danyo = false, muuji = false, isou = false, laotou = false, jiisou = false;
		int dora = 0, beidora = 0;
		bool ignore_tsumo_huu = false;

		// �Ƿ�Ϊ���̣���������
		bool is_annkez(const mentsu* mc);

		// �ͷ�ĳһ�����Ӳ������µ� yaku ����
		void free_yaku(yaku* first);

		// �ͷ�ȫ�����Ӳ������µġ�yaku_table ����
		void free_yaku_table(yaku_table* first);

		// ��ʼĳ������ļ��㣨Ϊ�˸ߵ㷨���裩
		void start();
	
		// ����ģ��
		void reset();
	
		// ����ĳ������ļ���
		void finish();
	
		// ����ۣ����Ѿ�������������һ���۵�����»��е�����������Ҫ�ϲ������
		void add_yaku(int yaku_id, int yaku_point);
	
		// �����
		void calculate_huu();
	
		// ��������㣨�Ѿ��������٣�
		void calculate_basicpoint();
	
		// �ж��Ƿ�Ϊ��һɫ����
		bool judge_ruiisou(const mentsu* mc);
	
		// �ж��Ƿ�Ϊ���۾�����
		bool is_daiyaojiu(const mentsu* mc);
	
		// �ж����������Ƿ񹹳���ɫͬ˳/ͬ�̣���������˳������ν
		// ����0���ǣ�����1��Ϊ��ɫͨ˳������2��Ϊ��ɫͬ��
		int is_sansya(const mentsu* mc1, const mentsu* mc2, const mentsu* mc3); 
	
		// �ж��Ƿ�Ϊһͨ���������ӣ�˳������С����
		bool is_iitsu(const mentsu* mc1, const mentsu* mc2, const mentsu* mc3);
	
		// ���������
		void calculate();
	
		//��ͳ�����������ȫ�� finish ��
		bool show_result(judgeResult* res);

		// �жϹ�ʿ����/�ۣ������ Syanten ���µ�ͬ������
		bool specialized_tenpai_detect(judgeRequest* rpai, judgeResult* resultEx);

		// �����������
		void output_tenpai(pai machi);
	
		// ������
		void tenpai_detect_recur_2(pai* cpai, int cpcount);
	
		// ��ȸͷ
		void tenpai_detect_recur(const pai* opai, int cpcount);
	
		// ���������
		int tenpai_detect_internal(judgeRequest* rpai, judgeResult* resultEx);
	
	public:

		// �ж��ۡ����Ƶȡ�����������ο� judgeRequest �� judgeResult �����������͵�˵����
		// rpai : ����
		// resultEx : ���
		// ����ֵ : 0 Ϊ���ɹ���ɡ�
		// tenpaiDetect Ϊ����
		int tenpai_detect(const judgeRequest* rpai, judgeResult* resultEx);
		int tenpaiDetect(const judgeRequest* rpai, judgeResult* resultEx);
	
};


// �ж��߶��ӡ�
// ppai : ����Ϊ 14 �������� pai ����
// nostrict : ��ѡ�����ղ����������ǲ������߶ԣ�ֻҪ������ 7 ��һ���������ƣ���������Ϊ true��
// ����ֵ : �ǻ�񣬸��Ǻͷ�Ϊ�ϸ�ֵ�������nostrict Ϊ true������ֵΪ false���������߶Ե������
bool JudgeChiitoitsu(const pai* ppai, bool* nostrict = NULL);


// �ж�����������
// ppai : ����Ϊ 14 �������� pai ����
// ����ֵ : 0 Ϊ�����ǣ�����Ϊ���ļ�ͷ������ĺꡣ
int JudgeDaisyarin(const pai* ppai);