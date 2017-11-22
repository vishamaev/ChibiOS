/*
 * rusefi_lse_fix.h
 *
 * Nov 21, 2017
 * Andrey Belomutskiy
 */

#ifndef CHIBIOS3_OS_HAL_PORTS_STM32_LLD_RTCV2_RUSEFI_LSE_FIX_H_
#define CHIBIOS3_OS_HAL_PORTS_STM32_LLD_RTCV2_RUSEFI_LSE_FIX_H_

/**
 * this rusEfi hack is about surviving lack of LSE (32kHz osc) part of RTC
 */
#define LSE_TIMEOUT 1000000

#endif /* CHIBIOS3_OS_HAL_PORTS_STM32_LLD_RTCV2_RUSEFI_LSE_FIX_H_ */
