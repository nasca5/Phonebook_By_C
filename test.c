#include <stdio.h> 
#include <stdlib.h> 

void check_password() {
  phonebook = fopen("./phonebook.txt", "a+");
  int exist;

  printf("can you have password already? (y : 1 / n : 0)\n");
  scanf("%d", &exist);

  if (exist == 1) {
    fgets(password, DATA, phonebook);
  }

  else if (exist == 0) {
    printf("wirte new password : ");
    scanf("%s", password);
    fputs(password, phonebook);
  }
  while(1) {
    printf("Enter your password\n");
    scanf("%s", check);

    if(strcmp(check, password) == 0) {
      printf("Welcome!\n\n");
      break;
    }
    else {
      printf("please typing correctly\n");
    }
  }
  
}

int main() {
  FILE* phonebook = fopen("./phonebook.txt", "a+b");

  check_password();
}