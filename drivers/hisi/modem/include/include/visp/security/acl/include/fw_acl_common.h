/***********************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                          fw_acl_common.h
 *
 *  Project Code: VISP1.6
 *  Module Name: ACL4
 *  Date Created: 2009-09-06
 *  Author: bhaskar 71224
 *  Description: ACL Common include structure. 
 *  Version:      1
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2009-09-06      bhaskar 71224    Create
 *  2011-3-17       Eswar  72335     Added one macro to notify group addition through 
 *                                   call back functions.
 *  2011-8-4        Eswar  72335     Added a structure and modified one existing structure to
 *                                   configure VLAN ID for MAC rules.
 ***********************************************************************************/
#ifndef _FW_ACL_COMMON_H_
#define _FW_ACL_COMMON_H_

#ifdef  __cplusplus
extern "C" 
{
#endif
    
#include "security/acl/include/fw_acl_def.h"

#define ACL_MAX_TR_NAME_LEN 33
#define ACL_MEMALLOC_INFO 0

/* Added by Rishab Joshi. */
#define ACL_NUM_ONE 1 

/*ACLFW_MAXNODE is now obsolete and should not be used.
The macro is retained only to support the old version*/
#define ACLFW_MAXNODE   256
    
#define ACLFW_MAX_INT_NAME_LEN 47
#define ACLFW_MIN_INT_NAME_LEN 1

#define ACLFW_LEN_32 32
#define ACLFW_LEN_256 256
#define ACLFW_LEN_1024 1024
    
/*filter Type*/ 
#define ACLFW_FITLERTYPE_IN         0 
#define ACLFW_FITLERTYPE_OUT        1 

/* Begin Add NEW.R.FireWall liangjicheng 2009-08-17 */
#define ACLFW_FITLERTYPE_MACIN     2 
#define ACLFW_FITLERTYPE_MACOUT    3 
    
#define ACLFW_CFG_ADD    0 
#define ACLFW_CFG_DEL    1 

/* Bhaskar 2009-10-24: Declarations moved from shell to fw_acl_common.h file */
/*f47854 add begin*/
#define ACL_DEL 0
#define ACL_ADD 1

#define    ACL_ACTION_DELETE      0
#define    ACL_ACTION_CREATE      1
#define    ACL_ACTION_RESERVED    2

/* Bhaskar 2009-10-24: End */

/*说明:当Debug ALL bit设置，将会打印所有报文Debug信息
当Debug ALL Bit 没有设置
当设置了IN or OUT,必需再设置Deny or Permit Bit
IN 和 OUT 可以同时设置
Deny 和Permit可以同时设置
*/
#define ACLFW_DBGF_ALL   0x00000001
#define ACLFW_DBGF_IN   0x00000002
#define ACLFW_DBGF_OUT   0x00000004
#define ACLFW_DBGF_DENY   0x00000008
#define ACLFW_DBGF_PERMIT   0x00000010

/* Begin Add NEW.R.FireWall liangjicheng 2009-08-17 */
#define ACLFW_DBGF_MACIN        0x00000020
#define ACLFW_DBGF_MACOUT       0x00000040
#define ACLFW_DBGF_MACDENY      0x00000080
#define ACLFW_DBGF_MACPERMIT    0x00000100
/* End Add NEW.R.FireWall*/

#define ACL_MODID (0x0E000000+0x00100000)


/* ACL的错误码 */

/**
* @defgroup ACLEC ACL Error Codes
* This section contains the error codes used in ACL.
*/

/**
* @defgroup enumACLHelp Other ACL Error Codes
* @ingroup ACLEC ACL Error Codes
* @par Prototype
* @code
* enum enumACLHelp
* {
*     Help_ACL_OK = 0,
*     Help_ACL_ERR,
*     Help_ACL_AccessListTooMuchRulesNormal,
*     Help_ACL_AccessInGroup,
*     Help_ACL_NameCreateFailedForMax,
*     Help_ACL_NameCreateAnotherTypeExist,  
*     Help_ACL_MatchOrderErr,
*     Help_ACL_Group_Exist,
*     Help_ACL_VrfNotExist,
*     Help_ACL_VrfNotSetRD,
*     Help_ACL_Not_Exist,
*     Help_ACLGroup_Not_Exist,
*     Help_ACL_Subitem_Number_Not_Exist,
*     Help_ACL_SubIDTooLarge,
*     Help_ACL_RULES_EXIST,
*     Help_ACL_NotChangeMatchOrder,
*     Help_ACL_RULES_TOOLARGE,
*     Help_ACL_CANOT_GIVEID,
*     Help_ACL_DESCRIPTION_NULL,
*     Help_ACL_ERRSTEP,
*     Help_ACL_RULEIndex_ERROR,
*     Help_ACL_NOTMODIFY,
*     Help_ACL_RULEManageErr,
*     Help_ACL_RULENode_MallocErr,
*     Help_ACL_DownLoadFail,
*     Help_ACL_END,
*     Help_ACL_GroupNumError,
*     Help_ACL_ActionError,
*     Help_ACL_PreError,
*     Help_ACL_TosError,
*     Help_ACL_DscpError,
*     Help_ACL_FrameTypeError,
*     Help_ACL_DescriptionTooLong,
*     Help_ACL_CannotSetPortNum,
*     Help_ACL_MallocError,
*     Help_ACL_TYPE_NOT_EXIST,
*     Help_ACL_TYPE_ID_ERROR,
*     Help_ACL_GROUP_RANGE_ERROR,
*     Help_ACL_GROUP_RANGE_CANOT_CHANGE,
*     Help_ACL_TYPE_ID_EXIST,
*     Help_ACL_ORDER_CANNOT_SET_DEFAULT,
*     Help_ACL_CONTENT_NULL,
*     Help_ACL_CONTENT_SIZEZERO,
*     Help_ACL_FUNC_NULL,
*     Help_ACL_INIT_ERR,
*     Help_ACL_NOT_INIT,
*     Help_ACL_PortNumError,
*     Help_ACL_Type_MallocError,
*     Help_ACL_Group_MallocError,
*     Help_ACL_MatchOrderErr_Snd,
*     Help_ACL_TYPE_BASIC_MallocErr,
*     Help_ACL_TYPE_ADV_MallocErr,
*     Help_ACL_TYPE_IF_MallocErr,
*     Help_ACL_TYPE_MAC_MallocErr,
*     Help_ACL_GROUP_BASIC_MallocErr,
*     Help_ACL_GROUP_ADV_MallocErr,
*     Help_ACL_GROUP_IF_MallocErr,
*     Help_ACL_GROUP_MAC_MallocErr,
*     Help_ACL_WAITLIST_OpenFail,
*     Help_ACL_WAITLIST_SetFail,
*     Help_ACL_WAITLIST_GetFail,
*     Help_ACL_WAITLIST_CloseFail,
*     Help_ACL_ERR_CreateSm,
*     Help_ACL_NULL_POINTER,
*     Help_ACL_TooMuchRulesINGroup,
*     Help_ACL_CALLBACK_EXIST,
*     Help_ACL_NotSupportOperType,
*     Help_ACL_ERR_GETMATCHCOUNT,
*     Help_ACL_ERR_GETVRFINDEX,
*     Help_ACL_ERR_ICMPCODE,
*     Help_ACL_ERR_ICMPTYPE,
*     Help_ACL_ERR_PORTOPTYPE,
*     Help_ACL_ERR_SEMAPHORE_ADDNAMEDB,
*     Help_ACL_ERR_ACC_ADDNAMEDB,
*     Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB,
*     Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB,
*     Help_ACL_ACC_SHARE_MallocError,
*     Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError,
*     Help_ACL_GLOBALSTRUCT_SHARE_MallocError,
*     Help_ACL_ERR_GETIFINDEX,
*     Help_ACL_ERR_GETIFINDEX_NAMELEN,
*     Help_ACL_ACL_STAT_INIT,
*     Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH,
*     Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT,
*     Help_ACL_ERR_STAT_DELETE_GROUP_HASH_SEARCH,
*     Help_ACL_FM_SHARE_MallocError,
*     Help_ACL_ERR_FM_ADDNAMEDB,
*     Help_ACL_ERR_RULESTATUSUPDATE_NORULE,
*     Help_ACL_ACC_SEMSHARE_MallocError,
*     Help_ACL_RFC_GET_PRECONFIG_FAIL,
*     Help_ACL_SETFWSTATISTICSWITCH_INVALID_SWITCH,
*     Help_ACL_SETFWSTATISTICSWITCH_NULL_SWITCH,
*     Help_ACL_GETFWSTATISTICSWITCH_NULLPTR,
*     Help_ACL_GETFWSTATISTICSWITCH_NULL_SWITCH,
*     Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_MALLOC,
*     Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_ADDNAMEDB,
*     Help_ACL_STAT_ERR_FLOWSTATINIT_MALLOC,
*     Help_ACL_STAT_ERR_FLOWSTATINIT_ADDNAMEDB,
*     Help_ACL_STAT_ERR_ACL_INIT_SWITCH_MALLOC,
* 	  Help_ACL_STAT_ERR_ACL_INIT_SWITCH_ADDNAMEDB,
*     Help_ACL_STAT_ERR_ACL_INIT_SWITCH_STAT_HASHTABLE,
*     Help_ACL_STAT_ERR_STATINIT_SWITCH_MALLOC,
*     Help_ACL_STAT_ERR_STATINIT_SWITCH_ADDNAMEDB,
*     Help_ACL_INIT_ERR_MALLOC_MODULE_ENABLE,
*     Help_ACL_INIT_ERR_ADD_NAME_DB_MODULE_ENABLE,
*     Help_ACL_INIT_ERR_CREATE_SYS_SPIN_LOCK,
*     Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_INVALID_SWITCH,
*     Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_NULL_SWITCH,
*     Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULLPTR,
*     Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULL_SWITCH,
*     Help_ACL_DEBUG_CLEARALLFLOWSTATISTIC_NULL_SHARE,
*     Help_ACL_TIMER_INIT_MALLOC_FAIL,
*     Help_ACL_TIMER_INIT_NAMEDB_ADD_FAIL,
*     Help_ACL_IPSAFE_INIT_FAIL,
*     Help_ACL_Refresh_GRP_TIMER_INIT_MALLOC_FAIL,
*     Help_ACL_Refresh_GRP_TIMER_INIT_NAMEDB_ADD_FAIL ,
*     Help_ACL_Refresh_GRP_TIMER_CREATE_FAIL ,
*     Help_ACL_COMMON_TIMER_INIT_MALLOC_FAIL,
*     Help_ACL_WRONG_VLANID,
*     Help_ACL_NO_RULES_EXIST,
*     Help_ACL_Max
* };
* @endcode 
* 
* @par Description
* This enum consists of other ACL error codes. 
* 
* @datastruct Help_ACL_OK=0 Indicates Success
* @datastruct Help_ACL_ERR Indicates input parameter is null
* @datastruct Help_ACL_AccessListTooMuchRulesNormal Indicates total number of ACL rules exceed limit
* @datastruct Help_ACL_AccessInGroup Indicates total number of rules inside the group exceeds limit
* @datastruct Help_ACL_NameCreateFailedForMax This error code is not in use
* @datastruct Help_ACL_NameCreateAnotherTypeExist This error code is not in use
* @datastruct Help_ACL_MatchOrderErr Indicates invalid match order 
* @datastruct Help_ACL_Group_Exist Indicates group already exists
* @datastruct Help_ACL_VrfNotExist Indicates VRF index does not exist
* @datastruct Help_ACL_VrfNotSetRD This error code is not in use
* @datastruct Help_ACL_Not_Exist Indicates ACL group does not exist
* @datastruct Help_ACLGroup_Not_Exist Indicates ACL group does not exist
* @datastruct Help_ACL_Subitem_Number_Not_Exist Indicates specified rule number does not exist
* @datastruct Help_ACL_SubIDTooLarge Indicates invalid next rule node
* @datastruct Help_ACL_RULES_EXIST Indicates rule already exists
* @datastruct Help_ACL_NotChangeMatchOrder Indicates match order cannot be changed
* @datastruct Help_ACL_RULES_TOOLARGE Indicates Rule ID too large
* @datastruct Help_ACL_CANOT_GIVEID Indicates ACL cannot provide new rule ID
* @datastruct Help_ACL_DESCRIPTION_NULL Indicates group description specified is null
* @datastruct Help_ACL_ERRSTEP Indicates invalid step value specified
* @datastruct Help_ACL_RULEIndex_ERROR Indicates Rule ID cannot be verified
* @datastruct Help_ACL_NOTMODIFY Indicates unable to modify rule
* @datastruct Help_ACL_RULEManageErr Indicates rule manager error
* @datastruct Help_ACL_RULENode_MallocErr Indicates new rule node malloc error
* @datastruct Help_ACL_DownLoadFail Indicates download error
* @datastruct Help_ACL_END Indicates iterator reached end
* @datastruct Help_ACL_GroupNumError Indicates group number error
* @datastruct Help_ACL_ActionError Indicates invalid action value specified
* @datastruct Help_ACL_PreError Indicates invalid precedence value specified
* @datastruct Help_ACL_TosError Indicates invalid TOS value specified
* @datastruct Help_ACL_DscpError Indicates invalid DSCP value specified
* @datastruct Help_ACL_FrameTypeError Indicates frame type error
* @datastruct Help_ACL_DescriptionTooLong Indicates group description too long
* @datastruct Help_ACL_CannotSetPortNum Indicates cannot set port number
* @datastruct Help_ACL_MallocError Indicates malloc error
* @datastruct Help_ACL_TYPE_NOT_EXIST Indicates type does not exist
* @datastruct Help_ACL_TYPE_ID_ERROR Indicates type ID does not exist
* @datastruct Help_ACL_GROUP_RANGE_ERROR Indicates invalid group number range specified
* @datastruct Help_ACL_GROUP_RANGE_CANOT_CHANGE Indicates cannot change group number range
* @datastruct Help_ACL_TYPE_ID_EXIST Indicates ACL type ID already exists
* @datastruct Help_ACL_ORDER_CANNOT_SET_DEFAULT Indicates rule match order cannot set to default
* @datastruct Help_ACL_CONTENT_NULL Indicates rule content null
* @datastruct Help_ACL_CONTENT_SIZEZERO Indicates rule content size zero
* @datastruct Help_ACL_FUNC_NULL Indicates callback function is null
* @datastruct Help_ACL_INIT_ERR Indicates ACL already initialized
* @datastruct Help_ACL_NOT_INIT Indicates ACL is not initialized
* @datastruct Help_ACL_PortNumError Indicates invalid port number is specified
* @datastruct Help_ACL_Type_MallocError Indicates ACL type malloc error
* @datastruct Help_ACL_Group_MallocError Indicates ACL group malloc error
* @datastruct Help_ACL_MatchOrderErr_Snd Indicates for MAC based rule, type match order cannot be auto 
* @datastruct Help_ACL_TYPE_BASIC_MallocErr Indicates basic rule type malloc error
* @datastruct Help_ACL_TYPE_ADV_MallocErr Indicates advance rule type malloc error
* @datastruct Help_ACL_TYPE_IF_MallocErr Indicates interface based rule type malloc error
* @datastruct Help_ACL_TYPE_MAC_MallocErr Indicates MAC based rule type malloc error
* @datastruct Help_ACL_GROUP_BASIC_MallocErr Indicates basic group malloc error
* @datastruct Help_ACL_GROUP_ADV_MallocErr Indicates advance group malloc error
* @datastruct Help_ACL_GROUP_IF_MallocErr Indicates interface base group malloc error
* @datastruct Help_ACL_GROUP_MAC_MallocErr Indicates MAC based group malloc error
* @datastruct Help_ACL_WAITLIST_OpenFail Indicates waitlist open fail
* @datastruct Help_ACL_WAITLIST_SetFail Indicates waitlist set fail
* @datastruct Help_ACL_WAITLIST_GetFail Indicates waitlist get fail
* @datastruct Help_ACL_WAITLIST_CloseFail Indicates waitlist close fail
* @datastruct Help_ACL_ERR_CreateSm Indicates semaphore creation error
* @datastruct Help_ACL_NULL_POINTER Indicates null pointer
* @datastruct Help_ACL_TooMuchRulesINGroup Indicates total number of rules inside the group exceeds limit
* @datastruct Help_ACL_CALLBACK_EXIST Indicates callback function already exists
* @datastruct Help_ACL_NotSupportOperType Indicates operation type not supported
* @datastruct Help_ACL_ERR_GETMATCHCOUNT Indicates get PPI match count error
* @datastruct Help_ACL_ERR_GETVRFINDEX Indicates unable to get VRF index by name 
* @datastruct Help_ACL_ERR_ICMPCODE Indicates for ICMP packet destination port is wrong
* @datastruct Help_ACL_ERR_ICMPTYPE Indicates for ICMP packet source port is wrong
* @datastruct Help_ACL_ERR_PORTOPTYPE Indicates error port type operation
* @datastruct Help_ACL_ERR_SEMAPHORE_ADDNAMEDB Indicates failed to add semaphore shared variable to name DB
* @datastruct Help_ACL_ERR_ACC_ADDNAMEDB Indicates failed to add g_pstAccACL_share shared variable to name DB
* @datastruct Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB Indicates failed to add g_pulAclGroupNumSum_share shared variable 
* to name DB
* @datastruct Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB Indicates failed to add g_pstACL_share shared variable to name DB
* @datastruct Help_ACL_ACC_SHARE_MallocError Indicates failed to malloc g_pstAccACL_share global variable
* @datastruct Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError Indicates failed to malloc g_pulAclGroupNumSum_share global 
* variable
* @datastruct Help_ACL_GLOBALSTRUCT_SHARE_MallocError Indicates failed to malloc g_pstACL_share global variable
* @datastruct Help_ACL_ERR_GETIFINDEX Indicates failed to get interface information
* @datastruct Help_ACL_ERR_GETIFINDEX_NAMELEN Indicates interface name length exceeds limit
* @datastruct Help_ACL_ACL_STAT_INIT Indicates failed to initialize ACL statistics 
* @datastruct Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH Indicates hash search error
* @datastruct Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT Indicates hash insert error
* @datastruct Help_ACL_ERR_STAT_DELETE_GROUP_HASH_SEARCH Indicates delete group hash search error
* @datastruct Help_ACL_FM_SHARE_MallocError Indicates failed to malloc g_pbFM_share global variable
* @datastruct Help_ACL_ERR_FM_ADDNAMEDB Indicates failed to add g_pbFM_share shared variable to name DB
* @datastruct Help_ACL_ERR_RULESTATUSUPDATE_NORULE Indicates no rule to update status 
* @datastruct Help_ACL_ACC_SEMSHARE_MallocError Indicates g_pstSemForACL_share malloc error
* @datastruct Help_ACL_RFC_GET_PRECONFIG_FAIL Indicates error in getting RFC pre-configuration data
* @datastruct Help_ACL_SETFWSTATISTICSWITCH_INVALID_SWITCH Indicates invalid switch
* @datastruct Help_ACL_SETFWSTATISTICSWITCH_NULL_SWITCH Indicates null switch
* @datastruct Help_ACL_GETFWSTATISTICSWITCH_NULLPTR Indicates null pointer
* @datastruct Help_ACL_GETFWSTATISTICSWITCH_NULL_SWITCH Indicates null switch
* @datastruct Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_MALLOC Indicates flow stat initialization for switch failed
* @datastruct Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_ADDNAMEDB Indicates adding to name DB failed
* @datastruct Help_ACL_STAT_ERR_FLOWSTATINIT_MALLOC Indicates flow stat memory allocation for switch failed
* @datastruct Help_ACL_STAT_ERR_FLOWSTATINIT_ADDNAMEDB Indicates adding to name DB failed
* @datastruct Help_ACL_STAT_ERR_ACL_INIT_SWITCH_MALLOC Indicates flow stat initialization for switch failed
* @datastruct Help_ACL_STAT_ERR_ACL_INIT_SWITCH_ADDNAMEDB Indicates adding to name DB failed
* @datastruct Help_ACL_STAT_ERR_ACL_INIT_SWITCH_STAT_HASHTABLE Indicates initializing statistics hash table failed
* @datastruct Help_ACL_STAT_ERR_STATINIT_SWITCH_MALLOC Indicates failed to allocate memory for statistics switch
* @datastruct Help_ACL_STAT_ERR_STATINIT_SWITCH_ADDNAMEDB Indicates adding to statistics name DB failed
* @datastruct Help_ACL_INIT_ERR_MALLOC_MODULE_ENABLE Indicates module initialization error
* @datastruct Help_ACL_INIT_ERR_ADD_NAME_DB_MODULE_ENABLE Indicates error in adding module name in DB
* @datastruct Help_ACL_INIT_ERR_CREATE_SYS_SPIN_LOCK Indicates error in creating spin lock
* @datastruct Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_INVALID_SWITCH Indicates invalid flow statistics switch
* @datastruct Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_NULL_SWITCH Indicates flow statistics switch is  null
* @datastruct Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULLPTR Indicates flow statistics switch is a null pointer
* @datastruct Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULL_SWITCH Indicates statistics switch is null
* @datastruct Help_ACL_DEBUG_CLEARALLFLOWSTATISTIC_NULL_SHARE Indicates statistics switch shared variable is null
* @datastruct Help_ACL_TIMER_INIT_MALLOC_FAIL Indicates error in memory allocation for ACL time range table
* @datastruct Help_ACL_TIMER_INIT_NAMEDB_ADD_FAIL Indicates error in adding ACL time range table name to database
* @datastruct Help_ACL_IPSAFE_INIT_FAIL Indicates error in the IPSAFE Init function
* @datastruct Help_ACL_Refresh_GRP_TIMER_INIT_MALLOC_FAIL Indicates error allocating memory for refresh ACL group timer
* @datastruct Help_ACL_Refresh_GRP_TIMER_INIT_NAMEDB_ADD_FAIL Indicate failed to add refresh ACL group timer to name DB
* @datastruct Help_ACL_Refresh_GRP_TIMER_CREATE_FAIL Indicate failed to create refresh ACL group timer
* @datastruct Help_ACL_COMMON_TIMER_INIT_MALLOC_FAIL Indicates error allocating memory for common ACL timer
* @datastruct Help_ACL_WRONG_VLANID Indicates given VLAN ID is out of range
* @datastruct Help_ACL_NO_RULES_EXIST Indicates no rule exists in the group
* @datastruct Help_ACL_Max Indicates the max code of the enum. It is not an error code. All the other error codes  
* should be added before it.
*/

enum enumACLHelp
{
    Help_ACL_OK = 0,
    Help_ACL_ERR,                           /* 1 无用 */
    Help_ACL_AccessListTooMuchRulesNormal,  /* 2 规则数超过规格 */
    Help_ACL_AccessInGroup,                 /* 3 规则索引超过规则组上限 */
    Help_ACL_NameCreateFailedForMax,        /* 4 无用 */
    Help_ACL_NameCreateAnotherTypeExist,    /* 5 无用 */
    Help_ACL_MatchOrderErr,             /* 6 规则组匹配顺序错误 */
    Help_ACL_Group_Exist,               /* 7 规则组已经存在 */
    Help_ACL_VrfNotExist,               /* 8 无用 */
    Help_ACL_VrfNotSetRD,               /* 9 无用 */
    Help_ACL_Not_Exist,                 /* 10 规则组不存在，以后不使用，现有不改变 */
    Help_ACLGroup_Not_Exist,            /* 11 规则组不存在 */
    Help_ACL_Subitem_Number_Not_Exist,  /* 12 规则不存在 */
    Help_ACL_SubIDTooLarge,             /* 13 规则索引用完，无法分配新的规则索引*/
    Help_ACL_RULES_EXIST,               /* 14 规则已经存在 */
    Help_ACL_NotChangeMatchOrder,       /* 15 规则组配置规则后不可改变匹配顺序 */
    Help_ACL_RULES_TOOLARGE,            /* 16 无用 */
    Help_ACL_CANOT_GIVEID,              /* 17 规则组配置顺序为自动匹配时，不允许指定规则号 */
    Help_ACL_DESCRIPTION_NULL,          /* 18 描述信息为空 */
    Help_ACL_ERRSTEP,                   /* 19 错误的步长 */
    Help_ACL_RULEIndex_ERROR,           /* 20 分配规则索引错误 */
    Help_ACL_NOTMODIFY,                 /* 21 自动匹配时禁止修改规则 */
    Help_ACL_RULEManageErr,             /* 22 配置规则失败 */
    Help_ACL_RULENode_MallocErr,        /* 23 分配规则节点失败 */
    Help_ACL_DownLoadFail,              /* 24 无用 */
    Help_ACL_END,                       /* 25 遍历规则时到达最后一条规则 */
    Help_ACL_GroupNumError,             /* 26 规则组序号错误 */
    Help_ACL_ActionError,               /* 27 action取值错误 */
    Help_ACL_PreError,                  /* 28 优先级取值错误 */
    Help_ACL_TosError,                  /* 29 tos值取值错误 */
    Help_ACL_DscpError,                 /* 30 dscp取值错误 */
    Help_ACL_FrameTypeError,            /* 31 帧类型取值错误 */
    Help_ACL_DescriptionTooLong,        /* 32 输入规则组描述信息超过128字节 */
    Help_ACL_CannotSetPortNum,          /* 33 协议号不匹配，不能设置端口号 */
    Help_ACL_MallocError,               /* 34 配置过程中分配内存错误 */
    Help_ACL_TYPE_NOT_EXIST,            /* 35 规则类型不存在 */
    Help_ACL_TYPE_ID_ERROR,             /* 36 规则类型ID错误 */
    Help_ACL_GROUP_RANGE_ERROR,         /* 37 指定规则组上下限非法 */
    Help_ACL_GROUP_RANGE_CANOT_CHANGE,  /* 38 规则组上下限不可修改 */
    Help_ACL_TYPE_ID_EXIST,             /* 39 规则类型ID已经使用 */ 
    Help_ACL_ORDER_CANNOT_SET_DEFAULT,  /* 40 匹配顺序不可设置为默认顺序*/
    Help_ACL_CONTENT_NULL,              /* 41 规则信息数据结构中的规则内容指针为空*/
    Help_ACL_CONTENT_SIZEZERO,          /* 42 注册类型数据结构中的规则内容大小为0*/
    Help_ACL_FUNC_NULL,                 /* 43 注册类型数据结构中有函数指针为空*/
    Help_ACL_INIT_ERR,                  /* 44 ACL CBB已经完成初始化*/
    Help_ACL_NOT_INIT,                  /* 45 ACL CBB未成功初始化*/
    Help_ACL_PortNumError,              /* 46 端口范围的段数不合法 */ /* Add by w60786 for A82D17808 2007-07-13 */
    Help_ACL_Type_MallocError,          /* 47 为规则类型分配内存失败 */
    Help_ACL_Group_MallocError,         /* 48 为规则组分配内存失败 */
    Help_ACL_MatchOrderErr_Snd,         /* 49 规则匹配顺序错误 */
    Help_ACL_TYPE_BASIC_MallocErr,      /* 50 为基本规则类型分配内存失败 */
    Help_ACL_TYPE_ADV_MallocErr,        /* 51 为高级规则类型分配内存失败 */
    Help_ACL_TYPE_IF_MallocErr,         /* 52 为基于接口规则类型分配内存失败 */
    Help_ACL_TYPE_MAC_MallocErr,        /* 53 为基于MAC规则类型分配内存失败 */
    Help_ACL_GROUP_BASIC_MallocErr,     /* 54 为基本规则组分配内存失败 */
    Help_ACL_GROUP_ADV_MallocErr,       /* 55 为高级规则组分配内存失败 */
    Help_ACL_GROUP_IF_MallocErr,        /* 56 为基于接口的规则组分配内存失败 */
    Help_ACL_GROUP_MAC_MallocErr,       /* 57 为基于MAC规则组分配内存失败 */
    Help_ACL_WAITLIST_OpenFail,         /* 58 打开waitlist失败 */
    Help_ACL_WAITLIST_SetFail,          /* 59 设置waitlist失败 */
    Help_ACL_WAITLIST_GetFail,          /* 60 获取waitlist节点失败 */
    Help_ACL_WAITLIST_CloseFail,        /* 61 关闭waitlist失败 */
    Help_ACL_ERR_CreateSm,              /* 62 Fail to create semaphore */
    Help_ACL_NULL_POINTER,              /* 63 输入指针为空 */
    Help_ACL_TooMuchRulesINGroup,       /* 64 某规则组下的规则数超过了允许值*/
    Help_ACL_CALLBACK_EXIST,            /* 65 同一模块的回调函数已经注册 */
    Help_ACL_NotSupportOperType,        /* 66 不支持的操作类型,非创建和删除*/ 
    Help_ACL_ERR_GETMATCHCOUNT,         /* 67 获取PPI数据面的规则匹配统计信息失败 */
    Help_ACL_ERR_GETVRFINDEX,         /* 68 获取VRF Index失败 */
    Help_ACL_ERR_ICMPCODE  ,            /* 69 ICMP Code取值错误 */
    Help_ACL_ERR_ICMPTYPE  ,            /* 70 ICMP Type取值错误 */
    Help_ACL_ERR_PORTOPTYPE  ,          /* 71 端口操作字取值错误 */
    Help_ACL_ERR_SEMAPHORE_ADDNAMEDB, /*72 Fail to add semaphore shared variable to name DB */	   
    Help_ACL_ERR_ACC_ADDNAMEDB,    /*73 Fail to add g_pstAccACL_share shared variable to name DB */     
    Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB,    /*74 Fail to add g_pulAclGroupNumSum_share shared variable to name DB */     
    Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB, /*75 Fail to add g_pstACL_share shared variable to name DB */     
    Help_ACL_ACC_SHARE_MallocError, /*76 Fail to malloc g_pstAccACL_share global variable */
    Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError,   /*77 Fail to malloc g_pulAclGroupNumSum_share global variable */ 
    Help_ACL_GLOBALSTRUCT_SHARE_MallocError,   /*78 Fail to malloc g_pstACL_share global variable */
    Help_ACL_ERR_GETIFINDEX,
    Help_ACL_ERR_GETIFINDEX_NAMELEN,
    Help_ACL_ACL_STAT_INIT,
    Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH, /*82 Hash search function failed to search the group stat*/
    Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT,  /*83 Hash add function failed to add the group stat*/
    Help_ACL_ERR_STAT_DELETE_GROUP_HASH_SEARCH,
    Help_ACL_FM_SHARE_MallocError, /* 85 Failed to malloc  g_pbFM_share global variable */
    Help_ACL_ERR_FM_ADDNAMEDB, /* 86 Fail to add g_pbFM_share shared variable to name DB */
    Help_ACL_ERR_RULESTATUSUPDATE_NORULE,
    Help_ACL_ACC_SEMSHARE_MallocError,
    Help_ACL_RFC_GET_PRECONFIG_FAIL,
    Help_ACL_SETFWSTATISTICSWITCH_INVALID_SWITCH,
    Help_ACL_SETFWSTATISTICSWITCH_NULL_SWITCH,
    Help_ACL_GETFWSTATISTICSWITCH_NULLPTR,
    Help_ACL_GETFWSTATISTICSWITCH_NULL_SWITCH,
    Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_MALLOC,
    Help_ACL_STAT_ERR_FLOWSTATINIT_SWITCH_ADDNAMEDB,
    Help_ACL_STAT_ERR_FLOWSTATINIT_MALLOC,
    Help_ACL_STAT_ERR_FLOWSTATINIT_ADDNAMEDB,
    Help_ACL_STAT_ERR_ACL_INIT_SWITCH_MALLOC,
	Help_ACL_STAT_ERR_ACL_INIT_SWITCH_ADDNAMEDB,
    Help_ACL_STAT_ERR_ACL_INIT_SWITCH_STAT_HASHTABLE,
    Help_ACL_STAT_ERR_STATINIT_SWITCH_MALLOC,
    Help_ACL_STAT_ERR_STATINIT_SWITCH_ADDNAMEDB,
    Help_ACL_INIT_ERR_MALLOC_MODULE_ENABLE,
    Help_ACL_INIT_ERR_ADD_NAME_DB_MODULE_ENABLE,
    Help_ACL_INIT_ERR_CREATE_SYS_SPIN_LOCK,
    Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_INVALID_SWITCH,
    Help_ACL_DEBUG_SETFLOWSTATISTICSWITCH_NULL_SWITCH,
    Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULLPTR,
    Help_ACL_DEBUG_GETFLOWSTATISTICSWITCH_NULL_SWITCH,
    Help_ACL_DEBUG_CLEARALLFLOWSTATISTIC_NULL_SHARE,
    Help_ACL_TIMER_INIT_MALLOC_FAIL,
    Help_ACL_TIMER_INIT_NAMEDB_ADD_FAIL,
    Help_ACL_IPSAFE_INIT_FAIL,
    Help_ACL_Refresh_GRP_TIMER_INIT_MALLOC_FAIL,
    Help_ACL_Refresh_GRP_TIMER_INIT_NAMEDB_ADD_FAIL,
    Help_ACL_Refresh_GRP_TIMER_CREATE_FAIL,
    Help_ACL_COMMON_TIMER_INIT_MALLOC_FAIL,
    Help_ACL_WRONG_VLANID, /*VLAN ID is out of range*/
    Help_ACL_NO_RULES_EXIST, /*Indicates no rule exists in the group*/
    Help_ACL_ERR_EXT_ADV_ALREADY_REGISTERED, 
    Help_ACL_INVALID_VALAN_PRIORITY, /*VLAN priority has invalid value*/
    Help_ACL_Max,   /* 87 The max code of the enum. It is not the really error code. All the other error codes should be added before it. */
};


/**
* @defgroup enumACLFWERR E_ACLFW_ERR
* @ingroup ACLEC ACL Error Codes
* @par Prototype
* @code
* typedef enum enumACLFWERR
* {
*     ACLFW_OK=0,
*     ACLFW_FOUND=ACL_MODID+0x1000+1,
*     ACLFW_ERR_NONODE,
*     ACLFW_ERR_MEM,
*     ACLFW_ERR_NULL,
*     ACLFW_ERR_IFNAME,
*     ACLFW_ERR_PARA,
*     ACLFW_ERR_END_TABLE,
*     ACLFW_ERR_ALREADY_REGISTERED,
*     ACLFW_ERR_REGISTERED,
*     ACLFW_ERR_IF_TABLE,
*     ACLFW_ERR_PPI_NOREG,
*     ACLFW_ERR_PPI_CFG,
*     ACLFW_ERR_SFE_INIT_SWITCH_MALLOC,
*     ACLFW_ERR_SFE_INIT_DBG_SWITCH_MALLOC,
*     ACLFW_ERR_SFE_INIT_STAT_MALLOC,
*     ACLFW_ERR_INIT_CFGDB_MALLOC,
*     ACLFW_ERR_SFE_INIT_SWITCH_ADDNAMEDB,
*     ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB,
*     ACLFW_ERR_SFE_INIT_STAT_ADDNAMEDB,
*     ACLFW_ERR_INIT_CFGDB_ADDNAMEDB,
*     ACLFW_ERR_SFE_CLEARSTAT_INIT,
*     ACLFW_ERR_SFE_SETENABLE_INIT,
*     ACLFW_ERR_SFE_GETENABLE_INIT,
*     ACLFW_ERR_SFE_SETDEBUG_INIT,
*     ACLFW_ERR_SFE_GETDEBUG_INIT,
*     ACLFW_ERR_SFE_GETSTAT_INIT,
*     ACLFW_ERR_SFE_CFGSECPOLICY_INIT,
*     ACLFW_ERR_SFE_SECPOLICYOPEN_INIT,
*     ACLFW_ERR_SFE_GETVCPUSTAT_VCPU,
*     ACLFW_ERR_SFE_GETVCPUSTAT_NULLPTR,
*     ACLFW_ERR_SFE_SHOWVCPUSTAT_VCPU,
*     ACLFW_ERR_SFE_GETGROUPSTAT_GROUP,
*     ACLFW_ERR_SFE_GETGROUPSTAT_NULLPTR,
*     ACLFW_ERR_SFE_SHOWGROUPSTAT_GROUP,
*     ACLFW_ERR_GETVCPUSTAT_NULLPTR,
*     ACLFW_ERR_GETGROUPSTAT_NULLPTR,
*     ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT,
*     ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_REGISTER,
*     ACLFW_ERR_SFE_ACLFW_SECPOLICY_GETNEXT_ITR,
*     ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_INIT,
*     ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_CLOSELIST,
*     ACLFW_ERR_HASH_INIT,
*     ACLFW_ERR_SFE_GETVCPUSTAT_INIT,
*     ACLFW_ERR_SFE_GETGROUPSTAT_INIT,
*     ACLFW_ERR_SFE_ACLFW_GETSTAT_LOCK,
*     ACLFW_ERR_SFE_ACLFW_GETSTAT_UNLOCK,
*     ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_LOCK,
*     ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_UNLOCK,
*     ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_LOCK,
*     ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_UNLOCK,
*     ACLFW_ERR_ACLFW_STATISTIC_TIMER_LOCK,
*     ACLFW_ERR_ACLFW_STATISTIC_TIMER_UNLOCK,
*     ACLFW_ERR_SFE_ACLFW_CFG_SECPOLICY_CONFIG,
*     ACLFW_ERR_SFE_GETCFGBYIF_INIT,
*     ACLFW_ERR_SFE_ACLFW_GETGROUP_STAT_GROUPNOTFOUND
*     ACLFW_ERR_ACLFW_STAT_OPENLIST_REGISTER,
*     ACLFW_ERR_ACLFW_STAT_GETNEXT_ITERATOR,
*     ACLFW_ERR_ACLFW_STAT_CLOSELIST_ITERATOR,
*     ACLFW_ERR_PROTOCOL_STACK_HOOK,
*     ACLFW_ERR_INIT_STAT_TIMER,
*     ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC,
*     ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE,
*     ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD,
*     ACLFW_ERR_GET_PRECONFIG_FAIL,
*     ACLFW_ERR_END
* }E_ACLFW_ERR;
* @endcode 
* 
* @par Description
* This enum consists of ACL FW error codes.
*
* @datastruct ACLFW_OK=0 Indicates Success
* @datastruct ACLFW_FOUND=ACL_MODID+0x1000+1 Indicates FW found error code
* @datastruct ACLFW_ERR_NONODE Indicates no more items exist to iterate
* @datastruct ACLFW_ERR_MEM Indicates error memory
* @datastruct ACLFW_ERR_NULL Indicates error null
* @datastruct ACLFW_ERR_IFNAME Indicates error in interface name
* @datastruct ACLFW_ERR_PARA Indicates parameter error
* @datastruct ACLFW_ERR_END_TABLE Indicates end of table
* @datastruct ACLFW_ERR_ALREADY_REGISTERED Indicates already registered
* @datastruct ACLFW_ERR_REGISTERED Indicates error in registration
* @datastruct ACLFW_ERR_IF_TABLE Indicates error in interface tables
* @datastruct ACLFW_ERR_PPI_NOREG Indicates no PPI call back function registered
* @datastruct ACLFW_ERR_PPI_CFG Indicates error in PPI configuration
* @datastruct ACLFW_ERR_SFE_INIT_SWITCH_MALLOC Indicates error in initializing switch malloc
* @datastruct ACLFW_ERR_SFE_INIT_DBG_SWITCH_MALLOC Indicates error in initializing debug switch malloc
* @datastruct ACLFW_ERR_SFE_INIT_STAT_MALLOC Indicates error in initializing stat malloc
* @datastruct ACLFW_ERR_INIT_CFGDB_MALLOC Indicates error in initializing configuration DB malloc
* @datastruct ACLFW_ERR_SFE_INIT_SWITCH_ADDNAMEDB Indicates error in initializing switch add name DB
* @datastruct ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB Indicates error in initializing switch add name DB
* @datastruct ACLFW_ERR_SFE_INIT_STAT_ADDNAMEDB Indicates error in initializing stat add name DB
* @datastruct ACLFW_ERR_INIT_CFGDB_ADDNAMEDB Indicates error in initializing configuration DB add name DB
* @datastruct ACLFW_ERR_SFE_CLEARSTAT_INIT Indicates error in clear stat init
* @datastruct ACLFW_ERR_SFE_SETENABLE_INIT Indicates error in SFE set enable
* @datastruct ACLFW_ERR_SFE_GETENABLE_INIT Indicates error in get enable
* @datastruct ACLFW_ERR_SFE_SETDEBUG_INIT Indicates error in set debug
* @datastruct ACLFW_ERR_SFE_GETDEBUG_INIT Indicates error in get debug
* @datastruct ACLFW_ERR_SFE_GETSTAT_INIT Indicates error in get stat init
* @datastruct ACLFW_ERR_SFE_CFGSECPOLICY_INIT Indicates error in policy init
* @datastruct ACLFW_ERR_SFE_SECPOLICYOPEN_INIT Indicates error in policy open init
* @datastruct ACLFW_ERR_SFE_GETVCPUSTAT_VCPU Indicates error in getting VCPU statistics
* @datastruct ACLFW_ERR_SFE_GETVCPUSTAT_NULLPTR Indicates null pointer
* @datastruct ACLFW_ERR_SFE_SHOWVCPUSTAT_VCPU Indicates error in showing VCPU stat
* @datastruct ACLFW_ERR_SFE_GETGROUPSTAT_GROUP Indicates error in getting group stat group
* @datastruct ACLFW_ERR_SFE_GETGROUPSTAT_NULLPTR Indicates null pointer
* @datastruct ACLFW_ERR_SFE_SHOWGROUPSTAT_GROUP Indicates error in showing group stat group
* @datastruct ACLFW_ERR_GETVCPUSTAT_NULLPTR Indicates VCPU stat null pointer
* @datastruct ACLFW_ERR_GETGROUPSTAT_NULLPTR Indicates get group stat null pointer
* @datastruct ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT Indicates sec policy open init
* @datastruct ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_REGISTER Indicates open register
* @datastruct ACLFW_ERR_SFE_ACLFW_SECPOLICY_GETNEXT_ITR Indicates get next ITR
* @datastruct ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_INIT Indicates close init
* @datastruct ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_CLOSELIST Indicates error in closing list
* @datastruct ACLFW_ERR_HASH_INIT Indicates error hash init
* @datastruct ACLFW_ERR_SFE_GETVCPUSTAT_INIT Indicates error in get init
* @datastruct ACLFW_ERR_SFE_GETGROUPSTAT_INIT Indicates get group stat init
* @datastruct ACLFW_ERR_SFE_ACLFW_GETSTAT_LOCK Indicates get stat lock
* @datastruct ACLFW_ERR_SFE_ACLFW_GETSTAT_UNLOCK Indicates get stat unlock
* @datastruct ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_LOCK Indicates lock
* @datastruct ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_UNLOCK Indicates unlock
* @datastruct ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_LOCK Indicates lock
* @datastruct ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_UNLOCK Indicates unlock
* @datastruct ACLFW_ERR_ACLFW_STATISTIC_TIMER_LOCK Indicates timer lock
* @datastruct ACLFW_ERR_ACLFW_STATISTIC_TIMER_UNLOCK Indicates timer unlock
* @datastruct ACLFW_ERR_SFE_ACLFW_CFG_SECPOLICY_CONFIG Indicates set policy config
* @datastruct ACLFW_ERR_SFE_GETCFGBYIF_INIT Indicates get CFG by if init
* @datastruct ACLFW_ERR_SFE_ACLFW_GETGROUP_STAT_GROUPNOTFOUND Indicates group not found
* @datastruct ACLFW_ERR_ACLFW_STAT_OPENLIST_REGISTER Indicates open list register
* @datastruct ACLFW_ERR_ACLFW_STAT_GETNEXT_ITERATOR Indicates iterator operation failed
* @datastruct ACLFW_ERR_ACLFW_STAT_CLOSELIST_ITERATOR Indicates 
* @datastruct ACLFW_ERR_PROTOCOL_STACK_HOOK Indicates stack hook
* @datastruct ACLFW_ERR_INIT_STAT_TIMER Indicates stat timer
* @datastruct ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC Indicates timer malloc
* @datastruct ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE Indicates timer create
* @datastruct ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD Indicates timer DBADD
* @datastruct ACLFW_ERR_GET_PRECONFIG_FAIL Indicates error in getting pre-configuration data
* @datastruct ACLFW_ERR_END Indicates error end
*/

/* Bhaskar 2009-10-24: Declarations moved from shell to fw_acl_common.h file */
/* Error codes for ACLFW */
typedef enum enumACLFWERR
{
    ACLFW_OK = 0,
    ACLFW_FOUND = ACL_MODID + 0x1000 + 1,        /* 1 找到节点 */
    ACLFW_ERR_NONODE,                              /* 2 节点没有找到 */
    ACLFW_ERR_MEM,                                 /* 3 内存分配失败 */
    ACLFW_ERR_NULL,                                /* 4 指针空 */
    ACLFW_ERR_IFNAME,                              /* 5 接口名错误*/
    ACLFW_ERR_PARA,                                /* 6 参数无效 */
    ACLFW_ERR_END_TABLE,                           /* 7 表末尾*/
    ACLFW_ERR_ALREADY_REGISTERED,                  /* 8 注册过了*/
    ACLFW_ERR_REGISTERED,                          /* 9 注册失败*/
    ACLFW_ERR_IF_TABLE,                            /* 10 注册失败*/
    ACLFW_ERR_PPI_NOREG,                            /* 11 未注册PPI下发接口*/
    ACLFW_ERR_PPI_CFG,                              /* 12 PPI下发配置失败*/
    ACLFW_ERR_SFE_INIT_SWITCH_MALLOC,              /* 11 Initialization for aclfw switch failed*/ 
    ACLFW_ERR_SFE_INIT_DBG_SWITCH_MALLOC,          /* 12 Initialization for aclfw debug switch failed*/
    ACLFW_ERR_SFE_INIT_STAT_MALLOC,                /* 13 Initialization for aclfw stat failed*/
    ACLFW_ERR_INIT_CFGDB_MALLOC,                   /* 14 Initialization for aclfw cfg failed*/ 
    ACLFW_ERR_SFE_INIT_SWITCH_ADDNAMEDB,
    ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB,
    ACLFW_ERR_SFE_INIT_STAT_ADDNAMEDB,
    ACLFW_ERR_INIT_CFGDB_ADDNAMEDB,
    ACLFW_ERR_SFE_CLEARSTAT_INIT,
    ACLFW_ERR_SFE_SETENABLE_INIT,
    ACLFW_ERR_SFE_GETENABLE_INIT,
    ACLFW_ERR_SFE_SETDEBUG_INIT,
    ACLFW_ERR_SFE_GETDEBUG_INIT,    
    ACLFW_ERR_SFE_GETSTAT_INIT,
    ACLFW_ERR_SFE_CFGSECPOLICY_INIT,
    ACLFW_ERR_SFE_SECPOLICYOPEN_INIT,    
    ACLFW_ERR_SFE_GETVCPUSTAT_VCPU,
    ACLFW_ERR_SFE_GETVCPUSTAT_NULLPTR,
    ACLFW_ERR_SFE_SHOWVCPUSTAT_VCPU,
    ACLFW_ERR_SFE_GETGROUPSTAT_GROUP,
    ACLFW_ERR_SFE_GETGROUPSTAT_NULLPTR,
    ACLFW_ERR_SFE_SHOWGROUPSTAT_GROUP,
    ACLFW_ERR_GETVCPUSTAT_NULLPTR,
    ACLFW_ERR_GETGROUPSTAT_NULLPTR,
    ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT,
    ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_REGISTER,
    ACLFW_ERR_SFE_ACLFW_SECPOLICY_GETNEXT_ITR,
    ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_INIT,
    ACLFW_ERR_SFE_ACLFW_SECPOLICY_CLOSE_CLOSELIST,
    ACLFW_ERR_HASH_INIT,
    ACLFW_ERR_SFE_GETVCPUSTAT_INIT,
    ACLFW_ERR_SFE_GETGROUPSTAT_INIT,
    ACLFW_ERR_SFE_ACLFW_GETSTAT_LOCK,
    ACLFW_ERR_SFE_ACLFW_GETSTAT_UNLOCK,
    ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_LOCK,
    ACLFW_ERR_SFE_ACLFW_GETVCPUSTAT_UNLOCK,
    ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_LOCK,
    ACLFW_ERR_SFE_ACLFW_GETGROUPSTAT_UNLOCK,
    ACLFW_ERR_ACLFW_STATISTIC_TIMER_LOCK,
    ACLFW_ERR_ACLFW_STATISTIC_TIMER_UNLOCK,
    ACLFW_ERR_SFE_ACLFW_CFG_SECPOLICY_CONFIG,
	ACLFW_ERR_SFE_GETCFGBYIF_INIT,
    ACLFW_ERR_SFE_ACLFW_GETGROUP_STAT_GROUPNOTFOUND,
    ACLFW_ERR_ACLFW_STAT_OPENLIST_REGISTER,
    ACLFW_ERR_ACLFW_STAT_GETNEXT_ITERATOR,
    ACLFW_ERR_ACLFW_STAT_CLOSELIST_ITERATOR,
    ACLFW_ERR_PROTOCOL_STACK_HOOK,
    ACLFW_ERR_INIT_STAT_TIMER,
    ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC,
    ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE,
    ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD,
    ACLFW_ERR_GET_PRECONFIG_FAIL,
    ACLFW_ERR_END                                  /* 11 表结束*/
}E_ACLFW_ERR;

/**
* @defgroup enum_AclAcc Accelerated ACL Error Codes
* @ingroup ACLEC ACL Error Codes
* @par Prototype
* @code
* enum enum_AclAcc
* {
*     AclAcc_PleaseWait,
*     AclAcc_Done,
*     AclAcc_AlreadyRun,
*     AclAcc_Disabled,
*     AclAcc_Enabled,
*     AclAcc_NOTE1,
*     AclAcc_NOTE2,
*     AclAcc_AclGroup,
*     AclAcc_TitleLine1,
*     AclAcc_TitleLine2,
*     AclAcc_AccFail,
*     AclAcc_NoRule,
*     AclAcc_TotalRules,
*     AclAcc_Unfit,
*     AclAcc_UnfitForTime,
*     AclAcc_UnfitForFrag,
*     AclAcc_UnfitForPre,
*     AclAcc_UnfitForTos,
*     AclAcc_UnfitFor5Same,
*     AclAcc_UnfitForVrf,
*     AclAcc_UnfitForCon,
*     AclAcc_MAX
* };
* @endcode 
* 
* @par Description
* This enum consists of error for accelerated ACL.
*
* @datastruct AclAcc_PleaseWait Indicates please wait
* @datastruct AclAcc_Done Indicates done
* @datastruct AclAcc_AlreadyRun Indicates already runnig
* @datastruct AclAcc_Disabled Indicates disabled
* @datastruct AclAcc_Enabled Indicates enabled 
* @datastruct AclAcc_NOTE1 Indicates note e1
* @datastruct AclAcc_NOTE2 Indicates note e2
* @datastruct AclAcc_AclGroup Indicates ACL group
* @datastruct AclAcc_TitleLine1 Indicates title line1
* @datastruct AclAcc_TitleLine2 Indicates title line2
* @datastruct AclAcc_AccFail Indicates acceleration failed
* @datastruct AclAcc_NoRule Indicates no rule
* @datastruct AclAcc_TotalRules Indicates total rules
* @datastruct AclAcc_Unfit Indicates unfit
* @datastruct AclAcc_UnfitForTime Indicates unfit for time
* @datastruct AclAcc_UnfitForFrag Indicates unfit for fragment
* @datastruct AclAcc_UnfitForPre Indicates unfit for precedence
* @datastruct AclAcc_UnfitForTos Indicates unfit for TOS
* @datastruct AclAcc_UnfitFor5Same Indicates unfit for same
* @datastruct AclAcc_UnfitForVrf Indicates unfit for VRF
* @datastruct AclAcc_UnfitForCon Indicates unit for con
* @datastruct AclAcc_MAX Indicates the maximum value for this enum. All error codes should be added before this 
* enum element
*/
/* Error Codes and Structures for Accelerated ACL */
enum enum_AclAcc
{
    AclAcc_PleaseWait,
    AclAcc_Done,
    AclAcc_AlreadyRun,
    AclAcc_Disabled,
    AclAcc_Enabled,
    AclAcc_NOTE1,
    AclAcc_NOTE2,
    AclAcc_AclGroup,
    AclAcc_TitleLine1,
    AclAcc_TitleLine2,
    AclAcc_AccFail,
    AclAcc_NoRule,
    AclAcc_TotalRules,
    AclAcc_Unfit,           /* Add by wangning for BYDD03707 */  
    AclAcc_UnfitForTime,
    AclAcc_UnfitForFrag,
    AclAcc_UnfitForPre,
    AclAcc_UnfitForTos,
    AclAcc_UnfitFor5Same,
    AclAcc_UnfitForVrf,
    AclAcc_UnfitForCon,
    
    AclAcc_MAX
};


/**
* @defgroup enum_AclTrng ACL Timer Error Codes
* @ingroup ACLEC ACL Error Codes
* @par Prototype
* @code
* enum enum_AclTrng
* {
*     ACL_TRNG_OK=0,
*     ACL_TRNG_ADD_TMR_RNG_NULL_NAME,
*     ACL_TRNG_ADD_TMR_RNG_INVALID_NAME_LEN,
*     ACL_TRNG_ADD_TMR_RNG_MAX_TIMERS_REACHED,
*     ACL_TRNG_ADD_TMR_RNG_TIMER_CREATION_FAILED,
*     ACL_TRNG_ADD_TMR_RNG_ALREADY_EXIST,
*     ACL_TRNG_DEL_TMR_RNG_NULL_NAME,
*     ACL_TRNG_DEL_TMR_RNG_NO_TIMERS_EXISTS,
*     ACL_TRNG_DEL_TMR_RNG_INVALID_NAME_LEN,
*     ACL_TRNG_DEL_TMR_RNG_NO_TIMER_IN_POSITION,
*     ACL_TRNG_DEL_TMR_RNG_NOEXIST,
*     ACL_TRNG_ADD_PER_TMR_NULL_POINTER_FOR_TIMER,
*     ACL_TRNG_ADD_PER_TMR_CREATION_FAILED,
*     ACL_TRNG_ADD_PER_TMR_DUPLICATE_TIME_RANGE,
*     ACL_TRNG_ADD_PER_TMR_WRONG_TMR_INDEX,
*     ACL_TRNG_ADD_PER_TMR_MAX_TIMERS_REACHED,
*     ACL_TRNG_ADD_PER_TMR_FIRST_INSERT_FAILED,
*     ACL_TRNG_ADD_PER_TMR_INSERT_FAILED,
*     ACL_TRNG_ADD_PER_TMR_DUPLICATE_INDEX,
*     ACL_TRNG_DEL_PER_TMR_NULL_PTR,
*     ACL_TRNG_DEL_PER_TMR_NO_PERIODIC_TIMERS,
*     ACL_TRNG_DEL_PER_TMR_NO_TIMER_EXIST,
*     ACL_TRNG_ADD_ABS_TMR_NULL_POINTER_FOR_TIMER,
*     ACL_TRNG_ADD_ABS_TMR_CREATION_FAILED,
*     ACL_TRNG_ADD_ABS_TMR_DUPLICATE_TIME_RANGE,
*     ACL_TRNG_ADD_ABS_TMR_WRONG_TMR_INDEX,
*     ACL_TRNG_ADD_ABS_TMR_MAX_TIMERS_REACHED,
*     ACL_TRNG_ADD_ABS_TMR_FIRST_INSERT_FAILED,
*     ACL_TRNG_ADD_ABS_TMR_DUPLICATE_FAILED,
*     ACL_TRNG_ADD_ABS_TMR_INSERT_FAILED,
*     ACL_TRNG_DEL_ABS_TMR_NULL_PTR,
*     ACL_TRNG_DEL_ABS_TMR_NO_ABSOLUTE_TIMERS,
*     ACL_TRNG_DEL_ABS_TMR_NO_TIMER_EXIST,
*     ACL_TRNG_GET_CUR_TIME_FAILED,
*     ACL_TRNG_ORDER_INS_ABS_NODE_FAIL,
*     ACL_TRNG_ORDER_INS_PER_NODE_FAIL,
*     ACL_TRNG_SHOW_CUR_TIME_FAIL,
*     ACL_TRNG_ADD_TMR_RNG_NAME_SHOULD_NOT_BE_ALL,
*     ACL_TRNG_ADD_PER_TMR_INVALID_DAY_FLAG,
*     ACL_TRNG_ADD_PER_TMR_NO_DAY_FLAG_SET,
*     ACL_TRNG_ADD_PER_TMR_START_TIME_MORE_THAN_END_TIME,
*     ACL_TRNG_ADD_ABS_TMR_START_TIME_MORE_THAN_END_TIME,
*     ACL_TRNG_ADD_PER_TMR_INVALID_TIME_RANGE,
*     ACL_TRNG_ADD_PER_TMR_INVALID__INVALID_TIME_RANGE,
*     ACL_TRNG_ADD_ABS_TMR_TIME_OUT_OF_RANGE,
*     ACL_TRNG_TIMES_TO_SECONDS_WRONG_DATE,
*     ACL_TRNG_ADD_PER_TMR_INVALID_INDEX,
*     ACL_TRNG_ADD_ABS_TMR_INVALID_INDEX,
*     ACL_TRNG_TIME_TO_SECONDS_WRONG_HOUR_MINUTE,
*     ACL_TRNG_TIME_TO_SECONDS_WRONG_DATE,
*     ACL_TRNG_TIME_TO_SECONDS__CONVERSION_FAILED,
*     ACL_TRNG_ADD_ABS_TMR_MAX_TIME_CALCULATION_FAILED,
*     ACL_TRNG_TIME_TO_SECONDS_NULL_POINTER,
*     ACL_TRNG_REFRESH_BEGIN_TIME_GET_FAILED,
*     ACL_TRNG_REFRESH_BEGIN_TIMER_CREATION_FAILED,
*     ACL_TRNG_INIT_FAILED
* }
* @endcode 
* 
* @par Description
* This enum consists of error for ACL TRNG.
* 
* @datastruct ACL_TRNG_OK=0 Normal return
* @datastruct ACL_TRNG_ADD_TMR_RNG_NULL_NAME Indicates null name
* @datastruct ACL_TRNG_ADD_TMR_RNG_INVALID_NAME_LEN Indicates invalid name length
* @datastruct ACL_TRNG_ADD_TMR_RNG_MAX_TIMERS_REACHED Indicates max timers reached
* @datastruct ACL_TRNG_ADD_TMR_RNG_TIMER_CREATION_FAILED Indicates timer creation failed
* @datastruct ACL_TRNG_ADD_TMR_RNG_ALREADY_EXIST Indicates already exist
* @datastruct ACL_TRNG_DEL_TMR_RNG_NULL_NAME Indicates null name
* @datastruct ACL_TRNG_DEL_TMR_RNG_NO_TIMERS_EXISTS Indicates timers exists
* @datastruct ACL_TRNG_DEL_TMR_RNG_INVALID_NAME_LEN Indicates invalid name length
* @datastruct ACL_TRNG_DEL_TMR_RNG_NO_TIMER_IN_POSITION Indicates timer in position
* @datastruct ACL_TRNG_DEL_TMR_RNG_NOEXIST Indicates range does not exist
* @datastruct ACL_TRNG_ADD_PER_TMR_NULL_POINTER_FOR_TIMER Indicates pointer for timer
* @datastruct ACL_TRNG_ADD_PER_TMR_CREATION_FAILED Indicates creation of timer failed
* @datastruct ACL_TRNG_ADD_PER_TMR_DUPLICATE_TIME_RANGE Indicates duplicate time range
* @datastruct ACL_TRNG_ADD_PER_TMR_WRONG_TMR_INDEX Indicates wrong timer index
* @datastruct ACL_TRNG_ADD_PER_TMR_MAX_TIMERS_REACHED Indicates max timers reached
* @datastruct ACL_TRNG_ADD_PER_TMR_FIRST_INSERT_FAILED Indicates first insert failed
* @datastruct ACL_TRNG_ADD_PER_TMR_INSERT_FAILED Indicates insert failed
* @datastruct ACL_TRNG_ADD_PER_TMR_DUPLICATE_INDEX Indicates timer duplicate index
* @datastruct ACL_TRNG_DEL_PER_TMR_NULL_PTR Indicates timer null pointer
* @datastruct ACL_TRNG_DEL_PER_TMR_NO_PERIODIC_TIMERS Indicates no periodic timers
* @datastruct ACL_TRNG_DEL_PER_TMR_NO_TIMER_EXIST Indicates no timer exist
* @datastruct ACL_TRNG_ADD_ABS_TMR_NULL_POINTER_FOR_TIMER Indicates null pointer for timer
* @datastruct ACL_TRNG_ADD_ABS_TMR_CREATION_FAILED Indicates creation of timer failed
* @datastruct ACL_TRNG_ADD_ABS_TMR_DUPLICATE_TIME_RANGE Indicates duplicate time range
* @datastruct ACL_TRNG_ADD_ABS_TMR_WRONG_TMR_INDEX Indicates wrong timer index
* @datastruct ACL_TRNG_ADD_ABS_TMR_MAX_TIMERS_REACHED Indicates max timers reached
* @datastruct ACL_TRNG_ADD_ABS_TMR_FIRST_INSERT_FAILED Indicates first insert failed
* @datastruct ACL_TRNG_ADD_ABS_TMR_DUPLICATE_FAILED Indicates duplicate failed
* @datastruct ACL_TRNG_ADD_ABS_TMR_INSERT_FAILED Indicates insert failed
* @datastruct ACL_TRNG_DEL_ABS_TMR_NULL_PTR Indicates null pointer
* @datastruct ACL_TRNG_DEL_ABS_TMR_NO_ABSOLUTE_TIMERS Indicates no absolute timers
* @datastruct ACL_TRNG_DEL_ABS_TMR_NO_TIMER_EXIST Indicates no timer exist
* @datastruct ACL_TRNG_GET_CUR_TIME_FAILED Indicates getting current timer failed
* @datastruct ACL_TRNG_ORDER_INS_ABS_NODE_FAIL Indicates order insertion in absolute node failed
* @datastruct ACL_TRNG_ORDER_INS_PER_NODE_FAIL Indicates order insertion in periodic node failed
* @datastruct ACL_TRNG_SHOW_CUR_TIME_FAIL Indicates displaying current timer failed
* @datastruct ACL_TRNG_ADD_TMR_RNG_NAME_SHOULD_NOT_BE_ALL Indicates should not be ALL
* @datastruct ACL_TRNG_ADD_PER_TMR_INVALID_DAY_FLAG Indicates day flag
* @datastruct ACL_TRNG_ADD_PER_TMR_NO_DAY_FLAG_SET Indicates no flag is set
* @datastruct ACL_TRNG_ADD_PER_TMR_START_TIME_MORE_THAN_END_TIME Indicates periodic timer's start timer is more than 
* the end time
* @datastruct ACL_TRNG_ADD_ABS_TMR_START_TIME_MORE_THAN_END_TIME Indicates absolute timer's start timer is more than 
* the end time
* @datastruct ACL_TRNG_ADD_PER_TMR_INVALID_TIME_RANGE Indicates invalid time range
* @datastruct ACL_TRNG_ADD_PER_TMR_INVALID__INVALID_TIME_RANGE Indicates invalid time range
* @datastruct ACL_TRNG_ADD_ABS_TMR_TIME_OUT_OF_RANGE Indicates time out of range
* @datastruct ACL_TRNG_TIMES_TO_SECONDS_WRONG_DATE Indicates seconds wrong date
* @datastruct ACL_TRNG_ADD_PER_TMR_INVALID_INDEX Indicates invalid index for adding the periodic timer
* @datastruct ACL_TRNG_ADD_ABS_TMR_INVALID_INDEX Indicates invalid index for adding the absolute timer
* @datastruct ACL_TRNG_TIME_TO_SECONDS_WRONG_HOUR_MINUTE Indicates wrong hour minute
* @datastruct ACL_TRNG_TIME_TO_SECONDS_WRONG_DATE Indicates wrong date
* @datastruct ACL_TRNG_TIME_TO_SECONDS__CONVERSION_FAILED Indicates conversion failed
* @datastruct ACL_TRNG_ADD_ABS_TMR_MAX_TIME_CALCULATION_FAILED Indicates calculation of MAX time failed
* @datastruct ACL_TRNG_TIME_TO_SECONDS_NULL_POINTER Indicates null pointer
* @datastruct ACL_TRNG_REFRESH_BEGIN_TIME_GET_FAILED Indicates getting the refreshed start time failed
* @datastruct ACL_TRNG_REFRESH_BEGIN_TIMER_CREATION_FAILED Indicates creation of refreshed timer failed
* @datastruct ACL_TRNG_INIT_FAILED Indicates timer initialization failed
*/

enum enum_AclTrng
{
    ACL_TRNG_OK = 0,
    ACL_TRNG_ADD_TMR_RNG_NULL_NAME,
    ACL_TRNG_ADD_TMR_RNG_INVALID_NAME_LEN,
    ACL_TRNG_ADD_TMR_RNG_MAX_TIMERS_REACHED,
    ACL_TRNG_ADD_TMR_RNG_TIMER_CREATION_FAILED,
    ACL_TRNG_ADD_TMR_RNG_ALREADY_EXIST,

    ACL_TRNG_DEL_TMR_RNG_NULL_NAME,
    ACL_TRNG_DEL_TMR_RNG_NO_TIMERS_EXISTS,
    ACL_TRNG_DEL_TMR_RNG_INVALID_NAME_LEN,
    ACL_TRNG_DEL_TMR_RNG_NO_TIMER_IN_POSITION,
    ACL_TRNG_DEL_TMR_RNG_NOEXIST,

    ACL_TRNG_ADD_PER_TMR_NULL_POINTER_FOR_TIMER,
    ACL_TRNG_ADD_PER_TMR_CREATION_FAILED,
    ACL_TRNG_ADD_PER_TMR_DUPLICATE_TIME_RANGE,
    ACL_TRNG_ADD_PER_TMR_WRONG_TMR_INDEX,
    ACL_TRNG_ADD_PER_TMR_MAX_TIMERS_REACHED,
    ACL_TRNG_ADD_PER_TMR_FIRST_INSERT_FAILED,
    ACL_TRNG_ADD_PER_TMR_INSERT_FAILED,
    ACL_TRNG_ADD_PER_TMR_DUPLICATE_INDEX,

    ACL_TRNG_DEL_PER_TMR_NULL_PTR,
    ACL_TRNG_DEL_PER_TMR_NO_PERIODIC_TIMERS,
    ACL_TRNG_DEL_PER_TMR_NO_TIMER_EXIST,

    ACL_TRNG_ADD_ABS_TMR_NULL_POINTER_FOR_TIMER,
    ACL_TRNG_ADD_ABS_TMR_CREATION_FAILED,
    ACL_TRNG_ADD_ABS_TMR_DUPLICATE_TIME_RANGE,
    ACL_TRNG_ADD_ABS_TMR_WRONG_TMR_INDEX,
    ACL_TRNG_ADD_ABS_TMR_MAX_TIMERS_REACHED,
    ACL_TRNG_ADD_ABS_TMR_FIRST_INSERT_FAILED,
    ACL_TRNG_ADD_ABS_TMR_DUPLICATE_FAILED,
    ACL_TRNG_ADD_ABS_TMR_INSERT_FAILED,

    ACL_TRNG_DEL_ABS_TMR_NULL_PTR,
    ACL_TRNG_DEL_ABS_TMR_NO_ABSOLUTE_TIMERS,
    ACL_TRNG_DEL_ABS_TMR_NO_TIMER_EXIST,

    ACL_TRNG_GET_CUR_TIME_FAILED,

    ACL_TRNG_ORDER_INS_ABS_NODE_FAIL,

    ACL_TRNG_ORDER_INS_PER_NODE_FAIL,

    ACL_TRNG_SHOW_CUR_TIME_FAIL,

    ACL_TRNG_ADD_TMR_RNG_NAME_SHOULD_NOT_BE_ALL,
    ACL_TRNG_ADD_PER_TMR_INVALID_DAY_FLAG,
    ACL_TRNG_ADD_PER_TMR_NO_DAY_FLAG_SET,
    ACL_TRNG_ADD_PER_TMR_START_TIME_MORE_THAN_END_TIME,
    ACL_TRNG_ADD_ABS_TMR_START_TIME_MORE_THAN_END_TIME,
    ACL_TRNG_ADD_PER_TMR_INVALID_TIME_RANGE,
    ACL_TRNG_ADD_PER_TMR_INVALID__INVALID_TIME_RANGE,
    ACL_TRNG_ADD_ABS_TMR_TIME_OUT_OF_RANGE,
    ACL_TRNG_TIMES_TO_SECONDS_WRONG_DATE,
    ACL_TRNG_ADD_PER_TMR_INVALID_INDEX,
    ACL_TRNG_ADD_ABS_TMR_INVALID_INDEX,
    ACL_TRNG_TIME_TO_SECONDS_WRONG_HOUR_MINUTE,
    ACL_TRNG_TIME_TO_SECONDS_WRONG_DATE,
    ACL_TRNG_TIME_TO_SECONDS__CONVERSION_FAILED,
    ACL_TRNG_ADD_ABS_TMR_MAX_TIME_CALCULATION_FAILED,
    ACL_TRNG_TIME_TO_SECONDS_NULL_POINTER,
    ACL_TRNG_REFRESH_BEGIN_TIME_GET_FAILED,
    ACL_TRNG_REFRESH_BEGIN_TIMER_CREATION_FAILED,
    ACL_TRNG_INIT_FAILED
};


/**
* @defgroup enumACLRFCERRCODE ACL RFC Error Codes
* @ingroup ACLEC ACL RFC Error Codes
* @par Prototype
* @code
* typedef enum enumACLRFCERRCODE
* {
*     ACL_RFC_SUCCESS = FWIPSAFE_OK,
*     ACL_RFC_CREATECHUNKFROMTOSPRE_MALLOC_FAIL = ACL_MODID + 0x4000 + 1,
*     ACL_RFC_CREATECHUNKFROMPREFIX_MALLOC_FAIL,
*     ACL_RFC_INIT_RULE_MALLOC_FAIL,
*     ACL_RFC_ERRORCODESTRUCTURE_NULL_PTR,
*     ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_RULE,
*     ACL_RFC_UNABLE_TO_CREATE_RULE,
*     ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_PHASE,
* }ACL_RFC_ERR_E;
* @endcode 
* 
* @par Description
* This enum consists of error for ACL RFC.
* 
* @datastruct ACL_RFC_SUCCESS=0 Normal return
* @datastruct ACL_RFC_CREATECHUNKFROMTOSPRE_MALLOC_FAIL Failed to create chunk from range
* @datastruct ACL_RFC_CREATECHUNKFROMPREFIX_MALLOC_FAIL Failed to create chunk from prefix
* @datastruct ACL_RFC_INIT_RULE_MALLOC_FAIL ACL RFC rule initialization failed
* @datastruct ACL_RFC_ERRORCODESTRUCTURE_NULL_PTR The input pointer is NULL
* @datastruct ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_RULE Unable to allocate memory for rule
* @datastruct ACL_RFC_UNABLE_TO_CREATE_RULE Unable to create rule
* @datastruct ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_PHASE Unable to allocate memory for PHASE
*/
typedef enum enumACLRFCERRCODE
{
    ACL_RFC_SUCCESS = 0,
    ACL_RFC_CREATECHUNKFROMTOSPRE_MALLOC_FAIL = ACL_MODID + 0x4000 + 1,
    ACL_RFC_CREATECHUNKFROMPREFIX_MALLOC_FAIL,
    ACL_RFC_INIT_RULE_MALLOC_FAIL,
    ACL_RFC_ERRORCODESTRUCTURE_NULL_PTR,
    ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_RULE,
    ACL_RFC_UNABLE_TO_CREATE_RULE,
    ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_PHASE,
} ACL_RFC_ERR_E;


/**
* @defgroup ACLS ACL Structures
* @ingroup accss ACL API Reference
* This section contains the structures.
*/

/**
* @defgroup ACLE ACL Enums
* @ingroup accss ACL API Reference
* This section contains the enums.
*/

/**
* @defgroup AclAccErr AclAccErrCode
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct AclAccErr
* {
*     ULONG unifit; 
*     ULONG ultype;
*     ULONG ulAclNum;
*     ULONG ulNodeID;
*     ULONG ulNodeID2;
* }AclAccErrCode;
* @endcode 
* 
* @par Description
* This structure consists of error codes returned during RFC table creation.
*
* @datastruct unifit This error code is not in use
* @datastruct ultype Indicates Type
* @datastruct ulAclNum Indicates ACL number
* @datastruct ulNodeID Indicates Node ID
* @datastruct ulNodeID2 Indicates second Node ID
*/

/* acl acceleration related error codes*/
typedef struct AclAccErr
{
    ULONG unifit; 
    ULONG ultype;
    ULONG ulAclNum;
    ULONG ulNodeID;
    ULONG ulNodeID2;
}AclAccErrCode;


/*define some macro of tcpip*/
#ifndef PROT_IP
 #define PROT_IP 0
#endif

#ifndef PROT_ICMP
 #define PROT_ICMP 1
#endif

#ifndef PROT_IGMP
 #define PROT_IGMP 2
#endif

#ifndef PROT_IPINIP
 #define PROT_IPINIP 4
#endif

#ifndef PROT_TCP
 #define PROT_TCP 6
#endif

#ifndef PROT_UDP
 #define PROT_UDP 17
#endif

#ifndef PROT_GRE
 #define PROT_GRE 47
#endif

#ifndef PROT_OSPF
 #define PROT_OSPF 89
#endif

#ifndef PROT_SCTP
 #define PROT_SCTP 132
#endif

#ifndef TH_SYN
 #define TH_SYN 0x02
#endif

/* Ethernet fragment type ARP */
#ifndef ETH_TYPE_ARP
 #define ETH_TYPE_ARP 0x0806
#endif

/* 规则组描述信息长度 */
#define ACL_DESCRIPTIONSTR_LEN  128

/* 规则类型ID取值范围 */
#define ACL_MIN_TYPEID  1
#define ACL_MAX_TYPEID  16

#define ACL_CFG_NOOPER  0 /*不配置标记*/
#define ACL_CFG_SET     1 /*配置标记*/
#define ACL_CFG_DEFAULT 2 /*恢复默认值标记*/

/* Added code to create special Rule to process UnTaggeg VLAN packets over
   VLAN Interface[HERT 3.3 Requirement]. */
#define ACL_CFG_UNTAG_VLAN_SET  3 

/*Added by eswar-r72335 Start
Added for configuring VLAN ID*/
#define VLANID_RANGE 0 /*To configure VLAN ID as range*/
#define VLAN_ID_START 1 /*Minimum value of VLAN ID*/
#define VLAN_ID_END 0xFFF /*Maximum value of VLAN ID*/
#define ACL_NO_VLANID 0xFFFF /*No VLAN ID in received packet*/
#define ACL_VLANTPID_SIZE 2 /*TPID size in VLAN header*/
#define ACL_MASK_TO_GETVLANID 0xFFF /*Mask to get VLAN ID*/
#define ACL_GETVLAN_PRIORITY(x) (x >> 13) /*Mask to get VLAN Priority*/
#define VLAN_PRIORITY_START 0   /* Minimum value of VLAN priority */
#define VLAN_PRIORITY_END 7     /* Maximum value of VLAN priority */
/* Added code to create special Rule to process UnTaggeg VLAN packets over
   VLAN Interface[HERT 3.3 Requirement]. */
#define VLAN_ID_UNTAGGED 0x1FFF 


/*Added by eswar-r72335 End*/

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */


/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/**********************************************************
*   规则相关宏定义
***********************************************************/
#define IPDEBUG_IFIN    1    /* 入接口过滤 */
#define IPDEBUG_IFOUT   2    /* 出接口过滤 */
#define IPDEBUG_IFANY   3    /* 入或出接口过滤 */
#define IPDEBUG_IFALL   4    /* 入与出接口过滤 */


/* 存放基于MAC的规则的帧类型取值 */
typedef enum tagExtendedMacACL_RuleType 
{   
    EXTENDEDMACACL_RULEID_NUNE,
    EXTENDEDMACACL_RULEID_TYPE,
    EXTENDEDMACACL_RULEID_LSAP
} EXTMACACL_IDTYPE_E;

/* 规则的操作值 */
#define    ACL_DENY         0 
#define    ACL_PERMIT       1
#define    ACL_NOTFOUND     2

/*This macros are used while setting the default action item
in ACLFW_CFG_SecPolocy*/
#define ACLFW_DENY 1
#define ACLFW_PERMIT 0

/**********************************************************
*   对外数据结构
***********************************************************/

/**
* @defgroup tagAclTypeInfo ACL_TYPE_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclTypeInfo
* {
*     ULONG ulTypeID;
*     ULONG ulLowNo;
*     ULONG ulUpNo;
* } ACL_TYPE_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of tag ACL Type information.
* 
* @datastruct ulTypeID Indicates ACL Type ID
* @datastruct ulLowNo Indicates minimum ACL group number
* @datastruct ulUpNo Indicates maximum ACL group number
*/
typedef struct tagAclTypeInfo
{
    ULONG ulTypeID;    /* 规则类型ID */
    ULONG ulLowNo;     /* 规则组序号下限 */
    ULONG ulUpNo;      /* 规则组序号上限 */
} ACL_TYPE_INFO_S;

/**
* @defgroup tagAclGroupInfo ACL_GROUP_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedefstructtagAclGroupInfo
* {
*     ULONGulTypeID;
*     ULONGulGroupNum;
*     ULONGulMatchOrder;
*     ULONGulStep;
*     CHARcACLDescription[ACL_DESCRIPTIONSTR_LEN];
*     ULONGulRuleNum;
* }ACL_GROUP_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL group information.
*
* @datastruct ulTypeID Indicates ACL Type ID
* @datastruct ulGroupNum Indicates ACL group number
* @datastruct ulMatchOrder Indicates ACL match order
* @datastruct ulStep Indicates step value, based on step value next rule ID is calculated
* @datastruct cACLDescription[ACL_DESCRIPTIONSTR_LEN] Indicates group description
* @datastruct ulRuleNum Indicates ACL rule number
*/
/*acl group info structure*/
typedef struct tagAclGroupInfo
{
    ULONG ulTypeID;                    /* 规则类型ID */
    ULONG ulGroupNum;                  /* 规则组序号 */
    ULONG ulMatchOrder;                /* 匹配顺序;0/1－配置顺序、1－自动顺序 */
    ULONG ulStep;                      /* 步长（1-20） */
    CHAR cACLDescription[ACL_DESCRIPTIONSTR_LEN];   /* 描述信息 */
    ULONG ulRuleNum;                   /* 规则数目 */
} ACL_GROUP_INFO_S;

/**
* @defgroup tagAclRuleInfo ACL_RULE_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclRuleInfo
* {
*     ULONG ulTypeID;
*     ULONG ulGroupNum;
*     ULONG ulRuleIndex;
*     ULONG ulCount;
*     VOID *pContentInfo;
*     BOOL_T bLog;
*     BOOL_T bEnable;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* } ACL_RULE_INFO_S;
* @endcode 
* 
* @par Description
* This structure is for tag acl rule information.
* 
* @datastruct ulTypeID Indicates ACL Rule Type ID
* @datastruct ulGroupNum Indicates ACL group number
* @datastruct ulRuleIndex Indicates ACL rule index
* @datastruct ulCount Indicates number of packets matching this rule
* @datastruct pContentInfo Indicates rule content information
* @datastruct bLog Indicates rule log status
* @datastruct bEnable Indicates time range status (enable/disable)
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/


/*acl rule info structure*/
typedef struct tagAclRuleInfo
{
    ULONG ulTypeID;        /*规则类型ID*/
    ULONG ulGroupNum;      /*规则组序号*/
    ULONG ulRuleIndex;     /*规则索引*/
    ULONG ulCount;         /*匹配应用计数*/
    VOID *pContentInfo;    /*规则内容*/
    BOOL_T bLog;           /*日志标志*/
    BOOL_T bEnable;                          /*Bind this rule with Timer*/
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];   /* Added by Vinay Gudur*/
    UCHAR ucPadding[3];                      /*ARM byte alignment ensured Defect Fix - BC3D03113*/
} ACL_RULE_INFO_S;

