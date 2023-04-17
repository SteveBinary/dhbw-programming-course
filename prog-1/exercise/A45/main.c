/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: SteveBinary
 *
 * Created on 10. März 2021, 14:06
 */

#include <stdio.h>
#include <stdlib.h>

struct list_item
{
    struct list_item* previous;
    struct list_item* next;
    char value;
};

typedef struct list_item* ListItem;

int PrintListOf(ListItem head);
ListItem CreateListItem(ListItem previous, ListItem next, char value);
ListItem InsertAfter(ListItem item, char value);
ListItem InsertBefore(ListItem item, char value);
ListItem Delete(ListItem item); //TODO
ListItem DeleteAll(ListItem item); //TODO
ListItem DeleteAfter(ListItem item); //TODO
ListItem DeleteBefore(ListItem item); //TODO
ListItem Search(ListItem item, char value);

int main()
{
    ListItem root = CreateListItem(NULL, NULL, 'a');

    ListItem current = root;
    for (int i = 'b'; i <= 'z'; ++i)
    {
        InsertAfter(current, (char) i);
        current = current->next;
    }

    PrintListOf(root);

    return (EXIT_SUCCESS);
}

ListItem CreateListItem(ListItem previous, ListItem next, char value)
{
    ListItem item = (ListItem) calloc(1, sizeof (ListItem));
    item->previous = previous;
    item->next = next;
    item->value = value;
    return item;
}

int PrintListOf(ListItem item)
{
    if (NULL == item) return (EXIT_FAILURE);

    // searching head of list
    ListItem current = item;
    while (NULL != current->previous)
    {
        current = current->previous;
    }

    while (NULL != current)
    {
        printf("%c\n", current->value);
        current = current->next;
    }

    return (EXIT_SUCCESS);
}

ListItem InsertAfter(ListItem item, char value)
{
    if (NULL == item) return (NULL);
    
    ListItem newItem = CreateListItem(item, item->next, value);
    item->next = newItem;
    return newItem;
}

ListItem InsertBefore(ListItem item, char value)
{
    if (NULL == item) return (NULL);

    ListItem newItem = CreateListItem(item->previous, item, value);
    if (newItem->previous) newItem->previous->next = newItem;
    item->previous = newItem;
    return newItem;
}

ListItem Search(ListItem item, char value)
{
    if (NULL == item) return (NULL);

    // searching head of list
    ListItem current = item;
    while (NULL != current->previous)
    {
        current = current->previous;
    }

    while (NULL != current)
    {
        if (value == current->value) {
            return current;
        }
        current = current->next;
    }
    
    return (NULL);
}
