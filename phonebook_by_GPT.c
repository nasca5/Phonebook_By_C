#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

typedef struct {
    char name[30];
    char phone_number[20];
} Contact;

Contact phonebook[MAX_CONTACTS];
int num_contacts = 0;

void load_phonebook() {
    FILE *fp = fopen("phonebook.dat", "rb");
    if (fp == NULL) {
        printf("�뙆�씪�씠 議댁옱�븯吏� �븡�뒿�땲�떎.\n");
        return;
    }
    fread(phonebook, sizeof(Contact), MAX_CONTACTS, fp);
    for (int i = 0; i < MAX_CONTACTS; i++) {
        if (strlen(phonebook[i].name) > 0) {
            num_contacts++;
        }
    }
    fclose(fp);
}

void save_phonebook() {
    FILE *fp = fopen("phonebook.dat", "wb");
    if (fp == NULL) {
        printf("�뙆�씪 �뿴湲곗뿉 �떎�뙣�뻽�뒿�땲�떎.\n");
        return;
    }
    fwrite(phonebook, sizeof(Contact), num_contacts, fp);
    fclose(fp);
}

void add_contact() {
    if (num_contacts >= MAX_CONTACTS) {
        printf("�뜑 �씠�긽 �뿰�씫泥섎�� 異붽���븷 �닔 �뾾�뒿�땲�떎.\n");
        return;
    }
    Contact new_contact;
    printf("�씠由�: ");
    scanf("%s", new_contact.name);
    printf("�쟾�솕踰덊샇: ");
    scanf("%s", new_contact.phone_number);
    phonebook[num_contacts] = new_contact;
    num_contacts++;
    save_phonebook();
}

void delete_contact() {
    if (num_contacts <= 0) {
        printf("�궘�젣�븷 �뿰�씫泥섍�� �뾾�뒿�땲�떎.\n");
        return;
    }
    char name[30];
    printf("�궘�젣�븷 �뿰�씫泥� �씠由�: ");
    scanf("%s", name);
    for (int i = 0; i < num_contacts; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            for (int j = i; j < num_contacts - 1; j++) {
                phonebook[j] = phonebook[j + 1];
            }
            num_contacts--;
            printf("%s �뿰�씫泥섍�� �궘�젣�릺�뿀�뒿�땲�떎.\n", name);
            save_phonebook();
            return;
        }
    }
    printf("%s �뿰�씫泥섎�� 李얠쓣 �닔 �뾾�뒿�땲�떎.\n", name);
}

void print_phonebook() {
    printf("=== �쟾�솕踰덊샇遺� ===\n");
    load_phonebook();
    for (int i = 0; i < num_contacts; i++) {
        printf("%s : %s\n", phonebook[i].name, phonebook[i].phone_number);
    }
    printf("=================\n");
}

int main() {
    load_phonebook();
    int choice = 0;
    while (1) {
        printf("1. �뿰�씫泥� 異붽��\n");
        printf("2. �뿰�씫泥� �궘�젣\n");
        printf("3. �뿰�씫泥� 異쒕젰\n");
        printf("4. 醫낅즺\n");
        printf("硫붾돱 �꽑�깮: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            add_contact();
            break;
        case 2:
            delete_contact();
            break;
        case 3:
            print_phonebook();
            break;
        case 4:
            printf("�봽濡쒓렇�옩�쓣 醫낅즺�빀�땲�떎.\n");
            return 0;
        default:
            printf("�옒紐삳맂 �엯�젰�엯�땲�떎. �떎�떆 �엯�젰�빐二쇱꽭�슂.\n");
            break;
        }
    }
return 0;
}