/* �÷����㷨count()��count_if()����ʾ�� */

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class IsFull 
{
public:
    bool operator() (int & score) 
    {
        return score==100;
    }       
};

int main (void) 
{
  vector <int> Scores;
  
  //����ɼ���
  Scores.push_back(67);  Scores.push_back(89);
  Scores.push_back(100); Scores.push_back(86);
  Scores.push_back(56);  Scores.push_back(100);
  Scores.push_back(99);  Scores.push_back(74);

  int NFullScoresV;     
  NFullScoresV = count (Scores.begin(), Scores.end(), 100);
  cout<<"��count()������"<<endl;
  cout << "There were " << NFullScoresV << " fullscores!" << endl;

  int NFullScoresF;     
  NFullScoresF = count_if (Scores.begin(), Scores.end(), IsFull());
  cout<<"��count_if()������"<<endl;
  cout << "There were " << NFullScoresF << " fullscores!" << endl;
  
  system("pause");
  return 0;
}
