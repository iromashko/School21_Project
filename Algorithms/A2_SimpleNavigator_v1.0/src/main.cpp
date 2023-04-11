#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (arr[i]) {
      delete[] arr[i];
    }
  }
  if (arr) {
    delete[] arr;
  }
}

void printResult(int *testGraph, size_t count) {
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i];
    if (i < count - 1) {
      std::cout << "->";
    }
  }
  std::cout << std::endl;
}

void printResult2D(int **matrix, unsigned int count) {
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < count; j++) {
      std::cout << matrix[i][j] << " |";
    }
    std::cout << std::endl;
  }
}

void makeDepthFirstSearch(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int *testGraph;

  testGraph = GraphAlgorithms.depthFirstSearch(graph, 1);
  std::cout << "***********" << std::endl;
  std::cout << "обход в глубину: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete[] testGraph;
}

void makeBreadthFirstSearch(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int *testGraph;

  testGraph = GraphAlgorithms.breadthFirstSearch(graph, 1);
  std::cout << "***********" << std::endl;
  std::cout << "обход в ширину: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete[] testGraph;
}

void makeDeyxtraAlg(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int start = 1;
  int finish = 4;
  int minDex =
      GraphAlgorithms.getShortestPathBetweenVertices(graph, start, finish);

  std::cout << "***********" << std::endl;
  std::cout << "minDeyxtra from " << start << " to " << finish;
  std::cout << ": " << minDex << std::endl;
}

void makeFloydWorshelAlg(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getShortestPathsBetweenAllVertices(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Floyd-Worshel: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeAlgOfPrim(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getLeastSpanningTree(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Prim's algorithm: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeVoyage(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  TsmResult rez;

  rez = GraphAlgorithms.solveTravelingSalesmanProblem(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Voyage:" << std::endl;
  std::vector<int>::iterator it = rez.vertices.begin();
  for (; it != rez.vertices.end(); it++) {
    std::cout << *it;
    if (it != rez.vertices.end() - 1) {
      std::cout << "->";
    }
  }
  std::cout << std::endl;
  std::cout << "Voyage distance: " << rez.distance << std::endl;
}

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    GraphAlgorithms GraphAlgorithms;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
    if (graph.exportGraphToDot("exportFile.dot") != 0) {
      s21::exitError("Error: cannot write graph to file");
    }
    // makeDepthFirstSearch(graph, GraphAlgorithms);
    // makeBreadthFirstSearch(graph, GraphAlgorithms);
    // makeDeyxtraAlg(graph, GraphAlgorithms);
    // makeFloydWorshelAlg(graph, GraphAlgorithms);
    // makeAlgOfPrim(graph, GraphAlgorithms);
    makeVoyage(graph, GraphAlgorithms);
  } else {
    s21::exitError("Error: invalid count of arguments");
  }
  // while (1) {};
  return (0);
}
