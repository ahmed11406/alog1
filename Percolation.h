#ifndef Percolation_h
#define Percolation_h
#include "WUFPC.h"
#include<random> // for generating random numbers.
class Percolate: public WUFPC {//inherting from the base class WUFPC, the one containing the WUFPC alogrithm.
    public:
    //global variables declaration
    int vtop_index; // index of virtual top vertex of the grid,
    int vbottom_index; // virtual bottom vertex.
    int total_Cells; // total number of cells in the square grid plus the virtual vertices.
    int OpenCount; // counting the opened cells.
    int single_dim; // user defined grid dimension.
    bool* Cells; // pointer that will point to dyn. mem. locations containing the grid cells.
    Percolate(int i){ //constructor of the class which called whenever an object is created.
        //intializing the above declared variables.
        single_dim=i; 
        //grid cells are enumerated from 0 to single_dim*single_dim -1, 
        //the top vertes is at single_dim*single_dim index, 
        //whilst the bottom is at (single_dim*single_dim)+1 index.
        vtop_index=(single_dim*single_dim);
        vbottom_index=(single_dim*single_dim)+1; 
        total_Cells= (single_dim*single_dim)+2;
        //N is a global variable from the WUFPC class that is assigned to 
        //the number of total objects the alogrithm works on, in this case, it's the total_Cells number.
        N=total_Cells;
        Cells = new bool[N-2]; //intializing dyn. mem. locations of boolean type for the grid cells.
        id= new int[N]; //the dyn. mem. locations for total_Cells IDs used in WUFPC alogrithm.
        sz= new int[N]; //the dyn. mem. locations for total_Cells tree sizes used in WUFPC alogrithm.
        OpenCount=0;    
        //caling the functions that starts the percolation path finding process:
        construct(total_Cells); //intializing the IDs, trees sizes and the Cells locations. 
        start_simu();    //starting the random cell opening process until percolation occurs. 
    }
    ~Percolate(){//destructor which is called whenever the object goes out of scope or manually deleted.
        //deleting the dynamic locations used anywhere througout the class during its object lifetime.
        delete[] id; 
        delete[] sz;
        delete[] Cells;
    }
    void start_simu(){
        int p=0;
        int q=0;
        std::random_device rand_dev1,rand_dev2; //intializing the seeds for the random generators. 
        std::mt19937 gen1(rand_dev1()),gen2(rand_dev2()); //intializing and seeding the generators.
        //random numbers are of integer type and uniformly distributed over the range 0 to single_dim-1.
        std::uniform_int_distribution<int> distr(0,(single_dim-1)); 
        //looping until the percolation function returns true(e.g. finding the percolation path):
        while (!is_percolated()){ 
            p=distr(gen1); //random row.. 
            q=distr(gen2); //random col..
            open(p,q); //opens the grid cell located in the p-th row and q-th column.     
        }
    }
    void construct(int x){
        for(int i=0; i<x; i++){
            id[i]=i; // all IDs intially equal to themselves. see the WUFPC alogrithm.
            sz[i]=1; // all tree sizes intially equal to 1. see the WUFPC alogrithm.
            if(i<x-2){ // since Cells elements are not including the virtual vetices.
                Cells[i]=false; // all grid cells intially is blocked(e.g. not open).
            } 
        }
    }
    void open(int row, int col){
        //to open a cell means to make it one(or true) instead of its initial zero(false) value,
        //and to build the path through the grid, each open cell is to be connected with its
        //neighbouring open cells. The grid is a square grid so the neighbours are 4 cells max.
        if(!(is_open(row,col))){ //if that cell is not already open...
            //these local variables below are used to transform the coordinates of the cell
            //from (row,col) representation to 1-dimension representation (index). 
            int index= (col+row)+(row*(single_dim-1)); 
            int Upindex=index-single_dim;   //the coordinate of the up neighbour.
            int Downindex=index+single_dim; //the coordinate of the down neighbour.
            int Rightindex=index+1;         //the coordinate of the right neighbour.
            int Leftindex=index-1;          //the coordinate of the left neighbour.
            Cells[index]=true;              //open the cell located in (row,col).
            OpenCount++;                    //increment the open cells counter.
            //the following if statements connect that cell with its neighbouring open cell:
            // the unite() and is_connected() are functions defined in the WUFPC header file,
            // see the WUFPC alogrithm header file for more info on this.
            // First, check if the cell resides in the central region of the grid
            //(e.g. not in the first/last row or first/last cols)
            if (col>0 && col<single_dim-1 && row>0 && row<single_dim-1) { 
                if(Cells[Leftindex]==true && !is_connected(index,Leftindex)){//on its left
                    unite(index,Leftindex);
                }
                if(Cells[Rightindex]==true && !is_connected(index,Rightindex)){//on its right 
                    unite(index,Rightindex);
                } 
                if(Cells[Upindex]==true && !is_connected(index,Upindex)){//above it 
                    unite(index,Upindex);
                }
                if(Cells[Downindex]==true && !is_connected(index,Downindex)){//below it 
                    unite(index,Downindex);
                }
                else return;
            }
            // Second, check if the cell resides in the right or left border of the grid
            // except the 4 corner cells.
            else if (row>0 && row<single_dim-1) { 
                if (Cells[Upindex]==true && !is_connected(index,Upindex)){//above it.
                    unite(index, Upindex);
                }
                if (Cells[Downindex]==true && !is_connected(index,Downindex)){//below it. 
                    unite(index, Downindex);
                }                    
                if (col==0){//left border.
                    if(Cells[Rightindex]==true && !is_connected(index,Rightindex)){//its right. 
                        unite(index, Rightindex);
                    } 
                }
                else if (col==single_dim-1){//right border.
                    if(Cells[Leftindex]==true && !is_connected(index,Leftindex)){//its left. 
                        unite(index,Leftindex);
                    } 
                }
                else return;
            }
            // Third, check if the cell resides in the up or down border of the grid.
            // except the 4 corner cells.
            else if (col>0 && col<single_dim-1) {
                if(Cells[Rightindex]==true && !is_connected(index,Rightindex)){//right. 
                    unite(index,Rightindex);
                } 
                if(Cells[Leftindex]==true && !is_connected(index,Leftindex)){//left. 
                    unite(index,Leftindex);
                }
                if(row==0){//up border. 
                    if(!is_connected(index,vtop_index)){//connect to virtual top vertex. 
                        unite(index, vtop_index);
                    } 
                    if(Cells[Downindex]==true && !is_connected(index,Downindex)){//below. 
                        unite(index,Downindex);
                    }                    
                }
                else if (row==single_dim-1){//down border.
                    if(!is_connected(index,vbottom_index)){//connect to virtual bottom vertex. 
                        unite(index,vbottom_index);
                    }
                    if(Cells[Upindex]==true && !is_connected(index,Upindex)){//above. 
                        unite(index, Upindex);
                    }
                }
                else return;
            }
            // Forth, check if the cell resides in rightmost/leftmost corner of the grid's up border.
            else if (row==0) {//first row..
                if(!is_connected(index,vtop_index)){//connect to the virtual top vertex. 
                    unite(index, vtop_index);
                } 
                if(Cells[Downindex]==true && !is_connected(index,Downindex)){//below. 
                    unite(index, Downindex);
                }
                if(col==0){//the up leftmost cell in the grid's corner. 
                    if(Cells[Rightindex]==true && !is_connected(index,Rightindex)){//right. 
                        unite(index,Rightindex);
                    } 
                }
                else if(col==single_dim-1){////the up rightmost cell in the grid's corner.
                    if(Cells[Leftindex]==true && !is_connected(index,Leftindex)){//left. 
                        unite(index,Leftindex);
                    }
                }
                else return;
            }
            // Finally, check if the cell resides in rightmost/ leftmost corner of the grid's down border.
            else if (row==single_dim-1) {
                if(!is_connected(index,vbottom_index)){//connect to the virtual bottom vertex. 
                    unite(index,vbottom_index);
                } 
                if(Cells[Upindex]==true && !is_connected(index,Upindex)){//above it. 
                    unite(index,Upindex);
                }
                if(col==0){//the leftmost cell in the grid's down corner.
                    if(Cells[Rightindex]==true && !is_connected(index,Rightindex)){//right. 
                        unite(index,Rightindex);
                    } 
                }
                else if(col==single_dim-1){//the rightmost cell in the grid's down corner.
                    if(Cells[Leftindex]==true && !is_connected(index,Leftindex)){//left. 
                        unite(index,Leftindex);
                    }
                }
                else return;//
            }
        else return;
        }
        return;
    }
    bool is_open(int row, int col){//check whether the cell in (row, col) coordinates is open. 
        int index=(col+row)+(row*(single_dim-1));//transform coordinates(row,col) to single coordinate(index).
        if (Cells[index]==true){ 
            return true;
        }
        else return false;
    }
    bool is_percolated(){//check whether there's a path connecting the top row to the bottom row.
        //following the above alogrithm, any open cell in the top row is connected to the virtual top vertex.
        //and any open cell in the bottom row is connected to the virtual bottom vertex. 
        //then, if the top vertex is connected to the bottom one, the system percolates.  
        return is_connected(vbottom_index,vtop_index);
    }
    double probability(){//returns the fraction of open cells to total cells, excluding the vetices.
        return static_cast<double>(OpenCount)/(single_dim*single_dim);
    }
};
#endif