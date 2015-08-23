#pragma once

// ��Ҫ������һЩ���ù������������͡�

#define RON false
#define TSUMO true
#define is_akari(x) (((x).trait&TRAIT_AKARIPAI)==TRAIT_AKARIPAI)
#define is_aka(x) (((x).trait&TRAIT_AKA)==TRAIT_AKA)
#define compare_pai_thesame compare_pai_same


#define Daisyarin 1
#define Daichikurin 2
#define Daisuurin 3

#define KOKUSHIMUSOU 1
#define KOKUSHIMUSOU_JUUSANMENMACHI 2

const int yaotrans[13] = { 1,9,10,18,19,27,28,29,30,31,32,33,34 };

const char yakuname[64][20] = { "��ֱ","һ��","��ǰ����","����","ƽ��","һ����","����/��","����/��","����/��","����/���綫","����/������",
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
const int paiorder[30] = { 0,7,0,4,0,9,0,0,0,0,0,0,1,5,0,3,0,0,2,0,0,0,8,6,0,10,0,0,0,0 };
//                   B   D   F             M N   P     S       W X   Z

const int funpai[7] = { 'D','N','X','B','W','F','Z' };

// �Ƶ�����
#define TRAIT_AKA 1
#define TRAIT_AKARIPAI 2
#define TRAIT_OPEN 4

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
	pai pais[13]; //���ƣ����ж���ʱ��Ӧ���� paiSort ���������������
	int mode; //���ģʽ 0Ϊ���������� 1Ϊ�����ۼ�⣬Ϊ0ʱ������Ĳ���������
	int fulucnt = 0; //��¶���� 0 or 1 or 2 or 3 or 4
	mentsu fulus[4]; //��¶ mentsu[0~fulucnt] �ýṹ�е� prev / next ֵû������
	pai tgtpai; //�����ۼ��ʱ ���˵�������
	bool akari_status; //�������� ����/�ٺ�  TSUMO or RON
	bool norelease = false; //����˺Ϳ��Գ��������˻�û����ƣ�֮ǰ�����ƣ�
	char jyouhuun = '\0'; //���� 'D' or 'N' or 'X' or 'B'������Ϊ '\0' �����ж�
	char jihuun = '\0'; //�Է� 'D' or 'N' or 'X' or 'B'������Ϊ '\0' �����ж�
	int flags = 0; //һ���߼�ֵ��flags&1 ��ֱ flags&2 W��ֱ flags&4 һ�� flags&8 ���� flags&16 �ӵ� flags&32 ���� flags&64 ����
	int doracnt = 0; //����DORA
};

