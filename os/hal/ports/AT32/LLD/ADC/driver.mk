ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_ADC TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC/hal_adc_lld.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC/hal_adc_lld.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC
