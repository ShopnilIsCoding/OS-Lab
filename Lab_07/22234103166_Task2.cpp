#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << ":\n";
        for (int j = 0; j < m; j++) {
            cout << "Maximum value for resource " << j + 1 << ":";
            cin >> max[i][j];
        }
        for (int j = 0; j < m; j++) {
            cout << "Allocated from resource " << j + 1 << ":";
            cin >> alloc[i][j];
        }
    }

    for (int j = 0; j < m; j++) {
        cout << "Enter total value of resource " << j + 1 << ":";
        cin >> available[j];
    }

  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

   
    vector<bool> finish(n, false);  
    vector<int> work = available;   
    vector<int> safeSequence;       

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                   
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            cout << "\nThe system is not in a safe state." << endl;
            return 0;
        }
    }

   
    cout << "\nThe system is in a safe state and ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i] + 1 << " ";
    }
    cout <<"is the safe sequence"<< endl;

    return 0;
}
