#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char* let;
  int v;
  struct Node* next;
  struct Node* to;
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

void FreeLinked(struct Node* v){
  if(v == 0) return;
  free(v->let);
  FreeLinked(v->next);
  FreeLinked(v->to);
  free(v);
  return;
}

int main(int argc, char* argv[argc+1]){

  FILE* fp = fopen(argv[1], "r");
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
    bubble(A[i]->next);
  }


  char **arr = calloc(num, sizeof(char*));
  for(int i = 0; i<num; i++){
    arr[i] = calloc(30, sizeof(char));
  }

  int k = 0;
  int count = 0;
  int count2 = 0;
  while(count != num){
    int g = 0;
    if(count == 0){
      strcpy(arr[0], A[0]->let);
      count++;
      count2++;
    }else{
      struct Node* temp;
      temp = A[k];
      while(temp->next!=0 && g != 1){
	int x = 0;
	temp = temp->next;
	for(int j = 0; j<num; j++){
	  if(strcmp(arr[j], temp->let) == 0) x = 1;
	}
	if(x!=1){
	  for(int m = 0; m<num; m++){
	    if(strcmp(temp->let, A[m]->let) == 0){
	      strcpy(arr[count], A[m]->let);
	      k = m;
	      g = 1;
	      count++;
	      count2 = count;
	    }
	  }

	}
      }
      if(g == 0){
	if(count2!=0){
	  count2 = count2-1;
	  for(int i = 0; i<num; i++){
	    if(strcmp(arr[count2],A[i]->let) == 0){
	      k = i;
	    }
	  }
	}else{
	  int in = 0;
	  for(int i = 0; i<num; i++){
	    in = 0;
	    for(int j = 0; j<num; j++){
	      if(strcmp(arr[j], A[i]->let) == 0){
		in = 1;
	      }
	    }
	    if(in == 0){
	      strcpy(arr[count], A[i]->let);
	      k = i;
	      count++;
	      count2 = count;
	      break;
	    }
	  }


	}
      }
    }
  }

  for(int i = 0; i<num; i++){
    if(i == 0){
      printf("%s", arr[i]);
    }else{
      printf(" %s", arr[i]);
    }
  }

  for(int i = 0; i<num; i++){
    free(arr[i]);
  }
  free(arr);

  printf("\n");

  for(int i = 0; i<num; i++){
    FreeLinked(A[i]);
  }

  fclose(fp);

  return EXIT_SUCCESS;

}