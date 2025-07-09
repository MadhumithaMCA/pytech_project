#include<stdio.h>
#include<stdlib.h>

struct node{

	int data;
	struct node*link;
};

  void count_of_nodes(struct node *head){

                int count=0;

                if(head == NULL)

                        printf("the listis empty");
                struct node*ptr =NULL;
                ptr=head;

                while(ptr !=NULL){

                        count ++;
                        ptr = ptr->link;
                }
                printf("the number of nodes is:%d\n",count);
        }

void print_data(struct node *head){

	if(head==0)
		printf("the list is empty");

	struct node *ptr =NULL;
	ptr = head;

	while(ptr!=NULL){

		printf("%d\n",ptr->data);
		ptr = ptr->link;
	}
}

void add_at_the_end(struct node *head,int data){

	struct node *ptr ,*temp;
	ptr = head;

	temp = (struct node *)malloc(sizeof(struct node));
	    temp->data= data;
	    temp->link = NULL;

	    while(ptr->link !=NULL){

	      ptr =ptr->link;
	      }
	      ptr->link = temp;
	      printf("the list after adding node%d\n",data);
	 }

int main(){

	struct node *head = malloc(sizeof(struct node));
	head->data =43;
	head->link = NULL;

	struct node *current= malloc(sizeof(struct node));
	current->data=32;
	current->link = NULL;
	head->link=current;

	current= malloc(sizeof(struct node));
	current->data=22;
	current->link = NULL;

	head->link->link = current;

	count_of_nodes(head);
	print_data(head);
	add_at_the_end(head,55);
	print_data(head);
	count_of_nodes(head);




//	printf("the added nodes are :%d\n%d\n%d\n",head->data,head->link->data,head->link->link->data);
        return 0;       
}
