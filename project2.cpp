// project2.cpp : Defines the entry point for the console application.
//

#include           "stdafx.h"
#include  "InputFileReader.h"
#include "BankersAlgorithm.h"

int main(int argc, char* argv[])
{

  InputFileReader* ifr = new InputFileReader;

  //
  // Read the values
  // from the input
  // file.
  //
  try
  {
    ifr->readFile();
  }
  catch (...) 
  {printf("***** Error reading input file *****\n\n");}

  //
  // If the file
  // was read OK,
  // invoke the
  // algorithm.
  //
  if(ifr->getFileReadOK()) 
  {
    const int nP = ifr->getNumberOfProcesses();
    BankersAlgorithm BA(ifr, 
                        nP,
                        ifr->getNumberOfResources(), 
                        ifr->getResources(), 
                        argc>1);

    //
    // If the algorithm reports "safe state" (returns
    // "true") print out the safe order to schedule
    // the processes.  Otherwise just report
    // "unsafe state."
    // 
    if (BA.execute()) 
    {
      printf("\nAlgorithm reports SAFE STATE\n");
      printf("  Order to safely schedule processes: ");
      for (int i=0; i<nP; ++i)
        printf("P%d ",BA.getSafeProcess(i));
      printf("\n\n");
    }
    else
      printf("\nAlgorithm reports UNSAFE STATE\n\n");  
  }

  delete ifr;

  return 0;

}

