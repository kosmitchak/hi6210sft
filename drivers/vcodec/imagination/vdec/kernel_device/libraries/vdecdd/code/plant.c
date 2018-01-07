/*!
 *****************************************************************************
 *
 * @file       plant.c
 *
 * VDECDD Plant Component
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called �GPLHEADER� included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include "img_defs.h"
#include "vdec_api.h"
#include "vdecdd_utils.h"
#include "vdecdd_int.h"
#include "vdecdd_mmu.h"
#include "core_api.h"
#include "resource.h"
#include "plant.h"
#include "lst.h"
#include "report_api.h"

#define GENC_BUFF_COUNT 4

#ifdef HAS_HEVC
#define SEQ_RES_NEEDED
#endif

/*!
******************************************************************************
 This structure contains stream configuration within the plant. This relates to
 stream specific information such as resolution, picture format and pixel format
 that are required to allocate memory for the stream resources.

 @brief  Plant Stream Configuration

******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32TBD;   //!< TDB.

} PLANT_sStrConfig;


/*!
******************************************************************************
 This structure contains the picture resource info.
 @brief  Picture Resource Info
******************************************************************************/
typedef struct
{
    IMG_UINT32         ui32PictResNum;       /*!< The number of picture resources that are allocated for this stream.                  */
    IMG_UINT32         ui32MBParamsBufSize;  /*!< The size of currently allocated MB parameters buffers (if in use). 0 otherwise.      */
#ifdef HAS_MPEG4
    IMG_UINT32         ui32DPBufSize;        /*!< Size of Data Partition MPEG4 Buffer */
#endif /* HAS_MPEG4 */
    VDEC_sPictRendInfo  sAuxPictRendInfo;    /*!< The size and structure of currently allocated auxiliary picture buffers (if in use). 0 otherwise.  */
    VDEC_sPictBufConfig sAuxPictBufConfig;   /*!< Aux Picture buffer configuration.                                                     */
#ifdef HAS_HEVC
    IMG_UINT32         ui32GencFragmentBufferSize; /*!< Size of GENC fragment buffer for HEVC */
#endif /* HAS_HEVC */

} PLANT_sPictResInfo;


/*!
******************************************************************************
 This structure contains the sequence resource info.
 @brief  Sequence Resource Info
******************************************************************************/
typedef struct
{
//#ifdef HAS_HEVC
    IMG_UINT32         ui32GencBufferSize;   /*!< Size of GEN buffers for HEVC */
//#endif /* HAS_HEVC */
} PLANT_sSeqResInfo;


typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).                            */

    VDECDD_sDdPictBuf   * psPictBuf;        // Pointer to aux picture buffer.
    VDECDD_sPictResInt  * psPictResInt;      // Pointer to internal resource which owns aux picture buffer.

} PLANT_sDetachedAuxPict;



/*!
******************************************************************************
 This structure contains the stream context.
 @brief  Plant Stream Context
******************************************************************************/
typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).                            */

    IMG_VOID *              pvUserData;            /*!< Callback user data from component.                                    */
    VDEC_sStrConfigData     sConfig;               /*!< Global stream configuration.                                          */

    IMG_HANDLE              hMmuStrHandle;         /*!<                                                                       */

    LST_T                   sPictResList;          /*!< List of active picture resources that are allocated for this stream.  */
    LST_T                   sOldPictResList;       /*!< List of picture resources that are allocated for this stream but no
                                                     longer suitable for new pictures.                                     */
#ifdef SEQ_RES_NEEDED
    LST_T                   sSeqResList;           /*!< List of active sequence resources that are allocated for this stream. */
    LST_T                   sOldSeqResList;        /*!< List of sequence resources that are allocated for this stream but no
                                                        longer suitable for new sequence(s).                                  */
#endif /* SEQ_RES_NEEDED */

    LST_T                   sPictBufList;          /*!< List of picture buffers that have been removed from active internal resources.  */

    PLANT_sPictResInfo      sPictResInfo;          /*!< Current picture resource info.                                        */
    PLANT_sSeqResInfo       sSeqResInfo;           /*!< Current sequence resource info.                                       */

    VDECDD_sDdPictBuf       sReconPictBuf;         /*!< Reconstructed picture buffer.                                         */
    VDEC_sPictSize          sCodedPictSize;        /*!< Coded picture size of last reconfiguration.                           */

} PLANT_sStreamContext;


/*!
******************************************************************************
 This structure contains the MB parameters buffer allocation info.
 @brief  MB Parameters Buffer Allocation Info
******************************************************************************/
typedef struct
{
    IMG_BOOL    bAllocMBParamBuffers;   /*!< Flag to indicate allocation of MB parameters buffers.            */
    IMG_UINT32  ui32MBParamSize;        /*!< Number of bytes required for each MB parameters data.            */
    IMG_UINT32  ui32OverallocateMbNum;  /*!< (BRN26832) Number of MBs to overallocate MB parameters buffers.  */

} PLANT_sMBParamAllocInfo;


static IMG_BOOL                bInitialised = IMG_FALSE;   /*!< Indicates whether component is initialised.  */
static VDECDD_pfnCompCallback  pfnCompCallback;            /*!< Callback from component to return output.    */
static IMG_VOID *              pvCompInitUserData;         /*!< Callback user data from component.           */
static VDECDD_sDdDevConfig     gsDevConfig;                /*!< Device configuration.                        */
static IMG_UINT32              gui32NumCores;              /*!< Number of cores on device.                   */
static LST_T                   sStreamList;                /*!< List of stream context structures.           */


static PLANT_sMBParamAllocInfo asMBParamAllocInfo[VDEC_STD_MAX - 1] =
{
    /*                AllocFlag    MBParamSize    Overalloc     */
    /* MPEG2    */  { IMG_TRUE,    0xc8,          0             },
    /* MPEG4    */  { IMG_TRUE,    0xc8,          0             },
    /* H263     */  { IMG_TRUE,    0xc8,          0             },
    /* H264     */  { IMG_TRUE,    0x80,          0             },
    /* VC1      */  { IMG_TRUE,    0x80,          (4096*2)/0x80 },
    /* AVS      */  { IMG_TRUE,    0x80,          0             },
    /* REAL     */  { IMG_TRUE,    0x80,          0             },
    /* JPEG     */  { IMG_FALSE,   0x00,          0             },
    /* VP6      */  { IMG_TRUE,    0x80,          0             },
    /* VP8      */  { IMG_TRUE,    0x80,          0             },
    /* SORENSON */  { IMG_TRUE,    0xc8,          0             },
    /* HEVC     */  { IMG_TRUE,    0x40,          0             },
};


/*!
******************************************************************************

 @Function              plant_StreamGetContext

 @Description

 This function returns the stream context structure for the given stream handle.

 @Return    PLANT_sStreamContext : This function returns a pointer to the stream
                                   context structure or IMG_NULL if not found.

******************************************************************************/
static PLANT_sStreamContext * plant_StreamGetContext(
    IMG_HANDLE  hPltStrCtx
)
{
    return (PLANT_sStreamContext *)hPltStrCtx;
}


