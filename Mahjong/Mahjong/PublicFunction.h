﻿#pragma once

// 主要定义了一些公用过程与数据类型。

#define MAX_MENTSU 4

#define RON false
#define TSUMO true
#define is_akari(x) (((x).trait&TRAIT_AKARIPAI)==TRAIT_AKARIPAI)
#define is_aka(x) (((x).trait&TRAIT_AKA)==TRAIT_AKA)
#define compare_pai_thesame compare_pai_same

#define _char char

#define Daisyarin 1
#define Daichikurin 2
#define Daisuurin 3

#define KOKUSHIMUSOU 1
#define KOKUSHIMUSOU_JUUSANMENMACHI 2

const int yaotrans[13] = { 1,9,10,18,19,27,28,29,30,31,32,33,34 };

const _char yakuname[65][40] = { "\0", "立直","一发","门前自摸","断幺","平和","一杯口","役牌/白","役牌/发","役牌/中","役牌/场风东","役牌/场风南",
"役牌/场风西","役牌/场风北","役牌/自风东","役牌/自风南","役牌/自风西","役牌/自风北","役牌/连风东",
"役牌/连风南","役牌/连风西","役牌/连风北","岭上","抢杠","海底","河底","三色同顺","一气","混全带幺九",
"七对子","对对","三暗","三杠子","三色同刻","混老头","小三元","W立直","混一","纯全带幺九","二杯口",
"清一","国士","四暗刻","大三元","小四喜","字一色","绿一色","清老头","九连","四杠子","天和","地和",
"人和","国士13面","大四喜","四暗单骑","大车轮","场风(未定义)","自风(未定义)","连风(未定义)","纯九连",
"宝牌","北宝牌","未定义役" };
//具体排列参考 役种id.txt

//paiorder 定义了在处理手牌时排序的顺序，本身应该是一个26成员的数组，
//每个字母，如M、S、P对应一个次序，不硬编码的主要原因是可以让用户方便的进行重定义
//数组中为0的成员都是无意义的
const int paiorder[30] = { 0,7,0,4,0,9,0,0,0,0,0,0,1,5,0,3,0,0,2,0,0,0,8,6,0,10,0,0,0,0 };
//                   B   D   F             M N   P     S       W X   Z

const int funpai[7] = { 'D','N','X','B','W','F','Z' };

// 牌的特征
#define TRAIT_AKA 1
#define TRAIT_AKARIPAI 2
#define TRAIT_OPEN 4


// 接口虚类定义
// EventBus 用户的接口，如 UI、AI、网络等，对于非即时返回的而言，*hasReturn 总为 false。
class EventBusUser {
public:
	virtual int aiMessage(unsigned char msgType, int par1, int par2, bool* hasReturn, void* payload) = 0;
};

// EventBus 比赛的接口，一般只用于内部调用。
class MatchingUser {
public:
	virtual void receiveEvent(int clientId, unsigned int response) = 0;
};

//牌数据结构。type 为颜色，分'M','S','P','D','N','X','B','W','F','Z'，这几种；fig 为数字；trait 为特征（包括赤等）
struct pai {
	unsigned char type;
	unsigned char fig;
	int trait;
};

//面子类型
enum mentsu_TYPE {
	mentsu_SHUNZ, //顺子面子
	mentsu_KEZ, //刻子面子
	mentsu_SHUNZ_CHI_A, //顺子面子，吃上家
	mentsu_SHUNZ_CHI_B, //保留
	mentsu_SHUNZ_CHI_C, //保留
	mentsu_KEZ_PON_A, //刻子面子，碰上家
	mentsu_KEZ_PON_B, //刻子面子，碰对家
	mentsu_KEZ_PON_C, //刻子面子，碰下家
	mentsu_KEZ_KANG_A, //杠子面子，杠上家
	mentsu_KEZ_KANG_B, //杠子面子，杠对家
	mentsu_KEZ_KANG_C, //杠子面子，杠下家
	mentsu_KEZ_KANG_S, //杠子面子，暗杠
};

//面子数据结构，包括一个双向链表；在大多数场合下，调用者不需要维护链表结构，链表指针是在内部起到提高效率的作用的。
struct mentsu {
	char type; //面子类型，为 mentsu_TYPE 枚举类型
	pai start; //刻子的开始一张牌
	pai middle; //刻子的中间一张牌
	pai last; //刻子的最后一张牌
	mentsu* prev; //内部实用，置零即可
	mentsu* next; //内部实用，置零即可
};

//面子表，内部数据结构。
struct mentsutable {
	mentsu* first;
	mentsu* tail;
};

