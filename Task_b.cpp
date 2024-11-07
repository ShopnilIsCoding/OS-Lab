#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrivalTime(n), cpuTime(n), waitingTime(n), turnAroundTime(n);
    vector<int> processID(n);

    cout << "Enter the CPU times:\n";
    for (int i = 0; i < n; i++) {
        cin >> cpuTime[i];
        processID[i] = i + 1;
    }

    cout << "Enter the arrival times:\n";
    for (int i = 0; i < n; i++) {
        cin >> arrivalTime[i];
    }

    vector<pair<pair<int, int>, int>> processes;
    for (int i = 0; i < n; i++) {
        processes.push_back({{arrivalTime[i], cpuTime[i]}, processID[i]});
    }

    sort(processes.begin(), processes.end(), [](const auto& a, const auto& b) {
        if (a.first.first == b.first.first) {
            return a.first.second < b.first.second;
        }
        return a.first.first < b.first.first;
    });

    int timer = 0;
    vector<bool> isProcessed(n, false);

    for (int completed = 0; completed < n; completed++) {
        int idx = -1;
        int minCPUTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!isProcessed[i] && processes[i].first.first <= timer && processes[i].first.second < minCPUTime) {
                minCPUTime = processes[i].first.second;
                idx = i;
            }
        }

        if (idx != -1) {
            isProcessed[idx] = true;
            int arrival = processes[idx].first.first;
            int cpu = processes[idx].first.second;
            int id = processes[idx].second - 1;

            waitingTime[id] = timer - arrival;
            turnAroundTime[id] = waitingTime[id] + cpu;
            timer += cpu;
        }
    }

    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": "
             << "Waiting Time: " << waitingTime[i]
             << ", Turnaround Time: " << turnAroundTime[i] << endl;
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    double avgWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double avgTurnAroundTime = static_cast<double>(totalTurnAroundTime) / n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
