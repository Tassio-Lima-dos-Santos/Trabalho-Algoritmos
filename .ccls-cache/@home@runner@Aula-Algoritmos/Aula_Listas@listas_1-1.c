/*#include <stdio.h>
#include <stdlib.h>

typedef struct listItem {
  int value;
  struct listItem *next;
} ListItem;

ListItem* add (ListItem *head, int value){
  ListItem *item = malloc(sizeof(ListItem));
  (*item).value = value;
  (*item).next = head;
  head = item;

  return head;
}

int main(){
  

  return 0;
}*/