/**
* @defgroup tagACL_BasicContentInfo ACL_BASIC_CONTENT_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_BasicContentInfo
* {
*     ULONG ulAction;
*     ULONG ulFrag;
*     ULONG ulAddr;
*     ULONG ulMask;
*     ULONG ulVrfIndex;
* } ACL_BASIC_CONTENT_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of basic content information.
* 
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulFrag Indicates whether rule is for fragmented packet
* @datastruct ulAddr Indicates source IP address
* @datastruct ulMask Indicates source mask 
* @datastruct ulVrfIndex Indicates VRF index value
*/

/*Basic acl rule content info structure*/
typedef struct tagACL_BasicContentInfo
{
    ULONG ulAction;     /* 匹配成功后的动作 */
    ULONG ulFrag;       /* 是否带分片选项 */
    ULONG ulAddr;       /* 源地址*/
    ULONG ulMask;       /* 通配符*/

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;   /* VRF索引 */

    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} ACL_BASIC_CONTENT_INFO_S;


/**
* @defgroup tagACL_AdvanceContentInfo ACL_ADVANCE_CONTENT_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_AdvanceContentInfo
* {
*     ULONG ulAction;
*     ULONG ulFrag;
*     ULONG ulSrcAddr;
*     ULONG ulSrcMask;
*     ULONG ulDstAddr;
*     ULONG ulDstMask;
*     USHORT usSPBegin1;
*     USHORT usSPEnd1;
*     USHORT usSPBegin2;
*     USHORT usSPEnd2;
*     USHORT usDPBegin1;
*     USHORT usDPEnd1;
*     USHORT usDPBegin2;
*     USHORT usDPEnd2;
*     UCHAR ucPIDBegin;
*     UCHAR ucPIDEnd;
*     UCHAR ucPre;
*     UCHAR ucTos;
*     UCHAR ucDscp;
*     UCHAR ucPadding[3];
*     ULONG ulVrfIndex;
* } ACL_ADVANCE_CONTENT_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of advanced content information.
*
* @datastruct ULONGulAction Indicates ACL rule action (permit/deny)
* @datastruct ULONGulFrag Indicates whether rule supports fragmented packet
* @datastruct ULONGulSrcAddr Indicates source IP address
* @datastruct ULONGulSrcMask Indicates source mask
* @datastruct ULONGulDstAddr Indicates destination IP address 
* @datastruct ULONGulDstMask Indicates destination mask
* @datastruct USHORTusSPBegin1 Indicates first source port range start
* @datastruct USHORTusSPEnd1 Indicates first source port range end
* @datastruct USHORTusSPBegin2 Indicates second source port range start
* @datastruct USHORTusSPEnd2 Indicates second source port range end
* @datastruct USHORTusDPBegin1 Indicates first destination port range start
* @datastruct USHORTusDPEnd1 Indicates first destination port range end
* @datastruct USHORTusDPBegin2 Indicates second destination port range start
* @datastruct USHORTusDPEnd2 Indicates second destination port range end
* @datastruct UCHARucPIDBegin Indicates protocol ID range start
* @datastruct UCHARucPIDEnd Indicates protocol ID range end
* @datastruct UCHARucPre Indicates Pre value
* @datastruct UCHARucTos Indicates TOS value
* @datastruct UCHARucDscp Indicates DSCP value
* @datastruct ucPadding[3] Indicates padding
* @datastruct ULONGulVrfIndex Indicates VRF index value
*/

