#include <iostream>
#include "Graph.h"
using namespace std;

Graph::Graph()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
	vertexCount = 0;
}

void Graph::addVertex(int vnumber)
{
	vertexes[vertexCount++] = vnumber;
}

void Graph::addEdge(int V1, int V2, int weight)
{
	matrix[V1][V2] = weight;
	matrix[V2][V1] = weight;
}


bool Graph::edgeExists(int v1, int v2)
{
	return matrix[v1][v2] > 0;
}

bool Graph::vertexExists(int v)
{
	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == v)
		{
			return true;
		}
	}
	return false;
}

void Graph::delVertex(int vnumber)
{
	// Ваш код должен быть здесь 
	for (int j = 0; j < SIZE; j++)
	{
		matrix[vnumber][j] = 0;
		matrix[j][vnumber] = 0;
	}

	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == vnumber)
		{
			vertexCount--;
			for (int j = i; j < vertexCount; j++)
			{
				vertexes[j] = vertexes[j + 1];
			}
		}
	}
}

void Graph::delEdge(int v1, int v2)
{
	// Ваш код должен быть здесь
	matrix[v1][v2] = 0;
	matrix[v2][v1] = 0;
}

void Graph::depth(int start)
{
	bool visited[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		visited[i] = false;
	}
	depthInner(start, visited);

	cout << endl;
}

void Graph::depthInner(int current, bool visited[])
{
	cout << "v" << current << " -> " << endl;
	visited[current] = true;
	for (int i = 0; i < SIZE; i++)
	{
		if (!visited[i] && edgeExists(current, i))
		{
			depthInner(i, visited);
		}
	}
}

void Graph::width(int start)
{
	// инициализация очереди и списка посещенных вершин
	int queue_to_visit[SIZE];
	int queueCount = 0;
	bool visited[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		visited[i] = false;
	}
	queue_to_visit[queueCount++] = start;

	// цикл по очепеди
	while (queueCount > 0)
	{
		// берем верхний элемент удаляем и выводим из очереди
		queueCount--;
		int current = queue_to_visit[0];
		for (int i = 0; i < queueCount; i++)
		{
			queue_to_visit[i] = queue_to_visit[i + 1];
		}
		visited[current] = true;
		cout << "v" << current << " -> ";

		// кладем в очередь все непосещенные смежные вершины
		for (int i = 0; i < vertexCount; i++)
		{
			int vnum = vertexes[i];
			int j = 0;
			for (; j < queueCount; j++)
			{
				if (queue_to_visit[j] == vnum)
				{
					break;
				}
			}

			if (j < queueCount)
			{
				continue;
			}

			if (!visited[vnum] && edgeExists(current, vnum))
			{
				queue_to_visit[queueCount++] = vnum;
			}
		}
	}

	cout << endl;
}

int Graph::findPathCount(int from, int to) // поиск количества всех возможных путей между двумя вершинами
{
	// Ваш код должен быть здесь
	bool visited[SIZE]; // массив пройденных вершин
	for (int i = 0; i < SIZE; i++)
	{
		visited[i] = false;
	}
	int count = 0;// результат
	pathCountInner(from, to, visited, count);
	return count;
}

void Graph::pathCountInner(int current, int to, bool visited[], int& count)
{
	if (current == to)
	{
		// если дошли до второй вершины, увеличиваем счётчик путей
	   // и выходим
		count++;
		return;
	}
	visited[current] = true; // отмечаем как посещенную
	for (int i = 0; i < SIZE; i++)
	{
		if (edgeExists(current, i) && !visited[i])
		{
			pathCountInner(i, to, visited, count);
		}
	}
	// отмечаем, что путь уже не содержит эту вершину
	visited[current] = false;
}

void Graph::findMinDistanceDecstr(int fromVert)
{
	int distances[SIZE]; // массив меток
	for (int i = 0; i < SIZE; i++)
	{
		distances[i] = VERYBIGINT; // инициализация меток
	}
	distances[fromVert] = 0;

	bool passed[SIZE]; // признак, что вершина окрашена
	for (int i = 0; i < SIZE; i++)
	{
		passed[i] = false; // все неокрашены изначально
	}

	int currentVertexNum = fromVert; // принимаем стартовую вершину за текущую
	int min_dist = 0;
	while (min_dist != VERYBIGINT)
	{
		passed[currentVertexNum] = true; // окрашиваем текущую
		for (int i = 0; i < SIZE; i++)
		{
			if (edgeExists(currentVertexNum, i) && distances[currentVertexNum] + matrix[currentVertexNum][i] < distances[i])
			{
				distances[i] = distances[currentVertexNum] + matrix[currentVertexNum][i]; // для смежных ребер пересчитываем метки
			}
		}

		min_dist = VERYBIGINT;
		for (int i = 0; i < SIZE; i++)
		{
			if (vertexExists(i) && !passed[i] && distances[i] < min_dist) // выбор новой вершины
			{
				min_dist = distances[i];
				currentVertexNum = i;
			}
		}
	}

	for (int i = 0; i < vertexCount; i++)
	{
		cout << "V" << i << ": " << distances[vertexes[i]] << " ";
	}
	cout << endl;
}

void Graph::findMinDistancesFloyd()
{
	int weights[SIZE][SIZE]; // матрица путей
	for (int i = 0; i < SIZE; i++)  // инициализация матрицы
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i == j)
			{
				weights[i][j] = 0; // путь до самой себя равен 0
			}
			else if (!edgeExists(i, j))
			{
				weights[i][j] = VERYBIGINT; // если ребра нет
			}
			else
			{
				weights[i][j] = matrix[i][j]; // если ребро есть
			}
		}
	}

	for (int k = 0; k < vertexCount; k++) 
	{
		int ck = vertexes[k]; // возьмем номер вершины
		for (int i = 0; i < vertexCount; i++)
		{
			if (i == k)
			{
				continue;
			}
			int ci = vertexes[i];
			for (int j = 0; j < SIZE; j++)
			{
				if (i == k)
				{
					continue;
				}
				int cj = vertexes[j];
				if (weights[ci][ck] + weights[ck][cj] < weights[i][j])
				{
					weights[i][j] = weights[ci][ck] + weights[ck][cj]; // пересчет матрицы путей
				}
			}
		}
	}

	for (int i = 0; i < vertexCount; i++)
	{
		cout << "V" << i << ": " << weights[0][vertexes[i]] << " "; // вывод всех минимальных путей от вершины '0'
	}
	cout << endl;
}

void Graph::inner(int current, int to, bool visited[], int& min, int currentDistance)
{
	if (current == to)
	{
		if (currentDistance < min) // если попали в целевую вершину, сравниваем текущий путь с минимальным
		{
			min = currentDistance; // если новое расстояние меньше, запоминаем
		}
		return;
	}
	visited[current] = true; // обозначем вершину посещенной
	for (int i = 0; i < SIZE; i++)
	{
		if (edgeExists(current, i) && !visited[i])
		{
			int newDis = currentDistance + matrix[current][i]; 
			inner(i, to, visited, min, newDis); // запускаем рекурсию для всех непосещенных смежных вершин
		}
	}

	cout << "Min Dist " << current << " and " << to << " : " << currentDistance << endl;
	visited[current] = false;
}

int Graph::findMinWayDFS(int from, int to)
{
	// Ваш код должен быть здесь 
	bool visited[SIZE]; // массив пройденных вершин
	for (int i = 0; i < SIZE; i++)
	{
		visited[SIZE] = false;
	}
	int currentDistance = 0;
	int min = VERYBIGINT; // начальное минимальное расстояние
	inner(from, to, visited, min, currentDistance);
	return min;
}