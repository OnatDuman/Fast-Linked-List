#include <stdio.h>
#include <stdlib.h>
#define max_size 10
typedef struct Data{
    int data;
    struct Data *next;
    struct Data *below;
}data;
data* add_shortcuts(data* prev_data, int floor, int *floors);
void print_linked_list(data* head);
data* find_element_for_add(data* head, int element){
    data* curr_data = head;
    data* prev_data = curr_data;
    while (curr_data != NULL && curr_data->data <= element) {
        prev_data = curr_data;
        curr_data = curr_data->next;
    }
    if (prev_data->below != NULL) {
        prev_data = prev_data->below;
        prev_data = find_element_for_add(prev_data, element);
    }
    return prev_data;
}
int menu(){
    int chs;
    printf("\nYapmak istediginiz islemi seciniz.\nEleman ekleme-(1)");
    printf("\nEleman silme-(2)\nEleman arama-(3)\nVeri yapisini goruntuleme-(4)\n");
    scanf(" %d", &chs);
    if (chs < 1 || chs > 4) {
        printf("\nyanlis bir secim yaptiniz. Lutfen tekrar deneyiniz.");
        chs = menu();
    }
    return chs;
}
data* free_shortcuts(data *head, int *floors, int *counter){
    data* curr_data = head;
    data* next_data = NULL;
    data* prev_data;
    next_data = curr_data->below;
    while (next_data->below != NULL) {
        next_data = curr_data->below;
        while (curr_data != NULL) {
            prev_data = curr_data;
            curr_data = curr_data->next;
            free(prev_data);
        }
        curr_data = next_data;
    }
    return next_data;
}
void find_element(data* head){
    data* curr_data = head;
    data* prev_data = NULL;
    int atitude, element, unique;
    printf("\nAramak istediginiz sayiyi giriniz.\n");
    scanf(" %d", &element);
    unique = 0;
    while (curr_data != NULL && curr_data->data <= element && unique != 1) {
        prev_data = curr_data;
        while (curr_data != NULL && curr_data->data <= element && unique != 1) {
            prev_data = curr_data;
            if (curr_data->data == element) {
                unique = 1;
            }
            curr_data = curr_data->next;
        }
        curr_data = prev_data;
        curr_data = curr_data->below;
    }
    curr_data = prev_data;
    if (unique == 1) {
        printf("\nAradiginiz sayi bulunmustur.\n");
        atitude = 1;
        while (curr_data->below != NULL) {
            atitude++;
            curr_data = curr_data->below;
        }
        printf("\nAradiginiz sayinin bulundugu seviye: %d\n", atitude);
    }else{
        printf("\nAradiginiz sayi bulunamamistir.\n");
    }
}
data* add_element(data* head, int *counter, int *floors){
    int element;
    data* curr_data;
    data* prev_data;
    printf("\nEklemek istediginiz sayiyi giriniz.\n");
    scanf(" %d", &element);
    prev_data = find_element_for_add(head, element);
    curr_data = (data*)malloc(sizeof(data));
    curr_data->next = prev_data->next;
    prev_data->next = curr_data;
    curr_data->data = element;
    curr_data->below = NULL;
    counter += 1;
    floors[0] += 1;
    head = free_shortcuts(head, floors, counter);
    head = add_shortcuts(head, 2, floors);
    printf("\n\n");
    print_linked_list(head);
    return head;
}
data* delete_element(data* head, int *floors, int *counter){
    data* curr_data = head;
    data* prev_data = NULL;
    int element;
    printf("\nSilmek istediginiz sayiyi giriniz.\n");
    scanf(" %d", &element);
    head = free_shortcuts(head, floors, counter);
    curr_data = head;
    while (curr_data->data < element) {
        prev_data = curr_data;
        curr_data = curr_data->next;
    }
    if (curr_data->data == element) {
        prev_data->next = curr_data->next;
        free(curr_data);
        counter -= 1;
        floors[0] -= 1;
    }else {
        printf("\nSilmek istediginiz sayi bulunamamistir");
    }
    head = add_shortcuts(head, 2, floors);
    printf("\n\n");
    print_linked_list(head);
    return head;
}
data* add_shortcuts(data* prev_data, int floor, int *floors){
    data* curr_data = NULL;
    data* tmp_data;
    data* tmp_data2;
    data* below_tmp_data;
    floors[floor-1]=0;
    if (floors[floor-1] < (float) floors[floor-2]/2 ) {
        curr_data = (data*)malloc(sizeof(data));
        curr_data->below = prev_data;
        curr_data->next = NULL;
        curr_data->data = 0;
        floors[floor-1]++;
    }
    tmp_data2 = curr_data;
    below_tmp_data = prev_data;
    while (floors[floor-1] < (float) floors[floor-2]/2 ) {
        tmp_data = (data*)malloc(sizeof(data));
        tmp_data2->next = tmp_data;
        below_tmp_data = below_tmp_data->next;
        below_tmp_data = below_tmp_data->next;
        tmp_data->below = below_tmp_data;
        tmp_data->data = below_tmp_data->data;
        tmp_data2 = tmp_data;
        floors[floor-1]++;
        tmp_data->next = NULL;
    }
    if (curr_data->next != NULL) {
        curr_data = add_shortcuts(curr_data, ++floor, floors);
    }
    return curr_data;
}
void print_linked_list(data* head){
    data* curr_data = head;
    data* tmp_data;
    printf("\n\n");
    while (curr_data != NULL) {
        tmp_data = curr_data;
        while (tmp_data != NULL) {
            printf("%d ", tmp_data->data);
            tmp_data = tmp_data->next;
        }
        printf("\n");
        curr_data = curr_data->below;
    }
}
int exit_the_program(){
    int chs;
    printf("\nPrograma devam etmek icin 1'i cikis icin 0'i tuslayiniz.\n");
    scanf(" %d", &chs);
    if (chs != 0 && chs != 1) {
        printf("\nYanlis bir secim yaptiniz. Lutfen tekrar deneyiniz.");
        chs = exit_the_program();
    }
    return chs;
}
int main(int argc, const char * argv[]) {
    int counter = 6;
    int floors[max_size];
    int i, chs;
    int unique = 1;
    data* head;
    data* curr_data;
    data* tmp_data;
    floors[0] = counter;
    head = (data*)malloc(sizeof(data));
    head->data = 0;
    head->next = NULL;
    head->below = NULL;
    curr_data = head;
    for (i=0; i<5; i++) {
        tmp_data = (data*)malloc(sizeof(data));
        curr_data->next = tmp_data;
        tmp_data->data = (i+1)*2;
        tmp_data->below = NULL;
        tmp_data->next = NULL;
        curr_data = tmp_data;
    }
    head = add_shortcuts(head, 2, floors);
    while (unique == 1) {
        chs = menu();
        if (chs == 1) {
            head = add_element(head, &counter, floors);
        }else if (chs == 2){
            head = delete_element(head, floors, &counter);
        }else if (chs == 3){
            find_element(head);
        }else if (chs == 4){
            print_linked_list(head);
        }
        unique = exit_the_program();
    }
    return 0;
}
