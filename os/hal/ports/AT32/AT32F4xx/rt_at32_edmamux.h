/*
    ChibiOS - Copyright (C) 2006..2019 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file 
 *          STM32G4xx/stm32_dmamux.h
 *          rt_at32_edmamux.h
 * @brief   STM32G4xx DMAMUX handler header.
 *
 * @addtogroup STM32G4xx_DMAMUX
 * @{
 */

#ifndef RT_AT32_EDMAMUX_H
#define RT_AT32_EDMAMUX_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    DMAMUX1 request sources
 * @{
 */
#if 0
#define STM32_DMAMUX1_REQ_GEN0      1
#define STM32_DMAMUX1_REQ_GEN1      2
#define STM32_DMAMUX1_REQ_GEN2      3
#define STM32_DMAMUX1_REQ_GEN3      4
#define STM32_DMAMUX1_ADC1          5
#define STM32_DMAMUX1_DAC1_CH1      6
#define STM32_DMAMUX1_DAC1_CH2      7
#define STM32_DMAMUX1_TIM6_UP       8
#define STM32_DMAMUX1_TIM7_UP       9
#define STM32_DMAMUX1_SPI1_RX       10
#define STM32_DMAMUX1_SPI1_TX       11
#define STM32_DMAMUX1_SPI2_RX       12
#define STM32_DMAMUX1_SPI2_TX       13
#define STM32_DMAMUX1_SPI3_RX       14
#define STM32_DMAMUX1_SPI3_TX       15
#define STM32_DMAMUX1_I2C1_RX       16
#define STM32_DMAMUX1_I2C1_TX       17
#define STM32_DMAMUX1_I2C2_RX       18
#define STM32_DMAMUX1_I2C2_TX       19
#define STM32_DMAMUX1_I2C3_RX       20
#define STM32_DMAMUX1_I2C3_TX       21
#define STM32_DMAMUX1_I2C4_RX       22
#define STM32_DMAMUX1_I2C4_TX       23
#define STM32_DMAMUX1_USART1_RX     24
#define STM32_DMAMUX1_USART1_TX     25
#define STM32_DMAMUX1_USART2_RX     26
#define STM32_DMAMUX1_USART2_TX     27
#define STM32_DMAMUX1_USART3_RX     28
#define STM32_DMAMUX1_USART3_TX     29
#define STM32_DMAMUX1_UART4_RX      30
#define STM32_DMAMUX1_UART4_TX      31
#define STM32_DMAMUX1_UART5_RX      32
#define STM32_DMAMUX1_UART5_TX      33
#define STM32_DMAMUX1_LPUART1_RX    34
#define STM32_DMAMUX1_LPUART1_TX    35
#define STM32_DMAMUX1_ADC2          36
#define STM32_DMAMUX1_ADC3          37
#define STM32_DMAMUX1_ADC4          38
#define STM32_DMAMUX1_ADC5          39
#define STM32_DMAMUX1_QUADSPI       40
#define STM32_DMAMUX1_DAC2_CH1      41
#define STM32_DMAMUX1_TIM1_CH1      42
#define STM32_DMAMUX1_TIM1_CH2      43
#define STM32_DMAMUX1_TIM1_CH3      44
#define STM32_DMAMUX1_TIM1_CH4      45
#define STM32_DMAMUX1_TIM1_UP       46
#define STM32_DMAMUX1_TIM1_TRIG     47
#define STM32_DMAMUX1_TIM1_COM      48
#define STM32_DMAMUX1_TIM8_CH1      49
#define STM32_DMAMUX1_TIM8_CH2      50
#define STM32_DMAMUX1_TIM8_CH3      51
#define STM32_DMAMUX1_TIM8_CH4      52
#define STM32_DMAMUX1_TIM8_UP       53
#define STM32_DMAMUX1_TIM8_TRIG     54
#define STM32_DMAMUX1_TIM8_COM      55
#define STM32_DMAMUX1_TIM2_CH1      56
#define STM32_DMAMUX1_TIM2_CH2      57
#define STM32_DMAMUX1_TIM2_CH3      58
#define STM32_DMAMUX1_TIM2_CH4      59
#define STM32_DMAMUX1_TIM2_UP       60
#define STM32_DMAMUX1_TIM3_CH1      61
#define STM32_DMAMUX1_TIM3_CH2      62
#define STM32_DMAMUX1_TIM3_CH3      63
#define STM32_DMAMUX1_TIM3_CH4      64
#define STM32_DMAMUX1_TIM3_UP       65
#define STM32_DMAMUX1_TIM3_TRIG     66
#define STM32_DMAMUX1_TIM4_CH1      67
#define STM32_DMAMUX1_TIM4_CH2      68
#define STM32_DMAMUX1_TIM4_CH3      69
#define STM32_DMAMUX1_TIM4_CH4      70
#define STM32_DMAMUX1_TIM4_UP       71
#define STM32_DMAMUX1_TIM5_CH1      72
#define STM32_DMAMUX1_TIM5_CH2      73
#define STM32_DMAMUX1_TIM5_CH3      74
#define STM32_DMAMUX1_TIM5_CH4      75
#define STM32_DMAMUX1_TIM5_UP       76
#define STM32_DMAMUX1_TIM5_TRIG     77
#define STM32_DMAMUX1_TIM15_CH1     78
#define STM32_DMAMUX1_TIM15_UP      79
#define STM32_DMAMUX1_TIM15_TRIG    80
#define STM32_DMAMUX1_TIM15_COM     81
#define STM32_DMAMUX1_TIM16_CH1     82
#define STM32_DMAMUX1_TIM16_UP      83
#define STM32_DMAMUX1_TIM17_CH1     84
#define STM32_DMAMUX1_TIM17_UP      85
#define STM32_DMAMUX1_TIM20_CH1     86
#define STM32_DMAMUX1_TIM20_CH2     87
#define STM32_DMAMUX1_TIM20_CH3     88
#define STM32_DMAMUX1_TIM20_CH4     89
#define STM32_DMAMUX1_TIM20_UP      90
#define STM32_DMAMUX1_AES_IN        91
#define STM32_DMAMUX1_AES_OUT       92
#define STM32_DMAMUX1_TIM20_TRIG    93
#define STM32_DMAMUX1_TIM20_COM     94
#define STM32_DMAMUX1_HRTIM_MASTER  95
#define STM32_DMAMUX1_HRTIM_TIMA    96
#define STM32_DMAMUX1_HRTIM_TIMB    97
#define STM32_DMAMUX1_HRTIM_TIMC    98
#define STM32_DMAMUX1_HRTIM_TIMD    99
#define STM32_DMAMUX1_HRTIM_TIME    100
#define STM32_DMAMUX1_HRTIM_TIMF    101
#define STM32_DMAMUX1_DAC3_CH1      102
#define STM32_DMAMUX1_DAC3_CH2      103
#define STM32_DMAMUX1_DAC4_CH1      104
#define STM32_DMAMUX1_DAC4_CH2      105
#define STM32_DMAMUX1_SPI4_RX       106
#define STM32_DMAMUX1_SPI4_TX       107
#define STM32_DMAMUX1_SAI1_A        108
#define STM32_DMAMUX1_SAI1_B        109
#define STM32_DMAMUX1_FMAC_READ     110
#define STM32_DMAMUX1_FMAC_WRITE    111
#define STM32_DMAMUX1_CORDIC_READ   112
#define STM32_DMAMUX1_CORDIC_WRITE  113
#define STM32_DMAMUX1_UCPD1_RX      114
#define STM32_DMAMUX1_UCPD1_TX      115
#else


#endif
/** @} */

/**
  * @brief edmamux flag
  */
#define EDMAMUX_SYNC_OV1_FLAG            ((uint32_t)0x00000001) /*!< edmamux stream1 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV2_FLAG            ((uint32_t)0x00000002) /*!< edmamux stream2 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV3_FLAG            ((uint32_t)0x00000004) /*!< edmamux stream3 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV4_FLAG            ((uint32_t)0x00000008) /*!< edmamux stream4 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV5_FLAG            ((uint32_t)0x00000010) /*!< edmamux stream5 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV6_FLAG            ((uint32_t)0x00000020) /*!< edmamux stream6 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV7_FLAG            ((uint32_t)0x00000040) /*!< edmamux stream7 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV8_FLAG            ((uint32_t)0x00000080) /*!< edmamux stream8 synchronization overrun event flag */

#define EDMAMUX_GEN_TRIG_OV1_FLAG        ((uint32_t)0x00000001) /*!< edmamux generator channel1 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV2_FLAG        ((uint32_t)0x00000002) /*!< edmamux generator channel2 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV3_FLAG        ((uint32_t)0x00000004) /*!< edmamux generator channel3 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV4_FLAG        ((uint32_t)0x00000008) /*!< edmamux generator channel4 overrun event flag */
/**
  * @}
  */

/**
  * @brief edmamux request id select type
  */
typedef enum {
  EDMAMUX_DMAREQ_ID_REQ_G1               = 0x01, /*!< edmamux channel request inputs resources: generator channel1 */
  EDMAMUX_DMAREQ_ID_REQ_G2               = 0x02, /*!< edmamux channel request inputs resources: generator channel2 */
  EDMAMUX_DMAREQ_ID_REQ_G3               = 0x03, /*!< edmamux channel request inputs resources: generator channel3 */
  EDMAMUX_DMAREQ_ID_REQ_G4               = 0x04, /*!< edmamux channel request inputs resources: generator channel4 */
  EDMAMUX_DMAREQ_ID_ADC1                 = 0x05, /*!< edmamux channel request inputs resources: adc1 */
  EDMAMUX_DMAREQ_ID_ADC2                 = 0x24, /*!< edmamux channel request inputs resources: adc2 */
  EDMAMUX_DMAREQ_ID_ADC3                 = 0x25, /*!< edmamux channel request inputs resources: adc3 */
  EDMAMUX_DMAREQ_ID_DAC1                 = 0x06, /*!< edmamux channel request inputs resources: dac1 */
  EDMAMUX_DMAREQ_ID_DAC2                 = 0x29, /*!< edmamux channel request inputs resources: dac2 */
  EDMAMUX_DMAREQ_ID_TMR6_OVERFLOW        = 0x08, /*!< edmamux channel request inputs resources: timer6 overflow */
  EDMAMUX_DMAREQ_ID_TMR7_OVERFLOW        = 0x09, /*!< edmamux channel request inputs resources: timer7 overflow */
  EDMAMUX_DMAREQ_ID_SPI1_RX              = 0x0A, /*!< edmamux channel request inputs resources: spi1 rx */
  EDMAMUX_DMAREQ_ID_SPI1_TX              = 0x0B, /*!< edmamux channel request inputs resources: spi1 tx */
  EDMAMUX_DMAREQ_ID_SPI2_RX              = 0x0C, /*!< edmamux channel request inputs resources: spi2 rx */
  EDMAMUX_DMAREQ_ID_SPI2_TX              = 0x0D, /*!< edmamux channel request inputs resources: spi2 tx */
  EDMAMUX_DMAREQ_ID_SPI3_RX              = 0x0E, /*!< edmamux channel request inputs resources: spi3 rx */
  EDMAMUX_DMAREQ_ID_SPI3_TX              = 0x0F, /*!< edmamux channel request inputs resources: spi3 tx */
  EDMAMUX_DMAREQ_ID_SPI4_RX              = 0x6A, /*!< edmamux channel request inputs resources: spi4 rx */
  EDMAMUX_DMAREQ_ID_SPI4_TX              = 0x6B, /*!< edmamux channel request inputs resources: spi4 tx */
  EDMAMUX_DMAREQ_ID_I2S2_EXT_RX          = 0x6E, /*!< edmamux channel request inputs resources: i2s2_ext_rx */
  EDMAMUX_DMAREQ_ID_I2S2_EXT_TX          = 0x6F, /*!< edmamux channel request inputs resources: i2s2_ext_tx */
  EDMAMUX_DMAREQ_ID_I2S3_EXT_RX          = 0x70, /*!< edmamux channel request inputs resources: i2s3_ext_rx */
  EDMAMUX_DMAREQ_ID_I2S3_EXT_TX          = 0x71, /*!< edmamux channel request inputs resources: i2s3_ext_tx */
  EDMAMUX_DMAREQ_ID_I2C1_RX              = 0x10, /*!< edmamux channel request inputs resources: i2c1_rx */
  EDMAMUX_DMAREQ_ID_I2C1_TX              = 0x11, /*!< edmamux channel request inputs resources: i2c1_tx */
  EDMAMUX_DMAREQ_ID_I2C2_RX              = 0x12, /*!< edmamux channel request inputs resources: i2c2_rx */
  EDMAMUX_DMAREQ_ID_I2C2_TX              = 0x13, /*!< edmamux channel request inputs resources: i2c2_tx */
  EDMAMUX_DMAREQ_ID_I2C3_RX              = 0x14, /*!< edmamux channel request inputs resources: i2c3_rx */
  EDMAMUX_DMAREQ_ID_I2C3_TX              = 0x15, /*!< edmamux channel request inputs resources: i2c3_tx */
  EDMAMUX_DMAREQ_ID_USART1_RX            = 0x18, /*!< edmamux channel request inputs resources: usart1_rx */
  EDMAMUX_DMAREQ_ID_USART1_TX            = 0x19, /*!< edmamux channel request inputs resources: usart1_tx */
  EDMAMUX_DMAREQ_ID_USART2_RX            = 0x1A, /*!< edmamux channel request inputs resources: usart2_rx */
  EDMAMUX_DMAREQ_ID_USART2_TX            = 0x1B, /*!< edmamux channel request inputs resources: usart2_tx */
  EDMAMUX_DMAREQ_ID_USART3_RX            = 0x1C, /*!< edmamux channel request inputs resources: usart3_rx */
  EDMAMUX_DMAREQ_ID_USART3_TX            = 0x1D, /*!< edmamux channel request inputs resources: usart3_tx */
  EDMAMUX_DMAREQ_ID_UART4_RX             = 0x1E, /*!< edmamux channel request inputs resources: uart4_rx */
  EDMAMUX_DMAREQ_ID_UART4_TX             = 0x1F, /*!< edmamux channel request inputs resources: uart4_tx */
  EDMAMUX_DMAREQ_ID_UART5_RX             = 0x20, /*!< edmamux channel request inputs resources: uart5_rx */
  EDMAMUX_DMAREQ_ID_UART5_TX             = 0x21, /*!< edmamux channel request inputs resources: uart5_tx */
  EDMAMUX_DMAREQ_ID_USART6_RX            = 0x72, /*!< edmamux channel request inputs resources: usart6_rx */
  EDMAMUX_DMAREQ_ID_USART6_TX            = 0x73, /*!< edmamux channel request inputs resources: usart6_tx */
  EDMAMUX_DMAREQ_ID_UART7_RX             = 0x74, /*!< edmamux channel request inputs resources: uart7_rx */
  EDMAMUX_DMAREQ_ID_UART7_TX             = 0x75, /*!< edmamux channel request inputs resources: uart7_tx */
  EDMAMUX_DMAREQ_ID_UART8_RX             = 0x76, /*!< edmamux channel request inputs resources: uart8_rx */
  EDMAMUX_DMAREQ_ID_UART8_TX             = 0x77, /*!< edmamux channel request inputs resources: uart8_tx */
  EDMAMUX_DMAREQ_ID_SDIO1                = 0x27, /*!< edmamux channel request inputs resources: sdio1 */
  EDMAMUX_DMAREQ_ID_SDIO2                = 0x67, /*!< edmamux channel request inputs resources: sdio2 */
  EDMAMUX_DMAREQ_ID_QSPI1                = 0x28, /*!< edmamux channel request inputs resources: qspi1 */
  EDMAMUX_DMAREQ_ID_QSPI2                = 0x68, /*!< edmamux channel request inputs resources: qspi2 */
  EDMAMUX_DMAREQ_ID_TMR1_CH1             = 0x2A, /*!< edmamux channel request inputs resources: timer1 ch1 */
  EDMAMUX_DMAREQ_ID_TMR1_CH2             = 0x2B, /*!< edmamux channel request inputs resources: timer1 ch2 */
  EDMAMUX_DMAREQ_ID_TMR1_CH3             = 0x2C, /*!< edmamux channel request inputs resources: timer1 ch3 */
  EDMAMUX_DMAREQ_ID_TMR1_CH4             = 0x2D, /*!< edmamux channel request inputs resources: timer1 ch4 */
  EDMAMUX_DMAREQ_ID_TMR1_OVERFLOW        = 0x2E, /*!< edmamux channel request inputs resources: timer1 overflow */
  EDMAMUX_DMAREQ_ID_TMR1_TRIG            = 0x2F, /*!< edmamux channel request inputs resources: timer1 trigger */
  EDMAMUX_DMAREQ_ID_TMR1_HALL            = 0x30, /*!< edmamux channel request inputs resources: timer1 hall */
  EDMAMUX_DMAREQ_ID_TMR8_CH1             = 0x31, /*!< edmamux channel request inputs resources: timer8 ch1 */
  EDMAMUX_DMAREQ_ID_TMR8_CH2             = 0x32, /*!< edmamux channel request inputs resources: timer8 ch2 */
  EDMAMUX_DMAREQ_ID_TMR8_CH3             = 0x33, /*!< edmamux channel request inputs resources: timer8 ch3 */
  EDMAMUX_DMAREQ_ID_TMR8_CH4             = 0x34, /*!< edmamux channel request inputs resources: timer8 ch4 */
  EDMAMUX_DMAREQ_ID_TMR8_OVERFLOW        = 0x35, /*!< edmamux channel request inputs resources: timer8 overflow */
  EDMAMUX_DMAREQ_ID_TMR8_TRIG            = 0x36, /*!< edmamux channel request inputs resources: timer8 trigger */
  EDMAMUX_DMAREQ_ID_TMR8_HALL            = 0x37, /*!< edmamux channel request inputs resources: timer8 hall */
  EDMAMUX_DMAREQ_ID_TMR2_CH1             = 0x38, /*!< edmamux channel request inputs resources: timer2 ch1 */
  EDMAMUX_DMAREQ_ID_TMR2_CH2             = 0x39, /*!< edmamux channel request inputs resources: timer2 ch2 */
  EDMAMUX_DMAREQ_ID_TMR2_CH3             = 0x3A, /*!< edmamux channel request inputs resources: timer2 ch3 */
  EDMAMUX_DMAREQ_ID_TMR2_CH4             = 0x3B, /*!< edmamux channel request inputs resources: timer2 ch4 */
  EDMAMUX_DMAREQ_ID_TMR2_OVERFLOW        = 0x3C, /*!< edmamux channel request inputs resources: timer2 overflow */
  EDMAMUX_DMAREQ_ID_TMR2_TRIG            = 0x7E, /*!< edmamux channel request inputs resources: timer2 trigger */
  EDMAMUX_DMAREQ_ID_TMR3_CH1             = 0x3D, /*!< edmamux channel request inputs resources: timer3 ch1 */
  EDMAMUX_DMAREQ_ID_TMR3_CH2             = 0x3E, /*!< edmamux channel request inputs resources: timer3 ch2 */
  EDMAMUX_DMAREQ_ID_TMR3_CH3             = 0x3F, /*!< edmamux channel request inputs resources: timer3 ch3 */
  EDMAMUX_DMAREQ_ID_TMR3_CH4             = 0x40, /*!< edmamux channel request inputs resources: timer3 ch4 */
  EDMAMUX_DMAREQ_ID_TMR3_OVERFLOW        = 0x41, /*!< edmamux channel request inputs resources: timer3 overflow */
  EDMAMUX_DMAREQ_ID_TMR3_TRIG            = 0x42, /*!< edmamux channel request inputs resources: timer3 trigger */
  EDMAMUX_DMAREQ_ID_TMR4_CH1             = 0x43, /*!< edmamux channel request inputs resources: timer4 ch1 */
  EDMAMUX_DMAREQ_ID_TMR4_CH2             = 0x44, /*!< edmamux channel request inputs resources: timer4 ch2 */
  EDMAMUX_DMAREQ_ID_TMR4_CH3             = 0x45, /*!< edmamux channel request inputs resources: timer4 ch3 */
  EDMAMUX_DMAREQ_ID_TMR4_CH4             = 0x46, /*!< edmamux channel request inputs resources: timer4 ch4 */
  EDMAMUX_DMAREQ_ID_TMR4_OVERFLOW        = 0x47, /*!< edmamux channel request inputs resources: timer4 overflow */
  EDMAMUX_DMAREQ_ID_TMR4_TRIG            = 0x7F, /*!< edmamux channel request inputs resources: timer4 trigger */
  EDMAMUX_DMAREQ_ID_TMR5_CH1             = 0x48, /*!< edmamux channel request inputs resources: timer5 ch1 */
  EDMAMUX_DMAREQ_ID_TMR5_CH2             = 0x49, /*!< edmamux channel request inputs resources: timer5 ch2 */
  EDMAMUX_DMAREQ_ID_TMR5_CH3             = 0x4A, /*!< edmamux channel request inputs resources: timer5 ch3 */
  EDMAMUX_DMAREQ_ID_TMR5_CH4             = 0x4B, /*!< edmamux channel request inputs resources: timer5 ch4 */
  EDMAMUX_DMAREQ_ID_TMR5_OVERFLOW        = 0x4C, /*!< edmamux channel request inputs resources: timer5 overflow */
  EDMAMUX_DMAREQ_ID_TMR5_TRIG            = 0x4D, /*!< edmamux channel request inputs resources: timer5 trigger */
  EDMAMUX_DMAREQ_ID_TMR20_CH1            = 0x56, /*!< edmamux channel request inputs resources: timer20 ch1 */
  EDMAMUX_DMAREQ_ID_TMR20_CH2            = 0x57, /*!< edmamux channel request inputs resources: timer20 ch2 */
  EDMAMUX_DMAREQ_ID_TMR20_CH3            = 0x58, /*!< edmamux channel request inputs resources: timer20 ch3 */
  EDMAMUX_DMAREQ_ID_TMR20_CH4            = 0x59, /*!< edmamux channel request inputs resources: timer20 ch4 */
  EDMAMUX_DMAREQ_ID_TMR20_OVERFLOW       = 0x5A, /*!< edmamux channel request inputs resources: timer20 overflow */
  EDMAMUX_DMAREQ_ID_TMR20_TRIG           = 0x5D, /*!< edmamux channel request inputs resources: timer20 trigger */
  EDMAMUX_DMAREQ_ID_TMR20_HALL           = 0x5E, /*!< edmamux channel request inputs resources: timer20 hall */
  EDMAMUX_DMAREQ_ID_DVP                  = 0x69  /*!< edmamux channel request inputs resources: dvp */
} edmamux_requst_id_sel_type;

/**
  * @brief dmamux sync id select type
  */
typedef enum {
  EDMAMUX_SYNC_ID_EXINT0                 = 0x00, /*!< edmamux channel synchronization inputs resources: exint line0 */
  EDMAMUX_SYNC_ID_EXINT1                 = 0x01, /*!< edmamux channel synchronization inputs resources: exint line1 */
  EDMAMUX_SYNC_ID_EXINT2                 = 0x02, /*!< edmamux channel synchronization inputs resources: exint line2 */
  EDMAMUX_SYNC_ID_EXINT3                 = 0x03, /*!< edmamux channel synchronization inputs resources: exint line3 */
  EDMAMUX_SYNC_ID_EXINT4                 = 0x04, /*!< edmamux channel synchronization inputs resources: exint line4 */
  EDMAMUX_SYNC_ID_EXINT5                 = 0x05, /*!< edmamux channel synchronization inputs resources: exint line5 */
  EDMAMUX_SYNC_ID_EXINT6                 = 0x06, /*!< edmamux channel synchronization inputs resources: exint line6 */
  EDMAMUX_SYNC_ID_EXINT7                 = 0x07, /*!< edmamux channel synchronization inputs resources: exint line7 */
  EDMAMUX_SYNC_ID_EXINT8                 = 0x08, /*!< edmamux channel synchronization inputs resources: exint line8 */
  EDMAMUX_SYNC_ID_EXINT9                 = 0x09, /*!< edmamux channel synchronization inputs resources: exint line9 */
  EDMAMUX_SYNC_ID_EXINT10                = 0x0A, /*!< edmamux channel synchronization inputs resources: exint line10 */
  EDMAMUX_SYNC_ID_EXINT11                = 0x0B, /*!< edmamux channel synchronization inputs resources: exint line11 */
  EDMAMUX_SYNC_ID_EXINT12                = 0x0C, /*!< edmamux channel synchronization inputs resources: exint line12 */
  EDMAMUX_SYNC_ID_EXINT13                = 0x0D, /*!< edmamux channel synchronization inputs resources: exint line13 */
  EDMAMUX_SYNC_ID_EXINT14                = 0x0E, /*!< edmamux channel synchronization inputs resources: exint line14 */
  EDMAMUX_SYNC_ID_EXINT15                = 0x0F, /*!< edmamux channel synchronization inputs resources: exint line15 */
  EDMAMUX_SYNC_ID_DMAMUX_CH1_EVT         = 0x10, /*!< edmamux channel synchronization inputs resources: dmamux channel1 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH2_EVT         = 0x11, /*!< edmamux channel synchronization inputs resources: dmamux channel2 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH3_EVT         = 0x12, /*!< edmamux channel synchronization inputs resources: dmamux channel3 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH4_EVT         = 0x13, /*!< edmamux channel synchronization inputs resources: dmamux channel4 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH5_EVT         = 0x14, /*!< edmamux channel synchronization inputs resources: dmamux channel5 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH6_EVT         = 0x15, /*!< edmamux channel synchronization inputs resources: dmamux channel6 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH7_EVT         = 0x16, /*!< edmamux channel synchronization inputs resources: dmamux channel7 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH8_EVT         = 0x17  /*!< edmamux channel synchronization inputs resources: dmamux channel8 event */
} edmamux_sync_id_sel_type;

/**
  * @brief dmamux sync polarity type
  */
typedef enum {
  EDMAMUX_SYNC_POLARITY_DISABLE          = 0x00, /*!< edmamux channel synchronization inputs resources polarity default value */
  EDMAMUX_SYNC_POLARITY_RISING           = 0x01, /*!< edmamux channel synchronization inputs resources polarity: rising */
  EDMAMUX_SYNC_POLARITY_FALLING          = 0x02, /*!< edmamux channel synchronization inputs resources polarity: falling */
  EDMAMUX_SYNC_POLARITY_RISING_FALLING   = 0x03  /*!< edmamux channel synchronization inputs resources polarity: rising_falling */
} edmamux_sync_pol_type;

/**
  * @brief dmamux generator id select type
  */
typedef enum {
  EDMAMUX_GEN_ID_EXINT0                  = 0x00, /*!< edmamux generator channel inputs resources: exint line0 */
  EDMAMUX_GEN_ID_EXINT1                  = 0x01, /*!< edmamux generator channel inputs resources: exint line1 */
  EDMAMUX_GEN_ID_EXINT2                  = 0x02, /*!< edmamux generator channel inputs resources: exint line2 */
  EDMAMUX_GEN_ID_EXINT3                  = 0x03, /*!< edmamux generator channel inputs resources: exint line3 */
  EDMAMUX_GEN_ID_EXINT4                  = 0x04, /*!< edmamux generator channel inputs resources: exint line4 */
  EDMAMUX_GEN_ID_EXINT5                  = 0x05, /*!< edmamux generator channel inputs resources: exint line5 */
  EDMAMUX_GEN_ID_EXINT6                  = 0x06, /*!< edmamux generator channel inputs resources: exint line6 */
  EDMAMUX_GEN_ID_EXINT7                  = 0x07, /*!< edmamux generator channel inputs resources: exint line7 */
  EDMAMUX_GEN_ID_EXINT8                  = 0x08, /*!< edmamux generator channel inputs resources: exint line8 */
  EDMAMUX_GEN_ID_EXINT9                  = 0x09, /*!< edmamux generator channel inputs resources: exint line9 */
  EDMAMUX_GEN_ID_EXINT10                 = 0x0A, /*!< edmamux generator channel inputs resources: exint line10 */
  EDMAMUX_GEN_ID_EXINT11                 = 0x0B, /*!< edmamux generator channel inputs resources: exint line11 */
  EDMAMUX_GEN_ID_EXINT12                 = 0x0C, /*!< edmamux generator channel inputs resources: exint line12 */
  EDMAMUX_GEN_ID_EXINT13                 = 0x0D, /*!< edmamux generator channel inputs resources: exint line13 */
  EDMAMUX_GEN_ID_EXINT14                 = 0x0E, /*!< edmamux generator channel inputs resources: exint line14 */
  EDMAMUX_GEN_ID_EXINT15                 = 0x0F, /*!< edmamux generator channel inputs resources: exint line15 */
  EDMAMUX_GEN_ID_DMAMUX_CH1_EVT          = 0x10, /*!< edmamux generator channel inputs resources: dmamux channel1 event */
  EDMAMUX_GEN_ID_DMAMUX_CH2_EVT          = 0x11, /*!< edmamux generator channel inputs resources: dmamux channel2 event */
  EDMAMUX_GEN_ID_DMAMUX_CH3_EVT          = 0x12, /*!< edmamux generator channel inputs resources: dmamux channel3 event */
  EDMAMUX_GEN_ID_DMAMUX_CH4_EVT          = 0x13, /*!< edmamux generator channel inputs resources: dmamux channel4 event */
  EDMAMUX_GEN_ID_DMAMUX_CH5_EVT          = 0x14, /*!< edmamux generator channel inputs resources: dmamux channel5 event */
  EDMAMUX_GEN_ID_DMAMUX_CH6_EVT          = 0x15, /*!< edmamux generator channel inputs resources: dmamux channel6 event */
  EDMAMUX_GEN_ID_DMAMUX_CH7_EVT          = 0x16, /*!< edmamux generator channel inputs resources: dmamux channel7 event */
  EDMAMUX_GEN_ID_DMAMUX_CH8_EVT          = 0x17  /*!< edmamux generator channel inputs resources: dmamux channel8 event */
} edmamux_gen_id_sel_type;

/**
  * @brief dmamux generator polarity type
  */
typedef enum {
  EDMAMUX_GEN_POLARITY_DISABLE           = 0x00, /*!< edmamux generator channel inputs resources polarity default value */
  EDMAMUX_GEN_POLARITY_RISING            = 0x01, /*!< edmamux generator channel inputs resources polarity: rising */
  EDMAMUX_GEN_POLARITY_FALLING           = 0x02, /*!< edmamux generator channel inputs resources polarity: falling */
  EDMAMUX_GEN_POLARITY_RISING_FALLING    = 0x03  /*!< edmamux generator channel inputs resources polarity: rising_falling */
} edmamux_gen_pol_type;



/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32_DMAMUX_H */

/** @} */
