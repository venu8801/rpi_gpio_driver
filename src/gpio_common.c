/** GPIO Common driver sub-routines
 * these sub-routines are extensions to control
 * different aspects of the GPIO pins.
 */

#include <gpio_drv.h>
#include <gpio_common_defs.h>

extern gpio_drv_ctx gpio_cdevObj;

int32_t gpio_pin_set(uint8_t pin_num) {
    // un-implemented
    return GPIO_SUCCESS;
}

void* get_fsel_reg(uint8_t pin_num)
{
    // if gpio_base is not mapped yet return NULL
    if (!gpio_cdevObj.gpio_base)
        return NULL;

    // based on the pin range return the actual MMIO address
    if (pin_num >= 0 && pin_num <= 9) {
        return GPIO_FSEL0(gpio_cdevObj.gpio_base);
    } else if (pin_num >= 10 && pin_num <= 19) {
        return GPIO_FSEL1(gpio_cdevObj.gpio_base);
    } else if (pin_num >= 20 && pin_num <= 29) {
        return GPIO_FSEL2(gpio_cdevObj.gpio_base);
    } else if (pin_num >= 30 && pin_num <= 39) {
        return GPIO_FSEL3(gpio_cdevObj.gpio_base);
    } else if (pin_num >= 40 && pin_num <= 49) {
        return GPIO_FSEL4(gpio_cdevObj.gpio_base);
    } else if (pin_num >= 50 && pin_num <= 53) {
        return GPIO_FSEL5(gpio_cdevObj.gpio_base);
    } else {
        printk(KERN_ERR "gpio pin out of valid range: pin_num: %u", pin_num);
        return NULL;
    }
}

int32_t gpio_function_select(uint8_t pin_num, gpio_func_type_t ftype)
{
    int32_t ret = GPIO_SUCCESS;
    volatile void *fsel_reg = get_fsel_reg(pin_num);
    if (fsel_reg == NULL) {
        printk(KERN_ERR "Invalid GPIO pin number");
        ret = GPIO_FAIL;
        goto exit;
    }
    uint8_t start_bit = (pin_num % 10) * 3;
    switch(ftype) {
        case GPIO_PIN_OUTPUT:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_OUTPUT << start_bit);
            break;
        case GPIO_PIN_INPUT:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit)| (GPIO_PIN_MASK_INPUT << start_bit);
            break;
        case GPIO_ALT0:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_ALT0 << start_bit);
            break;
        case GPIO_ALT1:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_ALT1 << start_bit);
            break;
        case GPIO_ALT2:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_ALT2 << start_bit);
            break;
        case GPIO_ALT3:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_ALT3 << start_bit);
            break;
        case GPIO_ALT4:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_MASK_ALT4 << start_bit);
            break;
        case GPIO_ALT5:
            *((uint32_t *)fsel_reg) = GPIO_FSEL_CLR(fsel_reg,  start_bit) | (GPIO_PIN_MASK_ALT5 << start_bit);
            break;
        default:
            /* GPIO pin default state to be input */
            *((uint32_t *)fsel_reg) |= GPIO_FSEL_CLR(fsel_reg, start_bit) | (GPIO_PIN_INPUT << start_bit);
    }
exit:
    return ret;
}

