//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

class Matrix {
  public:
    template <class T>
    static void input(vector<vector<T>> &A, int n, int m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d ", &A[i][j]);
            }
        }
    }

    template <class T>
    static void print(vector<vector<T>> &A) {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }
};


// } Driver Code Ends

class Solution {
  private:
    void dfs(vector<vector<int>> &adj, int i, vector<int> &isVisited, vector<int> &temp){
        temp.push_back(i);
        isVisited[i]++;
        for(auto &it : adj[i]){
            if(isVisited[it] == 0)
                dfs(adj, it, isVisited, temp);
        }
        return;
    }
  public:
    int findNumberOfGoodComponent(int e, int v, vector<vector<int>> &edges) {
        //Making adjacency matrix
        vector<vector<int>> adj(v + 1, vector<int> {});
        for(auto &e: edges){
            int a = e[0];
            int b = e[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        //This vector will basically store , whether a vertex has been visited in some component
        //or not
        //dfs krenge, humara dfs repetive naa ho uske liye
        int numberOfGoodComponents = 0;
        vector<int> isVisited (v + 1, 0);
        for(int i = 1; i <= v; i++){
            if(isVisited[i] == 0){
                vector<int> temp;
                dfs(adj, i, isVisited, temp);
                //temp will contain all the vertices in the component
                //good component ki condition kya thee?
                //agar har ek vertex humare component har dusri vertex se connected hai toh , component good hoga, nhi toh nhi hoga
                //isko pta lagane ka simple tareeka, suppose mere iss wale component mein 5 vertices thee. Toh iska matlab har vertex ki degree jo hogi woh 4 hogi (5 -1)
                // degree check krke adj[v].size() se 
                bool flag = true;
                for(auto &it : temp){
                    if(adj[it].size() != temp.size() - 1){
                        flag = false;
                        break;
                    }
                }
                if (flag){
                    numberOfGoodComponents++;
                }
            }
        }
        return numberOfGoodComponents;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    scanf("%d ", &t);
    while (t--) {

        int e;
        scanf("%d", &e);

        int v;
        scanf("%d", &v);

        vector<vector<int>> edges(e, vector<int>(2));
        Matrix::input(edges, e, 2);

        Solution obj;
        int res = obj.findNumberOfGoodComponent(e, v, edges);

        cout << res << endl;
    }
}

// } Driver Code Ends