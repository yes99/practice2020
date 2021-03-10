#include <iostream>

#include "CStudent.h"
#include "CStudentManager.h"

using namespace std;

void PrintMenu();
void Retrieve();
void Add();
void Delete();
void Update();
void Quit();
void PrintScores(int nIndex);

CStudentManager mgr;

int main()
{
   int nMenu;

   while (true)
   {
      PrintMenu();
      cin>>nMenu;

      switch (nMenu)
      {
      case 1:
         Retrieve();
         break;
      case 2: 
         Add();
         break;
      case 3:
         Delete();
         break;
      case 4:
         Update();
         break;
      case 5:
         Quit();
         return 0;
      }
   }
   
   return 0;
}

void PrintMenu()
{
   cout<<"*********************"<<endl;
   cout<<"1. Retrieve"<<endl;
   cout<<"2. Add"<<endl;
   cout<<"3. Delete"<<endl;
   cout<<"4. Update"<<endl;
   cout<<"5. Quit"<<endl;
   cout<<"*********************"<<endl;
   cout<<"> ";
}

void Retrieve()
{
   if (mgr.GetCount()==0)
   {
      cout<<"There is no data."<<endl;
      return;
   }

   int nMin=300;
   int nMax=0;
   int nKoreanSum=0;
   int nEnglishSum=0;
   int nMathSum=0;

   for(int i=1;i<=mgr.GetCount();i++)
   {
      PrintScores(i);

      if (nMin>=mgr.Retrieve(i).GetTotal())
         nMin=mgr.Retrieve(i).GetTotal();

      if (nMax<=mgr.Retrieve(i).GetTotal())
         nMax=mgr.Retrieve(i).GetTotal();

      nKoreanSum+=mgr.Retrieve(i).GetKoreanScore();
      nEnglishSum+=mgr.Retrieve(i).GetEnglishScore();
      nMathSum+=mgr.Retrieve(i).GetMathScore();
   }

   cout<<"Sum: Korean "<<nKoreanSum<<" points"<<" Math "<<nMathSum<<" points"
     <<" English "<<nEnglishSum<<" points"<<endl;
   cout<<"Average: Korean "<<nKoreanSum/mgr.GetCount()<<" points"
     <<" Math "<<nMathSum/mgr.GetCount()<<" points"
     <<" English "<<nEnglishSum/mgr.GetCount()<<" points"<<endl;

   cout<<"#1/";
   for (int i=1;i<=mgr.GetCount();i++)
      if (nMax==mgr.Retrieve(i).GetTotal())
         PrintScores(i);

   cout<<"#Last/";
   for (int i=1;i<=mgr.GetCount();i++)
      if (nMin==mgr.Retrieve(i).GetTotal())
         PrintScores(i);
}

void Add()
{
   if (mgr.GetCount()==MAX_STUDENT_CNT)
   {
      cout<<"There are the maximum number of data."<<endl;
      return;
   }

   CStudent student;
   int nKoreanScore=0;
   while (true)
   {
      cout<<"Korean Score?";
      cin>>nKoreanScore;
      if (nKoreanScore>=0&&nKoreanScore<=100)
      {
         student.SetKoreanScore(nKoreanScore);
         break;
      }
      else
         cout<<"The entered value is not from 0 to 100."<<endl;
   }

   int nMathScore=0;
   while (true)
   {
      cout<<"Math Score?";
      cin>>nMathScore;
      if (nMathScore>=0&&nMathScore<=100)
      {
         student.SetMathScore(nMathScore);
         break;
      }
      else
         cout<<"The entered value is not from 0 to 100."<<endl;
   }

   int nEnglishScore=0;
   while (true)
   {
      cout<<"English Score?";
      cin>>nEnglishScore;
      if (nEnglishScore>=0&&nEnglishScore<=100)
      {
         student.SetEnglishScore(nEnglishScore);
         break;
      }
      else
         cout<<"The entered value is not from 0 to 100."<<endl;
   }

   mgr.Add(student);
   PrintScores(mgr.GetCount());
   cout<<"Added!"<<endl;
}

void Delete()
{
   int nIndex;
   cout<<"Delete No?>";
   cin>>nIndex;

   if (nIndex<1||nIndex>mgr.GetCount())
   {
      cout<<"There is no data."<<endl;
      return;
   }

   mgr.Delete(nIndex);

   cout<<"Deleted!"<<endl;
}

void Update()
{
   int nIndex;
   cout<<"Update No?>";
   cin>>nIndex;
   if (nIndex<1||nIndex>mgr.GetCount())
   {
      cout<<"There is no data."<<endl;
      return;
   }

   CStudent student;

   int nKoreanScore=0;
   while (true)
   {
      cout<<"Korean Score?";
      cin>>nKoreanScore;
      if (nKoreanScore>=0&&nKoreanScore<=100)
      {
         student.SetKoreanScore(nKoreanScore);
         break;
      }
      else
         cout<<"The entered value is not fot From 0 to 100."<<endl;
   }

   int nMathScore=0;
   while (true)
   {
      cout<<"Math Score?";
      cin>>nMathScore;
      if (nMathScore>=0&&nMathScore<=100)
      {
         student.SetMathScore(nMathScore);
         break;
      }
      else
         cout<<"The entered value is not fot From 0 to 100."<<endl;
   }

   int nEnglishScore=0;
   while (true)
   {
      cout<<"English Score?";
      cin>>nEnglishScore;
      if (nEnglishScore>=0&&nEnglishScore<=100)
      {
         student.SetEnglishScore(nEnglishScore);
         break;
      }
      else
         cout<<"The entered value is not fot From 0 to 100."<<endl;
   }

   mgr.Update(nIndex, student);
   PrintScores(nIndex);   
   cout<<"Updated!"<<endl;
}

void Quit()
{
   cout<<"Bye!"<<endl;
}

void PrintScores(int nIndex)
{
   cout<<nIndex<<"."<<" Korean:"<<mgr.Retrieve(nIndex).GetKoreanScore()
     <<" Math:"<<mgr.Retrieve(nIndex).GetMathScore()
     <<" English:"<<mgr.Retrieve(nIndex).GetEnglishScore()<<endl;
}