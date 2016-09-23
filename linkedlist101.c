#include <stdio.h>
#include <stdlib.h>

typedef struct lln {
    int val;
    struct lln *next;
} lln_t; 

lln_t *head;

void Insert (lln_t **head, lln_t *node, int position) {
  lln_t *aux_node, *p_node = NULL;
  int cur = 0;

  if (*head == NULL){
    (*head) = node;
    (*head)->next = NULL;
    return;
  }

  if (position == 1) {
    node->next = (*head);
    (*head)    = node;
    return;
  }

  aux_node = (*head);

  /* locate a node at position */
  while (aux_node && (cur < position)) {
    p_node   = aux_node;
    aux_node = aux_node->next;
    cur++;
  }

  p_node->next = node;
  if (aux_node) {
    node->next = aux_node;
  }

}


/*
 * HEAD is not given , you delete node by copying value of next node to current node,
 * and deleting next node
 * Tip: Delete the next node
 */
void delete_node2 (lln_t *node) {
  lln_t *tmp;
  if (!node) {
    return;
  }

  if (node->next)
    {
      node->val  = node->next->val;
      tmp  = node->next->next;
      printf("Deleted node with value %d\n", node->next->val);
      free(node->next);
      node->next = tmp;
    } else {
    node->val = -1;
    printf("Can't delete, as next node is null, but marked as DUMMY\n");
  }
}

void delete_node (lln_t **head, int val) {
  lln_t *tmp, *prev;

  if (*head == NULL){
    return;
  }

  printf("delete_node: %d\n",val);
  tmp = *head;

  if (tmp->val == val) {
    *head = tmp->next;
    printf("Freeing head node with val %d tmp= %p head = %p \n", tmp->val,tmp,*head);
    free(tmp);
    printf("New head is head %p, val %d\n",*head, (*head)->val);
    return;
  }

  while (tmp != NULL && tmp->val != val) {
    prev = tmp;
    tmp = tmp->next;
  }

  if (tmp == NULL) {
    printf("Node not found\n");
    return;
  }
  prev->next = tmp->next;
  printf("Freed node with val %d\n", tmp->val);
  free(tmp);
}

void delete_duplicate(lln_t **head) {
  lln_t *outer = *head;
  lln_t *inner; 
  int i = 0, j = 0;

  /* 1. Walk outerloop .
   * 2. Walk inner loop with rest of the node to find duplicate
   */
  while (outer) {
    i++;
    inner = outer;
    j = 0;
    while (inner) {
      j++;
      if (inner->next && inner->next->val == outer->val) {
	//Found duplicate
	printf("Found Duplicate nodes with index %d and index %d value %d\n",i, j, outer->val);
	inner->next = inner->next->next;
      } else {
	inner = inner->next;
      }
    }
    outer = outer->next;
  }  
}

void delete_all(lln_t **head) {

  lln_t *q, *tmp = *head;
  while (tmp) {
    q = tmp->next;
    printf("Freeing %d\n",tmp->val);
    free(tmp);
    tmp = q;
  }
  *head = NULL;
}

void print_ll(lln_t *node) {
    lln_t *tmp = node;

printf("\n");
 while(tmp) {
    printf("%d ", tmp->val);
    tmp = tmp->next;
 }
 printf("\n");

}

/* Find kth element from the last */
int findKthLast (lln_t *node, int k) {
  lln_t *first, *second;
  /*
    Use two pointers, walk k elements, next walk till end while walking from head with another ptr
  */
  //Walk k elements first
  first = node;
  for (int i = 0; i < k; i++) {
    first = first->next;
    if (first == NULL)
      return (-1);
  }

  second = node;
  while (first) {
    first  = first->next;
    second = second->next;
  }  
  return second->val;
}

/*
 * Remember ********
 * Floyd Algorithm 
 * 1 = has loop, 
 *  0 = no loop
 * -1 = invalid input.
 */
int findLoop (lln_t *head) {

  lln_t *fastp = head; 
  lln_t *slowp = head;
  int     loop = 0;

  // Check for NULL next pointers indicating no loop 
  while (fastp && fastp->next) {
    slowp = slowp->next;
    fastp = fastp->next->next;
    if (slowp == fastp) {
      break;
    }
  }
 
  if (!fastp || !fastp->next) {
    return loop;
  }

  /* Find the loop length, by moving one step */
  fastp = fastp->next;
  while (slowp != fastp) { 
    fastp = fastp->next;
    loop++;
  }

  /* Find the beginning of the loop */
  fastp = slowp;
  slowp = head;

  while (fastp != slowp) {
    fastp = fastp->next;
    slowp = slowp->next;
    
  }
  if(fastp && slowp)
    printf("Loop starts at node %d\n",fastp->val);
  return (loop+1); //No Loop
}



//Remember
/*
This trick might help you
there are three pointer ( prev, current, next)

next = current*
current* = prev
prev = current
current = next
NCPC
 */
