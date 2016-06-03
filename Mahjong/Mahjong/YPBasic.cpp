#include "stdafx.h"
#include "PublicFunction.h"
#include "YakuProvider.h"
#include "YPBasic.h"

#define TOKEN_7TOITSU "7TOITSU"

bool judgeChiitoitsu(const pai* ppai, bool* nostrict)
{
	if (ppai[0] == ppai[1] && ppai[2] == ppai[3] && ppai[4] == ppai[5] && ppai[6] == ppai[7] && \
		ppai[8] == ppai[9] && ppai[10] == ppai[11] && ppai[12] == ppai[13])
	{
		if (nostrict != NULL)
			*nostrict = true;
		if (ppai[0] != ppai[2] && ppai[2] != ppai[4] && ppai[4] != ppai[6] && \
			ppai[6] != ppai[8] && ppai[8] != ppai[10] && ppai[10] != ppai[12])
			return true;
	}
	return false;
}

// ������ɫ��

YAKU_DEFINE(YakuBasicShapeYM, yakuType::colorLike, yakuTrait::yakumanLike | yakuTrait::shapeYaku)
YAKU_SUBNAME_BEGIN(YakuBasicShapeYM)
YAKU_SUBNAME(1, "��ʿ��˫")
YAKU_SUBNAME(2, "��ʿ��˫ʮ����")
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_C(YakuBasicShapeYM)
{
	SUBYAKU("��ʿ��˫(ʮ����)")
	{
		if (YAKU_MENZEN && paicnt == 14)
		{
			int cnt1[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			int twoId = -1;
			bool valid = true;
			std::for_each(pais, pais + paicnt, [&](auto& p) {
				valid = valid && isYaotyuu(p);
				if (isPaiAkari(p))
					twoId = getYaotyuuId(p);
				else
					cnt1[getYaotyuuId(p)]++;
			});
			if (valid)
			{
				auto singlePai = std::count(cnt1, cnt1 + 13, 1);
				if (singlePai == 13)
				{
					YAKU_ADD(2, YAKU_REDUCED(26));
				}
				else if (singlePai == 11)
				{
					cnt1[twoId]++;
					auto it = std::find(cnt1, cnt1 + 13, 2);
					if (it != cnt1 + 13)
					{
						(*it)--;
						if (13 == std::count(cnt1, cnt1 + 13, 1))
							YAKU_ADD(1, 13);
					}
				}
			}
		}
	}
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicShape, yakuType::colorLike, yakuTrait::yakumanLike | yakuTrait::shapeYaku)
YAKU_SUBNAME_BEGIN(YakuBasicShape)
YAKU_SUBNAME(1, "�߶���")
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_C(YakuBasicShape)
{
	SUBYAKU("�߶���")
	{
		if (paicnt == 14)
			if (judgeChiitoitsu(pais))
				YAKU_ADD(1, 2);
	}
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicCYM, yakuType::colorLike, yakuTrait::yakumanLike)

YAKU_SUBNAME_BEGIN(YakuBasicCYM)
YAKU_SUBNAME(0, "��һɫ")
YAKU_SUBNAME(1, "��ʿ��˫")
YAKU_SUBNAME(2, "��ʿ��˫ʮ����")
YAKU_SUBNAME(3, "��������")
YAKU_SUBNAME(4, "������������")

YAKU_SUBNAME(5, "���")
YAKU_SUBNAME(6, "�غ�")
YAKU_SUBNAME(7, "�˺�")
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_C(YakuBasicCYM)
{

	SUBYAKU("����˺�")
	{
		if (YAKU_CURRENT.norelease)
		{
			if (TSUMO == YAKU_CURRENT.akariStatus)
			{
				YAKU_ADD_IF(YAKU_CURRENT.jihuun == 'D', 5, 13);
				YAKU_ADD_IF(YAKU_CURRENT.jihuun != 'D', 6, 13);
			}
			else {
				YAKU_ADD(7, 13);
			}
		}
	}
	SUBYAKU("��һɫ")
	{
		if (std::any_of(pais, pais + paicnt, isJi))
			YAKU_ADD(0, 13);
	}
	SUBYAKU("(����)��������")
	{
		if (YAKU_MENZEN && paicnt == 14)
		{

			int num_cnt[10] = { 0,0,0,0,0,0,0,0,0,0 };
			int akari = 0;
			bool valid = true;
			std::for_each(pais, pais + paicnt, [&](auto& p) {
				valid = valid && (p.type == pais[0].type);
				if (isPaiAkari(p))
					akari = p.fig;
				else
					num_cnt[p.fig]++;
			});
			if (valid)
			{
				if (num_cnt[1] == 3 && num_cnt[9] == 3 && std::count(num_cnt + 2, num_cnt + 8, 1) == 7)
				{
					YAKU_ADD(4, YAKU_REDUCED(26));
				}
				else {
					bool kyuurenboudo = false;
					num_cnt[akari] ++;
					for (int i = 1; i <= 9; i++)
					{
						num_cnt[i]--;
						if (num_cnt[1] == 3 &&
							num_cnt[2] == 1 &&
							num_cnt[3] == 1 &&
							num_cnt[4] == 1 &&
							num_cnt[5] == 1 &&
							num_cnt[6] == 1 &&
							num_cnt[7] == 1 &&
							num_cnt[8] == 1 &&
							num_cnt[9] == 3)
						{
							kyuurenboudo = true;
							break;
						}
						num_cnt[i]++;
					}
					if (kyuurenboudo)
						YAKU_ADD(3, 13);
				}
			}
		}
	}

	SUBYAKU("��ʿ��˫(ʮ����)")
	{
		if (YAKU_MENZEN && paicnt == 14)
		{
			int cnt1[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			int twoId = -1;
			bool valid = true;
			std::for_each(pais, pais + paicnt, [&](auto& p) {
				valid = valid && isYaotyuu(p);
				if (isPaiAkari(p))
					twoId = getYaotyuuId(p);
				else
					cnt1[getYaotyuuId(p)]++;
			});
			if (valid)
			{
				auto singlePai = std::count(cnt1, cnt1 + 13, 1);
				if (singlePai == 13)
				{
					YAKU_ADD(2, YAKU_REDUCED(26));
				}
				else if (singlePai == 11)
				{
					cnt1[twoId]++;
					auto it = std::find(cnt1, cnt1 + 13, 2);
					if (it != cnt1 + 13)
					{
						(*it)--;
						if (13 == std::count(cnt1, cnt1 + 13, 1))
							YAKU_ADD(1, 13);
					}
				}
			}
		}
	}
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicC, yakuType::colorLike, 0)

YAKU_SUBNAME_BEGIN(YakuBasicC)
YAKU_SUBNAME(0, "���۾�")
YAKU_SUBNAME(1, "��һɫ")
YAKU_SUBNAME(2, "��һɫ")
YAKU_SUBNAME(4, "����ͷ")

YAKU_SUBNAME(5, "��ֱ")
YAKU_SUBNAME(6, "W��ֱ")
YAKU_SUBNAME(7, "һ��")
YAKU_SUBNAME(8, "��ǰ����")
YAKU_SUBNAME(9, "���Ͽ���")
YAKU_SUBNAME(10, "����")
YAKU_SUBNAME(11, "��������")
YAKU_SUBNAME(12, "�ӵ�����")
YAKU_SUBNAME_END()

// ��ϵ���ԣ�Ҫ���ۺ���״���ֿ���

YAKU_JUDGE_BEGIN_C(YakuBasicC)
{
	//һ���߼�ֵ��flags&1 ��ֱ flags&2 W��ֱ flags&4 һ�� flags&8 ���� flags&16 �ӵ� flags&32 ���� flags&64 ����
	SUBYAKU("������")
	{
		YAKU_ADD_IF((YAKU_CURRENT.flags & 1) != 0, 5, 1);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 2) != 0, 6, 2);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 4) != 0, 7, 1);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 1) != 0 && YAKU_CURRENT.akariStatus == TSUMO, 8, 1);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 64) != 0, 10, 1);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 8) != 0, 11, 1);
		YAKU_ADD_IF((YAKU_CURRENT.flags & 16) != 0, 12, 1);

		if ((YAKU_CURRENT.flags & 32) != 0)
		{
			YAKU_SET("ignoreTsumoFu");
			YAKU_ADD(9, 1);
		}
	}

	SUBYAKU("���۾�")
		YAKU_ADD_IF(!std::any_of(pais, pais + paicnt, isYaotyuu), 0, 1);
	SUBYAKU("Ⱦ��")
	{
		char type = '\0';
		bool noji = false, valid = true;
		for (int i = 0; i < paicnt; i++)
		{
			if (isJi(pais[i]))
				noji = true;
			else
			{
				if (type == '\0')
				{
					type = pais[i].type;
				}
				else {
					if (type != pais[i].type)
					{
						valid = false;
						break;
					}
				}
			}
		}
		if (valid && type != '\0')
		{
			if (noji)
				YAKU_ADD(2, YAKU_REDUCED(6));
			else
				YAKU_ADD(1, YAKU_REDUCED(3));
		}
	}
	SUBYAKU("����ͷ")
		YAKU_ADD_IF(std::all_of(pais, pais + paicnt, isYaotyuu), 4, 2);
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicM, yakuType::mentsuLike, 0)

