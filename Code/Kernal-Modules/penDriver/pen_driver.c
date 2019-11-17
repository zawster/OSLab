#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


// probe function 

static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO, "[*] Hello Pen drive (%04X:%04X) plugged\n",id->idVendor, id->idProduct);
	return 0; // return 0 indicates we will manage this device
}

// disconnect usb

static void pen_disconnect(struct usb_interface * interface){
	printk(KERN_INFO "[*] Hello Pen drive is removed\n");
}

// usb_device_id
static struct usb_device_id pen_table[] = {
	// 058f:6387
	{ USB_DEVICE(0x058f, 0x6387) },
	{} // terminating entry
};

MODULE_DEVICE_TABLE (usb, pen_table);


// usb_driver

static struct usb_driver pen_driver = {
	.name = "Hello USB Pen-Driver",
	.id_table = pen_table,  // usb device id
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void){
	int ret = -1;
	printk(KERN_INFO "[*] Hello Constructor od driver\n");
	printk(KERN_INFO "\t Registering Driver with kernel\n");
	
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\t Registration is complete\n");
	
	
	return ret;
}

static void __exit pen_exit(void){
	// un register
	printk(KERN_INFO "[*] Hello Destructor of driver\n");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "\t Unregistration Compelete!\n");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zawster");
MODULE_DESCRIPTION("USB Pen Registration Driver");













