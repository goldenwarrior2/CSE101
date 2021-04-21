typedef struct Queue Queue;

Queue* initializeQueue(int n, int* arr);

void destructQueue(Queue* q);

void enQueue(Queue* q, int x);

int deQueue(Queue* q);

void printQueue(Queue* q);

int count(Queue* q);
