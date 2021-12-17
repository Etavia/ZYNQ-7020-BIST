/*
 * networking_test.h
 *
 *  Created on: 6.12.2021
 *  Author: Tuomas Du-Ikonen
 *  SoC-FPGA course project work
 *  Real time video FPGA pipeline
 *  Networking Between PC and SoC-FPGA unit tests
 */

#ifndef SRC_TESTS_NETWORKING_TEST_H_
#define SRC_TESTS_NETWORKING_TEST_H_

void run_networking_tests();
void test_packet_address();
void set_buffers();
u32* read_data_out();
u32* read_data_in();
void test_copy32();
void copy32(u32* data, u32* new_data, u16_t n);

#endif /* SRC_TESTS_NETWORKING_TEST_H_ */
