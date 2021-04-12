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

void parsePoly(List coeffs, List degrees, char poly[], char *var);
void sortPoly(List coeff_list, List degree_list, List save_coeffs_print, List save_degrees_print, List save_coeffs_mult, List save_degrees_mult);
void printPoly(List temp_coeffs, List temp_degrees, char var);
void polyMult(List coeffs1, List degrees1, List coeffs2, List degrees2, char var);

List store_coeffs1_print; //allows us to store coeffs of first polynomial to print
List store_degrees1_print; // allows us to store degrees of first polynomial to print

List store_coeffs1_mult; // allows us to store coeffs of first polynomial to multiply
List store_degrees1_mult; //allows us to store degrees of first polynomial to multiply

List store_coeffs2_print; // allows us to store coeffs of second polynomial to print
List store_degrees2_print; // allows us to store degrees of second polynomial to print

List store_coeffs2_mult; // allows us to store coeffs of second polynomial to multiply
List store_degrees2_mult; // allows us to store degrees of second polynomial to multiply

int main(void) {
  List coeff_list1 = newList();
  List degree_list1 = newList();
  store_coeffs1_print = newList();
  store_degrees1_print = newList();
  store_coeffs1_mult = newList();
  store_degrees1_mult = newList();
  char var1;
  char polynomial[1000];
  fgets(polynomial, sizeof(polynomial), stdin);
  parsePoly(coeff_list1, degree_list1, polynomial, &var1);
  sortPoly(coeff_list1, degree_list1, store_coeffs1_print, store_degrees1_print, store_coeffs1_mult, store_degrees1_mult);  
  printPoly(store_coeffs1_print, store_degrees1_print, var1);
  freeList(&coeff_list1);
  freeList(&degree_list1);
  freeList(&store_coeffs1_print);
  freeList(&store_degrees1_print);
  
  printList(store_coeffs1_mult);
  printList(store_degrees1_mult);
  
  // second polynomial
  List coeff_list2 = newList();
  List degree_list2 = newList();
  store_coeffs2_print = newList();
  store_degrees2_print = newList();
  store_coeffs2_mult = newList();
  store_degrees2_mult = newList();
  char var2;
  char poly2[1000];
  fgets(poly2, sizeof(poly2), stdin);
  parsePoly(coeff_list2, degree_list2, poly2, &var2);
  sortPoly(coeff_list2, degree_list2, store_coeffs2_print, store_degrees2_print, store_coeffs2_mult, store_degrees2_mult);
  printPoly(store_coeffs2_print, store_degrees2_print, var2);
  freeList(&coeff_list2);
  freeList(&degree_list2);
  freeList(&store_coeffs2_print);
  freeList(&store_degrees2_print);
  
  printList(store_coeffs2_mult);
  printList(store_degrees2_mult);

  // multiplication
  freeList(&store_coeffs1_mult);
  freeList(&store_degrees1_mult);
  freeList(&store_coeffs2_mult);
  freeList(&store_degrees2_mult);
  return 0;
}

