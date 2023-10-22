/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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
 * @file    DMA/rt_at32_edma.h
 * @brief   DMA helper driver header. 
 *  
 * @note    This driver uses the new naming convention used for the RT-AT32F4xx
 *          so the "DMA channels" are referred as "DMA streams".
 *
 *
 * @addtogroup  RT_AT32_EDMA
 * @{
* @{
 */

#ifndef RT_AT32_EDMA_H
#define RT_AT32_EDMA_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   DMA capability.
 * @details if @p TRUE then the DMA is able of burst transfers, FIFOs,
 *          scatter gather and other advanced features.
 */
#define RT_AT32_EDMA_ADVANCED          FALSE                                   //FixMe Проверить!

/**
 * @brief   Total number of DMA streams.
 * @details This is the total number of streams among all the DMA units.
 */
#define RT_AT32_EDMA_STREAMS           8U                                   // VS OK

/**
 * @brief   Mask of the ISR bits passed to the DMA callback functions.
 */
#define RT_AT32_EDMA_ISR_MASK          0x0E                                    //FixMe Проверить!

/**
 * @brief   Returns the request line associated to the specified stream.
 * @note    In some AT32 manuals the request line is named confusingly
 *          channel.
 *
 * @param[in] id        the unique numeric stream identifier
 * @param[in] c         a stream/request association word, one request per
 *                      nibble
 * @return              Returns the request associated to the stream.
 */
#define RT_AT32_EDMA_GETCHANNEL(id, c)                                         \
  (((uint32_t)(c) >> (((uint32_t)(id) % (uint32_t)RT_AT32_EDMA1_NUM_CHANNELS) * 4U)) & 15U)

/**
 * @brief   Checks if a DMA priority is within the valid range.
 * @param[in] prio      DMA priority
 *
 * @retval              The check result.
 * @retval false        invalid DMA priority.
 * @retval true         correct DMA priority.
 */
#define RT_AT32_EDMA_IS_VALID_PRIORITY(prio) (((prio) >= 0U) && ((prio) <= 3U))

#if (RT_AT32_EDMA_SUPPORTS_DMAMUX == FALSE) || defined(_DOXYGEN__)
/**
 * @brief   Checks if a DMA stream id is within the valid range.
 *
 * @param[in] id        DMA stream id
 * @retval              The check result.
 * @retval false        invalid DMA channel.
 * @retval true         correct DMA channel.
 */
# define RT_AT32_EDMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) < RT_AT32_EDMA_STREAMS))
#else /* const stm32_dma_stream_t *dmaStreamAlloc(uint32_t id, == FALSE */
# if RT_AT32_EDMA2_NUM_CHANNELS > 0
#  define RT_AT32_EDMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (RT_AT32_EDMA_STREAMS + 2)))
# else
#  define RT_AT32_EDMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (RT_AT32_EDMA_STREAMS + 1)))
# endif
#endif /* RT_AT32_EDMA_SUPPORTS_DMAMUX == FALSE */

/**
 * @brief   Returns an unique numeric identifier for a DMA stream.
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              An unique numeric stream identifier.
 */
#define RT_AT32_EDMA_STREAM_ID(dma, stream)                                    \
  ((((dma) - 1) * RT_AT32_EDMA1_NUM_CHANNELS) + ((stream) - 1))

/**
 * @brief   Returns a DMA stream identifier mask.
 *
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              A DMA stream identifier mask.
 */
#define STM32_DMA_STREAM_ID_MSK(dma, stream)                                \
  (1U << RT_AT32_EDMA_STREAM_ID(dma, stream))

/**
 * @brief   Checks if a DMA stream unique identifier belongs to a mask.
 *
 * @param[in] id        the stream numeric identifier
 * @param[in] mask      the stream numeric identifiers mask
 *
 * @retval              The check result.
 * @retval false        id does not belong to the mask.
 * @retval true         id belongs to the mask.
 */
#define STM32_DMA_IS_VALID_ID(id, mask) (((1U << (id)) & (mask)))

#if (RT_AT32_EDMA_SUPPORTS_DMAMUX == TRUE) || defined(_DOXYGEN__)
/**
 * @name    Special stream identifiers
 * @{
 */
#define STM32_DMA_STREAM_ID_ANY         RT_AT32_EDMA_STREAMS
#define STM32_DMA_STREAM_ID_ANY_DMA1    (STM32_DMA_STREAM_ID_ANY + 1)
#if RT_AT32_EDMA2_NUM_CHANNELS > 0
#define STM32_DMA_STREAM_ID_ANY_DMA2    (STM32_DMA_STREAM_ID_ANY_DMA1 + 1)
#endif
/** @} */
#endif

/**
 * @name    DMA streams identifiers
 * @{
 */
/**
 * @brief   Returns a pointer to a stm32_dma_stream_t structure.
 *
 * @param[in] id        the stream numeric identifier
 * @return              A pointer to the stm32_dma_stream_t constant structure
 *                      associated to the DMA stream.
 */
#define RT_AT32_EDMA_STREAM(id)     (&_rt_at32_edma_streams[id])

#if RT_AT32_EDMA1_NUM_CHANNELS > 0
#define RT_AT32_EDMA1_STREAM1       RT_AT32_EDMA_STREAM(0)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 1
#define RT_AT32_EDMA1_STREAM2       RT_AT32_EDMA_STREAM(1)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 2
#define RT_AT32_EDMA1_STREAM3       RT_AT32_EDMA_STREAM(2)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 3
#define RT_AT32_EDMA1_STREAM4       RT_AT32_EDMA_STREAM(3)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 4
#define RT_AT32_EDMA1_STREAM5       RT_AT32_EDMA_STREAM(4)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 5
#define RT_AT32_EDMA1_STREAM6       RT_AT32_EDMA_STREAM(5)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 6
#define RT_AT32_EDMA1_STREAM7       RT_AT32_EDMA_STREAM(6)
#endif
#if RT_AT32_EDMA1_NUM_CHANNELS > 7
#define RT_AT32_EDMA1_STREAM8       RT_AT32_EDMA_STREAM(7)
#endif

/** @} */

/**
 * @name    CR register constants common to all DMA types
 * @{
 */
#define STM32_DMA_CCR_RESET_VALUE   0x00000000U
#define STM32_DMA_CR_EN             DMA_CCR_EN
#define STM32_DMA_CR_TEIE           DMA_CCR_TEIE
#define STM32_DMA_CR_HTIE           DMA_CCR_HTIE
#define STM32_DMA_CR_TCIE           DMA_CCR_TCIE
#define STM32_DMA_CR_DIR_MASK       (DMA_CCR_DIR | DMA_CCR_MEM2MEM)
#define STM32_DMA_CR_DIR_P2M        0U
#define STM32_DMA_CR_DIR_M2P        DMA_CCR_DIR
#define STM32_DMA_CR_DIR_M2M        DMA_CCR_MEM2MEM
#define STM32_DMA_CR_CIRC           DMA_CCR_CIRC
#define STM32_DMA_CR_PINC           DMA_CCR_PINC
#define STM32_DMA_CR_MINC           DMA_CCR_MINC
#define STM32_DMA_CR_PSIZE_MASK     DMA_CCR_PSIZE
#define STM32_DMA_CR_PSIZE_BYTE     0U
#define STM32_DMA_CR_PSIZE_HWORD    DMA_CCR_PSIZE_0
#define STM32_DMA_CR_PSIZE_WORD     DMA_CCR_PSIZE_1
#define STM32_DMA_CR_MSIZE_MASK     DMA_CCR_MSIZE
#define STM32_DMA_CR_MSIZE_BYTE     0U
#define STM32_DMA_CR_MSIZE_HWORD    DMA_CCR_MSIZE_0
#define STM32_DMA_CR_MSIZE_WORD     DMA_CCR_MSIZE_1
#define STM32_DMA_CR_SIZE_MASK      (STM32_DMA_CR_PSIZE_MASK |              \
                                     STM32_DMA_CR_MSIZE_MASK)
#define STM32_DMA_CR_PL_MASK        DMA_CCR_PL
#define STM32_DMA_CR_PL(n)          ((n) << 12U)
/** @} */

/**
 * @name    Request line selector macro
 * @{
 */
#if RT_AT32_EDMA_SUPPORTS_CSELR || defined(__DOXYGEN__)
# define STM32_DMA_CR_CHSEL_MASK     (15U << 16U)
# define STM32_DMA_CR_CHSEL(n)       ((n) << 16U)
#else
# define STM32_DMA_CR_CHSEL_MASK     0U
# define STM32_DMA_CR_CHSEL(n)       0U
#endif
/** @} */

/**
 * @name    CR register constants only found in enhanced DMA
 * @{
 */
#define STM32_DMA_CR_DMEIE          0U  /**< @brief Ignored by normal DMA.  */
/** @} */

/**
 * @name    Status flags passed to the ISR callbacks
 * @{
 */
#define STM32_DMA_ISR_FEIF          0U
#define STM32_DMA_ISR_DMEIF         0U
#define STM32_DMA_ISR_TEIF          DMA_ISR_TEIF1
#define STM32_DMA_ISR_HTIF          DMA_ISR_HTIF1
#define STM32_DMA_ISR_TCIF          DMA_ISR_TCIF1
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(RT_AT32_EDMA_SUPPORTS_DMAMUX)
# error "STM32_DMA_SUPPORTS_DMAMUX not defined in registry"
#endif

#if !defined(RT_AT32_EDMA_SUPPORTS_CSELR)
# error "STM32_DMA_SUPPORTS_CSELR not defined in registry"
#endif

#if RT_AT32_EDMA_SUPPORTS_DMAMUX && RT_AT32_EDMA_SUPPORTS_CSELR
# error "STM32_DMA_SUPPORTS_DMAMUX and STM32_DMA_SUPPORTS_CSELR both TRUE"
#endif

#if !defined(RT_AT32_EDMA1_NUM_CHANNELS)
# error "RT_AT32_EDMA_NUM_CHANNELS not defined in registry"
#endif

#if (RT_AT32_EDMA1_NUM_CHANNELS < 0) || (RT_AT32_EDMA1_NUM_CHANNELS > 8)
#error "unsupported channels configuration"
#endif

#if (RT_AT32_EDMA_SUPPORTS_DMAMUX == TRUE) || defined(__DOXYGEN__)
# include "rt_at32_edmamux.h"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a DMA callback.
 *
 * @param[in] p         parameter for the registered function
 * @param[in] flags     pre-shifted content of the ISR register, the bits
 *                      are aligned to bit zero
 */
typedef void (*rt_at32_edmaisr_t)(void *p, uint32_t flags);

/**
 * @brief   RT_AT32 EDMA stream descriptor structure.
 */
typedef struct {
  EDMA_TypeDef          *dma;           /**< @brief Associated DMA.         */
  EDMA_Channel_TypeDef  *channel;       /**< @brief Associated DMA channel. */
  uint32_t              cmask;          /**< @brief Mask of streams sharing
                                             the same ISR.                  */
#if (RT_AT32_EDMA_SUPPORTS_CSELR == TRUE) || defined(__DOXYGEN__)
  volatile uint32_t     *cselr;         /**< @brief Associated CSELR reg.   */
#elif RT_AT32_EDMA_SUPPORTS_DMAMUX == TRUE
  EDMAMUX_Channel_TypeDef *mux;         /**< @brief Associated DMA mux.     */
#else
  uint8_t               dummy;          /**< @brief Filler.                 */
#endif
  uint8_t               shift;          /**< @brief Bit offset in ISR, IFCR
                                             and CSELR registers.           */
  uint8_t               selfindex;      /**< @brief Index to self in array. */
  uint8_t               vector;         /**< @brief Associated IRQ vector.  */
} rt_at32_edma_stream_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Associates a peripheral data register to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] addr      value to be written in the CPAR register
 *
 * @special
 */