//役数据结构，内部数据类型
struct yaku {
	int yakuid;
	int yakusubid;
	int pt;
	yaku* prev;
	yaku* next;
};

//役表数据结构，内部数据类型
struct yaku_table {
	bool yakuman = false;
	yaku* first = NULL;
	yaku* tail = NULL;
	int yakutotal = 0;
	int huutotal = 0;
	int basicpt = 0;
};

//传递给 TenpaiAkariJudge 的主要请求
struct judgeRequest
{
	int paicnt; //手牌数量，必须为 3n+1
	pai pais[13]; //手牌，在判定役时，应是由 paiSort 排序过的有序数组
	int mode; //检测模式 0为听牌种类检测 1为和了役检测，为0时，后面的参数无意义
	int fulucnt = 0; //副露数量 0 or 1 or 2 or 3 or 4
	mentsu fulus[4]; //副露 mentsu[0~fulucnt] 该结构中的 prev / next 值没有意义
	pai tgtpai; //和了役检测时 和了的那张牌
	bool akari_status; //胡了种类 自摸/荣和  TSUMO or RON
	bool norelease = false; //天地人和可以成立（这人还没打过牌，之前无鸣牌）
	char jyouhuun = '\0'; //场风 'D' or 'N' or 'X' or 'B'，设置为 '\0' 即不判断
	char jihuun = '\0'; //自风 'D' or 'N' or 'X' or 'B'，设置为 '\0' 即不判断
	int flags = 0; //一组逻辑值，flags&1 立直 flags&2 W立直 flags&4 一发 flags&8 海底 flags&16 河底 flags&32 岭上 flags&64 抢杠
	int doracnt = 0; //几张DORA
};

//简化的请求，用于描述玩家状态
struct judgeRequestSimple
{
	bool akari_status; //胡了种类 自摸/荣和  TSUMO or RON
	bool norelease = false; //天地人和可以成立（这人还没打过牌，之前无鸣牌）
	char jyouhuun = '\0'; //场风 'D' or 'N' or 'X' or 'B'，设置为 '\0' 即不判断
	char jihuun = '\0'; //自风 'D' or 'N' or 'X' or 'B'，设置为 '\0' 即不判断
	int flags = 0; //一组逻辑值，flags&1 立直 flags&2 W立直 flags&4 一发 flags&8 海底 flags&16 河底 flags&32 岭上 flags&64 抢杠
};

