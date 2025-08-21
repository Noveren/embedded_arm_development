
#include "gd32e23x.h"

/// TODO: 先复位 RCU 相关寄存器(IRC8M)，再提供可配置接口选择需要的频率
void SystemInit() {
  // 0 24MHz; 1: 48MHz; 2: 72MHz
  fmc_wscnt_set(WS_WSCNT_2);

  rcu_deinit();
  rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
  rcu_pll_config(RCU_PLLSRC_IRC8M_DIV2, RCU_PLL_MUL18);
  rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
  rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV1);
  rcu_apb2_clock_config(RCU_APB2_CKAHB_DIV1);

  rcu_osci_on(RCU_IRC8M);
  rcu_osci_stab_wait(RCU_IRC8M);
  rcu_osci_on(RCU_PLL_CK);
  rcu_osci_stab_wait(RCU_PLL_CK);

  nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x00);
}