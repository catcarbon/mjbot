#pragma once
#define RON false
#define TSUMO true
#define is_akari(x) (((x).trait&TRAIT_AKARIPAI)==TRAIT_AKARIPAI)
#define is_aka(x) (((x).trait&TRAIT_AKA)==TRAIT_AKA)


char yakuname[64][20] = { "��ֱ","һ��","��ǰ����","����","ƽ��","һ����","����/��","����/��","����/��","����/���綫","����/������",
"����/������","����/���籱","����/�Է綫","����/�Է���","����/�Է���","����/�Է籱","����/���綫",
"����/������","����/������","����/���籱","����","����","����","�ӵ�","��ɫͬ˳","һ��","��ȫ���۾�",
"�߶���","�Զ�","����","������","��ɫͬ��","����ͷ","С��Ԫ","W��ֱ","��һ","��ȫ���۾�","������",
"��һ","��ʿ","�İ���","����Ԫ","С��ϲ","��һɫ","��һɫ","����ͷ","����","�ĸ���","���","�غ�",
"�˺�","��ʿ13��","����ϲ","�İ�����","����","����(δ����)","�Է�(δ����)","����(δ����)","������",
"����","������","δ������" };
//�������вο� ����id.txt

//paiorder �������ڴ�������ʱ�����˳�򣬱���Ӧ����һ��26��Ա�����飬
//ÿ����ĸ����M��S��P��Ӧһ�����򣬲�Ӳ�������Ҫԭ���ǿ������û�����Ľ����ض���
//������Ϊ0�ĳ�Ա�����������
int paiorder[30] = { 0,7,0,4,0,9,0,0,0,0,0,0,1,5,0,3,0,0,2,0,0,0,8,6,0,10,0,0,0,0 };
//                   B   D   F             M N   P     S       W X   Z

const int funpai[7] = { 'D','N','X','B','Z','W','F' };

// �Ƶ�����
const unsigned char TRAIT_AKA = 1;
const unsigned char TRAIT_AKARIPAI = 2;
const unsigned char TRAIT_OPEN = 4;

//�����ݽṹ��type Ϊ��ɫ����'M','S','P','D','N','X','B','W','F','Z'���⼸�֣�fig Ϊ���֣�trait Ϊ������������ȣ�
struct pai {
	unsigned char type;
	unsigned char fig;
	int trait;
};

//�������ݽṹ������һ��˫�������ڴ���������£������߲���Ҫά������ṹ������ָ�������ڲ������Ч�ʵ����õġ�
struct mentsu {
	char type;
	pai start;
	pai middle;
	pai last;
	mentsu* prev;
	mentsu* next;
};

//���ӱ��ڲ����ݽṹ��
struct mentsutable {
	mentsu* first;
	mentsu* tail;
};

//��������
enum mentsu_TYPE {
	mentsu_SHUNZ, //˳������
	mentsu_KEZ, //��������
	mentsu_SHUNZ_CHI_A, //˳�����ӣ����ϼ�
	mentsu_SHUNZ_CHI_B, //����
	mentsu_SHUNZ_CHI_C, //����
	mentsu_KEZ_PON_A, //�������ӣ����ϼ�
	mentsu_KEZ_PON_B, //�������ӣ����Լ�
	mentsu_KEZ_PON_C, //�������ӣ����¼�
	mentsu_KEZ_KANG_A, //�������ӣ����ϼ�
	mentsu_KEZ_KANG_B, //�������ӣ��ܶԼ�
	mentsu_KEZ_KANG_C, //�������ӣ����¼�
	mentsu_KEZ_KANG_S, //�������ӣ�����
};

//�����ݽṹ���ڲ���������
struct yaku {
	int yakuid;
	int pt;
	yaku* prev;
	yaku* next;
};

//�۱����ݽṹ���ڲ���������
struct yaku_table {
	yaku* first;
	yaku* tail;
	int yakutotal;
	int huutotal;
	int basicpt;
};

//���ݸ� TenpaiAkariJudge ����Ҫ����
struct judgeRequest
{
	int paicnt; //��������������Ϊ 3n+1
	pai pais[13]; //����
	int fulucnt; //��¶���� 0 or 1 or 2 or 3 or 4
	mentsu fulus[4]; //��¶ mentsu[0~fulucnt] �ýṹ�е� prev / next ֵû������
	int mode; //���ģʽ 0Ϊ���������� 1Ϊ�����ۼ�⣬Ϊ0ʱ������Ĳ���������
	pai tgtpai; //�����ۼ��ʱ ���˵�������
	bool akari_status; //�������� ����/�ٺ�  TSUMO or RON
	bool norelease; //����˺Ϳ��Գ��������˻�û����ƣ�֮ǰ�����ƣ�
	char jyouhuun; //���� 'D' or 'N' or 'X' or 'B'������Ϊ '\0' �����ж�
	char jihuun; //�Է� 'D' or 'N' or 'X' or 'B'������Ϊ '\0' �����ж�
	int flags; //һ���߼�ֵ��flags&1 ��ֱ flags&2 W��ֱ flags&4 һ�� flags&8 ���� flags&16 �ӵ� flags&32 ���� flags&64 ����
	int doracnt; //����DORAָʾ��
	pai doras[5]; //DORAָʾ�� pai[0~doracnt]
	int uracnt; //����URAָʾ��
	pai uras[5]; //URAָʾ�� pai[0~uracnt]
};