void reverse (lln_t **head) {
  lln_t *current = *head;
  lln_t *next = NULL;
  lln_t *prev= NULL;
  
  while(current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head = prev;
  printf("List reversed\n");

}

lln_t * findMiddleNode(lln_t *head) {
  lln_t *slow = head;
  lln_t *fast = head;

  if(!slow){
    return NULL;
  }

  while (fast->next) {
    slow = slow->next;
    if(!fast->next->next)
      break;
    fast = fast->next->next;
  }
  return slow;

}

/*
 Each list represent a number, with head carrying LSB.
 e.g 566 is represented as   HEAD 2->1->5->NULL
    +566    
---------
    1132      HEAD 1->1->3->2->NULL

    * watch for carry over, and include new node to represent.
    * watch for shorter number(MSB node (at the TAIL ) will be missing,(substitute with zero)    
*/

lln_t *addTwoList (lln_t *first, lln_t *second) {
  lln_t *prev, *temp, *res = NULL;
  int carry = 0;
  int sum;
  while (first || second){
    sum = carry + (first?first->val:0) + (second?second->val:0);
    carry = sum >= 10 ? 1:0;
    sum = sum%10;
    temp = malloc(sizeof(lln_t));
    temp->val = sum;
    temp->next = NULL;
    if(res == NULL)
      res = temp;
    else 
      prev->next = temp;
    prev = temp;
    if(first) 
      first = first->next;
    if(second )
      second = second->next;
  }

  if(carry > 0) {
    temp = malloc(sizeof(lln_t));
    temp->val = carry;
    temp->next = NULL;
    prev->next = temp;
  
  }
  return res;
}

/*
 * Given linked list, partitition it with values at left less than x, and right greater than x.
 * Logic: walk list, build left and right list,   merge  them at the end. 
*/
void partition_at_x(lln_t **head, int x) {
  lln_t   *left  = NULL;
  lln_t   *right = NULL;
  lln_t   *next  = NULL;
  lln_t   *node  = *head;
  lln_t   *prev  = NULL;

  while(node){
    next = node->next;
    if(node->val >= x) {//Insert at right
      node->next = right;
      right = node;
    } else {
      node->next = left;
      left = node;
    }
    node = next;
  }

  *head = left;
  printf("Left:");
  print_ll(left);
  printf("\nRight:");
  print_ll(right);
  while(left){
    prev = left;
    left = left->next;
  }
  prev->next = right;
  print_ll(*head);

}


//TBD does not work
lln_t * reverse2(lln_t *head, lln_t *prev) {
  lln_t *tmp = head->next;
  head->next = prev;
  if ( tmp != NULL) {
    reverse2(tmp, head);
  }
  return head;
}

/*
1. Delete
2. Insert
3. Print 
4. Delete All
5. Delete Duplicate
6. FindMid
7. Find Loop + Find loop length + Find starting point of loop
8. Reverse
9. Find Kth Last
10. Partition list by value
11. Add two number(given in two linked list into a third list).
12. Palindrome Test(    e.g   1->2->3->2->1 is a palidrome)
    Create duplidate list, and reverse it. Compre first half of original and duplicate, if they
    are equal , they its a palindrome.
    Or,  Push half elements into stack, and compare by popping, if they are equal ,its a palindrome.
*/

int main (int argc, char *argv[]) {
  /*
   * LinkedList Operations
   1. Insert or Delete at End,Beginning, Middle.
   2. Count Nodes
   3. Delete All.
  */
  lln_t *node, *lastnode;
  lln_t *first;
  lln_t *second;
  lln_t *sum;

  int    d = 0;
  for (int i=1; i <= 6; i++) {
    node       = (lln_t *)malloc( sizeof(lln_t) );
    node->next = NULL;
    node->val  = 7-i;
    Insert(&head, node, 1);
  }

  lastnode = node;
  // Add Duplicate
  for (int i=1; i <= 6; i++) {
    node       = (lln_t *)malloc( sizeof(lln_t) );
    node->next = NULL;
    node->val  = i;
    //Insert(&head, node, 1);
  }

  //print_ll(head);
  //head = reverse2(head, NULL);

  print_ll(head);
  node=  findMiddleNode(head);
  printf("Middle Node Val %d\n",node->val);
  reverse(&head);
  print_ll(head);

  node=  findMiddleNode(head);
  printf("Middle Node Val %d\n",node->val);

  printf("Finding 3rd Last Element:");
  printf("Value of Kth Last %d\n", findKthLast(head,3));


  delete_duplicate(&head);
  print_ll(head);

  //Create Loop and test code
  lastnode->next = head;
  printf("Created loop by connecting copying head ptr into last node->next\n");
  printf("Has %d length loop \n", findLoop(head));

  //Undo loop
  printf("Undoloop\n");
  lastnode->next = NULL;
  print_ll(head);
  printf("Has %d length loop now \n", findLoop(head));

  print_ll(head);

  partition_at_x(&head, 4);
  printf("partition at 4:\n");
  print_ll(head);

  printf("Trying to Delete Node with val %d, without passing HEAD\n", node->val);
  delete_node2(node);

  print_ll(head);

  delete_node(&head, 8);
  print_ll(head);
  delete_node(&head, 1);
  print_ll(head);
  delete_node(&head, 3);
  print_ll(head);
  delete_node(&head, 5);
  print_ll(head);
  delete_all(&head);
  print_ll(head);

  //Add two number using LL
  // 566 
  // 566
  //1132
  node       = (lln_t *)malloc( sizeof(lln_t) );
  node->next = NULL;
  node->val  = 6;
   
  Insert(&first,node,1);
  node       = (lln_t *)malloc( sizeof(lln_t) );
  node->next = NULL;
  node->val  = 6;
  Insert(&first,node,1);
 
  node       = (lln_t *)malloc( sizeof(lln_t) );
  node->next = NULL;
  node->val  = 5;
  Insert(&first,node,1);
  printf("Adding two list:\n");
  print_ll(first);
  printf("\n");
  print_ll(first);
  printf("----------");
  sum = addTwoList(first,first);
  print_ll(sum);

}