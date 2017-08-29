/*
 * second_scan.h
 *
 *  Created on: Aug 27, 2017
 *      Author: alexz
 */

#ifndef SECOND_SCAN_H_
#define SECOND_SCAN_H_

#include "utils.h"
#include "operation_dictionary.h"
#include "first_scan.h"
#include "constants.h"

Bool second_scan (bodyArray,int,symbol_ptr*,int );

int get_opcode(String);

int code_command_line(int opcode,Operand_type op1, Operand_type op2, int rea);

#endif /* SECOND_SCAN_H_ */
