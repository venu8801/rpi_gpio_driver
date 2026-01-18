/**
 * Header to define structure and macro definitions
 */
#include <linux/cdev.h>
 /* enum to find the GPIO status */
typedef enum {
    GPIO_IOREMAP_FAIL = -2,
    GPIO_FAIL = -1,
    GPIO_SUCCESS = 0,
    GPIO_SET_SUCCESS,
    GPIO_SET_FAILED,
    GPIO_GET_FAILED,
} gpio_status_t;

/* driver context structure */
typedef struct {
    struct cdev gpio_drv_cdev;
    dev_t gpio_dev_num;
    uint32_t *gpio_base;
} gpio_drv_ctx;

#define GPIO_DRV_NAME "gpio_drv_rpi"
#define GPIO_REG_SIZE 0xA4
#define GPIO_FSEL_INVALID 0xFFFFAAAA
#define GPIO_FSEL_BASE 0x7E200000
/** Function select registers on bcm283x
 * total 6 registers each register can control 9 pin functions
 * 9 * 6 = 54 total pin controls can be done
 */
#define GPIO_FSEL0(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x0 /* controls GPIO pins 0 to 9*/
#define GPIO_FSEL1(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x4 /* controls GPIO pins 10 to 19*/
#define GPIO_FSEL2(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x8 /* controls GPIO pins 20 to 29*/
#define GPIO_FSEL3(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0xC /* controls GPIO pins 30 to 39*/
#define GPIO_FSEL4(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x10 /* controls GPIO pins 40 to 49*/
#define GPIO_FSEL5(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x14 /* controls GPIO pins 50 to 53*/

/** Reserved Registers
 * these registers might be intended to be used by GPU (Broadcom VideoCore GPU)
 * as this is a propreitary IP by BroadCom the data sheet recommends to not use these registers
 */
#define GPIO_RESERVED0(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x18
#define GPIO_RESERVED1(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x24

/* GPSET registers @brief: registers to set the GPIO pins */
#define GPIO_SET0(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x1C
#define GPIO_SET1(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x20

/* GPCLR registers @brief: registers to clear the GPIO pins */
#define GPIO_CLR0(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x28
#define GPIO_CLR1(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x2C

/* GPLVL registers @brief: registers to read the GPIO pin level */
#define GPIO_PLVL0(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x34
#define GPIO_PLVL1(GPIO_FSEL_MMIO_BASE) GPIO_FSEL_MMIO_BASE + 0x38

//todo: more GPIO register to be added


/* driver routine prototypes */
int gpio_drv_open(struct inode *filenode, struct file *f_object);
int gpio_drv_close(struct inode *file_node, struct file *f_object);
ssize_t gpio_drv_write(struct file *f_object, const char __user *usrbuff, size_t usr_size, loff_t *usr_ofset);
ssize_t gpio_drv_read(struct file *f_object, char __user *usrbuff, size_t usr_bsize, loff_t *usr_ofset);
long gpio_drv_ioctl(struct file *f_object, unsigned int gpio_cmd_id, unsigned long gpio_arg);
int __init gpio_drv_init(void);
void __exit gpio_drv_exit(void);