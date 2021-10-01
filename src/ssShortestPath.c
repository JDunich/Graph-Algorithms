#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

struct Node{
  char* let;
  int v;
  struct Node* to;
  struct Node* next;
};

struct Edge{
  char* let;
  int distTo;
  struct Edge* prev;
};

void swap(struct Node* v, struct Node* i);
void bubble(struct Node* v);

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
    int x = v->v;
    struct Node* temp1 = v->to;
    v->let = i->let;
    v->v = i->v;
    v->to = i->to;
    i->let = temp;
    i->v = x;
    i->to = temp1;
}

void FreeLinkedA(struct Node* v){
  if(v == 0) return;
  free(v->let);
  FreeLinkedA(v->next);
  FreeLinkedA(v->to);
  free(v);
  return;
}

void FreeLinkedB(struct Edge* v){;
  if(v == 0) return;
  free(v->let);
  FreeLinkedB(v->prev);
  free(v);
  return;
}


int main(int argc, char* argv[argc+1]){

  FILE* fp = fopen(argv[1], "r");
  FILE* qp = fopen(argv[2], "r");

  int num;

  fscanf(fp, "%d\n", &num);
  struct Node* A[num];
  struct Edge* B[num];
  for(int i = 0; i < num; i++){
    char* x = calloc(25, sizeof(char));
    char* y = calloc(25, sizeof(char));
    fscanf(fp, "%s\n", x);
    strcpy(y, x);
    struct Node* temp;
    temp = calloc(1, sizeof(struct Node));
    temp->let = x;
    A[i] = temp;
    struct Edge* temp1;
    temp1 = calloc(1, sizeof(struct Edge));
    temp1->let = y;
    B[i] = temp1;
  }

  for(int i = 0; i<num-1; i++){
    for(int j = 0; j<num-i-1; j++){
      if(strcmp(A[j]->let, A[j+1]->let) > 0){
        char* x;
	char* y;
	x = A[j]->let;
	y = B[j]->let;
	A[j]->let = A[j+1]->let;
	B[j]->let = B[j+1]->let;
	A[j+1]->let = x;
	B[j+1]->let = y;
      }
    }
  }

  char char1[30];
  char char2[30];
  int int1;
  struct Node* temp1;
  struct Node* temp2;
  int m = 0;
  while(fscanf(fp, "%s %s %d\n", char1, char2, &int1)!=EOF){
    for(int i = 0; i<num; i++){
      if(strcmp(char1,A[i]->let) == 0){
	temp1 = A[i];
      }
      if(strcmp(char2,A[i]->let) == 0){
	temp2 = A[i];
      }
    }
    for(struct Node* i = temp1; i!=0; i = i->next){
      if(i->next == 0 && m!=1){
	struct Node* k;
	k = calloc(1, sizeof(struct Node));
	k->let = calloc(30, sizeof(char));
	strcpy(k->let, char2);
	k->v = int1;
	i->next = k;
	m = 1;
      }
    }
    m = 0;
    for(struct Node* i = temp2; i!=0; i = i->to){
      if(i->to == 0 && m!=1){
	struct Node* j;
	j = calloc(1, sizeof(struct Node));
	j->let = calloc(30, sizeof(char));
	strcpy(j->let, char1);
	i->to = j;
	m = 1;
      }
    }
    m = 0;
  }

  for(int i = 0; i<num; i++){
    for(int j = i+1; j<num; j++){
      for(struct Node* k = A[j]; k!=0; k = k->next){
	if(strcmp(A[i]->let, k->let) == 0){
	  printf("CYCLE\n");
	  return EXIT_SUCCESS;
	}
      }
    }
  }

  for(int i = 0; i<num; i++){
    bubble(A[i]->next);
  }

  struct Node* ptr;
  struct Edge* temp;
  while(fscanf(qp, "%s\n", char1)!=EOF){
    int x = 0;
    int y;
    for(int i = 0; i<num; i++){
      if(strcmp(B[i]->let,char1) == 0){
	y = i;
	B[i]->distTo = 0;
      }else{
	B[i]->distTo = INT_MAX;
	x++;
      }
    }

    int stop = 1;
    struct Node* head = 0;
    struct Node* pt;
    while(stop != 0){
      for(int i = 0; i<num; i++){
	if(strcmp(B[y]->let, A[i]->let) == 0){
	  ptr = A[i];
	}
      }
      for(struct Node* i = ptr; i!=0; i = i->next){
	if(strcmp(i->let, ptr->let) == 0){
	}else{
	  for(int j = 0; j<num; j++){
	    if(strcmp(B[j]->let, i->let) == 0){
	      temp = B[j];
	      if(head == 0){
		head = calloc(1, sizeof(struct Node));
		char* x = calloc(30, sizeof(char));
		strcpy(x, temp->let);
		head->let = x;
		break;
	      }else{
		for(struct Node* lol = head; lol!=0; lol = lol->next){
		  if(strcmp(lol->let, temp->let) == 0){
		    break;
		  }else{
		    if(lol->next == 0){
		      pt = calloc(1, sizeof(struct Node));
		      char* x = calloc(30, sizeof(char));
		      strcpy(x, temp->let);
		      pt->let = x;
		      lol->next = pt;
		      break;
		    }
		  }
		}
	      }
	    }
	  }
	  if(temp->distTo == INT_MAX || (B[y]->distTo + i->v < temp->distTo)){
	    temp->distTo = B[y]->distTo + i->v;
	  }
	}
      }

      struct Node* prev;
      if(head!=0){
	for(struct Node* i = head; i!=0; i = i->next){
	  if(strcmp(i->let, B[y]->let) == 0){
	    if(i == head){
	      struct Node* freed = head;
	      head = head->next;
	      free(freed->let);
	      free(freed);
	      break;
	    }else{
	      struct Node* freed = i;
	      prev->next = i->next;
	      free(freed->let);
	      free(freed);
	      i = prev;
	    }
	  }
	  prev = i;
	}
      }

      int m = 0;
      for(struct Node* i = ptr; i!=0; i = i->next){
	if(strcmp(i->let,ptr->let) == 0){
	}else{
	  for(int j = 0; j<num; j++){
	    if(strcmp(B[j]->let, i->let) == 0){
	      if(m == 0){
		m = B[j]->distTo;
		y = j;
	      }else{
		if(m > B[j]->distTo){
		  m = B[j]->distTo;
		  y = j;
		}
	      }
	    }
	  }
	}
      }

      if(ptr->next == 0){
        if(head!=0){
	  for(int i = 0; i<num; i++){
	    if(strcmp(head->let, B[i]->let) == 0){
	      y = i;
	      break;
	    }
	  }
	}else{
	stop = 0;
	}

      }
    }

    printf("\n");
    for(int i = 0; i<num; i++){
      printf("%s ", B[i]->let);
      if(B[i]->distTo == INT_MAX){
	printf("INF");
      }else{
	printf("%d", B[i]->distTo);
      }
      printf("\n");
    }
  }
  printf("\n");
  for(int i = 0; i<num; i++){
    FreeLinkedA(A[i]);
  }
  for(int i = 0; i<num; i++){
    FreeLinkedB(B[i]);
  }


  fclose(fp);
  fclose(qp);
  return EXIT_SUCCESS;

}