#include <iostream>
#include <cstring>
#pragma warning (disable : 4996)

const size_t MAX_NODE_LENGTH = 10;

struct Edge
{
    char from[MAX_NODE_LENGTH + 1]{};
    char to[MAX_NODE_LENGTH + 1]{};
};

struct Graph
{
    Edge* edges = nullptr;
    size_t edgesCount = 0;
    size_t nodesCount = 0;
};

void freeGraph(Graph& graph)
{
    delete[] graph.edges;
    graph.edges = nullptr;
    graph.edgesCount = graph.nodesCount = 0;
}

Edge initEdge(const char* from, const char* to)
{
    if (!from || !to)
    {
        return {};
    }

    Edge edge;
    strcpy(edge.from, from);
    strcpy(edge.to, to);

    return edge;
}

bool equalEdges(const Edge& lhs, const Edge& rhs)
{
    return !strcmp(lhs.from, rhs.from) && !strcmp(lhs.to, rhs.to);
}

bool hasLoop(const Edge& edge)
{
    return !strcmp(edge.from, edge.to);
}

bool containsNode(const char* node, const Graph& graph)
{
    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        if (!strcmp(node, graph.edges[i].from) && !strcmp(node, graph.edges[i].to))
        {
            return true;
        }
    }
    return false;
}

bool containsEdge(const Graph& graph, const Edge& edge)
{
    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        if (equalEdges(edge, graph.edges[i]))
        {
            return true;
        }
    }
    return false;
}

bool validateEdge(const Graph& graph, const Edge& edge)
{
    // a valid edge has no loop and isn't in the graph
    return !hasLoop(edge) && !containsEdge(graph, edge);
}

void readEdge(Edge& edge, const Graph& graph)
{

    do
    {
        std::cin.getline(edge.from, MAX_NODE_LENGTH);
        std::cin.getline(edge.to, MAX_NODE_LENGTH);
    } while (!validateEdge(graph, edge)); // we stop in the moment we finally read a valid edge

}

void createGraph(Graph& graph, size_t edgesCount)
{
    freeGraph(graph);

    graph.edges = new Edge[edgesCount]{};
    graph.edgesCount = edgesCount;

    for (size_t i = 0; i < edgesCount; i++)
    {
        Edge edge;
        readEdge(edge, graph);
        graph.nodesCount += !containsNode(edge.from, graph) + !containsNode(edge.to, graph);
        graph.edges[i] = edge;
    }
}

void addEdge(Graph& graph, const Edge& edge)
{
    if (!validateEdge(graph, edge))
    {
        return;
    }

    graph.nodesCount += !containsNode(edge.from, graph) + !containsNode(edge.to, graph);

    Edge* newEdges = new Edge[graph.edgesCount + 1]{};

    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        newEdges[i] = graph.edges[i];
    }

    newEdges[graph.edgesCount] = edge;
    graph.edgesCount++;

    delete[] graph.edges;
    graph.edges = newEdges;
    newEdges = nullptr;
}

void addEdge(Graph& graph, const char* from, const char* to)
{
    if (!from || !to)
    {
        return;
    }

    Edge edge = initEdge(from, to);

    addEdge(graph, edge);
}

int getInDegree(const Graph& graph, const char* node)
{
    if (!node)
    {
        return -1;
    }

    int deg = 0;

    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        if (!strcmp(graph.edges[i].to, node))
        {
            deg++;
        }
    }

    return deg;
}

int getOutDegree(const Graph& graph, const char* node)
{
    if (!node)
    {
        return -1;
    }

    int deg = 0;

    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        if (!strcmp(graph.edges[i].from, node))
        {
            deg++;
        }
    }

    return deg;
}

bool isGraphFull(const Graph& graph)
{
    return graph.nodesCount == graph.edgesCount * (graph.edgesCount - 1);
}

size_t findEdgeIdxInGraph(const Graph& graph, const Edge& edge)
{
    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        if (equalEdges(edge, graph.edges[i]))
        {
            return i;
        }
    }
    return graph.edgesCount;
}

void removeEdge(Graph& graph, const Edge& edge)
{
    size_t idx = findEdgeIdxInGraph(graph, edge);

    if (idx == graph.edgesCount)
    {
        return;
    }

    std::swap(graph.edges[idx], graph.edges[graph.edgesCount - 1]);
    graph.edgesCount--;
    graph.nodesCount -= (!containsNode(edge.from, graph) + !containsNode(edge.to, graph));

    // is it the best idea? idk but let's aim to make the edges arr with exact size, no filler spots

    Edge* newEdges = new Edge[graph.edgesCount]{};

    for (size_t i = 0; i < graph.edgesCount; i++)
    {
        newEdges[i] = graph.edges[i];
    }

    delete[] graph.edges;
    graph.edges = newEdges;
    newEdges = nullptr;
}

int main()
{
    return 0;
}