/*advance acl rule content info structure*/
typedef struct tagACL_AdvanceContentInfo 
{
    ULONG ulAction;     /* 匹配成功后的动作 */
    ULONG ulFrag;       /* 是否带分片选项 */
    ULONG ulSrcAddr;    /* 源地址 */
    ULONG ulSrcMask;    /* 源通配符 */
    ULONG ulDstAddr;    /* 目的地址 */
    ULONG ulDstMask;    /* 目的通配符 */
    
    /*Begin C02NEWR-ACL liangjicheng 2008-10-22
        source port is used for ICMP type- dest port is used for ICMP code  */
    USHORT usSPBegin1;  /* 第1段源端口范围的最小值 */
    USHORT usSPEnd1;    /* 第1段源端口范围的最大值 */
    USHORT usSPBegin2;  /* 第2段源端口范围的最小值 */
    USHORT usSPEnd2;    /* 第2段源端口范围的最大值 */  
    USHORT usDPBegin1;  /* 第1段目的端口范围的最小值 */
    USHORT usDPEnd1;    /* 第1段目的端口范围的最大值 */
    USHORT usDPBegin2;  /* 第2段目的端口范围的最小值 */
    USHORT usDPEnd2;    /* 第2段目的端口范围的最大值 */
     /*End C02NEWR-ACL liangjicheng 2008-10-22*/
    
    UCHAR ucPIDBegin;   /* 协议号范围最小值 */
    UCHAR ucPIDEnd;     /* 协议号范围最大值 */
    UCHAR ucPre;        /* 优先级 */
    UCHAR ucTos;        /* TOS值 */
    
    UCHAR ucDscp;       /* Dscp值 */
    UCHAR ucPadding[3]; /*ARM byte alignment ensured Defect Fix - BC3D03113*/
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;   /* VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} ACL_ADVANCE_CONTENT_INFO_S;


/**
* @defgroup tagACL_IfbasedContentInfo ACL_IFBASED_CONTENT_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_IfbasedContentInfo
* {
*     ULONG ulAction;
*     ULONG ulIfIndex;
* } ACL_IFBASED_CONTENT_INFO_S;
* @endcode 
* 
* @par Description
* This structure indicates If based content information.
* 
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulIfIndex Indicates interface index
*/

/* Interface based acl rule content info structure*/
typedef struct tagACL_IfbasedContentInfo
{
    ULONG ulAction;     /* 匹配成功后的动作 */
    ULONG ulIfIndex;    /* 接口索引，0xffffffff为ANY */
} ACL_IFBASED_CONTENT_INFO_S;


/**
* @defgroup tagACL_ExtMacContentInfo ACL_EXTMAC_CONTENT_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_ExtMacContentInfo
* {
*     ULONG ulAction;
*     UCHAR ucSrcMac[6];
*     UCHAR ucSrcMask[6]
*     UCHAR ucDstMac[6];
*     UCHAR ucDstMask[6]
*     ULONG ulFrameType;
*     USHORT usTypeCode;
*     USHORT usTypeMask;
*     USHORT usLaspCode;
*     USHORT usLaspMask;
*     USHORT usVlanIdStart;
*     USHORT usVlanIdEnd;
* }ACL_EXTMAC_CONTENT_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of external MAC content information.
*
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ucSrcMac[6] Indicates source MAC address
* @datastruct ucSrcMask[6] Indicates source mask
* @datastruct ucDstMac[6] Indicates destination MAC address
* @datastruct ucDstMask[6] Indicates destination mask
* @datastruct ulFrameType Indicates frame type
* @datastruct usTypeCode Indicates MAC type code
* @datastruct usTypeMask Indicates MAC type mask
* @datastruct usLaspCode Indicates MAC lasp code
* @datastruct usLaspMask Indicates MAC lasp mask
* @datastruct usVlanIdStart Indicates start of configured VLAN ID
* @datastruct usVlanIdEnd Indicates end of configured VLAN ID
*/


/* Extended MAC based acl rule content info structure*/
typedef struct tagACL_ExtMacContentInfo
{
    ULONG ulAction;         /* 匹配成功后的动作 */
    UCHAR ucSrcMac[6];      /* 源MAC */
    UCHAR ucSrcMask[6];     /* 源MAC通配符 */
    UCHAR ucDstMac[6];      /* 目的MAC */
    UCHAR ucDstMask[6];     /* 目的MAC通配符 */
    ULONG ulFrameType;      /* 帧类型 */
    USHORT usTypeCode;      /* type值 */
    USHORT usTypeMask;      /* type值通配符 */
    USHORT usLaspCode;      /* lasp值 */
    USHORT usLaspMask;      /* lasp值通配符 */
    /*Added by eswar-r72335 Start
      Added for configuring VLAN ID*/
    USHORT usVlanIdStart;
    USHORT usVlanIdEnd;
    /*Added by eswar-r72335 End*/    
    USHORT usVlanPriorityVal;  /*s72256- VAL priority*/
    USHORT usPadding;          /* s72256: Added 2 bytes for byte alignment */
} ACL_EXTMAC_CONTENT_INFO_S;


/**
* @defgroup tagAclRuleInfoOut ACL_RULE_INFO_OUT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_ExtMacContentInfo
* typedef struct tagAclRuleInfoOut
* {
*     ULONG ulTypeID;
*     ULONG ulGroupNum;
*     ULONG ulRuleIndex;
*     ULONG ulCount;
*     union
*     {
*         ACL_BASIC_CONTENT_INFO_S stBasicContentInfo;
*         ACL_ADVANCE_CONTENT_INFO_S stAdvContentInfo;
*         ACL_IFBASED_CONTENT_INFO_S stIfBasedContentInfo;
*         ACL_EXTMAC_CONTENT_INFO_S stExtMacContentInfo;
*     } stContent;
*     BOOL_T bLog;
*     BOOL_T bEnable;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* } ACL_RULE_INFO_OUT_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL rule information. 
*
* @datastruct ulTypeID Indicates ACL Type ID
* @datastruct ulGroupNum Indicates ACL group number
* @datastruct ulRuleIndex Indicates ACL rule number
* @datastruct ulCount Indicates number of packets matching this rule
* @datastruct stContent Indicates rule content information
* @datastruct stBasicContentInfo Indicates basic rule content information 
* @datastruct stAdvContentInfo Indicates advance rule content information 
* @datastruct stIfBasedContentInfo Indicates interface based rule content information 
* @datastruct stExtMacContentInfo Indicates external MAC based rule content information 
* @datastruct bLog Indicates the log status
* @datastruct bEnable Indicates whether time range is enabled or not
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/
/* acl rule info output structure */
typedef struct tagAclRuleInfoOut
{
    ULONG ulTypeID;        /*规则类型ID*/
    ULONG ulGroupNum;      /*规则组序号*/
    ULONG ulRuleIndex;     /*规则索引*/
    ULONG ulCount;         /*匹配应用计数*/
    union
    {
        ACL_BASIC_CONTENT_INFO_S stBasicContentInfo;
        ACL_ADVANCE_CONTENT_INFO_S stAdvContentInfo;
        ACL_IFBASED_CONTENT_INFO_S stIfBasedContentInfo;
        ACL_EXTMAC_CONTENT_INFO_S stExtMacContentInfo;
    } stContent;
    BOOL_T bLog;           /*日志标志*/
    BOOL_T bEnable;                           /*Bind this rule with Timer*/
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];    /* Added by Vinay Gudur*/
    UCHAR ucPadding[3];                       /*ARM byte alignment ensured Defect Fix - BC3D03113*/
} ACL_RULE_INFO_OUT_S;



