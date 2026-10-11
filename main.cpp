#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Structure to represent a position in the grid
struct Position {
    int row, col, dist;
    
    Position(int r, int c, int d) : row(r), col(c), dist(d) {}
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
    vector<pair<int, int>> umbrellaShops;
    
    // Read the grid and find start, home, and umbrella shops
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] == 3) {
                homeRow = i;
                homeCol = j;
            } else if (grid[i][j] == 4) {
                umbrellaShops.push_back({i, j});
            }
        }
    }
    
    // If no umbrella shop or no home, return -1 (though problem guarantees they exist)
    if (umbrellaShops.empty() || homeRow == -1 || homeCol == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    // BFS function to find shortest distance from start to target
    auto bfs = [&](int startR, int startC, int targetR, int targetC) -> int {
        if (startR == targetR && startC == targetC) return 0;
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<Position> q;
        q.push(Position(startR, startC, 0));
        visited[startR][startC] = true;
        
        while (!q.empty()) {
            Position curr = q.front();
            q.pop();
            
            // Check all four directions
            for (int i = 0; i < 4; i++) {
                int newRow = curr.row + dx[i];
                int newCol = curr.col + dy[i];
                
                // Check if the new position is valid
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && 
                    !visited[newRow][newCol] && grid[newRow][newCol] != 1) {
                    
                    if (newRow == targetR && newCol == targetC) {
                        return curr.dist + 1;
                    }
                    
                    visited[newRow][newCol] = true;
                    q.push(Position(newRow, newCol, curr.dist + 1));
                }
            }
        }
        
        return -1; // No path found
    };
    
    // Find shortest path from start to home via any umbrella shop
    int minDistance = INT_MAX;
    
    // Try each umbrella shop as an intermediate point
    for (auto& shop : umbrellaShops) {
        int shopRow = shop.first;
        int shopCol = shop.second;
        
        // Distance from start to umbrella shop
        int distToShop = bfs(startRow, startCol, shopRow, shopCol);
        if (distToShop == -1) continue; // No path to this shop
        
        // Distance from umbrella shop to home
        int distToHome = bfs(shopRow, shopCol, homeRow, homeCol);
        if (distToHome == -1) continue; // No path from this shop to home
        
        // Update minimum distance
        minDistance = min(minDistance, distToShop + distToHome);
    }
    
    if (minDistance == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << minDistance << endl;
    }
    
    return 0;
}