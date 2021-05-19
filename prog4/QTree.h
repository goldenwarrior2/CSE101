typedef struct pointObj {
	int x;
	int y;
} pointObj;
typedef pointObj* point;

typedef struct quadNodeObj {
	int count;
	point topLeft;
	point botRight;

	point node;
	struct quadNodeObj **child;
} quadNodeObj;
typedef quadNodeObj* quadNode;

point createPoint(int x, int y);

void deleteQuadTree(quadNode* pRoot);
