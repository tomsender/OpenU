#include "utils.h"


#define NUM_LABEL_ERRORS 4

/*
 * This enum used in the function that validates the label
 */

typedef enum{
	PASSED, /*Valid label*/
	TOO_LONG, /*invalid - more than max length*/
	FIRST_CHAR, /*invalid - label starts with invalid char*/
	INV_CHAR, /*invalid - invalid char was found (not a letter or a number)*/
	RESERVED /*invalid - label is command name*/
}label_val_status;

typedef struct label_status * label_status_ref;

typedef struct label_status{
	Bool TOO_LONG;
	Bool INV_FIRST_CHAR;
	Bool INV_CHAR_FOUND;
	Bool RESERVED;
	Bool VALID_LABEL;
}label_status;

typedef struct mat_status_report * mat_status_report_ref;
typedef struct mat_status_report{
	Bool inv_n_brackets;
	Bool inv_char_in_brackets;
	Bool syntax_error;
	Bool inv_label_found;
	Bool inv_registry_found;
	Bool valid_mat;
}mat_status_report;



label_status_ref initialize_label_struct();




Bool validate_file(parsed_item_ptr, int);

label_status_ref validate_label (String);
void print_label_errors(label_status_ref, parsed_item, list_item_reference*);

void mat_validation_errors(mat_status_report_ref errors, parsed_item item);

void validate_instruction(parsed_item* item, list_item_reference *);

Bool validate_operation(parsed_item* item, list_item_reference *, String);


/*Validate inst operators*/
void validate_ins_data (parsed_item* item, list_item_reference *);

void validate_ins_string (parsed_item* item, list_item_reference*  head);

/*void validate_ins_mat(body* item, list_item_reference*  head);*/

mat_status_report_ref validate_ins_mat(parsed_item* item);
Bool validate_mat_as_operand(String);

void validate_ins_entry(parsed_item* item, list_item_reference*  head, char *);

void validate_ins_extern(parsed_item* item, list_item_reference*  head, String);














void validate_oper_operands (parsed_item* item, list_item_reference *, String);

Operand_type get_operand_type (String operand);






Bool is_instructional_command(String );

Bool is_operational_command(String str);

Bool is_register(String str);

Bool is_valid_letter(char c);

Bool is_lowcase(char c);

Bool is_white_char (char c);

Bool is_string_lowercase(String str);

Bool is_valid_number (String );


Bool operand_match_commad(String command, Operand_type type);

int extract_number (String);