/**
* @defgroup tagAclTypeRegisterInfo ACL_TYPE_REGISTER_INFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclTypeRegisterInfo
* {
*     ULONG ulTypeID;
*     ULONG ulLowNo;
*     ULONG ulUpNo;
*     ULONG ulRuleNodeSize;
*     ULONG (*pFuncComp)(VOID *, VOID *);
*     ULONG (*pFuncRuleComp)(VOID *, VOID *);
*     VOID* (*pFuncCreateNode)(VOID);
*     VOID (*pFuncReleaseNode)(VOID*);
* }ACL_TYPE_REGISTER_INFO_S;
* @endcode 
* 
* @par Description
* This structure consists of tag ACL Type Register information.
* 
* @datastruct ulTypeID Indicates ACL Rule type ID
* @datastruct ulLowNo Indicates group number range begin
* @datastruct ulUpNo Indicates group number range end
* @datastruct ulRuleNodeSize Indicates rule node size
* @datastruct (*pFuncComp)(VOID*,VOID*) Indicates callback function to check duplication
* of rules while adding the rule.
* @datastruct (*pFuncRuleComp)(VOID*,VOID*) Indicates callback function to check whether 
* received packet matches with rule.
* @datastruct (*pFuncCreateNode)(VOID) Indicates rule node creation callback function
* @datastruct (*pFuncReleaseNode)(VOID*) Indicates rule node release callback function
*/

/* 规则类型参数数据结构，注册规则类型时用作参数的数据结构 */
typedef struct tagAclTypeRegisterInfo
{
    ULONG ulTypeID;         /* 规则类型ID（5－16）*/
    ULONG ulLowNo;          /* 规则组序号下限*/
    ULONG ulUpNo;           /* 规则组序号上限*/
    ULONG ulRuleNodeSize;   /*规则内容大小（不能为0）*/
    /* 比较两个节点是否相同 */
    ULONG (*pFuncComp)(VOID *, VOID *);

    /* 比较一个规则节点是否和包匹配，前一个参数是规则内容，后一个参数是待匹配报文信息。*/
    ULONG (*pFuncRuleComp)(VOID *, VOID *); 

    /* 创建规则内容 */
    VOID* (*pFuncCreateNode)(VOID);

    /* 释放规则内容 */
    VOID (*pFuncReleaseNode)(VOID*); 
} ACL_TYPE_REGISTER_INFO_S;

/**
* @defgroup tagACL_RANGEBYMASK32 ACL_RANGEBYMASK32_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_RANGEBYMASK32 
* {
*     union
*     {
*         UCHAR ucCode[2];
*         USHORT usCode;
*     } unCode; 
*     union
*     {
*         UCHAR ucCodeMask[2];
*         USHORT usCodeMask;
*     } unCodeMask;
* }ACL_RANGEBYMASK32_S;
* @endcode 
* 
* @par Description
* This structure consists of range by mask 32 structure.
* 
* @datastruct ucCode[2] Indicates MAC based rules Lsap value
* @datastruct usCode Indicates MAC based rules Lsap value
* @datastruct unCode Indicates union for MAC based rules Lsap value
* @datastruct ucCodeMask[2] Indicates MAC based rules Lsap mask
* @datastruct usCodeMask Indicates MAC based rules Lsap mask
* @datastruct unCodeMask Indicates union for MAC based rules Lsap mask
*/
/* 存放基于MAC的规则的TYPE/LSAP值和掩码 */
typedef struct tagACL_RANGEBYMASK32 
{
    union
    {
        UCHAR ucCode[2];       
        USHORT usCode;
    } unCode; 
    union
    {
        UCHAR ucCodeMask[2];       
        USHORT usCodeMask;
    } unCodeMask;              
}ACL_RANGEBYMASK32_S;

