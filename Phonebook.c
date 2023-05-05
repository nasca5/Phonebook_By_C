#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 10000
#define DATA 100

// 비밀번호와 전화번호부를 저장하기 위한 파일
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

void check_password(); // 비밀번호가 없으면 비밀번호 생성 후 파일에 저장, 있을 경우 비밀번호를 입력받고 맞는지 확인후 loop문 실행
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