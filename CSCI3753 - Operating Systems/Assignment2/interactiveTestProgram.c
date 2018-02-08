//interactiveTestProgram.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayMenu()
{
	printf("\nPress r to read from device\nPress w to write to the device\nPress e to exit from device\nPress anything to keep reading or writing from the device\n");
}

void readfromdevice()
{
	FILE *devicefile;

//	printf("Data read from device:\n");
	char data[1024];
	devicefile = fopen("/dev/simple_char_device","r");
	if( devicefile != NULL){
		int i = 0;
		printf("Data read from device:\n");
		fgets(data, 1024, devicefile);
		printf("%s\n", data);
	}
	fclose(devicefile);
}

void writetodevice()
{
	FILE *devicefile;
	char data[1024];
	printf("Enter data you want to write to the device\n");
	devicefile = fopen("/dev/simple_char_device","a");
	fgets(data,1024,stdin);
	fputs(data,devicefile);
	fclose(devicefile);
	printf("\n");
}

int main(int argc,char *argv[])
{
	if(argc > 1){
		printf("Usage: itp <nothing>\n argc = %d", argc);
		return 1;
	}

	char input[1024];
	while(1 == 1)
	{
		if(input[0] == 'e' /*&& input[1] == '\n'*/){
			printf("exiting device\n");
			break;
		}
		if(input[0] == 'r' /*&& input[1] == '\n'*/){
//			printf("reading from device\n");
			readfromdevice();
		}
		if(input[0] == 'w' /*&& input[1] == '\n'*/){
//			printf("writing to device\n");
			writetodevice();
		}
		
//		printf("input = %s", input);
		*input = '\0';
//		printf("input = %s\n", input);
		displayMenu();
		printf("Enter command: ");
		
		fgets(input,1024,stdin);
		input[(int)strlen(input)-1] = '\0';
		
		//input = '\0';
//		printf("exited from loop\n");
	}
	return 0;
}
