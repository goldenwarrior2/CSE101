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
void sortPoly(List coeff_list, List degree_list, List temp_coeffs, List temp_degrees);
void printPoly(List temp_coeffs, List temp_degrees, char var);
void polyMult(List coeffs1, List degrees1, List coeffs2, List degrees2);
void polySimplify(List coeffs, List degrees);

List simp_coeffs; //holds simplified coeffs
List simp_degrees; //holds simplified degrees
List mult_coeffs; // holds multiplied coeffs
List mult_degrees; // holds multiplied degrees
List temp_coeffs1; // holds coeffs of first poly
List temp_degrees1; // holds degrees of first poly
List temp_coeffs2; // holds coeffs of second poly
List temp_degrees2; // holds degrees of second poly

int main(void) {
  List coeff_list1 = newList();
  List degree_list1 = newList();
  temp_coeffs1 = newList();
  temp_degrees1 = newList();
  char var;
  char polynomial[1000];
  fgets(polynomial, sizeof(polynomial), stdin);
  parsePoly(coeff_list1, degree_list1, polynomial, &var);
  sortPoly(coeff_list1, degree_list1, temp_coeffs1, temp_degrees1);
  printPoly(temp_coeffs1, temp_degrees1, var);
  printf("multiply by\n");

  // second polynomial
  List coeff_list2 = newList();
  List degree_list2 = newList();
  temp_coeffs2 = newList();
  temp_degrees2 = newList();
  char poly2[1000];
  fgets(poly2, sizeof(poly2), stdin);
  parsePoly(coeff_list2, degree_list2, poly2, &var);
  sortPoly(coeff_list2, degree_list2, temp_coeffs2, temp_degrees2); 
  printPoly(temp_coeffs2, temp_degrees2, var);
  printf("is\n");
  
  // multiplication
  mult_coeffs = newList();
  mult_degrees = newList();
  polyMult(temp_coeffs1, temp_degrees1, temp_coeffs2, temp_degrees2);
  printPoly(mult_coeffs, mult_degrees, var);
  printf("which simplifies to\n");
  freeList(&coeff_list1);
  freeList(&degree_list1);
  freeList(&coeff_list2);
  freeList(&degree_list2);
  freeList(&temp_coeffs1);
  freeList(&temp_degrees1);
  freeList(&temp_coeffs2);
  freeList(&temp_degrees2);
  
  // simplifying
  simp_coeffs = newList();
  simp_degrees = newList();
  polySimplify(mult_coeffs, mult_degrees);
  printPoly(simp_coeffs, simp_degrees, var);
  freeList(&mult_coeffs);
  freeList(&mult_degrees);
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
      appendList(degree_list, 0); // if its a constant, that means the degree is 0
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

void sortPoly(List coeff_list, List degree_list, List temp_coeffs, List temp_degrees) {
  while (length(degree_list) > 0) {
    int max_index = max(degree_list);
    int curr_degree = delElement(degree_list, max_index);
    int curr_coeff = delElement(coeff_list, max_index);
    appendList(temp_coeffs, curr_coeff);
    appendList(temp_degrees, curr_degree);
  }
}

void printPoly(List temp_coeffs, List temp_degrees, char var) {
  int term = 0; // to keep track of which term we are on
  for (int i = 0; i < length(temp_degrees); i++) {
    int curr_degree = delElement(temp_degrees, 0);
    appendList(temp_degrees, curr_degree);
    int curr_coeff = delElement(temp_coeffs, 0);
    appendList(temp_coeffs, curr_coeff);

    if (curr_degree == 0) {
      if (term == 0) {
        printf("%d", curr_coeff); // if degree = 0 and it's the first term
      } else {
        if (curr_coeff < 0) {
          printf(" - %d", curr_coeff * -1); // if degree = 0 and it's not the first
                                   // term and the coeff is negative
        } else {
          printf(" + %d", curr_coeff); // if degree = 0 and it's not the first
                                       // term and the coeff is positive
        }
      }
    } else if (curr_degree == 1) {
      if (term == 0) {
        if (curr_coeff == -1) {
          printf("-%c", var); // if degree = 1 and it's the first term and the coeff is -1
        } else if (curr_coeff == 1) {
          printf("%c", var); // if degree = 1 and it's the first term and coeff is 1
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
          printf(" - %c", var); // if degree = 1 and it's not the first term and coeff is -1
        } else if (curr_coeff == 1) {
          printf(" + %c", var); // if degree = 1 and it's not the first term and coeff is 1
        } else {
          if (curr_coeff < 0) {
            printf(" - %d%c", curr_coeff * -1, var); // if degree = 1 and it's not
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
            printf("-%d%c^%d", curr_coeff * -1, var, curr_degree); // if degree > 1 and it's the first term and
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
            printf(" - %d%c^%d", curr_coeff * -1, var, curr_degree); // if degree > 1 and it's not the first term
                                 // and coeff is negative
          } else {
            printf(" + %d%c^%d", curr_coeff, var, curr_degree); // if degree > 1 and it's not the first term
                                 // and coeff is positive
          }
        }
      }
    }
    term++;
  }
  printf("\n");
}

void polyMult(List coeffs1, List degrees1, List coeffs2, List degrees2) {
  for (int i = 0; i < length(degrees1); i++) {
    int first_degree = delElement(degrees1, 0); // stores degree of first polynomial
    int first_coeff = delElement(coeffs1, 0); // stores coeff of first polynomial
    appendList(degrees1, first_degree);
    for (int j = 0; j < length(degrees2); j++) {
      int sec_degree = delElement(degrees2, 0); // stores degree of second polynomial
      int sec_coeff = delElement(coeffs2, 0); // stores coeff of second polynomial
      appendList(degrees2, sec_degree); // add the degree back to the list so we can reaccess it
      appendList(coeffs2, sec_coeff); // add the coeff back to the list so we can reaccess it
      appendList(mult_coeffs, first_coeff * sec_coeff); // multiply the coeffs and add them to the list
      appendList(mult_degrees, first_degree + sec_degree); // add the degrees and add them to the list
    }
  }
  //polySimplify(mult_coeffs, mult_degrees);
}

void polySimplify(List coeffs, List degrees) {
  int coeff_total = 0;
  while (length(degrees) > 0) {
    int max_index = max(degrees);
    int curr_degree = delElement(degrees, max_index); // gets each different degree
    int curr_coeff = delElement(coeffs, max_index); // gets each corresponding coeff
    coeff_total += curr_coeff;
    int duplicate = find(degrees, curr_degree);
    if (duplicate == -1) {
	if (coeff_total == 0) {
	} else {
	    appendList(simp_degrees, curr_degree);
	    appendList(simp_coeffs, coeff_total);
	    coeff_total = 0;
        }
    }
  }
}

bool isVar(char c) { return (c >= 97 && c <= 122); }

bool isPower(char c) { return (c == 94); }

bool isNum(char c) { return (c >= 48 && c <= 57); }

bool isWhite(char c) { return (c == 9 || c == 32); }

bool isPlus(char c) { return (c == 43); }

bool isMinus(char c) { return (c == 45); }
