/*
    ChibiOS - Copyright (C) 2006,2007,2008,2009,2010,2011,2012,2013,2014,
              2015,2016,2017,2018,2019,2020,2021 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    sb/vhal/sbvio_spi.c
 * @brief   ARM SandBox host Virtual SPI code.
 *
 * @addtogroup ARM_SANDBOX_HOST_VIO_SPI
 * @{
 */

#include "sb.h"

#if (VIO_CFG_ENABLE_SPI == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

static void vspi_cb(void *ip) {
  hal_sio_driver_c *siop = (hal_sio_driver_c *)ip;
  const vio_spi_unit_t *unitp = (const vio_spi_unit_t *)drvGetArgumentX(siop);

  sbVRQTriggerFromISR(unitp->vrqsb, unitp->vrqn);
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

void sb_sysc_vio_spi(struct port_extctx *ectxp) {
  sb_class_t *sbp = (sb_class_t *)chThdGetSelfX()->ctx.syscall.p;
  uint32_t sub  = ectxp->r0;
  uint32_t unit = ectxp->r1;
  ectxp->r0 = (uint32_t)CH_RET_INNER_ERROR;
  const vio_spi_unit_t *unitp;

  if (unit >= sbp->config->vioconf->spis->n) {
    ectxp->r0 = (uint32_t)HAL_RET_NO_RESOURCE;
    return;
  }

  unitp = &sbp->config->vioconf->spis->units[unit];

  switch (sub) {
  case SB_VSPI_INIT:
    {
      msg_t msg;

      /* Associating this virtual SPI to the SPI driver.*/
      drvSetArgumentX(unitp->spip, (void *)unitp);

      msg = drvStart(unitp->spip);
      if (msg == HAL_RET_SUCCESS) {

        /* Starting with disabled events, enabling the callback.*/
        sioWriteEnableFlags(unitp->spip, SIO_EV_NONE);
        drvSetCallbackX(unitp->spip, vspi_cb);
      }

      ectxp->r0 = (uint32_t)msg;
      break;
    }
  case SB_VSPI_DEINIT:
    {
      drvStop(unitp->spip);

      ectxp->r0 = (uint32_t)HAL_RET_SUCCESS;
      break;
    }
  default:
    ectxp->r0 = (uint32_t)CH_RET_ENOSYS;
    break;
  }
}

void sb_fastc_vio_spi(struct port_extctx *ectxp) {
  sb_class_t *sbp = (sb_class_t *)chThdGetSelfX()->ctx.syscall.p;
  uint32_t sub  = ectxp->r0;
  uint32_t unit = ectxp->r1;
  const vio_spi_unit_t *unitp;

  /* Returned value in case of error or illegal sub-code.*/
  ectxp->r0 = (uint32_t)-1;

  if (unit >= sbp->config->vioconf->spis->n) {
    return;
  }

  unitp = &sbp->config->vioconf->spis->units[unit];

  /* We don't want assertion or errors to be caused in host, making sure
     all functions are called in the proper state.*/
  if (unitp->spip->state != HAL_DRV_STATE_READY) {
    return;
  }

  switch (sub) {
  case SB_VSPI_SETCFG:
    {
      uint32_t conf = ectxp->r2;
      const vio_spi_config_t *confp;

      /* Check on configuration index.*/
      if (conf >= sbp->config->vioconf->spis->n) {
        ectxp->r0 = (uint32_t)HAL_RET_CONFIG_ERROR;
        return;
      }

      /* Specified VSPI configuration.*/
      confp = &sbp->config->vioconf->spiconfs->cfgs[conf];

      ectxp->r0 = (uint32_t)drvConfigureX(unitp->spip, confp->spicfgp);
      break;
    }
  default:
    /* Silently ignored.*/
    break;
  }
}

#endif /* VIO_CFG_ENABLE_SPI == TRUE */

/** @} */
