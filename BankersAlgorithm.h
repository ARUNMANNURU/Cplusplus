#if !defined(bankersAlgorithm___INCLUDED)
#define      bankersAlgorithm___INCLUDED

#include "InputFileReader.h"
#include <vector>

using namespace std;
class BankersAlgorithm
{

  const bool               verbose;

  InputFileReader* const       ifr;

  const int           numProcesses;
  const int           numResources;
  const int*             resources;

  typedef vector<int>       vIType;
  typedef vector<bool>      vBType;
  typedef vIType::iterator  vIIter;
  typedef vBType::iterator  vBIter;

  vIType             tempResources;
  vBType                      ftst;
  vBType                      fini;
  vIType                      aSeq;

  class vWType
  {
  public:
    vIType v;
    vWType& vWType::operator+=(vWType& x)
    {
      if (this->v.size())
      {
        vIIter l = v.begin();
        for (vIIter r = x.v.begin(); r != x.v.end(); ++r)
        {
            *l += *r;
            ++l;
        }

      }
      else this->v = x.v;
      return *this;
    }


  

    vWType& vWType::operator-=(vWType& x)
    {
      vIIter l = v.begin();
      for (vIIter r = x.v.begin(); r != x.v.end(); ++r)
      {
         if (this->v.size())
            *l -= *r;
         else
            *l = -*r;  
         ++l;
      }
      return *this;
    }
  };

  vWType work;

  class rROW
  {
  public:
    vWType mx;
    vWType al;
    vWType nd;
  };

  typedef vector<rROW*>    vTType;
  typedef vTType::iterator vVIter;

  vTType                   rTable;

  void oV(const char* const c, vIType& a, const int r);
  void oB(const char* const c, vBType& a, const int r);
  void dump();

public:

  BankersAlgorithm
    ( InputFileReader* const infr,
      const int                np,
      const int                nr,
      const int* const          r,
      const bool                v 
    );

	bool LE( vWType& lhs, vWType& rhs)
	{
      vIIter l = lhs.v.begin();
      for (vIIter r = rhs.v.begin(); r != rhs.v.end(); ++r)
      {
	     if(*l<*r) return false;  
         ++l;
      }
      return true;
    }

  const bool execute();

  const int  getSafeProcess(const unsigned int i);

  void       load();

  ~BankersAlgorithm() {rTable.clear();}

};

#endif