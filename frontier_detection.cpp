#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <functional>


bool isFrontier(
    const std::vector<std::vector<int>>& grid,
    int row,
    int col)
{
    // Check if the current cell is free
    if (grid[row][col] !=0) {
        return false;
    }
    // Define the four neighboring directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < 4; i++) {
        int newRow =  row + dr[i];
        int newCol = col + dc[i];
        printf("Checking neighbor at (%d, %d)\n", newRow, newCol);
    
      if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
          printf("Valid neighbor at (%d, %d) with value %d\n", newRow, newCol, grid[newRow][newCol]);
              if (grid[newRow][newCol] == -1) {
                 return true;
                }
        }

    }
    return false;
}

bool isReachable(
    const std::vector<std::vector<int>>& grid,
    std::pair<int, int> start,
    std::pair<int, int> goal)
{
    std::queue<std::pair<int, int>> q;

    int rows = grid.size();
    if (rows == 0) return false;

    int cols = grid[0].size();
    if (cols == 0) return false;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Check whether start and goal are inside the grid
    if (start.first < 0 || start.first >= rows || start.second < 0 || start.second >= cols || goal.first < 0 || goal.first >= rows || goal.second < 0 || goal.second >= cols) {
        return false;
        
    }
    // Check whether both cells are free
    if (grid[start.first][start.second] != 0 || grid[goal.first][goal.second] != 0) {
        return false;
    }

    q.push(start);
    visited[start.first][start.second] = true;
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        // Check whether we have reached the goal
        if (current == goal) {
            return true;
        }
        // Define the four neighboring directions
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int newRow = current.first + dr[i];
            int newCol = current.second + dc[i];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                // Check whether this cell is free and unvisited
                if (!visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
    }
    return false;
}

int shortestPathDistance(
    const std::vector<std::vector<int>>& grid,
    std::pair<int, int> start,
    std::pair<int, int> goal)
{
    int rows = grid.size();
    if (rows == 0) return -1;

    int cols = grid[0].size();
    if (cols == 0) return -1;

    // Check start and goal boundaries
    if (start.first < 0 || start.first >= rows ||
        start.second < 0 || start.second >= cols ||
        goal.first < 0 || goal.first >= rows ||
        goal.second < 0 || goal.second >= cols) {
        return -1;
    }

    // Check that both cells are free
    if (grid[start.first][start.second] != 0 ||
        grid[goal.first][goal.second] != 0) {
        return -1;
    }

    std::queue<std::pair<int, int>> q;

    std::vector<std::vector<int>> distance(
        rows, std::vector<int>(cols, -1)
    );

    std::vector<std::vector<std::pair<int, int>>> parent(
        rows,
        std::vector<std::pair<int, int>>(cols, {-1, -1})
    );

    q.push(start);
    distance[start.first][start.second] = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current == goal) {
            std::vector<std::pair<int, int>> path;
            std::pair<int, int> cell = goal;

            while (cell != start) {
                path.push_back(cell);
                cell = parent[cell.first][cell.second];
            }

            path.push_back(start);
            std::reverse(path.begin(), path.end());
            std::cout << "Path: ";

            for (const auto& point : path) {
                std::cout << "(" << point.first << ", "
                << point.second << ") ";
            }
            std::cout << "\n";

            return distance[current.first][current.second];
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newRow = current.first + dr[i];
            int newCol = current.second + dc[i];

            if (newRow >= 0 && newRow < rows &&
                newCol >= 0 && newCol < cols) {

                if (grid[newRow][newCol] == 0 &&
                    distance[newRow][newCol] == -1) {

                    distance[newRow][newCol] =
                        distance[current.first][current.second] + 1;

                    parent[newRow][newCol] = current;

                    q.push({newRow, newCol});
                }
            }
        }
    }

    return -1;
}    

std::vector<std::pair<int, int>> shortestPath(
    const std::vector<std::vector<int>>& grid,
    std::pair<int, int> start,
    std::pair<int, int> goal)
{
    int rows = grid.size();

    if (rows == 0) {
        return {};
    }
    int cols = grid[0].size();
    if (cols == 0) {
        return {};
    }
    // Validate start position
    if (start.first < 0 || start.first >= rows ||
        start.second < 0 || start.second >= cols) {
        return {};
    }

    // Validate goal position
    if (goal.first < 0 || goal.first >= rows ||
        goal.second < 0 || goal.second >= cols) {
        return {};
    }

    // Check whether both cells are free
    if (grid[start.first][start.second] != 0 ||
        grid[goal.first][goal.second] != 0) {
        return {};
    }
    // Create the BFS queue
    std::queue<std::pair<int, int>> q;

    // Add the starting position
    q.push(start);

    // Create the parent matrix
    std::vector<std::vector<std::pair<int, int>>> parent(
        rows,
        std::vector<std::pair<int, int>>(cols, {-1, -1})
    );
    // Track visited cells
    std::vector<std::vector<bool>> visited(
        rows, std::vector<bool>(cols, false)
    );
    visited[start.first][start.second] = true;
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current == goal) {
            break;
        }
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int newRow = current.first + dr[i];
            int newCol = current.second + dc[i];
            if (newRow >= 0 && newRow < rows &&
                newCol >= 0 && newCol < cols) {

                if (grid[newRow][newCol] == 0 &&
                    !visited[newRow][newCol]) {

                    visited[newRow][newCol] = true;
                    parent[newRow][newCol] = current;
                    q.push({newRow, newCol});
                }
            }
        }
        
    }
    if (!visited[goal.first][goal.second]) {
        return {};
    }
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> cell = goal;
    while (cell != start) {
        path.push_back(cell);
        cell = parent[cell.first][cell.second];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;

    
}