/**
* @defgroup tagACL_Range32 ACL_RANGE32_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_Range32 
* {
*     ULONG ulAddr;
*     ULONG ulMask;
* } ACL_RANGE32_S;
* @endcode 
* 
* @par Description
* This structure consists of IP address and mask value.
*
* @datastruct ulAddr Indicates IP address
* @datastruct ulMask Indicates mask value
*/


/* 存放规则中的IP地址和掩码 */
typedef struct tagACL_Range32 
{
    ULONG ulAddr;    
    ULONG ulMask;
} ACL_RANGE32_S;


/**
* @defgroup tagACL_Range16 ACL_RANGE16_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_Range16
* {
*     USHORT usBegin;
*     USHORT usEnd;
* } ACL_RANGE16_S;
* @endcode 
* 
* @par Description
* This structure consists of port number range.
*
* @datastruct usBegin Indicates port number start
* @datastruct usEnd Indicates port number end
*/


/* 存放规则中的端口号范围 */
typedef struct tagACL_Range16
{
    USHORT usBegin;    
    USHORT usEnd;
} ACL_RANGE16_S;


/**
* @defgroup tagACL_Range8 ACL_RANGE8_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_Range8
* {
*     UCHAR ucBegin;
*     UCHAR ucEnd;
*     UCHAR ucPadding[2];
* } ACL_RANGE8_S;
* @endcode 
* 
* @par Description
* This structure consists of protocol number range.
* 
* @datastruct ucBegin Indicates protocol number range begin
* @datastruct ucEnd Indicates protocol number range end
* @datastruct ucPadding[2] Indicates padding
*/


/* 存放规则中的协议号范围 */
typedef struct tagACL_Range8
{
    UCHAR ucBegin;
    UCHAR ucEnd;
    UCHAR ucPadding[2];/* 四字节对齐 */
} ACL_RANGE8_S;

/**
* @defgroup tagAclBasicRuleInfo ACL_BASIC_RULEINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclBasicRuleInfo
* {
*     ULONG   ulActionOp;
*     ULONG   ulAction;
*     ULONG   ulLogOp;
*     ULONG   ulLog;
*     ULONG   ulFragOp;
*     ULONG   ulFrag;
*     ULONG   ulSrcIPOp;
*     ACL_RANGE32_S   stSIP;
*     ULONG   ulVrfOp;
*     ULONG   ulVrfIndex;
*     ULONG ulTimerOp;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* } ACL_BASIC_RULEINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL basic rule information.
* 
* @datastruct ulActionOp Indicates whether rule action needs to be set
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulLogOp Indicates whether log flag need to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulFragOp Indicates whether fragmentation option needs to be set
* @datastruct ulFrag Indicates whether the rule is for fragmented packet
* @datastruct ulSrcIPOp Indicates whether source IP needs to be set
* @datastruct stSIP Indicates source IP information
* @datastruct ulVrfOp Indicates whether VRF index needs to be set
* @datastruct ulVrfIndex Indicates VRF index value
* @datastruct ulTimerOp Indicates whether timer needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/

/* 基本ACL规则信息，添加删除时做参数的数据结构 */
typedef struct tagAclBasicRuleInfo
{
    ULONG   ulActionOp;     /* 标记对参数action的操作类型：
                             * ACL_CFG_NOOPER -不配置;
                             * ACL_CFG_SET -配置;
                             * ACL_CFG_DEFAULT -恢复默认值;
                             */                             
    ULONG   ulAction;       /*待配置的新的action值;action无默认值*/

    ULONG   ulLogOp;        /*标记对参数log的操作类型*/
    ULONG   ulLog;          /*待配置的新的log值*/
    
    ULONG   ulFragOp;       /*标记对参数frag的操作类型*/
    ULONG   ulFrag;         /*待配置的新的frag值*/
    
    ULONG   ulSrcIPOp;      /*标记对源ip地址的操作类型*/
    ACL_RANGE32_S   stSIP;  /*待配置的新的源IP地址和掩码*/
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG   ulVrfOp;        /* 标记对VRF的操作类型 */
    ULONG   ulVrfIndex;     /* 待配置的VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    /* Begin: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp; 
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/
} ACL_BASIC_RULEINFO_S;

/**
* @defgroup tagAclAdvRuleInfo ACL_ADV_RULEINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclAdvRuleInfo
* {
*    ULONG   ulActionOp;
*    ULONG   ulAction;
*    ULONG   ulLogOp;
*    ULONG   ulLog;
*    ULONG   ulFragOp;
*    ULONG   ulFrag;
*    ULONG   ulSrcIPOp;
*    ACL_RANGE32_S   stSIP;
*    ULONG   ulDstIPOp;
*    ACL_RANGE32_S   stDIP;
*    ULONG   ulSrcPortOp;
*    ULONG   ulSPNum;
*    ULONG   ulSPOpType;
*    ACL_RANGE16_S   stSP[2];
*    ULONG   ulDstPortOp;
*    ULONG   ulDPNum;
*    ULONG   ulDPOpType;
*    ACL_RANGE16_S   stDP[2];
*    ULONG   ulPIDOp;
*    ACL_RANGE8_S    stPID;
*    ULONG   ulPreOp;
*    ULONG   ulPre;
*    ULONG   ulTosOp;
*    ULONG   ulTos;
*    ULONG   ulDscpOp;
*    ULONG   ulDscp;
*    ULONG   ulVrfOp;
*    ULONG   ulVrfIndex;
*    ULONG ulTimerOp;
*    CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*    UCHAR ucPadding[3];
* } ACL_ADV_RULEINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of the advanced rule information.
* 
* @datastruct ulActionOp Indicates whether rule action needs to be set
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulLogOp Indicates whether log flag need to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulFragOp Indicates whether fragmentation option needs to be set
* @datastruct ulFrag Indicates whether the rule is for fragmented packet
* @datastruct ulSrcIPOp Indicates whether source IP needs to be set
* @datastruct stSIP Indicates source IP information
* @datastruct ulDstIPOp Indicates whether destination IP needs to be set
* @datastruct stDIP Indicates destination IP information
* @datastruct ulSrcPortOp Indicates whether source port needs to be set
* @datastruct ulSPNum Indicates how many source port is set
* @datastruct ulSPOpType Indicates source port match type 
* @datastruct stSP[2] Indicates source port information
* @datastruct ulDstPortOp Indicates whether destination port needs to be set
* @datastruct ulDPNum Indicates how many destination port is set
* @datastruct ulDPOpType Indicates destination port match type
* @datastruct stDP[2] Indicates destination port information
* @datastruct ulPIDOp Indicates whether protocol ID needs to be set
* @datastruct stPID Indicates protocol ID
* @datastruct ulPreOp Indicates whether precedence value needs to be set
* @datastruct ulPre Indicates precedence value
* @datastruct ulTosOp Indicates whether TOS value needs to be set
* @datastruct ulTos Indicates TOS value
* @datastruct ulDscpOp Indicates whether DSCP value needs to set
* @datastruct ulDscp Indicates DSCP value
* @datastruct ulVrfOp Indicates whether VRF index needs to set 
* @datastruct ulVrfIndex Indicates VRF index value
* @datastruct ulTimerOp Indicates whether timer range needs to set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/

/* 扩展ACL规则信息，添加删除时做参数的数据结构 */
typedef struct tagAclAdvRuleInfo
{
    ULONG   ulActionOp;     /* 标记对参数action的操作类型：
                             * ACL_CFG_NOOPER -不配置;
                             * ACL_CFG_SET -配置;
                             * ACL_CFG_DEFAULT -恢复默认值;
                             */                             
    ULONG   ulAction;       /*待配置的新的action值*/

    ULONG   ulLogOp;        /*标记对bLog的操作类型*/
    ULONG   ulLog;          /*待配置的新的log值*/
    
    ULONG   ulFragOp;       /*标记对bFrag的操作类型*/
    ULONG   ulFrag;         /*待配置的新的frag值*/
    
    ULONG   ulSrcIPOp;      /*标记对源IP地址的操作类型*/
    ACL_RANGE32_S   stSIP;  /*待配置的新的源IP地址和掩码;源地址的默认值是掩码为0xffffffff的通配值*/

    ULONG   ulDstIPOp;      /*标记对源IP地址的操作类型*/
    ACL_RANGE32_S   stDIP;  /*待配置的新的目的IP地址和掩码;目的地址的默认值是掩码为0xffffffff的通配值*/

    /*Begin C02NEWR-ACL liangjicheng 2008-10-22
        source port is used for ICMP type- dest port is used for ICMP code  */
    ULONG   ulSrcPortOp;    /*标记对源端口的操作类型*/
    ULONG   ulSPNum;        /*源端口范围的段数: 为1时仅stSP[0]有效,为2时stSP[0],[1]均有效*/
    ULONG   ulSPOpType;     /*B015 liangjicheng 2008-12-11*/
    ACL_RANGE16_S   stSP[2];/*待配置的源端口范围;源端口的默认值是SPNum = 1,端口范围为0-65535*/

    ULONG   ulDstPortOp;    /*标记对目的端口的操作类型*/
    ULONG   ulDPNum;        /*目的端口范围的段数: 为1时仅stDP[0]有效,为2时stDP[0],[1]均有效*/
    ULONG   ulDPOpType;     /*B015 liangjicheng 2008-12-11*/
    ACL_RANGE16_S   stDP[2];/*待配置的目的端口范围;目的端口的默认值是DPNum = 1,端口范围为0-65535*/
    /*End C02NEWR-ACL liangjicheng 2008-10-22*/
    ULONG   ulPIDOp;        /*标记对协议号的操作类型*/
    ACL_RANGE8_S    stPID;  /*待配置的新的协议号值;协议号取值范围的默认值是0－255*/

    ULONG   ulPreOp;        /*标记对优先级的操作类型*/
    ULONG   ulPre;          /*待配置的新的优先级值;优先级的默认值是0xff，不对该数据项进行报文匹配*/

    ULONG   ulTosOp;        /*标记对tos的操作类型*/
    ULONG   ulTos;          /*待配置的新的tos值;tos的默认值是0xff，不对该数据项进行报文匹配*/

    ULONG   ulDscpOp;       /*标记对Dscp的操作类型*/
    ULONG   ulDscp;         /*待配置的新的dscp值;dscp的默认值是0xff，不对该数据项进行报文匹配*/

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-21 */
    ULONG   ulVrfOp;        /* 标记对VRF的操作类型 */
    ULONG   ulVrfIndex;     /* 待配置的VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-21 */
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/
} ACL_ADV_RULEINFO_S;


/**
* @defgroup tagAclIfBasedRuleInfo ACL_IFBASED_RULEINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclIfBasedRuleInfo
* {
*     ULONG   ulActionOp;
*     ULONG   ulAction;
*     ULONG   ulLogOp;
*     ULONG   ulLog;
*     ULONG   ulIfOp;
*     ULONG   ulIfIndex;
*     ULONG ulTimerOp;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* } ACL_IFBASED_RULEINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL interface based rule information.
* 
* @datastruct ulActionOp Indicates whether rule action needs to be set
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulLogOp Indicates whether log flag need to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulIfOp Indicates whether interface index needs to be set
* @datastruct ulIfIndex Indicates interface index
* @datastruct ulTimerOp Indicates whether timer range needs to set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/

/* 基于接口的ACL规则信息，添加删除时做参数的数据结构 */
typedef struct tagAclIfBasedRuleInfo
{
    ULONG   ulActionOp;     /* 标记对参数action的操作类型：
                             * ACL_CFG_NOOPER -不配置;
                             * ACL_CFG_SET -配置;
                             * ACL_CFG_DEFAULT -恢复默认值;
                             */                             
    ULONG   ulAction;       /*待配置的新的action值;action无默认值*/

    ULONG   ulLogOp;        /*标记对bLog的操作类型*/
    ULONG   ulLog;          /*待配置的新的log值*/
    
    ULONG   ulIfOp;         /*标记对ulIfIndex的操作类型*/
    ULONG   ulIfIndex;      /*待配置的新的接口索引;接口索引无默认值*/
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/
} ACL_IFBASED_RULEINFO_S;


/**
* @defgroup tagAclVlanRangeInfo ACL_VLAN_RANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclVlanRangeInfo
* {
*    USHORT usVlanIdStart;
*    USHORT usVlanIdEnd;
* }ACL_VLAN_RANGE_S;
* @endcode 
* 
* @par Description
* This structure consists of VLAN ID range to be configured in ACL_EXTMAC_RULEINFO_S 
* structure. To configure a VLAN ID, the start and end value has to be same.
* 
* @datastruct usVlanIdStart Indicates starting of VLAN ID to be configured.
* @datastruct usVlanIdEnd Indicates ending of VLAN ID to be configured.
*/
typedef struct tagAclVlanRangeInfo
{
    USHORT usVlanIdStart;
    USHORT usVlanIdEnd;
    USHORT usVlanPriorityFlag; /*Flag to decide VLAN Priority enable or not*/    
    USHORT usVlanPriorityVal;  /*Contains VLAN priority value.*/
}ACL_VLAN_RANGE_S;


/**
* @defgroup tagAclExtMacRuleInfo ACL_EXTMAC_RULEINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclExtMacRuleInfo
* {
*        ULONG   ulActionOp;
*        ULONG   ulAction;
*        ULONG   ulLogOp;
*        ULONG   ulLog;
*        ULONG   ulSrcMacOp;
*        UCHAR   ucSrcMac[6];
*        UCHAR   ucSrcMask[6];
*        ULONG   ulDstMacOp;
*        UCHAR   ucDstMac[6];
*        UCHAR   ucDstMask[6];
*        ULONG   ulFrameTypeOp;
*        ULONG   ulFrameType;
*        ACL_RANGEBYMASK32_S stTypeLsap;
*        ULONG ulTimerOp;
*        CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*        UCHAR ucPadding[3];
*        ULONG ulVLANIDOp;
*        ACL_VLAN_RANGE_S stVlanRange;
* } ACL_EXTMAC_RULEINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL external MAC based rule information.
* 
* @datastruct ulActionOp Indicates whether rule action needs to be set
* @datastruct ulAction Indicates ACL rule action (permit/deny)
* @datastruct ulLogOp Indicates whether log flag need to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulSrcMacOp Indicates whether source MAC needs to be set
* @datastruct ucSrcMac[6] Indicates sources MAC address
* @datastruct ucSrcMask[6] Indicates source mask
* @datastruct ulDstMacOp Indicates whether destination MAC needs to be set
* @datastruct ucDstMac[6] Indicates destination MAC address
* @datastruct ucDstMask[6] Indicates destination MAC mask
* @datastruct ulFrameTypeOp Indicates whether frame type needs to be set
* @datastruct ulFrameType Indicates frame type value
* @datastruct stTypeLsap Indicates MAC lsap value
* @datastruct ulTimerOp Indicates whether time range needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
* @datastruct ulVLANIDOp Indicates whether to consider VLAN ID configuration or not.
*                        If the option 3 is given, then usVlanIdStart and usVlanIdEnd  
*                        is set to 0x1FFF. This function is specially implemented 
*                        for specific customer requirement for no VLAN tagging.
* @datastruct stVlanRange VLAN ID to be configured. If user wants to configure the single VLAN ID,
* configure both elements of stVlanRange to same value.
* VLAN ID range is (1-4095).
*/


/* 基于MAC的ACL规则信息，添加删除时做参数的数据结构 */
typedef struct tagAclExtMacRuleInfo
{
    ULONG   ulActionOp;     /* 标记对参数action的操作类型：
                             * ACL_CFG_NOOPER -不配置;
                             * ACL_CFG_SET -配置;
                             * ACL_CFG_DEFAULT -恢复默认值;
                             */                             
    ULONG   ulAction;       /*待配置的新的action值;action无默认值*/

    ULONG   ulLogOp;        /*标记对bLog的操作类型*/
    ULONG   ulLog;          /*待配置的新的log值*/
    
    ULONG   ulSrcMacOp;     /*标记对bLog的操作类型*/
    UCHAR   ucSrcMac[6];    /*待配置的新的Mac地址*/
    UCHAR   ucSrcMask[6];   /*待配置的新的掩码值;源Mac地址的默认值是掩码为0，通配所有地址*/
    
    ULONG   ulDstMacOp;     /*标记对bLog的操作类型*/
    UCHAR   ucDstMac[6];    /*待配置的新的Mac地址*/
    UCHAR   ucDstMask[6];   /*待配置的新的掩码值;目的Mac地址的默认值是掩码为0，通配所有地址*/

    ULONG   ulFrameTypeOp;  /*标记对FrameType的操作类型*/
    ULONG   ulFrameType;    /*待配置的新的帧类型;帧类型的默认值为EXTENDEDMACACL_RULEID_NUNE*/
    ACL_RANGEBYMASK32_S stTypeLsap; /*待配置的新的Type/Lsap值;Type/Lsap值没有默认值*/
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/

    /*Added by eswar-r72335 Start
      Added for configuring VLAN ID*/
    ULONG ulVLANIDOp; /*Whether to consider VLAN ID configuration or not*/
    ACL_VLAN_RANGE_S stVlanRange; /*VLAN ID to be configured*/
    /*Added by eswar-r72335 End*/    
} ACL_EXTMAC_RULEINFO_S;



/**
* @defgroup tagACL_BasicRule ACL_BASIC_RULE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_BasicRule
* {
*        ULONG ulOperType;
*        ULONG ulAclAction;    
*        ULONG ulGroupNumber;
*        ULONG ulRuleId;
*        ULONG ulSorceIp;
*        ULONG ulMask;
*        ULONG ulSorceIpOp;
*        ULONG ulVrfOp;
*        CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH+1];
*        ULONG ulTimerOp;
*        CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*        UCHAR ucPadding[3];
* }ACL_BASIC_RULE_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL basic rule information.
* 
* @datastruct ulOperType Indicates ACL operation type
* @datastruct ulAclAction Indicates ACL rule action (permit/deny)
* @datastruct ulGroupNumber Indicates group number
* @datastruct ulRuleId Indicates rule number
* @datastruct ulSorceIp Indicates source IP address
* @datastruct ulMask Indicates mask value
* @datastruct ulSorceIpOp Indicates whether source IP address needs to be set
* @datastruct ulVrfOp Indicates whether VRF index needs to be set
* @datastruct szVrfName[ACL_MAX_VRFNAME_LENGTH+1] Indicates VRF name
* @datastruct ulTimerOp Indicates whether time range needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/



/* Bhaskar 71224: Data-structure declaration moved from acl_sh_api.h file on 2009-10-17 */
/* Basic ACL Rule structure */
typedef struct tagACL_BasicRule
{
    ULONG ulOperType;
    ULONG ulAclAction;    
    ULONG ulGroupNumber;
    ULONG ulRuleId;
    ULONG ulSorceIp;
    ULONG ulMask;

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulSorceIpOp;
    ULONG ulVrfOp;
    CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];

    /* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;   
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/
}ACL_BASIC_RULE_S;

/**
* @defgroup tagACL_BasicRuleEx ACL_BASIC_RULEEX_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_BasicRuleEx
* {
*     ULONG ulOperType;
*     ULONG ulAclAction;
*     ULONG ulGroupNumber;
*     ULONG ulRuleId;
*     ULONG ulSorceIp;
*     ULONG ulMask;
*     ULONG ulSorceIpOp;
*     ULONG ulVrfOp;
*     CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];
*     ULONG ulVrfIndex;
*     ULONG ulTimerOp;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* }ACL_BASIC_RULEEX_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL basic rule information.
* 
* @datastruct ulOperType Indicates ACL operation type
* @datastruct ulAclAction Indicates ACL rule action (permit/deny)
* @datastruct ulGroupNumber Indicates Group number
* @datastruct ulRuleId Indicates Rule number
* @datastruct ulSorceIp Indicates source IP address
* @datastruct ulMask Indicates mask value
* @datastruct ulSorceIpOp Indicates whether source IP address needs to be set
* @datastruct ulVrfOp Indicates whether VRF index needs to be set
* @datastruct szVrfName[ACL_MAX_VRFNAME_LENGTH+1] Indicates VRF name
* @datastruct ulVrfIndex Indicates VRF index 
* @datastruct ulTimerOp Indicates whether time range needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/

typedef struct tagACL_BasicRuleEx
{
    ULONG ulOperType;
    ULONG ulAclAction;    
    ULONG ulGroupNumber;
    ULONG ulRuleId;
    ULONG ulSorceIp;
    ULONG ulMask;

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulSorceIpOp;
    ULONG ulVrfOp;
    CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];
    ULONG ulVrfIndex;

    /* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/
}ACL_BASIC_RULEEX_S;


/**
* @defgroup tagACL_AdvRule ACL_ADV_RULE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_AdvRule
* {
*     ULONG ulOperType;
*     ULONG ulAclAction;
*     ULONG ulGroupNumber;
*     ULONG ulRuleId;
*     ULONG ulSorceIpOp;
*     ULONG ulSorceIp;
*     ULONG ulSorcMask;
*     ULONG ulDestIpOp;
*     ULONG ulDestIp;
*     ULONG ulDestMask; 
*     ULONG ulTosOp;
*     ULONG ulTos;
*     ULONG ulDscpOp;
*     ULONG ulDscp;
*     ULONG ulPreOp;
*     ULONG ulPre;
*     ULONG ulFragOp;
*     ULONG ulFrag;
*     ULONG ulLogOp;
*     ULONG ulLog;
*     ULONG  ulSPOp;
*     ULONG  ulSPOpType;
*     USHORT usSPBegin;
*     USHORT usSPEnd;
*     ULONG  ulDPOp;
*     ULONG  ulDPOpType;
*     USHORT usDPBegin;
*     USHORT usDPEnd;
*     ULONG  ulProtoOp;
*     UCHAR ucProtoBegin;
*     UCHAR ucProtoEnd;
*     UCHAR ucPadding[2];
*     ULONG ulVrfOp;
*     CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH+1];
*     ULONG ulTimerOp;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding1[3];
* }ACL_ADV_RULE_S;
* @endcode 
* 
* @par Description
* This structure consists of advanced rule information.
*
* @datastruct ulOperType Indicates ACL operation type
* @datastruct ulAclAction Indicates ACL rule action (permit/deny)
* @datastruct ulGroupNumber Indicates Group number
* @datastruct ulRuleId Indicates Rule number
* @datastruct ulSorceIpOp Indicates whether source IP address needs to be set
* @datastruct ulSorceIp Indicates source IP address
* @datastruct ulSorcMask Indicates source mask value
* @datastruct ulDestIpOp Indicates whether destination IP address needs to be set
* @datastruct ulDestIp Indicates destination IP address
* @datastruct ulDestMask Indicates mask value
* @datastruct ulTosOp Indicates whether TOS value needs to be set
* @datastruct ulTos Indicates TOS value
* @datastruct ulDscpOp Indicates whether DSCP value needs to be set
* @datastruct ulDscp Indicates DSCP value
* @datastruct ulPreOp Indicates whether precedence value needs to be set
* @datastruct ulPre Indicates precedence value
* @datastruct ulFragOp Indicates whether fragmentation option needs to be set
* @datastruct ulFrag Indicates fragmentation option
* @datastruct ulLogOp Indicates whether log flag needs to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulSPOp Indicates whether source port needs to be set
* @datastruct ulSPOpType Indicates source port match type
* @datastruct usSPBegin Indicates source port range begin
* @datastruct usSPEnd Indicates source port range end
* @datastruct ulDPOp Indicates whether destination port needs to be set
* @datastruct ulDPOpType Indicates destination port match type
* @datastruct usDPBegin Indicates destination port range begin
* @datastruct usDPEnd Indicates destination port range end
* @datastruct ulProtoOp Indicates whether protocol ID needs to be set
* @datastruct ucProtoBegin Indicates protocol ID start
* @datastruct ucProtoEnd Indicates protocol ID end
* @datastruct ucPadding[2] Indicates padding 
* @datastruct ulVrfOp Indicates whether VRF index needs to be set
* @datastruct szVrfName[ACL_MAX_VRFNAME_LENGTH+1] Indicates VRF name
* @datastruct ulTimerOp Indicates whether time range needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/

/* Bhaskar 71224: Data-structure declaration moved from acl_sh_api.h file on 2009-10-17 */
/* advance acl rule structure */
typedef struct tagACL_AdvRule
{
    ULONG ulOperType;
    ULONG ulAclAction;
    ULONG ulGroupNumber;
    ULONG ulRuleId;
    ULONG ulSorceIpOp;  /*01 B015 liangjicheng*/
    ULONG ulSorceIp;
    ULONG ulSorcMask;
    ULONG ulDestIpOp;   /*02 B015 liangjicheng*/
    ULONG ulDestIp;
    ULONG ulDestMask; 
    ULONG ulTosOp;      /*03 B015 liangjicheng*/
    ULONG ulTos;
    ULONG ulDscpOp;     /*04 B015 liangjicheng*/
    ULONG ulDscp;
    ULONG ulPreOp;      /*05 B015 liangjicheng*/
    ULONG ulPre;
    ULONG ulFragOp;     /*06 B015 liangjicheng*/
    ULONG ulFrag;
    ULONG ulLogOp;      /*07 B015 liangjicheng*/
    ULONG ulLog;

    /*Begin C02NEWR-ACL liangjicheng 2008-12-11
        source port is used for ICMP type- dest port is used for ICMP code 
        Add operation Code*/ 
    ULONG  ulSPOp;      /*08 B015 liangjicheng*/
    ULONG  ulSPOpType;/*Source Port Filter Type*/    
    USHORT usSPBegin; 
    USHORT usSPEnd; 
    ULONG  ulDPOp;      /*09 B015 liangjicheng*/
    ULONG  ulDPOpType;/*Dest Port Filter Type*/
    USHORT usDPBegin;
    USHORT usDPEnd;

    /*End C02NEWR-ACL liangjicheng 2008-10-22*/
    ULONG  ulProtoOp;   /*10 B015 liangjicheng*/
    UCHAR ucProtoBegin;
    UCHAR ucProtoEnd;
    UCHAR ucPadding[2];
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulVrfOp;
    CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];

    /* End: VISP1.7C03 VRF wangchengyang,2009-02-01 */
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding1[3];                     /*Padding for timer*/
}ACL_ADV_RULE_S;

