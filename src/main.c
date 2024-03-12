// #include "d_string.h"
// #include "my_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  ListNode* list = list_from_array(array, length);
  ListNode* head = list;
  // printf("%lu\n", get_length(list));
  // print_list(list);
  // prepend(list, -1111);
  // append(list, 16788);
  // add(list, 77777);
  // print_list(list);
  // printf("%lu\n", get_length(list));
  // ListNode* new_list = get_index(list, 5);
  // printf("%d\n", new_list->val);
  // printf("%lu\n", get_length(new_list));
  // insert_at(list, 14, -77777);
  // print_list(list);
  // remove_head(list);
  remove_at(list, 3);
  // print_list(list);
  remove_at(list, 13);
  print_list(list);
  printf("%lu\n", get_length(list));
  // for (int i = 0; i < length; i++) {
  //   printf("%d\n", array[i]);
  // }
  // printf("%d\n", index);
}
