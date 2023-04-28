#include <bits/stdc++.h>
using namespace std;

// Banker's Algorithm

// n -> number of process
// m -> number of resource

// Allocation --> Will add into Available if that certain process is taken.
// Max --> The number of resouces needed
// Availabe --> Resources[i] - Sum of Allocation[i]
// Need --> Max[i] - Allocation[i]

struct Array
{
    vector<int> resources;
    int age;
};

int n, m;

vector<Array> Allocation, Max, Need;
vector<int> Resource, Available, Sequence;
vector<bool> Finish;

int main()
{

    cout << "Number of Process : ";
    cin >> n;
    cout << endl;
    cout << "Number of Resource : ";
    cin >> m;
    cout << endl;

    Finish.resize(n + 2, false);
    Allocation.resize(n + 2);
    Max.resize(n + 2);
    Need.resize(n + 2);

    cout << "Enter the amount of resources: " << endl;

    for (int i = 0; i < m; i++)
    {
        cout << "Resource - " << i << " : ";
        int num;
        cin >> num;
        Resource.push_back(num);
    }

    cout << "Enter the amount of Allocation: " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Process - " << i << " : ";
        for (int j = 0; j < m; j++)
        {
            int num;
            cin >> num;
            Allocation[i].resources.push_back(num);
        }
    }

    cout << "Enter the amount of Max: " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Process - " << i << " : ";
        for (int j = 0; j < m; j++)
        {
            int num;
            cin >> num;
            Max[i].resources.push_back(num);
        }
    }

    // Figuring Out The Value Of Need For Each Process

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Need[i].resources.push_back(Max[i].resources[j] - Allocation[i].resources[j]);
        }
    }

    // Figuring Out The Value Of Available
    for(int j = 0; j < m; j++)
    {
        int sum = 0;
        for(int i = 0; i < n; i++)
        {
            sum += Allocation[i].resources[j];
        }
        Available.push_back(Resource[j]-sum);
    }

    bool flag = true;

    while (flag)
    {
        bool found = false;

        for (int index = 0; index < n; index++)
        {
            if (Finish[index])
            {
                continue;
            }
            bool current = true;
            for (int i = 0; i < m; i++)
            {
                if (Need[index].resources[i] > Available[i]) // The Process Can't Be Done
                {
                    current = false;
                }
            }
            if (current)
            {
                Finish[index] = true;
                found = true;
                Sequence.push_back(index);
                for (int i = 0; i < m; i++)
                {
                    Available[i] += Allocation[index].resources[i];
                }
            }
        }

        if (!found)
            flag = false;
    }

    if (Sequence.size() == n)
    {
        cout << "Safe sequence is: ";
        for (auto x : Sequence)
        {
            cout << x << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Safe Sequence Not Found " << endl;
    }

    return 0;
}

/*

5
3
10 5 7

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

*/
