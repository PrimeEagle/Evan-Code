#include <climits>
#include <algorithm>
#include <queue>
#include <time.h>
#include "ECLgraph.h"
#include <windows.h>

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
    int  tz_minuteswest; /* minutes W of Greenwich */
    int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval* tv, struct timezone* tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv)
    {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        /*converting file time to unix epoch*/
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tmpres /= 10;  /*convert into microseconds*/
        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if (NULL != tz)
    {
        if (!tzflag)
        {
            _tzset();
            tzflag++;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}



static void Dijkstra(const int src, const ECLgraph& g, int* const dist, int* const parent)
{
  // initialize dist and parent array
  for (int i = 0; i < g.nodes; i++)
  {
    dist[i] = INT_MAX;
    parent[i] = 0;
  }
  dist[src] = 0;

  // set up priority queue with just source node in it
  std::priority_queue< std::pair<int, int> > pq;
  pq.push(std::make_pair(0, src));
  while (pq.size() > 0) {
    // process closest vertex
    const int v = pq.top().second;
    pq.pop();
    const int dv = dist[v];
    // visit outgoing neighbors
    for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++) {
      const int n = g.nlist[i];
      const int d = dv + g.eweight[i];
      // check if new lower distance found
      if (d < dist[n]) {
        dist[n] = d;
        parent[n] = v;
        pq.push(std::make_pair(-d, n));
      }
    }
  }
}

static void BellmanFord(const int src, const ECLgraph& g, int* const dist,int* const parent)
{
   // egin by initializing all the distances of all nodes with MAX_INT, except for the source node, which is initialized with zero
    // Initialize distances to all vertices as infinite and parent of each vertex as -1
    for (int i = 0; i < g.nodes; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    //Next, we perform V - 1 steps.
    //  In each step, we iterate over all the edges inside the graph.
    //   For each edge from node u to v, we update the respective distances of v if needed.
    //   The new possible distance equals to the distance of u plus the weight of the edge between u and v.

    // Distance to source vertex is 0
    dist[src] = 0;

    // Relax all edges |V| - 1 times, where V = number of nodes
    for (int i = 0; i <= g.nodes - 1; i++) 
    {
        for (int j = 0; j < g.edges; j++)
        {
            int nindex = g.nindex[i];
            int u = i;
            int v = g.nlist[nindex];         
            int weight = g.eweight[nindex];

            if (dist[u] != INT_MAX && (dist[u] + weight) < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }
}


static void MST_prim(const int src, const ECLgraph& g, int* const dist, int* const prev, int* const color)
{
  
}


int main(int argc, char* argv[])
{
  printf("MST & SSSP (%s)\n", __FILE__);
  if (argc != 2) {fprintf(stderr, "USAGE: %s input_file_name\n", argv[0]); exit(-1);}

  // process command line
  ECLgraph g = readECLgraph(argv[1]);
  if (g.eweight == NULL) {fprintf(stderr, "ERROR: graph must have weights\n"); exit(-1);}
  printf("input: %s\n", argv[1]);
  printf("nodes: %d\n", g.nodes);
  printf("edges: %d\n", g.edges);
  const int source = 0;
  if ((source < 0) || (source >= g.nodes)) {fprintf(stderr, "ERROR: source_node_number must be between 0 and %d\n", g.nodes); exit(-1);}
  printf("source: %d\n", source);

  //MST Prim
  int* const distance = new int[g.nodes];
  int* const prev = new int[g.nodes];
  int* const color = new int[g.nodes];

  MST_prim(source,g, distance, prev, color);
  //comment this part when running with the large graphs
  for (int v = 1; v < g.nodes; v++) {
    printf("(%d ,  %d) and dist %d \n", v, prev[v],distance[v]);
  }
  timeval start, end;
  // SSSP
  int* const dist = new int[g.nodes];
  int* const parent = new int[g.nodes];
  gettimeofday(&start, NULL);
  BellmanFord(source, g, dist, parent);
  gettimeofday(&end, NULL);
  printf("BellmanFord runtime: %.6f s\n", end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0);
  int maxnode = 0;
  for (int v = 1; v < g.nodes; v++) {
    if (dist[maxnode] < dist[v]) maxnode = v;
  }
  printf("vertex %d has maximum distance %d\n", maxnode, dist[maxnode]);

  // compare yout solutions
  int* const verify = new int[g.nodes];
  gettimeofday(&start, NULL);
  Dijkstra(source, g, verify, parent);
  gettimeofday(&end, NULL);
  printf("Dijkstra runtime: %.6f s\n", end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0);
  for (int v = 0; v < g.nodes; v++) {
    if (dist[v] != verify[v]) {fprintf(stderr, "ERROR: verification failed for node %d: %d instead of %d\n", v, dist[v], verify[v]); exit(-1);}
  }
  printf("verification passed\n\n");
 
  // free memory
  delete [] verify;
  delete [] distance;
  delete [] dist;
  delete [] prev;
  delete [] color;
  freeECLgraph(g);
  return 0;
}