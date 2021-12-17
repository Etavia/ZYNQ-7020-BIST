# ZYNQ-7020-BIST
ZYNQ-7020-BIST Zynq-7020 Development Board Built-In-Self-Test (BIST). BIST checks some critical memory-mapped registers from Zynq SoC and prints test results to terminal. When program starts yellow light is lit. If all test pass, green light is lit on Zynq board. If even single test fails, red light is lit and program execution ends immediately.

This project should not be considered as comprehensive method to test Zynq board health. It demonstrates Vivado 2018.2 project for Zynq-7020 board, basic block design, RGB led control and reading memory-mapped registers.

Instructions and prerequisites for using this project
1. Download Vivado 2018.2. Using exactly same version is recommended since different versions of Vivado are know to have compatibility issues.
2. Block design is developed for Zynq-7020 development board Familiarity with Vivado development environment.
3. See Xilinx documentation and tutorials for this.

unit_tests folder contains unit tests for Networking Between PC and SoC-FPGA.

Instructions for using unit tests
1. Create project “Networking between PC and SoC-FPGA” by downloading it from: https://github.com/squarematr1x/Networking-between-PC-and-SoC-FPGA and follow instructions.
2. Move networking_test.c and networking_test.h to folder “..\Networking-between-PC-and-SoC-FPGA\server\tests”
3. Edit “..\Networking-between-PC-and-SoC-FPGA\server\networking.c” source file by adding two functions more

u32* read_data_in() {return data_in;}

u32* read_data_out() {return data_out;}

4. Edit “..\Networking-between-PC-and-SoC-FPGA\server\main.c” source file by including header networking_test.h to line 48 for example and call function run_networking_tests() for example in line 165

5. Run main.c. Test results are printed to terminal.