/**
* @defgroup tagACL_AdvRuleEx ACL_ADV_RULEEX_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_AdvRuleEx
* {
*    ULONG ulOperType;
*    ULONG ulAclAction;
*    ULONG ulGroupNumber;
*    ULONG ulRuleId;
*    ULONG ulSorceIpOp;
*    ULONG ulSorceIp;
*    ULONG ulSorcMask;
*    ULONG ulDestIpOp;
*    ULONG ulDestIp;
*    ULONG ulDestMask; 
*    ULONG ulTosOp;
*    ULONG ulTos;
*    ULONG ulDscpOp;
*    ULONG ulDscp;
*    ULONG ulPreOp;
*    ULONG ulPre;
*    ULONG ulFragOp;
*    ULONG ulFrag;
*    ULONG ulLogOp;
*    ULONG ulLog;
*    ULONG  ulSPOp;
*    ULONG  ulSPOpType;
*    USHORT usSPBegin;
*    USHORT usSPEnd;
*    ULONG  ulDPOp;
*    ULONG  ulDPOpType;
*    USHORT usDPBegin;
*    USHORT usDPEnd;
*    ULONG  ulProtoOp;
*    UCHAR ucProtoBegin;
*    UCHAR ucProtoEnd;
*    UCHAR   ucPadding[2];
*    ULONG ulVrfOp;
*    CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];
*    ULONG ulVrfIndex;
*    ULONG ulTimerOp;
*    CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*    UCHAR ucPadding1[3];
* }ACL_ADV_RULEEX_S;
* @endcode 
* 
* @par Description
* This structure consists of acl advanced rule ex information structure.
* 
* @datastruct ulOperType Indicates ACL operation type
* @datastruct ulAclAction Indicates ACL rule action (permit/deny)
* @datastruct ulGroupNumber Indicates Group number
* @datastruct ulRuleId Indicates Rule number
* @datastruct ulSorceIpOp Indicates whether source IP address needs to be set
* @datastruct ulSorceIp Indicates source IP address
* @datastruct ulSorcMask Indicates source mask value
* @datastruct ulDestIpOp Indicates whether destination IP address needs to be set
* @datastruct ulDestIp Indicates destination IP address
* @datastruct ulDestMask Indicates mask value
* @datastruct ulTosOp Indicates whether TOS value needs to be set
* @datastruct ulTos Indicates TOS value
* @datastruct ulDscpOp Indicates whether DSCP value needs to be set
* @datastruct ulDscp Indicates DSCP value
* @datastruct ulPreOp Indicates whether precedence value needs to be set
* @datastruct ulPre Indicates precedence value
* @datastruct ulFragOp Indicates whether fragmentation option needs to be set
* @datastruct ulFrag Indicates fragmentation option
* @datastruct ulLogOp Indicates whether log flag needs to be set
* @datastruct ulLog Indicates log flag value
* @datastruct ulSPOp Indicates whether source port needs to be set
* @datastruct ulSPOpType Indicates source port match type
* @datastruct usSPBegin Indicates source port range begin
* @datastruct usSPEnd Indicates source port range end
* @datastruct ulDPOp Indicates whether destination port needs to be set
* @datastruct ulDPOpType Indicates destination port match type
* @datastruct usDPBegin Indicates destination port range begin
* @datastruct usDPEnd Indicates destination port range end
* @datastruct ulProtoOp Indicates whether protocol ID needs to be set
* @datastruct ucProtoBegin Indicates protocol ID start
* @datastruct ucProtoEnd Indicates protocol ID end
* @datastruct ucPadding[2] Indicates padding
* @datastruct ulVrfOp Indicates whether VRF index needs to be set
* @datastruct szVrfName[ACL_MAX_VRFNAME_LENGTH+1] Indicates VRF name
* @datastruct ulVrfIndex Indicates VRF index 
* @datastruct ulTimerOp Indicates whether time range needs to be set
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Indicates time range value
* @datastruct ucPadding[3] Indicates padding
*/


typedef struct tagACL_AdvRuleEx
{
    ULONG ulOperType;
    ULONG ulAclAction;
    ULONG ulGroupNumber;
    ULONG ulRuleId;
    ULONG ulSorceIpOp;  /*01 B015 liangjicheng*/
    ULONG ulSorceIp;
    ULONG ulSorcMask;
    ULONG ulDestIpOp;   /*02 B015 liangjicheng*/
    ULONG ulDestIp;
    ULONG ulDestMask; 
    ULONG ulTosOp;      /*03 B015 liangjicheng*/
    ULONG ulTos;
    ULONG ulDscpOp;     /*04 B015 liangjicheng*/
    ULONG ulDscp;
    ULONG ulPreOp;      /*05 B015 liangjicheng*/
    ULONG ulPre;
    ULONG ulFragOp;     /*06 B015 liangjicheng*/
    ULONG ulFrag;
    ULONG ulLogOp;      /*07 B015 liangjicheng*/
    ULONG ulLog;

    /*Begin C02NEWR-ACL liangjicheng 2008-12-11
        source port is used for ICMP type- dest port is used for ICMP code 
        Add operation Code*/ 
    ULONG  ulSPOp;      /*08 B015 liangjicheng*/
    ULONG  ulSPOpType;/*Source Port Filter Type*/    
    USHORT usSPBegin; 
    USHORT usSPEnd; 
    ULONG  ulDPOp;      /*09 B015 liangjicheng*/
    ULONG  ulDPOpType;/*Dest Port Filter Type*/
    USHORT usDPBegin;
    USHORT usDPEnd;

    /*End C02NEWR-ACL liangjicheng 2008-10-22*/
    ULONG  ulProtoOp;   /*10 B015 liangjicheng*/
    UCHAR ucProtoBegin;
    UCHAR ucProtoEnd;
    UCHAR   ucPadding[2];
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulVrfOp;
    CHAR  szVrfName[ACL_MAX_VRFNAME_LENGTH + 1];
    ULONG ulVrfIndex;

    /* End: VISP1.7C03 VRF wangchengyang,2009-02-01 */
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    ULONG ulTimerOp;
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding1[3];                     /*Padding for timer*/
}ACL_ADV_RULEEX_S;

/**
* @defgroup tagExtendedMacInfo EXTENDEDMACINFO_S/PEXTENDEDMACINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagExtendedMacInfo
* {
*     union
*     {
*         UCHAR ucMac[12];       
*         USHORT usMac[6];
*         ULONG ulMac[3];
*     } unMac; 
*     USHORT usVlanId;
*     USHORT usPadding;
*     USHORT usType;
*     UCHAR ucNeedCheckType;
*     UCHAR ucIsDlswPort;
*     ULONG ulIfIndex;
*     ULONG ulTotalDataLen;
*     ULONG ulIgnoreByte;
* } EXTENDEDMACINFO_S, *PEXTENDEDMACINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of extended MAC based packet information.
* 
* @datastruct ucMac[12] Indicates mac address in unsigned char.
* @datastruct usMac[6] Indicates mac address in unsigned.
* @datastruct ulMac[3] Indicates mac address in ulong
* @datastruct unMac Indicates union for mac address
* @datastruct usVlanId VLANID of the received packet
* @datastruct usPadding Added for Padding
* @datastruct usType Indicates mac address type
* @datastruct ucNeedCheckType Indicates whether mac rule type or lsap is specified 
* @datastruct ucIsDlswPort This field is not in use
* @datastruct ulIfIndex Indicates interface index
* @datastruct ulTotalDataLen Indicates data length
* @datastruct ulIgnoreByte Indicates the fields that can be ignored 
*/
/* 从Ether报文中提取的信息 */
typedef struct tagExtendedMacInfo 
{
    union
    {
        UCHAR ucMac[12];       
        USHORT usMac[6];
        ULONG ulMac[3];
    } unMac; 

    /*Added by eswar-r72335 Start
      Added for VLAN ID*/
    USHORT usVlanId;  
    USHORT usVlanPriorityVal; /*s72256: This contains Vlan-Priority */
    /*Added by eswar-r72335 End*/

    USHORT usType;
    UCHAR ucNeedCheckType;
    UCHAR ucIsDlswPort;
    ULONG ulIfIndex;
    ULONG ulTotalDataLen;
    ULONG ulIgnoreByte;
    
} EXTENDEDMACINFO_S, *PEXTENDEDMACINFO_S;

/* 存放基于MAC的规则的源和目的MAC地址 */
/**
* @defgroup tagACL_Range96 ACL_RANGE96_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_Range96 
* {
*     union
*     {
*         UCHAR ucMac[12];
*         USHORT usMac[6];
*         ULONG ulMac[3];
*     } unMac;                     
*     union
*     {
*         UCHAR ucMask[12];
*         USHORT usMask[6];
*         ULONG ulMask[3];
*     } unMacMask;            
* } ACL_RANGE96_S;
* @endcode 
* 
* @par Description
* This structure consists of extended MAC based packet information.
* 
* @datastruct ucMac[12] Indicates mac address in unsigned char.
* @datastruct usMac[6] Indicates mac address in unsigned short.
* @datastruct ulMac[3] Indicates mac address in ulong
* @datastruct unMac Indicates union for mac address
* @datastruct ucMask[12] Indicates mask in unsigned char.
* @datastruct usMask[6] Indicates mask in unsigned short.
* @datastruct ulMask[3] Indicates mask in ulong.
* @datastruct unMacMask Indicates union for mask of mac address.
*/
typedef struct tagACL_Range96 
{
    union
    {
        UCHAR ucMac[12];    /* 前6个字节是目的MAC地址，后6个字节是源MAC地址 */       
        USHORT usMac[6];
        ULONG ulMac[3];
    } unMac;                     
    union
    {
        UCHAR ucMask[12];   /* 前6个字节是目的MAC地址的掩码，后6个字节是源MAC地址的掩码 */       
        USHORT usMask[6];
        ULONG ulMask[3];
    } unMacMask;            
} ACL_RANGE96_S;


/* 基本ACL规则内容 */
/**
* @defgroup tagACL_StandardIPNode ACL_STANDARD_IPNODE_S/PACL_STANDARD_IPNODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_StandardIPNode 
* {
*     ULONG ulAction;
*     BOOL_T bFrag;
*     UCHAR ucPadding[2];
*     ACL_RANGE32_S stSIP;
*     ULONG ulVrfIndex;
* } ACL_STANDARD_IPNODE_S, *PACL_STANDARD_IPNODE_S;
* @endcode 
* 
* @par Description
* This structure consists of the basic ACL rules.
* 
* @datastruct ulAction Operation values: 0-ACL_DENY,1-ACL_PERMIT
* @datastruct bFrag Flag which decides to check fragmented packets:
* TRUE-only slice packet inspection (do not check the first packet),
* FALSE-check all the packets
* @datastruct ucPadding[2] Padding
* @datastruct stSIP Source IP address
* @datastruct ulVrfIndex VRF Index
*/
typedef struct tagACL_StandardIPNode 
{

    ULONG ulAction;             /* 操作值:0-ACL_DENY,1-ACL_PERMIT */
    BOOL_T bFrag;               /* 只检查分片报文标志:
                                   TRUE-只检查分片报文(不检查首片报文和不分片报文),
                                   FALSE-检查所有的报文*/
    UCHAR ucPadding[2];
    ACL_RANGE32_S stSIP;        /* 源IP地址 + 通配符 */
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;           /* Vrf index */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} ACL_STANDARD_IPNODE_S, *PACL_STANDARD_IPNODE_S;



/* 扩展ACL规则内容 */
/**
* @defgroup tagACL_ExtendedIPNode ACL_EXTENDED_IPNODE_S/PACL_EXTENDED_IPNODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_ExtendedIPNode 
* {
*     ULONG ulAction;
*     BOOL_T bFrag;
*     UCHAR ucSPNum;
*     UCHAR ucDPNum;
*     ACL_RANGE16_S stSP[2];
*     ACL_RANGE16_S stDP[2];
*     ACL_RANGE32_S stSIP;
*     ACL_RANGE32_S stDIP;
*     ACL_RANGE8_S  stPID;
*     UCHAR ucPre;
*     UCHAR ucTos;
*     UCHAR ucDscp;
*     UCHAR ucPadding;
*     ULONG ulVrfIndex;
* } ACL_EXTENDED_IPNODE_S, *PACL_EXTENDED_IPNODE_S;
* @endcode 
* 
* @par Description
* This structure consists of extended ACL rules.
* 
* @datastruct ulAction Operation values: 0-ACL_DENY,1-ACL_PERMIT
* @datastruct bFrag Flag which decides to check fragmented packets:
* TRUE-only slice packet inspection (do not check the first packet),
* FALSE-check all the packets
* @datastruct ucSPNum The value which decides number of source port structures to be considered
* the value 1 - then only stSP [0] into effect, 
* the value of non-1, stSP [0] and stSP [1] are effective
* @datastruct ucDPNum The value which decides number of destination port strucures to be considered
* the value 1 - then only stDP [0] into effect, 
* the value of non-1, stDP [0] and stDP [1] are effective
* @datastruct stSP[2] source port number or stSP [0] stICMPType
* @datastruct stDP[2] destination port value or stDP [0] ICMPCode
* @datastruct stSIP source IP address
* @datastruct stDIP destination IP address
* @datastruct stPID protocol number range
* @datastruct ucPre precedence option
* @datastruct ucTos TOS option
* @datastruct ucDscp DSCP option
* @datastruct ucPadding padding
* @datastruct ulVrfIndex VRF Index
*/
typedef struct tagACL_ExtendedIPNode 
{
    ULONG ulAction;             /* 操作值:0-ACL_DENY,1-ACL_PERMIT */
    BOOL_T bFrag;               /* 只检查分片报文标志:
                                   TRUE-只检查分片报文(不检查首片报文和不分片报文),
                                   FALSE-检查所有的报文*/
    UCHAR ucSPNum;              /* 该成员值为1，则仅有stSP[0]生效，值为非1，则stSP[0]和stSP[1]都生效 */
    UCHAR ucDPNum;              /* 该成员值为1，则仅有stDP[0]生效，值为非1，则stDP[0]和stDP[1]都生效 */
    /*Begin C02NEWR-ACL liangjicheng 2008-10-22*/
    ACL_RANGE16_S stSP[2];      /* 源端口数值or  stSP[0] stICMPType*/
    ACL_RANGE16_S stDP[2];      /* 目的端口数值or stDP[0] ICMPCode*/
      /*End   C02NEWR-ACL */ 
    ACL_RANGE32_S stSIP;        /* 源IP地址 + 通配符 */
    ACL_RANGE32_S stDIP;        /* 目的IP地址 + 通配符 */
    ACL_RANGE8_S  stPID;        /* 协议号范围 */
    UCHAR ucPre;                /* precedence选项 */
    UCHAR ucTos;                /* TOS选项 */
    UCHAR ucDscp;               /* Dscp选项 */
    UCHAR ucPadding;

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;           /* Vrf index */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} ACL_EXTENDED_IPNODE_S, *PACL_EXTENDED_IPNODE_S;

/* 基于接口的ACL规则内容 */
/**
* @defgroup tagACL_IFBasedIPNode ACL_IFBASED_IPNODE_S/PACL_IFBASED_IPNODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_IFBasedIPNode 
* {
*     ULONG ulAction;
*     ULONG ulIfIndex;
* } ACL_IFBASED_IPNODE_S, *PACL_IFBASED_IPNODE_S;
* @endcode 
* 
* @par Description
* This structure consists of interface based ACL rules.
* 
* @datastruct ulAction Operation values: 0-ACL_DENY,1-ACL_PERMIT
* @datastruct ulIfIndex Interface Index
*/
typedef struct tagACL_IFBasedIPNode 
{
    ULONG ulAction;             /* 操作值:0-ACL_DENY,1-ACL_PERMIT */
    ULONG ulIfIndex;            /* 接口索引0xffffffff为任意端口 */
} ACL_IFBASED_IPNODE_S, *PACL_IFBASED_IPNODE_S;



/* 基于MAC的ACL规则内容 */
/**
* @defgroup tagACL_ExtendedMacNode ACL_EXTENDED_MAC_NODE_S/PACL_EXTENDED_MAC_NODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_ExtendedMacNode 
* {
*     ULONG ulAction;
*     ACL_RANGE96_S stMac;
*     ULONG ulFrameType;
*     ACL_RANGEBYMASK32_S stType;
*     ACL_RANGEBYMASK32_S stLsap;
*     ACL_VLAN_RANGE_S stVlanRange;
* } ACL_EXTENDED_MAC_NODE_S, *PACL_EXTENDED_MAC_NODE_S;
* @endcode 
* 
* @par Description
* This structure consists of MAC based ACL rules.
* 
* @datastruct ulAction Operation values: 0-ACL_DENY,1-ACL_PERMIT
* @datastruct stMac source MAC address and mask
* 12 address bytes, the first six bytes are the destination address, next 6 bytes are the source address
* 12 mask bytes, the first 6 bytes are the destination address mask, next 6 bytes are the source address mask
* @datastruct ulFrameType frame type :1-type ,2-Lsap ,0-None
* @datastruct stType Type value and mask, used when ulFrameType is type
* @datastruct stLsap Lsap value and mask used when ulFrameType is lsap
* @datastruct stVlanRange Configured VLAN ID
*/

typedef struct tagACL_ExtendedMacNode 
{
    ULONG ulAction;             /* 操作值:0-ACL_DENY,1-ACL_PERMIT */
    ACL_RANGE96_S stMac;        /* 源、目的MAC地址和掩码,
                                   12个地址字节中,前6个字节是目的地址，后6个字节是源地址
                                   12个掩码字节中,前6个字节是目的地址掩码，后6个字节是源地址掩码*/
    ULONG ulFrameType;          /* 帧类型:1-type,2-Lsap,0-None */
    ACL_RANGEBYMASK32_S stType; /* Type值和掩码 */
    ACL_RANGEBYMASK32_S stLsap; /* Lsap值和掩码 */

    /*Added by eswar-r72335 Start
      Added for configuring VLAN ID*/
    ACL_VLAN_RANGE_S stVlanRange; /*Configured VLAN ID*/
    /*Added by eswar-r72335 End*/    
} ACL_EXTENDED_MAC_NODE_S, *PACL_EXTENDED_MAC_NODE_S;




/* acl rfc action structure */
typedef struct tagACL_RFC_ACTION
{
    /* modified by x36308 for SWFD10711 2005-6-21 */
    /*#if(TCPIP_IN_VRP == VRP_YES)*/
    /*ACL_ACTIONS_E   eAction;*/
    /*#else*/
    ULONG eAction;

    /*#endif*/

    /* end of SWFD10711 */
    /* BOOL_T       bEnable; */  /* BYDD04800 */
    BOOL_T          bLog;

    /* Padding Bytes */
    UCHAR           ucPadding1[2];

    ULONG           ulCount;
    ULONG           ulSubItem;

    /*
    ULONG           ulVpnIndex; */
    UCHAR           ucTos;
    UCHAR           ucPre;
    UCHAR           ucDSCP;  /* not used for RFC computing. Just for reserved. */

    /* Padding Bytes */
    UCHAR           ucPadding2;

    /*ULONG eGroupType; */

}ACL_RFC_ACTION;

/* ACL规则 */
/**
* @defgroup tagACL_RuleNode ACL_RULE_NODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_RuleNode
* {
*     VOID  *pContent;
*     ULONG  ulSubItem;
*     ULONG  ulCount;
*     struct tagACL_RuleNode * pstNode;
*     BOOL_T bLog;
*     BOOL_T bEnable;
*     ACL_RFC_ACTION *pAccAction;
*     CHAR szTimername[ACL_MAX_TR_NAME_LEN];
*     UCHAR ucPadding[3];
* }ACL_RULE_NODE_S;
* @endcode 
* 
* @par Description
* This structure consists of ACL rule nodes.
* 
* @datastruct pContent Rules for content, according to the rules on the type of ACL
* @datastruct ulSubItem Rules for index
* @datastruct ulCount Number of times the rule matches
* @datastruct pstNode Next rule
* @datastruct bLog Whether to set the log flag: TRUE-set log, FALSE- do not set the log
* @datastruct bEnable Enable/disable RFC
* @datastruct pAccAction Pointer to ACL_RFC_ACTION
* @datastruct szTimername[ACL_MAX_TR_NAME_LEN] Bind this rule with Timer
* @datastruct ucPadding[3] Padding for timer
*/

typedef struct tagACL_RuleNode
{

    VOID  *pContent;                        /* 规则内容，根据ACL规则的类型决定 */
    ULONG  ulSubItem;                       /* 规则索引 */

    ULONG  ulCount;                         /* 匹配该规则的次数 */
    struct tagACL_RuleNode * pstNode;       /* 下一条规则 */
    BOOL_T bLog;                            /* 是否做日志标志:TRUE-做日志,FALSE-不做日志 */
    BOOL_T bEnable;                         /* Added by Vinay Gudur*/
    ACL_RFC_ACTION *pAccAction;
    /* Begine: Mayur 2009-11-11 Bind rule with timer*/
    CHAR szTimername[ACL_MAX_TR_NAME_LEN];  /*Bind this rule with Timer*/
    UCHAR ucPadding[3];                     /*Padding for timer*/

}ACL_RULE_NODE_S;

