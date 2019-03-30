#include <iostream>
#include <memory>

using namespace std;

class Node
{
public:
  int data;
  shared_ptr<Node> next;
  Node(int data) : data(data), next(NULL) {}
  Node() : data(-1), next(NULL) {}
};

class List
{
public:
  List(int *nums, int len);
  void print();
  void reverse();
  shared_ptr<Node> middleItem();
private:
  shared_ptr<Node> head;
  void create(int *nums, int len);
};

List::List(int *nums, int len)
{
  create(nums, len);
}

void List::create(int *nums, int len)
{
  shared_ptr<Node> p, pre_p;
  head = make_shared<Node>(Node());
  p = NULL;
  pre_p = head;
  for (int i=0; i < len; ++i) {
    p = make_shared<Node>(Node(nums[i]));
    pre_p->next = p;
    pre_p = p;
  }
}

void List::print()
{
  shared_ptr<Node> p(nullptr);
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
  shared_ptr<Node> p = head->next;
  shared_ptr<Node> post_p = NULL;
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

shared_ptr<Node> List::middleItem()
{
  if (head == NULL)
    return NULL;
  shared_ptr<Node> mid, cur;
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
