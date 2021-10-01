#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char* let;
  struct Node* next;
};

void swap(struct Node* v, struct Node* i);
void bubble(struct Node* v);

void FreeLinked(struct Node* v){
  if(v == 0) return;
  FreeLinked(v->next);
  free(v->let);
  free(v);
  return;
}

void bubble(struct Node *v){
  int s;
  struct Node *ptr;
  struct Node *prev = 0;

  if (v == 0)
    return;
  do{
    ptr = v;
    s = 0;
    while (ptr->next != prev){
      if (strcmp(ptr->let,ptr->next->let) > 0){
	swap(ptr, ptr->next);
	s= 1;
      }
      ptr = ptr->next;
    }
    prev = ptr;
  }
  while (s);
}

void swap(struct Node *v, struct Node *i) {
    char* temp = v->let;
    v->let = i->let;
    i->let = temp;
}

int main(int argc, char* argv[argc+1]){

  FILE* fp = fopen(argv[1], "r");
  FILE* qp = fopen(argv[2], "r");

  int num;

  fscanf(fp, "%d\n", &num);
  struct Node* A[num];
  for(int i = 0; i < num; i++){
    char* x = calloc(25, sizeof(char));
    fscanf(fp, "%s\n", x);
    struct Node* temp;
    temp = calloc(1, sizeof(struct Node));
    temp->let = x;
    A[i] = temp;
  }

  for(int i = 0; i<num-1; i++){
    for(int j = 0; j<num-i-1; j++){
      if(strcmp(A[j]->let, A[j+1]->let) > 0){
        char* x;
	x = A[j]->let;
	A[j]->let = A[j+1]->let;
	A[j+1]->let = x;
      }
    }
  }

  char char1[30];
  char char2[30];
  int m = 0;
  struct Node* temp1;
  struct Node* temp2;
  while(fscanf(fp, "%s %s\n", char1, char2)!=EOF){
    for(int i = 0; i < num; i++){
      if(strcmp(char1, A[i]->let) == 0){
	temp1 = A[i];
      }
      if(strcmp(char2, A[i]->let) == 0){
	temp2 = A[i];
      }
    }
    for(struct Node* i = temp1; i!=0; i = i->next){
      if(i->next == 0 && m!=1){
	struct Node* k;
	k = calloc(1, sizeof(struct Node));
	k->let = calloc(30, sizeof(char));
	strcpy(k->let, char2);
	i->next = k;
	m = 1;
      }
    }
    m = 0;
    for(struct Node* i = temp2; i!=0; i = i->next){
      if(i->next == 0 && m!=1){
	struct Node* j;
	j = calloc(1, sizeof(struct Node));
	j->let = calloc(30, sizeof(char));
	strcpy(j->let, char1);
	i->next = j;
	m = 1;
      }
    }
    m = 0;
  }

  for(int i = 0; i<num; i++){
    bubble(A[i]->next);
  }

  char popo;
  int x=0;
  while(fscanf(qp, "%c %s\n", &popo, char2)!=EOF){
    x = 0;
    if(popo == 'd'){
      for(int i = 0; i<num; i++){
	if(strcmp(char2,A[i]->let) == 0){
	  for(struct Node* j = A[i]; j!=0; j = j->next){
	    x++;
	  }
	  x = x-1;
	}
      }
      printf("%d\n", x);
    }else{
      for(int i = 0; i<num; i++){
	if(strcmp(char2,A[i]->let) == 0){
	  for(struct Node* j = A[i]; j!=0; j = j->next){
	    if(j == A[i]){
	    }else{
	      if(j->next == 0){
		printf("%s", j->let);
	      }else{
		printf("%s ", j->let);
	      }
	    }
	  }
	  printf("\n");
	}
      }
    }
  }

  for(int i = 0; i<num; i++){
    FreeLinked(A[i]);
  }

  fclose(fp);
  fclose(qp);
  return EXIT_SUCCESS;

}