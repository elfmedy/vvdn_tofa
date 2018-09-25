#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/shave_system.h>
#include <CyclesCount.h>
#include <Eigen/Core>
#include <Eigen/Eigen>
#include <Eigen/Eigenvalues>
#include <math.h>

#define MAX_MM 5000
#define NB_POINT 27

using namespace std;
using namespace Eigen;

typedef unsigned int u32;

// the code for calculating the mflops is commented

void benchHessengerb()
{
    std::cout<<"\n\n\n----- Bench Hessenberg decomposition  -----\n\n";
    int k=2;
    int size = k*k; // size of matrix
    u32 tick;
//    double tab_mflops[NB_POINT];
    int tab_sizes[NB_POINT];
    int count=0;

    while(size<=MAX_MM)
    {
        tab_sizes[count]=size;

        //matrix initialization
        MatrixXf A(k,k);
        MatrixXf X(k,k);
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                A(i,j)=j;
            }
        }

        //nb_op_base represents the number of operations
//         double nb_op_base = 0;
//         double r,b;
//         for (int j=0; j<size-2; ++j){
//             r = std::max(0,size-j-1);
//             b = std::max(0,size-j-2);
//             nb_op_base += 6 + 3*b + r*r*4 + r*size*4;
//         }

        //getting the execution time
        tick = swcReadPC3();
        for(int i=0;i<NB_REP;i++)
        X = HessenbergDecomposition<MatrixXf>(A).packedMatrix();
        tick = swcReadPC3()-tick;
//        float exec_time = (((float)tick/NB_REP)*(1.0000000/(float)FRQ));
        float cc = (float)tick/(float)NB_REP;
        printf("Size[%d][%d]= %d => CycleCount = %f \n",k,k,size,cc);
   
        //applying the mflops formula: number of operations/(execution time * 1e6)
//        tab_mflops[count++] = ((float)nb_op_base/exec_time)/1000000.000000;

        if(k<9)  k=k+1;
            else k=k+3;
        size = k*k;
    }

//     std::cout<<"\n\n ----- TESTING ----- \n";
//     for(int i=0;i<count;i++){
//         printf("%d. size= %d   ==>   mflops = %g  \n",i,tab_sizes[i], tab_mflops[i]);
//     }
    std::cout<<"\n --> Finished Hessenberg decomposition ! <-- \n\n"<< std::flush;

}
