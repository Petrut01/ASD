#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

struct Node
{
    int val,grad;
    Node *tata,*fiu,*frate;
};

Node *cap = NULL;
Node *cap1 = NULL;
Node *cap2 = NULL;
Node *cap3 = NULL;


void initializare(Node *temp,int x,int gr)
{
    temp->val = x;
    temp->grad = gr;
    temp->tata = temp->fiu = temp->frate = NULL;
}

void exempluHeapBinomial1()
{
    // B0
    Node *node1 = new Node;
    initializare(node1, 5, 0);
    cap = node1;

    // B2
    Node *node2 = new Node;
    initializare(node2, 6, 2);
    Node *node3 = new Node;
    initializare(node3, 12, 1);
    Node *node4 = new Node;
    initializare(node4, 34, 0);
    Node *node5 = new Node;
    initializare(node5, 33, 0);
    node2->fiu = node3;
    node3->tata = node2;
    node4->tata = node2;
    node3->fiu = node5;
    node3->frate = node4;
    node5->tata = node3;

    node1->frate = node2;

    // B3
    Node *node6 = new Node;
    initializare(node6, 1, 3);
    Node *node7 = new Node;
    initializare(node7, 2, 2);
    Node *node8 = new Node;
    initializare(node8, 12, 1);
    Node *node9 = new Node;
    initializare(node9, 6, 0);
    Node *node10 = new Node;
    initializare(node10, 4, 1);
    Node *node11 = new Node;
    initializare(node11, 13, 0);
    Node *node12 = new Node;
    initializare(node12, 18, 0);
    Node *node13 = new Node;
    initializare(node13, 7, 0);
    node6->fiu = node7;
    node7->tata = node6;
    node8->tata = node6;
    node7->tata = node6;
    node7->fiu = node10;
    node7->frate = node8;
    node8->fiu = node12;
    node8->frate = node9;
    node10->tata = node7;
    node11->tata = node7;
    node12->tata = node8;
    node10->fiu = node13;
    node10->frate = node11;
    node13->tata = node10;

    node2->frate = node6;
}

void exempluHeapBinomial2()
{
    // B1
    Node *node1 = new Node;
    initializare(node1, 29, 1);
    Node *node2 = new Node;
    initializare(node2, 33, 0);
    node1->fiu = node2;
    node2->tata = node1;
    cap1 = node1;

    // B2
    Node *node3 = new Node;
    initializare(node3, 21, 2);
    Node *node4 = new Node;
    initializare(node4, 23, 1);
    Node *node5 = new Node;
    initializare(node5, 78, 0);
    Node *node6 = new Node;
    initializare(node6, 50, 0);
    node3->fiu = node4;
    node4->tata = node3;
    node5->tata = node3;
    node4->fiu = node6;
    node4->frate = node5;
    node6->tata = node4;

    node1->frate = node3;

}

void reuniuneArbBinom(Node *t1,Node *t2)
{
    t2->tata = t1;
    t2->frate = t1->fiu;
    t1->fiu = t2;
    t1->grad++;
}

void reuniuneHeapBinomial(Node *&cap,Node*&cap2)
{
    if(cap==NULL)
    {
        cap = cap2;
    }
    else if(cap2==NULL)
    {
        cap2 = cap;
    }
    Node *i = cap;
    Node *j = cap2;
    Node *k = NULL;
    Node *temp = NULL;

    if(i->grad<=j->grad)
    {
        k = i;
        i = i->frate;
    }
    else
    {
        k = j;
        j = j->frate;
    }
    temp = k;
    while(i!=NULL && j!=NULL)
    {
        if(i->grad<j->grad)
        {
            k->frate = i;
            i= i->frate;
        }
        else
        {
            k->frate = j;
            j= j->frate;
        }
        k= k->frate;
    }
    if(i != NULL)
    {
        while(i!=NULL)
        {
            k->frate = i;
            i = i->frate;
            k = k->frate;
        }
    }
    if(j != NULL)
    {
        while(j!=NULL)
        {
            k->frate = j;
            j = j->frate;
            k = k->frate;
        }
    }
    k = temp;
    Node *pre = NULL;
    Node *next = k->frate;
    while(next!=NULL)
    {
        if((k->grad!=next->grad) || (next->frate!=NULL && k->grad==next->frate->grad))
        {
            pre = k;
            k = next;
        }
        else
        {
            if(k->val<=next->val)
            {
                k->frate = next->frate;
                reuniuneArbBinom(k,next);
            }
            else
            {
                if(pre==NULL)
                {
                    temp=next;
                }
                else
                {
                    pre->frate = next;
                }
                reuniuneArbBinom(next,k);
                k = next;
            }
        }
        next=k->frate;
    }
    cap = temp;
}

