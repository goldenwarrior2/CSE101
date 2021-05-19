#include <stdlib.h>
#include <stdio.h>
#include "QTree.h"

point createPoint(int x, int y) {
  point p = malloc(sizeof(point));
  p->x = x;
  p->y = y;
  return p;
}

quadNode createQuadTree(point topLeft, point botRight) {
  quadNode qt = (quadNode) malloc(sizeof(quadNodeObj));
  qt->count = 0;
  qt->topLeft = topLeft;
  qt->botRight = botRight;
  qt->child = (quadNode *) malloc(4 * sizeof(quadNode));
  qt->child[0] = NULL;
  qt->child[1] = NULL;
  qt->child[2] = NULL;
  qt->child[3] = NULL;
  qt->node = NULL;	
  return qt;	
}

void deleteQuadTree(quadNode* pRoot) {
  if (pRoot && *pRoot) {
    quadNode root = *pRoot;
    for (int i = 0; i < 4; i++) {
      if(root->child[i] != NULL) {
        free(root->child[i]);
      }
    }
    free(root->child);
    free(root->topLeft);
    free(root->botRight);
    if (root->node != NULL) {
      free(root->node);
    }
    free(root);
    root = NULL;
  }
}

void insertPoint(quadNode root, point p) {
  // check if p is already in the quadtree, if it is, return
  if (root->count == 0) {
    root->node = p;
    root->count++;
  } else {
    int midx = root->botRight->x / 2;
    int midy = root->botRight->y / 2;
    
    if (p->x < midx && p->y < midy) {
      insertPoint(root->child[0], p);
    } 
    else if (p->x < midx && p->y > midy) {
      insertPoint(root->child[1], p);
    }
    else if (p->x > midx && p->y < midy) {
      insertPoint(root->child[2], p);
    }
    else if (p->x > midx && p->y > midy) {
      insertPoint(root->child[3], p);
    }
  }
}

int main() {
	point p1 = createPoint(0, 0);
	point p2 = createPoint(128, 128);
	quadNode root = createQuadTree(p1, p2);
	printf("%d\n", root->count);
	printf("topLeft: %d, %d\n", root->topLeft->x, root->topLeft->y);
	printf("botRight: %d, %d\n", root->botRight->x, root->botRight->y);
	point p3 = createPoint(1, 1);
	insertPoint(root, p3);
	printf("point: %d, %d\n", root->node->x, root->node->y);
	deleteQuadTree(&root);
	return 0;	
}
