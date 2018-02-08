

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<asm/uaccess.h>
#define BUFFER_SIZE 1024


static char device_buffer[BUFFER_SIZE];
static short size_of_message = 0;

static int Device_Open = 0;
static int Device_Close = 0;

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/*  length is the length of the userspace buffer*/
	/*  current position of the opened file*/
	/* copy_to_user function. source is device_buffer (the buffer defined at the start of the code) and destination is the userspace 		buffer *buffer */
	int error_count = 0;
	printk("\n=====Inside function: %s=====\n", __FUNCTION__);

	//Read from the kernel: copy_to_user(destination,source,size)
	error_count = copy_to_user(buffer, device_buffer, BUFFER_SIZE);

	if(error_count == 0){
		printk("Sent %d characters to the user\n", size_of_message);
	}
	else{
		printk("Failed to send %d character to user\n", error_count);
		return -EFAULT;
	}

	printk("======Returning from %s======\n\n", __FUNCTION__);
	return size_of_message+1;
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/*  length is the length of the userspace buffer*/
	/*  current position of the opened file*/
	/* copy_from_user function. destination is device_buffer (the buffer defined at the start of the code) and source is the userspace 		buffer *buffer */
	int  error_count = 0;
	printk("\n=====Inside function: %s=====\n", __FUNCTION__);

	if((length + size_of_message) <= BUFFER_SIZE)	//If greater than buffer size
	{
		//Write to kernel: copy_from_user(destination,source,size)
		printk("buffer = %p\nlength = %d,  offset = %p\n", (int*)buffer, (int)length, (int*)offset);


		error_count = copy_from_user(device_buffer + size_of_message ,buffer,length);
		if(error_count == 0){
			printk("Wrote %d characters to kernel\n", (int)length-1);
		}
		else{
			printk("Failed to write %d characters to kernel\n", error_count);
		}
		size_of_message += (length - error_count - 1);
	}

        printk("======Returning from %s======\n\n", __FUNCTION__);

	return (length-error_count);
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	Device_Open++;
	printk(KERN_ALERT "simple_char_device opened, times = %d\n", Device_Open);
	return 0;
}


int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	Device_Close++;
	printk(KERN_ALERT "simple_char_device closed, times = %d\n", Device_Close);
	return 0;
}


struct file_operations simple_char_driver_file_operations = {

	.owner   = THIS_MODULE,
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
	.read = simple_char_driver_read,
        .write = simple_char_driver_write,
        .open = simple_char_driver_open,
        .release = simple_char_driver_close,

};

static int __init  simple_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
	register_chrdev(200,"simple_char_driver",&simple_char_driver_file_operations);
	return 0;
}

static void  __exit simple_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
	unregister_chrdev(200,"simple_char_driver");
//	return 0;
}

/* add module_init and module_exit to point to the corresponding init and exit function*/

module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
