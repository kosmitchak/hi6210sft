/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/

#ifndef __HI6402_DSP_REGS_H__
#define __HI6402_DSP_REGS_H__

#define HI6402_DSP_IOSHARE_BASE             0x20001000
#define HI6402_DSP_SCTRL_BASE               0x20003000
#define HI6402_CFG_SUB_BASE                 0x20007000
#define HI6402_AUDIO_SUB_BASE               0x20007200
#define HI6402_GPIO0_BASE                   0x20008000
#define HI6402_OCRAM1_BASE                  0x10020000

/* 0x20001000 */
#define HI6402_DSP_IOS_AF_CTRL0            (HI6402_DSP_IOSHARE_BASE + 0x100)
#define HI6402_DSP_IOS_IOM_I2S2_SDO        (HI6402_DSP_IOSHARE_BASE + 0x238)
#define HI6402_DSP_IOS_IOM_UART_TXD        (HI6402_DSP_IOSHARE_BASE + 0x278)

/* 0x20003000 */
#define HIFI_CMD_STAT                      (HI6402_DSP_SCTRL_BASE + 0x8)
#define HI6402_DSP_CMD_STAT_VLD            (HI6402_DSP_SCTRL_BASE + 0xc)

/* 0x20007000 */
#define HI6402_DSP_SW_RST_REQ              (HI6402_CFG_SUB_BASE + 0x001)
#define HI6402_DSP_CLK_CTRL                (HI6402_CFG_SUB_BASE + 0x002)
#define HI6402_DSP_SC_DSP_CTRL0            (HI6402_CFG_SUB_BASE + 0x004)
#define HI6402_DSP_CMD_STAT_VLD_IRQ        (HI6402_CFG_SUB_BASE + 0x016)
#define HI6402_DSP_RAM2AXI_CTRL            (HI6402_CFG_SUB_BASE + 0x020)
#define HI6402_DSP_I2S_DSPIF_CLK_EN        (HI6402_CFG_SUB_BASE + 0x045)
#define HI6402_DSP_DAC_DP_CLK_EN_1         (HI6402_CFG_SUB_BASE + 0x047)
#define HI6402_DSP_LP_CTRL                 (HI6402_CFG_SUB_BASE + 0x050)
#define HI6402_DSP_APB_CLK_CFG             (HI6402_CFG_SUB_BASE + 0x053)
#define HI6402_DSP_CMD_STATUS_VLD          (HI6402_CFG_SUB_BASE + 0x078)
#define HI6402_DSP_CMD_STATUS              (HI6402_CFG_SUB_BASE + 0x079)
#define HI6402_DSP_UART_DIV_0              (HI6402_CFG_SUB_BASE + 0x03D)
#define HI6402_DSP_UART_DIV_1              (HI6402_CFG_SUB_BASE + 0x03E)
#define HI6402_DSP_UART_DIV_2              (HI6402_CFG_SUB_BASE + 0x03F)
#define HI6402_DSP_UART_DIV_3              (HI6402_CFG_SUB_BASE + 0x03B)

/* 0x20007200 */
#define HI6402_CODE_CORE_BASE              (HI6402_CFG_SUB_BASE + 0x200)
#define HI6402_SC_S1_SRC_LR_CTRL_M         (HI6402_CODE_CORE_BASE + 0x37)
#define HI6402_SC_S2_SRC_LR_CTRL_M         (HI6402_CODE_CORE_BASE + 0x49)
#define HI6402_SC_S3_SRC_LR_CTRL_M         (HI6402_CODE_CORE_BASE + 0x58)
#define HI6402_SC_S4_SRC_LR_CTRL_M         (HI6402_CODE_CORE_BASE + 0x67)
#define HI6402_SC_FS_S1_CTRL_H             (HI6402_CODE_CORE_BASE + 0xAF)
#define HI6402_SC_FS_S2_CTRL_H             (HI6402_CODE_CORE_BASE + 0xB1)
#define HI6402_SC_FS_S3_CTRL_H             (HI6402_CODE_CORE_BASE + 0xB3)
#define HI6402_SC_FS_S4_CTRL_H             (HI6402_CODE_CORE_BASE + 0xB5)

