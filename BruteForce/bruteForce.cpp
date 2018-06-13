#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include <iterator>

using namespace std;

vector<string> split(const string &s, char delim);
int GetPowerOf2(int n);

int main(int argc, char *argv[])
{
    int w[20], p[20];
    ifstream in(argv[1]);//
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

    int n = atoi(input[0].c_str());
    int C = atoi(input[1].c_str());
    unsigned long int include[15][C+2];
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

    int currentWeight, currentProfit;
    int bestProfit = 0, bestWeight = 0;
    int j =0;
    int A[n+1], bestchoice[n+1];

    for(int i=0; i<=n; i++)
        A[i] = 0;

    for (int i=1;i<=GetPowerOf2(n);i++)
    {
        j=1;
        currentProfit = 0;
        currentWeight = 0;
        while(A[j] != 0 && j<=n)
            A[j++] = 0;
        A[j] = 1;
        for(int k= 1;k<=n; k++)
        {
            if(A[k]==1)
            {
                currentProfit += p[k];
                currentWeight += w[k];
            }
        }
        //cout<<endl;
        //cout<<"current profit: "<<currentProfit<<", "<<"current weight: "<<currentWeight;
        if(currentProfit > bestProfit && currentWeight <= C)
        {
            bestProfit = currentProfit;
            bestWeight = currentWeight;
            for(int i=1; i<=n; i++)
                bestchoice[i] = A[i];
        }
        /*for(int i=1; i<=n; i++)
        {
            cout<<A[i];
            //bestchoice[i] = A[i];
        }

        cout<<endl;
*/
    }
    //cout<<endl;
    int maxprofit = 0;
    int totalWeight = 0;
    for (int i = 1; i <= n; i++)
    {
        if(bestchoice[i] == 1)
        {
            maxprofit += p[i];
            totalWeight +=w[i];
        }

    }
    cout<<"Total Profit is "<<maxprofit<<endl;
    cout<<"Total Weight is "<<totalWeight<<endl;
    /*cout<<"best solution"<<endl;
    for(int i=1; i<=n; i++)
    {
        cout<<bestchoice[i];
    }*/

    cout<<endl;
    int counter = 1;
    for (int i = 1; i <= n; i++)
    {
        if(bestchoice[i] == 1)
        {
            cout<<"item "<<counter++<<": ";
            cout<<"profit-"<<p[i]<<", ";
            cout<<"weight-"<<w[i]<<endl;
        }

    }
    /*cout<<endl;
    for (int i = 1; i <= n; i++)
    {
        if(bestchoice[i] == 1)
            cout<<w[i]<<", ";
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

//return power of 2
int GetPowerOf2(int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return 2;
    else
    {
        int result = 1;;
        for(int i=0;i<n;i++)
            result = result * 2;
        return result;
    }
}