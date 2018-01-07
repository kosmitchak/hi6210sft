/*******************************************************************  
* (c) Copyright 2011-2012 Discretix Technologies Ltd.              *
* This software is protected by copyright, international           *
* treaties and patents.                                            *
* Use of this Software as part of or with the Discretix CryptoCell *
* or Packet Engine products is governed by the products'           *
* commercial end user license agreement ("EULA").                  *
* It is possible that copies of this Software might be distributed *
* under some type of GNU General Public License ("GPL").           *
* Notwithstanding any such distribution under the terms of GPL,    *
* GPL does not govern the use of this Software as part of or with  *
* the Discretix CryptoCell or Packet Engine products, for which a  *
* EULA is required.                                                *
* If the product's EULA allows any copy or reproduction of this    *
* Software, then such copy or reproduction must include this       *
* Copyright Notice as well as any other notices provided           *
* thereunder.                                                      *
********************************************************************/



#ifndef _DX_PAL_MEM_H
#define _DX_PAL_MEM_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "dx_pal_types.h"
#include "dx_pal_mem_plat.h"
#include "dx_pal_malloc_plat.h"
#include "log.h"

/** 
* @brief File Description:
*        This file conatins functions for memory operations. The functions implementations
*        are generally just wrappers to different operating system calls.
*        None of the described functions will check the input parameters so the behavior 
*        of the APIs in illegal parameters case is dependent on the operating system behavior.
*
*/


/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**** ----- Memory Operations APIs ----- ****/

/** 
 * @brief This function purpose is to compare between two given buffers according to given 
 *        size. 
 *         
 *
 * @param[in] aTarget - The target buffer to compare
 * @param[in] aSource - The Source buffer to compare to
 * @param[in] aSize - Number of bytes to compare
 *
 * @return The return values will be according to operating system return values.
 */
DxInt32_t DX_PAL_MemCmp(	const void* aTarget,	
	                  	    const void* aSource,	
		                      DxUint32_t  aSize		); 

/* Definition for MemCmp */		                      
#define  DX_PAL_MemCmp    _DX_PAL_MemCmp 		                      
		                      
/** 
 * @brief This function purpose is to perform secured memory comparison between two given 
 *        buffers according to given size. The function will compare each byte till aSize 
 *        number of bytes was compared even if the bytes are different.
 *        The function should be used to avoid security timing attacks.  
 *         
 *
 * @param[in] aTarget - The target buffer to compare
 * @param[in] aSource - The Source buffer to compare to
 * @param[in] aSize - Number of bytes to compare
 *
 * @return The function will return DX_SUCCESS in case of success, else errors from 
 *         DX_PAL_Error.h will be returned.
 */
DxError_t DX_PAL_SecMemCmp(	const DxUint8_t* aTarget,	
	                  	      const DxUint8_t* aSource,	
		                        DxUint32_t  aSize		); 		                      

/** 
 * @brief This function purpose is to copy aSize bytes from source buffer to destination buffer.
 *         
 *
 * @param[in] aDestination - The destination buffer to copy bytes to
 * @param[in] aSource - The Source buffer to copy from
 * @param[in] aSize - Number of bytes to copy
 *
 * @return void
 */
void DX_PAL_MemCopy(	const void* aDestination,	
	                  	const void* aSource,	
		                  DxUint32_t  aSize		);	

/** 
 * @brief This function purpose is to copy aSize bytes from source buffer to destination buffer. 
 * This function Supports ovelapped buffers
 *         
 *
 * @param[in] aDestination - The destination buffer to copy bytes to
 * @param[in] aSource - The Source buffer to copy from
 * @param[in] aSize - Number of bytes to copy
 *
 * @return void
 */
void DX_PAL_MemMove(	const void* aDestination,	
	                  	const void* aSource,	
		                  DxUint32_t  aSize		);	

/* Definition for MemCopy */
#define DX_PAL_MemCopy    _DX_PAL_MemCopy		 
#define DX_PAL_MemMove    _DX_PAL_MemMove		 
                 

/** 
 * @brief This function purpose is to set aSize bytes in the given buffer with aChar. 
 *         
 *
 * @param[in] aTarget - The target buffer to set
 * @param[in] aChar - The char to set into aTarget
 * @param[in] aSize - Number of bytes to set
 *
 * @return void
 */
void DX_PAL_MemSet(	const void* aTarget,	
	                  const DxUint8_t aChar,	
		                DxUint32_t  aSize		);		                  

/* Definition for MemSet */
#define DX_PAL_MemSet(aTarget, aChar, aSize)   _DX_PAL_MemSet(aTarget, aChar, aSize)		                  	  		                  

/** 
 * @brief This function purpose is to set aSize bytes in the given buffer with zeroes. 
 *         
 *
 * @param[in] aTarget - The target buffer to set
 * @param[in] aChar - The char to set into aTarget
 * @param[in] aSize - Number of bytes to set
 *
 * @return void
 */
void DX_PAL_MemSetZero(	const void* aTarget,		                  
		                    DxUint32_t  aSize		);		
		                                          
#define DX_PAL_MemSetZero(aTarget, aSize)   _DX_PAL_MemSetZero(aTarget, aSize)	
	                      
/**** ----- Memory Allocation APIs ----- ****/

/** 
 * @brief This function purpose is to allocate a memory buffer according to aSize.
 *         
 * @param[in] aSize - Number of bytes to allocate
 *
 * @return The function will return a pointer to allocated buffer or NULL if allocation failed.
 */
void* DX_PAL_MemMalloc(DxUint32_t aSize);

/* Definition for MemMalloc */
#define DX_PAL_MemMalloc  _DX_PAL_MemMalloc

/** 
 * @brief This function purpose is to reallocate a memory buffer according to aNewSize.
 *        The content of the old buffer is moved to the new location
 *         
 * @param[in] aBuffer - Pointer to allocated buffer
 * @param[in] aNewSize - Number of bytes to reallocate
 *
 * @return The function will return a pointer to the newly allocated buffer or NULL if allocation failed.
 */
void* DX_PAL_MemRealloc(  void* aBuffer,
                          DxUint32_t aNewSize );

/* Definition for MemRealloc */
#define DX_PAL_MemRealloc  _DX_PAL_MemRealloc

/** 
 * @brief This function purpose is to free allocated buffer.
 *         
 * @param[in] aBuffer - A pointer to allocated buffer
 *
 * @return void
 */
void DX_PAL_MemFree(void* aBuffer);
 
/* Definition for MemFree */
#define DX_PAL_MemFree  _DX_PAL_MemFree
    
#ifdef __cplusplus
}
#endif

#endif