/**
* @defgroup tagACL_AccessListGroup ACCESSLISTGROUP_S/PACCESSLISTGROUP_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_AccessListGroup
* {
*     ULONG ulVer;
*     ULONG ulMatchOrder;
*     ULONG ulNodeNum;
*     ULONG ulGroupIndex;
*     ULONG ulTypeID;
*     ULONG  ulAclRfcStatus;
*     ACL_RULE_NODE_S *pRuleNode;
*     CHAR *pACLDescription;
*     ULONG ulIndexStep;
*     ULONG ulNextNodeID;
*     ULONG ulRuleNodeSize;
*     UCHAR  ucIsFitAcc;
*     UCHAR  ucPadding[3];
* } ACCESSLISTGROUP_S, *PACCESSLISTGROUP_S;
* @endcode 
* 
* @par Description
* This structure consists of the details of an ACL group such as the version, the node number, 
* the group index, the rule node, the next node ID, the rule node size, and so on.
* 
* @datastruct ulVer Indicates version number.
* @datastruct ulMatchOrder Indicates match order.
* @datastruct ulNodeNum Indicates node number.
* @datastruct ulGroupIndex Indicates group index.
* @datastruct ulTypeID Indicates ACL type ID.
* @datastruct ulAclRfcStatus Indicates ACL status. The values can be: 
*	- ACL_STATUS_UNACC - 0
*	- ACL_STATUS_ACCUTD - 1
*	- ACL_STATUS_ACCOOD - 2
* @datastruct pRuleNode Indicates the rule node.
* @datastruct pACLDescription Indicates ACL description.
* @datastruct ulIndexStep Indicates the Index step.
* @datastruct ulNextNodeID Indicates the next node ID.
* @datastruct ulRuleNodeSize Indicates the size of the rule node.
* @datastruct ucIsFitAcc Indicates whether the rule is fit for ACL acceleration.
* This data member is used for internal purpose. User should provide a value 0 for this field.
* @datastruct ucPadding[3] Indicates padding.
*/
/* ACL规则组 */
typedef struct tagACL_AccessListGroup
{
    ULONG ulVer;                    /* 暂不使用，留待扩展 */
    ULONG ulMatchOrder;             /* 匹配顺序:0-配置顺序,1-自动顺序 */
    ULONG ulNodeNum;                /* 该规则组下已有的规则总数 */
    ULONG ulGroupIndex;             /* 规则组序号 */
    ULONG ulTypeID;                 /* 所属规则类型ID */

    /* added by Vinay Gudur*/
    ULONG  ulAclRfcStatus;                  /* 0-UnAcc UTD, 1-Acc UTD, 2-Acc OFD */	

    ACL_RULE_NODE_S *pRuleNode;     /* 下属规则链表表头 */
    CHAR *pACLDescription;          /* 该规则组的描述信息 */
    ULONG ulIndexStep;              /* 该规则组的步长 */
    ULONG ulNextNodeID;             /* 待分配的规则索引 */
    ULONG ulRuleNodeSize;           /* 规则内容的大小,指pRuleNode->pCoutent的内容大小 */

    UCHAR  ucIsFitAcc;     /*Added by Vinay Gudur */
    UCHAR  ucPadding[3];   /* Padding Bytes */
} ACCESSLISTGROUP_S, *PACCESSLISTGROUP_S;

/* ACL规则类型 */
/**
* @defgroup tagAclType ACL_TYPE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclType
* {
*     ULONG ulTypeID;
*     ULONG ulLowNo;
*     ULONG ulUpNo;
*     ULONG ulRuleNodeSize;
*     ULONG (*pFuncComp)(VOID *, VOID *); 
*     BOOL_T (*pFuncBefore)(VOID *, VOID *); 
*     ULONG (*pFuncRuleComp)(VOID *, VOID *); 
*     VOID* (*pFuncCreateNode)();
*     VOID (*pFuncReleaseNode)(VOID*); 
*     ACCESSLISTGROUP_S **ppstGroup;
* } ACL_TYPE_S;
* @endcode 
* 
* @par Description
* This structure consists of the details of an ACL Type.
* 
* @datastruct ulTypeID The rule type ID. The value can range from 1 to 16.
* @datastruct ulLowNo The lower limit of the ACL group number.
* @datastruct ulUpNo The upper limit of the ACL group number.
* @datastruct ulRuleNodeSize The size of the rule node.
* @datastruct pFuncComp Compares two nodes.
* @datastruct pFuncBefore Decides before which rule to place the next rule.
* @datastruct pFuncRuleComp Compares the rule node and packet. First parameter is 
* the rule content and the second is the packet information.
* @datastruct pFuncCreateNode Creates a rule node.
* @datastruct pFuncReleaseNode Releases the rule node.
* @datastruct ppstGroup Pointer to the location containing the ACL group details.
*/
typedef struct tagAclType
{
    ULONG ulTypeID;         /* 规则类型ID（1－16） */
    ULONG ulLowNo;          /* 规则组序号下限 */
    ULONG ulUpNo;           /* 规则组序号上限 */
    ULONG ulRuleNodeSize;   /* 规则内容的大小 */
    /* 比较两个节点是否相同 */
    ULONG (*pFuncComp)(VOID *, VOID *); 

    /* 判断规则是否合适插入某规则之前，前一个参数是待插入规则，后一个参数是被插入规则 */
    BOOL_T (*pFuncBefore)(VOID *, VOID *); 

    /* 比较一个规则节点是否和包匹配，前一个参数是规则内容，后一个参数是待匹配报文信息 */
    ULONG (*pFuncRuleComp)(VOID *, VOID *); 

    /* 创建一个规则节点 */
    VOID* (*pFuncCreateNode)(VOID);

    /* 释放一个规则节点 */
    VOID (*pFuncReleaseNode)(VOID*);    
    ACCESSLISTGROUP_S **ppstGroup;/* 规则组指针数组 */
} ACL_TYPE_S;


/* ACL规则数据结构入口 */
typedef struct tagACL_AccessList
{
    ULONG ulACLGroupSum;
    ACL_TYPE_S* pstACLType[ACL_MAX_TYPEID + 1];   
} ACCESSLIST_S, *PACCESSLIST_S;


/* 存放IP地址 */
/**
* @defgroup tagACL_INADDR ACL_INADDR_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_INADDR
* {
*     ULONG s_ulAddr;
* }ACL_INADDR_S;
* @endcode 
* 
* @par Description
* This structure stores IP addresses.
* 
* @datastruct s_ulAddr IP address
*/
typedef struct tagACL_INADDR
{
    ULONG s_ulAddr;
}ACL_INADDR_S;

/*Begin C02NEWR-ACL liangjicheng 2008-10-24*/
#ifndef IP_DF
#define IP_DF 0x4000            /* dont fragment flag */
#endif

#ifndef IP_MF
#define IP_MF 0x2000            /* more fragments flag */
#endif

#ifndef IP_OFFMASK
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
#endif

/*End C02NEWR-ACL liangjicheng 2008-10-24*/


/* IP报文首部定义 */
/**
* @defgroup tagACL_IP ACL_IP_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_IP
* {
* #if VRP_LITTLE_ENDIAN == VRP_YES
*     UCHAR   ip_chHLen:4;
*     UCHAR   ip_chVer: 4;
* #else
*     UCHAR  ip_chVer:  4;
*     UCHAR  ip_chHLen: 4;
* #endif
*     UCHAR   ip_chTOS;
*     USHORT  ip_usLen;
* #define ip_sLen ip_usLen
*     USHORT  ip_usId;
*     USHORT  ip_usOff;
* #define ip_sOff ip_usOff
*     UCHAR   ip_chTTL;
*     UCHAR   ip_chPr;
*     USHORT  ip_usSum;
*     struct  tagACL_INADDR ip_stSrc;
*     struct  tagACL_INADDR ip_stDst;
* }ACL_IP_S;
* @endcode 
* 
* @par Description
* This structure stores IP header details of network packets.
* 
* @datastruct ip_chHLen Indicates IP packet header length
* @datastruct ip_chVer Indicates version(IPV4/IPV6)
* @datastruct ip_chTOS Indicates type of service
* @datastruct ip_usLen Indicates total length of packet
* @datastruct ip_sLen Indicates total length of packet
* @datastruct ip_usId Indicates identification number
* @datastruct ip_usOff Indicates fragmentation offset
* @datastruct ip_sOff Indicates fragmentation offset
* @datastruct ip_chTTL Indicates TTL(Time TO Live) value
* @datastruct ip_chPr Indicates type of protocol
* @datastruct ip_usSum Indicates check-sum of packet
* @datastruct ip_stSrc Indicates source IP address
* @datastruct ip_stDst Indicates destination IP address
*/
typedef struct tagACL_IP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ip_chHLen:4;        /* header length */
    UCHAR   ip_chVer: 4;         /* version */
#else
    UCHAR  ip_chVer:  4;         /* version */
    UCHAR  ip_chHLen: 4;        /* header length */
#endif
    UCHAR   ip_chTOS;           /* type of service */
    USHORT  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    USHORT  ip_usId;            /* identification */
    USHORT  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
    UCHAR   ip_chTTL;           /* time to live */
    UCHAR   ip_chPr;            /* protocol */
    USHORT  ip_usSum;           /* checksum */
    struct  tagACL_INADDR ip_stSrc;
    struct  tagACL_INADDR ip_stDst; /* source and dest address */
}ACL_IP_S;

/* TCP报文首部定义 */
/**
* @defgroup tagACL_TCPHDR ACL_TCPHDR_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_TCPHDR
* {
*     USHORT  usSrcPort;
*     USHORT  usDstPort;
*     ULONG   seqSeqNumber;
*     ULONG   seqAckNumber;
* #if VRP_LITTLE_ENDIAN == VRP_YES
*     UCHAR  ucX2:4,
*     ucOffset:4;
* #else
*     UCHAR  ucOffset:4,
*            ucX2:4;
* #endif
*     UCHAR   ucFlags;
*     USHORT  usWnd;
*     USHORT  usCheckSum;
*     USHORT  usUrgentPoint;
* } ACL_TCPHDR_S;
* @endcode 
* 
* @par Description
* This structure stores TCP header details of network packets.
* 
* @datastruct usSrcPort Indicates source port number
* @datastruct usDstPort Indicates destination port number
* @datastruct seqSeqNumber Indicates sequence number
* @datastruct seqAckNumber Indicates acknowledgement number
* @datastruct ucX2 X2
* @datastruct ucOffset Offset
* @datastruct ucFlags Indicates TCP flags
* @datastruct usWnd Window size
* @datastruct usCheckSum Indicates checksum of TCP header
* @datastruct usUrgentPoint Indicates urgent pointer
*/
typedef struct tagACL_TCPHDR
{
    USHORT  usSrcPort;
    USHORT  usDstPort;
    ULONG   seqSeqNumber;
    ULONG   seqAckNumber;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR  ucX2:4,
    ucOffset:4;
#else
    UCHAR  ucOffset:4, /* warning:nonstandard extension used : bit field types other than LONG. */
    ucX2:4;     /* warning:nonstandard extension used : bit field types other than LONG. */
#endif
    UCHAR   ucFlags;
    USHORT  usWnd;
    USHORT  usCheckSum;
    USHORT  usUrgentPoint;
} ACL_TCPHDR_S;


/* UDP报文首部定义 */
/**
* @defgroup tagACL_UDPHDR ACL_UDPHDR_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_UDPHDR
* {
*     USHORT  uh_usSPort;
*     USHORT  uh_usDPort;
*     SHORT   uh_sULen;
*     USHORT  uh_usSum;
* }ACL_UDPHDR_S;
* @endcode 
* 
* @par Description
* This structure stores TCP header details of network packets.
* 
* @datastruct uh_usSPort Indicates source port number
* @datastruct uh_usDPort Indicates destination port number
* @datastruct uh_sULen Indicates header length
* @datastruct uh_usSum Indicates checksum of UDP header
*/
typedef struct tagACL_UDPHDR
{
    USHORT  uh_usSPort;     /* source port */
    USHORT  uh_usDPort;     /* destination port */
    SHORT   uh_sULen;       /* udp length */
    USHORT  uh_usSum;       /* udp checksum */
}ACL_UDPHDR_S;


/* ICMP报文首部定义 */
typedef struct tagACL_ICMP
{
    UCHAR   icmp_chType;        /* type of message, see below */
    UCHAR   icmp_chCode;        /* type sub code */
    USHORT  icmp_usCksum;       /* ones complement cksum of struct */
    union
    {
        UCHAR   ih_chPPtr;      /* ICMP_PARAMPROB */
        struct tagACL_INADDR ih_stGwAddr;   /* ICMP_REDIRECT */
        struct tagACL_IHIDSEQ
        {
            USHORT  icd_nsId;
            USHORT  icd_nsSeq;
        } Acl_ih_stIdSeq;
        LONG     ih_nVoid;

        /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
        struct tagACL_IHPMTU
        {
            USHORT ipm_nsVoid;
            USHORT ipm_nsNextMtu;
        } Acl_ih_stPMtu;
    }icmp_unHun;
#define icmp_chPPtr     icmp_unHun.ih_chPPtr
#define icmp_stGwAddr   icmp_unHun.ih_stGwAddr
#define icmp_nsId       icmp_unHun.ih_stIdSeq.icd_nsId
#define icmp_nsSeq      icmp_unHun.ih_stIdSeq.icd_nsSeq
#define icmp_nVoid      icmp_unHun.ih_nVoid
#define icmp_nsPmVoid   icmp_unHun.ih_stPMtu.ipm_nsVoid
#define icmp_nsNextMtu  icmp_unHun.ih_stPMtu.ipm_nsNextMtu
    union
    {
        struct tagACL_IDTS
        {
            ULONG  its_ntOTime;
            ULONG  its_ntRTime;
            ULONG  its_ntTTime;
        } Acl_id_stTS;
        struct tagACL_IDIP
        {
            struct tagACL_IP idi_stIp;
        } Acl_id_stIp;
        ULONG   id_ulMask;
        char    id_chData_a[9];
    } icmp_unDun;
#define icmp_ntOTime    icmp_unDun.id_stTS.its_ntOTime
#define icmp_ntRTime    icmp_unDun.id_stTS.its_ntRTime
#define icmp_ntTTime    icmp_unDun.id_stTS.its_ntTTime
#define icmp_stIp       icmp_unDun.id_stIp.idi_stIp
#define icmp_ulMask     icmp_unDun.id_ulMask
#define icmp_chData_a   icmp_unDun.id_chData_a
}ACL_ICMP_S;

#ifndef _PF_ACLREFRESHCALLBACK
#define _PF_ACLREFRESHCALLBACK
/* Added by z43740 for: ACL变化对外通知,2008/03/12 */
/**
* @defgroup PF_ACLREFRESHCALLBACK PF_ACLREFRESHCALLBACK
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID (*PF_ACLREFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
* @endcode 
* 
* @par Description
* This is a call back function to notify ACL change to external modules.	
* 
* @param[in] ulGroupId Indicates the group that getting changed [NA]
* @param[in] ulRuleId Indicates the rule ID that is getting changed [NA]
* @param[in] ulEventType Indicates action type for the rule (Add/Delete/Modify) [NA]
* 
* @retval VOID This function does not return any value [NA|NA]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef VOID (*PF_ACLREFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif


/* acl update callback structure */
/**
* @defgroup tagACL_UPDATE_CALLBACK_NODE ACL_UPDATE_CALLBACK_NODE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_UPDATE_CALLBACK_NODE
* {
*     PF_ACLREFRESHCALLBACK pfCallBack;
*     ULONG ulModuleId;
*     struct tagACL_UPDATE_CALLBACK_NODE * pstNext;
* }ACL_UPDATE_CALLBACK_NODE_S;
* @endcode 
* 
* @par Description
* This structure is an ACL update callback structure.
* 
* @datastruct pfCallBack Indicates call back function that needs to be called when ACL update happens
* @datastruct ulModuleId Module ID
* @datastruct pstNext Indicates next ACL call back structure
*/
typedef struct tagACL_UPDATE_CALLBACK_NODE
{
    PF_ACLREFRESHCALLBACK pfCallBack;
    ULONG ulModuleId;
    struct tagACL_UPDATE_CALLBACK_NODE * pstNext;
}ACL_UPDATE_CALLBACK_NODE_S;

/**
* @defgroup tagPPI_ACLFWCFG PPI_ACLFW_CFG_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagPPI_ACLFWCFG
* {
*     CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1];
*     ULONG   ulGroupID;
*     ULONG   ulDirection;
*     ULONG   ulDefaultAction;
* }PPI_ACLFW_CFG_S;
* @endcode 
* 
* @par Description
* This structure binds a group number to a particular interface defined by stIfName. 
* 
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name
* @datastruct ulGroupID ACL group ID
* @datastruct ulDirection It is the packet filter direction. The possible values are:
*	- 0-Inbound
*	- 1-Outbound
*	- 2-MAC-Inbound
*	- 3-MAC-Outbound
* @datastruct ulDefaultAction Indicates Default action to be taken when there is no rule that exists in
* the attached group. It can have the following values:
*	- 1 (ACLFW_DENY) : Denies access
*	- 0 (ACLFW_PERMIT) : Permits access
*/
/* ACL 防火墙配置下发PPI数据结构 */
typedef struct tagPPI_ACLFWCFG
{
    CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1]; /*接口名称*/
    ULONG   ulGroupID;          /* 规则组号 */ 
    ULONG   ulDirection;        /* Filter Direction 0:Inbound 1:Outbound 2: MAC-Inbound 3:MAC-Outbound*/ 
    ULONG   ulDefaultAction; /*ACL 没有匹配rule时的默认动作 ACLFW_DENY:1  ACLFW_PERMIT:0*/
}PPI_ACLFW_CFG_S;

/**
* @defgroup tagPPIACLFWMSGType E_ACLFW_PPI_MSG
* @ingroup ACLE ACL Enums
* @par Prototype
* @code
* typedef enum tagPPIACLFWMSGType
* {
*     PPI_ACLFW_BIND,
*     PPI_ACLFW_STAT
* }E_ACLFW_PPI_MSG;
* @endcode 
* 
* @par Description
* This enum stores the types of ACLFW messages.
* 
* @datastruct PPI_ACLFW_BIND Indicates packet filter binding.
* @datastruct PPI_ACLFW_STAT Indicates access to statistical information.
*/
typedef enum tagPPIACLFWMSGType  /* ulMsgType 取值*/
{
    PPI_ACLFW_BIND,        /* 包过滤绑定*/
        PPI_ACLFW_STAT         /*获取统计信息*/
}E_ACLFW_PPI_MSG;

/*---------------------------------
ACLFW PPI 结构定义
---------------------------------*/
/**
* @defgroup tagPPIACLFWOPRType E_ACLFW_PPI_OPR
* @ingroup ACLE ACL Enums
* @par Prototype
* @code
* typedef enum tagPPIACLFWOPRType
* {
*     PPI_ACLFW_ADD,
*     PPI_ACLFW_DEL,
*     PPI_ACLFW_GET,
*     PPI_ACLFW_CLR,
*     PPI_ACLFW_MAX
* }E_ACLFW_PPI_OPR;
* @endcode 
* 
* @par Description
* This enum stores the type of ACLFW operation type.
* 
* @datastruct PPI_ACLFW_ADD A new group is bound with an interface.
* @datastruct PPI_ACLFW_DEL A group is unbound with an interface.
* @datastruct PPI_ACLFW_GET To get hardware statistics.
* @datastruct PPI_ACLFW_CLR To clear the statistics.
* @datastruct PPI_ACLFW_MAX Indicate the maximum possible value of the type of operations. 
* All error codes for types of operation should be declared above this.
*/
typedef enum tagPPIACLFWOPRType  /* ulOprType  取值*/
{
    PPI_ACLFW_ADD,  /* 新增或者更新IP层防火墙配置节点 */
    PPI_ACLFW_DEL,  /* 删除IP层防火墙配置节点 */
    PPI_ACLFW_GET,  /* 获取防火墙信息 */
    PPI_ACLFW_CLR,  /* 信息清除*/
    PPI_ACLFW_MAX
}E_ACLFW_PPI_OPR;


/**
* @defgroup tagACL_pkt_type ACL_PKT_INOUT_TYPE_E
* @ingroup ACLE ACL Enums
* @par Prototype
* @code
* typedef enum tagACL_pkt_type
* {
*    ACL_INBOUND_TYPE = 0x0,
*    ACL_OUTBOUND_TYPE,
*    ACL_MAX_TYPE
* }ACL_PKT_INOUT_TYPE_E;
* @endcode 
* 
* @par Description
* This enum can be used to specify the flow; either inbound/outbound.
* 
* @datastruct ACL_INBOUND_TYPE Indicates inbound direction.
* @datastruct ACL_OUTBOUND_TYPE Indicates outbound direction.
* @datastruct ACL_MAX_TYPE Indicates maximum limit for this enum.
*/
typedef enum tagACL_pkt_type
{
    ACL_INBOUND_TYPE = 0x0,
    ACL_OUTBOUND_TYPE,
    ACL_MAX_TYPE
}ACL_PKT_INOUT_TYPE_E;


#define ACL_UPDATE_GROUP_DELETE         1
#define ACL_UPDATE_RULE_DELETE          2
#define ACL_UPDATE_RULE_MODIFY          3
#define ACL_UPDATE_RULE_ADD             4
#define ACL_UPDATE_GROUP_DELETE_ALL     5

/*Begin:VISP V1R8C01 Interface based  eswar 2009-11-03*/
#define ACL_UPDATE_RULE_IF_ADD          6
#define ACL_UPDATE_RULE_IF_DELETE       7
#define ACL_UPDATE_RULE_IF_MODIFY       8
/*End:VISP V1R8C01 Interface based  eswar 2009-11-03*/

/*Added by r72335 Begin 17-3-2011:
  Added one more ACL configuration type*/
#define ACL_UPDATE_GROUP_ADD            9
/*Added by r72335 End*/


/* End of addition by z43740 2008/03/12 */

/*Begin 2008-09-10 V1R7C02 同步V1R7C01*/
/**
* @defgroup ACL_PPI_GROUP_Update_NODES ACL_PPI_GROUP_Update_NODES
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID (*ACL_PPI_GROUP_Update_NODES) (ULONG ulOprType, ULONG ulGroupID);
* @endcode 
* 
* @par Description
* This is a PPI call back function to notify external modules about ACL group modifications.
* 
* @param[in] ulOprType Indicates the action that has been taken on the group(Add/Delete/Modify) [NA]
* @param[in] ulGroupID Indicates ACL group number [NA]
* 
* @retval VOID This function does not return any value [NA|NA]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef VOID (*ACL_PPI_GROUP_Update_NODES) (ULONG ulOprType, ULONG ulGroupID);

/**
* @defgroup ACL_PPI_RULE_Update_NODES ACL_PPI_RULE_Update_NODES
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID (*ACL_PPI_RULE_Update_NODES) (ULONG ulOprType, 
*                                    ULONG ulGroupID, 
*                                    ULONG ulRuleID, 
*                                    ULONG ulIfIndex,
*                                    ULONG ulDirection, 
*                                    VOID *pstContext);
* @endcode 
* 
* @par Description
* This is a PPI call back function to notify external modules about ACL rule modifications. 
* 
* @param[in] ulOprType Indicates operation type that has been taken on the given rule (Add/Delete/modify) [NA]
* @param[in] ulGroupID Indicates the group number for the modified rule [NA]
* @param[in] ulRuleID Indicates the ID of modified rule [NA]
* @param[in] ulIfIndex Indicates the interface index if the modified rule is bind with it [NA]
* @param[in] ulDirection Indicate the direction of that rule to work (Inbound/Outbound) [NA]
* @param[in] pstContext Configuration context [NA]
* @param[out] NA NA [NA]
* 
* @retval VOID This function does not return any value [NA|NA]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef VOID (*ACL_PPI_RULE_Update_NODES) (ULONG ulOprType, ULONG ulGroupID, ULONG ulRuleID, ULONG ulIfIndex,
                                           ULONG ulDirection, VOID *pstContext);

/*End    2008-09-10 V1R7C02 同步V1R7C01*/

