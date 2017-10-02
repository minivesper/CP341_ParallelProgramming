#include <stdio.h>
#include <stdlib.h>

struct _LinkedRecord {
  int year;
  int stops;
  void* next;
};

typedef struct _LinkedRecord LR_t;

LR_t* list_find(LR_t* head, int year) {
  if(head->year == 0) {
    head->year = year;
    head->stops = 0;
    LR_t n;
    LR_t* pn = n;
    head->next = pn;
  }
  if(head->year == year) {
    return head;
  }
  return list_find(head->next, year);
}

int parse_line(char** line) {
  char** year_text; //= //line[6:10];
  ///v incomplete
  return 0;
}

void print_list(LR_t* head) {
  if(head->year == 0) {
    return;
  }
  printf("%d had %d stops", head->year, head->stops);
  print_list(head->next);
}

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Usage: %s <traffic data>\nExiting...\n",argv[0]);
  }
  FILE* f;
  LR_t* out_list;
  f = fopen(argv[1], "r");

  return 0;
}
