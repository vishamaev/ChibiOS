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
 * @file    ADCv2/hal_adc_lld.c
 * @brief   STM32 ADC subsystem low level driver source.
 *
 * @addtogroup ADC
 * @{
 */

#include "hal.h"

#if HAL_USE_ADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define ADC1_DMA_CHANNEL                                                    \
  RT_AT32_DMA_GETCHANNEL(RT_AT32_ADC_ADC1_DMA_STREAM, RT_AT32_ADC1_DMA_CHN)

#define ADC2_DMA_CHANNEL                                                    \
  RT_AT32_DMA_GETCHANNEL(RT_AT32_ADC_ADC2_DMA_STREAM, RT_AT32_ADC2_DMA_CHN)

#define ADC3_DMA_CHANNEL                                                    \
  RT_AT32_DMA_GETCHANNEL(RT_AT32_ADC_ADC3_DMA_STREAM, RT_AT32_ADC3_DMA_CHN)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief ADC1 driver identifier.*/
#if RT_AT32_ADC_USE_ADC1 || defined(__DOXYGEN__)
ADCDriver ADCD1;
#endif

/** @brief ADC2 driver identifier.*/
#if RT_AT32_ADC_USE_ADC2 || defined(__DOXYGEN__)
ADCDriver ADCD2;
#endif

/** @brief ADC3 driver identifier.*/
#if RT_AT32_ADC_USE_ADC3 || defined(__DOXYGEN__)
ADCDriver ADCD3;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   ADC DMA service routine.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void adc_lld_serve_rx_interrupt(ADCDriver *adcp, uint32_t flags) {

  /* DMA errors handling.*/
  if ((flags & (RT_AT32_DMA_ISR_TEIF | RT_AT32_DMA_ISR_DMEIF)) != 0) {
    /* DMA, this could help only if the DMA tries to access an unmapped
       address space or violates alignment rules.*/
    _adc_isr_error_code(adcp, ADC_ERR_DMAFAILURE);
  }
  else {
    /* It is possible that the conversion group has already be reset by the
       ADC error handler, in this case this interrupt is spurious.*/
    if (adcp->grpp != NULL) {

      if ((flags & RT_AT32_DMA_ISR_TCIF) != 0) {
        /* Transfer complete processing.*/
        _adc_isr_full_code(adcp);
      }
      else if ((flags & RT_AT32_DMA_ISR_HTIF) != 0) {
        /* Half transfer processing.*/
        _adc_isr_half_code(adcp);
      }
    }
  }
}

/**
 * @brief   ADC IRQ service routine.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 * @param[in] sr        content of the SR register
 */
static void adc_lld_serve_interrupt(ADCDriver *adcp, uint32_t sr) {

  /*
  sr = 0x72 = 1110010 
              1         - RDY
               1        - Overflow occurred
                1       - Ordinary channel conversion has started
                 0      - No preempted channel conversion started
                  0     - (Preempted channel) Conversion is not complete
                   1    - (Ordinary channel)  Conversion is complete
                    0   - Voltage is within the value programmed
   
    ADC overflow condition, this could happen only if the DMA is unable to read data fast enough.
    Overflow detection is applicable to the case of DMA transfer enable or EOCSFEN =1
  */

  /* It could be a spurious interrupt caused by overflows after DMA disabling,
     just ignore it in this case.*/
  if (adcp->grpp != NULL) {
    adcerror_t emask = 0U;

    /* Note, an overflow may occur after the conversion ended before the driver
       is able to stop the ADC, this is why the state is checked too.*/
    if ((sr & ADC_STS_OCCO) && (adcp->state == ADC_ACTIVE)) {
      /* ADC overflow condition, this could happen only if the DMA is unable
         to read data fast enough.*/
      emask |= ADC_ERR_OVERFLOW;
    }
    if (sr & ADC_STS_VMOR) {
      /* Analog watchdog 1 error.*/
      emask |= ADC_ERR_AWD;
    }
    if (emask != 0U) {
      _adc_isr_error_code(adcp, emask);
    }
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if RT_AT32_ADC_USE_ADC1 || RT_AT32_ADC_USE_ADC2 || RT_AT32_ADC_USE_ADC3 ||       \
    defined(__DOXYGEN__)
/**
 * @brief   ADC interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(RT_AT32_ADC_HANDLER) {
  uint32_t sr;

  OSAL_IRQ_PROLOGUE();

#if RT_AT32_ADC_USE_ADC1
  sr = ADC1->STS;
  ADC1->STS = 0;
#if defined(RT_AT32_ADC_ADC1_IRQ_HOOK)
  RT_AT32_ADC_ADC1_IRQ_HOOK
#endif
  adc_lld_serve_interrupt(&ADCD1, sr);
#endif /* RT_AT32_ADC_USE_ADC1 */

#if RT_AT32_ADC_USE_ADC2
  sr = ADC2->STS;
  ADC2->STS = 0;
#if defined(RT_AT32_ADC_ADC2_IRQ_HOOK)
  RT_AT32_ADC_ADC2_IRQ_HOOK
#endif
  adc_lld_serve_interrupt(&ADCD2, sr);
#endif /* RT_AT32_ADC_USE_ADC2 */

#if RT_AT32_ADC_USE_ADC3
  sr = ADC3->STS;
  ADC3->STS = 0;
#if defined(RT_AT32_ADC_ADC3_IRQ_HOOK)
  RT_AT32_ADC_ADC3_IRQ_HOOK
#endif
  adc_lld_serve_interrupt(&ADCD3, sr);
#endif /* RT_AT32_ADC_USE_ADC3 */

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level ADC driver initialization.
 *
 * @notapi
 */
void adc_lld_init(void) {

#if RT_AT32_ADC_USE_ADC1
  /* Driver initialization.*/
  adcObjectInit(&ADCD1);
  ADCD1.adc     = ADC1;
  ADCD1.dmastp  = NULL;
  ADCD1.dmamode = RT_AT32_DMA_CR_CHSEL(ADC1_DMA_CHANNEL) |
                  RT_AT32_DMA_CR_PL(RT_AT32_ADC_ADC1_DMA_PRIORITY) |
                  RT_AT32_DMA_CR_DIR_P2M |
                  RT_AT32_DMA_CR_MSIZE_HWORD | RT_AT32_DMA_CR_PSIZE_HWORD |
                  RT_AT32_DMA_CR_MINC        | RT_AT32_DMA_CR_TCIE        |
                  RT_AT32_DMA_CR_DMEIE       | RT_AT32_DMA_CR_TEIE;
#endif

#if RT_AT32_ADC_USE_ADC2
  /* Driver initialization.*/
  adcObjectInit(&ADCD2);
  ADCD2.adc     = ADC2;
  ADCD2.dmastp  = NULL;
  ADCD2.dmamode = RT_AT32_DMA_CR_CHSEL(ADC2_DMA_CHANNEL) |
                  RT_AT32_DMA_CR_PL(RT_AT32_ADC_ADC2_DMA_PRIORITY) |
                  RT_AT32_DMA_CR_DIR_P2M |
                  RT_AT32_DMA_CR_MSIZE_HWORD | RT_AT32_DMA_CR_PSIZE_HWORD |
                  RT_AT32_DMA_CR_MINC        | RT_AT32_DMA_CR_TCIE        |
                  RT_AT32_DMA_CR_DMEIE       | RT_AT32_DMA_CR_TEIE;
#endif

#if RT_AT32_ADC_USE_ADC3
  /* Driver initialization.*/
  adcObjectInit(&ADCD3);
  ADCD3.adc     = ADC3;
  ADCD3.dmastp  = NULL;
  ADCD3.dmamode = RT_AT32_DMA_CR_CHSEL(ADC3_DMA_CHANNEL) |
                  RT_AT32_DMA_CR_PL(RT_AT32_ADC_ADC3_DMA_PRIORITY) |
                  RT_AT32_DMA_CR_DIR_P2M |
                  RT_AT32_DMA_CR_MSIZE_HWORD | RT_AT32_DMA_CR_PSIZE_HWORD |
                  RT_AT32_DMA_CR_MINC        | RT_AT32_DMA_CR_TCIE        |
                  RT_AT32_DMA_CR_DMEIE       | RT_AT32_DMA_CR_TEIE;
#endif

#if defined(rccResetADC)
  /* Shared reset case.*/
  rccResetADC();
#endif
  /* The shared vector is initialized on driver initialization and never
     disabled because sharing.*/
  nvicEnableVector(RT_AT32_ADC_NUMBER, RT_AT32_ADC_IRQ_PRIORITY);
}

/**
 * @brief   Configures and activates the ADC peripheral.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_start(ADCDriver *adcp) {

  /* If in stopped state then enables the ADC and DMA clocks.*/
  if (adcp->state == ADC_STOP) {
#if RT_AT32_ADC_USE_ADC1
    if (&ADCD1 == adcp) {
      adcp->dmastp = dmaStreamAllocI(RT_AT32_ADC_ADC1_DMA_STREAM,
                                     RT_AT32_ADC_ADC1_DMA_IRQ_PRIORITY,
                                     (at32_dmaisr_t)adc_lld_serve_rx_interrupt,
                                     (void *)adcp);

      osalDbgAssert(adcp->dmastp != NULL, "unable to allocate stream");
      dmaStreamSetPeripheral(adcp->dmastp, &ADC1->ODT);
#if defined(rccResetADC1)
      rccResetADC1();
#endif
      rccEnableADC1(true);
#if RT_AT32_DMA_SUPPORTS_DMAMUX
      dmaSetRequestSource(adcp->dmastp, STM32_DMAMUX1_ADC1);
#endif
    }
#endif /* RT_AT32_ADC_USE_ADC1 */

#if RT_AT32_ADC_USE_ADC2
    if (&ADCD2 == adcp) {
      adcp->dmastp = dmaStreamAllocI(RT_AT32_ADC_ADC2_DMA_STREAM,
                                     RT_AT32_ADC_ADC2_DMA_IRQ_PRIORITY,
                                     (at32_dmaisr_t)adc_lld_serve_rx_interrupt,
                                     (void *)adcp);
      osalDbgAssert(adcp->dmastp != NULL, "unable to allocate stream");
      dmaStreamSetPeripheral(adcp->dmastp, &ADC2->ODT);
#if defined(rccResetADC2)
      rccResetADC2();
#endif
      rccEnableADC2(true);
#if RT_AT32_DMA_SUPPORTS_DMAMUX
      dmaSetRequestSource(adcp->dmastp, STM32_DMAMUX1_ADC2);
#endif
    }
#endif /* RT_AT32_ADC_USE_ADC2 */

#if RT_AT32_ADC_USE_ADC3
    if (&ADCD3 == adcp) {
      adcp->dmastp = dmaStreamAllocI(RT_AT32_ADC_ADC3_DMA_STREAM,
                                     RT_AT32_ADC_ADC3_DMA_IRQ_PRIORITY,
                                     (at32_dmaisr_t)adc_lld_serve_rx_interrupt,
                                     (void *)adcp);
      osalDbgAssert(adcp->dmastp != NULL, "unable to allocate stream");
      dmaStreamSetPeripheral(adcp->dmastp, &ADC3->ODT);
#if defined(rccResetADC3)
      rccResetADC3();
#endif
      rccEnableADC3(true);
#if RT_AT32_DMA_SUPPORTS_DMAMUX
      dmaSetRequestSource(adcp->dmastp, STM32_DMAMUX1_ADC3);
#endif
    }
#endif /* RT_AT32_ADC_USE_ADC3 */

    /* This is a common register but apparently it requires that at least one
       of the ADCs is clocked in order to allow writing, see bug 3575297.*/
    ADC->CCTRL = (ADC->CCTRL & (ADC_CCTRL_ITSRVEN | ADC_CCTRL_VBATEN)) | (AT32_ADC_ADCPRE << 16);

    /* ADC initial setup, starting the analog part here in order to reduce
       the latency when starting a conversion.*/
    adcp->adc->CTRL1 = 0;
    adcp->adc->CTRL2 = 0;
    adcp->adc->CTRL2 = ADC_CTRL2_ADCEN;
  }
}

/**
 * @brief   Deactivates the ADC peripheral.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_stop(ADCDriver *adcp) {

  /* If in ready state then disables the ADC clock.*/
  if (adcp->state == ADC_READY) {

    dmaStreamFreeI(adcp->dmastp);
    adcp->dmastp = NULL;

    adcp->adc->CTRL1 = 0;
    adcp->adc->CTRL2 = 0;

#if RT_AT32_ADC_USE_ADC1
    if (&ADCD1 == adcp)
      rccDisableADC1();
#endif

#if RT_AT32_ADC_USE_ADC2
    if (&ADCD2 == adcp)
      rccDisableADC2();
#endif

#if RT_AT32_ADC_USE_ADC3
    if (&ADCD3 == adcp)
      rccDisableADC3();
#endif
  }
}

/**
 * @brief   Starts an ADC conversion.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_start_conversion(ADCDriver *adcp) {
  uint32_t mode;
  uint32_t ctrl2;
  const ADCConversionGroup *grpp = adcp->grpp;

  /* DMA setup.*/
  mode = adcp->dmamode;
  if (grpp->circular) {
    mode |= STM32_DMA_CR_CIRC;
    if (adcp->depth > 1) {
      /* If circular buffer depth > 1, then the half transfer interrupt
         is enabled in order to allow streaming processing.*/
      mode |= STM32_DMA_CR_HTIE;
    }
  }
  dmaStreamSetMemory0(adcp->dmastp, adcp->samples);
  dmaStreamSetTransactionSize(adcp->dmastp, (uint32_t)grpp->num_channels *
                                            (uint32_t)adcp->depth);
  dmaStreamSetMode(adcp->dmastp, mode);
  dmaStreamEnable(adcp->dmastp);

  /* ADC setup.*/
  adcp->adc->STS   = 0;
  adcp->adc->SMPR1 = grpp->spt1;
  adcp->adc->SMPR2 = grpp->spt2;
  adcp->adc->VMHB  = grpp->vmhb;
  adcp->adc->VMLB  = grpp->vmlb;
  adcp->adc->OSQ1  = grpp->osq1 | ADC_SQR1_NUM_CH(grpp->num_channels);
  adcp->adc->OSQ2  = grpp->osq2;
  adcp->adc->OSQ3  = grpp->osq3;

  /* ADC configuration and start.*/
//  adcp->adc->CTRL1 = grpp->ctrl1 | ADC_CTRL1_OCCOIE | ADC_CTRL1_SQEN;
  adcp->adc->CTRL1 = grpp->ctrl1 | ADC_CTRL1_OCCOIE;
  ctrl2 = grpp->ctrl2 | ADC_CTRL2_OCDMAEN | ADC_CTRL2_OCDRCEN | ADC_CTRL2_ADCEN;    /* Enforcing the mandatory bits in CTRL2.*/

  /* The start method is different dependign if HW or SW triggered, the
     start is performed using the method specified in the CR2 configuration.*/
  if ((ctrl2 & ADC_CTRL2_OCSWTRG) != 0) {
    adcp->adc->CTRL2 = (ctrl2 | ADC_CTRL2_RPEN) & ~ADC_CTRL2_OCSWTRG; /* Initializing CTRL2 while keeping ADC_CTRL_SWSTART at zero.*/
    adcp->adc->CTRL2 = (ctrl2 | ADC_CTRL2_RPEN);                      /* Finally enabling ADC_CTRL_SWSTART.*/
  }
  else
    adcp->adc->CTRL2 = ctrl2;
}

