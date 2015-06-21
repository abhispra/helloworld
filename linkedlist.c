#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	struct node* next;
	int val;
}Node;

unsigned length(Node* head)
{
	unsigned len = 0;
	Node* current = head;

	while(current != NULL)
	{
		len++;
		current = current->next;
	}
	return len;
}

int insert(Node** head, int val, unsigned pos)
{
	int err = 0;
	Node* current = NULL, *newNode = NULL;
	unsigned len = 0;

	if (head == NULL)
	{
		printf("Invalid input\n");
		goto ERR_EXIT;
	}
	
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Failed to allocate memory\n");
		err = -1;
		goto ERR_EXIT;
	}
	
	newNode->val = val;
	current = *head;
	
	if (current == NULL)
	{
		if (pos != 0)
		{
			printf("Invalid position specified for an empty list");
			err = -1;
			goto ERR_EXIT;
		}
		else
		{
			*head = newNode;
			newNode->next = NULL;
		}
	}
	else
	{
		while(current->next != NULL && len != pos -1)
		{
			current = current->next;
			len++;
		}
		if (len == pos - 1)
		{
			newNode->next = current->next;
			current->next = newNode;
		}
		else
		{
			printf("Invalid position(%d) specified", pos);
			err = -1;
			goto ERR_EXIT;
		}
	}
	
ERR_EXIT:
	if (err)
	{
		free(newNode);
	}
	return err;
}

void print(Node* head)
{
	Node* current = head;

	while(current != NULL)
	{
		printf("%d\n", current->val);
		current = current->next;
	}
}

void delete(Node** head)
{
	Node* current = NULL, *ptr = NULL;
	if (head != NULL)
	{
		current = *head;
		while(current != NULL)
		{
			ptr = current->next;
			free(current);
			current = ptr;
		}
		*head = NULL;
	}
}
int deleteat(Node**head, unsigned pos, int* val)
{
	int err = 0;
	Node* current = NULL, *prev = NULL;
	unsigned len = 0;
	
	if (head == NULL)
	{
		printf("Invalid pointer input\n");
		err = -1;
		goto ERR_EXIT;
	}
	current = prev = *head;
	
	if (current == NULL)
	{
		printf("Empty list, returning\n");
		goto ERR_EXIT;
	}

	if (pos == 0)
	{
		*head = current->next;
		if (val)
			*val = current->val;
		free(current);
	}
	else
	{
		while(current->next != NULL && len != pos)
		{
			prev = current;
			current = current->next;
			len++;
		}
		if (len == pos)
		{
			prev->next = current->next;
			if (val)
				*val = current->val;
			free (current);
		}
		else
		{
			printf("Invalid position specified - %d\n", pos);
			err = -1;
			goto ERR_EXIT;
		}
	}
ERR_EXIT:
	return err;
}

#define LEN_MAX    100

int main(int argc, char* argv[])
{
	Node *head = NULL;
	unsigned i = 0, randVal = 0;
	int err = 0, val = 0;
	time_t t;
	
	srand((unsigned) time(&t));
	
	print(head);
	for (i = 0; i < LEN_MAX; i++)
	{
		if ((err = insert(&head, i, i)) != 0)
		{
			printf("insert returned err for val %d, pos %d, breaking\n", i, i);
			break;
		}
	}
	print(head);
	printf("Length of list - %d\n", length(head));
	for (i = 0; i < LEN_MAX; i++)
	{
		randVal = rand() % LEN_MAX;
		deleteat(&head, randVal, &val);
	}
	print(head);
	printf("Length of list - %d\n", length(head));
	delete(&head);
	return 0;
}