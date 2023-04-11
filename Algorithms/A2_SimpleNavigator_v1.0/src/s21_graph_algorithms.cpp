#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  (void)rhs;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src)
    : GraphAlgorithms() {
  *this = src;
}

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  (void)gg;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) : GraphAlgorithms() {
  *this = gg;
}

GraphAlgorithms::~GraphAlgorithms() {}

void GraphAlgorithms::convertToArr(int *rez, std::vector<int> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    rez[i] = vec[i] + 1;
  }
}

int *GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  int index = startVertex - 1;
  s21::Stack<int> s;
  std::vector<int> vizit;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int *arr = new int[graph.getSizeGraph()];

  vizit.push_back(index);
  fillStack(s, graphVector[index], vizit);
  while (s.getSize() > 0) {
    // 0 - непосещенная вершина, 1 - посещенная
    if (checkElem(s.peek(), vizit) == 0) {
      vizit.push_back(s.peek());
      fillStack(s, graphVector[s.peek()], vizit);
    } else {
      s.pop();
    }
  }
  convertToArr(arr, vizit);
  return (arr);
}

int *GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
  s21::Queue<int> queue;
  int index = startVertex - 1;
  std::vector<int> visited;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int *arr = new int[graph.getSizeGraph()];

  visited.push_back(index);
  fillQueue(queue, graphVector[index], visited);
  while (queue.getSize() > 0) {
    if (checkElem(queue.peek(), visited) == 0) {
      visited.push_back(queue.peek());
      fillQueue(queue, graphVector[queue.peek()], visited);
    } else {
      queue.pop();
    }
  }
  convertToArr(arr, visited);
  return (arr);
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int v1,
                                                    int v2) {
  std::vector<int> distance;
  std::vector<int> vizit;
  int index = v1 - 1;
  int minindex;
  int min;
  int ret = 1;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int tmp;

  // init distance
  for (size_t i = 0; i < graphVector.size(); i++) {
    distance.push_back(10000);
    vizit.push_back(1);
  }
  distance[index] = 0;
  while (ret || minindex < 10000) {
    minindex = 10000;
    min = 10000;
    for (size_t i = 0; i < graphVector.size(); i++) {
      if (vizit[i] == 1 && distance[i] < min) {
        min = distance[i];
        minindex = i;
      }
    }
    if (minindex != 10000) {
      for (size_t i = 0; i < graphVector.size(); i++) {
        if (graphVector[minindex][i] > 0) {
          tmp = min + graphVector[minindex][i];
          if (tmp < distance[i]) {
            distance[i] = tmp;
          }
        }
      }
      vizit[minindex] = 0;
    }
    ret = 0;
  }
  return (distance[v2 - 1]);
}

int **GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  int **rez = new int *[graph.getSizeGraph()];
  for (size_t m = 0; m < graph.getSizeGraph(); m++) {
    rez[m] = new int[graph.getSizeGraph()];
  }
  firstFillArray(rez, graph);
  for (size_t k = 0; k < graph.getSizeGraph(); k++) {
    for (size_t i = 0; i < graph.getSizeGraph(); i++) {
      for (size_t j = 0; j < graph.getSizeGraph(); j++) {
        rez[i][j] = minElem(rez[i][j], rez[i][k] + rez[k][j]);
      }
    }
  }
  return (rez);
}

