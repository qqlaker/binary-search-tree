#include<iostream>
using namespace std;

class Tree
{
    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, int el) {
        if(t == NULL)
            return NULL;
        else if(el < t->data)
            return find(t->left, el);
        else if(el > t->data)
            return find(t->right, el);
        else
            return t;
    }

    void print_Tree(node* p, int level)
    {
        if(p)
        {
            print_Tree(p->right,level + 1);
            for(int i = 0;i< level;i++) cout<<"   ";
            cout << p->data << endl;
            print_Tree(p->left,level + 1);
        }
    }

    int height(node* r)
    {
        if (r == NULL) {
            return 0;
        }
        return 1 + max(height(r->left), height(r->right));
    }

public:
    Tree() {
        root = NULL;
    }

    ~Tree() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void print()
    {
        print_Tree(root, 0);
    }

    void print_min_leaf()
    {
        cout << findMin(root)->data << endl;
    }

    void print_max_leaf()
    {
        cout << findMax(root)->data << endl;
    }

    bool search(int el) {
        if (find(root, el) != NULL) return true;
        return false;
    }

    void print_height()
    {
        cout << height(root) << endl;
    }
};

int main() {
    Tree t;
    t.insert(20);
    t.insert(25);
    t.insert(24);
    t.insert(15);
    t.insert(10);
    t.insert(30);

    // Tree
    cout << "Whole Tree: " << endl;
    t.print();
    cout << "-------------------" << endl;
    
    // height
    cout << "Tree height is ";
    t.print_height();
    cout << "-------------------" << endl;

    // left leaf
    cout << "Min left leaf: ";
    t.print_min_leaf();
    cout << "-------------------" << endl;

    // remove element 15
    t.remove(15);
    t.print();
    cout << "-------------------" << endl;

    // search
    int for_find;
    cout << "input element: ";
    cin >> for_find;
    cout << "Element " << for_find;
    if (t.search(for_find)) cout << " found" << endl;
    else cout << " not found" << endl;
    cout << "-------------------" << endl;
    
    return 0; 
}