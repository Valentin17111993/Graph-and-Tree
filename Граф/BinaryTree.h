#pragma once
#include <iostream>
using namespace std;

#define SIZE 10

class BinaryTree
{
	public:
	struct Node
	{
		Node(int d, Node* p = nullptr);
		~Node();

		Node* parent; // родительский узел
		Node* leftChild; // левый узел
		Node* rightChild; // правый узел
		int data; // данные - целое число
	};

	BinaryTree();
	~BinaryTree();
	void addInt(int newdata);
	bool isLeaf(Node* check); // проверка является ли узел листом 
	bool isRoot(Node* check); // проверка, являтся ли узел корневым
	Node* findNodeByData(int finddata);
	void delInt(int deldata);

	private:
		Node* root; // корневой узел
};