

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    LCD_LIGHT = 3,
    LCD_SLEEP,
    LCD_DIM,
    LCD_RESET,
    LCD_UPDATE,
    LCD_CONTRAST,
    LCD_BRIGHTNESS,
    LCD_POWER_ON,
    LCD_POWER_OFF,
    LCD_DEL_TIMER,/*delete the power on animation timer*/
    LCD_SYS_POWER_DOWN,
    LCD_INIT_IMAGE,
    LCD_POWER_OFF_CHARGING_START,/*restart power off charging animation*/
    LCD_POWER_OFF_CHARGING_STOP,/*stop power off charging animation*/
    LCD_GET_FRAME_BUFFER,
    LCD_WRITE_IMAGE,
    LCD_ALL_WHITE,
    LCD_ALL_BLACK,
    LCD_CMD_MAX
}LCD_IOCTL_CMD;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : lcdRefresh
 功能描述  : lcd在指定位置刷屏函数
 输入参数  :
 输出参数  :
*          UINT32 ulXStart, UINT32 ulYStart－－起始坐标
*          UINT32 ulXOffset, UINT32 ulYOffset－－横向纵向偏移量
*          UINT8 *pucBuffer－－显示数据
 返 回 值  : void
*****************************************************************************/
extern int lcdRefresh(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,const unsigned char * test_buf);

#if (defined BSP_CORE_APP)
/*****************************************************************************
 函 数 名  : balong_lcd_ioctl
 功能描述  : lcd ioctl
 输入参数  :
*            int cmd --command ID
*            arg--para
 输出参数  : none
 返 回 值  : BSP_S32
*****************************************************************************/
extern BSP_S32 balong_lcd_ioctl(struct file *file, unsigned int cmd, unsigned int arg);
#endif

extern BSP_VOID lcdClearWholeScreen(BSP_VOID);
extern BSP_VOID lcdStringDisplay(UINT8 ucX, UINT8 ucY, UINT8 *pucStr);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_lcd.h */

