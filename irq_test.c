#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/module.h>

#define GPIO_LINE 17
int irq_line = -1;

static irqreturn_t irq_test_irq(int arg, void* ptr)
{
	printk("irq_test: interrupt\n");
	
	return IRQ_HANDLED;
}

static int __init irq_test_init(void)
{
	printk("irq_test: init\n");
	
	gpio_request_one(GPIO_LINE, GPIOF_DIR_IN, "irq_test");
	irq_line = gpio_to_irq(GPIO_LINE);
	
	if(request_irq(irq_line, irq_test_irq, IRQF_TRIGGER_RISING,
	"irq_test_driver", NULL)) {
		printk("irq_test: unable to attach gpio interrupt\n");
		return -2;
	}

	return 0;
}

static void __exit irq_test_exit(void)
{
	printk("irq_test: exit\n");
	
	free_irq(irq_line, NULL);
	gpio_free(GPIO_LINE);
	
	return;
}

module_init(irq_test_init);
module_exit(irq_test_exit);
MODULE_LICENSE("GPL");