/* Begin Add NEW.R.FireWall liangjicheng 2009-08-17 */
/**
* @defgroup ACLFW_PPI_UPDATE_NODES ACLFW_PPI_UPDATE_NODES
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG (*ACLFW_PPI_UPDATE_NODES) (ULONG ulOprType, ULONG ulMsgType, VOID *pData);
* @endcode 
* 
* @par Description
* This function is a callback function declaration for ACL node update.
* 
* @param[in] ulOprType Operation type [NA]
* @param[in] ulMsgType Message type [NA]
* @param[in] pData Configured data [NA]
* 
* @retval ULONG Return value depends on hooking function [NA|NA]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef ULONG (*ACLFW_PPI_UPDATE_NODES) (ULONG ulOprType, ULONG ulMsgType, VOID *pData);

/* End Add NEW.R.FireWall*/
/**
* @defgroup ACL_COM_WAITLIST_DEL_NOTIFY ACL_COM_WAITLIST_DEL_NOTIFY
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG (*ACL_COM_WAITLIST_DEL_NOTIFY) (ULONG ulMainType, VOID *pDataToDel);
* @endcode 
* 
* @par Description
* This function is a callback function declaration for ACL delete node update.
* 
* @param[in] ulMainType Module information [NA]
* @param[in] pDataToDel Data to be deleted [NA]
* 
* @retval ULONG return value depends on hooking function [NA|NA]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef ULONG (*ACL_COM_WAITLIST_DEL_NOTIFY) (ULONG ulMainType, VOID *pDataToDel);

/*Begin C02NEWR-ACL liangjicheng 2008-10-24*/
/* Description   :验证值是否在范围内，如果不在修改为相关范围*/

#define ACL_CHECKMINVALUE(checkValue, minValue)\
{\
    if (checkValue < minValue)\
    checkValue = minValue;\
}

#define ACL_CHECKMAXVALUE(checkValue, maxValue)\
{\
    if (checkValue > maxValue)\
    checkValue = maxValue;\
}

 /* Description   :将一个范围赋值*/
#define ACL_SETRANGE(beginValue, endValue, newBeginValue, newEndValue)\
{\
    if (newBeginValue <= newEndValue){\
    beginValue = newBeginValue;\
    endValue = newEndValue;\
    }\
    else\
    {\
        beginValue = newEndValue;\
        endValue = newBeginValue;\
    }\
}

/**
* @defgroup tagACLFW_CFG ACLFW_CFG_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_CFG
* {
*     ULONG   ulNoFlag;
*     CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1];
*     ULONG   ulACLGroup;
*     ULONG   ulDirection;
*     ULONG   ulDefaultAction;
* }ACLFW_CFG_S;
* @endcode 
* 
* @par Description
* This structure is used to configure ACL Firewall.
* 
* @datastruct ulNoFlag This flag indicates whether to add or delete 
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name.
* @datastruct ulACLGroup ACL group.
* @datastruct ulDirection Indicates the packet filtering direction. It can have the following values:
*	- 0 : Inbound 
*	- 1 : Outbound 
*	- 2 : MAC Inbound 
*	- 3 : MAC Outbound
* @datastruct ulDefaultAction Indicates Default action to be taken when there is no rule that exists in
* the attached group. It can have the following values:
*	- 1 (ACLFW_DENY) : Denies access
*	- 0 (ACLFW_PERMIT) : Permits access
*/
/*此数据结构用来配置ACL FireWall*/
typedef struct tagACLFW_CFG
{
    ULONG   ulNoFlag;       /*0: Add  1:Del*/    
    CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1];          
    ULONG   ulACLGroup;     /*ACL Group */
    /* Begin Modify NEW.R.FireWall liangjicheng 2009-08-17 */
    ULONG   ulDirection;    /*Filter Direction 0:Inbound 1:Outbound 2: MAC-Inbound 3:MAC-Outbound*/  
    /* End Modify NEW.R.FireWall */
    ULONG ulDefaultAction; /*ACL 没有匹配rule时的默认动作 ACLFW_DENY:0  ACLFW_PERMIT:1*/
}ACLFW_CFG_S;

/**
* @defgroup tagACLFW_CFGEX ACLFW_CFGEX_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_CFGEX
* {
*     ULONG   ulNoFlag;
*     CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN + 1];
*     ULONG   ulIfIndex;
*     ULONG   ulACLGroup;
*     ULONG   ulDirection;
*     ULONG ulDefaultAction;
* }ACLFW_CFGEX_S;
* @endcode 
* 
* @par Description
* This structure contains the configuration of extended version of ACLFW.
* 
* @datastruct ulNoFlag This flag indicates whether to add or delete 
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name
* @datastruct ulIfIndex Interface index.
* @datastruct ulACLGroup ACL group.
* @datastruct ulDirection Indicates the packet filtering direction. It can have the following values:
*	- 0 : Inbound 
*	- 1 : Outbound 
*	- 2 : MAC Inbound 
*	- 3 : MAC Outbound
* @datastruct ulDefaultAction Indicates Default action to be taken when there is no rule that exists in
* the attached group. It can have the following values:
*	- 1 (ACLFW_DENY) : Denies access
*	- 0 (ACLFW_PERMIT) : Permits access
*/
/*Extended version of ACLFW_CFG_S*/
typedef struct tagACLFW_CFGEX
{
    ULONG   ulNoFlag;       /*0: Add  1:Del*/    
    CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN + 1];
    ULONG   ulIfIndex;      /*Interface index*/
    ULONG   ulACLGroup;     /*ACL Group */
    ULONG   ulDirection;    /*Filter Direction 0:Inbound 1:Outbound 2: MAC-Inbound 3:MAC-Outbound*/  
    ULONG ulDefaultAction; /*ACL 没有匹配rule时的默认动作 ACLFW_DENY:1  ACLFW_PERMIT:0*/
}ACLFW_CFGEX_S;

/**
* @defgroup tagACLFW_SHOWCFG ACLFW_SHOWCFG_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_SHOWCFG
* {
*     CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1];
*     ULONG   ulIfIndex;
*     ULONG   ulInboundACL;
*     ULONG   ulOutboundACL;
*     ULONG   ulMacInboundACL;
*     ULONG   ulMacOutboundACL;
*     ULONG   ulInBoundACLDefaultAction;
*     ULONG   ulOutBoundACLDefaultAction;
*     ULONG   ulMacInBoundACLDefaultAction;
*     ULONG   ulMacOutBoundACLDefaultAction;
* }ACLFW_SHOWCFG_S;
* @endcode 
* 
* @par Description
* This structure displays the ACLFW configuration details.
* 
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name.
* @datastruct ulIfIndex Interface index.
* @datastruct ulInboundACL Indicates inbound packet ACL.
* @datastruct ulOutboundACL Indicates outbound packet ACL.
* @datastruct ulMacInboundACL Indicates MAC inbound packet ACL.
* @datastruct ulMacOutboundACL Indicates MAC outbound packet ACL.
* @datastruct ulInBoundACLDefaultAction Indicates default action to be taken when there is 
* no rule that exists in attached group for inbound packets in IP layer.
* @datastruct ulOutBoundACLDefaultAction Indicates default action to be taken when there is 
* no rule that exists in attached group for outbound packets in IP layer.
* @datastruct ulMacInBoundACLDefaultAction Indicates default action to be taken when there is 
* no rule that exists in attached group for inbound packets in MAC layer.
* @datastruct ulMacOutBoundACLDefaultAction Indicates default action to be taken when there is 
* no rule that exists in attached group for outbound packets in MAC layer.
*/
/*此数据结构用来显示配置ACL FireWall*/
typedef struct tagACLFW_SHOWCFG
{
    CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN+1];       
    ULONG   ulIfIndex;
    ULONG   ulInboundACL;       /*接口IP层接收方向过滤ACL组*/
    ULONG   ulOutboundACL;      /*接口IP层发送方向过滤ACL组*/
    /* Begin Modify NEW.R.FireWall liangjicheng 2009-08-17 */
    ULONG   ulMacInboundACL;    /*接口Mac层接收方向过滤ACL组*/
    ULONG   ulMacOutboundACL;   /*接口Mac层发送方向过滤ACL组*/
    /* End Modify NEW.R.FireWall */

    /*Begin Added by eswar: Default action is added for every interface*/
    ULONG   ulInBoundACLDefaultAction;
    ULONG   ulOutBoundACLDefaultAction;
    ULONG   ulMacInBoundACLDefaultAction;
    ULONG   ulMacOutBoundACLDefaultAction;
    /*Added by eswar End*/

    
}ACLFW_SHOWCFG_S;

/**
* @defgroup tagACLFW_STAT ACLFW_STAT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_STAT
* {
*     ULONG ulInDropPackets;
*     ULONG ulInPassPackets;
*     ULONG ulInErrPackets;
*     ULONG ulOutDropPackets;
*     ULONG ulOutPassPackets;
*     ULONG ulOutErrPackets;
*     ULONG ulMacInDropPackets;
*     ULONG ulMacInPassPackets;
*     ULONG ulMacInErrPackets;
*     ULONG ulMacOutDropPackets;
*     ULONG ulMacOutPassPackets;
*     ULONG ulMacOutErrPackets;
* }ACLFW_STAT_S;
* @endcode 
* 
* @par Description
* This structure stores the ACLFW statistics.
* 
* @datastruct ulInDropPackets Indicates the number of the dropped interface inbound packets.
* @datastruct ulInPassPackets Indicates the number of the passed interface inbound packets.
* @datastruct ulInErrPackets Indicates the number of the interface inbound packets with error.
* @datastruct ulOutDropPackets Indicates the number of the dropped interface outbound packets.
* @datastruct ulOutPassPackets Indicates the number of the passed interface outbound packets.
* @datastruct ulOutErrPackets Indicates the number of the interface outbound packets with error.
* @datastruct ulMacInDropPackets Indicates the number of the dropped MAC interface inbound packets.
* @datastruct ulMacInPassPackets Indicates the number of the passed MAC interface inbound packets.
* @datastruct ulMacInErrPackets Indicates the number of the MAC interface inbound packets with error.
* @datastruct ulMacOutDropPackets Indicates the number of the dropped MAC interface outbound packets.
* @datastruct ulMacOutPassPackets Indicates the number of the passed MAC interface outbound packets.
* @datastruct ulMacOutErrPackets Indicates the number of the MAC interface outbound packets with error.
*/
typedef struct tagACLFW_STAT
{
    ULONG ulInDropPackets;
    ULONG ulInPassPackets;
    ULONG ulInErrPackets;
    ULONG ulOutDropPackets;
    ULONG ulOutPassPackets;
    ULONG ulOutErrPackets;
    /* Begin Add NEW.R.FireWall liangjicheng 2009-08-17 */
    ULONG ulMacInDropPackets;   /*Mac层接收方向丢弃报文个数*/
    ULONG ulMacInPassPackets;   /*Mac层接收方向通过报文个数*/
    ULONG ulMacInErrPackets;    /*Mac层接收方向错误报文个数*/
    ULONG ulMacOutDropPackets;  /*Mac层发送方向丢弃报文个数*/
    ULONG ulMacOutPassPackets;  /*Mac层发送方向通过报文个数*/
    ULONG ulMacOutErrPackets;   /*Mac层发送方向错误报文个数*/
    /* End Add NEW.R.FireWall */
}ACLFW_STAT_S;

/*End C02NEWR-ACL liangjicheng 2008-10-24*/

/**
* @defgroup tagACLFW_SHOWFILTER_S ACLFW_SHOWFILTER_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_SHOWFILTER_S
* {
*     CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN + 1];
* }ACLFW_SHOWFILTER_S;
* @endcode 
* 
* @par Description
* This structure displays the ACLFW interface filter.
* 
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name.
*/
/*此数据结构用来配置ACL FireWall*/
typedef struct tagACLFW_SHOWFILTER_S
{
    CHAR    stIfName[ACLFW_MAX_INT_NAME_LEN + 1];
}ACLFW_SHOWFILTER_S;

/************************************************************************************************/
#ifndef _ACL_ITEM
#define _ACL_ITEM
/**
* @defgroup tagACL_Item ACL_Item/PACL_Item
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_Item
* {
*     ACL_RANGE32_S   stSIP;
*     ACL_RANGE32_S   stDIP;
*     UCHAR           ucPID;
*     UCHAR           ucPadding[3];
*     USHORT          usSP;
*     USHORT          usDP;
*     ULONG           ulVrfIndex;
* } ACL_Item, * PACL_Item;
* @endcode 
* 
* @par Description
* This structure contains the ACL sub-items.
* 
* @datastruct stSIP Source IP address
* @datastruct stDIP Destination IP address
* @datastruct ucPID Port ID.
* @datastruct ucPadding[3] Indicates padding.
* @datastruct usSP Source port number.
* @datastruct usDP Destination port number.
* @datastruct ulVrfIndex VRF index.
*/
/* ACL的子项,提供给IPSEC模块调用 */
typedef struct tagACL_Item
{
    ACL_RANGE32_S   stSIP;  /* 源地址 */
    ACL_RANGE32_S   stDIP;  /* 目的地址 */
    UCHAR           ucPID;  /* 协议号 */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* 源端口号 */
    USHORT          usDP;   /* 目的端口号 */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG           ulVrfIndex; /* 指定VRF，如果匹配所有则VrfIndex配置为0xFFFFFFFFL,如果没有使用VRF则填写0 */
    /* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */

    /* Begin:VISP V3R2C10 port-range chandra , 2014-03-27 */
    USHORT          usSPEnd; /*Source port End. Port Range will be considered only when this field is non-zero. */
    /* End:VISP V3R2C10 port-range chandra , 2014-03-27 */
    /* Begin:VISP V3R2C10 port-range chandra , 2014-03-27 */
    USHORT          usDPEnd; /* Dest port End.Port Range will be considered only when this field is non-zero. */
    /* End:VISP V3R2C10 port-range chandra , 2014-03-27 */
    
} ACL_Item, * PACL_Item;
#endif

/* ACL config information */
/**
* @defgroup tagAclConfig ACLCONFIG_S/PACLCONFIG_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAclConfig
* {
*     ULONG ulAclNumMin;
*     ULONG ulAclNumMax;
*     ULONG ulAclBasMinExt;
*     ULONG ulAclBasMaxExt;
*     ULONG ulAclAdvMinExt;
*     ULONG ulAclAdvMaxExt;
*     ULONG ulIpAddrAny;
*     ULONG ulAclDeny;
*     ULONG ulAclPermit;
*     ULONG ulAclNotfound;
* } ACLCONFIG_S, *PACLCONFIG_S;
* @endcode 
* 
*
* @par Description
* This structure stores ACL configuration.
* 
* @datastruct ulAclNumMin Indicates the minimum ACL number.
* @datastruct ulAclNumMax Indicates the maximum ACL number.
* @datastruct ulAclBasMinExt Indicates ACL basic minimum extension.
* @datastruct ulAclBasMaxExt Indicates ACL basic maximum extension.
* @datastruct ulAclAdvMinExt Indicates ACL advanced minimum extension.
* @datastruct ulAclAdvMaxExt Indicates ACL advanced maximum extension.
* @datastruct ulIpAddrAny Indicates any IP address.
* @datastruct ulAclDeny Indicates deny the ACL.
* @datastruct ulAclPermit Indicates permit the ACL.
* @datastruct ulAclNotfound Indicates ACL rule not found.
*/ 
#ifndef _ACLCONFIG_S
#define _ACLCONFIG_S
/* ACL config information */
typedef struct tagAclConfig
{
    ULONG ulAclNumMin;          /* 最小规则组序号 */
    ULONG ulAclNumMax;          /* 最大规则组序号 */
    ULONG ulAclBasMinExt;       /* 最小基本规则组序号 */
    ULONG ulAclBasMaxExt;       /* 最大基本规则组序号 */
    ULONG ulAclAdvMinExt;       /* 最小扩展规则组序号 */
    ULONG ulAclAdvMaxExt;       /* 最大扩展规则组序号 */
    ULONG ulIpAddrAny;          /* ip地址通配符 */
    ULONG ulAclDeny;            /* acl deny取值 */
    ULONG ulAclPermit;          /* acl permit取值 */
    ULONG ulAclNotfound;        /* acl notfound取值 */
} ACLCONFIG_S, *PACLCONFIG_S;
#endif

/**
* @defgroup tagIPPacketInfo IPPACKETINFO_S/PIPPACKETINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagIPPacketInfo 
* {
*    ULONG ulSIP;
*    ULONG ulDIP;
*    USHORT usSP;
*    USHORT usDP;
*    BOOL_T bFO;
*    BOOL_T bFM;
*    UCHAR ucPID;
*    UCHAR ucPRE;
*    UCHAR ucTOS;
*    UCHAR ucDSCP;
*    ULONG ulIfIndex;
*    ULONG ulIgnoreByte;
*    ULONG ulVrfIndex;
* } IPPACKETINFO_S, *PIPPACKETINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of IP packet information.
* 
* @datastruct ulSIP Indicates source IP address
* @datastruct ulDIP Indicates destination IP address
* @datastruct usSP Indicates source port number
* @datastruct usDP Indicates destination port number
* @datastruct bFO Indicates whether packet is fragmented
* @datastruct bFM Indicates whether packet filtering mode is used or not
* @datastruct ucPID Indicates protocol ID
* @datastruct ucPRE Indicates precedence value
* @datastruct ucTOS Indicates TOS value
* @datastruct ucDSCP Indicates DSCP value
* @datastruct ulIfIndex Indicates interface index value
* @datastruct ulIgnoreByte Indicates the byte used to indicate which field should be ignored
* @datastruct ulVrfIndex Indicates VRF index value
*/

#ifndef IPSAFE_IPPACKETINFO_S
#define IPSAFE_IPPACKETINFO_S
/* This structure is used to store information extracted from the IP packet */
typedef struct tagIPPacketInfo 
{
    ULONG ulSIP;              /* Source IP address */            
    ULONG ulDIP;              /* Destination IP address */ 
    USHORT usSP;             /* Source port number or ICMP Type */            
    USHORT usDP;             /* Destination port number or ICMP Type*/            
    BOOL_T bFO;               /* non initial fragment flag */
    BOOL_T bFM;               /* reserved. it is used for accurately match before. */
    UCHAR ucPID;             /* Protocol Number  */            
    UCHAR ucPRE;             /* precedence */          
    UCHAR ucTOS;             /* TOS value  */
    UCHAR ucDSCP;           /* DSCP Value */ 
    ULONG ulIfIndex;        /* Interface Index */
    ULONG ulIgnoreByte;     /* the byte used to indicate which field should be ingored */

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;           /* Vrf index */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} IPPACKETINFO_S, *PIPPACKETINFO_S;

#endif

/**
* @defgroup tagACLShowCond ACL_FILTER_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLShowCond
* {    
*     ULONG  ulRuleNumber;
* }ACL_FILTER_S;
* @endcode 
* 
*
* @par Description
* This structure stores the rule number for filtering the ACL rules.
* 
* @datastruct ulRuleNumber Indicates rule number to filter.
*/ 
typedef struct tagACLShowCond
{    
    ULONG  ulRuleNumber;
}ACL_FILTER_S;

/**
* @defgroup tagACLGroupShowCond ACL_GROUP_FILTER_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLGroupShowCond
* {    
*     ULONG  ulGroupNumber;
* }ACL_GROUP_FILTER_S;
* @endcode 
* 
*
* @par Description
* This structure stores the group number for filtering ACL group.
* 
* @datastruct ulGroupNumber Indicates the group number to filter.
*/ 
typedef struct tagACLGroupShowCond
{    
    ULONG  ulGroupNumber;
}ACL_GROUP_FILTER_S;



/* ACL PPI操作类型, 修改此枚矩需要同步修改ACL_PPI_OprType_En处理*/
/**
* @defgroup tagPPI_MSG_TYPE_ACL_E PPI_MSG_TYPE_ACL_E
* @ingroup ACLE ACL Enums
* @par Prototype
* @code
* typedef enum tagPPI_MSG_TYPE_ACL_E
* {
*     PPI_ACLRULE_CREATE,
*     PPI_ACLRULE_UPDATE,
*     PPI_ACLRULE_DEL,
*     PPI_ACLRULE_DELALL,
*     PPI_ACLGROUP_CREATE,
*     PPI_ACLGROUP_DEL,
*     PPI_ACL_GETMATCHCOUNT,
*     PPI_ACLRULE_IF_CREATE,
*     PPI_ACLRULE_IF_DEL,
*     PPI_ACLRULE_IF_UPDATE,
*     ACL_PPI_MSG_MAX
* }PPI_MSG_TYPE_ACL_E;
* @endcode 
* 
* @par Description
* This enum contains message types used to send to external product through PPI calls.
*
* @datastruct PPI_ACLRULE_CREATE ACL rule is created
* @datastruct PPI_ACLRULE_UPDATE ACL rule is updated
* @datastruct PPI_ACLRULE_DEL ACL rule is deleted 
* @datastruct PPI_ACLRULE_DELALL Delete all ACL rules from provided group
* @datastruct PPI_ACLGROUP_CREATE ACL group is created
* @datastruct PPI_ACLGROUP_DEL ACL group is deleted 
* @datastruct PPI_ACL_GETMATCHCOUNT To get the statistics from product 
* @datastruct PPI_ACLRULE_IF_CREATE New ACL group is bound with interface or new rules are added to the bound group 
* @datastruct PPI_ACLRULE_IF_DEL ACL group is unbound with the  interface or new rules are deleted from the bound group 
* @datastruct PPI_ACLRULE_IF_UPDATE ACL rule of interface bound group is updated 
* @datastruct ACL_PPI_MSG_MAX Maximum value
*/
typedef enum tagPPI_MSG_TYPE_ACL_E
{
    PPI_ACLRULE_CREATE,   /* 创建规则 */
    PPI_ACLRULE_UPDATE,   /* 更新规则 */
    PPI_ACLRULE_DEL,      /* 删除规则 */
    PPI_ACLRULE_DELALL,   /* 删除所有规则*/

    PPI_ACLGROUP_CREATE,  /* 创建规则组 */
    PPI_ACLGROUP_DEL,     /* 删除规则组 */

    PPI_ACL_GETMATCHCOUNT,/* 获取数据面匹配的统计信息 */

    /*Begin:VISP V1R8C01 Interface based  eswar 2009-11-03*/
    PPI_ACLRULE_IF_CREATE,
    PPI_ACLRULE_IF_DEL,
    PPI_ACLRULE_IF_UPDATE,
    /*End:VISP V1R8C01 Interface based  eswar 2009-11-03*/

    ACL_PPI_MSG_MAX
}PPI_MSG_TYPE_ACL_E;


/*us*Begin <= IN <= us*End*/
#define ACL_PORT_OP_TYPE_IN 0   

/*IN == us*Begin*/
#define ACL_PORT_OP_TYPE_EQ 1  

/*IN != us*Begin*/
#define ACL_PORT_OP_TYPE_NEQ 2  

/*IN >= us*Begin*/
#define ACL_PORT_OP_TYPE_GE 3 

/*IN <= us*Begin*/
#define ACL_PORT_OP_TYPE_LE 4  
#ifdef  __cplusplus
}
#endif


#endif /*_SFE_FW_ACL_COMMON_H_*/

