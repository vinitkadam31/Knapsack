#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include <iterator>

using namespace std;

int w[20], p[20], bestset[20];

int maxprofit = 0;
int num = 0;
int n = 0;
int C = 0;

vector<string> split(const string &s, char delim);
int convertTwo(int a, int b);

int main(int argc, char* argv[])
{
    ifstream in(argv[1]);
    vector<string> input;
    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    char str[255];

    while(in)
    {
        in.getline(str, 255);  // delim defaults to '\n'
        if(in)
        {
            input.push_back(str);
        }
    }
    in.close();
    //cout<<endl;

    n = atoi(input[0].c_str());
    C = atoi(input[1].c_str());
    int B[15][C+2];
    int include[15][C+2];
    vector<string> v = split(input[2], ',');
    for(int i=0;i<(int)v.size();i++)
    {
        p[i+1] = atoi(v[i].c_str());
    }

    vector<string> v1 = split(input[3], ',');
    for(int i=0;i<(int)v1.size();i++)
    {
        w[i+1] = atoi(v1[i].c_str());
    }

    for (int i = 0; i<= C;i++)  // row 0 (empty knapsack)
    {
        B[0][i] = 0;
        include[0][i] = 0;
    }


    for (int k = 1; k<=n; k++)  // rows 1 to n
    {
        B[k][0] = 0;          // element in column 0 (no profit for w = 0)
        include[k][0] = 0;
        for (int i = 1; i<=C; i++)   // elements in columns 1 to W
        {
            if ((w[k] <= i) && (B[k-1][i - w[k]] + p[k] > B[k-1][i]))
            {
                /*include[k] = 1;
                if(B[k-1][i - w[k]] == 0)
                {
                    for(int t=k-1;t>0;t--)
                        include[t] = 0;
                }*/
                B[k][i] = B[k-1][i - w[k]] + p[k];
                if(B[k-1][i - w[k]] != 0)
                {
                    int temp = convertTwo(include[k-1][i - w[k]], k==10?0:k);
                    //cout<<include[k-1][i - w[k]] << "-"<<k<<"="<<temp<<endl;
                    include[k][i] = temp; //"," + NumberToString(k);
                }
                else
                    include[k][i] = (k==10?0:k);//NumberToString(k);
            }
            else
            {
                //include[k] = 1;
                B[k][i] = B[k-1][i];
                //if(include[k-1][i] != 0)
                    include[k][i] = include[k-1][i];
            }
        }

    }

    cout<<"Total Profit is "<<B[n][C]<<endl;
    //cout<<B[n][C]<<endl;
    //cout<<include[n][C]<<endl;

    vector<int> sd;
    int number = include[n][C];
    while (number > 0)
    {
        int digit = number%10;
        number /= 10;
        sd.push_back(digit);
    }
    int counter = 0;
    int solutionSize = sd.size();
    while (!sd.empty())
    {
        int digit = sd[sd.size()-1];
        sd.pop_back();
        //print digit
        bestset[counter++] = digit;
    }

    /*for (int i = 0; i < solutionSize; i++)
        cout << bestset[i]==0?10:bestset[i]; //the best solution*/

    //cout<<endl;

    int totalWeight = 0;
    for (int i = 0; i < solutionSize; i++)
    {
        totalWeight += w[bestset[i]==0?10:bestset[i]];
    }
    cout<<"Total Weight is "<<totalWeight<<endl;
    cout<<endl;
    counter = 1;
    for (int i = 0; i < solutionSize; i++)
    {
        cout<<"item "<<counter++<<": ";
        cout<<"profit-"<<p[bestset[i]==0?10:bestset[i]]<<", ";
        cout<<"weight-"<<w[bestset[i]==0?10:bestset[i]]<<endl;
        //cout<<p[bestset[i]==0?10:bestset[i]]<<", ";
    }
    /*cout<<endl;
    for (int i = 0; i < solutionSize; i++)
    {
        cout<<w[bestset[i]==0?10:bestset[i]]<<", ";
    }*/

    return 0;
}

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

int convertTwo(int a, int b)
{
    ostringstream oss;
    oss << a << b;
    istringstream iss(oss.str());
    int c;
    iss >> c;
    return c;
}
