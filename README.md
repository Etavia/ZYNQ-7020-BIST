# ZYNQ-7020-BIST
ZYNQ-7020-BIST Zynq-7020 Development Board Built-In-Self-Test (BIST). BIST checks some critical memory-mapped registers from Zynq SoC and prints test results to terminal. When program starts yellow light is lit. If all test pass, green light is lit on Zynq board. If even single test fails, red light is lit and program execution ends immediately.

This project should not be considered as comprehensive method to test Zynq board health. It demonstrates Vivado 2018.2 project for Zynq-7020 board, basic block design, RGB led control and reading memory-mapped registers.

Instructions and prerequisites for using this project
1. Download Vivado 2018.2. Using exactly same version is recommended since different versions of Vivado are know to have compatibility issues.
2. Block design is developed for Zynq-7020 development board Familiarity with Vivado development environment.
3. See Xilinx documentation and tutorials for this.