/* 0x20008000 */
#define HI6402_GPIO0_DATA_ch5              (HI6402_GPIO0_BASE + 0x080)
#define HI6402_GPIO0_DIR                   (HI6402_GPIO0_BASE + 0x400)
#define HI6402_GPIO0_IS                    (HI6402_GPIO0_BASE + 0x404)
#define HI6402_GPIO0_IBE                   (HI6402_GPIO0_BASE + 0x408)
#define HI6402_GPIO0_IEV                   (HI6402_GPIO0_BASE + 0x40c)
#define HI6402_GPIO0_RIS                   (HI6402_GPIO0_BASE + 0x414)
#define HI6402_GPIO0_IE2                   (HI6402_GPIO0_BASE + 0x500)
#define HI6402_GPIO0_MIS2                  (HI6402_GPIO0_BASE + 0x530)

/* MAD */
#define HI6402_MAD_ANA_TIME_L              (HI6402_AUDIO_SUB_BASE + 0x0A5)
#define HI6402_MAD_PLL_TIME_L              (HI6402_AUDIO_SUB_BASE + 0x1D4)
#define HI6402_MAD_ADC_TIME_L              (HI6402_AUDIO_SUB_BASE + 0x1D5)
#define HI6402_MAD_OMIT_SAMP               (HI6402_AUDIO_SUB_BASE + 0x0A0)
#define HI6402_MAD_RMS_NUM                 (HI6402_AUDIO_SUB_BASE + 0x0A1)
#define HI6402_MAD_AUTO_ACT_NUMBER         (HI6402_AUDIO_SUB_BASE + 0x0A2)
#define HI6402_MAD_RMS_MODE                (HI6402_AUDIO_SUB_BASE + 0x0A6)
#define HI6402_MAD_SLEEP_TIME0             (HI6402_AUDIO_SUB_BASE + 0x0A7)
#define HI6402_MAD_SLEEP_TIME1             (HI6402_AUDIO_SUB_BASE + 0x0A8)
#define HI6402_MAD_SLEEP_TIME2             (HI6402_AUDIO_SUB_BASE + 0x0A9)
#define HI6402_MAD_SLEEP_TIME2_BIT             0
#define HI6402_MAD_RMS_INT_EN              (HI6402_AUDIO_SUB_BASE + 0x0A9)
#define HI6402_MAD_RMS_INT_EN_BIT              7
#define HI6402_MAD_RMS_THRE0               (HI6402_AUDIO_SUB_BASE + 0x098)
#define HI6402_MAD_RMS_THRE1               (HI6402_AUDIO_SUB_BASE + 0x099)
#define HI6402_MAD_RMS_THRE2               (HI6402_AUDIO_SUB_BASE + 0x09a)
#define HI6402_MAD_RMS_THRE3               (HI6402_AUDIO_SUB_BASE + 0x09b)
#define HI6402_MAD_RMS_TIME0               (HI6402_AUDIO_SUB_BASE + 0x09c)
#define HI6402_MAD_RMS_TIME1               (HI6402_AUDIO_SUB_BASE + 0x09d)
#define HI6402_MAD_RMS_DIFF_THRE0          (HI6402_AUDIO_SUB_BASE + 0x09e)
#define HI6402_MAD_RMS_DIFF_THRE1          (HI6402_AUDIO_SUB_BASE + 0x09f)
#define HI6402_MAD_FILTER_ID               (HI6402_AUDIO_SUB_BASE + 0x0AA)
#define HI6402_MAD_FILTER_ID_BIT               2
#define HI6402_MAD_FILTER_ID1              (HI6402_AUDIO_SUB_BASE + 0x1FC)
#define HI6402_MAD_FILTER_ID1_BIT              1
#endif/*__HI6402_DSP_REGS_H__*/
