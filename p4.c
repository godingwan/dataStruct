#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // in order to use isdigit()

struct Stack;
typedef struct Stack *PtrToNode;
typedef PtrToNode Stack;
typedef char ElementType;

struct Stack{
  char key;
  int top;
  int max_stack_size;
  PtrToNode next;
};

Stack createStack();
void push(ElementType e, Stack s);
char pop(Stack s);
char top(Stack s);
int isEmpty(Stack s);
void removeStack(Stack s);

int main(int argc, char *argv[]){
  FILE *ifp;
  ifp = fopen(argv[1], "r");
  
  char input[100]; // array to store input line
  fgets(input, 100, ifp);
  Stack s;
  s = createStack();

  printf("Original infix form: %s\n", input);
  printf("Converted postfix form: ");

  // postfix logic
  for (int i=0; i<100; i++){
    if (input[i] == '#'){
      while (!isEmpty(s))
        printf("%c", pop(s)); // print out until stack is empty
      break;
    }
    else if (isdigit(input[i])) // print out the operands
      printf("%c", input[i]);
    else{
      if (isEmpty(s))
        push(input[i], s);
      else{
        if (input[i] == ')'){ // pop out all the operants until (
          while (top(s) != '(')
            printf("%c", pop(s));
          pop(s); // need to pop to get rid of the (
        }
        else if (input[i] == '*' || input[i] == '/' || input[i] == '%'){
          if (top(s) == '-' || top(s) == '+')
            push(input[i], s);
          else if (top(s) == '*' || input[i] == '/' || input[i] == '%'){
            if (top(s) == '(')
              push(input[i],s);
            else{
              printf("%c", pop(s));
              push(input[i], s);
            }
          }
          else
            push(input[i], s);
        }
        else{ // when input[i] is '+', '-', or '('
          if (input[i] == '(')
            push(input[i], s);
          else if (top(s) == '*' || top(s) == '/' || top(s) == '%'){
            if (top(s) == '(')
              push(input[i],s);
            else{
              printf("%c", pop(s));
              push(input[i], s);
            }
          }
          else{
            if (top(s) == '(')
              push(input[i],s);
            else{
              printf("%c", pop(s));
              push(input[i], s);
            }
          }
        }
      }
    }
  }
  printf("#\n");
  return 0;
}

Stack createStack(){
  Stack s;
  s = malloc(sizeof(struct Stack));

  if (s == NULL){
    printf("malloc() ERROR: Not enough memory\n");
    exit(1);
  }

  s->next = NULL;
  return s;
}

void push(ElementType e, Stack s){
  PtrToNode tmp;
  tmp = malloc(sizeof(struct Stack));

  if (tmp == NULL){
    printf("malloc() ERROR: Not enough memory\n");
    exit(1);
  }
  else{
    tmp->key = e;
    tmp->next = s->next;
    s->next = tmp;
  }
}

char pop(Stack s){
  PtrToNode firstCell;
  firstCell = s->next;
  char c;
  if (firstCell == NULL){
    printf("pop() ERROR: No element in stack\n");
    exit(3);
  }
  else{
    c = firstCell->key;
    s->next = firstCell->next;
    free(firstCell);
    return c;
  }
}

char top(Stack s){
  PtrToNode firstCell;
  firstCell = s->next;
  if (firstCell == NULL){
    printf("top() ERROR: No element in stack\n");
    exit(3);
  }
  else{ return s->next->key; }
}

int isEmpty(Stack s){
  return s->next == NULL;
}

void removeStack(Stack s){
  if (s == NULL){
    printf("removeStack() ERROR: No stack exists\n"); 
    exit(2);
  }
  else{
    while(!isEmpty(s)){
      pop(s);
    }
    free(s);
  }
}