#define dmaStreamSetPeripheral(dmastp, addr) {                              \
  (dmastp)->channel->CPAR = (uint32_t)(addr);                               \
}

/**
 * @brief   Associates a memory destination to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] addr      value to be written in the CMAR register
 *
 * @special
 */
#define dmaStreamSetMemory0(dmastp, addr) {                                 \
  (dmastp)->channel->CMAR = (uint32_t)(addr);                               \
}

/**
 * @brief   Sets the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] size      value to be written in the CNDTR register
 *
 * @special
 */
#define dmaStreamSetTransactionSize(dmastp, size) {                         \
  (dmastp)->channel->CNDTR = (uint32_t)(size);                              \
}

/**
 * @brief   Returns the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @return              The number of transfers to be performed.
 *
 * @special
 */
#define dmaStreamGetTransactionSize(dmastp) ((size_t)((dmastp)->channel->CNDTR))

/**
 * @brief   Programs the stream mode settings.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register
 *
 * @special
 */
#if RT_AT32_EDMA_SUPPORTS_CSELR || defined(__DOXYGEN__)
#define dmaStreamSetMode(dmastp, mode) {                                    \
  uint32_t cselr = *(dmastp)->cselr;                                        \
  cselr &= ~(0x0000000FU << (dmastp)->shift);                               \
  cselr |=  (((uint32_t)(mode) >> 16U) << (dmastp)->shift);                 \
  *(dmastp)->cselr = cselr;                                                 \
  (dmastp)->channel->CCR  = (uint32_t)(mode);                               \
}
#else
#define dmaStreamSetMode(dmastp, mode) {                                    \
  (dmastp)->channel->CCR  = (uint32_t)(mode);                               \
}
#endif

