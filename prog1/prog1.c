#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isVar(char c);
bool isPower(char c);
bool isNum(char c);
bool isWhite(char c);
bool isPlus(char c);
bool isMinus(char c);

void parsePoly(List coeffs, List degrees, char* var);
void printPoly(List coeff, List degrees, char var);

int main(void) {
  List coeff_list1 = newList();
  List degree_list1 = newList();
  char var1;
  parsePoly(coeff_list1, degree_list1, &var1);
  printPoly(coeff_list1, degree_list1, var1);
  freeList(&coeff_list1);
  freeList(&degree_list1);
  return 0;
}

void parsePoly(List coeff_list, List degree_list, char *var) {
  bool negative = false;
  bool variable = false;
  int num_vars = 0;
  int num_coeffs = 0;
  int num_degrees = 0;
  int nums[5] = {0, 0, 0, 0, 0};
  int nums_index = 0;
  char poly[100];
  fgets(poly, sizeof(poly), stdin);
  // loops through one polynomial
  for (int i = 0; i < strlen(poly); i++) {
    char character = poly[i];
    // if we read in a variable add it to the variable count
    if (isVar(character)) {
      *var = character; 
      variable = true;
      num_vars++;
    }
    // if we read in a minus sign, we change the bool negative to true so that
    // the next number we read in will be converted to negative
    if (isMinus(character)) {
      negative = true;
    }

    // if we have read in a number
    // we add the number to an array where we will store all the digits of that
    // number
    else if (isNum(character)) {
      // printf("%c ", character);
      int num = character - '0'; // converts the character to an int
      nums[nums_index] = num;    // adds the int to the number array
      nums_index++; // updates the array index so that if there is another digit
                    // we can put it in the array
    }

    // if we read in a variable and there is no number that has been read in
    // right before it then the coeff is 1 or -1 so we append 1  or -1 to our
    // coeff list and update the num_coeffs
    else if (isVar(character) && nums[0] == 0) {
      if (negative) {
        appendList(coeff_list, -1);
        num_coeffs++;
        negative = false;
      } else {
        appendList(coeff_list, 1);
        num_coeffs++;
      }
    }
    // if we read in a variable and nums[0] != 0 that means that an entire
    // coefficient has been read in so we loop through the nums array and form
    // all the digits into a single number if there has been a negative sign
    // read in, we multiply the coeff by -1 and make negative false again then
    // we append the coeff to the coeff list and update the num_coeffs
    // then we reset the nums list back to all 0's
    else if ((isVar(character) || isWhite(character)) && nums[0] != 0) {
      int num = nums[0];
      // i starts at 1 because we set coeff to nums[0], i < nums_index + 1
      // because we only want to add the numbers up until the nums_index
      for (int i = 1; i < nums_index; i++) {
        num = num * 10 + nums[i];
      }
      if (negative) {
        num = num * -1;
        negative = false;
      }
      if (num_coeffs == 0 || num_coeffs == num_degrees) {
        appendList(coeff_list, num);
        num_coeffs++;

      } else if (num_degrees < num_coeffs) {
        appendList(degree_list, num);
        num_degrees++;
        variable = false;
      }
      for (int i = 0; i < 5; i++) {
        nums[i] = 0;
      }
      nums_index = 0;
    }
    // if we read in a whitespace character and there is no number that has been
    // read in right before it then the degree is 1 so we append 1 to our degree
    // list and update the num_degrees
    else if (isWhite(character) && variable == true && nums[0] == 0 &&
             num_degrees < num_coeffs) {
      appendList(degree_list, 1);
      num_degrees++;
      variable = false;
    }
    // if we read in a whitespace character and num_coeff > num_degrees, that
    // means the last term was a constant which means that the degree was 0, we
    // need to append 0 to our degree list and update the num_degrees in order
    // to keep our lists consistent
    else if (isWhite(character) && variable == false &&
             num_coeffs > num_degrees) {
      appendList(degree_list, 0);
      num_degrees++;
      variable = false;
    }
  }
  // to check for numbers at the end of the polynomial, we check if there are
  // numbers in the num array and if there are we figure out if they represent a
  // constant or a degree
  if (nums[0] != 0) {
    int num = nums[0];
    for (int i = 1; i < nums_index; i++) {
      num = num * 10 + nums[i];
    }
    if (negative) {
      num = num * -1;
      negative = false;
    }
    if (num_coeffs == 0 || num_coeffs == num_degrees) {
      appendList(coeff_list, num);
      num_coeffs++;
      appendList(degree_list,
                 0); // if its a constant, that means the degree is 0
      num_degrees++;
      variable = false;
    } else if (num_degrees < num_coeffs) {
      appendList(degree_list, num);
      num_degrees++;
      variable = false;
    }
    for (int i = 0; i < 5; i++) {
      nums[i] = 0;
    }
    nums_index = 0;
  } else if (num_degrees < num_coeffs) {
    appendList(degree_list, 1);
    num_degrees++;
    variable = false;
  }
}

void printPoly(List coeff_list, List degree_list, char var) {
  printList(coeff_list);
  printList(degree_list);
  List temp_coeffs = newList();
  List temp_degrees = newList();
  while (length(degree_list) > 0) {
    int max_index = max(degree_list);
    appendList(temp_degrees, delElement(degree_list, max_index)); //delete max element from degree list
  									 // and add it to temp_degrees
    appendList(temp_coeffs, delElement(coeff_list, max_index)); // do the same for corresponding coeff
  }
  printList(temp_degrees);
  printList(temp_coeffs);
  
  //Node *curr_degree = temp_degrees->head;
  //Node *curr_coeff = temp_coeffs->head;  
}

bool isVar(char c) { return (c >= 97 && c <= 122); }

bool isPower(char c) { return (c == 94); }

bool isNum(char c) { return (c >= 48 && c <= 57); }

bool isWhite(char c) { return (c == 9 || c == 32); }

bool isPlus(char c) { return (c == 43); }

bool isMinus(char c) { return (c == 45); }
