#include <stdint.h>

/* Symbols provided by the linker script */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector"), used))
const uintptr_t vector_table[] =
{
    (uintptr_t)&_estack,          /* 0  Initial Stack Pointer */
    (uintptr_t)Reset_Handler,     /* 1  Reset */

    (uintptr_t)Default_Handler,   /* 2  NMI */
    (uintptr_t)Default_Handler,   /* 3  HardFault */
    (uintptr_t)Default_Handler,   /* 4  MemManage */
    (uintptr_t)Default_Handler,   /* 5  BusFault */
    (uintptr_t)Default_Handler,   /* 6  UsageFault */

    0,                            /* 7  Reserved */
    0,                            /* 8  Reserved */
    0,                            /* 9  Reserved */
    0,                            /* 10 Reserved */

    (uintptr_t)Default_Handler,   /* 11 SVCall */
    (uintptr_t)Default_Handler,   /* 12 Debug Monitor */

    0,                            /* 13 Reserved */

    (uintptr_t)Default_Handler,   /* 14 PendSV */
    (uintptr_t)Default_Handler    /* 15 SysTick */
};

void Default_Handler(void)
{
    while (1)
    {
    }
}

void Reset_Handler(void)
{
    /* Copy .data from FLASH to RAM */
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata)
    {
        *dst = *src;
        ++src;
        ++dst;
    }

    /* Initialize .bss to zero */
    uint32_t *start = &_sbss;

    while (start < &_ebss)
    {
        *start = 0;
        ++start;
    }

    main();

    while (1)
    {
    }
}