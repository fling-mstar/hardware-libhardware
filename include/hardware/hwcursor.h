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
//    supplied together with third party's software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party's software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar's confidential information and you agree to keep MStar's
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
//    MStar Software in conjunction with your or your customer's product
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

#ifndef ANDROID_HWCURSOR_INTERFACE_H
#define ANDROID_HWCURSOR_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <cutils/native_handle.h>

#include <hardware/hardware.h>
#include <linux/fb.h>

__BEGIN_DECLS

#define GRALLOC_HARDWARE_HWCURSOR0 "hwcursor0"

/*****************************************************************************/


/*****************************************************************************/

#define HWCURSOR_ICON 0x01
#define HWCURSOR_POSITION 0x02
#define HWCURSOR_MATRIX 0x04
#define HWCURSOR_ALPHA 0x08
#define HWCURSOR_SHOW 0x10
#define HWCURSOR_HIDE 0x20
#define HWCURSOR_RESOLUTION_CHANGED 0x40

#define HWCURSOR_MAX_WIDTH 128
#define HWCURSOR_MAX_HEIGHT 128
#define HWCURSOR_DSTFB_NUM 2

typedef struct hwcursor_fix_info {
    int hwCursorAddr;
    int hwCursorVaddr;
    int hwCursorWidth;
    int hwCursorHeight;
    int hwCursorStride;
    float matrix[4];
    int hwCursorDstAddr[HWCURSOR_DSTFB_NUM];
    int hwCursorDstWidth;
    int hwCursorDstHeight;
    int hwCursorDstStride;
} hwcursor_fix_info;

typedef struct hwcursor_var_info {
    float positionX;
    float positionY;
    float hotSpotX;
    float hotSpotY;
    int iconWidth;
    int iconHeight;
    float matrix[4];
    float alpha;
    unsigned char visible;
    unsigned char state;
} hwcursor_var_info;

typedef struct hwcursor_device_t {
    struct hw_device_t common;

    struct hwcursor_fix_info hwCursorFinfo;
    struct hwcursor_var_info hwCursorVinfo;

    int (*hwCursorShow)(struct hwcursor_device_t* window);
    int (*hwCursorHide)(struct hwcursor_device_t* window);
    int (*hwCursorSetMatrix)(struct hwcursor_device_t* window, float dsdx, float dtdx, float dsdy, float dtdy);
    int (*hwCursorSetPosition)(struct hwcursor_device_t* window, float positionX, float positionY, float hotSpotX, float hotSpotY, int iconWidth, int iconHeight);
    int (*hwCursorSetAlpha)(struct hwcursor_device_t* window, float alpha);
    int (*hwCursorChangeIcon)(struct hwcursor_device_t* window);
    int (*hwCursorDoTransaction)(struct hwcursor_device_t* window);
    int (*hwCursorGetfinfo)(struct hwcursor_device_t* window, struct hwcursor_fix_info * hwCursorFinfo);
    int (*hwCursorResolutionChanged)(struct hwcursor_device_t* window);

} hwcursor_device_t;


/** convenience API for opening and closing a supported device */

static inline int hwcursor_open(const struct hw_module_t* module,
        struct hwcursor_device_t** device) {
    return module->methods->open(module,
            GRALLOC_HARDWARE_HWCURSOR0, (struct hw_device_t**)device);
}

static inline int hwcursor_close(struct hwcursor_device_t* device) {
    return device->common.close(&device->common);
}


__END_DECLS

#endif  // ANDROID_HWCURSOR_INTERFACE_H