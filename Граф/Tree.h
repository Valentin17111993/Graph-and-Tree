#pragma once
#include <iostream>
using namespace std;

#define SIZE 10

class Tree
{
	struct Node // структура узла
	{
		Node(int _number, Node *_parent = nullptr);
		~Node();
		void addChild(Node* newChild); // вставка дочерней вершины
		void delChild(Node* child);

		int number; // номер вершины
		Node* parent; // родительская вершина
		Node* children[SIZE]; // список дочерних вершин
		int childCount; // количество детей  
	};

	public:
		Tree();
		~Tree();
		void setRoot(int number); // вставка корневой вершины
		void addNode(int parentNumber, int newNodeNumber); // вставка узла
		Node* getNodeByNumber(int number, Node* current); // получить вершину по номеру
		void delNodeMine(int number); // удаление узла (мой)
		void delNode(int number); // удаление узла
	private:
		Node* root;
};