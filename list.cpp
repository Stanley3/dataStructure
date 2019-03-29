#include <iostream>

using namespace std;

class Node
{
public:
  int data;
  Node *next;
  ~Node()
  {
    if (next != NULL)
      delete next;
  }
  Node(int data) : data(data), next(NULL) {}
  Node() : data(-1), next(NULL) {}
};

class List
{
public:
  List(int *nums, int len);
  ~List()
  {
    if (head != NULL)
      delete head;
  }
  void print();
  void reverse();
  Node *middleItem();
private:
  Node *head;
  void create(int *nums, int len);
};

List::List(int *nums, int len)
{
  create(nums, len);
}

void List::create(int *nums, int len)
{
  Node *p, *pre_p;
  head = new Node();
  p = NULL;
  pre_p = head;
  for (int i=0; i < len; ++i) {
    p = new Node(nums[i]);
    pre_p->next = p;
    pre_p = p;
  }
}

void List::print()
{
  Node *p = NULL;
  if (head != NULL)
    p = head->next;
  while (p != NULL) {
    cout << p->data << " ";
    p = p->next;
  }
  cout << endl;
}

void List::reverse()
{
  if (head == NULL)
    return;
  Node *p = head->next;
  Node *post_p = NULL;
  head->next = NULL;
  while(p != NULL) {
    post_p = p->next;
    if (head->next == NULL) {
      head->next = p;
      p->next = NULL;
    } else {
      p->next=head->next;
      head->next = p;
    }
    p = post_p;
  }
}

Node *List::middleItem()
{
  if (head == NULL)
    return NULL;
  Node *mid, *cur;
  mid = cur = head->next;
  while(cur != NULL && cur->next != NULL) {
    mid = mid->next;
    cur = cur->next;
    cur = cur->next;
  }

  return mid;
}

int main()
{
  int nums[] = {1, 3, 5, 9, 8, 3, 6};
  List list(nums, 7);
  cout << "Normal list: ";
  list.print();
  cout << "After reverse: ";
  list.reverse();
  list.print();

  cout << "Middle Item is: " << list.middleItem()->data;
  cout << endl;

  return 0;
}
