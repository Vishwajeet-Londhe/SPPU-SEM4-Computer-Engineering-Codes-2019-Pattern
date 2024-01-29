#include <iostream>
using namespace std;

class bstnode
{
    int data;
    bstnode *right;
    bstnode *left;

public:
    bstnode *create(int data);
    bstnode *insert(bstnode *root, int data);
    bool search(bstnode *root, int data);
    void preorder(bstnode *root);
    void inorder(bstnode *root);
    void postorder(bstnode *root);
    int min(bstnode *root);
    int height(bstnode *root);
    void mirror(bstnode *root);
};

bstnode *bstnode::create(int data)
{
    bstnode *temp;
    temp = new bstnode();
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

bstnode *bstnode::insert(bstnode *root, int data)
{
    if (root == NULL)
    {
        root = create(data);
        cout << "\n"
             << root->data << "\n";
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
        cout << root->left->data << "->";
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
        cout << root->right->data << "->";
    }
    return root;
}

bool bstnode::search(bstnode *root, int data)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->data == data)
    {
        return true;
    }
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else if (data > root->data)
    {
        return search(root->right, data);
    }
}

void bstnode::preorder(bstnode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        cout << root->data << "->";
        preorder(root->left);
        preorder(root->right);
    }
}

void bstnode::inorder(bstnode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        inorder(root->left);
        cout << root->data << "->";
        inorder(root->right);
    }
}

void bstnode::postorder(bstnode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << "->";
    }
}

int bstnode::min(bstnode *root)
{
    if (root == NULL)
    {
        cout << "BST is empty";
        return -1;
    }
    else if (root->left == NULL)
    {
        cout << root->data;
        return root->data;
    }
    else
    {
        cout << root->data;
        return min(root->left);
    }
}

int bstnode::height(bstnode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int lheight = height(root->left);
        int rheight = height(root->right);
        if (lheight > rheight)
        {
            return (lheight + 1);
        }
        else
        {
            return (rheight + 1);
        }
    }
}

void bstnode::mirror(bstnode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        bstnode *temp;
        mirror(root->left);
        mirror(root->right);
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

int main()
{
    bstnode *root;
    root = NULL;
    bstnode b;
    char ans;
    do
    {
        cout << "\n1)Insert\n";
        cout << "2)Search\n";
        cout << "3)Preorder\n";
        cout << "4)Inorder\n";
        cout << "5)Postorder\n";
        cout << "6)Minimum in BST\n";
        cout << "7)Number of nodes in BST\n";
        cout << "8)Mirror of BST\n";
        cout << "9)End\n";
        cout << "\nEnter Choice:";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            int val;
            cout << "\nEnter value to be inserted:";
            cin >> val;
            root = b.insert(root, val);
            break;
        case 2:
            int num;
            cout << "\nEnter value to be searched:\n";
            cin >> num;
            if (b.search(root, num))
            {
                cout << "\nFound\n";
            }
            else
            {
                cout << "\nNot Found\n";
            }
            break;
        case 3:
            cout << "\nPreorder Traversal\n";
            b.preorder(root);
            break;
        case 4:
            cout << "\nInorder Traversal\n";
            b.inorder(root);
            break;
        case 5:
            cout << "\nPostorder Traversal\n";
            b.postorder(root);
            break;
        case 6:
            cout << "\nMinimum in BST\n";
            b.min(root);
            break;
        case 7:
            cout << "Number of nodes in BST:" << b.height(root);
            break;
        case 8:
            cout << "\nBefore Swapping\n";
            b.inorder(root);
            b.mirror(root);
            cout << "\nAfter Swapping\n";
            b.inorder(root);
            break;
        case 9:
            exit(0);
        }
    } while (true);
}