//TenpaiAkariJudge ģ�鴫�ݻصĽṹ
struct judgeResult
{
	int cnt = 0; //���������ж�ģʽ�£�Ϊ�����Ƶ���������
	pai t[20]; //pai[cnt]��������
	int yakucnt = 0; //�������ж���ģʽ�£��۵�����
	int yakutotal = 0; //�ܷ���
	int huutotal = 0; //����
	int basicpt = 0; //������
	int yakuid[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //�۵�ID
	int pt[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //��Ӧ�۵ķ���
};

//��������ݰ�����
struct Packet
{
	unsigned char packetLength; //������, �������ֽ�, Ϊ0xFF ʱΪ������, ����֮���������ݣ�0xFE ʱΪ���ư�, ���鸶
	unsigned int crc; //У���, �Ѹó�Ա֮���ÿһ���ֽڴ�(unsigned int)0��ʼ���
	unsigned int id; //��id, �Է��������͵����ְ���ʼ��1��, �ͻ��˺ͷ�����ѭ����һ, �����ͻ��˻Ự�б��ֵ�������
	unsigned char uType; //��Ϣ����, ��interface
	unsigned int p1; //����1, ��interface
	unsigned int p2; //����2, ��interface
	unsigned char payloadLength; //�������ݳ��ȣ����м����¼���Ҫ��, �����ʱ��Ϊ0, ֮��Ϊ��������
};

//����˿��ư�����
struct ControlPacket
{
	unsigned char reserved; //0xFF
	unsigned char packetLength; //�����İ�����, ����������һ���ֽ�, ��������һ���ֽ�
	unsigned int crc; //У���, �Ѹó�Ա֮���ÿһ���ֽڴ�(unsigned int)0��ʼ���
	unsigned char type; //���ư�����, 0 = �ط����ݰ�, 1 = ״̬ͨ��
	unsigned int param1; //type = 1ʱ, Ϊ��Ҫ�ط������ݰ���id��type = 2ʱ, p1 = 1 �����ݰ����ط�, p1 = 2, ���������������ͬ��״̬
};

namespace ai
{

	//�¼�ö������
	enum
	{
		init = 0,
		deinit,
		start,
		initalizeTehai,
		newDora,
		newUra,
		othersTurn,
		othersTurnFinished,
		yourTurn,
		yourTurnSpecial,
		minDone,
		minChance,
		finish,
		finishNaga,
		finishNagaSpecial,
		scoreChange,
		finishAbnormal,
		communicationAbnormal,
		negotiate,
		sessionInitialize,
		sessionCreated,
		sessionRestoration, //δʵ��
		wait,
		gameFinish,
		othersTepai
	};

	//����ö������
	namespace min {
		enum
		{
			chi = 1, //��
			pon, //��
			kang, //������
			kangj, //�Ӹ�
			kangs, //����
			riichi //��ֱ
		};
	}

	//Payload : ����
	struct AKARI
	{
		unsigned int from; //�ļҵ�ģ��ο� ai::start �е����λ��
		unsigned int to; //�ļҺ͵ģ��ο� ai::start �е����λ��
		unsigned char pai; //�͵���id
						   /*from==to ʱΪ����*/
		int huu; //����
		int fan; //����
		int pt; //���˵���������ʱΪ�����㣩
		int reserved;
		int yakucnt;
		unsigned char yaku_id[16]; //������id������id�ο�mahjongĿ¼�ڵ� ����id.txt
		unsigned char yaku_fan[16]; //��Ӧ���۵ķ���
									/*����������Ա��Ϊ�������ͣ��±�Ϊ0��fan-1*/
	};

	//Payload : ��ǰ״̬
	struct CURRENT //δʵ��
	{
		/*unsigned char pos; //Client ��λ��
		unsigned char base; //0~7 ��1~4 ��1~4 �Դ�����
		unsigned char richii_bang; */
	};

	//Payload : ����״̬
	struct TENPAI
	{
		unsigned char p[4]; // 0δ���ƣ���ʱ��Ӧ��tepai(cnt)������ 1���� 2����
		int tepaicnt[4];
		pai tepai0[13];
		pai tepai1[13];
		pai tepai2[13];
		pai tepai3[13];
	};
}

// EventBus ����
struct ebRequest
{
	int id;
	unsigned char msgType;
	unsigned int par1;
	unsigned int par2;
	void* payload;
	int lpayload;
};

// EventBus �ͻ�
struct client
{
	int clientType;
	int clientHandle;
};

// EventBus �¼�
struct ebEvent
{
	int id;
	unsigned int response;
};

namespace ct {
	enum
	{
		undefined = 0,
		local_ai,
		local_user,
		local_extended,
		remote
	};
}

typedef void(__stdcall *aiFunc)(unsigned char, int, int);
typedef void(__stdcall *evtDealer)(LPVOID, int, unsigned int);
typedef void(__stdcall *crf)(LPVOID, unsigned int, unsigned char, int, int, int);

const char ji[4] = { 'D','N','X','B' };

// ��������

// �Ƚ���������ͬ/��ͬ
// ���Ƚ�ֻ�Ƚϻ�ɫ�����֣������Ƿ�Ϊ��
bool operator == (const pai& a, const pai& b);
bool operator != (const pai& a, const pai& b);
bool compare_pai (const pai& a, const pai& b);

// �Ƚ���������ͬ/��ͬ (����)
// ���ȽϱȽϻ�ɫ�����֣����Ƚϳ������Ƿ���ͬ
bool compare_pai_aka(const pai& a, const pai& b);

// �Ƚ���������ͬ/��ͬ (ȫͬ)
// ���Ƚ�Ҫ��������ȫ�ȣ�����ɫ�������⣬trait ҲҪһ��
bool compare_pai_same(const pai& a, const pai& b);

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

// ����۾�ID
// pai : ��
// ����ֵ : ID��19M19S19P���������׷��зֱ��� 0-12��������Ϊ 13
int get_yaotyuu_id(const pai& wpai);

// ������ӵ����ͣ������������
// a,b,c : �Ƶ� ID���� retrieveID3 ��ͬ
// ����ֵ : 1Ϊ���ӣ�2Ϊ˳�ӣ�-1Ϊ��������
int getMentsuType(int a, int b, int c);

// ����������ַ���ת��Ϊ�����顣��������˳��
// pstring : ���ƣ���ĸ����ΪСд��ĸ��1-9m 1-9s 1-9p 1-7z 0m0s0p
// parr : ���յ�����
// *buffersize : �����������󳤶ȣ�������Ҳ���������մ�����Ϣ��
// ����ֵ : �ɹ�����������ֵΪ�����������������
// buffersize Ϊ 0 : ���������Ȳ��㣬-1 / -2 : ��ʽ����
bool convertPaiString(std::string& pstring, pai* parr, int* buffersize);

// ͳ��һ����������ַ����е��Ƶ�������Ϊ convertPaiString ������׼��
// pstring : ���ƣ���ĸ����ΪСд��ĸ��1-9m 1-9s 1-9p 1-7z 0m0s0p
// ����ֵ : ���������Ϊ��������Ϊʧ�ܡ����ڿ��ַ������� 0��
int convertPaiStringPrepare(std::string& pstring);