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
  free(v->let);
  FreeLinked(v->next);
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

  while(fscanf(qp, "%s\n", char1)!=EOF){
    struct Node* temp;
    struct Node* temp1;
    for(int i = 0; i<num; i++){
      if(strcmp(char1, A[i]->let) == 0){
	temp = A[i];
      }
    }
    struct Node* q = 0;
    struct Node* visit = 0;
    struct Node* pt;
    struct Node* ptr;
    struct Node* freed;
    int m = 0;
    while(m!=1){
      int x = 0;
      if(visit == 0){
	visit = calloc(1, sizeof(struct Node));
	char* x = calloc(25, sizeof(char));
	strcpy(x, temp->let);
	visit->let = x;
	pt = visit;
        while(temp->next!=0){
	  temp = temp->next;
	  if(q == 0){
	    q = calloc(1, sizeof(struct Node));
	    char* x = calloc(25, sizeof(char));
	    strcpy(x, temp->let);
	    q->let = x;
	    ptr = q;
	    freed = q;
	  }else{
	    struct Node* temp2;
	    temp2 = calloc(1, sizeof(struct Node));
	    char* x = calloc(25, sizeof(char));
	    strcpy(x, temp->let);
	    temp2->let = x;
	    ptr->next = temp2;
	    ptr = ptr->next;
	  }
	}
      }else{
	for(struct Node* i = visit; i!=0; i = i->next){
	  if(strcmp(i->let, q->let) == 0){
	    x = 1;
	  }
	}
	if(x == 1){
	  q = q->next;
	}else{
	  for(int i = 0; i<num; i++){
	    if(strcmp(A[i]->let, q->let) == 0){
	      struct Node* temp2;
	      temp2 = calloc(1, sizeof(struct Node));
	      char* x = calloc(25, sizeof(char));
	      strcpy(x, A[i]->let);
	      temp2->let = x;
	      pt->next = temp2;
	      pt = pt->next;
	      temp1 = A[i];
	      while(temp1->next!=0){
		temp1 = temp1->next;
		temp2 = calloc(1, sizeof(struct Node));
		char* x = calloc(25, sizeof(char));
		strcpy(x, temp1->let);
		temp2->let = x;
		ptr->next = temp2;
		ptr = ptr->next;
	      }
	    }
	  }
	  q = q->next;
	}
      }
      if(q == 0){
	 m = 1;
      }
    }
    for(struct Node* i = visit; i!=0; i=i->next){
      if(i->next == 0){
	printf("%s", i->let);
      }else{
	printf("%s ", i->let);
      }
    }
    printf("\n");
    FreeLinked(visit);
    FreeLinked(freed);
  }

 for(int i = 0; i<num; i++){
    FreeLinked(A[i]);
  }

  fclose(fp);
  fclose(qp);

  return EXIT_SUCCESS;

}

