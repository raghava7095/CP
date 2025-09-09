#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool isSafe(int row, int col, vector<string>&board) {
    for (int i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;
    for (int i = row, j = col; j >= 0 && i < 8; i++, j--)
        if (board[i][j] == 'Q')
            return false;
    return true;
}
void solveNQUtil(int col, vector<string>&board, int &res) {
    if (col >= 8) {
        res++;
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (board[i][col] == '.' && isSafe(i, col, board)) {
            board[i][col] = 'Q';
            solveNQUtil(col + 1, board, res);
            board[i][col] = '.';
        }
    }
}
int solveNQ(vector<string>&board) {
    int res = 0;
    solveNQUtil(0, board, res);
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string>board(8);
    for(int i=0;i<8;i++) cin>>board[i];
    cout<<solveNQ(board)<<endl;
    return 0;
}