#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include <iterator>

using namespace std;

int w[20], p[20], include[20], bestset[20];
int maxprofit = 0;
int num = 0;
int n = 0;
int C = 0;

vector<string> split(const string &s, char delim);
int KWF4(int i, int weight, int profit);
bool promising(int i, int weight, int profit);
void knapsack(int i, int profit, int weight);

int main(int argc, char *argv[])
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

    //TODO: Check sorting
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if((p[j]/w[j])>(p[i]/w[i]))
            {
                int temp = p[j];
                p[j] = p[i];
                p[i] = temp;

                temp = w[j];
                w[j] = w[i];
                w[i] = temp;
            }
        }
    }

    num = 0;    //number of items considered
    maxprofit = 0;
    knapsack(0, 0, 0);
    cout<<"Total Profit is "<<maxprofit<<endl;
    /*for (int i = 1; i <= num; i++)
        cout << bestset[i]; //the best solution
*/
    int totalWeight = 0;
    for (int i = 1; i <= num; i++)
    {
        if(bestset[i] == 1)
            totalWeight+= w[i];
    }

    cout<<"Total Weight is "<<totalWeight<<endl;

    cout<<endl;
    int counter = 1;
    for (int i = 1; i <= num; i++)
    {
        if(bestset[i] == 1)
        {
            cout<<"item "<<counter++<<": ";
            cout<<"profit-"<<p[i]<<", ";
            cout<<"weight-"<<w[i]<<endl;
        }
    }
    /*cout<<endl;
    for (int i = 1; i <= num; i++)
    {
        if(bestset[i] == 1)
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

int KWF4(int i, int weight, int profit)
{
    int bound = profit;
    float x[n+1];

    for (int j = i; j<=n; j++)
       x[j] = 0;  //initialize variables to 0

    while (weight < C && i <= n)  {     //not “full” and more items
        if (weight + w[i] <= C)                //room for next item
        {
            x[i]=1;                                        //item i is added to knapsack
            weight = weight + w[i];
            bound = bound +p[i];
        }
       else
       {
            x[i]=(C - weight)/w[i];  //fraction of  i added to knapsack
            weight = C;
            bound = bound + p[i]*x[i];
       }
       i=i+1;                             // next item
    }

    return bound;
}

bool promising(int i, int weight, int profit)
{
    //Cannot get a solution by expanding node i
    if (weight >= C) return false;

    //Compute upper bound
    int bound = KWF4(i+1, weight, profit);

    return (bound > maxprofit);

}

void knapsack(int i, int profit, int weight)
{
    if ( weight <= C && profit > maxprofit ) {
   // save better solution
        maxprofit = profit;
        num = i; //bestset = include;
        for (int j = 1; j<=n; j++) {
            bestset[j] = include[j];
        }
    }
    if (promising(i, weight, profit)) {
       include[i + 1] = 1;
       knapsack(i+1, profit + p[i+1], weight + w[i+1]);
       include[i+1] = 0;
       knapsack(i+1,profit,weight);
    }

}