/*!
******************************************************************************

 @Function              plant_FreePictureResource

******************************************************************************/
static IMG_RESULT plant_FreePictureResource(
    VDECDD_sPictResInt * psPicResInt
)
{
    IMG_RESULT      ui32Result;

    if (IMG_NULL != psPicResInt->psDdPictBuf)
    {
        ui32Result = MMU_FreeMem(&psPicResInt->psDdPictBuf->psPictBuf->sDdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        IMG_FREE(psPicResInt->psDdPictBuf->psPictBuf);
        IMG_FREE(psPicResInt->psDdPictBuf);
    }
    if (IMG_NULL != psPicResInt->psMBParamBuf)
    {
        ui32Result = MMU_FreeMem(&psPicResInt->psMBParamBuf->sDdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        IMG_FREE(psPicResInt->psMBParamBuf);
    }
#ifdef HAS_MPEG4
    if (IMG_NULL != psPicResInt->psDP0Buf)
    {
        ui32Result = MMU_FreeMem(&psPicResInt->psDP0Buf->sDdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        IMG_FREE(psPicResInt->psDP0Buf);
    }
    if (IMG_NULL != psPicResInt->psDP1Buf)
    {
        ui32Result = MMU_FreeMem(&psPicResInt->psDP1Buf->sDdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        IMG_FREE(psPicResInt->psDP1Buf);
    }
#endif /* HAS_MPEG4 */
#ifdef HAS_HEVC
    if (IMG_NULL != psPicResInt->psGencFragmentBuffer)
    {
        MMU_FreeMem(&psPicResInt->psGencFragmentBuffer->sDdBufInfo);
        IMG_FREE(psPicResInt->psGencFragmentBuffer);
    }
#endif /* HAS_HEVC */

#ifdef SEQ_RES_NEEDED
    RESOURCE_ItemReturn(&psPicResInt->psSeqResInt->ui32RefCount);
    psPicResInt->psSeqResInt = 0;
#ifdef HAS_HEVC
    {
        IMG_UINT32 ui32i;
        for (ui32i = 0; ui32i < GENC_BUFF_COUNT; ++ui32i)
        {
            psPicResInt->pasGencBuffers[ui32i] = 0;
        }
    }
#endif /* HAS_HEVC */
#endif /* SEQ_RES_NEEDED */

    IMG_FREE(psPicResInt);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_FreeSequenceResource

******************************************************************************/
#ifdef SEQ_RES_NEEDED
static IMG_VOID plant_FreeSequenceResource(
    VDECDD_sSeqResInt * psSeqResInt
)
{
#ifdef HAS_HEVC
    IMG_UINT32 ui32i;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    for (ui32i = 0; ui32i < GENC_BUFF_COUNT; ++ui32i)
    {
        if (IMG_NULL != psSeqResInt->pasGencBuffers[ui32i])
        {
            ui32Result = MMU_FreeMem(&psSeqResInt->pasGencBuffers[ui32i]->sDdBufInfo);
            if (IMG_SUCCESS != ui32Result)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                       "MMU_Free for GENC buffer %u failed with error %u",
                       ui32i, ui32Result);
            }
            IMG_FREE(psSeqResInt->pasGencBuffers[ui32i]);
            psSeqResInt->pasGencBuffers[ui32i] = 0;
        }
    }
#endif /* HAS_HEVC */

    IMG_FREE(psSeqResInt);
}
#endif /* SEQ_RES_NEEDED */


static IMG_RESULT
plant_ReattachPictBuf(
    PLANT_sStreamContext  * psPltStrCtx,
    VDECDD_sPictResInt    * psPictResInt
)
{
    PLANT_sDetachedAuxPict * psDetachedAuxPict;
    IMG_BOOL bFound = IMG_FALSE;

    if (LST_empty(&psPltStrCtx->sPictBufList))
    {
        // Since there are no pictures to re-attach just return.
        return IMG_SUCCESS;
    }

    // Re-attach picture buffer if it was removed.
    psDetachedAuxPict = LST_first(&psPltStrCtx->sPictBufList);
    while (psDetachedAuxPict)
    {
        if (psPictResInt == psDetachedAuxPict->psPictResInt)
        {
            // Reattach and remove from pict buf list.
            psPictResInt->psDdPictBuf = psDetachedAuxPict->psPictBuf;

            LST_remove(&psPltStrCtx->sPictBufList, psDetachedAuxPict);
            IMG_FREE(psDetachedAuxPict);
            psDetachedAuxPict = IMG_NULL;
            bFound = IMG_TRUE;
            break;
        }

        psDetachedAuxPict = LST_next(psDetachedAuxPict);
    }

    if (!bFound)
    {
        IMG_ASSERT(psPictResInt->psDdPictBuf);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_PrintBufferConfig

******************************************************************************/
static IMG_RESULT
plant_PrintBufferConfig(
    IMG_BOOL                      bNewRecon,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDEC_sPictRendInfo    * psReconPictBufInfo,
    const VDEC_sPictBufConfig   * psReconPictBufConfig,
    const VDEC_sPictRendInfo    * psAuxPictBufInfo,
    const VDEC_sPictRendInfo    * psDisplayPictBufInfo,
    const VDEC_sPictBufConfig   * psDisplayPictBufConfig
)
{
    DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");

    if (bNewRecon)
    {
        if (psAuxPictBufInfo->ui32RenderedSize)
        {
            // Aux buffer definition means that this configuration is only for recon.
            DEBUG_REPORT(REPORT_MODULE_PLANT, "Recon Buffer Configuration");
            DEBUG_REPORT(REPORT_MODULE_PLANT, "---------------------------");
        }
        else
        {
            // No aux buffer definition means that display buffer also defines recon configuration.
            DEBUG_REPORT(REPORT_MODULE_PLANT, "Display/Recon Buffer Configuration");
            DEBUG_REPORT(REPORT_MODULE_PLANT, "----------------------------------");
        }

        VDECDDUTILS_PrintBufferProperties(psOutputConfig,
                                          psReconPictBufInfo,
                                          psReconPictBufConfig);

        DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
    }

    if (!bNewRecon || psAuxPictBufInfo->ui32RenderedSize)
    {
        DEBUG_REPORT(REPORT_MODULE_PLANT, "Display Buffer Configuration");
        DEBUG_REPORT(REPORT_MODULE_PLANT, "---------------------------");

        VDECDDUTILS_PrintBufferProperties(psOutputConfig,
                                          psDisplayPictBufInfo,
                                          psDisplayPictBufConfig);

        DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              plant_StreamResourceDeprecate

******************************************************************************/
static IMG_RESULT plant_StreamResourceDeprecate(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    VDECDD_sPictResInt * psPicResInt;
    IMG_RESULT           ui32Result;

    /* Free all "old" picture resources since these should now be unused. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    while (psPicResInt)
    {
        if (psPicResInt->ui32RefCount != 0)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                "[USERSID=0x%08X] Internal resource should be unused since it has been deprecated before",
                psPltStrCtx->sConfig.ui32UserStrId);

            return IMG_ERROR_MEMORY_IN_USE;
        }

        ui32Result = plant_FreePictureResource(psPicResInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    }

    /* Move all "active" picture resources to the "old" list if they are still in use. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    while (psPicResInt)
    {
        // Instruct other blocks to stop using resource.
        ui32Result = pfnCompCallback(
            PLANT_CB_PICTURE_RESOURCE_REMOVE,
            pvCompInitUserData,
            IMG_NULL,
            psPltStrCtx->pvUserData,
            psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }


        // Re-attach picture buffer if it was removed.
        ui32Result = plant_ReattachPictBuf(psPltStrCtx, psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        /* If the active resource is not being used, free now.
           Otherwise add to the old list to be freed later. */
        if (psPicResInt->ui32RefCount == 0)
        {
            ui32Result = plant_FreePictureResource(psPicResInt);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        else
        {
            LST_add(&psPltStrCtx->sOldPictResList, psPicResInt);
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    }

    /* Reset the resource configuration. */
    VDEC_BZERO(&psPltStrCtx->sPictResInfo);

#ifdef SEQ_RES_NEEDED
    {
        VDECDD_sSeqResInt * psSeqResInt;

        /* Free all "old" sequence resources since these should now be unused. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        while (psSeqResInt)
        {
            if (psSeqResInt->ui32RefCount != 0)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "[USERSID=0x%08X] Internal sequence resource should be unused "
                    "since it has been deprecated before",
                    psPltStrCtx->sConfig.ui32UserStrId);

                return IMG_ERROR_MEMORY_IN_USE;
            }

            plant_FreeSequenceResource(psSeqResInt);
            psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        }

        /* Move all "active" sequence resources to the "old" list if they are still in use. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        while (psSeqResInt)
        {
            /* If the active resource is not being used, free now.
               Otherwise add to the old list to be freed later. */
            psSeqResInt->ui32RefCount == 0 ?
                plant_FreeSequenceResource(psSeqResInt) :
                LST_add(&psPltStrCtx->sOldSeqResList, psSeqResInt);

            psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        }

        /* Reset the resource configuration. */
        VDEC_BZERO(&psPltStrCtx->sSeqResInfo);
    }
#endif /* SEQ_RES_NEEDED */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_StreamResourceDestroy

******************************************************************************/
static IMG_RESULT plant_StreamResourceDestroy(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    VDECDD_sPictResInt * psPicResInt;
    IMG_RESULT           ui32Result;

    /* Remove any "active" picture resources allocated for this stream. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    while (psPicResInt)
    {
        // Re-attach picture buffer if it was removed.
        ui32Result = plant_ReattachPictBuf(psPltStrCtx, psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        ui32Result = plant_FreePictureResource(psPicResInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    }

    /* Remove any "old" picture resources allocated for this stream. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    while (psPicResInt)
    {
        ui32Result = plant_FreePictureResource(psPicResInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    }

    /* Reset the resource configuration. */
    VDEC_BZERO(&psPltStrCtx->sPictResInfo);

#ifdef SEQ_RES_NEEDED
    {
        VDECDD_sSeqResInt * psSeqResInt;

        /* Remove any "active" sequence resources allocated for this stream. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        while (psSeqResInt)
        {
            plant_FreeSequenceResource(psSeqResInt);
            psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        }

        /* Remove any "old" sequence resources allocated for this stream. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        while (psSeqResInt)
        {
            plant_FreeSequenceResource(psSeqResInt);
            psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        }

        /* Reset the resource configuration. */
        VDEC_BZERO(&psPltStrCtx->sSeqResInfo);
    }
#endif /* SEQ_RES_NEEDED */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_StreamDestroy

******************************************************************************/
static IMG_RESULT plant_StreamDestroy(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    IMG_RESULT ui32Result;

    ui32Result = plant_StreamResourceDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    LST_remove(&sStreamList, psPltStrCtx);

    IMG_FREE(psPltStrCtx);
    psPltStrCtx = IMG_NULL;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_AdditionalBufsGetSize

******************************************************************************/
static IMG_RESULT plant_AdditionalBufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    IMG_UINT32                 * pui32MBParamsBufSize,
    IMG_VOID                   * pvAdditionalSizes,
    IMG_VOID                   * pvAdditionalSizes2
)
{
    IMG_UINT32 ui32WidthMB;
    IMG_UINT32 ui32HeightMB;
    IMG_UINT32 ui32MBNum = 0;
    VDEC_eVidStd eVidStd = psPltStrCtx->sConfig.eVidStd;
    IMG_UINT32 ui32StdIdx = eVidStd - 1;
#ifdef HAS_MPEG4
    IMG_UINT32 * pui32DPBufSize = pvAdditionalSizes;
#endif /* HAS_MPEG4 */

    /* Reset the MB parameters buffer size. */
    *pui32MBParamsBufSize = 0;
#ifdef HAS_MPEG4
    if ((VDEC_STD_MPEG4    == eVidStd) ||
        (VDEC_STD_H263     == eVidStd) ||
        (VDEC_STD_SORENSON == eVidStd))
    {
        /* Reset DP buffer size. */
        *pui32DPBufSize = 0;
    }
#endif /* HAS_MPEG4 */

    if (asMBParamAllocInfo[ui32StdIdx].bAllocMBParamBuffers)
    {
#ifdef HAS_HEVC
        if (eVidStd == VDEC_STD_HEVC)
        {
            /* shall be == 64 (0x40)*/
            const IMG_UINT32 ui32Align = asMBParamAllocInfo[ui32StdIdx].ui32MBParamSize;
            const IMG_UINT32 ui32DpbWidth =
                (psMaxPictSize->ui32Width + ui32Align * 2 - 1) / ui32Align * 2;
            const IMG_UINT32 ui32PicHeight =
                (psMaxPictSize->ui32Height + ui32Align - 1) / ui32Align;
            const IMG_UINT32 ui32PicWidth =
                (psMaxPictSize->ui32Width + ui32Align - 1) / ui32Align;

            /* calculating for worst case: max frame size, B-frame */
            *pui32MBParamsBufSize =
                (ui32Align * 2) * ui32PicWidth * ui32PicHeight +
                ui32Align * ui32DpbWidth * ui32PicHeight;
        }
        else
        {
#endif
        /* Calculate the number of MBs needed for current video sequence settings. */
        ui32WidthMB  = VDEC_ALIGN_SIZE(psMaxPictSize->ui32Width, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION;
        ui32HeightMB = VDEC_ALIGN_SIZE(psMaxPictSize->ui32Height, 2 * VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION;
        ui32MBNum = ui32WidthMB * ui32HeightMB;
#ifdef HAS_MPEG4
        /* Calculate size of Data Partition Buffers if doing MPEG4 */
        if(VDEC_STD_MPEG4 == eVidStd)
        {
            *pui32DPBufSize = ui32MBNum * 16;
        }
#endif /* HAS_MPEG4 */

        /* Calculate the final number of MBs needed. */
        ui32MBNum += asMBParamAllocInfo[ui32StdIdx].ui32OverallocateMbNum;

        /* Calculate the MB params buffer size. */
        *pui32MBParamsBufSize = ui32MBNum * asMBParamAllocInfo[ui32StdIdx].ui32MBParamSize;
#ifdef HAS_HEVC
        }
#endif

        /* Adjust the buffer size for MSVDX. */
        VDECDDUTILS_BufMsvdxAdjustSize(pui32MBParamsBufSize);
    }

#ifdef HAS_HEVC
    if(VDEC_STD_HEVC == eVidStd)
    {
        const static IMG_UINT16
            aui16MaxSliceSegments[HEVC_LEVEL_MAJOR_NUM][HEVC_LEVEL_MINOR_NUM] =
        {
            /* level: 1.0  1.1  1.2  */
                    { 16,    0,   0, },
            /* level: 2.0  2.1  2.2  */
                    { 16,   20,   0, },
            /* level: 3.0  3.1  3.2  */
                    { 30,   40,   0, },
            /* level: 4.0  4.1  4.2  */
                    { 75,   75,   0, },
            /* level: 5.0  5.1  5.2  */
                    { 200, 200, 200, },
            /* level: 6.0  6.1  6.2  */
                    { 600, 600, 600, }
        };

        const static IMG_UINT8
            aui8MaxTileCols[HEVC_LEVEL_MAJOR_NUM][HEVC_LEVEL_MINOR_NUM] =
        {
            /* level: 1.0  1.1  1.2  */
                    {   1,   0,   0, },
            /* level: 2.0  2.1  2.2  */
                    {   1,   1,   0, },
            /* level: 3.0  3.1  3.2  */
                    {   2,   3,   0, },
            /* level: 4.0  4.1  4.2  */
                    {   5,   5,   0, },
            /* level: 5.0  5.1  5.2  */
                    {  10,  10,  10, },
            /* level: 6.0  6.1  6.2  */
                    {  20,  20,  20, }
        };

        const static IMG_UINT32 HEVC_LEVEL_IDC_MIN = 30;
        const static IMG_UINT32 HEVC_LEVEL_IDC_MAX = 186;
        const static IMG_UINT32 GENC_ALIGNMENT = 0x1000;

        const static IMG_UINT32 ui32MbSize = 16;
        const static IMG_UINT32 ui32MaxMbRowsInCtu = 4;
        const static IMG_UINT32 ui32BytesPerFragmentPointer = 16;

        const IMG_UINT32 ui32MaxTileHeightInMbs =
            psSeqHdrInfo->sMaxFrameSize.ui32Height / ui32MbSize;

        IMG_UINT8 ui8LevelMaj = psSeqHdrInfo->ui32CodecLevel / 30;
        IMG_UINT8 ui8LevelMin = (psSeqHdrInfo->ui32CodecLevel % 30) / 3;

        if (psSeqHdrInfo->ui32CodecLevel > HEVC_LEVEL_IDC_MAX
            || psSeqHdrInfo->ui32CodecLevel < HEVC_LEVEL_IDC_MIN)
        {
            ui8LevelMaj = 6;
            ui8LevelMin = 2;
        }

        /* if we are somehow able to deliver more information here (CTU size,
           number of tile columns/rows) then memory usage could be reduced */
        {
            const IMG_UINT16 ui16MaxSliceSegments =
                aui16MaxSliceSegments[ui8LevelMaj - 1][ui8LevelMin];
            const IMG_UINT8 ui8MaxTileCols =
                aui8MaxTileCols[ui8LevelMaj - 1][ui8LevelMin];

            IMG_UINT32 * pui32GencFragmentBufferSize = pvAdditionalSizes;
            IMG_UINT32 * pui32GencBufferSize = pvAdditionalSizes2;

            *pui32GencFragmentBufferSize =
                ui32BytesPerFragmentPointer
                * (psSeqHdrInfo->sMaxFrameSize.ui32Height / ui32MbSize
                   * ui8MaxTileCols
                   + ui16MaxSliceSegments - 1) * ui32MaxMbRowsInCtu;

            *pui32GencBufferSize =
                2 * 384
                * psSeqHdrInfo->sMaxFrameSize.ui32Width / ui32MbSize
                * ui32MaxTileHeightInMbs / 4;

            *pui32GencBufferSize =
                VDEC_ALIGN_SIZE(*pui32GencBufferSize, GENC_ALIGNMENT);
            *pui32GencFragmentBufferSize =
                VDEC_ALIGN_SIZE(*pui32GencFragmentBufferSize, GENC_ALIGNMENT);

            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "Sizes for GENC in HEVC: 0x%X (frag), 0x%X (x4)",
                         *pui32GencFragmentBufferSize,
                         *pui32GencBufferSize);
        }
    }
#endif

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_UseDisplayAsRecon

 @Description

 All reconstructed pictures within a closed GOP must have the same properties
 (inc. stride, no scaling, zero-rotation etc.). If the output configuration
 matches the decode properties and the display buffer is compatible with the
 reconstructed configuration display buffers can be used instead of internally
 allocated aux picture buffers. Internal resources will still be required until
 there are no references held.

 @Input     psComSeqHdrInfo : Pointer to sequence header information.

 @Input     psOutputConfig : Pointer to stream output configuration.

 @Input     psReconPictBuf : Pointer to reconstructed picture buffer.

 @Input     psDispPictBuf  : Pointer to display picture buffer.

 @Return    IMG_BOOL

******************************************************************************/
static IMG_BOOL
plant_UseDisplayAsRecon(
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psReconPictBuf,
    const VDECDD_sDdPictBuf     * psDispPictBuf
)
{
    IMG_BOOL bNoTransformationRequired = IMG_FALSE;
    IMG_BOOL bCompatibleLayout = IMG_TRUE;

    if ( IMG_FALSE == VDECDDUTILS_IsSecondaryOutputRequired( psComSeqHdrInfo, psOutputConfig ) )
    {
        bNoTransformationRequired = IMG_TRUE;
    }

    // Determine whether the layout is compatible if reconstructed picture is already defined.
    if (psReconPictBuf->sRendInfo.ui32RenderedSize != 0)
    {
        // Picture render size should be the same.
        if (VDEC_SIZE_NE(psDispPictBuf->sRendInfo.sRendPictSize, psReconPictBuf->sRendInfo.sRendPictSize))
        {
            bCompatibleLayout = IMG_FALSE;
        }

        // Picture stride should be the same for all planes.
        if (psDispPictBuf->sRendInfo.asPlaneInfo[0].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[0].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[1].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[1].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[2].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[2].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[3].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[3].ui32Stride)
        {
            bCompatibleLayout = IMG_FALSE;
        }

        // Tiling scheme should be the same
        if (psDispPictBuf->sBufConfig.eTileScheme == psReconPictBuf->sBufConfig.eTileScheme)
        {
            // Same byte interleaved setting should be used.
            // Convert to actual bools by comparing with zero.
            if ((psDispPictBuf->sBufConfig.b128ByteInterleave > 0) != (psReconPictBuf->sBufConfig.b128ByteInterleave > 0))
            {
                bCompatibleLayout = IMG_FALSE;
            }
        }
        else
        {
            bCompatibleLayout = IMG_FALSE;
        }
    }

    return bNoTransformationRequired && bCompatibleLayout;
}



/*!
******************************************************************************

 @Function              plant_PictResGetInfo

******************************************************************************/
static IMG_RESULT plant_PictResGetInfo(
    PLANT_sStreamContext        * psPltStrCtx,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo
)
{
    VDEC_sPictSize  sCodedPictSize;
    IMG_RESULT      ui32Result;

    /* Reset the picture resource info. */
    VDEC_BZERO(psPictResInfo);

    sCodedPictSize = psComSeqHdrInfo->sMaxFrameSize;

    // Determine whether the output picture buffers are suitable to double-up as reconstructed/reference.
    // It would be desirable (band-width and memory saving) to use output buffers both for reference and display.
    // It might only now be possible because the display buffers again have the same basic properties as the references.
    // For example, rotation angle may have returned to normal from perpendicular (where stride and orientation were
    // different to reference) and cannot be mixed.
    if (!plant_UseDisplayAsRecon(psComSeqHdrInfo, psOutputConfig, &psPltStrCtx->sReconPictBuf, psDispPictBuf))
    {
        IMG_BOOL bMatchDisplay = psPltStrCtx->sConfig.bBandwidthEfficient;

        if ((VDEC_STD_VC1 == psPltStrCtx->sConfig.eVidStd) && 
            psComSeqHdrInfo->bPostProcessing)
        {
            // IPGear30189: VC-1 streams with post-processing signalled at the sequence level 
            // must have internal image buffers allocated with the same properties as the display.
            // The post-processing feature may be disabled for some frames and, since the scaler
            // might be missing, their data cannot be written using the alternate output path.
            // Subsequently the recon path must be used which requires that these image buffers
            // are suitable for reference (must match references stored in internal image buffers 
            // when post-processing was enabled for previous pictures).
            bMatchDisplay = IMG_TRUE;
        }

        // Since the display pictures cannot be used for reference/reconstructed,
        // determine the auxiliary picture buffer layout.
        if (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
        {
            if (bMatchDisplay)
            {
                VDEC_sPictBufConfig sBufConfig = psDispPictBuf->sBufConfig;

                // Rotate picture back to zero degrees by swapping width and height.
                if (psOutputConfig->eRotMode == VDEC_ROTATE_90 ||
                    psOutputConfig->eRotMode == VDEC_ROTATE_270)
                {
                    IMG_UINT32 ui32Width = sBufConfig.ui32CodedWidth;
                    sBufConfig.ui32CodedWidth = sBufConfig.ui32CodedHeight;
                    sBufConfig.ui32CodedHeight = ui32Width;
                }

                // For bandwidth efficiency just use the external buffer properties
                // without any transformations (rotation/scaling etc.).
                VDECDDUTILS_ConvertBufferConfig(&psPltStrCtx->sConfig,
                                                &sBufConfig,
                                                psComSeqHdrInfo,
                                                &psPictResInfo->sAuxPictRendInfo);

                psPictResInfo->sAuxPictBufConfig = sBufConfig;
            }
            else
            {
                VDEC_sPictRendConfig    sPictRendConfig;
                VDEC_sStrOutputConfig   sAuxStrOutputConfig;

                // Reset the auxiliary output config (all transformations are turned off)
                // and apply the current bitstream settings.
                VDEC_BZERO(&sAuxStrOutputConfig);
                sAuxStrOutputConfig.sPixelInfo = psComSeqHdrInfo->sPixelInfo;

                // Reset and populate the picture render region configuration.
                VDEC_BZERO(&sPictRendConfig);
                sPictRendConfig.sCodedPictSize = sCodedPictSize;
#ifdef VDEC_TARGET_CEDARVIEW
                sPictRendConfig.bUseExtendedStrides = IMG_FALSE;
#else
                sPictRendConfig.bUseExtendedStrides = 1;
#endif
                // IPGear 29610 - VC1 AP streams
                if ((psPltStrCtx->sConfig.eVidStd == VDEC_STD_VC1) // only VC1
                    && (psComSeqHdrInfo->bPostProcessing)          // range mapping enabled.
                    && (!psOutputConfig->bForceOold)               // no oold
                    && (!psOutputConfig->bScale)                   // no scaling
                    && (psOutputConfig->eRotMode == VDEC_ROTATE_0))// no rotation.
                {
                    sPictRendConfig.sCodedPictSize.ui32Width = psDispPictBuf->sBufConfig.aui32Stride[VDEC_PLANE_VIDEO_Y];
                    sPictRendConfig.sCodedPictSize.ui32Height = sCodedPictSize.ui32Height;
                }

                // When the reconstructed picture buffer information is not yet set
                // calculate the optimal (memory usage) auxiliary layout based on
                // current bitstream properties.
                ui32Result = VDECDDUTILS_PictBufGetInfo(&psPltStrCtx->sConfig,
                                                        &sPictRendConfig,
                                                        &sAuxStrOutputConfig,
                                                        &psPictResInfo->sAuxPictRendInfo);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

                ui32Result = VDECDDUTILS_PictBufGetConfig(&psPltStrCtx->sConfig,
                                                          &sPictRendConfig,
                                                          IMG_FALSE,
                                                          &sAuxStrOutputConfig,
                                                          &psPictResInfo->sAuxPictBufConfig);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }
        }
        else
        {
            // Auxiliary picture buffers must adhere to the current reconstructed layout
            // so just take on the reconstructed picture buffer information.
            // Since the picture size, pixel format and stride must be the same there is not
            // much scope for making this buffer layout anymore memory efficient.
            psPictResInfo->sAuxPictRendInfo = psPltStrCtx->sReconPictBuf.sRendInfo;
            psPictResInfo->sAuxPictBufConfig = psPltStrCtx->sReconPictBuf.sBufConfig;
        }
    }

    /* Calculate the size if MB parameters buffers needed for current settings. */
    switch (psPltStrCtx->sConfig.eVidStd)
    {
#ifdef HAS_MPEG4
        case VDEC_STD_MPEG4:
        case VDEC_STD_H263:
        case VDEC_STD_SORENSON:
            plant_AdditionalBufsGetSize(psPltStrCtx,
                                        psComSeqHdrInfo,
                                        &sCodedPictSize,
                                        &psPictResInfo->ui32MBParamsBufSize,
                                        &psPictResInfo->ui32DPBufSize,
                                        IMG_NULL);
            break;
#endif /* HAS_MPEG4 */
#ifdef HAS_VC1
        case VDEC_STD_VC1:
            plant_AdditionalBufsGetSize(psPltStrCtx,
                                        psComSeqHdrInfo,
                                        &sCodedPictSize,
                                        &psPictResInfo->ui32MBParamsBufSize,
                                        IMG_NULL,
                                        IMG_NULL);
            break;
#endif /* HAS_VC1 */
#ifdef HAS_HEVC
        case VDEC_STD_HEVC:
            plant_AdditionalBufsGetSize(psPltStrCtx,
                                        psComSeqHdrInfo,
                                        &sCodedPictSize,
                                        &psPictResInfo->ui32MBParamsBufSize,
                                        &psPictResInfo->ui32GencFragmentBufferSize,
                                        &psSeqResInfo->ui32GencBufferSize);
            break;
#endif /* HAS_HEVC */
        default:
            plant_AdditionalBufsGetSize(psPltStrCtx,
                                        psComSeqHdrInfo,
                                        &sCodedPictSize,
                                        &psPictResInfo->ui32MBParamsBufSize,
                                        IMG_NULL,
                                        IMG_NULL);
            break;
    }

    /* If any picture resources are needed... */
    if ((psPictResInfo->sAuxPictRendInfo.ui32RenderedSize > 0) || (psPictResInfo->ui32MBParamsBufSize > 0)
#ifdef HAS_MPEG4
        || ((VDEC_STD_MPEG4 == psPltStrCtx->sConfig.eVidStd) && (psPictResInfo->ui32DPBufSize > 0))
#endif /* HAS_MPEG4 */
#ifdef HAS_VP8
        || ((VDEC_STD_VP8 == psPltStrCtx->sConfig.eVidStd) && (psPictResInfo->ui32DPBufSize > 0))
#endif /* HAS_VP8 */
#ifdef HAS_HEVC
        || IMG_TRUE /* GENC buffers are always needed */
#endif /* HAS_HEVC */
       )
    {
        IMG_UINT32 ui32MaxRefPicNum;

        /* Calculate the number of reference buffers required. */
        ui32Result = VDECDDUTILS_RefPictGetMaxNum(&psPltStrCtx->sConfig, psComSeqHdrInfo, &ui32MaxRefPicNum);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        /* Return the number of resources required:
         * the number of reference buffers plus the current picture buffer. */
        psPictResInfo->ui32PictResNum = ui32MaxRefPicNum + 1;

        /* Allow the device to be fully-loaded with resources for maximum hardware utilisation. */
        psPictResInfo->ui32PictResNum += gsDevConfig.ui32NumSlotsPerCore - 1;                       // Master core.
        psPictResInfo->ui32PictResNum += ((gui32NumCores - 1) * gsDevConfig.ui32NumSlotsPerCore);   // Slave cores.
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_IsStreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsStreamResourceSuitable(
    PLANT_sStreamContext        * psPltStrCtx,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo
)
{
    IMG_RESULT              ui32Result;
    PLANT_sPictResInfo      sAuxPictResInfo;
    PLANT_sPictResInfo    * psAuxPictResInfo;
    PLANT_sSeqResInfo       sSeqResInfo;

    /* If resource info is needed externally, just use it. Otherwise use internal structure. */
    if (IMG_NULL != psPictResInfo)
    {
        psAuxPictResInfo = psPictResInfo;
    }
    else
    {
        psAuxPictResInfo = &sAuxPictResInfo;
    }

    if (IMG_NULL == psSeqResInfo)
    {
        psSeqResInfo = &sSeqResInfo;
    }

    /* Get the resource info for current settings. */
    ui32Result = plant_PictResGetInfo(
                        psPltStrCtx,
                        psComSeqHdrInfo,
                        psOutputConfig,
                        psDispPictBuf,
                        psAuxPictResInfo,
                        psSeqResInfo);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_FALSE;
    }

    /* Check the auxiliary buffer size against the size of currently allocated auxiliary buffers. */
    if (psAuxPictResInfo->sAuxPictRendInfo.ui32RenderedSize > psPltStrCtx->sPictResInfo.sAuxPictRendInfo.ui32RenderedSize)
    {
        return IMG_FALSE;
    }

    /* Check the size against the size of currently allocated MB parameters buffers. */
    if (psAuxPictResInfo->ui32MBParamsBufSize > psPltStrCtx->sPictResInfo.ui32MBParamsBufSize)
    {
        return IMG_FALSE;
    }

#ifdef HAS_MPEG4
    if (VDEC_STD_MPEG4 == psPltStrCtx->sConfig.eVidStd)
    {
        /* Check the size against the size of currently allocated Data Partition MPEG4 buffers. */
        if (psAuxPictResInfo->ui32DPBufSize > psPltStrCtx->sPictResInfo.ui32DPBufSize)
        {
            return IMG_FALSE;
        }
    }
#endif /* HAS_MPEG4 */

#ifdef HAS_HEVC
    if (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd)
    {
        /* Check the size against the size of currently allocated GENC buffers */
        if (psSeqResInfo->ui32GencBufferSize > psPltStrCtx->sSeqResInfo.ui32GencBufferSize
            || psPictResInfo->ui32GencFragmentBufferSize > psPltStrCtx->sPictResInfo.ui32GencFragmentBufferSize)
        {
            return IMG_FALSE;
        }
    }
#endif /* HAS_MPEG4 */

    /* Check the number of picture resources required against the current number. */
    if (psAuxPictResInfo->ui32PictResNum > psPltStrCtx->sPictResInfo.ui32PictResNum)
    {
        return IMG_FALSE;
    }

    return IMG_TRUE;
}


/*!
******************************************************************************

 @Function              plant_DoResourceRealloc

******************************************************************************/
static IMG_BOOL plant_DoResourceRealloc(
    PLANT_sStreamContext *  psPltStrCtx,
    PLANT_sPictResInfo *    psPictResInfo,
    PLANT_sSeqResInfo     * psSeqResInfo
)
{
    /* If buffer sizes are sufficient and only the greater number of resources is needed... */
    if ((psPltStrCtx->sPictResInfo.ui32MBParamsBufSize >= psPictResInfo->ui32MBParamsBufSize) &&
        (psPltStrCtx->sPictResInfo.sAuxPictRendInfo.ui32RenderedSize >= psPictResInfo->sAuxPictRendInfo.ui32RenderedSize) &&
#ifdef HAS_MPEG4
        ((VDEC_STD_MPEG4 == psPltStrCtx->sConfig.eVidStd) ?
        (psPltStrCtx->sPictResInfo.ui32DPBufSize >= psPictResInfo->ui32DPBufSize) : IMG_TRUE) &&
#endif /* HAS_MPEG4 */
#ifdef HAS_HEVC
        (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd ?
         (psPltStrCtx->sPictResInfo.ui32GencFragmentBufferSize >= psPictResInfo->ui32GencFragmentBufferSize) : IMG_TRUE) &&
        (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd ?
         (psPltStrCtx->sSeqResInfo.ui32GencBufferSize >= psSeqResInfo->ui32GencBufferSize) : IMG_TRUE) &&
#endif /* HAS_HEVC */
        (psPltStrCtx->sPictResInfo.ui32PictResNum < psPictResInfo->ui32PictResNum))
    {
        /* ...full internal resource reallocation is not required. */
        return IMG_FALSE;
    }

    /* Otherwise request full internal resource reallocation. */
    return IMG_TRUE;
}



/*!
******************************************************************************

 @Function              PLANT_Initialise

 ******************************************************************************/
IMG_RESULT PLANT_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    VDECDD_sDdDevConfig     sDdDevConfig,
    IMG_UINT32              ui32NumCores
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    if (!bInitialised)
    {
        IMG_ASSERT(pfnCallback);
        IMG_ASSERT(pvInitUserData);
        pfnCompCallback = pfnCallback;
        pvCompInitUserData = pvInitUserData;

        gsDevConfig = sDdDevConfig;
        gui32NumCores = ui32NumCores;

        LST_init(&sStreamList);

        bInitialised = IMG_TRUE;
    }
    else
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant already initialised");
        ui32Result = IMG_ERROR_ALREADY_INITIALISED;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              PLANT_Deinitialise

******************************************************************************/
IMG_RESULT PLANT_Deinitialise(
    IMG_VOID
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    if (bInitialised)
    {
        // Stream lists should be empty.
        IMG_ASSERT(LST_empty(&sStreamList));

        pfnCompCallback = IMG_NULL;
        pvCompInitUserData = IMG_NULL;

        bInitialised = IMG_FALSE;
    }
    else
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              PLANT_StreamCreate

******************************************************************************/
IMG_RESULT PLANT_StreamCreate(
    VDEC_sStrConfigData *  psStrConfig,
    IMG_HANDLE             hMmuStrHandle,
    IMG_VOID *             pvStrUserData,
    IMG_HANDLE *           phPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "[USERSID=0x%08X] Plant not initialised",
            psStrConfig->ui32UserStrId);
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    VDEC_MALLOC(psPltStrCtx);
    IMG_ASSERT(psPltStrCtx);
    if(psPltStrCtx == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    // Initialise the context structure to NULL. Any non-zero
    // default values should be set at this point.
    VDEC_BZERO(psPltStrCtx);
    psPltStrCtx->sConfig = *psStrConfig;
    psPltStrCtx->pvUserData = pvStrUserData;
    psPltStrCtx->hMmuStrHandle = hMmuStrHandle;
    LST_init(&psPltStrCtx->sPictResList);
    LST_init(&psPltStrCtx->sOldPictResList);
#ifdef SEQ_RES_NEEDED
    LST_init(&psPltStrCtx->sSeqResList);
    LST_init(&psPltStrCtx->sOldSeqResList);
#endif /* SEQ_RES_NEEDED */
    LST_init(&psPltStrCtx->sPictBufList);

    LST_add(&sStreamList, psPltStrCtx);

    *phPltStrCtx = (IMG_HANDLE)psPltStrCtx;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PLANT_StreamDestroy

******************************************************************************/
IMG_RESULT PLANT_StreamDestroy(
    IMG_HANDLE  hPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    ui32Result = plant_StreamDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PLANT_StreamResourceCreate

******************************************************************************/
IMG_RESULT PLANT_StreamResourceCreate(
    IMG_HANDLE                    hPltStrCtx,
    IMG_BOOL                      bClosedGOP,
    MSVDXIO_sMemPool              sMemPool,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf
)
{
    PLANT_sStreamContext * psPltStrCtx;
    VDECDD_sPictResInt * psPictResInt = IMG_NULL;
#ifdef SEQ_RES_NEEDED
    VDECDD_sSeqResInt  * psSeqResInt = IMG_NULL;
#endif /* SEQ_RES_NEEDED */
    IMG_RESULT ui32Result = IMG_SUCCESS;
    IMG_UINT32 i, startCnt = 0;
    PLANT_sPictResInfo sPictResInfo;
    PLANT_sSeqResInfo sSeqResInfo;
    IMG_BOOL bMBParamBufAllocated = IMG_FALSE;
    IMG_BOOL bAuxPictBufAllocated = IMG_FALSE;
#ifdef HAS_MPEG4
    IMG_BOOL bDP0BufAllocated = IMG_FALSE;
    IMG_BOOL bDP1BufAllocated = IMG_FALSE;
#endif /* HAS_MPEG4 */
#ifdef HAS_HEVC
    IMG_BOOL abGencBufferAllocated[GENC_BUFF_COUNT];
    IMG_BOOL bGencFragmentBufferAllocated;
#endif /* HAS_HEVC */

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        return IMG_ERROR_NOT_INITIALISED;
    }

    /* Get the PLANT stream context. */
    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);
#ifdef SEQ_RES_NEEDED
    psSeqResInt = LST_first(&psPltStrCtx->sSeqResList);
#endif /* SEQ_RES_NEEDED */

    // Clear the reconstructed picture buffer layout if the previous references are no longer used.
    // Only under these circumstances should the bitstream resolution change.
    if (bClosedGOP)
    {
        VDEC_BZERO(&psPltStrCtx->sReconPictBuf.sRendInfo);
        VDEC_BZERO(&psPltStrCtx->sCodedPictSize);
    }
    else
    {
        if (VDEC_SIZE_NE(psPltStrCtx->sCodedPictSize, psComSeqHdrInfo->sMaxFrameSize))
        {
            IMG_ASSERT(IMG_FALSE);
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                "[USERSID=0x%08X] Coded picture size changed within the closed GOP (i.e. mismatched references)",
                psPltStrCtx->sConfig.ui32UserStrId);
        }
    }

    /* If current buffers are not suitable for specified VSH/Output config... */
    if (!plant_IsStreamResourceSuitable(hPltStrCtx, psComSeqHdrInfo, psOutputConfig, psDispPictBuf, &sPictResInfo, &sSeqResInfo))
    {
        /* If full internal resource reallocation is needed... */
        if (plant_DoResourceRealloc(psPltStrCtx, &sPictResInfo, &sSeqResInfo))
        {
            /* Mark all the active resources as deprecated and
               free-up where no longer used. */
            plant_StreamResourceDeprecate(psPltStrCtx);
        }
        else
        {
            /* Use current buffer size settings. */
            sPictResInfo.ui32MBParamsBufSize = psPltStrCtx->sPictResInfo.ui32MBParamsBufSize;
            sPictResInfo.sAuxPictRendInfo = psPltStrCtx->sPictResInfo.sAuxPictRendInfo;
            sPictResInfo.sAuxPictBufConfig = psPltStrCtx->sPictResInfo.sAuxPictBufConfig;
#ifdef HAS_MPEG4
            if (VDEC_STD_MPEG4 == psPltStrCtx->sConfig.eVidStd)
            {
                sPictResInfo.ui32DPBufSize = psPltStrCtx->sPictResInfo.ui32DPBufSize;
            }
#endif /* HAS_MPEG4 */

#ifdef HAS_HEVC
            if (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd)
            {
                sPictResInfo.ui32GencFragmentBufferSize =
                    psPltStrCtx->sPictResInfo.ui32GencFragmentBufferSize;
                sSeqResInfo.ui32GencBufferSize =
                    psPltStrCtx->sSeqResInfo.ui32GencBufferSize;
            }
#endif /* HAS_HEVC */

            /* Set start counter to only allocate the number of resources that are missing. */
            startCnt = psPltStrCtx->sPictResInfo.ui32PictResNum;
        }

        /* allocate sequence resources */
        {
#ifdef SEQ_RES_NEEDED
            VDEC_MALLOC(psSeqResInt);
            IMG_ASSERT(IMG_NULL != psSeqResInt);
            if(IMG_NULL == psSeqResInt)
            {
                goto err_out_of_memory;
            }
            VDEC_BZERO(psSeqResInt);
            LST_add(&psPltStrCtx->sSeqResList, psSeqResInt);

#ifdef HAS_HEVC
            VDEC_BZERO(&abGencBufferAllocated);

            if (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd)
            {
                IMG_UINT32 ui32I;

                /* Allocate GENC buffers */
                for (ui32I = 0; ui32I < GENC_BUFF_COUNT; ++ui32I)
                {
                    /* Allocate the GENC buffer info structure. */
                    VDEC_MALLOC(psSeqResInt->pasGencBuffers[ui32I]);
                    IMG_ASSERT(IMG_NULL != psSeqResInt->pasGencBuffers[ui32I]);
                    if(IMG_NULL == psSeqResInt->pasGencBuffers[ui32I])
                    {
                        goto err_out_of_memory;
                    }
                    VDEC_BZERO(psSeqResInt->pasGencBuffers[ui32I]);

                    /* Allocate the GENC fragment buffer. */
                    psSeqResInt->pasGencBuffers[ui32I]->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;
                    ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                                  psSeqResInt->pasGencBuffers[ui32I]->eMmuHeapId,
                                                  sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                                  sSeqResInfo.ui32GencBufferSize,
                                                  DEV_MMU_PAGE_ALIGNMENT,
                                                  &psSeqResInt->pasGencBuffers[ui32I]->sDdBufInfo);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        goto err_out_of_memory;
                    }

                    /* Mark GENC fragment buffer as allocated. */
                    abGencBufferAllocated[ui32I] = IMG_TRUE;
                }
            }
#endif /* HAS_HEVC */
#endif /* SEQ_RES_NEEDED */
        }

        /* Allocate resources for current settings. */
        for (i = startCnt; i < sPictResInfo.ui32PictResNum; i++)
        {
            /* Reset buffer allocation status. */
            bMBParamBufAllocated = IMG_FALSE;
            bAuxPictBufAllocated = IMG_FALSE;
#ifdef HAS_MPEG4
            bDP0BufAllocated = IMG_FALSE;
            bDP1BufAllocated = IMG_FALSE;
#endif /* HAS_MPEG4 */

            /* Allocate the picture resources structure. */
            VDEC_MALLOC(psPictResInt);
            IMG_ASSERT(IMG_NULL != psPictResInt);
            if(IMG_NULL == psPictResInt)
            {
                goto err_out_of_memory;
            }
            VDEC_BZERO(psPictResInt);

            /* If MB params buffers are needed... */
            if (sPictResInfo.ui32MBParamsBufSize > 0)
            {
                /* Allocate the MB parameters buffer info structure. */
                VDEC_MALLOC(psPictResInt->psMBParamBuf);
                IMG_ASSERT(IMG_NULL != psPictResInt->psMBParamBuf);
                if(IMG_NULL == psPictResInt->psMBParamBuf)
                {
                    goto err_out_of_memory;
                }
                VDEC_BZERO(psPictResInt->psMBParamBuf);

                /* Allocate the MB parameters buffer. */
                psPictResInt->psMBParamBuf->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;
                ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                              psPictResInt->psMBParamBuf->eMmuHeapId,
                                              sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                              sPictResInfo.ui32MBParamsBufSize,
                                              DEV_MMU_PAGE_ALIGNMENT,
                                              &psPictResInt->psMBParamBuf->sDdBufInfo);
                IMG_ASSERT_TESTED(IMG_SUCCESS == ui32Result);
                if (IMG_SUCCESS != ui32Result)
                {
                    goto err_out_of_memory;
                }


                /* Mark MB parameters buffer as allocated. */
                bMBParamBufAllocated = IMG_TRUE;
            }

#ifdef HAS_MPEG4
            if (VDEC_STD_MPEG4 == psPltStrCtx->sConfig.eVidStd)
            {
                /* If Data Partition buffers are needed... */
                if (sPictResInfo.ui32DPBufSize > 0)
                {
                    /* Allocate the DP0 buffer info structure. */
                    VDEC_MALLOC(psPictResInt->psDP0Buf);
                    IMG_ASSERT(IMG_NULL != psPictResInt->psDP0Buf);
                    if(IMG_NULL == psPictResInt->psDP0Buf)
                    {
                        goto err_out_of_memory;
                    }
                    VDEC_BZERO(psPictResInt->psDP0Buf);

                    /* Allocate the MB parameters buffer. */
                    psPictResInt->psDP0Buf->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;
                    ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                                  psPictResInt->psDP0Buf->eMmuHeapId,
                                                  sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                                  sPictResInfo.ui32DPBufSize,
                                                  DEV_MMU_PAGE_ALIGNMENT,
                                                  &psPictResInt->psDP0Buf->sDdBufInfo);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        goto err_out_of_memory;
                    }

                    /* Mark DP0 buffer as allocated. */
                    bDP0BufAllocated = IMG_TRUE;

                    /* Allocate the DP1 buffer info structure. */
                    VDEC_MALLOC(psPictResInt->psDP1Buf);
                    IMG_ASSERT(IMG_NULL != psPictResInt->psDP1Buf);
                    if(IMG_NULL == psPictResInt->psDP1Buf)
                    {
                        goto err_out_of_memory;
                    }
                    VDEC_BZERO(psPictResInt->psDP1Buf);

                    /* Allocate the MB parameters buffer. */
                    psPictResInt->psDP1Buf->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;
                    ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                                  psPictResInt->psDP1Buf->eMmuHeapId,
                                                  sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                                  sPictResInfo.ui32DPBufSize,
                                                  DEV_MMU_PAGE_ALIGNMENT,
                                                  &psPictResInt->psDP1Buf->sDdBufInfo);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        goto err_out_of_memory;
                    }

                    /* Mark DP1 buffer as allocated. */
                    bDP1BufAllocated = IMG_TRUE;
                }
            }
#endif /* HAS_MPEG4 */

#ifdef HAS_HEVC
            bGencFragmentBufferAllocated = IMG_FALSE;

            if (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd)
            {
                /* Allocate the GENC fragment buffer info structure. */
                VDEC_MALLOC(psPictResInt->psGencFragmentBuffer);
                IMG_ASSERT(IMG_NULL != psPictResInt->psGencFragmentBuffer);
                if(IMG_NULL == psPictResInt->psGencFragmentBuffer)
                {
                    goto err_out_of_memory;
                }
                VDEC_BZERO(psPictResInt->psGencFragmentBuffer);

                /* Allocate the GENC fragment buffer. */
                psPictResInt->psGencFragmentBuffer->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;
                ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                              psPictResInt->psGencFragmentBuffer->eMmuHeapId,
                                              sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                              sPictResInfo.ui32GencFragmentBufferSize,
                                              DEV_MMU_PAGE_ALIGNMENT,
                                              &psPictResInt->psGencFragmentBuffer->sDdBufInfo);
                IMG_ASSERT(IMG_SUCCESS == ui32Result);
                if (IMG_SUCCESS != ui32Result)
                {
                    goto err_out_of_memory;
                }

                /* Mark GENC fragment buffer as allocated. */
                bGencFragmentBufferAllocated = IMG_TRUE;
            }
#endif /* HAS_HEVC */

            /* If auxiliary picture buffers are needed... */
            if (sPictResInfo.sAuxPictRendInfo.ui32RenderedSize > 0)
            {
                /* Allocate the auxiliary picture buffer info structure. */
                VDEC_MALLOC(psPictResInt->psDdPictBuf);
                IMG_ASSERT(IMG_NULL != psPictResInt->psDdPictBuf);
                if(IMG_NULL == psPictResInt->psDdPictBuf)
                {
                    goto err_out_of_memory;
                }
                VDEC_BZERO(psPictResInt->psDdPictBuf);

                VDEC_MALLOC(psPictResInt->psDdPictBuf->psPictBuf);
                IMG_ASSERT(IMG_NULL != psPictResInt->psDdPictBuf->psPictBuf);
                if(IMG_NULL == psPictResInt->psDdPictBuf->psPictBuf)
                {
                    goto err_out_of_memory;
                }
                VDEC_BZERO(psPictResInt->psDdPictBuf->psPictBuf);

                /* Allocate the auxiliary picture buffer. */
                MMU_GetHeap(sPictResInfo.sAuxPictBufConfig.eTileScheme,
                    sPictResInfo.sAuxPictRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride,
                    &psPictResInt->psDdPictBuf->psPictBuf->eMmuHeapId);
                ui32Result = MMU_StreamMalloc(psPltStrCtx->hMmuStrHandle,
                                              psPictResInt->psDdPictBuf->psPictBuf->eMmuHeapId,
                                              sMemPool, //Secure if Secure Content and secure allocation is possible (we don't know the device is secure or not here)
                                              sPictResInfo.sAuxPictRendInfo.ui32RenderedSize,
                                              DEV_MMU_PAGE_ALIGNMENT,
                                              &psPictResInt->psDdPictBuf->psPictBuf->sDdBufInfo);
                IMG_ASSERT_TESTED(IMG_SUCCESS == ui32Result);
                if (IMG_SUCCESS != ui32Result)
                {
                    goto err_out_of_memory;
                }
                psPictResInt->psDdPictBuf->sRendInfo = sPictResInfo.sAuxPictRendInfo;
                psPictResInt->psDdPictBuf->sBufConfig = sPictResInfo.sAuxPictBufConfig;

                /* Mark auxiliary picture buffer as allocated. */
                bAuxPictBufAllocated = IMG_TRUE;
            }

            LST_add(&psPltStrCtx->sPictResList, psPictResInt);
            psPltStrCtx->sPictResInfo.ui32PictResNum++;
        }
    }

    // Set the reconstructed picture buffer information.
    {
        PLANT_sDetachedAuxPict    * psDetachedAuxPict;
        VDEC_sPictRendInfo          sRendInfo;
        VDEC_sPictBufConfig         sBufConfig;

        if (sPictResInfo.sAuxPictRendInfo.ui32RenderedSize == 0)
        {
            sRendInfo = psDispPictBuf->sRendInfo;
            sBufConfig = psDispPictBuf->sBufConfig;

            // Temporarily remove all aux picture buffers from internal resources
            // to ensure that the Decoder uses the display buffers for reference.
            psPictResInt = LST_first(&psPltStrCtx->sPictResList);
            while (psPictResInt)
            {
                if (psPictResInt->psDdPictBuf)
                {
                    VDEC_MALLOC(psDetachedAuxPict);
                    IMG_ASSERT(psDetachedAuxPict);
                    if (psDetachedAuxPict == IMG_NULL)
                    {
                        goto err_out_of_memory;
                    }

                    psDetachedAuxPict->psPictBuf = psPictResInt->psDdPictBuf;
                    psDetachedAuxPict->psPictResInt = psPictResInt;

                    LST_add(&psPltStrCtx->sPictBufList, psDetachedAuxPict);

                    // Clear the aux picture buffer pointer.
                    psPictResInt->psDdPictBuf = IMG_NULL;
                }

                psPictResInt = LST_next(psPictResInt);
            }
        }
        else
        {
            PLANT_sDetachedAuxPict * psNextDetachedAuxPict = IMG_NULL;

            sRendInfo = sPictResInfo.sAuxPictRendInfo;
            sBufConfig = sPictResInfo.sAuxPictBufConfig;

            // Ensure that all internal resources have picture buffers attached.
            // If these were previously removed, re-attach.
            psDetachedAuxPict = LST_first(&psPltStrCtx->sPictBufList);
            while (psDetachedAuxPict)
            {
                psNextDetachedAuxPict = LST_next(psDetachedAuxPict);

                psPictResInt = LST_first(&psPltStrCtx->sPictResList);
                while (psPictResInt)
                {
                    if (psPictResInt == psDetachedAuxPict->psPictResInt)
                    {
                        // Reattach and remove from pict buf list.
                        psPictResInt->psDdPictBuf = psDetachedAuxPict->psPictBuf;
                        LST_remove(&psPltStrCtx->sPictBufList, psDetachedAuxPict);
                        IMG_FREE(psDetachedAuxPict);
                        psDetachedAuxPict = IMG_NULL;
                        break;
                    }

                    psPictResInt = LST_next(psPictResInt);
                }

                IMG_ASSERT(psDetachedAuxPict == IMG_NULL);

                psDetachedAuxPict = psNextDetachedAuxPict;
            }
        }

        plant_PrintBufferConfig(
            (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
                ? IMG_TRUE : IMG_FALSE,
            psOutputConfig,
            &sRendInfo,
            &sBufConfig,
            &sPictResInfo.sAuxPictRendInfo,
            &psDispPictBuf->sRendInfo,
            &psDispPictBuf->sBufConfig);

        // Set the reconstructed buffer properties if they
        // may have been changed.
        if (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
        {
            psPltStrCtx->sReconPictBuf.sRendInfo = sRendInfo;
            psPltStrCtx->sReconPictBuf.sBufConfig = sBufConfig;
            psPltStrCtx->sCodedPictSize = psComSeqHdrInfo->sMaxFrameSize;
        }
        else
        {
            if (IMG_MEMCMP(&sRendInfo, &psPltStrCtx->sReconPictBuf.sRendInfo, sizeof(sRendInfo)))
            {
                // Reconstructed picture buffer information has changed during a closed GOP.
                IMG_ASSERT("Reconstructed picture buffer information cannot change within a GOP" == IMG_NULL);
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                        "[USERSID=0x%08X] Reconstructed picture buffer information cannot change within a GOP.",
                        psPltStrCtx->sConfig.ui32UserStrId);
            }
        }
    }

    if (sPictResInfo.sAuxPictRendInfo.ui32RenderedSize == 0)
    {
        // Preserve the old aux picture buffer info it is was not used this time.
        sPictResInfo.sAuxPictRendInfo = psPltStrCtx->sPictResInfo.sAuxPictRendInfo;
    }

    /* Store the current resource config. */
    psPltStrCtx->sPictResInfo = sPictResInfo;

    // Push all resources out of plant
    psPictResInt = LST_first(&psPltStrCtx->sPictResList);
    while (psPictResInt)
    {
        // Increment the reference count to indicate that this resource is also
        // held by plant until it is added to the Scheduler list. If the the
        // resource has not just been created it might already be in circulation.
        RESOURCE_ItemUse(&psPictResInt->ui32RefCount);

        /* attach sequence resources */
#ifdef SEQ_RES_NEEDED
        RESOURCE_ItemUse(&psSeqResInt->ui32RefCount);
        psPictResInt->psSeqResInt = psSeqResInt;
#ifdef HAS_HEVC
        if (VDEC_STD_HEVC == psPltStrCtx->sConfig.eVidStd)
        {
            IMG_UINT32 ui32i;
            for (ui32i = 0; ui32i < GENC_BUFF_COUNT; ++ui32i)
            {
                psPictResInt->pasGencBuffers[ui32i] = psSeqResInt->pasGencBuffers[ui32i];
            }
        }
#endif /* HAS_HEVC */
#endif /* SEQ_RES_NEEDED */

        ui32Result = pfnCompCallback(
            PLANT_CB_PICTURE_RESOURCE_ADD,
            pvCompInitUserData,
            IMG_NULL,
            psPltStrCtx->pvUserData,
            psPictResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        psPictResInt = LST_next(psPictResInt);
    }

    return IMG_SUCCESS;

    /* Handle out of memory errors. */
err_out_of_memory:
    /* Free resources being currently allocated. */
    if (IMG_NULL != psPictResInt)
    {
        if (IMG_NULL != psPictResInt->psDdPictBuf)
        {
            if (IMG_NULL != psPictResInt->psDdPictBuf->psPictBuf)
            {
                if (bAuxPictBufAllocated)
                {
                    MMU_FreeMem(&psPictResInt->psDdPictBuf->psPictBuf->sDdBufInfo);
                }
                IMG_FREE(psPictResInt->psDdPictBuf->psPictBuf);
            }
            IMG_FREE(psPictResInt->psDdPictBuf);
        }
        if (IMG_NULL != psPictResInt->psMBParamBuf)
        {
            if (bMBParamBufAllocated)
            {
                MMU_FreeMem(&psPictResInt->psMBParamBuf->sDdBufInfo);
            }
            IMG_FREE(psPictResInt->psMBParamBuf);
        }
#ifdef HAS_MPEG4
        if (IMG_NULL != psPictResInt->psDP0Buf)
        {
            if (bDP0BufAllocated)
            {
                MMU_FreeMem(&psPictResInt->psDP0Buf->sDdBufInfo);
            }
            IMG_FREE(psPictResInt->psDP0Buf);
        }
        if (IMG_NULL != psPictResInt->psDP1Buf)
        {
            if (bDP1BufAllocated)
            {
                MMU_FreeMem(&psPictResInt->psDP1Buf->sDdBufInfo);
            }
            IMG_FREE(psPictResInt->psDP1Buf);
        }
#endif /* HAS_MPEG4 */
#ifdef HAS_HEVC
        if (IMG_NULL != psPictResInt->psGencFragmentBuffer)
        {
            if (bGencFragmentBufferAllocated)
            {
                MMU_FreeMem(&psPictResInt->psGencFragmentBuffer->sDdBufInfo);
            }
            IMG_FREE(psPictResInt->psGencFragmentBuffer);
        }
#endif /* HAS_HEVC */

        IMG_FREE(psPictResInt);
    }
#ifdef SEQ_RES_NEEDED
    if (IMG_NULL != psSeqResInt)
    {
#ifdef HAS_HEVC
        IMG_UINT32 ui32I;
        for (ui32I = 0; ui32I < GENC_BUFF_COUNT; ++ ui32I)
        {
            if (IMG_NULL != psSeqResInt->pasGencBuffers[ui32I])
            {
                if (abGencBufferAllocated[ui32I])
                {
                    MMU_FreeMem(&psSeqResInt->pasGencBuffers[ui32I]->sDdBufInfo);
                }
                IMG_FREE(psSeqResInt->pasGencBuffers[ui32I]);
            }
        }
#endif /* HAS_HEVC */
        IMG_FREE(psSeqResInt);
    }
#endif /* SEQ_RES_NEEDED */

    /* Free all the other resources. */
    plant_StreamResourceDestroy(psPltStrCtx);

    REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
            "[USERSID=0x%08X] Plant not able to allocate stream resources due to lack of memory",
            psPltStrCtx->sConfig.ui32UserStrId);

    return IMG_ERROR_OUT_OF_MEMORY;
}


/*!
******************************************************************************

 @Function              PLANT_StreamResourceDestroy

******************************************************************************/
IMG_RESULT PLANT_StreamResourceDestroy(
    IMG_HANDLE  hPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    ui32Result = plant_StreamResourceDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}


/*!
******************************************************************************

 @Function              PLANT_IsStreamResourceSuitable

******************************************************************************/
IMG_BOOL PLANT_IsStreamResourceSuitable(
    IMG_HANDLE                      hPltStrCtx,
    const VDEC_sComSequHdrInfo    * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig,
    const VDECDD_sDdPictBuf       * psDispPictBuf
)
{
    PLANT_sStreamContext * psPltStrCtx;

    /* Check if PLANT is initialised. */
    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        return IMG_FALSE;
    }

    /* Get the PLANT stream context. */
    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    /* Check the suitability of internal resources. */
    return plant_IsStreamResourceSuitable(psPltStrCtx, psComSeqHdrInfo, psOutputConfig, psDispPictBuf, IMG_NULL, IMG_NULL);
}


