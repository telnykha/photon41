
#pragma once

template <class T> class AVL_Tree
{
    struct Node
    {
        T key;
        Node * left, * right;
        int bal;
    } * root;

    static const T & add ( const T & x, Node * & p, bool & h )
    {
        if ( ! p )
        {
            p = new Node;
            p->key = x;
            p->left = p->right = 0;
            p->bal = 0;
            h = true;
            return p->key;
        }
        if ( p->key > x )
        {
            const T & res = add ( x, p->left, h );
            if ( h )
            {
                switch ( p->bal )
                {
                case 0: p->bal = -1; break;
                case -1:
                    {
                        Node * p1 = p->left;
                        if ( p1->bal == -1 )
                        {
                            p->left = p1->right;
                            p1->right = p;
                            p->bal = 0;
                            p = p1;
                        }
                        else
                        {
                            Node * p2 = p1->right;
                            p1->right = p2->left;
                            p2->left = p1;
                            p->left = p2->right;
                            p2->right = p;
                            p ->bal = p2->bal == -1 ? 1 : 0;
                            p1->bal = p2->bal == 1 ? -1 : 0;
                            p = p2;
                        }
                    }
                case 1:
                    p->bal = 0;
                    h = false;
                }
            }
            return res;
        }
        if ( p->key < x )
        {
            const T & res = add ( x, p->right, h );
            if ( h )
            {
                switch ( p->bal )
                {
                case 0: p->bal = 1; break;
                case 1:
                    {
                        Node * p1 = p->right;
                        if ( p1->bal == 1 )
                        {
                            p->right = p1->left;
                            p1->left = p;
                            p->bal = 0;
                            p = p1;
                        }
                        else
                        {
                            Node * p2 = p1->left;
                            p1->left = p2->right;
                            p2->right = p1;
                            p->right = p2->left;
                            p2->left = p;
                            p ->bal = p2->bal == 1 ? -1 : 0;
                            p1->bal = p2->bal == -1 ? 1 : 0;
                            p = p2;
                        }
                    }
                case -1:
                    p->bal = 0;
                    h = false;
                }
            }
            return res;
        }
        h = false;
        return p->key;
    }

    static void delAll ( Node * p )
    {
        if ( ! p ) return;
        delAll ( p->left );
        delAll ( p->right );
        delete p;
    }
public:
    AVL_Tree () : root ( 0 ) {}

    ~AVL_Tree ()
    {
        delAll ( root );
    }

    const T & add ( const T & x )
    {
        bool h;
        return add ( x, root, h );
    }
};