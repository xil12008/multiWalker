#READ ME

The graph.cpp and graph.h files are copied from previous project powerlawP2P. They store graph as adjacent list in the memory and support operations including adding edge, removing edge, checking node degrees.

a node could have more attributes as required in new cases. For multi-layer networks, a node should have a flag for the type (i.e. layer number), and then the type of an edge is naturally determined by the types of its two ends. 
A meta-path is determined by the sequence of the types of nodes. A hashing function, which maps a specific path (an instance) to its meta-path type, should be constructed. The possiblity of a random walk on an edge from source node X should be computed by the number of each type of the edges starting from X, which is p{type t} = 1/(the number of edges with type t). Every node should have a vector rp={r of meta-path i}, storing the random walk possibility of each meta-path.   
# multiWalker
