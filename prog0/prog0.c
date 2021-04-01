#include <stdio.h>
#include <unistd.h>

int length;    // height/ number of rows
int width;     // number of columns
int bordercol; // color of border of polygon
int fillcol;   // color of interior of polygon
int givenX;    // row index of point inside the polygon
int givenY;    // col index of point inside the polygon

void polyFill(int image[length][width], int x, int y) {
  if (image[x][y] != bordercol && image[x][y] != fillcol) {
    image[x][y] = fillcol;
  } else {
    return;
  }
  // north pixel
  if (x + 1 > -1 && x + 1 < length && y > -1 && y < width) {
    polyFill(image, x + 1, y);
  }
  // east pixel
  if (x > -1 && x < length && y + 1 > -1 && y + 1 < width) {
    polyFill(image, x, y + 1);
  }
  // west pixel
  if (x > -1 && x < length && y - 1 > -1 && y - 1 < width) {
    polyFill(image, x, y - 1);
  }
  // south pixel
  if (x - 1 > -1 && x - 1 < length && y > -1 && y < width) {
    polyFill(image, x - 1, y);
  }
}

int main() {
  fscanf(stdin, "%d", &length);
  //printf("Length: %d\n", length);
  fscanf(stdin, "%d", &width);
  //printf("Width: %d\n", width);
  fscanf(stdin, "%d", &bordercol);
  //printf("border color: %d\n", bordercol);
  fscanf(stdin, "%d", &fillcol);
  //printf("fill color: %d\n", fillcol);
  fscanf(stdin, "%d", &givenX);
  //printf("x coord: %d\n", givenX);
  fscanf(stdin, "%d", &givenY);
  //printf("y coord: %d\n", givenY);

  int img[length][width];
  for (int row = 0; row < length; row++) {
    for (int col = 0; col < width; col++) {
      int val = 0; // variable to store each value of the image
      fscanf(stdin, "%d", &val);
      img[row][col] = val;
      //printf("%4d", img[row][col]);
    }
    //printf("\n");
  }

  //printf("\n");

  polyFill(img, givenX, givenY);
  for (int x = 0; x < length; x++) {
    for (int y = 0; y < width; y++) {
      printf("%4d", img[x][y]);
    }
    printf("\n");
  }

  return 0;
}
