#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	//Check for null pointer
	if (head==NULL) {return 0;}
	//Start separate so they don't immediatly collide
	node* current = head->next;
	node* slow = head;
	
	//Loop
	int count = 1;
	while(current!=NULL) {
		if (current==slow) {
			return -1;
		}
		current=current->next;
		if(count%2==0) {
			slow=slow->next;
		}
		count++;
	}
	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	//Make use of length function
	int size = length(head);
	char* str;

	//If it's zero or less malloc an empty string
	if (size<=0) {
		str = (char*)malloc(sizeof(char));
		if (str==NULL) {
			//Exit because i can't find any other way to avoid undefined behavior
			//Specifically, printf has undefined behavior with treating null pointers as strings
			exit(-1);
		}
		*str = '\0';
		return str;
	}


	str = (char*)malloc((size+1)*sizeof(char));
	if (str==NULL) {
		//Try to malloc an empty string
		str = (char*)malloc(sizeof(char));
		if (str==NULL) {
			//Exit to avoid undefined behaviors
			exit(-1);
		}
	}
	node* current = head;
	//Loop through elements
	for (int i = 0; i<size; i++) {
		if (current == NULL) {
			//Double check for null
			*(str+i) = '\0';
			return str;
		}
		*(str+i) = current->letter;
		current = current->next;
	}
	*(str+size) = '\0';
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	if (pHead==NULL) {return;}
	int size = length(*pHead);
	if (size<0) {return;}
	if (size==0) {
		*pHead = (node*)malloc(sizeof(node));
		if (*pHead!=NULL) {
			(*pHead)->letter = c;
		}
		return;
	}
	node* current = *pHead;
	int count = 1;
	while (current->next!=NULL) {
		if (count>=size) {
			return;
		}
		current = current->next;
		count++;
	}
	current->next = (node*)malloc(sizeof(node));
	current=current->next;
	if (current!=NULL) {
		current->letter = c;
	}
	return;
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	if (pHead==NULL) {return;}
	int size = length(*pHead);
	if (size<0) {
		//IDK
		return;
	}
	if (size<=1) {
		//Freeing null pointers is fine
		free(*pHead);
		return;
	}
	while (size>0) {
		node* current = *pHead;
		if (current==NULL) {break;}
		if (current->next==NULL) {
			free(current);
			size=0;
			break;
		}
		while (current->next->next!=NULL) {
			current=current->next;
		}
		free(current->next);
		//Prevent use after free
		current->next=NULL;
		size--;
	}
	return;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}