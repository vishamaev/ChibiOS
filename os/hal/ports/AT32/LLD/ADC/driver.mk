ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_ADC TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC/hal_adc_lld.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/firmware/at32f435_437_adc.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC/hal_adc_lld.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/firmware/at32f435_437_adc.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC
PLATFORMINC += $(CHIBIOS)/os/hal/ports/AT32/AT32F4xx/inc
