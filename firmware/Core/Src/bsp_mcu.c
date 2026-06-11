#include "bsp_mcu.h"

static volatile uint32_t Systick_Counter = 0;

void BSP_SystemClock_Init(void) {
    MCU_RCC->CR |= (1 << 16); 
    while (!(MCU_RCC->CR & (1 << 17))); 

    volatile uint32_t *flash_acr = (volatile uint32_t *)0x40023C00U;
    *flash_acr = (1 << 8) | (1 << 9) | (5 << 0); 

    MCU_RCC->PLLCFGR = (8 << 0) | (336 << 6) | (0 << 16) | (1 << 22);

    MCU_RCC->CR |= (1 << 24);
    while (!(MCU_RCC->CR & (1 << 25)));

    MCU_RCC->CFGR &= ~(0x3U);
    MCU_RCC->CFGR |= 0x2U;
    while (((MCU_RCC->CFGR >> 2) & 0x3U) != 0x2U);

    volatile uint32_t *systick_ctrl = (volatile uint32_t *)0xE000E010U;
    volatile uint32_t *systick_load = (volatile uint32_t *)0xE000E014U;
    
    *systick_load = 168000U - 1U; 
    *systick_ctrl = (1 << 0) | (1 << 1) | (1 << 2); 
}

void BSP_GPIO_Init_StatusLED(void) {
    MCU_RCC->AHB1ENR |= (1 << 2);
    MCU_GPIOC->MODER &= ~(3U << (13 * 2));
    MCU_GPIOC->MODER |= (1 << (13 * 2));   
    MCU_GPIOC->OTYPER &= ~(1 << 13);       
    MCU_GPIOC->OSPEEDR |= (2 << (13 * 2));  
}

void BSP_Delay_ms(uint32_t ms) {
    Systick_Counter = ms;
    while (Systick_Counter != 0) {
        __asm__ volatile("nop"); 
    }
}

void SysTick_Handler(void) {
    if (Systick_Counter > 0) {
        Systick_Counter--;
    }
}