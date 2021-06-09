/*
 * Selftest.h
 *
 *  Created on: 4.6.2021
 *  Author: Tuomas Du-Ikonen
 *  SoC-FPGA course project work
 *  Real time video FPGA pipeline
 *  Built In Self Test (BIST)
 */

#ifndef SRC_SELFTEST_H_
#define SRC_SELFTEST_H_

//AXI GPIO driver
#include "xgpio.h"

//send data over UART
#include "xil_printf.h"

// Function declarations
u32 Gpio_SetLeds(int color);
void SelfTest_Execute();
int SelfTest_Run();

#endif /* SRC_SELFTEST_H_ */
