#if !defined(InputFileReader___INCLUDED)
#define      InputFileReader___INCLUDED

class InputFileReader
{

  enum {VALUESPERPROCESS  = 6};
  enum {NUMBERRESOURCES   = 3};

  int index;
  int numberOfValues;

  enum {MAXLENGTH = 2048};
  char  buffer[MAXLENGTH];

  enum {MAXVALS = 1024};
  int     vals[MAXVALS];

  bool fileReadOK;

  int  numberOfProcesses;

  int  resources[NUMBERRESOURCES];

public:

  InputFileReader();
  void      readFile();
  const int getNumberOfValues();
  const int getNextValue();

  inline const bool       getFileReadOK()        {return        fileReadOK;}
  inline const int        getNumberOfResources() {return   NUMBERRESOURCES;}
  inline const int* const getResources()         {return         resources;}
  inline const int        getNumberOfProcesses() {return numberOfProcesses;}
};

#endif