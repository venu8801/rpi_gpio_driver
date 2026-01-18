/**
 * Common header definitions
 */


/** defines GPIO function types inlcluding alternate functions
 * alternate function definitions are defined in the peripherals document
 * at section 16.2
 */
typedef enum {
    GPIO_PIN_OUTPUT = 0x0,
    GPIO_PIN_INPUT,
    GPIO_ALT0,
    GPIO_ALT1,
    GPIO_ALT2,
    GPIO_ALT3,
    GPIO_ALT4,
    GPIO_ALT5,
} gpio_func_type_t;

/* common function prototypes */
int32_t gpio_function_select(uint8_t pin_num, gpio_func_type_t ftype);
void* get_fsel_reg(uint8_t pin_num);
int32_t gpio_pin_set(uint8_t pin_num);