YAKU_SUBNAME_BEGIN(YakuBasicM)
YAKU_SUBNAME(0, "��Ԫ��")
YAKU_SUBNAME(1, "С��Ԫ")
YAKU_SUBNAME(2, "ƽ��")
YAKU_SUBNAME(3, "һ��ͨ��")
YAKU_SUBNAME(4, "һ����")
YAKU_SUBNAME(5, "������")
YAKU_SUBNAME(6, "��ȫ���۾�")
YAKU_SUBNAME(7, "��ȫ���۾�")
YAKU_SUBNAME(8, "����")
YAKU_SUBNAME(9, "��ɫͬ˳")
YAKU_SUBNAME(10, "��ɫͬ��")
YAKU_SUBNAME(11, "�ԶԺ�")
YAKU_SUBNAME(12, "������")
YAKU_SUBNAME(13, "������")
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_M(YakuBasicM)
{
	SUBYAKU("����")
	{
		int fpYaku = 0;
		std::for_each(mentsus, mentsus + mentsucnt, [&](auto& mt) {
			if (isKez2(mt))
			{
				if (mt.start.type == YAKU_CURRENT.jyouhuun)
					fpYaku++;
				if (mt.start.type == YAKU_CURRENT.jihuun)
					fpYaku++;
			}
		});
		YAKU_ADD_IF(fpYaku != 0, 8, fpYaku);
	}
	SUBYAKU("���ơ�С��Ԫ")
	{
		auto yp = std::count_if(mentsus, mentsus + mentsucnt, [](auto& mt) {return isSanyuan(mt.start); });
		YAKU_ADD_IF(yp > 0, 0, (int)yp);
		YAKU_ADD_IF(yp == 2 && isSanyuan(janto[0]), 1, 2);
	}
	SUBYAKU("ƽ��")
	{
		if (YAKU_MENZEN && isNotYakuPai(janto[0]) && !isPaiAkari(janto[0]) && !isPaiAkari(janto[1]) && \
			std::none_of(mentsus, mentsus + mentsucnt, [&](auto& mt) -> bool {
			if (mt.type != mentsu_SHUNZ)
				return true;
			if (isMentsuAkari(mt))
			{
				if (isPaiAkari(mt.middle))
					return true;
				if (isPaiAkari(mt.start) && mt.start.fig == 7)
					return true;
				if (isPaiAkari(mt.last) && mt.last.fig == 3)
					return true;
			}
			return false;
		}))
		{
			YAKU_ADD(2, 1);
			YAKU_SET("ignoreTsumoFu");
		}
	}
	SUBYAKU("һ��")
	{
		static auto isItsuu = [](const mentsu& mc1, const mentsu& mc2, const mentsu& mc3) -> bool {
			if (isShunz2(mc1) && isShunz2(mc2) && isShunz2(mc3))
				if (mc1.start.type == mc2.start.type == mc3.start.type)
					if (mc1.start.fig == 1 && mc2.start.fig == 4 && mc3.start.fig == 7)
						return true;
			return false;
		};
		YAKU_ADD_IF(YAKU_SELECT3(isItsuu), 3, YAKU_REDUCED(2));
	}
	SUBYAKU("һ������")
	{
		if (YAKU_MENZEN && mentsucnt == 4)
		{
			if ((mentsus[0] == mentsus[1] && mentsus[2] == mentsus[3] && mentsus[0].type == mentsu_SHUNZ && mentsus[2].type == mentsu_SHUNZ) || \
				(mentsus[0] == mentsus[2] && mentsus[1] == mentsus[3] && mentsus[0].type == mentsu_SHUNZ && mentsus[1].type == mentsu_SHUNZ))
			{
				YAKU_ADD(5, 3);
			}
			else {
				if ((mentsus[0] == mentsus[1] && mentsus[0].type == mentsu_SHUNZ) || \
					(mentsus[1] == mentsus[2] && mentsus[1].type == mentsu_SHUNZ) || \
					(mentsus[2] == mentsus[3] && mentsus[2].type == mentsu_SHUNZ))
					YAKU_ADD(4, 1);
			}
		}
	}
	SUBYAKU("���۾�")
	{
		bool hasJi = isJi(janto[0])      || std::any_of(mentsus, mentsus + mentsucnt, [](const mentsu& mt) {return isJi(mt.start); });
		bool isYao = isYaotyuu(janto[0]) || std::any_of(mentsus, mentsus + mentsucnt, [](const mentsu& mt) {return (mt.start.fig == 1) || (mt.last.fig == 9); });
		YAKU_ADD_IF(isYao &  hasJi, 6, YAKU_REDUCED(2));
		YAKU_ADD_IF(isYao & !hasJi, 7, YAKU_REDUCED(3));
	}
	SUBYAKU("��ɫͬ˳/��ɫͬ��")
	{
		static auto isSansya = [](const mentsu& mc1, const mentsu& mc2, const mentsu& mc3) -> int {
			bool sansya = false;
			if (mc1.start.type == 'M' && mc2.start.type == 'S' && mc3.start.type == 'P') sansya = true;
			if (mc1.start.type == 'M' && mc2.start.type == 'P' && mc3.start.type == 'S') sansya = true;
			if (mc1.start.type == 'S' && mc2.start.type == 'M' && mc3.start.type == 'P') sansya = true;
			if (mc1.start.type == 'S' && mc2.start.type == 'P' && mc3.start.type == 'M') sansya = true;
			if (mc1.start.type == 'P' && mc2.start.type == 'S' && mc3.start.type == 'M') sansya = true;
			if (mc1.start.type == 'P' && mc2.start.type == 'M' && mc3.start.type == 'S') sansya = true;
			if (!sansya) return 0;
			if (mc1.start.fig != mc2.start.fig || mc2.start.fig != mc3.start.fig || mc1.start.fig != mc3.start.fig) return 0;
			if (isSameType(mc1, mc2) && isSameType(mc2, mc3))
				return isShunz2(mc1) ? 1 : 2;
			return 0;
		};
		static auto dealtWithSansya = [&](const mentsu& mc1, const mentsu& mc2, const mentsu& mc3) -> bool {
			int result = isSansya(mc1, mc2, mc3);
			switch (result)
			{
			case 1:
				YAKU_ADD(9, YAKU_REDUCED(2));
				return true;
				break;
			case 2:
				YAKU_ADD(9, 2);
				return true;
				break;
			}
			return false;
		};
		YAKU_SELECT3(dealtWithSansya);
	}
	SUBYAKU("�ԶԺ�")
		YAKU_ADD_IF(std::all_of(mentsus, mentsus + mentsucnt, isKez2), 11, 2);
	SUBYAKU("������")
		YAKU_ADD_IF(std::count_if(mentsus, mentsus + mentsucnt, [=](auto& mt) {return isAnke(mt); }) == 3, 13, 2);
	SUBYAKU("������")
		YAKU_ADD_IF(std::count_if(mentsus, mentsus + mentsucnt, isKangz2) == 3, 13, 2);
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicMYM, yakuType::mentsuLike, yakuTrait::yakumanLike)

