C Author: Thomas LeCompte (Argonne)
C This shows a trivial MPI program.  The idea is that one can take an
C   existing piece of code and alter it so that N ranks run simultaneously
C   in different directories with different random number seeds.  The 
C   subdirectories are named 0,1...10...100... up to the highest numbered
C   rank.
C This will not scale to tens of thousands of ranks, but it will get
C   you started.

       program trivial 
       implicit none

C This line needs to be added to your code 
      include 'mpif.h'

C These two lines need to be added to your code
       integer rank, ierr
       character(10) directory

C These two lines need to be added to your code
       call MPI_INIT(ierr)
       call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)

C This line needs to be changed in your code
C Seed the random number generator with the rank
C    The plus 1 is there because seeding the RNG with zero
C    or small values can be problematic.  Other RNGs seed differently,
C    (and you should probably consider them, as rand is not very good)
C     but this shows what needs to happen.
      call srand(rank+1)

C These six lines need to be added to your code
       write(directory,'(i5)') rank
       call chdir (trim(adjustl(directory)),ierr)
       if(ierr.ne.0) then
         write(0,*) 'Rank ',rank,' failed to change directories'
         call exit(1)
       endif



C =============== The original code goes here ============= 

      open(unit=7, file='output.dat', status='replace')
      write(7,*) rand() 
      close(7)

C ============== End of the original code ================





C This line needs to be added to your code
      call MPI_FINALIZE(ierr)

      end program
