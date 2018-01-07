/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Omappoperator.h
  版 本 号   : 初稿
  作    者   : jinni168360
  生成日期   : 2012年08月08日

  最近修改   :
  功能描述   : Omappoperator.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年08月08日
    作    者   : jinni168360
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OM_APPOPERATOR_H__
#define __OM_APPOPERATOR_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"
#include "omprivate.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern LOG_LEVEL_EN   g_aulLogPrintLevPsTable[];
extern LOG_LEVEL_EN   g_aulLogPrintLevDrvTable[];

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 OM_AcpuEstablishReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_AcpuReleaseReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_VOID OM_AcpuQueryMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of OmOpeator.h */

