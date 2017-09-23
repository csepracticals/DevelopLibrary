
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LinkedListApi.h"
#include <assert.h>

ll_t* init_singly_ll(){
    return calloc(1, sizeof(ll_t));
}

singly_ll_node_t* singly_ll_init_node(void* data){
    singly_ll_node_t* node = calloc(1, sizeof(singly_ll_node_t));
    node->data = data;
    return node;
}

int 
singly_ll_add_node(ll_t* ll, singly_ll_node_t *node){
    if(!ll) return -1;
    if(!node) return -1;
    if(!GET_HEAD_SINGLY_LL(ll)){
        GET_HEAD_SINGLY_LL(ll) = node;
        INC_NODE_COUNT_SINGLY_LL(ll);
        return 0;
    }

    node->next = GET_HEAD_SINGLY_LL(ll);
    GET_HEAD_SINGLY_LL(ll) = node;
    INC_NODE_COUNT_SINGLY_LL(ll);
    return 0;
}

int 
singly_ll_add_node_by_val(ll_t *ll, void* data){
    singly_ll_node_t* node = singly_ll_init_node(data);
    return singly_ll_add_node(ll, node);
}

int
singly_ll_delete_node(ll_t *ll, singly_ll_node_t *node){
    if(!ll) return -1;
    if(!GET_HEAD_SINGLY_LL(ll) || !node) return 0;
    singly_ll_node_t *trav = NULL;
    /*if node is not the last node*/
    if(node->next){
        singly_ll_node_t *temp = NULL;
        node->data = node->next->data;
        temp = node->next;
        node->next = node->next->next;
        free(temp);
        DEC_NODE_COUNT_SINGLY_LL(ll);
        return 0;
    }

    /* if node is the only node in LL*/
    if(ll->node_count == 1 && GET_HEAD_SINGLY_LL(ll) == node){
        free(node);
        GET_HEAD_SINGLY_LL(ll) = NULL;
        DEC_NODE_COUNT_SINGLY_LL(ll);
        return 0;
    }

    /*if node is the last node of the LL*/
    trav = GET_HEAD_SINGLY_LL(ll);
    while(trav->next != node){
        trav = trav->next;
        continue;
    }
    
    trav->next = NULL;
    free(node);
    DEC_NODE_COUNT_SINGLY_LL(ll);
    return 0;
}

int
singly_ll_remove_node(ll_t *ll, singly_ll_node_t *node){
	if(!ll || !GET_HEAD_SINGLY_LL(ll)) return 0;
	if(!node){
		printf("%s(%d) : Error : node is NULL\n", __FUNCTION__, __LINE__);
		return -1;		
	}
	int i = 0;
	singly_ll_node_t *head = GET_HEAD_SINGLY_LL(ll), *prev = NULL;
	
	if(head == node){
		GET_HEAD_SINGLY_LL(ll) = GET_NEXT_NODE_SINGLY_LL(head);
		DEC_NODE_COUNT_SINGLY_LL(ll);
		node->next = NULL;
		return 0;
	}

	prev = head;
	head = GET_NEXT_NODE_SINGLY_LL(head);
	for(i =1; i < GET_NODE_COUNT_SINGLY_LL(ll); i++){
		if(head != node){
			prev = head;
			head = GET_NEXT_NODE_SINGLY_LL(head);
			continue;
		}
		
		GET_NEXT_NODE_SINGLY_LL(prev) = GET_NEXT_NODE_SINGLY_LL(head);
		GET_NEXT_NODE_SINGLY_LL(head) = NULL;
		DEC_NODE_COUNT_SINGLY_LL(ll);
		node->next = NULL;
		return 0;	
	}	
	printf("%s(%d) : Error : node not found\n", __FUNCTION__, __LINE__);
	return -1;
}



