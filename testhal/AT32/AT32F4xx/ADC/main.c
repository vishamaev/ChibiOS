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

#include "ch.h"
#include "hal.h"

#include "chprintf.h"             //++VS

#define CHPP  &SD1
#define CHP   (BaseSequentialStream*)CHPP 


#define LINE_LED    LINE_LED2     // Yellow LED ++VS

#define ADC_GRP1_NUM_CHANNELS   1
#define ADC_GRP1_BUF_DEPTH      8

#define ADC_GRP2_NUM_CHANNELS   8
#define ADC_GRP2_BUF_DEPTH      16

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];    // 1*8
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];    // 8*16 = 128

static void dump_sumple(int n, adcsample_t* pb) {
  int i;

  for (i = 0; i < n; i++) {
    chprintf(CHP, "0x%03.3x", pb[i]);
    if ((i+1)%8) {
      chprintf(CHP, ":");
    } else {
      chprintf(CHP, "\r\n");
    }
  }
  chprintf(CHP, "\r\n-------------------------\r\n");
}
#if 0
static void dump_dev(uint32_t *pb,  int n) {
  int i;
  static int cnt = 0;

  chprintf(CHP, "%02.2d-------------------------\r\n", cnt++);

  for (i = 0; i < n; i++) {
    chprintf(CHP, "0x%08.8x:  0x%08.8x\r\n", (uint32_t) pb, *pb);
    pb++;
  }
}
#endif

/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;

static void adccallback(ADCDriver *adcp) {

  if (adcIsBufferComplete(adcp)) {
    nx += 1;
  }
  else {
    ny += 1;
  }
}


size_t nerr = 0;

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
//  chprintf(CHP, "ADC Error: 0x%x\r\n", err);
  nerr++;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 1 channel, SW triggered.
 * Channels:    IN11.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  .circular     = false,
  .num_channels = ADC_GRP1_NUM_CHANNELS,
  .end_cb       = NULL,
  .error_cb     = adcerrorcallback,
 /* adc_lld_configuration_group_fields */
  .ctrl1        = 0,
  .ctrl2        = ADC_CTRL2_OCSWTRG,
  .spt1         = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3),
  .spt2         = 0,                                          
  .vmhb         = 0,
  .vmlb         = 0,
  .osq1         = 0,
  .osq2         = 0,
  .osq3         = ADC_OSQ3_OSN1_N(ADC_CHANNEL_IN11)
};


/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN11, IN12, IN11, IN12, IN11, IN12, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  .circular     = TRUE,
  .num_channels = ADC_GRP2_NUM_CHANNELS,
  .end_cb       = adccallback,
  .error_cb     = adcerrorcallback,
  .ctrl1        = ADC_CTRL1_SQEN,
  .ctrl2        = ADC_CTRL2_OCSWTRG,
  .spt1         = ADC_SMPR1_SMP_AN12(ADC_SAMPLE_56) | ADC_SMPR1_SMP_AN11(ADC_SAMPLE_56) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_144),
  .spt2         = 0,                                          
  .vmhb         = 0,
  .vmlb         = 0,
  .osq1         = 0,
  .osq2         = ADC_OSQ2_OSN8_N(ADC_CHANNEL_SENSOR) | ADC_OSQ2_OSN7_N(ADC_CHANNEL_VREFINT),
  .osq3         = ADC_OSQ3_OSN6_N(ADC_CHANNEL_IN12)   | ADC_OSQ3_OSN5_N(ADC_CHANNEL_IN11)    |
                  ADC_OSQ3_OSN4_N(ADC_CHANNEL_IN12)   | ADC_OSQ3_OSN3_N(ADC_CHANNEL_IN11)    |
                  ADC_OSQ3_OSN2_N(ADC_CHANNEL_IN12)   | ADC_OSQ3_OSN1_N(ADC_CHANNEL_IN11)
};

/*
 * Yellow LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetLine(LINE_LED);
    chThdSleepMilliseconds(500);
    palClearLine(LINE_LED);
    chThdSleepMilliseconds(500);
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  sdStart(CHPP, NULL);    /* Starting a serial port for chprintf().*/

  /*
   * Setting up analog inputs used by the demo.
   */
  palSetGroupMode(GPIOC,                                    // port      port identifier                 
                  PAL_PORT_BIT(1) | PAL_PORT_BIT(2),        // mask      group mask                      
                  0,                                        // offset    group bit offset within the port
                  PAL_MODE_INPUT_ANALOG);                   // mode      group mode                      

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chprintf(CHP, "GPT_ADC_AT: test start\r\n");
  chprintf(CHP, "nx: %d\r\nny: %d\r\n", nx, ny);
  dump_sumple(ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH, samples1);

  /*
   * Activates the ADC1 driver and the temperature sensor.
   */
  adcStart(&ADCD1, NULL);
  adcAT32EnableTSVREFE();

  /*
   * Linear conversion.
   */
  adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
