#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 10000
#define DATA 100

// ��й�ȣ�� ��ȭ��ȣ�θ� �����ϱ� ���� ����
FILE* phonebook;

typedef struct {
  char phonenumber[DATA];
  char name[DATA];
  char group[DATA];
  char information[MAX];
} PHONE;

int PLAY = 1;
char password[DATA];
char check[DATA];
char what[DATA];
char search[DATA];

void check_password(); // ��й�ȣ�� ������ ��й�ȣ ���� �� ���Ͽ� ����, ���� ��� ��й�ȣ�� �Է¹ް� �´��� Ȯ���� loop�� ����
void display_main(char* arg1);
void display_search(char* arg2);
void display_info(char* arg3);
void decide();
void save_info();

int main() {
  phonebook = fopen("D://phonebook.txt", "a+b");
  check_password();

  // while(PLAY) {
  //     display_main(&what);

  //     if(strcmp(what, "search") == 0) {
  //       display_search(&search);
  //       display_info(&search);
  //       decide();
  //     }

  //     else if(strcmp(what, "add") == 0) {
  //       save_info();
  //       decide();
  //     }

  //     else {
  //       printf("please type search or add\n");
  //       continue;
  //     }
  //   }
  return 0;
}


void check_password() {
  phonebook = fopen("./phonebook.txt", "a+");

  int cnt = 5;
  int exist;

  while(1) {
    fgets(password, DATA, phonebook);
    printf("can you have password already? (y : 1 / n : 0)");
    scanf("%d", &exist);

    if (exist == 1) {
      if (strlen(password) == 0) {
        printf("No! you make a new password!\n");
        printf("wirte new password : ");
        scanf("%s", password);
        fputs(password, phonebook);
        fputs("\n", phonebook);
      }

      break;
    }

    else if (exist == 0) {
      if(strlen(password) == 0) {
        printf("wirte new password : ");
        scanf("%s", password);
        fputs(password, phonebook);
        fputs("\n", phonebook);
      }

      else {
        printf("you already have password!\n");
      }

      break;
    }

    else {
      printf("write 1 or 0 please\n");
    }
  }

  while(1) {
    printf("Enter your password : ");
    scanf("%s", check);

    if(strcmp(check, password) == 0) {
      printf("\n\nWelcome!\n\n");
      break;
    }

    else {
      cnt--;
      printf("please typing correctly. chance : %d\n", cnt);
    }

    if (cnt == 0) {
      printf("so many wrongs sorry\n");
      exit(0);
    }
  }
}