////////////////////////////////////////////////////////////////////////////////
// File         : fuzzy.h
// Project      : 
// Subsystem    : 
// Component    : 
// Author       : Igor Sarzi Sartori
// Description  : fuzzy class that implemets simple fuzzy operator
////////////////////////////////////////////////////////////////////////////////
// Copyright (C) Siemens AG 2000
// Automotive Electronics
// Alle Rechte vorbehalten. All Rights Reserved.
//
// The reproduction, transmission or use of this document or its contents is
// not permitted without express written authority.
// Offenders will be liable for damages. All rights, including rights created
// by patent grant or registration of a utility model or design, are reserved.
////////////////////////////////////////////////////////////////////////////////
// History      : 08.06.2001   Igor Sarzi Sartori    Created


///////////// fuzzy header
#ifndef  __FUZZY_COLLECTION_H__
#define  __FUZZY_COLLECTION_H__

#include <stdlib.h>

class FuzzyCollection
{
private:
   int fuzzyFALSE;
   int fuzzyTRUE;
   int fuzzyUNDEF;

public:
   FuzzyCollection(): fuzzyFALSE(0), fuzzyTRUE(100), fuzzyUNDEF(fuzzyTRUE >> 1)  {}
   FuzzyCollection(int a, int b, int c){fuzzyFALSE = a; fuzzyTRUE = b; fuzzyUNDEF = c;}

   int Fuzzy(int lValue, int lStart, int lEnd);
   int FuzzyAND(int nFirst, int nSecond){return nFirst < nSecond ? nFirst : nSecond;}
   int FuzzyOR(int nFirst, int nSecond){ return nFirst > nSecond ? nFirst : nSecond;}
   int FuzzyHYPEROR(int nFirst, int nSecond) {return ( (nFirst + nSecond) >= fuzzyTRUE ) ? fuzzyTRUE : ( nFirst + nSecond);}
   int FuzzyNOT(int nFuzzy){ return nFuzzy < fuzzyTRUE ? (fuzzyTRUE - nFuzzy) : fuzzyFALSE;}
};

////////////////////
// Fuzzy :
//                 --------------------
//               /
//             /
// -----------
/*! Normalized a value between 0 and 100. Linear norm into the rage is used.
// Values that <= lStart are 0; values that are >= lEnd are 100
// \param lValue : value to be normalized
// \param lStart : start range
// \param lEnd   : end range
*/
inline int FuzzyCollection::Fuzzy(int lValue, int lStart, int lEnd)
{
   if(lValue <= lStart)
   {
      return(fuzzyFALSE);
   }
   else if(lValue >= lEnd)
   {
      return(fuzzyTRUE);
   }
   else if(lEnd == lStart)
   {
      return(fuzzyTRUE);
   }
   else
   {
      return((short)(((lValue - lStart) * fuzzyTRUE) / (lEnd - lStart)));
   }
}

#endif
//////// end fuzzy header

