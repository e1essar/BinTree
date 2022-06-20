﻿#include <iostream>
#include <ctime>
using namespace std;



class Node {
    int key;
    Node* left, * right;
public:
    Node(int k = 0, Node* l = NULL, Node* r = NULL) {
        key = k;
        left = l;
        right = r;
    }
    friend class BinTree;
};

struct elem {
    Node* p;
    elem* next;
};

class BinTree {
    Node* root;
public:
    BinTree() { root = NULL; }
    BinTree(int);
    BinTree(int*, int);
    ~BinTree();

    BinTree(const BinTree&);
    Node* CopyTree(const Node* q);
    BinTree operator =(const BinTree&);  
    
    Node* GetRoot() { return root; }

    void DestroyTree(Node* root);
    void PrintTree(Node*, int);
   
    int min(Node* q);
    int max(Node* q);

    void Insert(int k);
    void Erase(int k);
    Node* Find(int k);

    void NLR(Node*);
    void LNR(Node*);
    void LRN(Node*);
    elem* BFS(Node*);

    /*
    void inarray(Node*, int*, int& k);
    void BinTree::inarray(Node* q, int* a, int& k) {
        if (q == NULL) return;
        inarray(q->left, a, k);
        a[k++] = q->key;
        inarray(q->right, a, k);
    }
    Node* InsertR(Node* node, int k);
    Node* BinTree::InsertR(Node* node, int k) {
    if (root == NULL) {
        Node* node = new Node(k);
        return node;
    }
    if (k < node->key) if(k < node->key) node->left = InsertR(node->left, k);
    else node->right = InsertR(node->right, k);
}
    */
};



BinTree::BinTree(int n) { // конструктор 2 (случайные ключи)
    srand(time(NULL));
    if (root == 0) root = NULL;
    for (int i = 0; i < n; i++) {
        int k = rand() % 100;
        Insert(k);
    }
}

BinTree::BinTree(int* a, int size) { // конструктор 3 (по массиву)
    if (root == 0) root = NULL;
    for (int i = 0; i < size; i++) {
        Insert(a[i]);
    }
}

BinTree::~BinTree() { // деструктор
    DestroyTree(root);
}

BinTree::BinTree(const BinTree& T) { // конструктор копирования
    if (T.root == NULL) root = NULL; 
    else {
        root = new Node(T.root->key);
        root->left = CopyTree(T.root->left);
        root->right = CopyTree(T.root->right);
    }
}

Node* BinTree::CopyTree(const Node* T) { // копирование узлов
    if (T == NULL) return NULL;
    Node* node = new Node(T->key);
    node->left = CopyTree(T->left);
    node->right = CopyTree(T->right);
    return node;
}

BinTree BinTree::operator=(const BinTree &T) { // оператор присваивания
    if (this == &T) return *this;
    this -> ~BinTree();
    if (T.root == NULL) root = NULL;
    else {
        root = new Node(T.root->key);
        root->left = CopyTree(T.root->left);
        root->right = CopyTree(T.root->right);
    }
    return *this;
}

void BinTree::DestroyTree(Node* T) { // удаление дерева
    if (T != NULL) {
        DestroyTree(T->left);
        DestroyTree(T->right);
        delete T;
    }
}

void BinTree::PrintTree(Node* T, int k) { // вывод дерева
    if (T == NULL) return;
    PrintTree(T->right, k + 5);
    for (int i = 0; i < k; i++) cout << " ";
    cout.width(2);
    cout << T->key << endl;
    PrintTree(T->left, k + 5);
}

int BinTree::min(Node* p) { // нахождение минимума
    if (root == NULL) { cout << "Empty"; return -1; }
    Node* node = root;
    while (node->left) node = node->left;
    if (node) return node->key;
    return -1;
}

int BinTree::max(Node* p) { // нахождение максимума
    if (root == NULL) { cout << "Empty"; return -1; }
    Node* node = root;
    while (node->right) node = node->right;
    if (node) return node->key;
    return -1;
}

