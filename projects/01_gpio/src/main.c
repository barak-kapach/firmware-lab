#include <stdint.h>


/***
 * base adress - we want to work relatively to them,
 *  this is easier to understand and debug, in addion
 *  , this code also fit to another PIN by changin some offsets
 * in this case/
 */
#define RCC_BASE_ADDRESS     0x40021000UL
#define GPIOB_BASE_ADDRESS   0x48000400UL

#define RCC_AHB2ENR_OFFSET   0x4CUL
#define GPIO_MODER_OFFSET    0x00UL
#define GPIO_ODR_OFFSET      0x14UL

#define LED_PIN              13U

//MACROS
#define RCC_AHB2ENR (RCC_BASE_ADDRESS + RCC_AHB2ENR_OFFSET)
#define GPIOB_MODER (GPIOB_BASE_ADDRESS + GPIO_MODER_OFFSET)
#define GPIOB_ODR   (GPIOB_BASE_ADDRESS + GPIO_ODR_OFFSET)

int main(void){
    volatile uint32_t *rcc_ahb2enr = (volatile uint32_t *)RCC_AHB2ENR;
    volatile uint32_t * gpiob_moder = (volatile uint32_t *)GPIOB_MODER;
    volatile uint32_t * gpiob_odr = (volatile uint32_t *)GPIOB_ODR;
    
    //enable the clk for GPIOB
    *rcc_ahb2enr |= (1U << 1);

    //configure PB13 as an output
    *gpiob_moder &= (~(0x3U << (2U * LED_PIN)));
    *gpiob_moder |= (1U << (2U * LED_PIN));

    //turn on PB13 - active high
    *gpiob_odr |= (1U << LED_PIN);
    while (1)
    {


    }
    
}