//TenpaiAkariJudge 模块传递回的结构
struct judgeResult
{
	int cnt = 0; //听牌种类判断模式下，为听的牌的种类数量
	pai t[20]; //pai[cnt]，听的牌
	int yakucnt = 0; //和了役判断吗模式下，役的数量
	int yakutotal = 0; //总翻数
	int huutotal = 0; //符数
	int basicpt = 0; //基本点
	int yakuid[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //役的ID，和 yakuname 数组相对应
	int pt[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //对应役的翻数
};

//网络端数据包定义
struct Packet
{
	unsigned char packetLength; //包长度, 包括该字节, 为0xFF 时为心跳包, 忽略之后所有数据；0xFE 时为控制包, 详情付
	unsigned int crc; //校验和, 把该成员之后的每一个字节从(unsigned int)0开始相加
	unsigned int id; //包id, 以服务器发送的握手包开始（1）, 客户端和服务器循环加一, 单个客户端会话中保持递增序列
	unsigned char uType; //消息类型, 参interface
	unsigned int p1; //参数1, 参interface
	unsigned int p2; //参数2, 参interface
	unsigned char payloadLength; //额外数据长度（仅有几个事件需要）, 大多数时候为0, 之后为负载内容
};

//网络端控制包定义
struct ControlPacket
{
	unsigned char reserved; //0xFF
	unsigned char packetLength; //真正的包长度, 不包括上面一个字节, 包括下面一个字节
	unsigned int crc; //校验和, 把该成员之后的每一个字节从(unsigned int)0开始相加
	unsigned char type; //控制包类型, 0 = 重发数据包, 1 = 状态通告
	unsigned int param1; //type = 1时, 为需要重发的数据包的id；type = 2时, p1 = 1 无数据包可重发, p1 = 2, 意外错误、请求重新同步状态
};

namespace ai
{

	//事件枚举类型
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
		sessionRestoration, //未实现
		wait,
		gameFinish,
		othersTepai
	};

	//鸣牌枚举类型
	namespace min {
		enum
		{
			chi = 1, //吃
			pon, //碰
			kang, //大明杠
			kangj, //加杠
			kangs, //暗杠
			riichi //立直
		};
	}

	//Payload : 和牌
	struct AKARI
	{
		unsigned int from; //哪家点的，参考 ai::start 中的相对位置
		unsigned int to; //哪家和的，参考 ai::start 中的相对位置
		unsigned char pai; //和的牌id
						   /*from==to 时为自摸*/
		int huu; //符数
		int fan; //番数
		int pt; //和了点数（自摸时为基本点）
		int reserved;
		int yakucnt;
		unsigned char yaku_id[16]; //和了役id，具体id参考mahjong目录内的 役种id.txt
		unsigned char yaku_fan[16]; //对应的役的翻数
									/*上述两个成员均为数组类型，下标为0到fan-1*/
	};

	//Payload : 当前状态
	struct CURRENT //未实现
	{
		/*unsigned char pos; //Client 的位置
		unsigned char base; //0~7 东1~4 南1~4 以此类推
		unsigned char richii_bang; */
	};

	//Payload : 流局状态
	struct TENPAI
	{
		unsigned char p[4]; // 0未听牌，此时对应的tepai(cnt)无意义 1听牌 2流满
		int tepaicnt[4];
		pai tepai0[13];
		pai tepai1[13];
		pai tepai2[13];
		pai tepai3[13];
	};
}

// EventBus 请求
struct ebRequest
{
	int id;
	unsigned char msgType;
	unsigned int par1;
	unsigned int par2;
	void* payload;
	int lpayload;
};

// EventBus 客户
struct client
{
	int clientType;
	EventBusUser* clientHandle;
};

// EventBus 事件
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

const char ji[4] = { 'D','N','X','B' };

// 函数定义

// 比较两张牌相同/不同
// 本比较只比较花色和数字，不管是否为赤
bool operator == (const pai& a, const pai& b);
bool operator != (const pai& a, const pai& b);
bool compare_pai (const pai& a, const pai& b);

// 比较两张牌相同/不同 (含赤)
// 本比较比较花色和数字，并比较赤的情况是否相同
bool compare_pai_aka(const pai& a, const pai& b);

// 比较两张牌相同/不同 (全同)
// 本比较要求两张牌全等，除花色和数字外，trait 也要一样
bool compare_pai_same(const pai& a, const pai& b);

// 获得牌的序号。1M-9M：0-8，1S-9S：9-17，1P-9P：18-26，之后依次为东南西北白发中：27-33。
// 本函数不考虑是否为赤宝牌。
// 本函数主要是 TenpaiAkariJudge 模块内部实用。外部使用（网络、界面）请尽量使用 retrieveID3
// cpai : 牌
// 返回值 : 牌的序号
int retrieveID(const pai& cpai);

// 获得牌的序号。等于 retrieveID + 1，即比上面一个函数大一。
// 本函数不考虑是否为赤宝牌。
// 本函数主要用于外部过程，如界面、网络等（因为 0 在外部过程中可能有别的意义）
// cpai : 牌
// 返回值 : 牌的序号
int retrieveID3(const pai& cpai);

// 获得牌的序号。
// 本函数考虑是否为赤宝牌，是对 retrieveID3 函数的扩展，retrieveID3 的范围为 1-33，
// 在本函数中，赤5M、5S、5P分别为 34, 35, 36
// cpai : 牌
// 返回值 : 牌的序号
int retrieveID2(const pai& cpai);

//bool retrievePai(pai* pai, int id);

// 通过序号获得牌。此序号的意义和 retrieveID2 函数返回的相同，范围为 1-36
// pai : 接收的返回值
// id : 需要转换的 id
// 返回值 : 输入的 id 是否有效
bool retrievePai3(pai* pai, int id);

// 取得宝牌，当指示牌无效时，结果未定义
// show : 宝牌指示牌
// result : 指向结果的指针
// 返回值 : 无
void doraNext(const pai& show, pai* result);

// 对两张牌排序（小于等于号），用于 sort (STL)；排序的原则是，同色从小到大；不同色按 paiorder 数组的值指定。
// 实际上直接针对牌 ID 排序也是可以的，也就是 return retrieveID(a)<retrieveID(b); 这里采用如下比较方法是处于效率的考量
// a : 牌 1
// b : 牌 2
// 返回值 : 小于等于为真，大于为假
bool paiSort(const pai& a, const pai& b);

// 判断一个面子是不是刻子（包括杠）
// mc : 面子的指针
// 返回值 : 真或假
bool isKez(const mentsu* mc);

// 判断一个面子是不是杠（包括暗杠）
// mc : 面子的指针
// 返回值 : 真或假
bool isKangz(const mentsu* mc);

// 获得其他家的相对位置，输入参数为逆时针 0-4
// self : 自家位置
// other : 他家位置
// 返回值 : 0下家 1对家 2上家 -1错误 
int getRelativePosition(int self, int other);

// 获得幺九ID
// pai : 牌
// 返回值 : ID，19M19S19P东南西北白发中分别是 0-12，其他均为 13
int get_yaotyuu_id(const pai& wpai);

// 获得面子的类型，可以是无序的
// a,b,c : 牌的 ID，与 retrieveID3 相同
// 返回值 : 1为刻子，2为顺子，-1为不是面子
int getMentsuType(int a, int b, int c);

// 将天凤手牌字符串转换为牌数组。保持输入顺序。
// pstring : 手牌，字母必须为小写字母。1-9m 1-9s 1-9p 1-7z 0m0s0p
// parr : 接收的数组
// *buffersize : 接收数组的最大长度，本参数也会用来接收错误信息。
// 返回值 : 成功与否。如果返回值为否，有这样几种情况。
// buffersize 为 0 : 缓冲区长度不足，-1 / -2 : 格式出错
bool convertPaiString(std::string& pstring, pai* parr, int* buffersize);

// 统计一个天凤手牌字符串中的牌的数量，为 convertPaiString 函数做准备
// pstring : 手牌，字母必须为小写字母。1-9m 1-9s 1-9p 1-7z 0m0s0p
// 返回值 : 数量。如果为负数，则为失败。对于空字符串返回 0。
int convertPaiStringPrepare(std::string& pstring);

// 役的特性，描述见下图
// 相对的特殊情况：
// (1) 当起和役包含 yakumanLike 时，仅 doraLike 的役不会出现，而具有 doraLike & yakumanLike 的会出现
// (2) doraLike & yakumanLike 的役并不会抑制非 yakumanLike 的其他役
enum yakuTrait
{
	doraLike = 1, // 需要其他起胡役
	yakumanLike = 2, // 是最高级别的役，会无视其他非 yakumanLike 役
	specialJudge = 4, // 特殊判定（役除了和牌之外，还和玩家的状态有关），当为真时，在 judgeYaku 前，会额外调用 setSpecialJudge 来设定判定信息。
	default = 0
};

// 役判断的基本接口
class YakuProviderBase
{
public:
	// 取得一个役的名字
	// buffer : 名字缓冲区
	// bufferSize : 名字缓冲区的尺寸
	// outBufferSize : 返回尺寸，注意，这个值可能为 NULL；当名字缓冲区不够时且该值不为 NULL 时，该值为需要的尺寸。
	// subid : 子役 ID
	// 返回值 : bool，是否成功写入了缓冲区
	virtual bool queryName(_char* buffer, const int bufferSize, int* outBufferSize, int subid) = 0;