void BinTree::Insert(int k) { // добавление узла
    if (root == NULL) {
        root = new Node(k);
        return;
    } 
    Node* node = root;
    while (node && node->key != k) {
        if (node->key > k && node->left == NULL) {
            node->left = new Node(k);
            return;
        }
        if (node->key < k && node->right == NULL) { // если ключи одинаковые?
            node->right = new Node(k);
            return;
        }
        if (node->key > k) node = node->left;
        else node = node->right;
    }
}

void BinTree::Erase(int k) { // удаление узла
    Node* node = root;
    Node* parent = NULL;
    while (node && node->key != k) {
        parent = node;
        if (node->key > k) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (!node) return;
    if (node->left == NULL) {
        if (parent && parent->left == node) parent->left = node->right;
        if (parent && parent->right == node) parent->right = node->right;
        delete node;
        return;
    }
    if (node->right == NULL) {
        if (parent && parent->left == node) parent->left = node->left;
        if (parent && parent->right == node) parent->right = node->left;
        delete node;
        return;
    }

    Node* tmp = node->left;
    parent = NULL;
    if (tmp->right == NULL) {
        node->key = tmp->key;
        node->left = tmp->left;
        delete tmp;
        return;
    }
    else {
        while (tmp->right != NULL) {
            parent = tmp;
            tmp = tmp->right;
        }
        node->key = tmp->key;
        parent->right = tmp->left;
        delete tmp;
        return;
    }
}

Node* BinTree::Find(int k) { // поиска узла по ключу
    if (root == NULL) return NULL;
    Node* node = root;
    while (node) {
        if (node->key == k) return node;
        //else if(node->key > k && node->left == NULL) return NULL;
            //else if (node->key < k && node->right == NULL) return NULL;
        if (node->key > k) node = node->left;
        else node = node->right;
    }
    return NULL;
}

void BinTree::NLR(Node* node) { // прямой обход
    if (node == NULL) node = root;
    cout << node->key << " ";
    if (node->left) NLR(node->left);
    if (node->right) NLR(node->right);
}

void BinTree::LNR(Node* node) { // централизованный обход
    if (node == NULL) node = root;
    if (node->left) LNR(node->left);
    cout << node->key << " ";
    if (node->right) LNR(node->right);
}

void BinTree::LRN(Node* node) { // обратный обход
    if (node == NULL) node = root;
    if (node->left) LRN(node->left);
    if (node->right) LRN(node->right);
    cout << node->key << " ";
}

elem* BinTree::BFS(Node* node) { // обход по уровням
    elem* current;
    elem* t;
    elem* h = new elem;
    h->p = root;
    h->next = NULL;
    t = h;
    current = h;
    while (h != NULL) {
        if (h->p->left != NULL) {
            elem* L = new elem;
            L->p = h->p->left;
            L->next = NULL;
            current->next = L;
            current = current->next;
        }
        if (h->p->right != NULL) {
            elem* R = new elem;
            R->p = h->p->right;
            R->next = NULL;
            current->next = R;
            current = current->next;
        }
        cout << h->p->key << " ";
        h = h->next;
    }
    return t;
}

int main() {
    srand(time(NULL));
    int n = 15;
    int a[] = { 54, 92, 23, 62, 89, 1, 73, 36, 8, 29, 99, 16, 45, 36, 0 };
    cout << endl << endl << endl;
    BinTree A(a,n);
    A.PrintTree(A.GetRoot(), 0);
    
    A.NLR(A.GetRoot());
    cout << endl;
    A.LNR(A.GetRoot());
    cout << endl;
    A.LRN(A.GetRoot());
    cout << endl;
    A.BFS(A.GetRoot());
    cout << endl;
   
    if (A.Find(5)) cout << "Found!" << endl;
    else cout << "Not found!" << endl;
    cout << "min:" << A.min(A.GetRoot()) << endl;
    cout << "max:" << A.max(A.GetRoot()) << endl;
    cout << endl << endl << endl;
    
    A.Erase(92);
    A.PrintTree(A.GetRoot(), n);
    A.Insert(39);
    cout << endl << endl << endl;
    A.PrintTree(A.GetRoot(), n);
}