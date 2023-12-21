#include <iostream>
using namespace std;

char b[3][3]; char AI = 'X', HU = 'O';

bool check_win(char p) {
    for (int i = 0; i < 3; i++) if ((b[i][0] == p && b[i][1] == p && b[i][2] == p) || (b[0][i] == p && b[1][i] == p && b[2][i] == p)) return true;
    return (b[0][0] == p && b[1][1] == p && b[2][2] == p) || (b[0][2] == p && b[1][1] == p && b[2][0] == p);
}

bool check_draw() { for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (b[i][j] == ' ') return false; return true; }

void best_move(int &x, int &y) {
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (b[i][j] == ' ') { b[i][j] = AI; if (check_win(AI)) { x = i; y = j; b[i][j] = ' '; return; } b[i][j] = ' '; }
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (b[i][j] == ' ') { b[i][j] = HU; if (check_win(HU)) { x = i; y = j; b[i][j] = ' '; return; } b[i][j] = ' '; }
    if (b[1][1] == ' ') { x = 1; y = 1; return; }
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        int cx = corners[i][0], cy = corners[i][1];
        if (b[cx][cy] == ' ') { x = cx; y = cy; return; }
    }
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (b[i][j] == ' ') { x = i; y = j; return; }
}

int main() {
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) b[i][j] = ' ';
    while (true) {
        for (int i = 0; i < 3; i++, cout << endl) for (int j = 0; j < 3; j++) cout << b[i][j] << ' ';
        cout << "Enter your move (row 1-3, column 1-3): "; int x, y;
        if (!(cin >> x >> y)) {
            cout << "Invalid input! Please enter numbers only.\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }
        x--; y--;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && b[x][y] == ' ') b[x][y] = HU;
        else { cout << "Invalid move! Enter row and column numbers between 1 and 3.\n"; continue; }
        if (check_win(HU)) { cout << "You win!\n"; break; } if (check_draw()) { cout << "Draw!\n"; break; }
        best_move(x, y); b[x][y] = AI; cout << "AI placed at row " << x+1 << " column " << y+1 << endl;
        if (check_win(AI)) { cout << "AI wins!\n"; break; } if (check_draw()) { cout << "Draw!\n"; break; }
    }
    return 0;
}