/**
 * @brief   Stops an ongoing conversion.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_stop_conversion(ADCDriver *adcp) {

  dmaStreamDisable(adcp->dmastp);
  adcp->adc->CTRL1 = 0;
  /* Because ticket #822, preserving injected conversions.*/
  adcp->adc->CTRL2 &= ~(ADC_CTRL2_OCSWTRG);
  adcp->adc->CTRL2 = ADC_CTRL2_ADCEN;
}

/**
 * @brief   Enables the TSVREFE bit.
 * @details The TSVREFE bit is required in order to sample the internal
 *          temperature sensor and internal reference voltage.
 * @note    This is an STM32-only functionality.
 */
void adcAT32EnableTSVREFE(void) {

  ADC->CCTRL |= ADC_CCTRL_ITSRVEN;
}

/**
 * @brief   Disables the TSVREFE bit.
 * @details The TSVREFE bit is required in order to sample the internal
 *          temperature sensor and internal reference voltage.
 * @note    This is an STM32-only functionality.
 */
void adcAT32DisableTSVREFE(void) {

  ADC->CCTRL &= ~ADC_CCTRL_ITSRVEN;
}

/**
 * @brief   Enables the VBATE bit.
 * @details The VBATE bit is required in order to sample the VBAT channel.
 * @note    This is an STM32-only functionality.
 * @note    This function is meant to be called after @p adcStart().
 */
void adcAT32EnableVBATE(void) {

  ADC->CCTRL |= ADC_CCTRL_VBATEN;
}

/**
 * @brief   Disables the VBATE bit.
 * @details The VBATE bit is required in order to sample the VBAT channel.
 * @note    This is an STM32-only functionality.
 * @note    This function is meant to be called after @p adcStart().
 */
void adcAT32DisableVBATE(void) {

  ADC->CCTRL &= ~ADC_CCTRL_VBATEN;
}

#endif /* HAL_USE_ADC */

/** @} */
