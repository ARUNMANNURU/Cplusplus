#include "stdafx.h"  
#include "InputFileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

InputFileReader::InputFileReader() 
{
  numberOfProcesses =     0;
  numberOfValues    =     0;
  index             =     0;
  fileReadOK        = false;
  return;
}

const int InputFileReader::getNumberOfValues() 
{
  return (fileReadOK)? numberOfValues : 0;
}

const int InputFileReader::getNextValue() 
{
  return (index < numberOfValues) ? vals[index++] : 0;
}

void InputFileReader::readFile()
{

  fileReadOK = false;

  //
  // Read the data from "infile.dat" in the current
  // directory.  It is assumed that the data
  // is OK so no error checking is done.
  //
  FILE* const fp = fopen("infile.dat", "r");

  int lastChar = 0;
  for (int i = 0; i < MAXLENGTH; ++i)
  {

    const char ch = getc(fp);
    if (ch == EOF) 
    {
      fileReadOK = true;
      buffer[lastChar++] = '\0';
      fclose(fp);
      break;
    }

    if((ch!='\n') && (ch!='\r')) buffer[lastChar++] =  ch;
    else                         buffer[lastChar++] = ' ';

  }

  char delim[]      = " ";

  resources[0]      = atoi(strtok(buffer,delim));
  for (int j = 1; j<NUMBERRESOURCES; ++j)
      resources[j] = atoi(strtok(NULL,delim));

  numberOfProcesses = atoi(strtok(NULL,delim));
  numberOfValues    = VALUESPERPROCESS*numberOfProcesses;
  for (int j = 0; j<numberOfValues; ++j)
    vals[j] = atoi(strtok(NULL,delim));

  fileReadOK = true;

  return;
}


