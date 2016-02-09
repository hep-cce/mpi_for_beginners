// Author: Thomas LeCompte (Argonne)
// This shows a trivial MPI program.  The idea is that one can take an
//   existing piece of code and alter it so that N ranks run simultaneously
//   in different directories with different random number seeds.  The 
//   subdirectories are named 0,1...10...100... up to the highest numbered
//   rank.
// This will not scale to tens of thousands of ranks, but it will get
//   you started.

// This line needs to be added to your code 
#include <mpi.h>

#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <unistd.h>
using namespace std;

main() {

// These two lines need to be added to your code
   int Rank;
   std::stringstream directory;

   float Rfloat;   
   FILE *outfile;


// These two lines need to be added to your code
   MPI_Init((int *)0, (char ***)0);
   MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

// This line needs to be changed in your code
// Seed the random number generator with the rank
//    The plus 1 is there because seeding the RNG with zero
//    can be problematic.  Other RNGs seed differently,
//    but this shows what needs to happen.
   srand(Rank+1);

// These five lines need to be added to your code
   directory << Rank;
   if(chdir(("./"+directory.str()).c_str())!=0) {
      fprintf(stderr,"Rank %d failed to change directories.\n");
      exit(1);
   }




// ============== The original code goes here ============= 

   outfile=fopen("output.dat","w");
   Rfloat = 1.0*rand()/RAND_MAX;
   fprintf(outfile,"Rfloat = %f\n",Rfloat);

// ============== End of the original code ================






// This line needs to be added to your code
   MPI_Finalize();

}