//  dump_dev((uint32_t*)ADC1, 20);

  chThdSleepMilliseconds(1000);

  /*
   * Starts an ADC continuous conversion.
   */
  adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);
//  dump_dev((uint32_t*)ADC1, 20);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */

  while (true) {
    if (palReadPad(GPIOA, GPIOA_BUTTON)) {
      adcStopConversion(&ADCD1);
      adcAT32DisableTSVREFE();
      chprintf(CHP, "GPT_ADC_AT: test stop\r\n");
      chprintf(CHP, "ERRS: %d\r\n", nerr);
      chprintf(CHP, "--- samples1 ---\r\n");
      dump_sumple(ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH, samples1);
      chprintf(CHP, "--- samples2 ---\r\n");
      dump_sumple(ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH, samples2);


      /* 
      #define ADC_VREF                         (3.3)
      #define ADC_TEMP_BASE                    (1.26)
      #define ADC_TEMP_SLOPE                   (-0.00423)
       
      #define ADC_VREF_100000                  (330000)
      #define ADC_TEMP_BASE_100000             (126000)
      #define ADC_TEMP_SLOPE_100000            (-423)
       
      int sensor_vol = (ADC_TEMP_BASE_100000 - (adcValue)*ADC_VREF_100000)/4096  126000 - 1584 * 330000 / 4096 = -1 617,1875 
       
      int sensor_tmp = sensor_vol * 1000/ADC_TEMP_SLOPE_100000 +25               (-127,58/-423) + 25  
       
       
          printf("internal_temperature = %f deg C\r\n", (ADC_TEMP_BASE - (double)tmp * ADC_VREF / 4096) / ADC_TEMP_SLOPE + 25);
       
          (1.26 - 1584 * 3.3 / 4096) /-0.00423 + 25  = 28,82
       
          (1.26 - 1584 * 3.3 / 4096) = −0,016171875
          (126000 - 1584 * 330000 / 4096) = -1 617,1875
       
          -1 617,1875/-423 = 3,823138298
          -1 617/-423      = 3,822695035
      */ 

      #define ADC_VREF_10000                  (33000)
      #define ADC_TEMP_BASE_10000             (12600)
      #define ADC_TEMP_SLOPE_100000            (-423)

      int sensor_val = (ADC_TEMP_BASE_10000 - ((samples2[7]) * ADC_VREF_10000)/4096)*10;
      int sensor_tmp = sensor_val/ADC_TEMP_SLOPE_100000 + 25;

//      chprintf(CHP, "sensor_val = %D deg C\r\n", sensor_val);
      chprintf(CHP, "internal_temperature = %D deg C\r\n", sensor_tmp);

      /* 
              ADC_VREF         (3.3)
              ADC_TEMP_BASE    (1.26)
              ADC_TEMP_SLOPE   (-0.00423)
       
  #define SENSOR_ADC_MAX 		4095.0
  #define SENSOR_ADC_REFV  		3.3
  #define SENSOR_AVG_SLOPE 		2.5 
  #define SENSOR_V25  			  0.76
 
  float sensor_vol = (adcValue) * SENSOR_ADC_REFV / SENSOR_ADC_MAX;                 1584 * 3.3 / 4095.0 = 1.27648
  float sensor_tmp = ((sensor_vol - SENSOR_V25) *1000 / SENSOR_AVG_SLOPE) + 25.0;   (1.27648 - 0.76) * 1000 /2.5 + 25.0   = 231,592
       
        */

  #define SENSOR_ADC_MAX_I	    4095
  #define SENSOR_ADC_REFV_10	  33
  #define SENSOR_AVG_SLOPE_10   25 
  #define SENSOR_V25_100  		  76
       

//      double sensor_vol_10 = (samples2[7]) * SENSOR_ADC_REFV_10 / SENSOR_ADC_MAX_I;
//      double sensor_tmp = (((sensor_vol_10 * 10) - SENSOR_V25_100) * 100 / SENSOR_AVG_SLOPE_10) + 25.0;
//      int sensor_vol_10 = (samples2[7]) * SENSOR_ADC_REFV_10 / SENSOR_ADC_MAX_I;
//      int sensor_tmp = (((sensor_vol_10 * 10) - SENSOR_V25_100) * 100 / SENSOR_AVG_SLOPE_10) + 25;
//
//      chprintf(CHP, "internal_temperature = %D deg C\r\n", sensor_tmp);

//      chprintf(CHP, "nx: %d\r\nny: %d\r\n", nx, ny);
    }
    chThdSleepMilliseconds(500);
  }
}

/* 
*/ 
