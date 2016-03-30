#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct circularQueue;
typedef struct circularQueue *ptrToNode;
typedef ptrToNode circularQueue;

struct circularQueue{
  int *key; // pointer to circular array queue
  int first;
  int rear;
  int size;
  int max_queue_size;
};

// function prototypes
circularQueue makeEmpty(int max);
int isEmpty(circularQueue q);
int isFull(circularQueue q);
void dequeue(circularQueue q);
void enqueue(circularQueue q, int x);
void printFirst(circularQueue q);
void printRear(circularQueue q);
void deleteQueue(circularQueue q);

int main(int argc, char* argv[]){
  FILE *ifp;
  ifp = fopen(argv[1], "r");
  char input[10]; // array to store line
  char cmd;
  char *cmdPtr;
  int element = 1;

  circularQueue q;
  
  while (fgets(input, 10, ifp)){
    cmdPtr = strtok(input, " ");
    cmd = cmdPtr[0];
    if (cmd == 'n' || cmd == 'e')
      element = atoi(strtok(NULL, " "));
    switch(cmd){
      case 'e':
        enqueue(q, element);
        break;
      case 'd':
        dequeue(q);
        break;
      case 'f':
        printFirst(q);
        break;
      case 'r':
        printRear(q);
        break;
      case 'n':
        q = makeEmpty(element);
        break;
      case 'p': // printing off the array to test if circular array is working
        for(int i=0; i<q->max_queue_size; i++)
          printf("[%i],", q->key[i]);
        printf("\n");
    }
  }
  deleteQueue(q); // free the memory
  fclose(ifp);

  return 0;
}

circularQueue makeEmpty(int max){
  circularQueue q = malloc(sizeof(struct circularQueue));
  q->first = 0;
  q->rear = -1;
  q->size = 0;
  q->max_queue_size = max;
  int *queue = malloc(max * sizeof(int));
  q->key = &queue[0];

  return q;
}

int isEmpty(circularQueue q){
  return q->size == 0;
}

int isFull(circularQueue q){
  return q->size == q->max_queue_size;
}

void dequeue(circularQueue q){
  if (isEmpty(q))
    printf("Dequeue Failed\t\t: Queue is Empty!!\n");
  else{
    q->size--;
    if (q->first == q->max_queue_size)
      q->first %= (q->max_queue_size - 1);
      // if the circular array reaches the end then it should reset to the beginning
    else
      q->first++;
    printf("Dequeue Success\t\t: %i\n", q->key[q->first - 1]);
  }
}

void enqueue(circularQueue q, int x){
  if (isFull(q))
    printf("Insertion Failed\t: Queue is Full!!\n");
  else{
    if ((q->rear + 1) == q->max_queue_size) 
      q->rear = (q->rear % (q->max_queue_size - 1) - 1);
      // if the circular array reaches the end then it should reset to the beginning
    q->key[q->rear++ + 1] = x;
    q->size++;
    printf("Insertion Success\t: %i\n", x);
  }
}

void printFirst(circularQueue q){
  if (isEmpty(q))
    printf("Print Failed\t\t: Queue is Empty!!\n");
  else
    printf("Front of queue\t\t: %i\n", q->key[q->first]);
}

void printRear(circularQueue q){
  if (isEmpty(q))
    printf("Print Failed\t\t: Queue is Empty!!\n");
  else
    printf("Rear of queue\t\t: %i\n", q->key[q->rear]);
}

void deleteQueue(circularQueue q){ // function to free the dynamically allocated memories
  free(q->key);
  free(q);
}
