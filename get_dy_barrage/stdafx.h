/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2015, Douyu Network Technology Co., Ltd. in Wuhan
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail：xiaolongicx@gmail.com
 *  @date : 2015/5/19
 *
 *  Revision Notes :
*/

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#include <stdio.h>

#ifdef _MSC_VER
#include <Windows.h>
#include <tchar.h>

#define strtoll _strtoi64
#define strtoull _strtoui64
#define snprintf _snprintf
#define popen   _popen
#define pclose  _pclose
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#else
#include <pthread.h>
#endif

// TODO: 在此处引用程序需要的其他头文件
