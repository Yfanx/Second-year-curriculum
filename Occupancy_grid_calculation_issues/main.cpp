#include <iostream>
#include <vector>

using namespace std;


// 深度优先搜索
void DFS(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited, int& size) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0 || visited[i][j]) {
        return;
    } // 越界或者不是1或者已经访问过了

    visited[i][j] = true;
    size++;

    // 检查上下左右相邻的方格
    DFS(grid, i - 1, j, visited, size);
    DFS(grid, i + 1, j, visited, size);
    DFS(grid, i, j - 1, visited, size);
    DFS(grid, i, j + 1, visited, size);
}

// 给定组中的某个方格，计算组的大小
int get_group_size(vector<vector<int>>& grid, int i, int j) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int size = 0;
    DFS(grid, i, j, visited, size);
    return size;
}

// 计算不同组的数量
int count_groups(vector<vector<int>>& grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false)); // 初始化为false，便于判断是否已经访问过
    int count = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                // 新的组开始
                count++;
                int size = 0;
                DFS(grid, i, j, visited, size);
            }
        }
    }

    return count;
}

// 列出所有的组
void list_all_groups(vector<vector<int>>& grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int a = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                // 新的组开始
                int size = 0;
                DFS(grid, i, j, visited, size);
                cout << "Group" << "[" << a++ << "] size: " << size << endl;
            }
        }
    }
}

int main() {
    // 生成一个N*N的网格
    cout << "请输入网格的行数：" << endl;
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n, 0));

    cout << "输入网格（1为有障碍，0为无障碍）：" << endl;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> grid[i][j];
        }
    }

    /*0 0 0 0 0 1
      0 1 1 0 0 1
      0 0 0 0 0 0
      0 1 0 1 0 0
      1 0 0 1 0 0
      0 0 0 1 1 0*/

    // 1) 给定组中的某个方格，计算组的大小
    cout <<"请输入组的起始方格的坐标：" << endl;
    int x, y;
    cin >> x >> y;

    int group_size = get_group_size(grid, x, y);
    printf("[%d, %d]所在的组的大小是： %d\n", x, y, group_size);

    // 2) 计算不同组的数量
    int num_groups = count_groups(grid);
    cout << "组的数量是： " << num_groups << endl;

    // 3) 列出所有的组
    list_all_groups(grid);

    return 0;
}
