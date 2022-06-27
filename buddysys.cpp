//////////////////////////////////////////////////////////////////////////////////
//
//   Program Name:  Buddy System Algorithm
//                  
//   Description:  Buddy System Algorithm
//                  
//   Student name:
//
//
//
//////////////////////////////////////////////////////////////////////////////////

#include "buddysys.h"
#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////

void insertEnd(Node** head, int data){
   Node* newNode = new Node;
   Node* last = *head;
   newNode->size = data;
   newNode->next = NULL;
   if(*head == NULL){
      newNode->previous = NULL;
      *head = newNode;
      return;
   }
   while(last->next != NULL){
      last = last->next;
      last->next = newNode;
      newNode->previous = last;
      return;
   }
}

void deleteNode(Node** head, Node* del_node){
   if(*head == NULL || del_node == NULL){
      return;
   }
   if(*head == del_node){
      *head = del_node->next;
   }
   if(del_node->next != NULL){
      del_node->next->previous = del_node->previous;
   }
   if(del_node->previous != NULL){
      del_node->previous->next = del_node->next;
   }
}

void displayList(Node* node){
   Node* last;
   while(node != NULL){
      cout << node->size << "->";
      last = node;
      node = node->next;
   }
   if(node == NULL){
      cout << "NULL\n";
   }
}

void *buddyMalloc(int request_memory){

    ///////////////////////////////////    
    //put your implementation here
   void *p;
   bool empty = true;

   // Find the smallest bin
   int memory_request = request_memory + sizeof(Node);
   int bin = 1;
   int smallest_k = 0;
   while(bin < memory_request){
      bin*=2;
      smallest_k++;
   }
   // Maximum bin
   int k = 0;
   int num = 1;
   while(num < MEMORYSIZE){
      num *= 2;
      k++;
   }
   int max_k = k;
   // If desired bin is larger than maximum return NULL;
   if(smallest_k > max_k){
      printf("Failed to allocate\n");
      return NULL;
   }

   // Find Minimum k
   while(num > sizeof(Node)*2){
      num /= 2;
      k--;
   }
   int min_k = k;
   p=allocpages((memory_request/PAGESIZE)+1);
   // Range of the Free list
   int range = max_k - min_k;

   while(wholememory){
      if(wholememory->next){
         empty = false;
         break;
      }
      wholememory = wholememory->next;
   }
   
   long long int tmp = MEMORYSIZE;
   while(sizeof(Node) < tmp){
      if(tmp/2 < memory_request && memory_request <= tmp){
         insertEnd(&wholememory, tmp);
         break;
      }
      else{
         tmp/=2;
         insertEnd(&wholememory, tmp);
         deleteNode(&wholememory, wholememory);
      }
   }
   
   //return (void*)((Node*)((uintptr_t)wholememory+(uintptr_t)sizeof(Node)));
   return p;
} 

int buddyFree(void *p){

   ///////////////////////////////////
   //put your implementation here
   //Node* data = (Node*)((uintptr_t)p - (uintptr_t)sizeof(Node));
   //deleteNode(&wholememory, data);
   int n;
   n=freepages(p);
   if(!n) puts("Failed");
   return n;
   
}