YAKU_SUBNAME_BEGIN(YakuBasicMYM)
YAKU_SUBNAME(0, "����Ԫ")
YAKU_SUBNAME(1, "С��ϲ")
YAKU_SUBNAME(2, "����ϲ")
YAKU_SUBNAME(3, "��һɫ")
YAKU_SUBNAME(4, "����ͷ")
YAKU_SUBNAME(5, "�İ���")
YAKU_SUBNAME(6, "�İ��̵���")
YAKU_SUBNAME(7, "�ĸ���")
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_M(YakuBasicMYM)
{
	SUBYAKU("����Ԫ")
		YAKU_ADD_IF(3 == std::count_if(mentsus, mentsus + mentsucnt, [](auto& mt) {return isSanyuan(mt.start); }), 0, 13);
	SUBYAKU("��С��ϲ")
	{
		auto fengpai = std::count_if(mentsus, mentsus + mentsucnt, [](auto& mt) {return isFeng(mt.start); });
		if (fengpai == 4)
			YAKU_ADD(2, YAKU_REDUCED(26));
		else
			YAKU_ADD_IF(isFeng(janto[0]), 1, 13);
	}
	SUBYAKU("��һɫ")
		YAKU_ADD_IF(isGreen(janto[0]) && std::all_of(mentsus, mentsus + mentsucnt, [](auto& mt) {
		    return isGreen(mt.start) && (isKez2(mt) || mt.start.fig == 2);
		}), 3, 13);
	SUBYAKU("����ͷ")
		YAKU_ADD_IF(isYaotyuu2(janto[0]) && std::all_of(mentsus, mentsus + mentsucnt, [](auto& mt) {return isKez2(mt) && isYaotyuu2(mt.start); }), 4, 13);
	SUBYAKU("�İ���(��)")
	{
		bool danqi = isPaiAkari(janto[0]) || isPaiAkari(janto[1]);
		bool sianke = std::all_of(mentsus, mentsus + mentsucnt, [&](auto& mt) {return isAnke(mt); });
		if (sianke)
		{
			YAKU_ADD_IF(!danqi, 5, 13);
			YAKU_ADD_IF( danqi, 6, YAKU_REDUCED(26));
		}
	}
	SUBYAKU("�ĸ���")
		YAKU_ADD_IF(std::count_if(mentsus, mentsus + mentsucnt, isKangz2) == 4, 7, 13);
}
YAKU_JUDGE_END()

