//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#include <common.h>
#include <malloc.h>

#define PAGE_SIZE	 4096

typedef unsigned int volatile ulv;
typedef unsigned long int volatile ullv;

#if CONFIG_MINIUBOOT
#else
int Test_MemBandWidth_int(ulv * pSrc, ulv * pDest, unsigned int nCount)
{
	ulv *p1 = NULL;
	ulv *p2 = NULL;
	unsigned int	i;
	unsigned int	nTest;

	for (nTest = 0; nTest < 10; nTest++)
	{
		p1 = (ulv *) pSrc;
		p2 = (ulv *) pDest;

		for (i = 0; i < nCount; i++)
			*p2++ = *p1++;
	}

	return nTest;
}

int Test_MemBandWidth_long(ulv * pSrc, ulv * pDest, unsigned int nCount)
{
	ullv *p1 = NULL;
	ullv *p2 = NULL;
	unsigned int	i;
	unsigned int	nTest;

	for (nTest = 0; nTest < 10; nTest++)
	{
		p1 = (ullv *) pSrc;
		p2 = (ullv *) pDest;

		for (i = 0; i < nCount; i++)
			*p2++ = *p1++;
	}

	return nTest;
}

int Test_Memcpy(ulv * pSrc, ulv * pDest, unsigned int nCount)
{
	int nTest;
	for (nTest = 0; nTest < 10; nTest++)
		memcpy((void*)pDest, (void*)pSrc, nCount*sizeof(unsigned int));
	return nTest;
}

int Test_Memread(ulv * pSrc, unsigned int nCount)
{
	register unsigned int val;
	ulv *p1 = NULL;
	unsigned int    nTest, i;
	for (nTest = 0; nTest < 10; nTest++)
	{
		p1 = (ulv *) pSrc;
		for (i = 0; i < nCount; i++)
			val = *p1++;
	}
	return nTest;
}

int Test_Memwrite(ulv * pDest, unsigned int nCount)
{
	register unsigned int val = 0xA5A4B5B4;
	ulv *p2 = NULL;
	unsigned int    nTest, i;
	for (nTest = 0; nTest < 10; nTest++)
	{
		p2 = (ulv *) pDest;
		for (i = 0; i < nCount; i++)
			*p2++ = val;
	}
	return nTest;
}

int Test_MemBandWidthRW(ulv * pSrc, ulv * pDest, unsigned int nCount, unsigned int step_size)
{
	ulv *p1 = NULL;
	ulv *p2 = NULL;
	//unsigned int	i;
	unsigned int	nTest;
	int Count;

	for (nTest = 0; nTest < 10 * step_size; nTest++)
	{
        p1 = (ulv *) pSrc;
		p2 = (ulv *) pDest;
		Count = nCount / step_size;
        //memcpy((void*)p2, (void*)p1, nCount*4);
        while(Count--)
        {
            *p2 = *p1;
            p2 += step_size;
            p1 += step_size;
        }
	}

	return nTest;
}

int Test_MemBandWidthR(ulv * pSrc, ulv * pDest, unsigned int nCount, unsigned int step_size)
{
	ulv *p1 = NULL;
	ulv *p2 = NULL;
	//unsigned int	i;
	unsigned int	nTest;
	int Count;

	for (nTest = 0; nTest < 10 * step_size; nTest++)
	{
        p1 = (ulv *) pSrc;
		p2 = (ulv *) pDest;
		Count = nCount / step_size;
        //memcpy((void*)p2, (void*)p1, nCount*4);
        while(Count--)
        {
            *p2 = *p1;
            p1 += step_size;
        }
	}

	return nTest;
}

int Test_MemBandWidthW(ulv * pSrc, ulv * pDest, unsigned int nCount, unsigned int step_size)
{
	ulv *p1 = NULL;
	ulv *p2 = NULL;
	//unsigned int	i;
	unsigned int	nTest;
	int Count;

	for (nTest = 0; nTest < 10 * step_size; nTest++)
	{
        p1 = (ulv *) pSrc;
		p2 = (ulv *) pDest;
		Count = nCount / step_size;
        //memcpy((void*)p2, (void*)p1, nCount*4);
        while(Count--)
        {
            *p2 = *p1;
            p2 += step_size;
        }
	}

	return nTest;
}

