#include "Tree.h"

Tree::Node :: Node(int _number, Node *_parent = nullptr) : number(_number), parent(_parent), childCount(0)
{
}

Tree::Node :: ~Node()
{
	for (int i = 0; i < childCount; i++)
	{
		delete children[i];
	}
}

Tree::Tree()
{
	root = nullptr;
}

Tree :: ~Tree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void Tree::Node::addChild(Node* newChild)
{
	children[childCount++] = newChild;
}

void Tree::setRoot(int number)
{
	if (root != nullptr) // удаляем корень, если он был
	{
		delete root;
		root = nullptr;
	}
	root = new Node(number); // устанавливаем новый корень
}

Tree::Node* Tree::getNodeByNumber(int number, Node* current)
{
	if (current->number == number)
	{
		return current;
	}
	for (int i = 0; i < current->childCount; i++)
	{
		// обходим в глубину, пока не найдем искомую
		Node* found = getNodeByNumber(number, current->children[i]);
		if (found)
		{
			return found;
		}
	}
	return nullptr;
}

void Tree::addNode(int parentNumber, int newNodeNumber)
{
	Node* parentNode = getNodeByNumber(parentNumber, root); // нашли родителя
	Node *newNode = getNodeByNumber(newNodeNumber, parentNode); // создали новую
	parentNode->addChild(newNode);// добавили к родителю
}

void Tree::delNodeMine(int number)
{
	// Ваш код должен быть здесь
	Node* found = getNodeByNumber(number, root);
	for (int i = 0; i < found->childCount; i++)
	{
		found->parent = found->children[i];
	}
	delete found;
}

void Tree::Node::delChild(Node* child) 
{
	int foundIndex = -1;
	for (int i = 0;i < childCount; i++)
		if (children[i] == child)
			foundIndex = i; // нашли индекс удаляемой вершины в массиве
	delete children[foundIndex]; // удалили вершину
	childCount--; // удалили ее из массива
	for (int i = foundIndex; i < childCount; i++)
		children[i] = children[i + 1];
}

void Tree::delNode(int number) 
{
	// Ваш код должен быть здесь
	Node* node = getNodeByNumber(number, root); // нашли вершину для удаления
	Node* parent = node->parent; // нашли ее родителя
	// перебросили всех детей удаляемой вершины её родителю
	for (int i = 0; i < node->childCount; i++)
	{
		parent->addChild(node->children[i]);
		node->children[i]->parent = node->parent;
	}
	// указали, что у  удаляемой вершины, больше нет детей
	node->childCount = 0;
	// удалили вершину
	parent->delChild(node);
}