// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#if defined(_MSC_VER)
#   if _MSC_VER >= 1900 
#       define C11
#   endif
#elif __cplusplus > 199711L
#   define C11
#endif

#include "targetver.h"
#include "Winsock2.h"

#include <stdio.h>
#include <tchar.h>
#include <cstring>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <queue>

#include "..\MyGaclib\GacUI.h"
#ifdef WIN32
#pragma comment(lib, "..\\Release\\MyGaclib.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MyGaclib.lib")
#endif

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
