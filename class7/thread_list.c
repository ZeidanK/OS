#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// from last class work will do some more work here?
//

struct List {
  int val;
  struct List *next;
};

struct Range {
  int num;
  int from;
  int till;
};

struct List *head = NULL; // LIST is global variable

pthread_mutex_t mtx;
void random_sleep();
void *add_items(void *);
void add_one_item(struct List **, int);
void print_list(struct List *);

// constants and global variables

//------------------------------------------------
int main() {
  pthread_mutex_init(&mtx, NULL);
  pthread_t t1, t2;
  struct Range range1 = {1, 1, 5}, range2 = {2, 6, 10};

  printf("MAIN Thread starting...\n");
  pthread_create(&t1, NULL, add_items, &range1);
  pthread_create(&t2, NULL, add_items, &range2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&mtx);
  printf("MAIN Thread: ALL Threads terminated! Printing the List before "
         "exiting.\n");
  print_list(head);
  pthread_exit(NULL);
  // exit(0);
}

//------------------------------------------------
void *add_items(void *ptr) {
  struct Range *range = ptr;
  int num = range->num;
  int from = range->from;
  int till = range->till;
  if (num == 1)
    sleep(4); // make one of the threads sleep while the other does its job
  for (int val = from; val <= till; val++) {

    // pthread_mutex_lock(&mtx);
    printf("Thread #%d: going to add: %d\n", num, val);
    add_one_item(&head, val);

    // pthread_mutex_unlock(&mtx);
  }
  printf("function %s: Thread #%d ending... printing the list as it is now:\n",
         __func__, num);
  print_list(head);

  pthread_exit(NULL);
}
//======= List functions =======

//******* for debug *******
void print_one_item(struct List *item) {
  printf("%s val=%d, next=%p\n", __func__, item->val, item->next);
}

//------------------------------------------------
void add_one_item(struct List **head, int val) {
  struct List *new_item, *temp;
  new_item = (struct List *)malloc(sizeof(struct List));
  new_item->val = val;
  pthread_mutex_lock(&mtx);
  temp = *head;
  sleep(1);
  random_sleep();
  *head = new_item;
  pthread_mutex_unlock(&mtx);
  random_sleep();
  new_item->next = temp;
}

//------------------------------------------------
void print_list(struct List *head) {
  while (head) {
    printf("--> %d ", head->val);
    head = head->next;
  }
  printf("\n");
}

//-------------------------------------------------
void random_sleep() {
  int d = (rand() ^ pthread_self() ^ getpid()) % 20 + 10;
  const struct timespec ts = {0, d * 1000 * 1000 * 10};
  nanosleep(&ts, NULL);
}