void parsePoly(List coeff_list, List degree_list, char poly[], char *var) {
  bool negative = false;
  bool variable = false;
  int num_vars = 0;
  int num_coeffs = 0;
  int num_degrees = 0;
  int nums[5] = {0, 0, 0, 0, 0};
  int nums_index = 0;

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

void sortPoly(List coeff_list, List degree_list, List save_coeffs_print, List save_degrees_print, List save_coeffs_mult, List save_degrees_mult) {
  while (length(degree_list) > 0) {
    int max_index = max(degree_list);
    int curr_degree = delElement(degree_list, max_index);
    int curr_coeff = delElement(coeff_list, max_index);
    appendList(save_degrees_print, curr_degree); // store the degrees temporarily so we can print
    appendList(save_coeffs_print, curr_coeff); // store the coeffs temporarily so we can print 
    appendList(save_degrees_mult, curr_degree); // store the degrees temporarily so we can multiply
    appendList(save_coeffs_mult, curr_coeff); // store the coeffs temporarily so we can multiply
  }
}

void printPoly(List temp_coeffs, List temp_degrees, char var) {
  int term = 0; // to keep track of which term we are on
  while (length(temp_degrees) != 0) {
    int curr_degree = delElement(temp_degrees, 0);
    int curr_coeff = delElement(temp_coeffs, 0);  

    if (curr_degree == 0) {
      if (term == 0) {
        printf("%d", curr_coeff); // if degree = 0 and it's the first term
      } else {
        if (curr_coeff < 0) {
          printf(" - %d",
                 curr_coeff * -1); // if degree = 0 and it's not the first
                                   // term and the coeff is negative
        } else {
          printf(" + %d", curr_coeff); // if degree = 0 and it's not the first
                                       // term and the coeff is positive
        }
      }
    } else if (curr_degree == 1) {
      if (term == 0) {
        if (curr_coeff == -1) {
          printf(
              "-%c",
              var); // if degree = 1 and it's the first term and the coeff is -1
        } else if (curr_coeff == 1) {
          printf("%c",
                 var); // if degree = 1 and it's the first term and coeff is 1
        } else {
          if (curr_coeff < 0) {
            printf("-%d%c", curr_coeff * -1, var); // if degree = 1 and it's the
                                                   // first term and coeff is
                                                   // negative
          } else {
            printf("%d%c", curr_coeff, var); // if degree = 1 and it's the first
                                             // term and coeff is positive
          }
        }
      } else {
        if (curr_coeff == -1) {
          printf(
              " - %c",
              var); // if degree = 1 and it's not the first term and coeff is -1
        } else if (curr_coeff == 1) {
          printf(
              " + %c",
              var); // if degree = 1 and it's not the first term and coeff is 1
        } else {
          if (curr_coeff < 0) {
            printf(" - %d%c", curr_coeff * -1,
                   var); // if degree = 1 and it's not
                         // the first term and coeff is
                         // negative
          } else {
            printf(" + %d%c", curr_coeff, var); // if degree = 1 and it's not
                                                // the first term and coeff is
                                                // positive
          }
        }
      }
    } else {
      if (term == 0) {
        if (curr_coeff == -1) {
          printf("-%c^%d", var, curr_degree); // if degree > 1 and it's the
                                              // first term and coeff is -1
        } else if (curr_coeff == 1) {
          printf("%c^%d", var, curr_degree); // if degree > 1 and it's the first
                                             // term and coeff is 1
        } else {
          if (curr_coeff < 0) {
            printf("-%d%c^%d", curr_coeff * -1, var,
                   curr_degree); // if degree > 1 and it's the first term and
                                 // coeff is negative
          } else {
            printf("%d%c^%d", curr_coeff, var,
                   curr_degree); // if degree > 1 and it's the first term and
                                 // coeff is positive
          }
        }
      } else {
        if (curr_coeff == -1) {
          printf(" - %c^%d", var, curr_degree); // if degree > 1 and it's not
                                                // the first term and coeff is
                                                // -1
        } else if (curr_coeff == 1) {
          printf(" + %c^%d", var, curr_degree); // if degree > 1 and it's not
                                                // the first term and coeff is 1
        } else {
          if (curr_coeff < 0) {
            printf(" - %d%c^%d", curr_coeff * -1, var,
                   curr_degree); // if degree > 1 and it's not the first term
                                 // and coeff is negative
          } else {
            printf(" + %d%c^%d", curr_coeff, var,
                   curr_degree); // if degree > 1 and it's not the first term
                                 // and coeff is positive
          }
        }
      }
    }
    term++;
  }
  printf("\n");
}

void polyMult(List coeffs1, List degrees1, List coeffs2, List degrees2, char var) {  
}

bool isVar(char c) { return (c >= 97 && c <= 122); }

bool isPower(char c) { return (c == 94); }

bool isNum(char c) { return (c >= 48 && c <= 57); }

bool isWhite(char c) { return (c == 9 || c == 32); }

bool isPlus(char c) { return (c == 43); }

bool isMinus(char c) { return (c == 45); }
