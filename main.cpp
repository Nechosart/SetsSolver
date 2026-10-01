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
#include <sstream>

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
    string enter_value;
    int number;


    // 1.1. Input sets name and values
    while (variables_count < variables_max_count) {
        std::cout << "Enter your set name(Enter U to make universum), press Enter if want to input equation" << endl;
        getline(cin, variable_name);
        if (variable_name == "") {
            break;
        }
        variables_name[variables_count] = variable_name;

        std::cout << "Enter your set values, if want to stop then enter any letter" << endl;
        i = 0;
        variables_size[variables_count] = 0;

        if (getline(cin, enter_value)) {
            std::stringstream ss(enter_value);
            while (ss >> number) {
                variables[variables_count][i] = number;
                i++;
                variables_size[variables_count] = i;
            }
            cout << enter_value << endl;
        }

        if (variables_size[variables_count] == 0) {
            std::cout << "Error: no values in set, the set won't be added" << endl;
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
        variables[0][1] = 3;
        variables[0][2] = 4;

        variables_name[1] = "B";
        variables_size[1] = 4;
        variables[1][0] = 1;
        variables[1][1] = 2;
        variables[1][2] = 4;
        variables[1][3] = 5;

        variables_count = 2;
    }
    // 1.2. Input equation

    std::cout << "Rules:  no symbols:   ^   !^   !    =>    <=>   A   \\  " << endl;
    std::cout << "Rules: use English:  and  or  not  then  equal xor minus" << endl;
    std::cout << "Rules: use 1 space between variables/symbols, example: (A and B) then (not C)" << endl;
    std::cout << "Enter your equation (if you want standard one, press Enter)" << endl << endl;
    std::getline(std::cin, equation);
    if (equation == "") {
        equation = "((A or (A and B)) equal (A and (A or B))) and ((A or (A and B)) equal A)";
        //equation = "A or B or C equal C and B and A";
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
        std::cout << variables_name[enum_variable] << " = {";
        for (i = 0; i != variables_size[enum_variable]; i++) {
            if (i != 0) { std::cout << ", "; }
            std::cout << variables[enum_variable][i];
        }
        std::cout << "}" << endl;
        std::cout << "|" << variables_name[enum_variable] << "| = " << pow(2, variables_size[enum_variable]) << endl;
    }

    cout << equation << endl;
    int length = equation.length() + 2;
    equation.insert(0, 1, '(');
    equation.insert(length - 1, 1, ')');

    // 2. Declaration variables / arrays


    const int columns_max_count = variables_max_count * 4;
    const int objects_max_count = 16;
    string columns[columns_max_count][3 + objects_max_count];
    int columns_count = variables_count;
    for (i = 0; i != variables_count; i++) {
        columns[i][0] = variables_name[i];
        columns[i][1] = "variable";
    }

    // In order from most priorite to least
    int operations_count = 7;
    string operations[] =       { "not", "and", "or", "minus", "xor", "then", "equal" };
    int operations_argument[] = {   1,     0,    0,      2,      0,     2,       2 };


    bool current_operation_not_found, is_variable_new,
        is_variable_before_operation, previous_equal, is_column_new;
    int enum_operation, i_back, brackets_need_to_pass, enum_column, enum_object, enum_object1, enum_operation1;

    char element = ' ';
    string brackets_add = "";
    string object_found;
    string objects_found[objects_max_count];
    int objects_found_count;
    int objects_add_count, objects_start, objects_end, jump_over;

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
        std::cout << "Error: some brackets don't have pair";
        return 0;
    }
    i = 1;


    // 3. Main cycle : Getting columns


    while (i < length) {
        element = equation[i];

        if (element == ')') {


            // 3.1. Add column

            i_back = i - 1;
            object_found = "";
            objects_found_count = 0;
            brackets_need_to_pass = 1;

            // Finding all objects
            while (i_back >= 0 && brackets_need_to_pass > 0) {
                element = equation[i_back];

                if (element == '(') {
                    brackets_need_to_pass -= 1;
                } else if (element == ')') {
                    brackets_need_to_pass += 1;
                }

                if ((element == ' ' && brackets_need_to_pass == 1) || 
                    (element == '(' && brackets_need_to_pass == 0)) {
                    objects_found[objects_found_count] = object_found;
                    objects_found_count++;
                    object_found = "";
                }
                else {
                    object_found.insert(0, 1, element);
                }

                i_back -= 1;
            }

            /*
            for (i1 = objects_found_count - 1; i1 >= 0; i1-=1) {
                std::cout << objects_found[i1] << " ";
            }
            std::cout << endl;
            */

            for (enum_operation = 0; enum_operation != operations_count; enum_operation++) {
                for (enum_object = objects_found_count - 1; enum_object >= 0; enum_object -= 1) {
                    if (operations[enum_operation] == objects_found[enum_object]) {


                        objects_add_count = operations_argument[enum_operation];


                        if (operations_argument[enum_operation] == 1) {
                            objects_start = enum_object;
                            objects_end = enum_object - 1;
                            columns[columns_count][3] = objects_found[enum_object-1];

                        } 
                        else if (operations_argument[enum_operation] == 2) {
                            objects_start = enum_object + 1;
                            objects_end = enum_object - 1;
                            columns[columns_count][3] = objects_found[enum_object + 1];
                            columns[columns_count][4] = objects_found[enum_object - 1];

                        }
                        else {
                            objects_start = enum_object + 1;
                            objects_end = 0;
                            for (enum_object1 = enum_object-2; enum_object1 >= 0; enum_object1 -= 2) {
                                for (enum_operation1 = enum_operation + 1; enum_operation1 < operations_count; enum_operation1++) {
                                    if (operations[enum_operation1] == objects_found[enum_object1]) {
                                        objects_end = enum_object1 + 1;
                                        enum_object1 = 0;
                                        break;
                                    }
                                }
                            }
                            for (enum_object1 = objects_start; enum_object1 >= objects_end; enum_object1 -= 2) {
                                columns[columns_count][objects_add_count+3] = objects_found[enum_object1];
                                objects_add_count++;
                            }
                        }

                        // Writing main data
                        objects_add_count += 2;
                        columns[columns_count][1] = to_string(objects_add_count);
                        columns[columns_count][2] = objects_found[enum_object];

                        // Connecting all elements to caption
                        columns[columns_count][0] = objects_found[objects_start];
                        for (enum_object1 = objects_start-1; enum_object1 >= objects_end; enum_object1-=1) {
                            columns[columns_count][0] += " " + objects_found[enum_object1];
                        }
                        //std::cout << columns[columns_count][0] << endl;

                        // Converting all found objects to one, moving all past them to its level
                        objects_found[objects_end] = columns[columns_count][0];
                        jump_over = objects_start - objects_end;
                        objects_found_count -= jump_over;
                        for (enum_object1 = objects_end + 1; enum_object1 <= objects_found_count; enum_object1++) {
                            objects_found[enum_object1] = objects_found[enum_object1+jump_over];
                        }
                        enum_object -= enum_object - objects_end;
                        
                        // Adding new column
                        is_column_new = true;
                        for (enum_column = 0; enum_column != columns_count; enum_column++) {
                            if (columns[enum_column][0] == columns[columns_count][0]) {
                                is_column_new = false;
                                break;
                            }
                        }
                        if (is_column_new) {
                            columns_count++;
                        }
                    }
                }
            }

            // Add () to the last column
            columns[columns_count-1][0].insert(0, 1, '(');
            columns[columns_count-1][0].push_back(')');
        }

        i++;
    }


    // If operations not found
    bool is_operation_found = false;
    for (i = 0; i < columns_count; i++) {
        if (columns[i][2] != "variable" && columns[i][2] != "") {
            is_operation_found = true;
            break;
        }
    }
    if (is_operation_found == false) {
        std::cout << "Error: no operations found";
        return 0;
    }


    // 4. Calculating values of columns and outputting them
    bool values[columns_max_count][variables_elements_max_count];
    int x, i_search;
    bool value = true;

    // Write variables
    for (x = 0; x != variables_count; x++) {
        std::cout << columns[x][0] << "  =  ";
        for (i = 0; i != universum_size; i++) {
            value = variables_boolean[x][i];
            values[x][i] = value;
            if (value) { std::cout << "1"; }
            else { std::cout << "0"; }
        }
        std::cout << endl;
    }

    // Write values
    bool value1 = true;
    bool value2 = true;
    string operation;
    int objects_count;
    int columns_id[3+objects_max_count];

    for (x = variables_count; x != columns_count; x++) {
        objects_count = stoi(columns[x][1]);
        for (enum_object = 3; enum_object <= objects_count; enum_object++) {
            for (enum_column = 0; enum_column != x; enum_column++) {
                if (columns[enum_column][0] == columns[x][enum_object]) {
                    columns_id[enum_object] = enum_column;
                    break;
                }
            }
        }

        operation = columns[x][2];

        std::cout << endl << endl << columns[x][0] << "  =  ";
        for (i = 0; i != universum_size; i++) {
            value = values[columns_id[3]][i];
            if (operation == "not") {
                value = !value;
            }
            else {
                for (enum_object = 4; enum_object <= objects_count; enum_object++) {
                    value2 = values[columns_id[enum_object]][i];

                    if (operation == "and") {
                        value = value && value2;
                    }
                    else if (operation == "or") {
                        value = value || value2;
                    }
                    else if (operation == "then") {
                        value = (!value) || value2;
                    }
                    else if (operation == "equal") {
                        value = value == value2;
                    }
                    else if (operation == "xor") {
                        value = (value || value2) != (value && value2);
                    }
                    else if (operation == "minus") {
                        value = value && (value2 == false);
                    }
                }
            }

            values[x][i] = value;
            std::cout << value;
        }
    }
    std::cout << endl;
    std::cout << columns[columns_count - 1][0] << " = {";
    int elements_count = 0;
    for (i = 0; i != universum_size; i++) {
        if (values[columns_count - 1][i]) {
            if (elements_count != 0) { std::cout << ", "; }
            std::cout << universum[i];
            elements_count++;
        }
    }
    std::cout << "}" << endl;
    std::cout << "|set| = " << pow(2, elements_count) << endl;
    std::cout << endl << endl;

    /**/
    return 0;
}
