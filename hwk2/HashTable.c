// Operations supporting hash tables

#include "HashTable.h"
// Converts a 5 letter key into an integer
// CC###: ascii equivalent of letters and digits are simply added together
// #####: ascii equivalent of digits are simply added together
int convert(char key[5]) {
  int value;
  int sum;
  for (int i = 0; i < 5; i++) {
    value = key[i];
    sum += value;
  }
  return sum;
}

// Hash function that returns an index into the hash table given a key
int hash(char key[5], int slots) {
  int ascii = convert(key);
  int index = ascii % slots;
  return index;
}
