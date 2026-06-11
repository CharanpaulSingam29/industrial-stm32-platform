#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void Default_Handler(void) {
    while (1);
}

void Reset_Handler(void);
extern void SysTick_Handler(void);

__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))&_estack, 
    Reset_Handler,            
    Default_Handler,          
    Default_Handler,          
    Default_Handler,          
    Default_Handler,          
    Default_Handler,          
    0, 0, 0, 0,               
    Default_Handler,          
    Default_Handler,          
    0,                        
    Default_Handler,          
    SysTick_Handler           
};

void Reset_Handler(void) {
    uint32_t *pSource = &_sidata;
    uint32_t *pDest = &_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSource++;
    }

    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    main();
    while (1); 
}