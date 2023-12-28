#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited, int& size) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0 || visited[i][j]) {
        return;
    } // 越界或者不是1或者已经访问过了

    visited[i][j] = true;
    size++;

    // 检查上下左右相邻的方格
    dfs(grid, i - 1, j, visited, size);
    dfs(grid, i + 1, j, visited, size);
    dfs(grid, i, j - 1, visited, size);
    dfs(grid, i, j + 1, visited, size);
} // DFS 深度优先搜索

int get_group_size(vector<vector<int>>& grid, int i, int j) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int size = 0;
    dfs(grid, i, j, visited, size);
    return size;
}

int count_groups(vector<vector<int>>& grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int count = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                // 新的组开始
                count++;
                int size = 0;
                dfs(grid, i, j, visited, size);
            }
        }
    }

    return count;
}

void list_all_groups(vector<vector<int>>& grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                // 新的组开始
                int size = 0;
                dfs(grid, i, j, visited, size);
                cout << "Group size: " << size << endl;
            }
        }
    }
}

int main() {
    // 示例网格
    vector<vector<int>> grid = {
            {0, 0, 0, 0, 0, 1},
            {0, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0}
    };

    // 1) 给定组中的某个方格，计算组的大小
    int group_size = get_group_size(grid, 0, 0);
    cout << "Group size: " << group_size << endl;

    // 2) 计算不同组的数量
    int num_groups = count_groups(grid);
    cout << "Number of groups: " << num_groups << endl;

    // 3) 列出所有的组
    list_all_groups(grid);

    return 0;
}