/**
 * @brief   DMA stream enable.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamEnable(dmastp) {                                           \
  (dmastp)->channel->CCR |= STM32_DMA_CR_EN;                                \
}

/**
 * @brief   DMA stream disable.
 * @details The function disables the specified stream and then clears any
 *          pending interrupt.
 * @note    This function can be invoked in both ISR or thread context.
 * @note    Interrupts enabling flags are set to zero after this call, see
 *          bug 3607518.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamDisable(dmastp) {                                          \
  (dmastp)->channel->CCR &= ~(STM32_DMA_CR_TCIE | STM32_DMA_CR_HTIE |       \
                              STM32_DMA_CR_TEIE | STM32_DMA_CR_EN);         \
  dmaStreamClearInterrupt(dmastp);                                          \
}

/**
 * @brief   DMA stream interrupt sources clear.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamClearInterrupt(dmastp) {                                   \
  (dmastp)->dma->IFCR = RT_AT32_EDMA_ISR_MASK << (dmastp)->shift;              \
}

/**
 * @brief   Starts a memory to memory operation using the specified stream.
 * @note    The default transfer data mode is "byte to byte" but it can be
 *          changed by specifying extra options in the @p mode parameter.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register, this value
 *                      is implicitly ORed with:
 *                      - @p STM32_DMA_CR_MINC
 *                      - @p STM32_DMA_CR_PINC
 *                      - @p STM32_DMA_CR_DIR_M2M
 *                      - @p STM32_DMA_CR_EN
 *                      .
 * @param[in] src       source address
 * @param[in] dst       destination address
 * @param[in] n         number of data units to copy
 */
