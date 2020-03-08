#pragma once

class CStudent
{
private:
   int nKoreanScore;
   int nEnglishScore;
   int nMathScore;

public:
   CStudent();
   int GetKoreanScore();
   int GetEnglishScore();
   int GetMathScore();
   int GetTotal();

   void SetKoreanScore(int _nKoreanScore);
   void SetEnglishScore(int _nEnglishScore);
   void SetMathScore(int _nMathScore);

};