/*
 * Selftest.c
 *
 *  Created on: 4.6.2021
 *  Author: Tuomas Du-Ikonen
 *  SoC-FPGA course project work
 *  Real time video FPGA pipeline
 *  Built In Self Test (BIST)
 */

#include "Selftest.h"

void SelfTest_Execute()
{
	int result;
	printf("Start built in self test\n\n");

	result = SelfTest_Run();

	if(result == 0)
	{
		printf("\nBIST OK\n");
	}
	else
	{
		printf("\nBIST failed. Program execution terminated.\n");
		exit(0);
	}

}

int SelfTest_Run()
{
	int result = 0;
	XGpio gpio;
	u32 led;
	int biststatus = 2;
	int runtests = 1;

	// Pointers for errors
	/*
	Mismatch error flag from the BIST Checker. 1 bit
	per data slice.
	1'b1: Pattern mismatch error
	1'b0: All patterns matched
	This is a sticky flag. In order to clear this bit, port
	reg_phy_bist_err_clr must be set HIGH. Note that
	reg6b is unused.
	*/
	int *phybisterr = 0xF80061B0;

	/*
	Error Status
	Indicates the error status of the CAN controller.
	00: Indicates Configuration Mode (CONFIG = 1).
	Error State is undefined.
	01: Indicates Error Active State.
	11: Indicates Error Passive State.
	10: Indicates Bus Off State.
	 */
	int *canerr0 = 0xE0008018;
	int *canerr1 = 0xE0009018;

	/*
	Set to 1 when an uncorrectable ECC error is
	captured. As long as this is a 1, no further ECC
	errors will be captured. This is cleared when a 1 is
	written to register bit[0] of ECC CONTROL
	REGISTER (0x31).
	 */
	int *eccerr = 0xF80060DC;

	/*
	System Error (EHCI). AHB interconnect.
	0: no error detected.
	1: AHB error received (write 1 to clear)
	 */
	int *usberr0 = 0xE0002144;
	int *usberr1 = 0xE0003144;

	XGpio_Initialize(&gpio, 0);

	XGpio_SetDataDirection(&gpio, 1, 0x00000000); // set LED GPIO channel tristates to All Output

	led = 0x00000000; // Set rgb led off

	if (runtests > 0)
	{
		led = Gpio_SetLeds(3);
		XGpio_DiscreteWrite(&gpio, 1, led); // Set led color yellow while running tests

		// Checking states related to BIST
		if ((*phybisterr & (0<<0)) != 0) // If first bit is not equal to zero..
		{
			biststatus = 1;
			result = 1;
			printf("BIST pattern mismatch check\t\t\t\t\t\t\t\t\t\tFAILED\n");
		}
		else
		{
			printf("BIST pattern mismatch check\t\t\t\t\t\t\t\t\t\tPASSED\n");
		}

		if ((*canerr0 & (7<<1)) == 1) // If 7th bit is equal to one...
		{
			biststatus = 1;
			result = 1;
			printf("CAN 0 controller test\t\t\t\t\t\t\t\t\t\t\t\t\tFAILED\n");
		}
		else
		{
			printf("CAN 0 controller test\t\t\t\t\t\t\t\t\t\t\t\t\tPASSED\n");
		}

		if ((*canerr1 & (7<<1)) == 1)
		{
			biststatus = 1;
			result = 1;
			printf("CAN 1 controller test\t\t\t\t\t\t\t\t\t\t\t\t\tFAILED\n");
		}
		else
		{
			printf("CAN 1 controller test\t\t\t\t\t\t\t\t\t\t\t\t\tPASSED\n");
		}

		if ((*eccerr & (0<<0)) != 0)
		{
			biststatus = 1;
			result = 1;
			printf("Uncorrectable ECC error test\t\t\t\t\t\t\t\t\t\tFAILED\n");
		}
		else
		{
			printf("Uncorrectable ECC error test\t\t\t\t\t\t\t\t\t\tPASSED\n");
		}

		if ((*usberr0 & (4<<0)) != 0)
		{
			biststatus = 1;
			result = 1;
			printf("AHB USB0 interconnect system error (EHCI) test\t\tFAILED\t\n");
		}
		else
		{
			printf("AHB USB0 interconnect system error (EHCI) test\t\tPASSED\n");
		}

		if ((*usberr1 & (4<<0)) != 0)
		{
			biststatus = 1;
			result = 1;
			printf("AHB USB1 interconnect system error (EHCI) test\t\tFAILED\n");
		}
		else
		{
			printf("AHB USB1 interconnect system error (EHCI) test\t\tPASSED\n");
		}
		runtests = 0;
	}

	led = Gpio_SetLeds(biststatus); // Set led color
	XGpio_DiscreteWrite(&gpio, 1, led);

	return result;
}

u32 Gpio_SetLeds(int color)
{
	u32 led = 0x00000000;

	if (color == 1) // Red
	{
		led = 0x00000020;
	}
	else if (color == 2) // Green
	{
		led = 0x00000090;
	}
	else if (color == 3) // Yellow
	{
		led = 0x000000B0;
	}
	else // Lights off
	{
		led = 0x00000000;
	}

	return led;
}

