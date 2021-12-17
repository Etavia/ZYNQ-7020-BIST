# ZYNQ-7020-BIST
ZYNQ-7020-BIST Zynq-7020 Development Board Built-In-Self-Test (BIST). BIST checks some critical memory-mapped registers from Zynq SoC and prints test results to terminal. When program starts yellow light is lit. If all test pass, green light is lit on Zynq board. If even single test fails, red light is lit and program execution ends immediately.

This project should not be considered as comprehensive method to test Zynq board health. It demonstrates Vivado 2018.2 project for Zynq-7020 board, basic block design, RGB led control and reading memory-mapped registers.

Instructions and prerequisites for using this project
1. Download Vivado 2018.2. Using exactly same version is recommended since different versions of Vivado are know to have compatibility issues.
2. Block design is developed for Zynq-7020 development board Familiarity with Vivado development environment.
3. See Xilinx documentation and tutorials for this.

unit_tests folder contains unit tests for Networking Between PC and SoC-FPGA.

Instructions for using unit tests
1. Create project “Networking between PC and SoC-FPGA” by downloading it from: https://github.com/squarematr1x/Networking-between-PC-and-SoC-FPGA and follo instructions.
2. Move networking_test.c and networking_test.h to folder “..\Networking-between-PC-and-SoC-FPGA\server\tests”
3. Edit “..\Networking-between-PC-and-SoC-FPGA\server\networking.c” source file
void print_app_header() {
#if (LWIP_IPV6==0)
    xil_printf("\n\r\n\r-----lwIP TCP ICAT3170 server ------\n\r");
#endif
}

void set_buffers() {
    data_in = (u32*) RX_BUFFER_BASE;
    data_out = (u32*) TX_BUFFER_BASE;
    data_in = (u32*)0x1;
}

u32* read_data_in() {   <- Add this

    return data_in;
}

u32* read_data_out() {
    return data_out;
}

/* Append new data to the end of previously received data (not in use atm) */
void append8(u8* raw_data, u8* new_data, u16_t n) {
    for (int i = 0; i < n; i++) {
        raw_data[last_i] = new_data[i];
        last_i++;
    }
}

4. Edit “..\Networking-between-PC-and-SoC-FPGA\server\main.c” source file
#include <stdio.h>

#include "xparameters.h"

#include "netif/xadapter.h"

#include "platform.h"
#include "platform_config.h"
#if defined (__arm__) || defined(__aarch64__)
#include "xil_printf.h"
#endif

#include "lwip/tcp.h"
#include "xil_cache.h"

#include "tests\networking_test.h" <- Add this

#if LWIP_IPV6==1
#include "lwip/ip.h"
#else
#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif
#endif

and

#if LWIP_IPV6==0
#if LWIP_DHCP==1
    ipaddr.addr = 0;
    gw.addr = 0;
    netmask.addr = 0;
#else
    // initliaze IP addresses to be used
    IP4_ADDR(&ipaddr,  192, 168,   1, 10);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      192, 168,   1,  1);
#endif  
#endif

    run_networking_tests(); <- Add this

    print_app_header();

    lwip_init();


4. Run main.c. Test results are printed to terminal.
