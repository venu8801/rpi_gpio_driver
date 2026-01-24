/**
 * Common header definitions
 */


/** defines GPIO function types inlcluding alternate functions
 * alternate function definitions are defined in the peripherals document
 * at section 16.2
 */
#define GPIO_PIN_MASK_BITS 0x7

/* ping state mask value for FSEL registers */
#define GPIO_PIN_MASK_OUTPUT 0x01
#define GPIO_PIN_MASK_INPUT 0x00
#define GPIO_PIN_MASK_ALT0 0x04
#define GPIO_PIN_MASK_ALT1 0x05
#define GPIO_PIN_MASK_ALT2 0x06
#define GPIO_PIN_MASK_ALT3 0x07
#define GPIO_PIN_MASK_ALT4 0x03
#define GPIO_PIN_MASK_ALT5 0x02

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

/* clears GPIO_PIN_MASK_BITS from the start_bit given in the registers */
#define GPIO_FSEL_CLR(reg, start_bit) (*((uint32_t *)reg) &~(GPIO_PIN_MASK_BITS << start_bit))