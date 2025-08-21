
#include "gd32f30x.h"

void SystemInit(void) {
  volatile uint32_t i;

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  /* set CP10 and CP11 Full Access */
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif

  RCU_CTL |= RCU_CTL_IRC8MEN;
  while (0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
  }
  if (((RCU_CFG0 & RCU_CFG0_SCSS) == RCU_SCSS_PLL)) {
    // The following is to prevent Vcore fluctuations caused by frequency
    // switching. It is strongly recommended to include it to avoid issues
    // caused by self-removal.
    volatile uint32_t reg;
    for (i = 0; i < 0x50; i++) {
    }

    reg = RCU_CFG0;
    reg &= ~(RCU_CFG0_AHBPSC);
    reg |= RCU_AHB_CKSYS_DIV2;
    RCU_CFG0 = reg;
    for (i = 0; i < 0x50; i++) {
    }

    reg = RCU_CFG0;
    reg &= ~(RCU_CFG0_AHBPSC);
    reg |= RCU_AHB_CKSYS_DIV4;
    RCU_CFG0 = reg;
    for (i = 0; i < 0x50; i++) {
    }

    reg = RCU_CFG0;
    reg &= ~(RCU_CFG0_AHBPSC);
    reg |= RCU_AHB_CKSYS_DIV8;
    RCU_CFG0 = reg;
    for (i = 0; i < 0x50; i++) {
    }

    reg = RCU_CFG0;
    reg &= ~(RCU_CFG0_AHBPSC);
    reg |= RCU_AHB_CKSYS_DIV16;
    RCU_CFG0 = reg;
    for (i = 0; i < 0x50; i++) {
    }
  }
  RCU_CFG0 &= ~RCU_CFG0_SCS; // Select CK_IRC8M as the CK_SYS Source
  for (i = 0; i < 200 * 10; i++) {
  }

#if (defined(GD32F30X_HD) || defined(GD32F30X_XD))
  // Reset HXTALEN, CKMEN and PLLEN bits
  RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN);
  // Reset all interrrupt flags
  RCU_INT = 0x009f0000U;
#elif defined(GD32F30X_CL)
  // Reset HXTALEN, CKMEN, PLLEN, PLL1EN and PLL2EN bits
  RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_PLL1EN | RCU_CTL_PLL2EN | RCU_CTL_CKMEN |
               RCU_CTL_HXTALEN);
  // Reset all interrrupt flags
  RCU_INT = 0x00ff0000U;
#endif
  RCU_CTL &= ~(RCU_CTL_HXTALBPS);
  RCU_CFG0 = 0x00000000U;
  RCU_CFG1 = 0x00000000U;
}