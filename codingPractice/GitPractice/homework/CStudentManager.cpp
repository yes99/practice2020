#include "CStudent.h"
#include "CStudentManager.h"

CStudentManager:: CStudentManager()
{
   nCnt=0;
}

int CStudentManager::GetCount()
{
   return nCnt;
}

CStudent CStudentManager::Retrieve(int nIndex)
{
   return pStudent[nIndex - 1];
}

void CStudentManager::Add(CStudent& _pStudent)
{
   pStudent[nCnt]=_pStudent;
   nCnt++;
}

bool CStudentManager::Delete(int nIndex)
{
   if (nIndex<1||nIndex>nCnt)
   {
      return false;
   }

   for (int i=nIndex;i<nCnt;i++)
   {
      pStudent[i-1]=pStudent[i];
   }
   nCnt--;
   return true;
}

bool CStudentManager::Update(int nIndex, CStudent& _pStudent)
{
   if (nIndex<1||nIndex>nCnt)
   {
      return false;
   }
   pStudent[nIndex-1]=_pStudent;
   return true;
}