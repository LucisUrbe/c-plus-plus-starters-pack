///
/// @file       graph.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 20, 2024
/// @version    0.2
/// @brief      The graph class, storing a graph using an adjacent matrix.
///

template <typename VERTEX_T, typename EDGE_T>
class graph {
public:
    virtual void insert(VERTEX_T v1, VERTEX_T v2, EDGE_T weight) = 0;
    virtual void remove(VERTEX_T v1, VERTEX_T v2) = 0;
    virtual void exist(VERTEX_T v1, VERTEX_T v2) const = 0;
    int vertex_count() const {
        return vertexes;
    }
    int edge_count() const {
        return edges;
    }
protected:
    int vertexes, edges;
};

// AM: adjacent matrix
template <typename VERTEX_T, typename EDGE_T>
class AMGraph: public graph<VERTEX_T, EDGE_T> {
public:
    AMGraph(int vertex_size, const VERTEX_T raw_vertexes[], const EDGE_T no_edge_flag);
    ~AMGraph();
    void insert(VERTEX_T v1, VERTEX_T v2, EDGE_T weight);
    void remove(VERTEX_T v1, VERTEX_T v2);
    bool exist(VERTEX_T v1, VERTEX_T v2) const;
private:
    EDGE_T** edge; // adjacent matrix
    VERTEX_T* vertex;
    EDGE_T infinity_flag;
    int find(VERTEX_T toFind) const {
        for (int i = 0; i < vertexes; i++)
            if (vertex[i] == toFind)
                return i;
    }
};

template <typename VERTEX_T, typename EDGE_T>
AMGraph<VERTEX_T, EDGE_T>::AMGraph(int vertex_size, const VERTEX_T raw_vertexes[], const EDGE_T no_edge_flag) {
    vertexes = vertex_size;
    edges = 0;
    infinity_flag = no_edge_flag;
    vertex = new VERTEX_T[vertex_size];
    for (int i = 0; i < vertex_size; i++)
        vertex[i] = raw_vertexes[i];
    edge = new EDGE_T*[vertex_size];
    for (int i = 0; i < vertex_size; i++) {
        edge[i] = new EDGE_T[vertex_size];
        for (int j = 0; j < vertex_size; j++)
            edge[i][j] = infinity_flag;
        edge[i][i] = 0;
    }
}

template <typename VERTEX_T, typename EDGE_T>
AMGraph<VERTEX_T, EDGE_T>::~AMGraph() {
    delete [] vertex;
    for (int i = 0; i < vertexes; i++)
        delete [] edge[i];
    delete [] edge;
}

template <typename VERTEX_T, typename EDGE_T>
void AMGraph<VERTEX_T, EDGE_T>::insert(VERTEX_T v1, VERTEX_T v2, EDGE_T weight) {
    int x = find(v1), y = find(v2);
    edge[x][y] = weight;
    edges++;
}

template <typename VERTEX_T, typename EDGE_T>
void AMGraph<VERTEX_T, EDGE_T>::remove(VERTEX_T v1, VERTEX_T v2) {
    int x = find(v1), y = find(v2);
    edge[x][y] = infinity_flag;
    edges--;
}

template <typename VERTEX_T, typename EDGE_T>
bool AMGraph<VERTEX_T, EDGE_T>::exist(VERTEX_T v1, VERTEX_T) const {
    int x = find(v1), y = find(v2);
    return (edge[x][y] != infinity_flag);
}
