#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define MAX 10000
#define DATA 100

// ��й�ȣ�� ��ȭ��ȣ�θ� �����ϱ� ���� ����
FILE* phonebook;

// ��ȭ��ȣ���� ������ ���� ����ü
typedef struct {
  char phonenumber[DATA];
  char name[DATA];
  char group[DATA];
  char information[MAX];
  int exist;
} PHONE;

// ��� ���� ������ ���ϴ� ����
int PLAY = 1;
// ��й�ȣ ������ ���ڿ�
char password[DATA];
// ��й�ȣ �˻��� ���ڿ�
char check[DATA];
// � �Լ� �������� �����ϴ� ���ڿ�
char what[DATA];
// �˻��� ���ڿ�
char search[DATA];

// ��й�ȣ�� ������ ��й�ȣ ���� �� ���Ͽ� ����, ���� ��� ��й�ȣ�� �Է¹ް� �´��� Ȯ���� loop�� ����
void check_password(); 
// ��ȭ��ȣ�� ���� ȭ�� ���. ����� ��ȭ��ȣ��� "search"���� "add"���� ���� �� �ִ� �Է�ĭ ��� �Է¿� �°� ���� �Լ� ���� 
void display_main(PHONE* phone);

void display_search(char* arg2);

void display_info(char* arg3);

void decide();

void save_info();

int main() {
  check_password();

  PHONE phone[DATA] = {
    {"01077143103", "Kang", "friend", "nerd", 0},  
    {"01062143103", "Hyun", "friend", "idiot", 0}
  };
  
  for (int i = 0; i < DATA; i++) {
    phone[i].exist = 0;
  }

  phone[0].exist = 1;
  phone[1].exist = 1;

  // while(PLAY) {
      display_main(phone);

  //  if(strcmp(what, "search") == 0) {
  //    display_search(&search);
  //    display_info(&search);
  //    decide();
  //  }

  //  else if(strcmp(what, "add") == 0) {
  //    save_info();
  //    decide();
  //  }

  //  else {
  //    printf("please type search or add\n");
  //    continue;
  //  }
  //}
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

void display_main(PHONE* phone) {
  int i = 0;
  printf("========================================\n");
  while(phone[i].exist != 0) {
    printf("%-3d : %-15s\n", i+1, phone[i].name);
    i++;
  }
  printf("========================================\n");
    do {
    printf("What you want to do? (typing search or add) : ");
    scanf("%s", check);

    if(strcmp(check, "search") == 0) {
      //display_search();
      break;
    }

    else if(strcmp(check, "add") == 0) {
      //save_info();
      break;
    }

    else {
      printf("please typing search or add\n");
    }
  } while(strcmp(check, "search") != 0 && strcmp(check, "add") != 0);
}