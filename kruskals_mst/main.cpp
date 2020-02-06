#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define NAMOUNT 5
#define EAMOUNT NAMOUNT*(NAMOUNT-1)
#define MAX 10
#define MIN 1

struct Edge {
  public:
    int from;
    int to;
    int weight;

    char* toString() {
        char* ret = (char*) malloc(sizeof(char)*32);
        int n = sprintf(ret, "%d->%d@%d", this->from, this->to, this->weight);
        return ret;
    }
};

struct Node {
  public:
    int id;
    std::vector<Edge> edges;

    Node(int id, std::vector<Edge> edges) {
        this->id = id;
        this->edges = edges;
    }
};

int random(int lower, int upper) {
    return rand()%(upper+1-lower)+lower;
}

int random_except(int n, int lower, int upper) {
    int ret;
    while ((ret = random(lower, upper)) == n);
    return ret;
}

void sort_edges(Edge* a, int left, int right) {
    Edge p = a[right];
    int l = left, r = right;

    while (l < r) {
        while (l < r && a[l].weight <= p.weight) l++;
        while (r > l && a[r].weight >= p.weight) r--;
        Edge t = a[l];
        a[l] = a[r];
        a[r] = t;
    }

    a[right] = a[l];
    a[l] = p;

    if (l - 1 - left > 0) sort_edges(a, left, l-1);
    if (right - l - 1 > 0) sort_edges(a, l+1, right);
}

bool includes(std::vector<Node> nodes, Node n) {
    for (std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if (it->id == n.id) return true;
    }
    return false;
}

void printa(Edge* a, int len) {
    printf("[ ");
    for (int i = 0; i < len-1; i++) {
        printf("%s, ", a[i].toString());
    }
    printf("%s ]\n", a[len-1].toString());
}

void printc(char c, int n) {
    for (int i = 0; i < n; i++) printf("%c", c);
}

void printt(Node cu, int intend, Node* nodes, std::vector<Node> past_nodes) {
    std::vector<Node> n_past_nodes = std::vector<Node>(past_nodes);
    n_past_nodes.push_back(cu);
    printc(' ', intend);
    printf("%d\n", cu.id);
    for (std::vector<Edge>::iterator it = cu.edges.begin(); it != cu.edges.end(); it++) {
        if (includes(past_nodes, nodes[it->to])) continue;
        printt(nodes[it->to], intend+2, nodes, n_past_nodes);
    }
}

bool cycle(int target, Node current, Node* nodes, std::vector<Node> past_nodes) {
    bool state = false;
    std::vector<Node> n_past_nodes = std::vector<Node>(past_nodes);
    n_past_nodes.push_back(current);
    for (std::vector<Edge>::iterator it = current.edges.begin(); it != current.edges.end(); it++) {
        if (it->to == target) return true;
        if (includes(past_nodes, nodes[it->to])) continue;
        state = cycle(target, nodes[it->to], nodes, n_past_nodes) || state;
    }
    return state;
}

int main() {
    /*
     * Kruskal's Minimum Spanning Tree
     * -------------------------------
     *
     * Build an MST from a given set of nodes and
     * edges using Kruskal's algorithm.
     *
     * // Caution: Doesn't run in QtCreator Community
     * // but it does run when compiled with G++.
     *
     */

    printf("Kruskal's Minimum Spanning Tree\n");
    printc('=', 64);
    printf("\n");

    srand(time(NULL));
    Edge* edges = (Edge*) malloc(sizeof(Edge)*EAMOUNT);
    Node* nodes = (Node*) malloc(sizeof(Node)*NAMOUNT);

    int ind = 0;
    for (int i = 0; i < NAMOUNT; i++) {
        nodes[i] = Node(i, {});
        for (int j = 0; j < NAMOUNT; j++) {
            if (j == i) continue;
            edges[ind++] = { i, j, random(MIN, MAX) };
        }
    }

    printf("Edges:\t\t");
    printa(edges, EAMOUNT);

    sort_edges(edges, 0, EAMOUNT-1);

    printf("Edges:\t\t");
    printa(edges, EAMOUNT);

    nodes[edges[0].from].edges.push_back(edges[0]);
    nodes[edges[0].to].edges.push_back({ edges[0].to, edges[0].from, edges[0].weight });
    int picked = 1;

    for (int i = 1; picked < NAMOUNT-1 && i < EAMOUNT; i++) {
        if (cycle(edges[i].from, nodes[edges[i].to], nodes, {})) continue;
        nodes[edges[i].from].edges.push_back(edges[i]);
        nodes[edges[i].to].edges.push_back({ edges[i].to, edges[i].from, edges[i].weight });
        picked++;
    }

    printf("#Picked:\t");
    printf("%d\n", picked);
    printf("MST: \n");
    printt(nodes[edges[0].from], 2, nodes, {});

    printc('=', 64);
    printf("\n");
    return 0;
}
