#include <iostream>
#include <queue>
#include <functional>

using namespace std;

class QueueItem {
    public:

        int idx;
        int dest;
    
        QueueItem(int i, int d) : idx(i), dest(d) {}        
};

bool operator<(const QueueItem& q1, const QueueItem& q2) {
    return q1.dest > q2.dest;
}

bool operator>(const QueueItem& q1, const QueueItem& q2) {
    return q1.dest < q2.dest;
}

int main(void) {
    int n;
    int *t_arr, *p_arr, *sum_arr;
    priority_queue<QueueItem> pq;

    cin >> n;

    t_arr = new int[n];
    p_arr = new int[n];
    sum_arr = new int[n];

    for(int i=0;i<n;i++) {
        sum_arr[i] = 0;
        cin >> t_arr[i] >> p_arr[i];
    }

    for(int i=0;i<n;i++) {
        if(i > 0) {
            sum_arr[i] = sum_arr[i - 1];            
        }        

        // cout << i << endl;

        if(i + t_arr[i] - 1 < n) {
            // q_arr[i + t_arr[i] - 1].push(i);
            pq.push(QueueItem(i, i + t_arr[i] - 1));
        }        

        while(!pq.empty()) {
            int prev_sum;
            QueueItem q = pq.top();
            // cout << "q pop: " << q.dest << " p[idx]: " << p_arr[q.idx] << endl;
            if(q.dest != i) {
                break;
            } else {
                pq.pop();
            }

            prev_sum = q.idx <= 0 ? 0 : sum_arr[q.idx - 1];

            

            sum_arr[i] = max(prev_sum + p_arr[q.idx], sum_arr[i]);
        }

        // for(int j=0;j<n;j++) {
        //     cout << sum_arr[j] << ' ' ;
        // }
        // cout << endl;
    }

    cout << sum_arr[n - 1];

    delete [] t_arr;
    delete [] p_arr;
    delete [] sum_arr;

    return 0;
}