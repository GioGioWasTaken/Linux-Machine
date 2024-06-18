#include <stdio.h>
#include <alloca.h>
#include <string.h>
int g_canary;
int main(){
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	int size = 0xffffff00 -0x20;
	asm("nop");
	asm("nop");
	asm("nop");
	char * buffer = alloca(size+4);
	asm("nop");
	asm("nop");
	asm("nop");
        scanf("%d", &g_canary);
	asm("nop");
	asm("nop");
	asm("nop");
	memcpy(buffer+size, &g_canary, 4);	// canary will detect overflow.
	asm("nop");
	asm("nop");
	asm("nop");
	return 0;
}
