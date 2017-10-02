#include <stdio.h>
#include <stdlib.h>
#include "LinkedListApi.h"
#include <string.h>

typedef struct person_{
    
    char name[32];
    int age;
    int weight;
} person_t;

int
person_comparison_fn(void *struct_ptr, void *key){

    person_t *person = (person_t *)struct_ptr;
    if(strncmp(person->name, (char *)key, strlen((char *)key)) == 0 && 
          strlen((char *)key) == strlen(person->name))
        return 1; /*Match*/
     return 0;/*Not Match*/
}

void
print_person_details(person_t *outperson){

    printf("outperson->name = %s\n", outperson->name);
    printf("outperson->age = %d\n", outperson->age);
    printf("outperson->weight = %d\n", outperson->weight);
}

int
main(int argc, char **argv){

    ll_t *person_list = init_singly_ll();

    /*Register comparison fn*/
    person_list->comparison_fn = person_comparison_fn;

    person_t person1 = {"Ram", 30, 68};
    person_t person2 = {"Vibhor", 31, 70};
    person_t person3 = {"Akshay", 32, 56};

    singly_ll_add_node_by_val(person_list, &person1);
    singly_ll_add_node_by_val(person_list, &person2);
    singly_ll_add_node_by_val(person_list, &person3);

    person_t *outperson = NULL;

    printf("\n\nSearching ....\n");
    outperson = (person_t *)singly_ll_search_by_key(person_list, "Ram");
    
    print_person_details(outperson);

    printf("\n\n Looping ...\n");
    /*using looping macro to iterare*/
    singly_ll_node_t *list_node = NULL;

    ITERATE_LIST(person_list, list_node){

        outperson = (person_t *)list_node->data;
        print_person_details(outperson);
    }
    return 0;
}

