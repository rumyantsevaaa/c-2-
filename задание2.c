#include "stdafx.h"
#include <stdlib.h>

typedef struct node {
	int data;           // ������ (�������� ����� ������)
	struct node * next; // ��������� �� ��������� ������� (������������� �����)
} node_t;


typedef struct list {
	node_t* head;       // ��������� �� ������ ������ (������)
	unsigned int size;  // ������ ������ (���������� ���������)
} list_t;

list_t* create_list(void);                      // ������� ������
node_t* create_node(int x, node_t* next);       // ������� ������� ������ (���������������)
node_t* append_list(list_t* const lst, int x);  // �������� ������� � ����� ������
node_t* prepend_list(list_t* const lst, int x); // �������� ������� � ������ ������
int pop_list(list_t * const lst);               // ������� ������ ������� ������
void print_list(const list_t * const lst);      // ������� ������
void free_list(list_t * const lst);             // ������� ������
struct node* CopyList(struct node* head);

int main(void)
{
	list_t* plist = create_list();
	list_t* plist2 = CopyList(plist);
	for (int i = 0; i<10; ++i) {
		append_list(plist, i);
	}
	print_list(plist);
	prepend_list(plist, 9000);
	print_list(plist);
	pop_list(plist);
	pop_list(plist);
	pop_list(plist);
	print_list(plist);
	free_list(plist);

	print_Copy(plist2);
	return 0;
}

list_t* create_list(void)
{
	list_t* p_new_list = (list_t*)malloc(sizeof(list_t));
	p_new_list->head = NULL;
	p_new_list->size = 0;
	return p_new_list;

}

node_t* create_node(int x, node_t* next)
{
	node_t* p_new_node = (node_t*)malloc(sizeof(node_t));
	if (p_new_node == NULL) {
		return NULL;
	}

	p_new_node->data = x;
	p_new_node->next = next;

	return p_new_node;
}


node_t* append_list(list_t* const lst, int x)
{
	node_t* p_new_node = create_node(x, NULL);

	node_t* current = lst->head; // �������� � ������ ������
	if (current != NULL)
	{
		while (current->next != NULL) {
			current = current->next;
		}

		current->next = p_new_node;
	}
	else
	{
		lst->head = p_new_node;
	}

	++lst->size;

	return p_new_node;
}

/*
�������� ������� � ������ ������
@param  list_t* const lst � ��������� �� ������� ������ (���������)
@param  int x � �������� ��������
@return node_t* � ��������� �� ����������� �������
*/
node_t* prepend_list(list_t* const lst, int x)
{
	// ������� ����� �������. ���� next ��������� �� ������� ������,
	// ��� ��� ������� ����� ������ ������ � ������
	node_t* p_new_node = create_node(x, lst->head);
	if (p_new_node != NULL) {
		// ������ ������� ������ ����� �������
		lst->head = p_new_node;
		// �������������� ������� (����� ������)
		++lst->size;
	}

	// ���������� ��������� �� ����� �������
	return p_new_node;
}

/*
������� ������ ������� ������
���������� � ��� ������� ������� �������� �� ������ + �������� ���.
@param  list_t* const lst � ��������� �� ������� ������ (���������)
@return int � �������� ������� �������� ������
*/
int pop_list(list_t * const lst)
{
	// ���� ������ ������, �� ���������� 0. ��� ���� ��������������.
	if (lst->head == NULL) {
		return 0;
	}
	// ���������� ���� ��������� �������. ����� ������ ����������, ����� �� ��� ������
	node_t* next = lst->head->next;
	// ���������� �������� ��������. ����� ������ ����������, ����� �� ��� ������
	int data = lst->head->data;
	// ����������� ������, ������� �������� ��� �������� (�������)
	free(lst->head);
	// ����� ������ � ��, ���� �������� ������ �������
	lst->head = next;
	// �������������� ������� (����� ������)
	--lst->size;

	// ���������� ����������� �������� ��������
	return data;
}

/*
������� ������
������� �������� �������� ������ ���� �� ����� ����� ������
@param  const list_t * const lst � ��������� �� ������� ������ (���������)
*/
void print_list(const list_t * const lst)
{
	// ���� ������ ������, �� ������ �� ������
	if (lst->head == NULL) {
		return;
	}
	// ���� �� ������. �������� � ������
	node_t* current = lst->head;
	while (current != NULL) {
		// ������� �������� ������� ��������
		printf("%i ", current->data);
		current = current->next;
	}
	// ����������� ������
	printf("\n");
}

/*
������� ������
����������� ������
@param  list_t * const � ��������� �� ������� ������ (���������)
*/
void free_list(list_t * const lst)
{
	// ������� ������ ���������. ����� ����� ���� ������ �� ������.
	if (lst->head != NULL) {
		// ���� �� ������. �������� � ������
		node_t* current = lst->head;
		while (current != NULL) {
			// ���������� ���� ��������� �������. �� ��� ������ � ������ ����������
			node_t* next = current->next;
			// ����������� ������, ������� �������� ��� �������� (�������)
			free(current);
			current = next;
		}
	}
	// ������� ������ (���������)
	free(lst);
}
list_t* CopyList(const list_t * const lst)
{
	if (lst->head == NULL) {
		return NULL;
	}
	else
	{
		list_t* Copy_list = (list_t*)malloc(sizeof(list_t));
		Copy_list->head = lst->head;
		Copy_list->size = lst->size;
		return(Copy_list);

	}
}
void print_Copy(const list_t * const Copy_list)
{
	// ���� ������ ������, �� ������ �� ������
	if (Copy_list->head == NULL) {
		return;
	}
	// ���� �� ������. �������� � ������
	node_t* current = Copy_list->head;
	while (current != NULL) {
		// ������� �������� ������� ��������
		printf("%i ", current->data);
		current = current->next;
	}
	// ����������� ������
	printf("\n");
}
