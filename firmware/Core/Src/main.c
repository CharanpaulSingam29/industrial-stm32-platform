#include "main.h"
#include "bsp_mcu.h"

int main(void) {
    BSP_SystemClock_Init();
    BSP_GPIO_Init_StatusLED();

    while (1) {
        if (MCU_GPIOC->IDR & (1 << 13)) {
            MCU_GPIOC->BSRR = (1 << (13 + 16)); 
        } else {
            MCU_GPIOC->BSRR = (1 << 13);        
        }
        BSP_Delay_ms(500);
    }
    return 0;
}