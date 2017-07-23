#include "stdafx.h"
#include "BankersAlgorithm.h"


BankersAlgorithm::BankersAlgorithm
        (
        InputFileReader* const infr,
        const int                np,
        const int                nr,
        const int* const          r,
        const bool                v 
        ) :
  verbose(v),
  numProcesses(np),
  numResources(nr),
  resources(r),
  ifr    (infr)
{

  //
  // Load the data read from the input file
  // into the internal data structures.
  //
  this->load();
}

void BankersAlgorithm::load()
{

  //
  // Load the internal data structures needed by the
  // Banker's Algorithm.
  //
  vWType tempWork;

  for (int i=0; i<numProcesses; ++i)
  {

    //
    // Create a new row and populate it from values
    // extracted from the input file.
    //
    rROW* r = new rROW();
    for (int j=0; j<numResources; ++j)
      r->mx.v.push_back(ifr->getNextValue());

    for (int j=0; j<numResources; ++j)
    {
      r->al.v.push_back(ifr->getNextValue());
      r->nd.v.push_back(r->mx.v[j] - r->al.v[j]);
    }
    tempWork += r->al;

    //
    // Add the row to the computation
    // table.
    //
    rTable.push_back(r);

  }

  //
  // Compute the initial values for the
  // "work," "finish" and "all true" vectors.
  //
  for (int j=0; j<numResources; ++j)
    tempResources.push_back(resources[j]);

  for (int j=0; j<numProcesses; ++j)
  {
    fini.push_back(false);
    ftst.push_back (true);
  } 
   
  work.v  = tempResources;
  work   -=      tempWork;

}

//
// The following three functions are used
// to dump the contents of the internal 
// structures when verbose is set to true.
//
void BankersAlgorithm::oV(const char* const c, vIType& a, const int r=0)
{
  if (verbose)
  {
    printf(c);
    if (a.size())
      for(vIIter i = a.begin(); i!=a.end(); ++i) printf("%d ",*i);
      else printf(" ** empty **");
    if(r) for (int k=0; k<r; ++k) printf("\n");
  }
}

void BankersAlgorithm::oB(const char* const c, vBType& a, const int r=0)
{
  if (verbose)
  {
    printf(c);
    for(vBIter i = a.begin(); i!=a.end(); ++i) 
      if (*i) printf("T ");
      else    printf("F ");
    if(r) for (int k=0; k<r; ++k) printf("\n");
  }
}

void BankersAlgorithm::dump()
{
  if (verbose)
  {
    int pID = 0;
    printf("\n   DUMP of internal values:\n");
    oV("\nResources: ",tempResources, 1);
    for(vVIter i = rTable.begin(); i!=rTable.end(); ++i)
    {
      printf("Process ID: P%d   ", pID++);
      oV("Max: ",    (*i)->mx.v  );
      oV("  Alloc: ",(*i)->al.v  );
      oV("  Need: ", (*i)->nd.v,1);
    }
    oV("Work:   ",       work.v,1);
    oB("Finish: ",       fini,  1);
    oV("Safe Sequence: ",aSeq,  1);
  }
}

const int  BankersAlgorithm::getSafeProcess(const unsigned int i) 
{
  if   (i<numProcesses) return aSeq[i];
  else                  return      -1;
}

const bool BankersAlgorithm::execute()
{

  vIType   workLast;

  //
  // Loop until the work vector doesn't change (Unsafe) or
  // until final vector is all true (safe);
  //
  while(workLast != work.v)
  {

    workLast = work.v;

    for(int pID=0; pID<numProcesses; ++pID)
    {
      dump();

      //
      // If the work vector >= need then it's OK to
      // allocate the requested resources and 
      // schedule the process next.
      //
      if(LE(work,rTable[pID]->nd)) 
      {

        //
        // If the process has not been 
        // scheduled it is OK to do so.
        //
        if(!fini[pID])
        {

          //
          // Add the needed resources to the work vector,
          // schedule the process and test if all processes
          // have been scheduled.
          //
          work      += rTable[pID]->al;
          fini[pID]  =     true;
          aSeq.push_back(pID);
          if (fini == ftst)
          {
            dump();
            return true;
          }

        }
      }
    }
  }
  return false;
}






