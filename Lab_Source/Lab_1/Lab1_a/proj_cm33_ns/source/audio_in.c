/*****************************************************************************
* File Name        : audio_in.c
*
* Description      : This file contains the Audio In path configuration and
*                    processing code.
*
* Related Document : See README.md
*
******************************************************************************
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
*****************************************************************************/
#include "audio_in.h"
#include "audio.h"
#include "emusbdev_audio_config.h"
#include "retarget_io_init.h"
#include "rtos.h"


/*****************************************************************************
* Macros
*****************************************************************************/
/*Macro to select STEREO or MONO mode */
#define AUDIO_DATA_INTERLEAVING      (1u)

#define LSB_MASK                     (0x0000FFFF)

/*****************************************************************************
* Global Variables
*****************************************************************************/
const cy_stc_pdm_pcm_channel_config_t pdm_pcm_channel_2_config =
{
    .sampledelay = 1,
    .wordSize = CY_PDM_PCM_WSIZE_16_BIT,
    .signExtension = true,
    .rxFifoTriggerLevel = 31,
    .fir0_enable = false,
    .fir0_decim_code = CY_PDM_PCM_CHAN_FIR0_DECIM_1,
    .fir0_scale = 0,
#if (AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_16KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_32,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_3,
    .fir1_scale = 10,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_32KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_3,
    .fir1_scale = 8,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_48KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_2,
    .fir1_scale = 5,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_22KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_4,
    .fir1_scale = 8,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_44KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_2,
    .fir1_scale = 5,
#endif
    .dc_block_disable = true,
    .dc_block_code = CY_PDM_PCM_CHAN_DCBLOCK_CODE_16,
};

const cy_stc_pdm_pcm_channel_config_t pdm_pcm_channel_3_config =
{
    .sampledelay = 5,
    .wordSize = CY_PDM_PCM_WSIZE_16_BIT,
    .signExtension = true,
    .rxFifoTriggerLevel = 31,
    .fir0_enable = false,
    .fir0_decim_code = CY_PDM_PCM_CHAN_FIR0_DECIM_1,
    .fir0_scale = 0,
#if (AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_16KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_32,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_3,
    .fir1_scale = 10,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_32KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_3,
    .fir1_scale = 8,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_48KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_2,
    .fir1_scale = 5,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_22KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_4,
    .fir1_scale = 8,
#elif(AUDIO_IN_SAMPLE_FREQ == AUDIO_SAMPLING_RATE_44KHZ)
    .cic_decim_code  = CY_PDM_PCM_CHAN_CIC_DECIM_16,
    .fir1_decim_code = CY_PDM_PCM_CHAN_FIR1_DECIM_2,
    .fir1_scale = 5,
#endif
    .dc_block_disable = true,
    .dc_block_code = CY_PDM_PCM_CHAN_DCBLOCK_CODE_16,
};

/* PCM buffer data (16-bits) */
uint16_t audio_in_pcm_buffer_ping[(MAX_AUDIO_IN_PACKET_SIZE_WORDS)];
uint16_t audio_in_pcm_buffer_pong[(MAX_AUDIO_IN_PACKET_SIZE_WORDS)];

/* Audio IN flags */
volatile bool audio_in_start_recording = false;
volatile bool audio_in_is_recording    = false;

/* Mic mute status */
U8 mic_mute;

/*****************************************************************************
* Static const data
*****************************************************************************/
const unsigned char silent_frame[MAX_AUDIO_IN_PACKET_SIZE_BYTES] = {0};

