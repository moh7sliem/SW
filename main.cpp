#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* temp = new Value[sz];
            for (int i = 0; i < n; ++i) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[n++] = v;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

struct Node {
    Array<int> adj;

    void Initialize() { adj.Initialize(); }
    void Destroy() { adj.Destroy(); }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; ++i) nodes[i].Initialize();
    }

    void Destroy() {
        for (int i = 0; i < n; ++i) nodes[i].Destroy();
        delete[] nodes;
    }
};

template<class Type>
struct Queue {
    int f, n;
    Type* elems;

    void Initialize(int size) {
        f = 0;
        n = 0;
        elems = new Type[size];
    }

    void Destroy() {
        delete[] elems;
    }

    void Add(Type t) {
        elems[(f + n) % 2500] = t;
        n++;
    }

    Type Pop() {
        Type t = elems[f];
        f = (f + 1) % 2500;
        n--;
        return t;
    }

    int Num() {
        return n;
    }
};

int main() {
    int E;
    cin >> E;

    Graph graph;
    graph.Initialize(E);


    for (int i = 0; i < E; ++i) {
        int N;
        cin >> N;
        for (int j = 0; j < N; ++j) {
            int friendID;
            cin >> friendID;
            graph.nodes[i].adj.AddLast(friendID);
        }
    }

    int T;
    cin >> T;

    while (T--) {
        int source;
        cin >> source;

        bool visited[2500] = {false};
        int boomSize[2500] = {0};

        Queue<int> queue;
        queue.Initialize(2500);
        queue.Add(source);
        visited[source] = true;

        int maxBoomSize = 0, firstMaxDay = 0, day = 0;

        while (queue.Num() > 0) {
            int currentDaySize = queue.Num();
            int dailyBoom = 0;

            for (int i = 0; i < currentDaySize; ++i) {
                int u = queue.Pop();

                for (int j = 0; j < graph.nodes[u].adj.n; ++j) {
                    int v = graph.nodes[u].adj[j];
                    if (!visited[v]) {
                        visited[v] = true;
                        queue.Add(v);
                        dailyBoom++;
                    }
                }
            }

            if (dailyBoom > maxBoomSize) {
                maxBoomSize = dailyBoom;
                firstMaxDay = day + 1;
            }

            day++;
        }

        if (maxBoomSize == 0) {
            cout << "0\n";
        } else {
            cout << maxBoomSize << " " << firstMaxDay << "\n";
        }

        queue.Destroy();
    }

    graph.Destroy();
    return 0;
}
