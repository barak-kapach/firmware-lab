#include <stdint.h>

//values from another files (linker work)
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void);
// void Default_Handler(void);

__attribute__((section(".isr_vector"), used))
const uintptr_t vector_table[] =
{
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler
};


void Reset_Handler(void){
    //copy data from FLASH to RAM
    uint32_t * src = &_sidata;
    uint32_t * dst = &_sdata;
    while(dst < &_edata){
        *dst = *src;
        ++src;
        ++dst;
    }
    //initialize .bss -> ZEROES
    uint32_t * start = &_sbss;
    uint32_t *end = &_ebss;
    while(start < end){
        *start = 0;
        ++start;
    }
    main();

    while (1)
    {
    }
    
}

