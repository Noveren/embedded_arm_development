
void NMI_Handler(void) {}

void HardFault_Handler(void) {}

void MemManage_Handler(void) {}

void BusFault_Handler(void) {}

void UsageFault_Handler(void) {}

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

void SysTick_Handler(void) {}

#include <gd32f30x.h>

int main(void) {
  // uint32_t i = 0;
  // rcu_periph_clock_enable(RCU_GPIOB);

  // gpio_init(GPIOB, GPIO_MODE_OUT_OD, GPIO_OSPEED_2MHZ, GPIO_PIN_0);
  // gpio_bit_set(GPIOB, GPIO_PIN_0);
  // for (;;) {
  //   gpio_bit_write(GPIOB, GPIO_PIN_0, !gpio_output_bit_get(GPIOB,
  //   GPIO_PIN_0)); for (i = 0; i < 750 * 1000; i++) {
  //   }
  // }
}