/**
 * Header to define structure and macro definitions
 */
#include <linux/cdev.h>
 /* enum to find the GPIO status */
typedef enum {
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
} gpio_drv_ctx;

#define GPIO_DRV_NAME "gpio_drv_rpi"
#define GPIO_FSEL_BASE 0x7E200000

/* Function select registers on bcm283x */
#define GPIO_FSEL0 GPIO_FSEL_BASE + 0x0
#define GPIO_FSEL1 GPIO_FSEL_BASE + 0x4
#define GPIO_FSEL2 GPIO_FSEL_BASE + 0x8
#define GPIO_FSEL3 GPIO_FSEL_BASE + 0xC
#define GPIO_FSEL4 GPIO_FSEL_BASE + 0x10
#define GPIO_FSEL5 GPIO_FSEL_BASE + 0x14

/* Reserved Registers */
#define GPIO_RESERVED1 GPIO_FSEL_BASE + 0x18
#define GPIO_RESERVED1 GPIO_FSEL_BASE + 0x24

/* GPSET registers @brief: registers to set the GPIO pins */
#define GPIO_SET0 GPIO_FSEL_BASE + 0x1C
#define GPIO_SET1 GPIO_FSEL_BASE + 0x20

/* GPCLR registers @brief: registers to clear the GPIO pins */
#define GPIO_CLR0 GPIO_FSEL_BASE + 0x28
#define GPIO_CLR1 GPIO_FSEL_BASE + 0x2C

/* GPLVL registers */
#define GPIO_PLVL0 GPIO_FSEL_BASE + 0x34
#define GPIO_PLVL1 GPIO_FSEL_BASE + 0x38

/* driver routine prototypes */
int gpio_drv_open(struct inode *filenode, struct file *f_object);
int gpio_drv_close(struct inode *file_node, struct file *f_object);
ssize_t gpio_drv_write(struct file *f_object, const char __user *usrbuff, size_t usr_size, loff_t *usr_ofset);
ssize_t gpio_drv_read(struct file *f_object, char __user *usrbuff, size_t usr_bsize, loff_t *usr_ofset);
long gpio_drv_ioctl(struct file *f_object, unsigned int gpio_cmd_id, unsigned long gpio_arg);
int __init gpio_drv_init(void);
void __exit gpio_drv_exit(void);