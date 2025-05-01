#include "BinaryTree.h"

BinaryTree::Node::Node(int d, Node* p = nullptr) : data(d), parent(p)
{
	leftChild = nullptr;
	rightChild = nullptr;
}

BinaryTree::Node::~Node()
{
	// чистим за собой память
	if (rightChild != nullptr)
	{
		delete rightChild;
	}

	if (leftChild != nullptr)
	{
		delete leftChild;
	}
}

BinaryTree::BinaryTree()
{
	root = nullptr;
}

BinaryTree::~BinaryTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void BinaryTree::addInt(int newdata)
{
	if (root == nullptr)
	{
		root = new Node(newdata); // если дерево пустое, то новый элемент станет корнем
	}
	else
	{
		Node* current = root; // начинаем с корня
		Node* newNode = nullptr;
		while (newNode == nullptr)
		{
			if (current->data >= newdata)
			{
				if (current->leftChild != nullptr) // если элемент меньше текущего, идем влево
				{
					current = current->leftChild;
					continue;
				}
				else
				{
					newNode = new Node(newdata, current); // если левого узла нет, то нашли место для нового элемента
					current->leftChild = newNode;
				}
			}
			else
			{
				if (current->rightChild != nullptr)
				{
					current = current->rightChild;
					continue;
				}
				else
				{
					newNode = new Node(newdata, current); // если правого узла нет, то нашли место для нового элемента
					current->rightChild = newNode;
				}
			}
		}
	}
}

bool BinaryTree::isLeaf(Node* check)
{
	return check->leftChild == nullptr && check->rightChild == nullptr;
}

bool BinaryTree::isRoot(Node* check)
{
	return check == root;
}

// поиск, возвращает указатель на найденный элемент

BinaryTree::Node* BinaryTree::findNodeByData(int finddata)
{
    // Ваш код
    if (root->data == finddata)
    {
        return root;
    }
    else
    {
        Node* current = root;
        Node* found = nullptr;
        while (found == nullptr)
        {
            if (current->data > finddata)
            {
                current = current->leftChild;
                continue;
            }
            if (current->data < finddata)
            {
                current = current->rightChild;
                continue;
            }
            if (current->data == finddata)
            {
                found = current;
            }
        }
        return found;
    }
    return nullptr;
}
// удаление элемента
void BinaryTree::delInt(int deldata)
{
    // Ваш код
    Node* current = findNodeByData(deldata);
    if (current == nullptr)
    {
        return;
    }

    Node* parent = current->parent;

    if (current->leftChild == nullptr && current->rightChild == nullptr)
    {
        if (parent->rightChild == current)
            parent->rightChild = nullptr;

        if (parent->leftChild == current)
            parent->leftChild = nullptr;
        delete current;
        return;
    }
    if (current->leftChild != nullptr && current->rightChild == nullptr)
    {
        if (parent->rightChild == current)
            parent->rightChild = current->leftChild;

        if (parent->leftChild == current)
            parent->leftChild = current->leftChild;

        current->leftChild->parent = parent;
        current->leftChild = nullptr;
        delete current;
        return;
    }
    if (current->leftChild == nullptr && current->rightChild != nullptr)
    {
        if (parent->rightChild == current)
            parent->rightChild = current->rightChild;

        if (parent->leftChild == current)
            parent->leftChild = current->rightChild;

        current->rightChild->parent = current->parent;
        current->rightChild = nullptr;
        delete current;
        return;
    }
    if (current->leftChild != nullptr && current->rightChild != nullptr)
    {
        Node* mostLeftChild = current->leftChild;
        Node* mostLeftParent = current;

        while (mostLeftChild->rightChild != nullptr)
        {
            mostLeftParent = mostLeftChild;
            mostLeftChild = mostLeftChild->rightChild;
        }

        current->data = mostLeftChild->data;
        current = mostLeftChild;

        if (mostLeftParent->leftChild == mostLeftChild)
            mostLeftParent->leftChild = nullptr;
        else
            mostLeftParent->rightChild = mostLeftChild->rightChild;
        return;
    }
}