int **GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int x;
  int y;
  size_t edgeNum;
  std::vector<std::vector<int> > graph_arr = graph.getGraph();
  size_t graph_size = graph.getSizeGraph();
  int *vizit = new int[graph_size];
  int **res = new int *[graph_size];

  for (size_t i = 0; i < graph_size; i++) {
    res[i] = new int[graph_size];
    memset(res[i], 0, sizeof(int) * graph_size);
  }
  memset(vizit, 0, sizeof(int) * graph_size);
  edgeNum = 0;
  vizit[0] = 1;
  while (edgeNum < graph_size - 1) {
    int min = 10000;
    x = 0;
    y = 0;
    for (size_t i = 0; i < graph_size; i++) {
      if (vizit[i] == 1) {
        for (size_t j = 0; j < graph_size; j++) {
          if (vizit[j] == 0 && graph_arr[i][j]) {
            if (min > graph_arr[i][j]) {
              min = graph_arr[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }

    res[x][y] = res[y][x] = min;
    vizit[y] = 1;
    edgeNum++;
  }
  delete[] vizit;
  return (res);
}

double GraphAlgorithms::probability(size_t to, TsmResult &ant,
                                    double **distance, double **pheromone,
                                    size_t vertex) {
  for (size_t i = 0; i < ant.vertices.size(); i++) {
    if ((int)to == ant.vertices[i]) {
      return (0);
    }
  }
  double sum = 0.0;
  double ret;
  size_t from = ant.vertices[ant.vertices.size() - 1];

  for (size_t j = 0; j < vertex; j++) {
    int flag = 1;
    for (size_t i = 0; i < ant.vertices.size(); i++) {
      if ((int)j == ant.vertices[i]) {
        flag = 0;
      }
      if (flag == 1) {
        sum += pow(pheromone[from][j], ALPHA) * pow(distance[from][j], BETA);
      }
    }
  }
  ret = (pow(pheromone[from][to], ALPHA) * pow(distance[from][to], BETA)) / sum;
  return (ret);
}

void GraphAlgorithms::freeArr(double **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (arr[i]) {
      delete[] arr[i];
    }
  }
  if (arr) {
    delete[] arr;
  }
}

void GraphAlgorithms::initAnts(TsmResult *ants, size_t graphSize) {
  size_t start = 0;
  for (int i = 0; i < M; i++) {
    start += 1;
    ants[i].distance = 0.0;
    ants[i].vertices.push_back(start);
    if (start == graphSize - 1) {
      start = 0;
    }
  }
}

void GraphAlgorithms::initData(double **dist, double **pheromone,
                               size_t graphSize, Graph &graph) {
  for (size_t i = 0; i < graphSize; i++) {
    dist[i] = new double[graphSize];
    pheromone[i] = new double[graphSize];
    for (size_t j = 0; j < graphSize; j++) {
      pheromone[i][j] = 1.0 / graphSize;
      if (graph.getGraph()[i][j] != 0) {
        dist[i][j] = 1.0 / graph.getGraph()[i][j];
      }
    }
  }
}

void GraphAlgorithms::rangePheromone(TsmResult &ant, double **pheromone) {
  for (size_t m = 0; m < ant.vertices.size() - 1; m++) {
    size_t from = ant.vertices[m % ant.vertices.size()];
    size_t to = ant.vertices[(m + 1) % ant.vertices.size()];

    pheromone[from][to] += Q / ant.distance;
    pheromone[to][from] = pheromone[from][to];
  }
}

void GraphAlgorithms::checkBestWay(TsmResult &ant, TsmResult &way) {
  if (ant.distance < way.distance || way.distance < 0) {
    way.distance = ant.distance;
    way.vertices.clear();
    for (size_t x = 0; x < ant.vertices.size(); x++) {
      way.vertices.push_back(ant.vertices[x] + 1);
    }
  }
}

void GraphAlgorithms::updateAnt(TsmResult &ant) {
  ant.distance = 0.0;
  ant.vertices.clear();
  ant.vertices.push_back(0);
}

void GraphAlgorithms::updatePheromone(double **pheromone, size_t graphSize) {
  for (size_t i = 0; i < graphSize; i++) {
    for (size_t j = 0; j < graphSize; j++) {
      if (i != j) {
        pheromone[i][j] *= (1 - RHO);
      }
    }
  }
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TsmResult way;
  way.distance = -1;
  way.vertices.clear();
  size_t graphSize = graph.getSizeGraph();
  double **distance = new double *[graphSize];
  double **pheromone = new double *[graphSize];
  TsmResult ants[M];

  initData(distance, pheromone, graphSize, graph);
  initAnts(ants, graphSize);
  for (int i = 0; i < T_MAX; i++) {  // основной цикл
    // цикл по муравьям
    for (int k = 0; k < M; k++) {
      // поиск маршрута для текущего муравья
      while (ants[k].vertices.size() <= graphSize) {
        int jMax = -1;
        double pMax = 0.0;
        for (size_t j = 0; j < graphSize; j++) {
          double p = probability(j, ants[k], distance, pheromone, graphSize);
          if (p && p > pMax) {
            pMax = p;
            jMax = j;
          }
        }
        if (jMax == -1) {
          int first = ants[k].vertices.back();
          int second = ants[k].vertices.front();
          if (graph.getGraph()[first][second] > 0) {
            ants[k].distance += graph.getGraph()[first][second];
            ants[k].vertices.push_back(ants[k].vertices.front());
          } else {
            s21::exitError(
                "Error: impossible to solve the salesman's problem with a "
                "giving graph");
          }
        } else {
          ants[k].distance += graph.getGraph()[ants[k].vertices.back()][jMax];
          ants[k].vertices.push_back(jMax);
        }
      }
      rangePheromone(ants[k], pheromone);
      checkBestWay(ants[k], way);
      updateAnt(ants[k]);
    }
    updatePheromone(pheromone, graphSize);
  }
  freeArr(distance, graphSize);
  freeArr(pheromone, graphSize);
  return (way);
}

int GraphAlgorithms::fillStack(s21::Stack<int> &r, std::vector<int> v,
                               std::vector<int> viz) {
  size_t i = v.size() - 1;

  while (i > 0) {
    if (v[i] != 0 && checkElem(i, viz) == 0) {
      r.push(i);
    }
    i--;
  }
  return (0);
}

int GraphAlgorithms::fillQueue(s21::Queue<int> &r, std::vector<int> v,
                               std::vector<int> viz) {
  size_t i = 0;
  while (i < v.size()) {
    if (v[i] != 0 && checkElem(i, viz) == 0) {
      r.push(i);
    }
    i++;
  }
  return (0);
}

int GraphAlgorithms::checkElem(int num, std::vector<int> &viz) {
  for (std::vector<int>::iterator it = viz.begin(); it != viz.end(); it++) {
    if (num == *it) {
      return (1);
    }
  }
  return (0);
}

void GraphAlgorithms::firstFillArray(int **arr, Graph &graph) {
  std::vector<std::vector<int> > matrixGraph = graph.getGraph();

  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    for (size_t j = 0; j < graph.getSizeGraph(); j++) {
      if (i == j) {
        arr[i][j] = 0;
      } else {
        if (matrixGraph[i][j] == 0) {
          arr[i][j] = 10000;
        } else {
          arr[i][j] = matrixGraph[i][j];
        }
      }
    }
  }
}

int GraphAlgorithms::minElem(int elem1, int elem2) {
  if (elem1 < elem2) {
    return (elem1);
  } else {
    return (elem2);
  }
}
