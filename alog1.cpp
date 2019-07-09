
#include <iostream>
#include "PercolationStatistics.h"
using namespace std;
int main() {
    int x, y;
    cout<<"Please enter only ONE dimension of the square grid followed by the No. of trials you want: \n";
    cout<<"-----------------------------------------------------------------------------------------\n";
    cout<<"Grid's single dimension: \n";
    cin>>x;
    cout<<"No. of experiments: \n";
    cin>>y;
    cout<<"The simulation is running....\n";
    cout<<"-----------------------------------------------------------------------------------------\n";
    getchar();
    PercolationStats MCS(x, y);
    getchar();
    return 0;
}
