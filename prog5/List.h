typedef struct node {
  int value;
  struct node *next;
  struct node *prev;
} node;

node* createList(int n);
node *findList(node *head, int val);

void insertList(node **head, node *new);

void deleteList(node **head, node *del);
void printList(node *head);

int getValue(node* x);