std::vector<std::pair<int, int>> dijkstraPath(
    const std::vector<std::vector<int>>& grid,
    std::pair<int, int> start,
    std::pair<int, int> goal)
{
    int rows = grid.size();

    if (rows == 0) {
        return {};
    }

    int cols = grid[0].size();

    if (cols == 0) {
        return {};
    }
    if (start.first < 0 || start.first >= rows) {
        return {};
    }

    if (start.second < 0 || start.second >= cols) {
        return {};
    }
    if (goal.first < 0 || goal.first >= rows) {
        return {};
    }

    if (goal.second < 0 || goal.second >= cols) {
        return {};
    }
    if (grid[start.first][start.second] != 0) {
        return {};
    }
    if (grid[goal.first][goal.second] != 0) {
        return {};
    }
    std::vector<std::vector<double>> dist(
    rows,
        std::vector<double>(
            cols,
            std::numeric_limits<double>::infinity()
        )
    );
    dist[start.first][start.second] = 0.0;
    using Node = std::pair<double, std::pair<int, int>>;

    std::priority_queue<
        Node,
        std::vector<Node>,
        std::greater<Node>
    > pq;
    pq.push({0.0, start});
    // Create the parent matrix
    std::vector<std::vector<std::pair<int, int>>> parent(
        rows,
        std::vector<std::pair<int, int>>(cols, {-1, -1})
    );

    // We'll implement Dijkstra here
    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        double currentDistance = current.first;
        int row = current.second.first;
        int col = current.second.second;
        if (currentDistance > dist[row][col]) {
            continue;
        }
        if (row == goal.first && col == goal.second) {
            break;
        }
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            // We'll validate these coordinates next.
            if (newRow >= 0 && newRow < rows && newCol >=0 && newCol < cols) {
                if (grid[newRow][newCol] == 0) {
                    double newDistance = currentDistance + 1.0;
                    if (newDistance < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newDistance;
                        parent[newRow][newCol] = {row, col};
                        pq.push({newDistance, {newRow, newCol}});
                    }
                }
            }
        }
    }
    // STAGE 2: Reconstruct the shortest path
    // First check whether the goal was reachable
    if (dist[goal.first][goal.second] ==
        std::numeric_limits<double>::infinity()) {
        return {};
    }
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> cell = goal;
    while (cell != start) {
        path.push_back(cell);
        cell = parent[cell.first][cell.second];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

void updateMap(
    std::vector<std::vector<int>>& grid,
    const std::vector<std::vector<int>>& groundTruth,
    std::pair<int, int> robotPosition)
{
    int rows = grid.size();
    int cols = grid[0].size();

    int row = robotPosition.first;
    int col = robotPosition.second;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int newRow = row + dr[i];
        int newCol = col + dc[i];
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
            grid[newRow][newCol] = groundTruth[newRow][newCol];
        }
    }
}

void printMap(const std::vector<std::vector<int>>& grid)
{
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
}

