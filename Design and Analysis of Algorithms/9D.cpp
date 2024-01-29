#include <iostream>
#include <string>

using namespace std;

class dictionary;

class avlnode
{
    string keyword;
    string meaning;
    avlnode *left, *right;
    int bf;

public:
    avlnode()
    {
        keyword = '\0';
        meaning = '\0';
        left = right = NULL;
        bf = 0;
    }

    avlnode(string k, string m)
    {
        keyword = k;
        meaning = m;
        left = right = NULL;
        bf = 0;
    }

    friend class dictionary;
};

class dictionary
{
    avlnode *par, *loc;

public:
    avlnode *root;

    dictionary()
    {
        root = NULL;
        par = loc = NULL;
    }

    void accept();
    void insert(string key, string mean);
    void LLrotation(avlnode *, avlnode *);
    void RRrotation(avlnode *, avlnode *);
    void inorder(avlnode *root);
    void deletekey(string key);
    void descending(avlnode *);
    void search(string);
    void update(string, string);
};

void dictionary::descending(avlnode *root)
{
    if (root)
    {
        descending(root->right);
        cout << root->keyword << " " << root->meaning << endl;
        descending(root->left);
    }
}

void dictionary::accept()
{
    string key, mean;
    cout << "Enter keyword: " << endl;
    cin >> key;
    cout << "Enter meaning: " << endl;
    cin >> mean;
    insert(key, mean);
}

void dictionary::LLrotation(avlnode *a, avlnode *b)
{
    cout << "LL rotation" << endl;
    a->left = b->right;
    b->right = a;
    a->bf = b->bf = 0;
}

void dictionary::RRrotation(avlnode *a, avlnode *b)
{
    cout << "RR rotation" << endl;
    a->right = b->left;
    b->left = a;
    a->bf = b->bf = 0;
}

void dictionary::insert(string key, string mean)
{
    if (!root)
    {
        root = new avlnode(key, mean);
        cout << "ROOT CREATED" << endl;
        return;
    }

    avlnode *a, *pa, *p, *pp;
    p = a = root;
    pp = NULL;

    while (p)
    {
        if (p->bf)
        {
            a = p;
            pa = pp;
        }
        if (key < p->keyword)
        {
            pp = p;
            p = p->left;
        }
        else if (key > p->keyword)
        {
            pp = p;
            p = p->right;
        }
        else
        {
            cout << "Already exist" << endl;
            return;
        }
    }

    avlnode *y = new avlnode(key, mean);

    if (key < pp->keyword)
    {
        pp->left = y;
    }
    else
    {
        pp->right = y;
    }

    int d;
    avlnode *b, *c;
    a = pa = NULL;
    p = a = root;
    pp = NULL;

    while (p != y)
    {
        if (key > p->keyword)
        {
            pp = p;
            p = p->right;
        }
        else
        {
            pp = p;
            p = p->left;
        }
    }

    if (!(a->bf) || !(a->bf + d))
    {
        a->bf += d;
        return;
    }

    if (d == 1)
    {
        b = p = a->right;
        d = -1;

        if (key > a->keyword)
        {
            LLrotation(a, b);
        }
        else
        {
            cout << "LR rotation" << endl;
            c = b->right;
            b->right = c->left;
            a->left = c->right;
            c->left = b;
            c->right = a;

            switch (c->bf)
            {
            case 1:
                a->bf = 0;
                b->bf = -1;
                break;
            case -1:
                a->bf = 1;
                b->bf = 0;
                break;
            case 0:
                a->bf = 0;
                b->bf = 0;
                break;
            }

            c->bf = 0;
            b = c;
        }
    }
    else if (d == -1)
    {
        b = p = a->left;
        d = 1;

        if (key < a->keyword)
        {
            RRrotation(a, b);
        }
        else
        {
            cout << "RL rotation" << endl;
            c = b->left;
            a->right = c->left;
            b->left = c->right;
            c->left = a;
            c->right = b;

            switch (c->bf)
            {
            case 1:
                a->bf = 0;
                b->bf = -1;
                break;
            case -1:
                a->bf = 1;
                b->bf = 0;
                break;
            case 0:
                a->bf = 0;
                b->bf = 0;
                break;
            }

            c->bf = 0;
            b = c;
        }
    }

    if (!pa)
    {
        root = b;
    }
    else if (a == pa->left)
    {
        pa->left = b;
    }
    else
    {
        pa->right = b;
    }

    cout << "AVL tree created!!" << endl;
}

void dictionary::search(string key)
{
    loc = NULL;
    par = NULL;

    if (root == NULL)
    {
        cout << "Tree not created" << endl;
        return;
    }

    avlnode *ptr = root;

    while (ptr != NULL)
    {
        if (ptr->keyword == key)
        {
            break;
        }
        else if (key < ptr->keyword)
        {
            par = ptr;
            ptr = ptr->left;
        }
        else
        {
            par = ptr;
            ptr = ptr->right;
        }
    }

    if (loc == NULL)
    {
        cout << "Not found" << endl;
    }
}

void dictionary::update(string oldkey, string newmean)
{
    search(oldkey);
    loc->meaning = newmean;
    cout << "UPDATE SUCCESSFUL" << endl;
}

void dictionary::deletekey(string key)
{
    // Not implemented
}

void dictionary::inorder(avlnode *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->keyword << " " << root->meaning << endl;
        inorder(root->right);
    }
}

int main()
{
    string k, m;
    dictionary d;
    int ch;
    string key, mean;

    do
    {
        cout << "1. Insert" << endl;
        cout << "2. Update" << endl;
        cout << "3. Ascending" << endl;
        cout << "4. Descending" << endl;
        cout << "5. Display" << endl;
        cout << "6. Quit" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter word and its meaning" << endl;
            cin >> k >> m;
            d.insert(k, m);
            break;

        case 2:
            cout << "Enter key whose meaning to update" << endl;
            cin >> key;
            cout << "Enter new meaning" << endl;
            cin >> mean;
            d.update(key, mean);
            break;

        case 3:
            d.inorder(d.root);
            break;

        case 4:
            cout << "Descending" << endl;
            d.descending(d.root);
            break;

        case 5:
            d.inorder(d.root);
            break;

        default:
            break;
        }
    } while (ch != 6);

    return 0;
}