/* <-- Add this function --> */
void audio_gain_control_task(void *arg)
{
    CY_UNUSED_PARAMETER(arg);
    cy_en_pdm_pcm_gain_sel_t current_scale = CY_PDM_PCM_SEL_GAIN_5DB;
    /* Set initial gain */
    Cy_PDM_PCM_SetGain(CYBSP_PDM_HW, LEFT_CH_INDEX, current_scale);
    Cy_PDM_PCM_SetGain(CYBSP_PDM_HW, RIGHT_CH_INDEX, current_scale);
    printf("Gain: Scale Value = %d\r\n", current_scale);
    for (;;)
    {
        uint32_t num_available = 0;
        /* Check if any characters are available in UART RX FIFO (non-blocking) */
        num_available = Cy_SCB_UART_GetNumInRxFifo(CYBSP_DEBUG_UART_HW);
        if (num_available > 0)
        {
            /* Read character from UART */
            uint32_t read_value = Cy_SCB_UART_Get(CYBSP_DEBUG_UART_HW);
            if (read_value != CY_SCB_UART_RX_NO_DATA)
            {
                char received_char = (char)read_value;
                bool gain_changed = false;
                if (received_char == 'u')
                {
                    /* Increase gain */
                    if (current_scale > CY_PDM_PCM_SEL_GAIN_83DB)
                    {
                        current_scale --;
                        gain_changed = true;
                    }
                    else
                    {
                        printf("Already at maximum gain!\r\n");
                    }
                }
                else if (received_char == 'd')
                {
                    /* Decrease gain */
                    if (current_scale < CY_PDM_PCM_SEL_GAIN_NEGATIVE_103DB)
                    {
                        current_scale ++;
                        gain_changed = true;
                    }
                    else
                    {
                        printf("Already at minimum gain!\r\n");
                    }
                }
                if (gain_changed)
                {
                    /* Apply new gain to both channels */
                    Cy_PDM_PCM_SetGain(CYBSP_PDM_HW, LEFT_CH_INDEX, current_scale);
                    Cy_PDM_PCM_SetGain(CYBSP_PDM_HW, RIGHT_CH_INDEX, current_scale);
                    printf("Gain: Scale value = %d\r\n", current_scale);
                }
            }
        }
        /* Small delay to avoid busy-waiting and allow other tasks to run */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}   /* <-- End of added function --> */

/*****************************************************************************
* Function Name: audio_in_init
******************************************************************************
* Summary:
*  Initialize the PDM/PCM block and create the "Audio In Task" which will
*  process the Audio IN endpoint transactions.
*
* Parameters:
*  None
*
* Return:
*  None
*
*****************************************************************************/
void audio_in_init(void)
{
    BaseType_t rtos_task_status;

    /* Initialize PDM/PCM block */
    cy_en_pdm_pcm_status_t status = Cy_PDM_PCM_Init(CYBSP_PDM_HW, &CYBSP_PDM_config);
    
    if(CY_PDM_PCM_SUCCESS != status)
    {
        handle_app_error();
    }

    /* Initialize PDM/PCM channel 0 -Left, 1 -Right */
    /* Enable PDM channel, we will activate channel for record later */
    Cy_PDM_PCM_Channel_Enable(CYBSP_PDM_HW, LEFT_CH_INDEX);
    Cy_PDM_PCM_Channel_Enable(CYBSP_PDM_HW, RIGHT_CH_INDEX);

    Cy_PDM_PCM_Channel_Init(CYBSP_PDM_HW, &pdm_pcm_channel_2_config, (uint8_t) LEFT_CH_INDEX);
    Cy_PDM_PCM_Channel_Init(CYBSP_PDM_HW, &pdm_pcm_channel_3_config, (uint8_t) RIGHT_CH_INDEX);

    /* Create the AUDIO Write RTOS task */
    rtos_task_status = xTaskCreate(audio_in_process, "Audio In Task", AUDIO_TASK_STACK_DEPTH, NULL,
            AUDIO_WRITE_TASK_PRIORITY, &rtos_audio_in_task);
    if (pdPASS != rtos_task_status)
    {
        handle_app_error();
    }

	/** <-- Add code to create task --> **/
	/* Create the Audio Gain Control RTOS task with lower priority */
    rtos_task_status = xTaskCreate(audio_gain_control_task, "Gain Control Task", 512u, NULL, 1u, NULL);
    if (pdPASS != rtos_task_status)
    {
        handle_app_error();
    }   /** <-- End of added code to create task --> **/
}


/*****************************************************************************
* Function Name: audio_in_enable
******************************************************************************
* Summary:
*  Start a recording session.
*
* Parameters:
*  None
*
* Return:
*  None
*
*****************************************************************************/
void audio_in_enable(void)
{
    audio_in_start_recording = true;

    /* Activate recording from channel after init Activate Channel */
    Cy_PDM_PCM_Activate_Channel(CYBSP_PDM_HW, LEFT_CH_INDEX);
    Cy_PDM_PCM_Activate_Channel(CYBSP_PDM_HW, RIGHT_CH_INDEX);

    /* Turn ON the kit LED to indicate start of a recording session */
    Cy_GPIO_Write(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CYBSP_LED_STATE_ON);
}


/*****************************************************************************
* Function Name: audio_in_disable
******************************************************************************
* Summary:
*  Stop a recording session.
*
* Parameters:
*  None
*
* Return:
*  None
*
*****************************************************************************/
void audio_in_disable(void)
{
    audio_in_is_recording = false;

    Cy_PDM_PCM_DeActivate_Channel(CYBSP_PDM_HW, LEFT_CH_INDEX);
    Cy_PDM_PCM_DeActivate_Channel(CYBSP_PDM_HW, RIGHT_CH_INDEX);

    /* Turn OFF the kit LED to indicate the end of the recording session */
    Cy_GPIO_Write(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CYBSP_LED_STATE_OFF);
}


/*****************************************************************************
* Function Name: audio_in_process
******************************************************************************
* Summary:
*  Wrapper task for USBD_AUDIO_Write_Task (audio in endpoint).
*
* Parameters:
*  arg
*
* Return:
*  None
*
*****************************************************************************/
void audio_in_process(void *arg)
{
    CY_UNUSED_PARAMETER(arg);

    USBD_AUDIO_Write_Task();

    for (;;)
    {
    }
}


/*****************************************************************************
* Function Name: audio_in_endpoint_callback
******************************************************************************
* Summary:
*  Callback called in the context of USBD_AUDIO_Write_Task.
*  Handles data sent to the host (IN direction).
*
* Parameters:
*  pUserContext: User context which is passed to the callback.
*  ppNextBuffer: Buffer containing audio samples which should match the
*                configuration from microphone USBD_AUDIO_IF_CONF.
*  pNextPacketSize: Size of the next buffer.
*
* Return:
*  None
*
*****************************************************************************/
void audio_in_endpoint_callback(void *pUserContext,
                                const U8 **ppNextBuffer,
                                U32 *pNextPacketSize)
{
    static uint16_t *audio_in_pcm_buffer = NULL;

    CY_UNUSED_PARAMETER(pUserContext);

    if (audio_in_start_recording)
    {
        audio_in_start_recording = false;
        audio_in_is_recording = true;

        /* Clear Audio In buffer */
        memset(audio_in_pcm_buffer_ping, 0, (MAX_AUDIO_IN_PACKET_SIZE_BYTES));
        memset(audio_in_pcm_buffer_pong, 0, (MAX_AUDIO_IN_PACKET_SIZE_BYTES));

        audio_in_pcm_buffer = audio_in_pcm_buffer_ping;

        /* Start a transfer to the Audio IN endpoint */
        *ppNextBuffer = (uint8_t *) audio_in_pcm_buffer;
        *pNextPacketSize = MAX_AUDIO_IN_PACKET_SIZE_BYTES;
    }
    else if (audio_in_is_recording) /* Check if should keep recording */
    {
        if (audio_in_pcm_buffer == audio_in_pcm_buffer_ping)
        {
            audio_in_pcm_buffer = audio_in_pcm_buffer_pong;
        }
        else
        {
            audio_in_pcm_buffer = audio_in_pcm_buffer_ping;
        }
        
        /* Read audio data from PDM-PCM FIFO */
        for(uint8_t i=0; i < MAX_AUDIO_IN_PACKET_SIZE_WORDS; i++)
        {
            int32_t data = (int32_t) Cy_PDM_PCM_Channel_ReadFifo(CYBSP_PDM_HW, LEFT_CH_INDEX);

            #if AUDIO_DATA_INTERLEAVING
            *(audio_in_pcm_buffer + i++) = (uint16_t) (data);
            #else
                audio_data_left[l] = (int16_t) (data);
            #endif

            data = (int32_t) Cy_PDM_PCM_Channel_ReadFifo(CYBSP_PDM_HW, RIGHT_CH_INDEX);

            #if AUDIO_DATA_INTERLEAVING
            *(audio_in_pcm_buffer + i) = (uint16_t) (data);
            #else
                audio_data_right[l] = (int16_t) (data);
            #endif
        }
        if (mic_mute)
        {
            /* Send silent frames in case of mute */
            *ppNextBuffer = silent_frame;
        }
        else
        {
        /* Send captured audio samples to the Audio IN endpoint */
            *ppNextBuffer = (uint8_t *) audio_in_pcm_buffer;
        }
        *pNextPacketSize = MAX_AUDIO_IN_PACKET_SIZE_BYTES;
    }
}

/* [] END OF FILE */