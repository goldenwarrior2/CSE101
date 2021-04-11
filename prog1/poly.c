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

int main(void) {
  char poly[100];
  fgets(poly, sizeof(poly), stdin);
  for (int i = 0; i < strlen(poly); i++) {
	printf("%c", poly[i]);
  }
  /*bool negative = false;
  char character;
  int num_coeffs = 0;
  int num_degrees = 0;
  struct ListObj *coeff_list = newList();
  struct ListObj *degree_list = newList();
  while ((character = fgetc(stdin)) != EOF) {
    if (isVar(character) && num_coeffs == 0) {
      appendList(coeff_list, 1); // if we have read in a variable before a
                                 // coefficient, that means the first coeff is 1
      num_coeffs++;

    } else if (isNum(character) && num_coeffs == 0) {
      int coeff;
      if (negative) {
        coeff = (character - '0') * -1;
      } else {
        coeff = character - '0';
      }
      appendList(coeff_list, coeff); // if we have read in a number and there
                                     // are no coefficients yet then this is the
                                     // first coeff
      num_coeffs++;

    } else if (isNum(character) && num_degrees == 0 && num_coeffs == 1) {
      int degree = character - '0';
      appendList(degree_list, degree); // if we have read in a number and there
                                       // is 1 coeff and no degrees then this
                                       // is the first degree
      num_degrees++;

    } else if (isNum(character) && num_coeffs != 0 && num_degrees != 0 &&
               num_coeffs == num_degrees) {
      int coeff;
      if (negative) {
        coeff = (character - '0') * -1;
      } else {
        coeff = character - '0';
      }
      appendList(coeff_list, coeff); // if we have read in a number and there is
                                     // an equal amount of coeffs and degrees
                                     // then this is the next coeff
      num_coeffs++;
    }
    // else if(isNum(character) && num_coeffs != 0 && num_degrees != 0 &&
    // num_coeffs == num_degrees + 1) {
    //  int degree = character - '0';
    // appendList(degree_list, degree);
    // }
    else if (isPower(character) || isWhite(character) || isPlus(character)) {
    } else if (isMinus(character)) {
      negative = true;
    }
  }

  // printf("The biggest element is at index: %d\n", max(new_list));
  // printf("The element %d is at index %d\n", 8, find(new_list, 8));
  // printf("element deleted: %d\n", delElement(new_list, max(new_list)));
  printList(coeff_list);
  printList(degree_list);
  freeList(&coeff_list);
  freeList(&degree_list); */
  return 0; 
}

bool isVar(char c) { return (c >= 97 && c <= 122); }

bool isPower(char c) { return (c == 94); }

bool isNum(char c) { return (c >= 48 && c <= 57); }

bool isWhite(char c) { return (c == 9 || c == 32); }

bool isPlus(char c) { return (c == 43); }

bool isMinus(char c) { return (c == 45); }