/*Unit is 1MB*/
void MemPerformance(unsigned int uMemSize)
{
	unsigned int	nLoop = 0;
	unsigned int	nAllocBytes;
	unsigned int	nBufSize;
	unsigned int	nCount;
	unsigned int	PAGE_MASK;
	void volatile	* pBuf = NULL;
	void volatile	* pAlignedBuf = NULL;
	ulv				* pSrc;
	ulv				* pDest;
	int				nDelay;
	int				nTestCount = 0;
	int				nSize;
    ulong           pasttime;
    ulong           currtime;

	PAGE_MASK = (unsigned int) ~(PAGE_SIZE - 1);
	nBufSize	= (unsigned int) (uMemSize << 20);
	nAllocBytes = nBufSize + PAGE_SIZE;


	pBuf = (void volatile *) malloc(nAllocBytes);
	if (!pBuf)
	{
		printf(" Error :: malloc failed\n");
		return;
	}

	printf(" Allocated %d bytes at 0x%08x\n", nAllocBytes, (unsigned int) pBuf);
	if ((unsigned int) pBuf % PAGE_SIZE)
	{
		pAlignedBuf = (void volatile *) (((unsigned int) pBuf + PAGE_SIZE) & PAGE_MASK);
		printf(" Aligned at 0x%08x\n", (unsigned int) pAlignedBuf);
	}
	else
	{
		pAlignedBuf = pBuf;
	}

	nCount = (nBufSize / 2) / sizeof(unsigned int);

	pSrc = (ulv *) pAlignedBuf;
	pDest = (ulv *) ((unsigned int) pAlignedBuf + (nBufSize / 2));

	printf(" Read from : 0x%p\n", pSrc);
	printf(" Write to  : 0x%p\n", pDest);

	nSize = nCount * sizeof(unsigned int);

	printf(" Size : 0x%x\n", nSize);

	printf("\nMemory read/write test\n");
	nLoop  = 0;
	int i = 0;
    
    /*Memory performance test item 1 */
	printf("\n(1) Memory read/write test through 16-bit pointer access\n");
    pasttime = get_timer(0);
    nTestCount = Test_MemBandWidth_int(pSrc, pDest, nCount);
    currtime = get_timer(0);
    nDelay = ((currtime - pasttime)/12) / 1000;
	printf("Read/Write %3d: %d times, %8d bytes, %4d msec => %6d KB/sec\n",
        nLoop, nTestCount, nSize, nDelay, (((nSize * nTestCount) / 1024) * 1000) / nDelay);

    /*Memory performance test item 2 */
	printf("\n(2) Memory read/write test through 32-bit pointer access\n");
    pasttime = get_timer(0);
    nTestCount = Test_MemBandWidth_long(pSrc, pDest, nCount);
    currtime = get_timer(0);
    nDelay = ((currtime - pasttime)/12) / 1000;
    printf("Read/Write %3d: %d times, %8d bytes, %4d msec => %6d KB/sec\n",
        nLoop, nTestCount, nSize, nDelay, (((nSize * nTestCount) / 1024) * 1000) / nDelay);

    /*Memory performance test item 3 */
	printf("\n(3) Memory read/write test through memcpy()\n");
    pasttime = get_timer(0);
    nTestCount = Test_Memcpy(pSrc, pDest, nCount);
    currtime = get_timer(0);
    nDelay = ((currtime - pasttime)/12) / 1000;
    printf("Read/Write %3d: %d times, %8d bytes, %4d msec => %6d KB/sec\n",
        nLoop, nTestCount, nSize, nDelay, (((nSize * nTestCount) / 1024) * 1000) / nDelay);

    /*Memory performance test item 4 */
	printf("\n(4) Memory read test\n");
    pasttime = get_timer(0);
    nTestCount = Test_Memread(pSrc, nCount);
    currtime = get_timer(0);
    nDelay = ((currtime - pasttime)/12) / 1000;
    printf("Read/Write %3d: %d times, %8d bytes, %4d msec => %6d KB/sec\n",
        nLoop, nTestCount, nSize, nDelay, (((nSize * nTestCount) / 1024) * 1000) / nDelay);

    /*Memory performance test item 5 */
	printf("\n(5) Memory write test\n");
    pasttime = get_timer(0);
    nTestCount = Test_Memwrite(pDest, nCount);
    currtime = get_timer(0);
    nDelay = ((currtime - pasttime)/12) / 1000;
    printf("Write %3d: %d times, %8d bytes, %4d msec => %6d KB/sec\n",
        nLoop, nTestCount, nSize, nDelay, (((nSize * nTestCount) / 1024) * 1000) / nDelay);

    /*Memory performance test item 6 */
	printf("\n(6) Memory read/write test\n");
    for(i = 1 ; i < 513; i = i<<1)
    {
        pasttime = get_timer(0);
        nTestCount = Test_MemBandWidthRW(pSrc, pDest, nCount, i);
        currtime = get_timer(0);
        nDelay = ((currtime - pasttime)/12) / 1000;
        printf("Read/Write  %8d bytes, skip %4d bytes %4d msec => %6d KB/sec\n",
            nSize, i*4, nDelay, ((((nSize / i) * nTestCount) / 1024) * 1000) / nDelay);
    }

    /*Memory performance test item 7 */
	printf("\n(7) Memory read test\n");
    for(i = 1 ; i < 513; i = i<<1)
    {
        pasttime = get_timer(0);
        nTestCount = Test_MemBandWidthR(pSrc, pDest, nCount, i);
        currtime = get_timer(0);
        nDelay = ((currtime - pasttime)/12) / 1000;
        printf("Read  %8d bytes, skip %4d bytes %4d msec => %6d KB/sec\n",
            nSize, i*4, nDelay, ((((nSize / i) * nTestCount) / 1024) * 1000) / nDelay);
    }

    /*Memory performance test item 8 */
	printf("\n(8) Memory write test\n");
    for(i = 1 ; i < 513; i = i<<1)
    {
        pasttime = get_timer(0);
        nTestCount = Test_MemBandWidthW(pSrc, pDest, nCount, i);
        currtime = get_timer(0);
        nDelay = ((currtime - pasttime)/12) / 1000;
        printf("Write  %8d bytes, skip %4d bytes %4d msec => %6d KB/sec\n",
            nSize, i*4, nDelay, ((((nSize / i) * nTestCount) / 1024) * 1000) / nDelay);
    }

	free((void *) pBuf);
}
#endif