unsigned int
singly_ll_delete_node_by_value(ll_t *ll, void *data, int size){
    if(!ll || !GET_HEAD_SINGLY_LL(ll)) return 0;
    unsigned int curren_node_count = GET_NODE_COUNT_SINGLY_LL(ll);
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    while(trav != NULL){
        if(memcmp(trav->data, data, size) == 0){
            singly_ll_delete_node(ll, trav);
	    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
        }
        trav = trav->next;
    }
    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
}


unsigned int
singly_ll_remove_node_by_value(ll_t *ll, void *data, int size){
    if(!ll || !GET_HEAD_SINGLY_LL(ll)) return 0;
    unsigned int curren_node_count = GET_NODE_COUNT_SINGLY_LL(ll);
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    while(trav != NULL){
        if(memcmp(trav->data, data, size) == 0){
            singly_ll_remove_node(ll, trav);
	    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
        }
        trav = trav->next;
    }
    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
}


unsigned int
singly_ll_remove_node_by_dataptr(ll_t *ll, void *data){
    if(!ll || !GET_HEAD_SINGLY_LL(ll)) return 0;
    unsigned int curren_node_count = GET_NODE_COUNT_SINGLY_LL(ll);
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    while(trav != NULL){
        if(trav->data == data){
            singly_ll_remove_node(ll, trav);
            return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
        }
        trav = trav->next;
    }
    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
}


singly_ll_node_t*
singly_ll_get_node_by_data_ptr(ll_t *ll, void *data){
	if(!ll || !GET_HEAD_SINGLY_LL(ll)) return NULL;
	int i = 0;
	singly_ll_node_t *head = GET_HEAD_SINGLY_LL(ll);

	for(; i < GET_NODE_COUNT_SINGLY_LL(ll); i++){
		if(head->data == data)
			return head;
		head = GET_NEXT_NODE_SINGLY_LL(head);			
	}
	return NULL;
}


void print_singly_LL(ll_t *ll){
    if(!ll) {
        printf("Invalid Linked List\n"); 
        return;
    }
    if(is_singly_ll_empty(ll)){
        printf("Empty Linked List\n");
        return;
    }
    
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    unsigned int i = 0;
    printf("node count = %d\n", GET_NODE_COUNT_SINGLY_LL(ll));
    while(trav){
        printf("%d. Data = %p, node = %p\n", i, trav->data, trav);
        i++;
        trav = trav->next;
    }
}

bool_t 
is_singly_ll_empty(ll_t *ll){
    if(!ll) assert(0);
    if(ll->node_count == 0)
        return LL_TRUE;
    return LL_FALSE;
}

void 
reverse_singly_ll(ll_t *ll){
   if(!ll) assert(0) ;
   if(is_singly_ll_empty(ll)) return;
   if(GET_NODE_COUNT_SINGLY_LL(ll) == 1) return;
   singly_ll_node_t *p1 = GET_HEAD_SINGLY_LL(ll), 
                    *p2 = ll->head->next, *p3 = NULL;
   p1->next = NULL;
   do{
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
   }while(p3);
   ll->head = p1;
   return;
}

void
delete_singly_ll(ll_t *ll){
	if(!ll) return;

	if(is_singly_ll_empty(ll)){
		return;
	}

	singly_ll_node_t *head = GET_HEAD_SINGLY_LL(ll),
			 *next = GET_NEXT_NODE_SINGLY_LL(head);

	do{
		free(head);
		head = next;
		if(next)
			next = GET_NEXT_NODE_SINGLY_LL(next);

	} while(head);

	ll->node_count = 0;
	ll->head = NULL;
}

void singly_ll_set_comparison_fn(ll_t *ll, int (*comparison_fn)(void *, void *)){

    if(!ll) assert(0) ;
    ll->comparison_fn = comparison_fn;
}

void * 
singly_ll_search_by_key(ll_t *ll, void *key){

    assert(ll);
    if(!key)
        return NULL;

    singly_ll_node_t *list_node = NULL;
    ITERATE_LIST(ll, list_node){
        if(ll->comparison_fn(list_node->data, key))
            return list_node->data;
    }
    return NULL;
}
