#include <stdio.h>
#include <unistd.h>
int main() {
 char first_name[21] = {0};
 write(1, "Enter Your Name: ", 17);
 read(0, first_name, 20);
 printf("Hello %s\n", first_name);
 return 0;
}