#define dmaStartMemCopy(dmastp, mode, src, dst, n) {                        \
  dmaStreamSetPeripheral(dmastp, src);                                      \
  dmaStreamSetMemory0(dmastp, dst);                                         \
  dmaStreamSetTransactionSize(dmastp, n);                                   \
  dmaStreamSetMode(dmastp, (mode) |                                         \
                           STM32_DMA_CR_MINC | STM32_DMA_CR_PINC |          \
                           STM32_DMA_CR_DIR_M2M | STM32_DMA_CR_EN);         \
}

/**
 * @brief   Polled wait for DMA transfer end.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 */
#define dmaWaitCompletion(dmastp) {                                         \
  while ((dmastp)->channel->CNDTR > 0U)                                     \
    ;                                                                       \
  dmaStreamDisable(dmastp);                                                 \
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
extern const rt_at32_edma_stream_t _rt_at32_edma_streams[RT_AT32_EDMA_STREAMS];
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void dmaInit(void);
  const rt_at32_edma_stream_t *dmaStreamAllocI(uint32_t        id,
                                            uint32_t        priority,
                                            rt_at32_edmaisr_t  func,
                                            void *param);

  const rt_at32_edma_stream_t *dmaStreamAlloc(uint32_t         id,
                                           uint32_t         priority,
                                           rt_at32_edmaisr_t   func,
                                           void *param);

  void dmaStreamFreeI(const rt_at32_edma_stream_t *dmastp);
  void dmaStreamFree(const rt_at32_edma_stream_t *dmastp);
  void dmaServeInterrupt(const rt_at32_edma_stream_t *dmastp);
#if RT_AT32_EDMA_SUPPORTS_DMAMUX == TRUE
  void dmaSetRequestSource(const rt_at32_edma_stream_t *dmastp, uint32_t per);
#endif
#ifdef __cplusplus
}
#endif

#endif /* STM32_DMA_H */

/** @} */
