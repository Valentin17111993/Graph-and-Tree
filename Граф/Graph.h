#pragma once
#include <iostream>
using namespace std;

#define SIZE 10 
#define VERYBIGINT 1000000000 // очень большое число

class Graph
{
	public:
		Graph();
		void addVertex(int vnumber);
		void addEdge(int V1, int V2, int weight);
		void delVertex(int vnumber); // удаление вершины
		void delEdge(int v1, int v2); // удаление ребра
		void depth(int start); // обход в глубину
		void depthInner(int current, bool visited[]);
		void width(int start); // обход в ширину
		int findPathCount(int from, int to); // количество путей от одной вершины к другой
		void pathCountInner(int current, int to, bool visited[], int& count); // количество внутренних путей
		void findMinDistanceDecstr(int fromVert);// Алгоритм Дейкстры (поиск кратчайшего пути)
		void findMinDistancesFloyd(); // Алгоритм Флойда-Уоршера
		void inner(int current, int to, bool visited[], int& min, int currentDistance);
		int findMinWayDFS(int from, int to);
	private:
		bool edgeExists(int v1, int v2);// проверка существования ребра
		bool vertexExists(int v); // проверка существования вершины
		int matrix[SIZE][SIZE]; // матрица смежности
		int vertexes[SIZE]; // хранилище вершин
		int vertexCount; // количество добавленных вершин
};