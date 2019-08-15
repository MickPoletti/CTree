/* Mason McDaniel UTAID: 1001456342 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char* n;

    struct node* left;
    struct node* right;
};

int main()
{
	FILE *fp;
	fp = fopen("data-tree.txt", "r");
	if(fp == NULL)
	{
		printf("ERROR: Cant open file!");
		exit(1);
	}
	else
	{
		/* File successfully loaded */
		readFile(fp);
	}
	return 0;
}

void preOrder(struct node* root) {
   if(root == NULL)
       return;

   printf("%s ", root->n);
   preOrder(root->left);
   preOrder(root->right);
}

void inOrder(struct node* root) {
   if(root == NULL)
       return;

   inOrder(root->left);
   printf("%s ", root->n);
   inOrder(root->right);
}

void postOrder(struct node* root) {
   if(root == NULL)
       return;

   postOrder(root->left);
   postOrder(root->right);
   printf("%s ", root->n);
}

void freeMem(struct node* root) {
   if(root == NULL)
       return;

   freeMem(root->left);
   freeMem(root->right);
   printf("freeing %d\n", root->n);
   free(root);
}


struct node* addNode(char* element) {
    struct node* temp = malloc( sizeof(struct node) );

    temp->n = element;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

struct node* balance(char** array, int first_index, int last_index)
{
	int middle_index;
	struct node* temp;
	if(first_index <= last_index)
	{
		middle_index = first_index + (last_index - first_index)/2;
		temp = addNode(array[middle_index]);

		temp->left = balance(array, first_index, middle_index-1);
		temp->right = balance(array, middle_index+1,last_index);

		return temp;
	}
	else
	{
		return NULL;
	}
}

char** msort(char** array, int count)
{
	int i, j, swapped;
	char *temp;
	struct node* root;
	for(i=0; i<count-1; i++)
	{
		swapped = 0;
		for(j=0;j<count-i-1; j++)
		{
			if(strcmp(array[j], array[j+1])>0)
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp; 
				swapped = 1;
			}
		}
		if(swapped == 0)
		{
			break;
		}
	}
	return(array); 
}

void printMenu(struct node* root)
{
	printf("\n");
	printf(" preorder: ");
	preOrder(root);
	printf("\n");
	printf("\n");
	printf("  inorder: ");
	inOrder(root);
	printf("\n");
	printf("\n");
	printf("postorder: ");
	postOrder(root);
	printf("\n");
}

int readFile(FILE* fp)
{
	char **array = calloc(2, sizeof(char*));
	char buffer[21] = {0};
	int i, count, addresses;
	struct node* root;
	count = 0;
	addresses = 2;
	for(i=0;i<2;++i)
	{
		array[i] = (char*)malloc(21);
	}

	while(fgets(buffer, 21, fp) != 0)
	{	
		char **temp = calloc(2, sizeof(char*));
		char *pos, *dst;
	
        if((pos=strchr(buffer, '\n')) != NULL)
        {
            *pos = '\0';
        }
		if(count == addresses)
		{
			addresses *= 2;
			temp = realloc(array, (addresses * sizeof(char*)));
			printf("reallocating to %d addresses\n", addresses);
			if(temp != NULL)
			{
				array = temp;
					
			}
			else
			{
				printf("unable to reallocate\n");
				free(temp);
				free(array);
				exit(1);
			}
			/*
			for(i=count+1; i<addresses+1; i++)
			{
				array[i] = (char*)malloc(20);
			}*/
		}
		dst = malloc(strlen(buffer)+1);
		if(dst == NULL)
		{
			printf("unable to allocate\n");
			exit(1);
		}
		strcpy(dst, buffer);
		array[count] = dst;
		count++;

	}
	
	array = msort(array,count);
	root = balance(array, 0, count-1);
	printMenu(root);	
}