void Afisare(Node *cap)
{
    Node *i = cap;
    while(i)
    {
        cout<<"B"<<i->grad<<endl;
        vector<Node*> q;
        q.push_back(i);
        while(q.size())
        {
            Node *j = q.front();
            q.erase(q.begin());
            cout<<j->val<<" ";
            if(j->fiu)
            {
                Node *temp = j->fiu;
                while(temp)
                {
                    q.push_back(temp);
                    temp = temp->frate;
                }
            }
        }
        i = i->frate;
        cout<<endl;
    }
}

void inserareNod(Node *&cap,int x)
{
    Node *nod = new Node;
    initializare(nod,x,0);
    reuniuneHeapBinomial(cap,nod);
}

Node *gasireMinim(Node *cap)
{
    Node *p = cap,*pmin = NULL;
    int minim = INT_MAX;
    while(p!=NULL)
    {
        if(p->val < minim)
        {
            minim = p->val;
            pmin = p;
        }
        p = p->frate;
    }
    return pmin;
}

Node *findNode(Node *cap,int x)
{
    if(cap==NULL)
    {
        return NULL;
    }
    if(cap->val==x)
    {
        return cap;
    }
    Node *rez = findNode(cap->fiu,x);
    if(rez)
    {
        return rez;
    }
    return findNode(cap->frate,x);
}

void aparitii(Node *cap,int x,int &nr)
{
    while(cap)
    {
        if(cap->val==x)
        {
            nr++;
        }
        aparitii(cap->fiu,x,nr);
        cap = cap->frate;
    }
}

void decreaseKey(Node *&cap,int vechi,int nou)
{
    Node *nod = findNode(cap,vechi);
    if(nod==NULL)
    {
        return ;
    }
    nod->val = nou;
    Node *p = nod->tata;
    while(p && nod->val < p->val)
    {
        swap(nod->val,p->val);
        nod = p;
        p = p->tata;
    }
}

void deleteMin(Node *&cap)
{
    int k = 0;
    aparitii(cap,gasireMinim(cap)->val,k);
    while(k)
    {
        Node *min_prev = NULL;
        Node *min_node = cap;
        int val_m = min_node->val;
        Node *p = min_node;
        while(p->frate)
        {
            if((p->frate)->val < val_m)
            {
                val_m = (p->frate)->val;
                min_prev = p;
                min_node = p->frate;
            }
            p = p->frate;
        }
        if(min_prev==NULL && min_node->frate==NULL)
        {
            cap = NULL;
        }
        else if(min_prev==NULL)
        {
            cap = min_node->frate;
        }
        else
        {
            min_prev->frate = min_node->frate;
        }

        Node *fiu = min_node->fiu;
        while (fiu != NULL)
        {
            fiu->tata = NULL;
            fiu = fiu->frate;
        }

        stack<Node*> s;
        fiu = min_node->fiu;
        while (fiu != NULL)
        {
            s.push(fiu);
            fiu = fiu->frate;
        }

        Node *curent = s.top();
        Node *temp = curent;
        s.pop();

        while (!s.empty())
        {
            curent->frate = s.top();
            s.pop();
            curent = curent->frate;
        }

        curent->frate = NULL;
        cap3=temp;

        reuniuneHeapBinomial(cap,cap3);

        k--;
    }
}

void binomialNodDelete(Node *&cap,int x)
{
    if(cap==NULL)
    {
        return ;
    }
    int k = 0;
    aparitii(cap,x,k);
    while(k)
    {
        decreaseKey(cap,x,-1);
        deleteMin(cap);
        k--;
    }
}

int main()
{
    int k,x;
    exempluHeapBinomial1();// heap binomial folosit pentru teste
    exempluHeapBinomial2();
    cin>>k;
    while(k)
    {
        switch(k)
        {
        case 1:
        {
            cout<<"Afisarea heap-ului"<<endl;
            Afisare(cap);
            break;
        }
        case 2:
        {
            cout<<"Inserarea unui nod cu valoarea:\n";
            cin>>x;
            inserareNod(cap,x);
            Afisare(cap);
            break;
        }
        case 3:
        {
            cout<<"Stergerea unei valori din heap\n";
            cin>>x;
            binomialNodDelete(cap,x);
            Afisare(cap);
            break;
        }
        case 4:
        {
            cout<<"Stergerea din heap a minimului\n";
            deleteMin(cap);
            Afisare(cap);
            break;
        }
        case 5:
        {
            reuniuneHeapBinomial(cap,cap1);
            Afisare(cap);
            break;
        }
        default:
            cout<<"Operatie inexistenta";
        }
        cout<<endl;
        cin>>k;
    }
    return 0;
}