//TenpaiAkariJudge ģ�鴫�ݻصĽṹ
struct judgeResult
{
	int cnt; //���������ж�ģʽ�£�Ϊ�����Ƶ���������
	pai t[20]; //pai[cnt]��������
	int yakucnt; //�������ж���ģʽ�£��۵�����
	int yakutotal; //�ܷ���
	int huutotal; //����
	int basicpt; //������
	int yakuid[16]; //�۵�ID
	int pt[16]; //��Ӧ�۵ķ���
};

// ��������

// �Ƚ���������ͬ/��ͬ
// ���Ƚ�ֻ�Ƚϻ�ɫ�����֣������Ƿ�Ϊ��
inline bool operator == (const pai& a, const pai& b);
inline bool operator != (const pai& a, const pai& b);

// �Ƚ���������ͬ/��ͬ (����)
// ���ȽϱȽϻ�ɫ�����֣����Ƚϳ������Ƿ���ͬ
inline bool compare_pai_aka(const pai& a, const pai& b);

// �Ƚ���������ͬ/��ͬ (ȫͬ)
// ���Ƚ�Ҫ��������ȫ�ȣ�����ɫ�������⣬trait ҲҪһ��
inline bool compare_pai_same(const pai& a, const pai& b);

// ����Ƶ���š�1M-9M��0-8��1S-9S��9-17��1P-9P��18-26��֮������Ϊ���������׷��У�27-33��
// �������������Ƿ�Ϊ�౦�ơ�
// ��������Ҫ�� TenpaiAkariJudge ģ���ڲ�ʵ�á��ⲿʹ�ã����硢���棩�뾡��ʹ�� retrieveID3
// cpai : ��
// ����ֵ : �Ƶ����
int retrieveID(const pai& cpai);

// ����Ƶ���š����� retrieveID + 1����������һ��������һ��
// �������������Ƿ�Ϊ�౦�ơ�
// ��������Ҫ�����ⲿ���̣�����桢����ȣ���Ϊ 0 ���ⲿ�����п����б�����壩
// cpai : ��
// ����ֵ : �Ƶ����
int retrieveID3(const pai& cpai);

// ����Ƶ���š�
// �����������Ƿ�Ϊ�౦�ƣ��Ƕ� retrieveID3 ��������չ��retrieveID3 �ķ�ΧΪ 1-33��
// �ڱ������У���5M��5S��5P�ֱ�Ϊ 34, 35, 36
// cpai : ��
// ����ֵ : �Ƶ����
int retrieveID2(const pai& cpai);

//bool retrievePai(pai* pai, int id);

// ͨ����Ż���ơ�����ŵ������ retrieveID2 �������ص���ͬ����ΧΪ 1-36
// pai : ���յķ���ֵ
// id : ��Ҫת���� id
// ����ֵ : ����� id �Ƿ���Ч
bool retrievePai3(pai* pai, int id);

// ȡ�ñ��ƣ���ָʾ����Чʱ�����δ����
// show : ����ָʾ��
// result : ָ������ָ��
// ����ֵ : ��
void doraNext(const pai& show, pai* result);

// ������������С�ڵ��ںţ������� sort (STL)�������ԭ���ǣ�ͬɫ��С���󣻲�ͬɫ�� paiorder �����ֵָ����
// ʵ����ֱ������� ID ����Ҳ�ǿ��Եģ�Ҳ���� return retrieveID(a)<retrieveID(b); ����������±ȽϷ����Ǵ���Ч�ʵĿ���
// a : �� 1
// b : �� 2
// ����ֵ : С�ڵ���Ϊ�棬����Ϊ��
bool paiSort(const pai& a, const pai& b);

// �ж�һ�������ǲ��ǿ��ӣ������ܣ�
// mc : ���ӵ�ָ��
// ����ֵ : ����
bool isKez(const mentsu* mc);

// �ж�һ�������ǲ��Ǹܣ��������ܣ�
// mc : ���ӵ�ָ��
// ����ֵ : ����
bool isKangz(const mentsu* mc);

// ��������ҵ����λ�ã��������Ϊ��ʱ�� 0-4
// self : �Լ�λ��
// other : ����λ��
// ����ֵ : 0�¼� 1�Լ� 2�ϼ� -1���� 
int getRelativePosition(int self, int other);