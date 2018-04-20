#include "stdafx.h"
#include <stdlib.h>

typedef struct node {
	int data;           // Данные (полезная часть данных)
	struct node * next; // Указатель на следующий элемент (вспомогальная часть)
} node_t;


typedef struct list {
	node_t* head;       // Указатель на начало списка (голову)
	unsigned int size;  // Размер списка (количество элементов)
} list_t;

list_t* create_list(void);                      // Создать список
node_t* create_node(int x, node_t* next);       // Создать элемент списка (вспомогательная)
node_t* append_list(list_t* const lst, int x);  // Добавить элемент в конец списка
node_t* prepend_list(list_t* const lst, int x); // Добавить элемент в начало списка
int pop_list(list_t * const lst);               // Извлечь первый элемент списка
void print_list(const list_t * const lst);      // Вывести список
void free_list(list_t * const lst);             // Удалить список
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

	node_t* current = lst->head; // Начинаем с головы списка
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
Добавить элемент в начало списка
@param  list_t* const lst — указатель на связный список (контейнер)
@param  int x — значение элемента
@return node_t* — указатель на добавленный элемент
*/
node_t* prepend_list(list_t* const lst, int x)
{
	// Создаем новый элемент. Поле next указывает на текущую голову,
	// так как элемент будет стоять первым в списке
	node_t* p_new_node = create_node(x, lst->head);
	if (p_new_node != NULL) {
		// Делаем головой списка новый элемент
		lst->head = p_new_node;
		// Инкрементируем счетчик (длина списка)
		++lst->size;
	}

	// Возвращаем указатель на новый элемент
	return p_new_node;
}

/*
Извлечь первый элемент списка
Извлечение — это возврат первого элемента из списка + удаление его.
@param  list_t* const lst — указатель на связный список (контейнер)
@return int — значение первого элемента списка
*/
int pop_list(list_t * const lst)
{
	// Если список пустой, то возвращаем 0. Это наша договоренность.
	if (lst->head == NULL) {
		return 0;
	}
	// Запоминаем куда указывает элемент. Иначе данные потеряются, когда мы его удалим
	node_t* next = lst->head->next;
	// Запоминаем значение элемента. Иначе данные потеряются, когда мы его удалим
	int data = lst->head->data;
	// Освобождаем память, которую выделяли для элемента (удаляем)
	free(lst->head);
	// Новая голова — то, куда указывал первый элемент
	lst->head = next;
	// Декрементируем счетчик (длина списка)
	--lst->size;

	// Возвращаем сохранненое значение элемента
	return data;
}

/*
Вывести список
Выводим элементы связного списка один за одним через пробел
@param  const list_t * const lst — указатель на связный список (контейнер)
*/
void print_list(const list_t * const lst)
{
	// Если список пустой, то ничего не делаем
	if (lst->head == NULL) {
		return;
	}
	// Идем по списку. Начинаем с головы
	node_t* current = lst->head;
	while (current != NULL) {
		// Выводим значение каждого элемента
		printf("%i ", current->data);
		current = current->next;
	}
	// Заканчиваем строку
	printf("\n");
}

/*
Удалить список
Освобождаем память
@param  list_t * const — указатель на связный список (контейнер)
*/
void free_list(list_t * const lst)
{
	// Удаляем память элементов. Имеет смысл если список не пустой.
	if (lst->head != NULL) {
		// Идем по списку. Начинаем с головы
		node_t* current = lst->head;
		while (current != NULL) {
			// Запоминаем куда указывает элемент. Мы его удалим и данные потеряются
			node_t* next = current->next;
			// Освобождаем память, которую выделяли для элемента (удаляем)
			free(current);
			current = next;
		}
	}
	// Удаляем список (контейнер)
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
	// Если список пустой, то ничего не делаем
	if (Copy_list->head == NULL) {
		return;
	}
	// Идем по списку. Начинаем с головы
	node_t* current = Copy_list->head;
	while (current != NULL) {
		// Выводим значение каждого элемента
		printf("%i ", current->data);
		current = current->next;
	}
	// Заканчиваем строку
	printf("\n");
}
