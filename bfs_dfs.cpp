#include <iostream>
#include <omp.h>
#include <stack>
#include <queue>

using namespace std;

class Node
{
public:
    int data;
    Node *leftChild;
    Node *rightChild;

    Node()
    {
        data = 0;
        leftChild = NULL;
        rightChild = NULL;
    }

    Node(int data)
    {
        this->data = data;
        leftChild = NULL;
        rightChild = NULL;
    }

    void setData(int data)
    {
        this->data = data;
    }

    void insertChildren()
    {
        int numChild = 0;
        cout << "\nHow many children for node with value " << this->data << "? (0, 1, or 2) : ";
        cin >> numChild;

        if (numChild == 2)
        {
            int leftData = 0, rightData = 0;

            cout << "\nEnter the value for left child for node with value " << this->data << ": ";
            cin >> leftData;

            this->leftChild = new Node(leftData);
            this->leftChild->insertChildren();

            cout << "\nEnter the value for right child for node with value " << this->data << ": ";
            cin >> rightData;

            this->rightChild = new Node(rightData);
            this->rightChild->insertChildren();
        }
        else if (numChild == 1)
        {
            char choice = 'x';

            while (choice != 'l' && choice != 'r')
            {
                cout << "\nLeft child or Right child? (l or r) : ";
                cin >> choice;
            }

            if (choice == 'l')
            {
                int leftData = 0;

                cout << "\nEnter the value for left child for node with value " << this->data << ": ";
                cin >> leftData;

                this->leftChild = new Node(leftData);
                this->leftChild->insertChildren();
            }
            if (choice == 'r')
            {
                int rightData = 0;

                cout << "\nEnter the value for right child for node with value " << this->data << ": ";
                cin >> rightData;

                this->rightChild = new Node(rightData);
                this->rightChild->insertChildren();
            }
        }
        else
            return;
    }
};

void parallelBFS(Node *root)
{

    queue<Node *> q;

    q.push(root);

    while (!q.empty())
    {

#pragma omp parallel for
        for (int i = 0; i < q.size(); i++)
        {
#pragma omp critical
            {
                Node *currentNode = q.front();
                q.pop();
                cout << currentNode->data << " ";
    
                if (currentNode->leftChild)
                    q.push(currentNode->leftChild);
                if (currentNode->rightChild)
                    q.push(currentNode->rightChild);
            }
        }
    }
}

void DFS(Node *root, bool *visited)
{

    visited[root->data] = true;
    cout << root->data << " ";

#pragma omp task
    if (root->leftChild && !visited[root->leftChild->data])
    {
        DFS(root->leftChild, visited);
    }

#pragma omp task
    if (root->rightChild && !visited[root->rightChild->data])
    {
        DFS(root->rightChild, visited);
    }
}

void parallelDFS(Node *root)
{

    bool *visited = new bool[100];

#pragma omp parallel for
    for (int i = 0; i < 100; i++)
    {
        visited[i] = false;
    }

#pragma omp parallel
    {
#pragma omp single
        DFS(root, visited);
    }

    delete[] visited;
}

int main()
{

    int val;

    Node *root = new Node();

    cout << "Enter the value for root node: ";
    cin >> val;

    root->setData(val);

    root->insertChildren();

    cout << "\nBFS: ";
    parallelBFS(root);

    cout << "\nDFS: ";
    parallelDFS(root);

    return 0;
}

// Sample input eiu: 5 2 3 2 1 0 4 0 8 2 6 1 r 7 0 9 0
// Tree:
//          5
//        /  \
//      3     8
//     / \   / \
//    1  4  6  9
//           \
//            7
