class WUFPC {
    public: //all the following is public. 
    //Declaring the global variables..
    int N;  //N: the total number of objects that the alogrithm works on.
    int* id;//the pointer that is to point to the objects IDs array. 
    int* sz;//a pointer to trees sizes that weights each tree root with the num. of objects connected to it. 
    void construct(int x){//construct the alogrithm: initializing N, IDs and size mem. locations.
        N=x;
        id= new int[N]; //N dyn. mem. locations of integer type is assigned to id pointer.
        sz= new int[N]; //N dyn. mem. locations of integer type is assigned to sz pointer.
        for(int i=0; i<N; i++){
          id[i]=i; // at first, each object id equals to itself.
          sz[i]=1; // and each tree size is equal to 1. they all are roots in the meantime. 
        }
    } 
    bool is_connected(int p, int q){//check whether the object p and q is connected.
        return  (root(p)==root(q))? true: false; //if they are connected, they have the same root.
    }
    int root(int p){//the root finding alogrithm:
        if (id[p]!=p){//check whether the object p is already a root, this is true if the ID of p = p.
            int pindex=p;//local variable to register p index so it can be accessed from anywhere in the function.
            int i=0;//a local variable that registers the number of parents attached with the root of p
                    //which is used later to compress the tree branches into a flat tree. 
            int pc[N]; //a local array whose elements are the objects connected to the root of p(parents of p).  
            while (p<N){
                if(p!=id[p]){// while object p is not the root yet,
                    pc[i]= p; // register object p in the path comp. array,
                    p= id[p]; // assign the id of p to the object p, here id[p] is not changed, but p itself is.
                    i++;     // increment the parent counter.
                }
                else break;//break out of the root once the the root of p is found, now its assigned to p.
            }
            if(id[pindex]!=p){//now p is the root of p, not the object p, the object p is registered in pindex.
                        //this checks whether the ID of the object p(id[pindex]) is already its root.
                        //this is nesscary to ensure that the program won't go on to compress the path 
                        //if it's already compressed(already flat and the object directly points to its root).
                for (int j=0; j<i; j++){//iterate over all parents(their num is now known, i).
                                        //Also, their values are now known and registered in pc array. 
                    id[pc[j]]=p;//change the parents' ID to the root p. This compress the path, resulting in flat trees. 
                }
            }
            else return p; //if the path is already compressed, return p, the root.
        }
        else return p;  
        return p;
    }
    void unite(int p, int q){//connecting two objects by connecting their roots:
        int i= root(p);
        int j= root(q); 
        if (i == j) {//if their roots is already equal, they are already connected.
            return;
        }
        else if (sz[i]>sz[j]) {//if not, then assign the id of the bigger tree root to the id of the smaller one.
            id[j]=i; // now the smaller tree is attached to the bigger one. 
            sz[i]+=sz[j]; //add the size of the smaller tree to the size of the bigger one.
        }
        else { 
            id[i]=j;
            sz[j]+=sz[i];
        }        
          
    }
};