YAKU_DEFINE(YakuBasicDora, yakuType::colorLike, yakuTrait::doraLike)

YAKU_SUBNAME_BEGIN(YakuBasicDora)
YAKU_SUBNAME(0, "����")
YAKU_SUBNAME(1, "������") // not used
YAKU_SUBNAME_END()

YAKU_JUDGE_BEGIN_C(YakuBasicDora)
{
	int doraCnt = YAKU_GET("dora");
	YAKU_ADD_IF(doraCnt != 0, 0, doraCnt);
}
YAKU_JUDGE_END()

void SysPtProvider::judgeFu(const pai * pais, int paicnt, const mentsu * mentsus, int mentsucnt, const pai * janto, int jantocnt, yakuTable* current, void * yakuProvider)
{
	bool fulu = false;
	if (mentsus == NULL)
	{
		current->huutotal = 25;
		return;
	}
	current->huutotal = 20;
	for (auto next = (mentsus + 0); next != (mentsus + mentsucnt); next++)
	{
		if (isMentsuAkari(*next))
			if (next->type == mentsu_SHUNZ)
			{
				if ((((next->middle).trait)&TRAIT_AKARIPAI) == TRAIT_AKARIPAI)
					current->huutotal += 2;
				if ((((next->start).trait)&TRAIT_AKARIPAI) == TRAIT_AKARIPAI && (next->start).fig == 7)
					current->huutotal += 2;
				if ((((next->last).trait)&TRAIT_AKARIPAI) == TRAIT_AKARIPAI && (next->last).fig == 3)
					current->huutotal += 2;
			}
		bool ann = true;
		switch (next->type)
		{
		case mentsu_KEZ_PON_A:
		case mentsu_KEZ_PON_B:
		case mentsu_KEZ_PON_C:
			fulu = true;
			ann = false;
		case mentsu_KEZ:
			if (YAKU_CURRENT.akariStatus == RON)
				if (isMentsuAkari(*next))
					ann = false;
			if ((next->start).fig == 1 || (next->start).fig == 9)
				if (ann)
					current->huutotal += 8;
				else
					current->huutotal += 4;
			else if (ann)
				current->huutotal += 4;
			else
				current->huutotal += 2;
			break;
		case mentsu_KEZ_KANG_S:
			if ((next->start).fig == 1 || (next->start).fig == 9)
				current->huutotal += 32;
			else
				current->huutotal += 16;
			break;
		case mentsu_KEZ_KANG_A:
		case mentsu_KEZ_KANG_B:
		case mentsu_KEZ_KANG_C:
			fulu = true;
			if ((next->start).fig == 1 || (next->start).fig == 9)
				current->huutotal += 16;
			else
				current->huutotal += 8;
			break;
		case mentsu_SHUNZ:
			break;
		default:
			fulu = true;
			break;
		}
	}
	if (janto[0].type == YAKU_CURRENT.jyouhuun || janto[0].type == YAKU_CURRENT.jihuun || isSanyuan(janto[0]))
		current->huutotal += 2;
	if (isPaiAkari(janto[0]) || isPaiAkari(janto[1]))
		current->huutotal += 2;
	if (!fulu && YAKU_CURRENT.akariStatus == RON)
		current->huutotal += 10;
	if (!YAKU_GET("ignoreTsumoFu") && YAKU_CURRENT.akariStatus == TSUMO)
		current->huutotal += 2;
	if (current->yakutotal == 1 && current->huutotal == 20)
		current->huutotal = 30;
	if (fulu && YAKU_CURRENT.akariStatus == RON && current->huutotal == 20)
		current->huutotal = 30;
	if (current->huutotal % 10 != 0)
		current->huutotal = 10 * (1 + (current->huutotal) / 10);
}

bool SysPtProvider::judgePt(const pai* pais, int paicnt, const mentsu* mentsus, int mentsucnt, const pai* janto, int jantocnt, yakuTable* yTable, void* yakuProvider)
{
	yakuTable* current = yTable;
	if (yTable->yakutotal != 0)
		judgeFu(pais, paicnt, mentsus, mentsucnt, janto, jantocnt, yTable, yakuProvider);
	switch (yTable->yakutotal)
	{
	case 0:
		current->basicpt = 0;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		current->basicpt = current->huutotal * 1 << (current->yakutotal + 2);
		if (current->basicpt >= 2000)
			current->basicpt = 2000;
		break;
	case 5:
		current->basicpt = 2000;
		break;
	case 6:
	case 7:
		current->basicpt = 3000;
		break;
	case 8:
	case 9:
	case 10:
		current->basicpt = 4000;
		break;
	case 11:
	case 12:
		current->basicpt = 6000;
		break;
	case 13:
		current->basicpt = 8000;
		break;
	default:
		if (current->yakutotal > 13)
			current->basicpt = (current->yakutotal) / 13 * 8000;
		break;
	}
	return false;
}
