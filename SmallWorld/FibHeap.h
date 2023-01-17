#pragma once

#include<float.h>

class node:public Node {
public:
    int degree;
    node* parent;
    node* child;
    node* left;
    node* right;
    char mark;
    char C;
};

// Implementing the Fibonacci heap
class FibonacciHeap:public Heap {
private:
    int nH;

    node* H;
    node* w;
    //Declaring all the functions that are later to be used as operations on the heap
public:
    node* InitializeHeap();
    void Fibonnaci_link(node*, node*, node*);
    node* Create_node(int);
    node* Insert(node*, node*);
    node* Union(node*, node*);
    node* Extract_Min(node*);
    void Consolidate(node*);
    void Display(node*);
    node* Find(node*, int);
    void Decrease_key(node*, double);
    void Cut(node*, node*, node*);
    void Cascase_cut(node*, node*);
    FibonacciHeap() { H = InitializeHeap(); }


    virtual Node* extractMin() {
        node* tmp = H;
        Extract_Min(H);
        return tmp;
    }
    virtual Node* insert(int vertex) {
        node* p = Create_node(DBL_MAX);
        p->vertex = vertex;
        w = Insert(w, p);
        return p;
    }
    virtual void decreaseKey(Node* n, int newParent, double dist) {
        n->parentVertex = newParent;
        n->dist = dist;
        Decrease_key(dynamic_cast<node*>(n), dist);
    }
    virtual bool isEmpty() {
        return H == nullptr;
    }
    virtual void print() {
        Display(w);
    }
};

// Initialize heap
node* FibonacciHeap::InitializeHeap() {
    node* np;
    np = NULL;
    return np;
}

// Creating node
node* FibonacciHeap::Create_node(int value) {
    node* x = new node;
    x->dist = value;
    return x;
}

// Inserting node
node* FibonacciHeap::Insert(node* H, node* x) {
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    x->mark = 'F';
    x->C = 'N';
    if (H != NULL) {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->dist < H->dist)
            H = x;
    }
    else {
        H = x;
    }
    nH = nH + 1;
    return H;
}

// Create linking
void FibonacciHeap::Fibonnaci_link(node* H1, node* y, node* z) {
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (z->right == z)
        H1 = z;
    y->left = y;
    y->right = y;
    y->parent = z;

    if (z->child == NULL)
        z->child = y;

    y->right = z->child;
    y->left = (z->child)->left;
    ((z->child)->left)->right = y;
    (z->child)->left = y;

    if (y->dist < (z->child)->dist)
        z->child = y;
    z->degree++;
}

// Union Operation
node* FibonacciHeap::Union(node* H1, node* H2) {
    node* np;
    node* H = InitializeHeap();
    H = H1;
    (H->left)->right = H2;
    (H2->left)->right = H;
    np = H->left;
    H->left = H2->left;
    H2->left = np;
    return H;
}

// Display the heap
void FibonacciHeap::Display(node* H) {
    node* p = H;
    if (p == NULL) {
        cout << "Empty Heap" << endl;
        return;
    }
    cout << "Root Nodes: " << endl;

    do {
        cout << p->dist;
        p = p->right;
        if (p != H) {
            cout << "-->";
        }
    } while (p != H && p->right != NULL);
    cout << endl;
}

// Extract min
node* FibonacciHeap::Extract_Min(node* H1) {
    node* p;
    node* ptr;
    node* z = H1;
    p = z;
    ptr = z;
    if (z == NULL)
        return z;

    node* x;
    node* np;

    x = NULL;

    if (z->child != NULL)
        x = z->child;

    if (x != NULL) {
        ptr = x;
        do {
            np = x->right;
            (H1->left)->right = x;
            x->right = H1;
            x->left = H1->left;
            H1->left = x;
            if (x->dist < H1->dist)
                H1 = x;

            x->parent = NULL;
            x = np;
        } while (np != ptr);
    }

    (z->left)->right = z->right;
    (z->right)->left = z->left;
    H1 = z->right;

    if (z == z->right && z->child == NULL)
        H = NULL;

    else {
        H1 = z->right;
        Consolidate(H1);
    }
    nH = nH - 1;
    return p;
}

// Consolidation Function
void FibonacciHeap::Consolidate(node* H1) {
    int d, i;
    float f = (log(nH)) / (log(2));
    int D = f;
    node** A = new node*[D];

    for (i = 0; i <= D; i++)
        A[i] = NULL;

    node* x = H1;
    node* y;
    node* np;
    node* pt = x;

    do {
        pt = pt->right;

        d = x->degree;

        while (A[d] != NULL)

        {
            y = A[d];

            if (x->dist > y->dist)

            {
                np = x;

                x = y;

                y = np;
            }

            if (y == H1)
                H1 = x;
            Fibonnaci_link(H1, y, x);
            if (x->right == x)
                H1 = x;
            A[d] = NULL;
            d = d + 1;
        }

        A[d] = x;
        x = x->right;

    }

    while (x != H1);
    H = NULL;
    for (int j = 0; j <= D; j++) {
        if (A[j] != NULL) {
            A[j]->left = A[j];
            A[j]->right = A[j];
            if (H != NULL) {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->dist < H->dist)
                    H = A[j];
            }
            else {
                H = A[j];
            }
            if (H == NULL)
                H = A[j];
            else if (A[j]->dist < H->dist)
                H = A[j];
        }
    }
}

// Decrease Key Operation
void FibonacciHeap::Decrease_key(node* ptr, double newDist) {
    node* y;
    if (ptr == NULL) {
        cout << "Node not found in the Heap" << endl;
        return;
    }

    if (ptr->dist < newDist) {
        cout << "Entered key greater than current key" << endl;
        return;
    }
    ptr->dist = newDist;
    y = ptr->parent;
    if (y != NULL && ptr->dist < y->dist) {
        Cut(ptr, ptr, y);
        Cascase_cut(ptr, y);
    }

    if (H != NULL && ptr->dist < H->dist)
        H = ptr;

    return;
}

// Cutting Function
void FibonacciHeap::Cut(node* H1, node* x, node* y)

{
    if (x == x->right)
        y->child = NULL;
    (x->left)->right = x->right;
    (x->right)->left = x->left;
    if (x == y->child)
        y->child = x->right;
    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;
    (H1->left)->right = x;
    x->right = H1;
    x->left = H1->left;
    H1->left = x;
    x->parent = NULL;
    x->mark = 'F';
}

// Cascade cut
void FibonacciHeap::Cascase_cut(node* H1, node* y) {
    node* z = y->parent;
    if (z != NULL) {
        if (y->mark == 'F') {
            y->mark = 'T';
        }
        else

        {
            Cut(H1, y, z);
            Cascase_cut(H1, z);
        }
    }
}

// Search function
node* FibonacciHeap::Find(node* H, int k) {
    node* x = H;
    x->C = 'Y';
    node* p = NULL;
    if (x->dist == k) {
        p = x;
        x->C = 'N';
        return p;
    }

    if (p == NULL) {
        if (x->child != NULL)
            p = Find(x->child, k);
        if ((x->right)->C != 'Y')
            p = Find(x->right, k);
    }

    x->C = 'N';
    return p;
}
