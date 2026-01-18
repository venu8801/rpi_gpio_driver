/**
 * IOCTL GPIO Driver for rpi zero 2w
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <gpio_drv.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Venu Gopal Atchyutanna <venu.ark.prasad@gmail.com>");
MODULE_VERSION("0.1");

/* global driver context structure */
gpio_drv_ctx gpio_cdevObj = {0};

/* file operations structure for GPIO driver */
struct file_operations gpio_drv_fops = {
    .open = gpio_drv_open,
    .release = gpio_drv_close,
    .read = gpio_drv_read,
    .write = gpio_drv_write,
    .unlocked_ioctl = gpio_drv_ioctl,
};

int gpio_drv_open(struct inode *filenode, struct file *f_object)
{
    int ret = GPIO_SUCCESS;
    printk(KERN_INFO "GPIO Driver - Opened");
    // io-remap the physical address to kernels virtual address space
    gpio_cdevObj.gpio_base = ioremap(GPIO_FSEL_BASE, GPIO_REG_SIZE);
    if (gpio_cdevObj.gpio_base == NULL) {
        printk(KERN_ERR "Failed to map the GPIO base addr");
        ret = GPIO_IOREMAP_FAIL;
        goto exit;
    }
exit:
    return ret;
}

int gpio_drv_close(struct inode *file_node, struct file *f_object)
{
    printk(KERN_INFO "GPIO Driver - Released");
    return GPIO_SUCCESS;
}

ssize_t gpio_drv_write(struct file *f_object, const char __user *usrbuff, size_t usr_size, loff_t *usr_ofset)
{
    ssize_t bytesWritten = 0;
    printk(KERN_INFO "GPIO - Drv write called");
    return bytesWritten;
}

ssize_t gpio_drv_read(struct file *f_object, char __user *usrbuff, size_t usr_bsize, loff_t *usr_ofset)
{
    ssize_t bytesRead = 0;
    printk(KERN_INFO "GPIO - Drv read called");
    return bytesRead;
}

long gpio_drv_ioctl(struct file *f_object, unsigned int gpio_cmd_id, unsigned long gpio_arg)
{
    printk(KERN_INFO "GPIO - Drv IOCTL tirggered with cmd-id;: [%d]", gpio_cmd_id);
    return GPIO_SUCCESS;
}

int __init gpio_drv_init(void)
{
    printk(KERN_INFO "GPIO DRV Init");
    int ret = GPIO_SUCCESS;
    /* register one character device */
    ret = alloc_chrdev_region(&gpio_cdevObj.gpio_dev_num, 0, 1, GPIO_DRV_NAME);
    if (ret)
    {
        printk(KERN_ERR "GPIO - Driver allocation failed");
        goto exit;
    }
    printk(KERN_INFO "char device allocation successful dev Major: %d - Minor: %d",
        MAJOR(gpio_cdevObj.gpio_dev_num), MINOR(gpio_cdevObj.gpio_dev_num));
    /* initialize cdev */
    cdev_init(&gpio_cdevObj.gpio_drv_cdev, &gpio_drv_fops);

    ret = cdev_add(&gpio_cdevObj.gpio_drv_cdev, gpio_cdevObj.gpio_dev_num, 1);
    if (ret)
    {
        printk(KERN_ERR "GPIO driver cdev_add() failed with ret: %d", ret);
        goto exit;
    }

exit:
    return ret;
}

void __exit gpio_drv_exit(void)
{
    printk(KERN_INFO "Rpi GPIO Drv exit");
    unregister_chrdev_region(gpio_cdevObj.gpio_dev_num, 1);
    cdev_del(&gpio_cdevObj.gpio_drv_cdev);
    return;
}


module_init(gpio_drv_init);
module_exit(gpio_drv_exit);