#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrivalTime(n), cpuTime(n), waitingTime(n), turnAroundTime(n);
    vector<int> processID(n);

    cout << "Enter Arrival Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> arrivalTime[i];
        processID[i] = i + 1; 
    }

    cout << "Enter CPU Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> cpuTime[i];
    }

    vector<pair<pair<int, int>, int>> process;
    for (int i = 0; i < n; i++) {
        process.push_back({{arrivalTime[i], cpuTime[i]}, processID[i]});
    }

    sort(process.begin(), process.end(), [](const auto& a, const auto& b) {
        return a.first.first < b.first.first;
    });

    int sum = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (int i = 0; i < n; i++) {
        int arrival = process[i].first.first;
        int cpu = process[i].first.second;
        int id = process[i].second - 1;

        if (i == 0) {
            waitingTime[id] = 0;
            turnAroundTime[id] = cpu + waitingTime[id];
        } else {
            sum += process[i - 1].first.second;
            waitingTime[id] = sum - arrival;
            turnAroundTime[id] = cpu + waitingTime[id];
        }

        totalWaitingTime += waitingTime[id];
        totalTurnAroundTime += turnAroundTime[id];
    }

    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": "
             << "Arrival Time: " << arrivalTime[i]
             << ", Waiting Time: " << waitingTime[i]
             << ", Turnaround Time: " << turnAroundTime[i] << endl;
    }

  
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double avgTurnAroundTime = static_cast<double>(totalTurnAroundTime) / n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
