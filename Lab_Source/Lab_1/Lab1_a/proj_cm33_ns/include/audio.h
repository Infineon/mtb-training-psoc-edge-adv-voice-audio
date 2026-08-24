/******************************************************************************
* File Name   : audio.h
*
* Description : This file contains the constants for USB Audio and PDM-PCM
*               configurations
*
* Note        : See README.md
*
*******************************************************************************
 * (c) 2025-2026, Infineon Technologies AG, or an affiliate of Infineon
 * Technologies AG. All rights reserved.
 * This software, associated documentation and materials ("Software") is
 * owned by Infineon Technologies AG or one of its affiliates ("Infineon")
 * and is protected by and subject to worldwide patent protection, worldwide
 * copyright laws, and international treaty provisions. Therefore, you may use
 * this Software only as provided in the license agreement accompanying the
 * software package from which you obtained this Software. If no license
 * agreement applies, then any use, reproduction, modification, translation, or
 * compilation of this Software is prohibited without the express written
 * permission of Infineon.
 *
 * Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
 * THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
 * SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
 * Infineon reserves the right to make changes to the Software without notice.
 * You are responsible for properly designing, programming, and testing the
 * functionality and safety of your intended application of the Software, as
 * well as complying with any legal requirements related to its use. Infineon
 * does not guarantee that the Software will be free from intrusion, data theft
 * or loss, or other breaches ("Security Breaches"), and Infineon shall have
 * no liability arising out of any Security Breaches. Unless otherwise
 * explicitly approved by Infineon, the Software may not be used in any
 * application where a failure of the Product or any consequences of the use
 * thereof can reasonably be expected to result in personal injury.
******************************************************************************/
#ifndef AUDIO_H
#define AUDIO_H

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
* Constants from USB Audio Descriptor
******************************************************************************/
/* Audio sampling rates supported by the application */
#define AUDIO_SAMPLING_RATE_16KHZ               (16000U)
#define AUDIO_SAMPLING_RATE_22KHZ               (22050U)
#define AUDIO_SAMPLING_RATE_32KHZ               (32000U)
#define AUDIO_SAMPLING_RATE_44KHZ               (44100U)
#define AUDIO_SAMPLING_RATE_48KHZ               (48000U)

/* USB Audio IN Endpoint configuration data */
#define AUDIO_IN_NUM_CHANNELS                   (2U)
#define AUDIO_IN_SUB_FRAME_SIZE                 (2U)   /* In bytes */
#define AUDIO_IN_BIT_RESOLUTION                 (16U)
#define AUDIO_IN_SAMPLE_FREQ                    AUDIO_SAMPLING_RATE_16KHZ  // <-- update

#define AUDIO_VOLUME_SIZE     (2U)
/**< Volume minimum value MSB */
#define AUDIO_VOLUME_MIN_MSB  (0x00U)
/**< Volume minimum value LSB */
#define AUDIO_VOLUME_MIN_LSB  (0xF1U)
/**< Volume maximum value MSB */
#define AUDIO_VOLUME_MAX_MSB  (0x00U)
/**< Volume maximum value LSB */
#define AUDIO_VOLUME_MAX_LSB  (0x00U)
/**< Volume resolution MSB */
#define AUDIO_VOLUME_RES_MSB  (0x00U)
/**< Volume resolution LSB */
#define AUDIO_VOLUME_RES_LSB  (0x01U)

/* USB device VendorID */
#define AUDIO_DEVICE_VENDOR_ID                  (0x058B)

/* USB device ProductIDs */
#if (AUDIO_SAMPLING_RATE_16KHZ == AUDIO_IN_SAMPLE_FREQ)
#define AUDIO_DEVICE_PRODUCT_ID                 (0x0285)
#elif (AUDIO_SAMPLING_RATE_22KHZ == AUDIO_IN_SAMPLE_FREQ)
#define AUDIO_DEVICE_PRODUCT_ID                 (0x0286)
#elif (AUDIO_SAMPLING_RATE_32KHZ == AUDIO_IN_SAMPLE_FREQ)
#define AUDIO_DEVICE_PRODUCT_ID                 (0x0287)
#elif (AUDIO_SAMPLING_RATE_44KHZ == AUDIO_IN_SAMPLE_FREQ)
#define AUDIO_DEVICE_PRODUCT_ID                 (0x0288)
#elif (AUDIO_SAMPLING_RATE_48KHZ == AUDIO_IN_SAMPLE_FREQ)
#define AUDIO_DEVICE_PRODUCT_ID                 (0x02A8)
#else
#error "Sample rate not supported in this code example."
#endif


/******************************************************************************
* Has to match the configured values in Microphone Configuration
* For a sample rate of 44100, 16 bits per sample, 2 channels:
* (44100 * ((16/8) * 2)) / 1000 = 176 bytes
* Additional sample size is added to make sure we can send 
* odd sized frames if necessary:
* 176 bytes + ((16/8) * 2) = 180
******************************************************************************/

/* USB IN Endpoint Audio maximum packet size (in bytes) */
/* Packet size = ( Sampling frequency * (Bit resolution / 8) * Num of channels ) / (frame duration in ms) */
#define MAX_AUDIO_IN_PACKET_SIZE_BYTES          ((((AUDIO_IN_SAMPLE_FREQ) * (((AUDIO_IN_BIT_RESOLUTION) / 8U) * (AUDIO_IN_NUM_CHANNELS))) / 1000U))

/* USB IN Endpoint Audio maximum packet size (in words) */
/* Number of Words = (Number of bytes / Audio sub-frame size) */
#define MAX_AUDIO_IN_PACKET_SIZE_WORDS          ((MAX_AUDIO_IN_PACKET_SIZE_BYTES) / (AUDIO_IN_SUB_FRAME_SIZE))

/* PDM-PCM Configuration data */
#define NUM_CHANNELS                            (2u)
#define LEFT_CH_INDEX                           (2u)
#define RIGHT_CH_INDEX                          (3u)
#define PDM_IRQ                                 pdm_0_CHANNEL_3_IRQ
#define LEFT_CH_CONFIG                          channel_2_config
#define RIGHT_CH_CONFIG                         channel_3_config

#if defined(__cplusplus)
}
#endif

#endif /* AUDIO_H */

/* [] END OF FILE */
