#include <iostream>

#include <string>

#include <vector>

#include <cmath>

#include <ctime>

#include <stdlib.h>

#include <iomanip>

#include <cfloat>

using namespace std;



// vector<int> S;

void backtracking(const vector<vector<int>> &B, int curState, int L, vector<int> &S);



int main()

{

  int N, M, L;

  cin >> N >> M >> L;

  vector<double> P0;

  double pr;



  for (int i = 0; i < N; i++)

  {

    cin >> pr;

    pr = -(log2(pr));

    P0.push_back(pr);

  }

  // cout<<"this";



  vector<vector<double>> T;

  for (int i = 0; i < N; i++)

  {

    vector<double> temp;

    for (int j = 0; j < N; j++)

    {

      cin >> pr;

      pr = -(log2(pr));

      temp.push_back(pr);

    }

    T.push_back(temp);

  }



  vector<vector<double>> O; //observation matrix

  for (int i = 0; i < N; i++)

  {

    vector<double> temp;

    for (int j = 0; j < M; j++)

    {

      cin >> pr;

      pr = -(log2(pr));

      temp.push_back(pr);

    }

    O.push_back(temp);

  }



  vector<int> E; //sequence of observations, H=0 T=1

  E.push_back(0);

  int x;

  for (int i = 0; i < L; i++)

  {

    cin >> x;

    E.push_back(x);

  };



  vector<int> A; //actual seq of states

  for (int i = 0; i <= L; i++)

  {

    cin >> x;

    A.push_back(x);

  }

//---------

  //fill in probability and backtracking table P and B

  //because we do -lo2 we need to minimize values

  vector<vector<double>> P(N, vector<double>(L + 1, DBL_MAX));

  vector<vector<int>> B(N, vector<int>(L + 1, 0));

  //initialize first column base case

  for (int i = 0; i < N; i++)

  {

    P[i][0] = P0[i];

    B[i][0] = i;

  }



  //curent i previous

  vector<int> S;

  for (int j = 1; j <= L; j++)

  {

    for (int i = 0; i < N; i++)

    {

      double minVal = DBL_MAX;

      int fromState = 0;

      for (int prev = 0; prev < N; prev++)

      {

        double curP = P[prev][j - 1] + T[i][prev];

        if (curP < minVal)

        {

          minVal = curP;

          fromState = prev;

        }

      } //for prev

      int e = E[j];

      double curO = O[i][e];

      P[i][j] = minVal + curO;

      B[i][j] = fromState;

    }

    int curState = 0;

    double minVal = DBL_MAX;

    for (int i = 0; i < N; i++)

    {

      if (P[i][L] < minVal)

      {

        minVal = P[i][L];

        curState=i;

      }

    }

    backtracking(B, curState, L, S);

  }

  for (int i = 0; i < N; i++)

  {

    cout << std::fixed << std::setprecision(12) << P[i][L]<<" ";

  }

  cout << endl;

  for (int i = 0; i <= L; i++)

  {

    cout << S[i] << " ";

  }

  cout << endl;



  double accuracy = 0.0;

  int correct = 0;

  for (int i = 0; i <= L; i++)

  {

    if (A[i] ==  S[i])

    {

      correct++;

    }

  }

  accuracy += (0.0 + correct) / (L + 1.0);

  accuracy *= 100;

  cout << std::fixed << std::setprecision(2) << accuracy << endl;

  //

  return 0;

}



void backtracking(const vector<vector<int>> &B, int curState, int col, vector<int> &S)

{

  if (col == 0)

  {

    S.push_back(curState);

    return;

  }

  int prevState = B[curState][col];

  backtracking(B, prevState, col - 1, S);

  S.push_back(curState);

}