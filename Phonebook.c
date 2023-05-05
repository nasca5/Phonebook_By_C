#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define MAX 10000
#define DATA 100

// 비밀번호와 전화번호부를 저장하기 위한 파일
FILE* phonebook;

// 전화번호들의 정보를 담을 구조체
typedef struct {
  char name[DATA];
  char phonenumber[DATA];
  char group[DATA];
  char information[MAX];
  int exist;
} PHONE;

// 계속 있을 것인지 정하는 변수
int PLAY = 1;
// 비밀번호 저장할 문자열
char password[DATA];
// 비밀번호 검사할 문자열
char check[DATA];
// 어떤 함수 실행할지 결정하는 문자열

// 비밀번호가 없으면 비밀번호 생성 후 파일에 저장, 있을 경우 비밀번호를 입력받고 맞는지 확인후 loop문 실행
void check_password(); 
// 전화번호부 메인 화면 출력. 저장된 전화번호들과 "name"인지 "add"인지 정할 수 있는 입력칸 출력 입력에 맞게 다음 함수 실행 
void display_main(PHONE*);
// file에 저장된 전화번호들을 구조체에 저장하는 함수
void init_phonebook(PHONE*);
// 전화번호부에서 검색한 전화번호의 정보를 출력하는 함수
void display_search(PHONE*);
//
void decide();
//입력 버퍼를 지우는 함수
void Clear();
// 전화번호부에 새로운 전화번호를 저장하는 함수
void save_info();





int main() {
  check_password();
  PHONE phone[DATA] = {};

  for (int i = 0; i < DATA; i++) {
    phone[i].exist = 0;
  }

  init_phonebook(phone);

  while(PLAY) {
    display_main(phone);
  }

  printf("Bye!\n");

  return 0;
}




void check_password() {
  phonebook = fopen("./phonebook.txt", "a+b");
  if (phonebook == NULL) {
    printf("error!\n");
    exit(0);
  }

  int cnt = 5;
  int exist;

  while(1) {
    fgets(password, DATA, phonebook);

    printf("can you have password already? (y : 1 / n : 0)");
    scanf("%d", &exist);

    if(exist > MAX) {
      exit(0);
    }

    if (exist == 1) {
      if (strlen(password) == 0) {
        printf("No! you make a new password!\n");
        printf("wirte new password : ");
        scanf("%s", password);
        fputs(password, phonebook);
        fputs("\n", phonebook);
        fflush(phonebook);
      }

      else {
        password[strlen(password) -1] = '\0';
      }

      fclose(phonebook);
      break;
    }

    else if (exist == 0) {
      if(strlen(password) == 0) {
        printf("wirte new password : ");
        scanf("%s", password);
        fputs(password, phonebook);
        fputs("\n", phonebook);
        fflush(phonebook);
      }

      else {
        printf("you already have password!\n");
        password[strlen(password) -1] = '\0';
      }
      fclose(phonebook);

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

void init_phonebook(PHONE* phone) {
  phonebook = fopen("./phonebook.txt", "a+b");
  if (phonebook == NULL) {
    printf("error!\n");
    exit(0);
  }

  int i = 0;
  char temp[DATA];
  //fseek(phonebook, strlen(password) + 1, SEEK_SET);
  fgets(temp, DATA, phonebook);

  while(fgets(temp, DATA, phonebook) != NULL) {
    temp[strlen(temp) - 1] = '\0';
    strcpy((phone+i)->name, temp);

    fgets(temp, DATA, phonebook);
    temp[strlen(temp) - 1] = '\0';
    strcpy((phone+i)->phonenumber, temp);

    fgets(temp, DATA, phonebook);
    temp[strlen(temp) - 1] = '\0';
    strcpy((phone+i)->group, temp);

    fgets(temp, MAX, phonebook);
    temp[strlen(temp) - 1] = '\0';
    strcpy((phone+i)->information, temp);

    (phone+i)->exist = 1;
    i++;
  }

  fclose(phonebook);
}

void display_main(PHONE* phone) {
  int message = 0;
  int i = 0;

  printf("========================================\n");

  while((phone+i)->exist != 0) {
    printf("%-3d : %-15s\n", i+1, (phone+i)->name);
    i++;
    message = 1;
  }

  if (message == 0) {
    printf("No data!\n");
  }

  printf("========================================\n");
    
  printf("What you want to do? (typing name to search info or new to save info) : ");
  scanf("%s", check);

  system("cls");
  Clear();

  if(strcmp(check, "new") == 0) {
    save_info();
  }

  else {
    display_search(phone);
  }
}

void display_search(PHONE* phone) {
  int message = 0;

  for(int i = 0; i < DATA; i++) {
    if(strcmp(check, (phone+i)->name) == 0) {
      printf("========================================\n");
      printf("        name : %-15s\n", (phone+i)->name);
      printf("phone number : %-15s\n", (phone+i)->phonenumber);
      printf("       group : %-15s\n", (phone+i)->group);
      printf(" information : %-100s\n", (phone+i)->information);
      printf("========================================\n");
      message = 1;
    }
  }

  if (message == 0) {
    printf("No info!\n");
  }

  decide();
}

void save_info(PHONE* phone) {
  phonebook = fopen("./phonebook.txt", "a+b");

  if (phonebook == NULL) {
    printf("error!\n");
    exit(0);
  }

  //Clear();

  for(int i = 0; i < DATA; i++) {
    if((phone+i)->exist == 0) {
      printf("========================================\n");
      printf("        name : ");
      fgets((phone+i)->name, DATA, stdin);
      fputs((phone+i)->name, phonebook);
      printf("phone number : ");
      fgets((phone+i)->phonenumber, DATA, stdin);
      fputs((phone+i)->phonenumber, phonebook);
      printf("       group : ");
      fgets((phone+i)->group, DATA, stdin);
      fputs((phone+i)->group, phonebook);
      printf(" information : ");
      fgets((phone+i)->information, MAX, stdin);
      fputs((phone+i)->information, phonebook);
      printf("========================================\n");
      break;
    }
  }
  decide();

}

void decide() {
  printf("do you want to continue? (y : 1 / n : 0) : ");
  scanf("%d", &PLAY);

  system("cls");
  Clear();
}

void Clear() {
  while(getchar() != '\n') {
    continue;
  }
}