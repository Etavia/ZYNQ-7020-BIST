/*
 * networking_test.c
 *
 *  Created on: 6.12.2021
 *  Author: Tuomas Du-Ikonen
 *  SoC-FPGA course project work
 *  Real time video FPGA pipeline
 *  Networking Between PC and SoC-FPGA unit tests
 */

#include <stdio.h>
#include "../platform.h"
#include "../axi_dma.h"
#include "networking_test.h"

void run_networking_tests()
{
	xil_printf("NETWORKING TESTS STARTING\n");
	test_packet_address();
	test_copy32();
}

void test_packet_address()
{
    u32* data_out;
    u32* data_in;
    u32* rx_buff_addr = (u32*)0x01300000;
    u32* tx_buff_addr = (u32*)0x01100000;

    set_buffers();
    data_out = read_data_out();
    data_in = read_data_in();

    if (data_in == rx_buff_addr && data_out == tx_buff_addr)
    {
        xil_printf("Memory address test passed.\n");
    }
    else
    {
        xil_printf("Memory address test failed.\n");
    }
}

void test_copy32()
{
    u16_t n = 1000;
    u32 a[n];
    u32 b[n];

    u32* data = a;
    u32* new_data = b;

    copy32(data, new_data, n);

    int notequal = 1;
    for(int i = 0; i < n; i++)
    {
        if (new_data[i] == data[i])
        {
        }
        else
        {
            notequal = 0;
        }
    }

    if(notequal)
    {
        xil_printf("Image data copy test passed.\n");
    }
    else
    {
        xil_printf("Image data copy test failed.\n");
    }
}
