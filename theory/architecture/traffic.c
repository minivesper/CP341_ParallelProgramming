#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _LinkedRecord LR_t;

struct _LinkedRecord {
  char* year;
  int stops;
  LR_t* next;
};

LR_t* list_find(LR_t* head, char* year) {
  if(head->year == 0) {
    head->year = malloc(sizeof(char)*5);
    strcpy(head->year, year);
    head->stops = 0;
    head->next = malloc(sizeof(LR_t));
    head->next->year = 0;
  }
  if(strcmp(head->year,year) == 0){
    return head;
  }
  return list_find(head->next, year);
}

char* parse_line(char* line) {
  char* year_text = malloc(sizeof(char)*5);
  char* ptr;
  long ret;
  line = line + 6;
  strncpy(year_text, line, 4);
  year_text[4] = 0;
  ret = strtol(year_text, &ptr, 4);
  if(ret > 0) {
    return year_text;
  }
  else {
    return "-1";
  }
}

void print_list(LR_t* head) {
  if(head->year == 0) {
    return;
  }
  printf("%s had %d stops\n", head->year, head->stops);
  print_list(head->next);
}

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Usage: %s <traffic data>\nExiting...\n",argv[0]);
  }
  FILE* f;
  char* year;
  LR_t* node;
  LR_t* out_list = malloc(sizeof(LR_t));
  char * line = 0;
  size_t len = 0;
  ssize_t read;

  f = fopen(argv[1], "r");

  while ((read = getline(&line, &len, f)) != -1) {
        year = parse_line(line);
        node = list_find(out_list, year);
        // printf("node %s, count %d, next: %p\n", node->year, node->stops, node->next);
        node->stops++;
    }

  fclose(f);
  print_list(out_list);
  return 0;
}
