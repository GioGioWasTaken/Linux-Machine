#include <stdio.h>
int main(){
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	char buffer[10];
	asm("nop");
	asm("nop");
	asm("nop");
	fgets(buffer,0xffffff00, stdin);
	asm("nop");
	asm("nop");
	asm("nop");
}
