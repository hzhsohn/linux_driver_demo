#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/device.h>

#include <linux/miscdevice.h>
//#include <asm/hardware.h>


static struct class *firstdrv_class;
static struct class_device	*firstdrv_class_dev;

volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;

static int gaoyuan_open(struct inode *inode, struct file *file)
{
	printk("gaoyuan_open\n");
	return 0;
}

static int gaoyuan_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	printk("gaoyuan_write\n");
	return 0;
}
#if 1
static struct file_operations gaoyuan_led_dev_fops = {
	.owner			= THIS_MODULE,
	.open = gaoyuan_open, //提供了接口，自己去实现
	.write = gaoyuan_write,	  
	
};
#endif
#if 0
static struct file_operations tiny4412_led_dev_fops = {
	.owner			= THIS_MODULE,
	//.unlocked_ioctl	= tiny4412_leds_ioctl,
	
	.open = gaoyuan_open, //提供了接口，自己去实现
	.write = gaoyuan_write,	  
	
};

static struct miscdevice gaoyuan_led_dev_fops = {
	.minor			= 200,
	.name			= "aa",
	.fops			= &tiny4412_led_dev_fops,
};
#endif
int major;
static int __init gaoyuan_led_init(void) {
	
	printk("iiiiiiiiiiiiiiiiii\n");
	printk("iiiiiiiiiiiiiiiiii\n");
	//register_chrdev(231,"gao_leds",&gaoyuan_led_dev_fops);
	//事实证明通过手动方式创建节点的方式，卸载和运行都是正常的
	
	major = register_chrdev(0, "gao_leds", &gaoyuan_led_dev_fops); // 注册, 告诉内核  是系统自动设置主设备号的意思
/*在/sys/class/目录下创建设备类test_class别目录my_device_driver*/
	firstdrv_class = class_create(THIS_MODULE, "my_device_driver");   // 相当于手动的mknod 了
	

/*在/dev/目录和/sys/class/my_device_driver目录下分别创建设备文件my_device*/
	firstdrv_class_dev = device_create(firstdrv_class, NULL, MKDEV(major, 0), NULL, "my_device");

	/* /dev/gao_mknod 此设备号为0，其实这个次设备号，可以作为判断的以重依据的	这个设备节点是随便写的 自己想写啥写啥的*/

	return 0;
}

static void __exit gaoyuan_led_exit(void) {
	
	printk("tttttttttttttt\n");
	
	//dev_t devno = MKDEV (major, 0);
	//cdev_del(&gaoyuan_led_dev_fops);
	
	unregister_chrdev(major, "gao_leds"); // 卸载
	
	//device_destroy(firstdrv_class_dev,major);//  销毁  草  竟然不是这个函数引起的bug,那你到别编译过去呀，误导我
	device_unregister(firstdrv_class_dev);//  销毁
	
	class_destroy(firstdrv_class);

	
	printk("tttttttttttttt\n");
}

module_init(gaoyuan_led_init);
module_exit(gaoyuan_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("gaoyuan publish");