int main()
{
    const std::vector<std::vector<int>> groundTruth = {
    {100, 100, 100, 100, 100, 100, 100},
    {100,   0,   0, 100,   0,   0, 100},
    {100,   0,   0, 100,   0,   0, 100},
    {100,   0,   0,   0,   0,   0, 100}
    };

    int rows = groundTruth.size();
    int cols = groundTruth[0].size();
    std::vector<std::vector<int>> grid(
        rows, std::vector<int>(cols, -1)
    );
    std::pair<int, int> robotPosition = {1, 1};
    // Mark the robot's initial position as free in the grid
    grid[robotPosition.first][robotPosition.second] = 0;
    // Perform initial sensor observation
    updateMap(grid, groundTruth, robotPosition);

    bool explorationComplete = false;
    while (!explorationComplete) {
        std::vector<std::pair<int, int>> frontiers;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                bool result = isFrontier(grid, i, j);
                if (result == true) {
                    frontiers.emplace_back(i, j);
                    printf("Cell (%d, %d) is a frontier.\n", i, j);
                } else {
                    printf("Cell (%d, %d) is not a frontier.\n", i, j);
                }
            }
        }
    
    
        std::queue<std::pair<int, int>> frontierQueue;
        std::vector<std::vector<bool>> visited(grid.size(),std::vector<bool>(grid[0].size(), false));
    
        // Step 1: Select the starting frontier
    
        if (frontiers.empty()) {
            std::cout << "No frontiers found.\n";
            explorationComplete = true;
            break;
        }

        std::vector<std::vector<std::pair<int, int>>> clusters;

        for (const auto& frontier : frontiers) {

            if (visited[frontier.first][frontier.second]) {
                continue;
            }
            // Start a new cluster
            auto start = frontier;

            frontierQueue.push(start);
            visited[start.first][start.second] = true;

            std::vector<std::pair<int, int>> cluster;
            // Step 4: Start BFS traversal
            while (!frontierQueue.empty()) {

                auto current = frontierQueue.front();
                frontierQueue.pop();
                cluster.push_back(current);

                std::cout << "Processing frontier: ("
                        << current.first << ", "
                        << current.second << ")\n";
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};

                for (int i = 0; i < 4; i++) {
                    int newRow = current.first + dr[i];
                    int newCol = current.second + dc[i];


                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        if (!visited[newRow][newCol] && isFrontier(grid, newRow, newCol)) {
                            visited[newRow][newCol] = true;
                            frontierQueue.push({newRow, newCol});
                        }
                    }
                }
            }
            clusters.push_back(cluster);
        }
        
    
        std::cout << "Total clusters: " << clusters.size() << std::endl;
        // Store one exploration goal per cluster
        std::vector<std::pair<int, int>> explorationGoals;
        for (const auto& cluster : clusters) {

            double sumRow = 0.0;
            double sumCol = 0.0;

            // Write your inner loop here
            for (int i = 0; i < cluster.size(); i++) {
                sumRow += cluster[i].first;
                sumCol += cluster[i].second;
            }

        

            double avgRow = sumRow / cluster.size();
            double avgCol = sumCol / cluster.size();

            std::cout << "Cluster center: (" << avgRow << ", " << avgCol << ")\n";
            double minDistance = std::numeric_limits<double>::max();

            std::pair<int, int> bestFrontier = cluster[0];
            for (const auto& frontier : cluster) {
                double distance = std::sqrt(std::pow(frontier.first - avgRow, 2) + std::pow(frontier.second - avgCol,2));
                if (distance < minDistance) {
                    minDistance = distance;
                    bestFrontier = frontier;
                
                }
            }
            std::cout << "Best frontier: (" << bestFrontier.first << ", " << bestFrontier.second << ")\n";
            // Store the selected frontier
            explorationGoals.push_back(bestFrontier);
        

        }
        // Check that exploration goals exist
        if (explorationGoals.empty()) {
            std::cout << "No exploration goals found.\n";
            explorationComplete = true;
            break;
        }
    
        // Initialiaze goal selection variables
        double minGoalDistance = std::numeric_limits<double>::max();
        std::pair<int, int> selectedGoal = explorationGoals[0];
        bool goalFound = false;
        for (const auto& goal : explorationGoals) {
            int distance = shortestPathDistance(grid, robotPosition, goal);
            if (distance == -1) {
                std::cout << "Skipping unreachable goal\n";
                continue;
            }
        
            std::cout << "Distance from robot to goal (" << goal.first << ", "<< goal.second << "): " << distance << std::endl;
            if (distance < minGoalDistance) {
                minGoalDistance = distance;
                selectedGoal = goal;
                goalFound = true;
            }
        }
        // Print the final selected goal
        if (goalFound) {
            std::cout << "Selected exploration goal: (" << selectedGoal.first << "," << selectedGoal.second << ")\n";
        } else {
            std::cout << "No reachable exploration goal found.\n";
            explorationComplete = true;
            break;
        }
    
        std::cout << "Dijkstra path:\n";

        auto path = dijkstraPath(grid, robotPosition, selectedGoal);

        if (!path.empty()) {

            std::cout << "Path length: " << path.size() << "\n";

            for (const auto& point : path) {
                std::cout << "(" << point.first << ", "
                    << point.second << ") ";
            }

            std::cout << "\n";

            // Simulate robot movement
            robotPosition = path.back();

            // Simulate sensor observation
            updateMap(grid, groundTruth, robotPosition);

            // Display updated occupancy grid
            printMap(grid);

        } else {
            std::cout << "Path planning failed." << std::endl;
            break;
        }


        
    
    }
    std::cout << "\nFinal occupancy grid:\n";
    printMap(grid);
    return 0;
}
