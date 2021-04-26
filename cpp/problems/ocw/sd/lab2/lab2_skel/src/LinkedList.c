#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    /* TODO */
    struct linked_list_t *ll;
    ll = (struct linked_list_t*) malloc(sizeof(struct linked_list_t));
    ll->data_size = data_size;
    ll->head = 0x0;
    ll->size = 0;
    return ll;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    /* TODO */
    unsigned int i;
    struct ll_node_t* newest;
    struct ll_node_t* current;

    newest = (struct ll_node_t*) malloc(sizeof(struct ll_node_t));

    newest->data = malloc(list->data_size);
    for (i = 0; i < list->data_size; i++) {
        *(char *)(newest->data + i) = *(char *)(new_data + i);
    }
    if (list->size == 0) {
        newest->next = 0x0;
        list->head = newest;
    } else {
        if (n < list->size) {
            current = list->head;
            if (n == 0) {
                newest->next = current;
                list->head = newest;
            } else {
                while(--n) current = current->next;
                newest->next = current->next;
                current->next = newest;
            }
        } else {
            current = list->head;
            while(current->next) {
                current = current->next;
            }
            newest->next = 0x0;
            current->next = newest;
        }
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    /* TODO */
    unsigned int i = 0;
    ll_node_t* prev = 0x0;
    ll_node_t* current = list->head;
    /* struct ll_node_t* to_be_deleted; */

    if (n == 0) {
        list->head = list->head->next;
    } else {
        if (n < list->size) {
            while(n) {
                prev = current;
                current = current->next;
                n--;
            }
            if (prev) {
                prev->next = current->next;
            } else {
                current = list->head;
                list->head = list->head->next;
            }
        } else {
            while(current->next) {
                prev = current;
                current = current->next;
            }
            if (prev) {
                prev->next = 0x0;
            } else {
                list->head = 0x0;
            }
        }
    }
    list->size--;
    return current;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
    /* TODO */
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    /* TODO */
    ll_node_t* current = list->head;
    while(current) {
        printf("%i ", *((int*)current->data));
        current = current->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    /* TODO */
    ll_node_t* current = list->head;
    while(current) {
        printf("%s ", current->data);
        current = current->next;
    }

    printf("\n");
}
