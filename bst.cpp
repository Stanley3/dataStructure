#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void processData(int data)
{
  cout << data << " ";
}
class Node
{
public:
  int data;
  Node *parent;
  Node *left;
  Node *right;
  Node(): data(-1), parent(NULL), left(NULL), right(NULL) {}
  Node(int num): data(num), parent(NULL), left(NULL), right(NULL) {}
  ~Node()
  {
    if (left != NULL)
      delete left;
    if (right != NULL)
      delete right;
  }
};

class Tree
{
public:
  Tree(int num[], int len);
  void insertNode1(int data); //递归实现插入
  void insertNode(int data); //非递归实现插入
  Node *searchNode(int data);
  void deleteNode(int data);
  void inOrderTree(); // 递归实现
  void inOrderTree1(); // 非递归实现
  void preOrderTree(); //递归实现
  void preOrderTree1(); // 非递归实现
  void postOrderTree(); //递归实现
  void postOrderTree1(); //非递归实现
  void levelOrderTree(); // 层次遍历
  ~Tree()
  {
    if (root != NULL)
      delete root;
  }
private:
  void insertNode(Node *current, int data);
  Node *searchNode(Node *current, int data);
  void deleteNode(Node *current);
  void inOrderTree(Node *current);
  void preOrderTree(Node *current);
  void postOrderTree(Node *current);
  Node *root;
};

Tree::Tree(int num[], int len)
{
  root = new Node(num[0]);
  for (int i=1; i<len; ++i) {
    insertNode1(num[i]);
  }
}

void Tree::insertNode1(int data)
{
  insertNode(root, data);
}
void Tree::insertNode(Node *current, int data)
{
  if (current->data > data) {
    if (current->left == NULL) {
      current->left = new Node(data);
      current->left->parent = current;
    } else {
      insertNode(current->left, data);
    }
  } else if (current->data < data) {
    if (current->right == NULL) {
      current->right = new Node(data);
      current->right->parent = current;
    } else {
      insertNode(current->right, data);
    }
  } else {
    return;
  }
}

void Tree::insertNode(int data)
{
  Node *p, *prev_p, *newNode;
  p = root;
  prev_p = NULL;
  while(p) {
    prev_p = p->parent;
    if (p->data > data)
      p = p->left;
    else if (p->data < data)
      p = p->right;
    else
      return;
  }

  newNode = new Node(data);
  newNode->parent = prev_p;
  if (prev_p->data > data)
    prev_p->left = newNode;
  else
    prev_p->right = newNode;
}

Node * Tree::searchNode(int data)
{
  return searchNode(root, data);
}

Node * Tree::searchNode(Node *current, int data)
{
  if (current == NULL)
    return NULL;

  if (current->data > data)
    return searchNode(current->left, data);
  else if (current->data < data)
    return searchNode(current->right, data);
  else
    return current;
}

void Tree::deleteNode(int data)
{
  Node *n = searchNode(data);
  if (n != NULL)
    deleteNode(n);
}

void Tree::deleteNode(Node *current)
{
  if (current->left != NULL)
    deleteNode(current->left);

  if (current->right != NULL)
    deleteNode(current->right);

  if (current->parent == NULL) {
    delete current;
    root = NULL;
    return;
  }

  if (current->parent->data > current->data)
    current->parent->left = NULL;
  else
    current->parent->right = NULL;

  delete current;
}

void Tree::inOrderTree()
{
  inOrderTree(root);
}

void Tree::inOrderTree(Node *current)
{
  if (current != NULL) {
    inOrderTree(current->left);
    processData(current->data);
    inOrderTree(current->right);
  }
}

void Tree::inOrderTree1()
{
  stack<Node *> stack;
  Node *p;
  p = root;
  while (p != NULL || !stack.empty()) {
    while(p != NULL) {
      stack.push(p);
      p = p->left;
    }

    if (!stack.empty()) {
      p = stack.top();
      stack.pop();
      processData(p->data);
      p = p->right;
    }
  }
}

void Tree::preOrderTree()
{
  preOrderTree(root);
}

void Tree::preOrderTree(Node *current)
{
  if (current != NULL) {
    processData(current->data);
    preOrderTree(current->left);
    preOrderTree(current->right);
  }
}

void Tree::preOrderTree1()
{
  stack<Node *> stack;
  Node *p = root;

  while (p != NULL || !stack.empty()) {

    while(p != NULL) {
      processData(p->data);
      stack.push(p);
      p = p->left;
    }

    if (!stack.empty()) {
      p = stack.top();
      stack.pop();
      p = p->right;
    }
  }
}

void Tree::postOrderTree()
{
  postOrderTree(root);
}

void Tree::postOrderTree(Node *current)
{
  if (current != NULL) {
    postOrderTree(current->left);
    postOrderTree(current->right);
    processData(current->data);
  }
}

/*
 * 思路：要保证根节点在左右子节点被访问之后，才能访问。如果不存在左孩子和右孩子，则可以直接访问它；
 * 或者存在左孩子或右孩子，但是左孩子或右孩子都已被访问了，则同样可以直接访问该节点。
 */
void Tree::postOrderTree1()
{
  stack<Node *> stack;
  Node *cur, *pre = NULL;
  if (root != NULL)
    stack.push(root);

  while(!stack.empty()) {
    cur = stack.top();
    if ((cur->left == NULL && cur->right == NULL) ||
        (pre != NULL && (pre == cur->left || pre == cur->right))) {
      processData(cur->data);
      stack.pop();
      pre = cur;
    } else {
      if (cur->right != NULL)
        stack.push(cur->right);
      if (cur->left != NULL)
        stack.push(cur->left);
    }
  }
}

void Tree::levelOrderTree()
{
  queue<Node *> q;
  Node *p = root;
  if (root != NULL)
    q.push(root);

  while (!q.empty()) {
    p = q.front();
    q.pop();
    processData(p->data);
    if (p->left != NULL)
      q.push(p->left);
    if (p->right != NULL)
      q.push(p->right);
  }
}

int main()
{
  int num[] = {5, 3, 7, 2, 4, 6, 8, 1};
  Tree tree(num, 8);
  cout << "In order:  ";
  tree.inOrderTree();
  cout << "\nIn order1: ";
  tree.inOrderTree1();

  cout << "\nPre Order:   ";
  tree.preOrderTree();
  cout << "\nPre Order1:  ";
  tree.preOrderTree1();

  cout << "\nPost Order:   ";
  tree.postOrderTree();
  cout << "\nPost Order1:  ";
  tree.postOrderTree();

  cout << "\nLevel Order: ";
  tree.levelOrderTree();

  cout << endl;
  return 0;
}
