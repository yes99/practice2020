#pragma once

#define MAX_STUDENT_CNT 10

class CStudentManager {
private:
   int nCnt;
   CStudent pStudent[MAX_STUDENT_CNT];
public:
   CStudentManager();
   int GetCount();

   CStudent Retrieve(int nIndex);
   void Add(CStudent& _pStudent);
   bool Delete(int nIndex);
   bool Update(int nIndex, CStudent& _pStudent);
};
