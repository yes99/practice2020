#include "CStudent.h"

CStudent::CStudent()
{
   nKoreanScore=0;
   nEnglishScore=0;
   nMathScore=0;
}

int CStudent::GetKoreanScore()
{
   return nKoreanScore;
}

int CStudent::GetEnglishScore()
{
   return nEnglishScore;
}

int CStudent::GetMathScore()
{
   return nMathScore;
}

int CStudent::GetTotal()
{
   return nKoreanScore+nEnglishScore+ nMathScore;
}

void CStudent::SetKoreanScore(int _nKoreanScore)
{
   nKoreanScore=_nKoreanScore;
}

void CStudent::SetEnglishScore(int _nEnglishScore)
{
   nEnglishScore=_nEnglishScore;
}

void CStudent::SetMathScore(int _nMathScore)
{
   nMathScore=_nMathScore;
}
