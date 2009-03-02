// graphtraverse.cpp
// Glenn G. Chappell
// 4 Dec 2006
// 
// For CS 311
// Graph traversals demo: DFS & BFS

#include <iostream>
using std::cout;
using std::endl;
#include <stack>   // for std::stack
#include <queue>   // for std::queue
#include <vector>  // for std::vector


// dfs
// Prints Depth-First Search ordering of vertices of graph
// described by given adjacency matrix.
//
// Vertices are numbered 0 .. numVerts-1.
// adjMat represents 0,1-matrix of size numVerts x numVerts.
// i,j entry of matrix is adjMat[i*numVerts + j].
// 
// Pre:
//     numVerts >= 0.
//     adjMat has size at least numVerts * numVerts
// Post:
//     DFS, as described above, has been printed to std::cout,
//      blank-separated vertex numbers, followed by blank,
//      then newline.
// May throw std::bad_alloc.
// Basic Guarantee (but only std::cout is modified).
void dfs(const std::vector<int> & adjMat,
         int numVerts,
         int start)
{
    std::stack<int> s;
    std::vector<int> visited(numVerts, 0);

    s.push(start);

    while (!s.empty())
    {
        int vert = s.top();
        s.pop();

        if (visited[vert])
            continue;

        cout << vert << " ";
        visited[vert] = 1;

        for (int i = numVerts-1; i >= 0; --i)
        {
            if (adjMat[vert*numVerts + i] && !visited[i])
                s.push(i);
        }
    }
    cout << endl;
}


// bfs
// Prints Breadth-First Search ordering of vertices of graph
// described by given adjacency matrix.
//
// Vertices are numbered 0 .. numVerts-1.
// adjMat represents 0,1-matrix of size numVerts x numVerts.
// i,j entry of matrix is adjMat[i*numVerts + j].
// 
// Pre:
//     numVerts >= 0.
//     adjMat has size at least numVerts * numVerts
// Post:
//     BFS, as described above, has been printed to std::cout,
//      blank-separated vertex numbers, followed by blank,
//      then newline.
// May throw std::bad_alloc.
// Basic Guarantee (but only std::cout is modified).
void bfs(const std::vector<int> & adjMat,
         int numVerts,
         int start)
{
    std::queue<int> s;
    std::vector<int> visited(numVerts, 0);

    s.push(start);

    while (!s.empty())
    {
        int vert = s.front();
        s.pop();

        if (visited[vert])
            continue;

        cout << vert << " ";
        visited[vert] = 1;

        for (int i = 0; i < numVerts; ++i)
        {
            if (adjMat[vert*numVerts + i] && !visited[i])
                s.push(i);
        }
    }
    cout << endl;
}


int main()
{
    // 8-Cycle
    // 8 vertices: 0 .. 7.
    // Adjacencies: 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 0
    const int NUMVERTS = 8;
    std::vector<int> adjMat(NUMVERTS * NUMVERTS, 0);

    for (int i = 0; i < NUMVERTS; ++i)
    {
        adjMat[i*NUMVERTS + (i+1)%NUMVERTS] = 1;
        adjMat[((i+1)%NUMVERTS)*NUMVERTS + i] = 1;
    }

    cout << "8-Cycle" << endl;
    cout << "DFS: ";
    dfs(adjMat, NUMVERTS, 0);
    cout << "BFS: ";
    bfs(adjMat, NUMVERTS, 0);
    cout << endl;

    // Binary Tree
    // 7 vertices: 0 .. 6.
    // Adjacencies: 0 - 1, 0 - 2
    //              1 - 3, 1 - 4
    //              2 - 5, 2 - 6
    const int NUMVERTS2 = 7;
    std::vector<int> adjMat2(NUMVERTS2 * NUMVERTS2, 0);
    adjMat2[0*NUMVERTS2 + 1] = 1;  // Edge 0 - 1
    adjMat2[1*NUMVERTS2 + 0] = 1;
    adjMat2[0*NUMVERTS2 + 2] = 1;  // Edge 0 - 2
    adjMat2[2*NUMVERTS2 + 0] = 1;
    adjMat2[1*NUMVERTS2 + 3] = 1;  // Edge 1 - 3
    adjMat2[3*NUMVERTS2 + 1] = 1;
    adjMat2[1*NUMVERTS2 + 4] = 1;  // Edge 1 - 4
    adjMat2[4*NUMVERTS2 + 1] = 1;
    adjMat2[2*NUMVERTS2 + 5] = 1;  // Edge 2 - 5
    adjMat2[5*NUMVERTS2 + 2] = 1;
    adjMat2[2*NUMVERTS2 + 6] = 1;  // Edge 2 - 6
    adjMat2[6*NUMVERTS2 + 2] = 1;

    cout << "Binary Tree" << endl;
    cout << "DFS: ";
    dfs(adjMat2, NUMVERTS2, 0);
    cout << "BFS: ";
    bfs(adjMat2, NUMVERTS2, 0);
    cout << endl;

    return 0;
}