	// 设置役的特性，出于性能考虑，该函数可能只会在 register 时调用一次
	// 为 enum yakuTrait 的或值
	virtual int getTraits() = 0;

	// 设定判定信息，不需要 specialJudge 的役需直接设定为空函数。
	// jreq : 存储了玩家状态。出于性能考虑，直接传递指针，但*不应该*修改本参数的值。
	virtual void setSpecialJudge(judgeRequestSimple* jreq) = 0;

	// 获得役的种类
	// 返回值 : 0 为面子类（继承自 YakuProviderM），1 为颜色类（继承自 YakuProviderC）
	virtual int getType() = 0;
};

// 颜色类役的判断接口
class YakuProviderC : public YakuProviderBase
{
public:
	// 判断一个役的存在
	// pais : 手牌数组
	// paicnt : 手牌数量
	// fulu : 副露数组
	// fulucnt : 副露数量
	// subid : 子役 ID（对于一对一接口的情况，可以忽视，或者置 0）
	// yaku : 翻数，可以为 0，甚至是负数
	// 返回值 : bool，有没有该翻
	virtual bool judgeYaku(const pai* pais, int paicnt, const mentsu* fulu, int fulucnt, int* subid, int* yaku) = 0;
};

// 面子类役的判断接口
class YakuProviderM : public YakuProviderBase
{
public:
	// 判断一个役的存在
	// mentsu : 面子数组（包括手牌和副露）
	// mentsucnt : 面子数量
	// subid : 子役 ID（对于一对一接口的情况，可以忽视，或者置 0）
	// yaku : 翻数，可以为 0，甚至是负数
	// 返回值 : bool，有没有该翻
	virtual bool judgeYaku(const mentsu* mentsu, int mentsucnt, int* subid, int* yaku) = 0;
};