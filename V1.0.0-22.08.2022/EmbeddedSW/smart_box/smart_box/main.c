/* smart_box.c
*
* Created: 7/21/2022 9:01:57 PM
* Author : Muhammad_Ali
*/
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/wdt.h>
#include "system.h"

int main(void)
{
	wdt_enable(WDTO_2S);
	System_Init();
    
	while (1)
	{
		System_SmartBox();
		wdt_reset();
	}
}

