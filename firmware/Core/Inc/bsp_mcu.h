#ifndef BSP_MCU_H
#define BSP_MCU_H

#include <stdint.h>

#define PERIPH_BASE_ADDR        (0x40000000U)
#define AHB1_PERIPH_BASE        (PERIPH_BASE_ADDR + 0x00020000U)
#define APB1_PERIPH_BASE        (PERIPH_BASE_ADDR + 0x00000000U)

typedef struct {
    volatile uint32_t MODER;   
    volatile uint32_t OTYPER;  
    volatile uint32_t OSPEEDR; 
    volatile uint32_t PUPDR;   
    volatile uint32_t IDR;     
    volatile uint32_t ODR;     
    volatile uint32_t BSRR;    
} BSP_GPIO_RegisterMap;

typedef struct {
    volatile uint32_t CR;       
    volatile uint32_t PLLCFGR;  
    volatile uint32_t CFGR;     
    volatile uint32_t CIR;      
    volatile uint32_t AHB1ENR;  
    volatile uint32_t APB1ENR;  
} BSP_RCC_RegisterMap;

#define MCU_RCC    ((BSP_RCC_RegisterMap *) (AHB1_PERIPH_BASE + 0x3800U))
#define MCU_GPIOC  ((BSP_GPIO_RegisterMap *) (AHB1_PERIPH_BASE + 0x0800U))

void BSP_SystemClock_Init(void);
void BSP_GPIO_Init_StatusLED(void);
void BSP_Delay_ms(uint32_t ms);

#endif /* BSP_MCU_H */