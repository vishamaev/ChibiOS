# Required platform files.
PLATFORMSRC := $(CHIBIOS)/os/hal/ports/common/ARMCMx/nvic.c \
               $(CHIBIOS)/os/hal/ports/AT32/AT32F4xx/at32_isr.c \
               $(CHIBIOS)/os/hal/ports/AT32/AT32F4xx/hal_lld.c  \
               $(CHIBIOS)/os/hal/ports/AT32/AT32F4xx/hal_efl_lld.c

# Required include directories.
PLATFORMINC := $(CHIBIOS)/os/hal/ports/common/ARMCMx \
               $(CHIBIOS)/os/hal/ports/AT32/AT32F4xx

# Optional platform files.
ifeq ($(USE_SMART_BUILD),yes)

# Configuration files directory
ifeq ($(HALCONFDIR),)
  ifeq ($(CONFDIR),)
    HALCONFDIR = .
  else
    HALCONFDIR := $(CONFDIR)
  endif
endif

HALCONF := $(strip $(shell cat $(HALCONFDIR)/halconf.h | egrep -e "\#define"))

else
endif

# Drivers compatible with the platform.
include $(CHIBIOS)/os/hal/ports/AT32/LLD/ADC/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/CAN/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/CRYP/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/DAC/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/DMA/driver.mk
#include $(CHIBIOS)/os/hal/ports/STM32/LLD/DMAv2/driver.mk
#include $(CHIBIOS)/os/hal/ports/AT32/LLD/EDMA/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/EXTI/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/GPIO/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/I2C/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/MACv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/OTGv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/QUADSPIv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/RTCv2/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SPIv1/driver_v2.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SDIOv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SYSTICKv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/TIMv1/driver.mk
include $(CHIBIOS)/os/hal/ports/AT32/LLD/USART/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/xWDGv1/driver.mk

# Shared variables
ALLCSRC += $(PLATFORMSRC)
ALLINC  += $(PLATFORMINC)
