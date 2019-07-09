//HeaderFile guards: ifndef, define, endif.
#ifndef PercolationStatistics_h
#define PercolationStatistics_h
#include "Percolation.h"
#include<math.h>   // for power arthimatic calculations (pow() function).
#include<iostream>
#include<iomanip> // for setting the precision for double type.
#include<chrono> //for execution time calculations.
using namespace std::chrono;
class PercolationStats: public Percolate { // Percolate is the base class for the PercolationStats class.
    // declaring global variables..
    public:         // all is defined as public.
    double* trials; // declaring a pointer that will point to the dynamic mem registering the trials outputs.
    int trials_num; // no. of trials desaired.
    //using the mean_var, standard_dev, CIL, CIH as global variables permits the program to use function outputs
    //multiple times wherever needed throughout the class without calling the expensive function each time required.
    double prob_accumlator, mean_var, standard_dev, CIL, CIH;
    PercolationStats(int x, int y): Percolate(x) { 
        // by default, the default base class constructor is called when an instance of derived class is created, if 
        // a specific constructor in the base class is used by the derived class it should be initiated in that class
        // using its own constructor(e.g. derived_class_constr(): specific base_class_constr() {})
        auto timer_start= high_resolution_clock::now();   //START the timer
        // initializing variables in the constructor:
        trials_num=y;  
        mean_var=0;
        standard_dev=0;
        CIL=0;
        CIH=0;
        trials= new double[trials_num]; //intializing the dynamic memory locations of double type.
        trials[0]=probability(); //the first trial is done once an object is created,
        prob_accumlator=trials[0]; //that's because the base_class_constr is automatically called.
        //creating a loop to start the simulation a user specified number of times.
        for (int i=1; i<trials_num; i++){ 
            Percolate grid(x); // creating an object of the base class with user defined parameter..
            trials[i]= grid.probability(); // register the simulation output into dyn. mem.
            prob_accumlator+=trials[i];  // adding all outputs togather for calculating their mean.
            // before checking the condition for the next iteration, the object "grid" is destructed/deleted
            // automatically by going out of scope.
        }
        //calling the statistics functions: 
        mean(); 
        standard_deviation();
        confidence_interval_low();
        confidence_interval_high();
        //calling desplaying results function:
        display();
        //stopping the timer and calculating the alogrithm execution time:
        auto timer_end= high_resolution_clock::now();    //STOP
        std::cout<<"---------------------------------------------------------------------------------";
        std::cout<<"\nSuccessful Simulation\n";
        auto duration= duration_cast<microseconds>(timer_end-timer_start); //a standard templete function for duration.
        auto CPU_Time= (duration.count())*pow(10, -6);
        std::cout<<"\n-----------------------------\nElapsed time= "<<CPU_Time<<" seconds\t \n";
    }
    double mean(){
        mean_var= prob_accumlator/trials_num;
        return mean_var;  
    }
    double standard_deviation(){
        double z=0;
        double x=0;
        for (int i=0; i<trials_num; i++){
            z=trials[i]-mean_var;
            x+=pow(z,2);
        }
        standard_dev= x/(trials_num-1);
        return standard_dev;
    }
    double confidence_interval_low(){
        CIL= ((mean_var)-((1.96*standard_dev)/sqrt(trials_num)));
        return CIL;
    }
    double confidence_interval_high(){
        CIH= ((mean_var)+((1.96*standard_dev)/sqrt(trials_num)));
        return CIH;
    }
    void display(){
        std::cout<<"The Monte Carlo simulation of Percolation problem results are the following:\n";
        std::cout<<"---------------------------------------------------------------------------------\n";
        std::cout<<"Grid dimensions: "<<single_dim<<" x "<<single_dim<<"\n";
        std::cout<<"Total cells in the grid: "<<single_dim*single_dim<<" cells"<<"\n";
        std::cout<<"Sample size: "<<std::setprecision(15)<<trials_num<<" trials\n";
        std::cout<<"Threshold mean: "<<mean_var<<"\n";
        std::cout<<"Threshold standard deviation: "<<standard_dev<<"\n";
        std::cout<<"Threshold 95% confidence interval: ["<<CIL<<", "<<CIH<<"]\n";
    }
};
#endif