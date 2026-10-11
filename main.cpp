#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Structure to represent a state in the grid
// Includes position and whether umbrella has been collected
struct State {
    int row, col, dist, hasUmbrella;
    
    State(int r, int c, int d, int u) : row(r), col(c), dist(d), hasUmbrella(u) {}
};

// Directions for moving up, down, left, right
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    int startRow = -1, startCol = -1;
    int homeRow = -1, homeCol = -1;
    
    // Read the grid and find start and home positions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] == 3) {
                homeRow = i;
                homeCol = j;
            }
        }
    }
    
    // Use BFS with state (row, col, hasUmbrella)
    // visited[row][col][hasUmbrella] = whether this state has been visited
    vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(2, false)));
    queue<State> q;
    
    // Start from the initial position without umbrella
    q.push(State(startRow, startCol, 0, 0));
    visited[startRow][startCol][0] = true;
    
    int minDistance = -1;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        // If we reached home with umbrella, we found a valid path
        if (curr.row == homeRow && curr.col == homeCol && curr.hasUmbrella == 1) {
            minDistance = curr.dist;
            break;
        }
        
        // Check all four directions
        for (int i = 0; i < 4; i++) {
            int newRow = curr.row + dx[i];
            int newCol = curr.col + dy[i];
            
            // Check if the new position is valid
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && grid[newRow][newCol] != 1) {
                int newHasUmbrella = curr.hasUmbrella;
                
                // If we are at an umbrella shop, we can collect the umbrella
                if (grid[newRow][newCol] == 4) {
                    newHasUmbrella = 1;
                }
                
                // If this state hasn't been visited, add it to the queue
                if (!visited[newRow][newCol][newHasUmbrella]) {
                    visited[newRow][newCol][newHasUmbrella] = true;
                    q.push(State(newRow, newCol, curr.dist + 1, newHasUmbrella));
                }
            }
        }
    }
    
    cout << minDistance << endl;
    
    return 0;
}