/*
Виконав студент групи ШІ-12
Нечай Артем
Автоматичне обчислення логічних операцій над множининами
для довільного вводу



----Algorithm plan----

1. Input sets and equation
    1.1. Input sets name and values
    1.2. Input equation
    1.3. Fill universum array with all unique elements from variables arrays
    1.4. Fill variables_boolean array with true/false values for each variable of universum
    1.5. Output variables, their values, and their power
2. Declaration variables/arrays
3. Main cycle: Getting columns
    3.1. Add column
4. Calculating values of columns and outputting them

----   End plan   ----
*/


#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    // 1. Input sets and equation
    const int variables_max_count = 8;
    const int variables_elements_max_count = 64;
    string variables_name[variables_max_count];
    int variables_size[variables_max_count];
    int variables[variables_max_count][variables_elements_max_count];
    bool variables_boolean[variables_max_count][variables_elements_max_count];
    int variables_count = 0;
    int i = 0;
    string variable_name;


    // 1.1. Input sets name and values
    while (variables_count < variables_max_count) {
        std::cout << "Enter your set name(Enter U to make universum), press Enter if want to input equation" << endl;
        getline(cin, variable_name);
        if (variable_name == "") {
            break;
        }
        variables_name[variables_count] = variable_name;

        cout << "Enter your set values, if want to stop then enter any letter" << endl;
        i = 0;
        while (true) {
            variables_size[variables_count] = i;
            cin >> variables[variables_count][i];
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                break;
            }
            i++;
        }
        if (variables_size[variables_count] == 0) {
            cout << "Error: no values in set, the set won't be added" << endl;
        }
        else {
            variables_count++;
        }
    }

    int universum[variables_elements_max_count];
    int universum_size = 0;
    int enum_variable, diap_mid, diap1, diap2, element_position, is_new_element, element_number, i1;
    string equation;

    if (variables_count == 0) {
        // Standard equation

        variables_name[0] = "A";
        variables_size[0] = 3;
        variables[0][0] = 1;
        variables[0][1] = 2;
        variables[0][2] = 3;

        variables_name[1] = "B";
        variables_size[1] = 4;
        variables[1][0] = 1;
        variables[1][1] = 3;
        variables[1][2] = 4;
        variables[1][3] = 5;

        variables_count = 2;
        equation = "((A or (A and B)) equal (A and (A or B))) and ((A or (A and B)) equal A)";
    }
    else {
        // 1.2. Input equation

        std::cout << "Rules:  no symbols:   ^   !^   !    =>    <=>   A   \\  " << endl;
        std::cout << "Rules: use English:  and  or  not  then  equal xor minus" << endl;
        std::cout << "Rules: use 1 space between variables/symbols, example: (A and B) then (not C)" << endl;
        std::cout << "Enter your equation (if you want standard one, press Enter)" << endl << endl;
        std::getline(std::cin, equation);
        while (equation == "") {
            std::cout << "No equation entered" << endl;
            std::getline(std::cin, equation);
        }
    }

    // 1.3. Fill universum array with all unique elements from variables arrays
    // sort numbers by dividing range in 2
    for (enum_variable = 0; enum_variable != variables_count; enum_variable++) {
        for (i = 0; i != variables_size[enum_variable]; i++) {
            element_number = variables[enum_variable][i];
            is_new_element = true;
            element_position = 0;

            if (universum_size != 0) {
                diap1 = 0;
                diap2 = universum_size - 1;
                while (diap2 != diap1) {
                    diap_mid = diap1 + (diap2 - diap1) / 2;
                    if (element_number <= universum[diap_mid]) {
                        diap2 = diap_mid;
                    }
                    else {
                        diap1 = diap_mid + 1;
                    }
                }
                if (element_number == universum[diap1]) {
                    is_new_element = false;
                }
                else if (element_number < universum[diap1]) {
                    element_position = diap1;
                }
                else {
                    element_position = diap1 + 1;
                }
            }

            if (is_new_element) {
                // Adding new element to universum array in sorted position

                if (universum_size != 0) {
                    for (i1 = universum_size; i1 != element_position; i1 -= 1) {
                        universum[i1] = universum[i1 - 1];
                    }
                }
                universum[element_position] = element_number;
                universum_size++;
            }
        }
    }

    // 1.4. Fill variables_boolean array with true/false values for each variable of universum
    for (enum_variable = 0; enum_variable != variables_count; enum_variable++) {
        for (i = 0; i != universum_size; i++) {
            variables_boolean[enum_variable][i] = false;
        }
    }
    for (i = 0; i != universum_size; i++) {
        for (enum_variable = 0; enum_variable != variables_count; enum_variable++) {
            for (i1 = 0; i1 != variables_size[enum_variable]; i1++) {
                if (universum[i] == variables[enum_variable][i1]) {
                    variables_boolean[enum_variable][i] = true;
                    break;
                }
            }
        }
    }

    // 1.5. Output variables, their values, and their power
    for (enum_variable = 0; enum_variable != variables_count; enum_variable++) {
        cout << variables_name[enum_variable] << " = {";
        for (i = 0; i != variables_size[enum_variable]; i++) {
            if (i != 0) { cout << ", "; }
            cout << variables[enum_variable][i];
        }
        cout << "}" << endl;
        cout << "|" << variables_name[enum_variable] << "| = " << pow(2, variables_size[enum_variable]) << endl;
    }

    int length = equation.length() + 2;
    equation.insert(0, 1, '(');
    equation.insert(length - 1, 1, ')');

    // 2. Declaration variables / arrays


    const int columns_max_count = variables_max_count * 4;
    string columns[columns_max_count][4];
    int columns_count = variables_count;
    for (i = 0; i != variables_count; i++) {
        columns[i][0] = variables_name[i];
        columns[i][1] = "variable";
    }

    string operations[] = { "not", "and", "or", "then", "equal", "xor", "minus" };
    int operations_count = 7;


    bool current_operation_not_found, is_variable_new,
        is_variable_before_operation, previous_equal, is_column_new;
    int current_operation_i, operation_enum, i_back,
        brackets_need_to_pass, operation_name_length, i_check, enum_column;

    char element = ' ';
    string variable = "";
    string variable_before_operation = "";
    string operation = "";
    string brackets_add = "";

    // If brackets count doesn't match
    brackets_need_to_pass = 0;
    for (i = 0; i < length; i++) {
        element = equation[i];
        if (element == '(') {
            brackets_need_to_pass += 1;
        }
        else if (element == ')') {
            brackets_need_to_pass -= 1;
        }
    }
    if (brackets_need_to_pass != 0) {
        cout << "Error: some brackets don't have pair";
        return 0;
    }
    i = 1;


    // 3. Main cycle : Getting columns


    while (i < length) {
        element = equation[i];

        if (element == ')') {


            // 3.1. Add column

            brackets_add = ")";
            i_back = i - 1;
            variable_before_operation = "";
            is_variable_before_operation = false;
            current_operation_i = 0;
            brackets_need_to_pass = 1;
            // Going backwards to find the beginning of THAT ')'
            // brackets_need_to_pass -- program can get on another ')' and 
            // then '(' which program could missread as THAT ')' beginning
            // example: (A and (B or C))
            // 
            // without brackets_need_to_pass: (A and (B or C))
            //                                       * End
            //                  we will end up with: (B or C))
            // 
            // with brackets_need_to_pass: (A and (B or C))
            //                             * End
            //           we will end up with: (A and (B or C))

            while (i_back >= 0 && brackets_need_to_pass > 0) {
                element = equation[i_back];
                brackets_add.insert(0, 1, element);


                if (is_variable_before_operation) {
                    variable_before_operation.insert(0, 1, element);
                }

                if (element == '(') {
                    brackets_need_to_pass -= 1;
                }
                else {

                    if (element == ')') {
                        brackets_need_to_pass += 1;
                    }
                    else if (brackets_need_to_pass == 1 && is_variable_before_operation == false) {
                        if (element == ' ') {
                            current_operation_i = 0;
                            variable = brackets_add;
                            variable.erase(0, 1);
                            variable.pop_back();
                            // Economing time
                        }
                        else {
                            // For situations like that: (A then (B or C))
                            // 'then' will be lost because lastOperation is 'or'
                            current_operation_not_found = true;
                            for (operation_enum = 0; operation_enum != operations_count; operation_enum++) {

                                operation_name_length = operations[operation_enum].length();
                                if (operation_name_length > current_operation_i) {

                                    // Check if all of the previous and current elements is
                                    // equal to operations[operation_enum] elements
                                    previous_equal = true;
                                    for (i_check = 0; i_check != current_operation_i + 1; i_check++) {
                                        if (operations[operation_enum][operation_name_length - 1 - i_check] != equation[i_back + current_operation_i - i_check]) {
                                            previous_equal = false;
                                        }
                                    }
                                    if (previous_equal) {
                                        current_operation_not_found = false;
                                        if (current_operation_i + 1 == operation_name_length && equation[i_back - 1] == ' ') {
                                            current_operation_i = 0;
                                            operation = operations[operation_enum];
                                            if (operation != "not") {
                                                // Skip next element so in the next cycle
                                                // it was not missread as 3.2 Add column
                                                i_back -= 1;
                                                brackets_add.insert(0, 1, ' ');
                                                // Operation is found so lastly we need to find
                                                // variable before it so we add every element that comes before
                                                is_variable_before_operation = true;
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                            if (current_operation_not_found) {
                                // Previous and current elements is not
                                // any operations
                                current_operation_i = 0;
                            }
                            else {
                                // 
                                current_operation_i++;
                            }
                        }
                    }
                }
                i_back -= 1;
            }

            // Adding found to columns
            is_column_new = true;
            for (enum_column = 0; enum_column != columns_count; enum_column++) {
                if (columns[enum_column][0] == brackets_add) {
                    is_column_new = false;
                    break;
                }
            }
            if (is_column_new) {
                columns[columns_count][0] = brackets_add;
                columns[columns_count][1] = operation;
                columns[columns_count][2] = variable;
                // If operator require variable before and after
                if (operation != "not") {
                    variable_before_operation.erase(0, 1);
                    columns[columns_count][3] = variable_before_operation;
                }
                columns_count++;
            }
        }

        i++;
    }


    // If operations not found
    bool is_operation_found = false;
    for (i = 0; i < columns_count; i++) {
        if (columns[i][1] != "variable" && columns[i][1] != "") {
            is_operation_found = true;
            break;
        }
    }
    if (is_operation_found == false) {
        cout << "Error: no operations found";
        return 0;
    }


    // 4. Calculating values of columns and outputting them
    bool values[columns_max_count][variables_elements_max_count];
    int x, i_search;
    bool value = true;

    // Write variables
    for (x = 0; x != variables_count; x++) {
        cout << columns[x][0] << "  =  ";
        for (i = 0; i != universum_size; i++) {
            value = variables_boolean[x][i];
            values[x][i] = value;
            if (value) { std::cout << "1"; }
            else { std::cout << "0"; }
        }
        cout << endl;
    }

    // Write values
    bool value1 = true;
    bool value2 = true;
    int column1_position = 0;
    int column2_position = 0;

    for (x = variables_count; x != columns_count; x++) {
        cout << endl << endl << columns[x][0] << "  =  ";
        for (i_search = 0; i_search != x; i_search++) {
            if (columns[x][2] == columns[i_search][0]) {
                column2_position = i_search;
                break;
            }
        }

        operation = columns[x][1];
        if (operation != "not") {
            for (i_search = 0; i_search != x; i_search++) {
                if (columns[x][3] == columns[i_search][0]) {
                    column1_position = i_search;
                    break;
                }
            }
        }

        for (i = 0; i != universum_size; i++) {
            value2 = values[column2_position][i];
            if (operation == "not") {
                value = !value2;
            }
            else {
                value1 = values[column1_position][i];

                if (operation == "and") {
                    value = value1 && value2;
                }
                else if (operation == "or") {
                    value = value1 || value2;
                }
                else if (operation == "then") {
                    value = (!value1) || value2;
                }
                else if (operation == "equal") {
                    value = value1 == value2;
                }
                else if (operation == "xor") {
                    value = (value1 || value2) != (value1 && value2);
                }
                else if (operation == "minus") {
                    value = value1 && (value2 == false);
                }
            }

            values[x][i] = value;
            std::cout << value;
        }
    }
    std::cout << endl;
    std::cout << columns[columns_count - 1][0] << " = {";
    bool first_char = true;
    for (i = 0; i != universum_size; i++) {
        if (values[columns_count - 1][i]) {
            if (first_char == false) { std::cout << ", "; }
            else { first_char = false; }
            std::cout << universum[i];
        }
    }
    std::cout << "}" << endl;
    std::cout << endl << endl;

    /**/
    return 0;
}
