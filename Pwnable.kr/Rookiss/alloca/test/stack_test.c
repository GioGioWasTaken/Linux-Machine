#include <stdio.h>
#include <alloca.h>
int main(){
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	int value = 0xffffff00 -0x20;
	asm("nop");
	asm("nop");
	asm("nop");
	char * buffer = alloca(value);
	asm("nop");
	asm("nop");
	asm("nop");

}
