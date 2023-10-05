// add your imports here
#include <iostream>
#include <vector>

using namespace std;

struct point
{
  int x;
  int y;
};

vector<point> GetNeighbors(const vector<bool>& data, const vector<bool>& visited, point p, int xSize, int ySize);
bool PointValid(point p, int xSize, int ySize);
int GetRand(int pool[], int& index);
void PrintMaze(const vector<bool>& hori, const vector<bool>& vert, int xSize, int ySize);

int main()
{
  // Variable declarations
  int xSize, ySize;
  int randPool[100] = {72, 99, 56, 34, 43, 62, 31, 4,  70, 22, 6,  65, 96, 71, 29, 9,  98, 41, 90, 7,
         30, 3,  97, 49, 63, 88, 47, 82, 91, 54, 74, 2,  86, 14, 58, 35, 89, 11, 10, 60,
         28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5,  24, 33, 77, 53,
         51, 59, 20, 42, 80, 61, 1,  0,  38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13,
         12, 78, 75, 73, 84, 81, 8,  32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
  int randIndex = 0;

  vector<bool> data;

  vector<point> stack;
  vector<bool> visited;

  vector<bool> horizontals;
  vector<bool> verticals;

  // user input
  cin >> xSize >> ySize >> randIndex;

  data.reserve(xSize * ySize);
  visited.reserve(xSize * ySize);
  horizontals.reserve(xSize * (ySize + 1));
  verticals.reserve((xSize + 1) * ySize);

  for (int i = 0; i < xSize * ySize; i++)
  {
    data[i] = true;
    visited[i] = false;
  }
  for (int i = 0; i < xSize * (ySize + 1); i++)
  {
    horizontals[i] = true;
  }
  for (int i = 0; i < (xSize + 1) * ySize; i++)
  {
    verticals[i] = true;
  }

  // do loop
  stack.push_back(point(0, 0));

  while (!stack.empty())
  {
    point curr = stack.back();

    visited[xSize*curr.y+curr.x] = true;

    vector<point> neighbors = GetNeighbors(data, visited, curr, xSize, ySize);
    if (neighbors.empty())
    {
      stack.pop_back();
    }
    else
    {
      // choose a neighbor
      point chosen;
      if (neighbors.size() == 1)
      {
        chosen = neighbors[0];
      }
      else
      {
        int randomNum = GetRand(randPool, randIndex);
        int index = randomNum % neighbors.size();

        chosen = neighbors[index];
      }

      // remove wall
      if (chosen.y == curr.y-1) // North
      {
        horizontals[xSize*(curr.y-1)+curr.x] = false;
        data[xSize*curr.y+curr.x] = false;
      }
      else if (chosen.x == curr.x+1) // East
      {
        verticals[(xSize+1)*curr.y+(curr.x+1)] = false;
        data[xSize*curr.y+curr.x] = false;
      }
      else if (chosen.y == curr.y+1) // South
      {
        horizontals[xSize*curr.y+curr.x] = false;
        data[xSize*curr.y+curr.x] = false;
      }
      else if (chosen.x == curr.x-1) // West
      {
        verticals[(xSize+1)*curr.y+curr.x] = false;
        data[xSize*curr.y+curr.x] = false;
      }
      else
      {
        std::cout << ":2" << std::endl;
      }

      // add neighbor
      stack.push_back(chosen);

    }

    if (stack.empty())
    {
      break;
    }

  }

  // print result
  PrintMaze(horizontals, verticals, xSize, ySize);

  return 0;
}

vector<point> GetNeighbors(const vector<bool>& data, const vector<bool>& visited, point p, int xSize, int ySize)
{
  vector<point> neighbors;
  neighbors.clear();
  point temp;

  // north
  temp.x = p.x;
  temp.y = p.y-1;
  if (!PointValid(temp, xSize, ySize)) {}
  else if (data[xSize*temp.y+temp.x] && !visited[xSize*temp.y+temp.x])
  {
    neighbors.push_back(temp);
  }

  // east
  temp.x = p.x+1;
  temp.y = p.y;
  if (!PointValid(temp, xSize, ySize)) {}
  else if (data[xSize*temp.y+temp.x] && !visited[xSize*temp.y+temp.x])
  {
    neighbors.push_back(temp);
  }

  // south
  temp.x = p.x;
  temp.y = p.y+1;
  if (!PointValid(temp, xSize, ySize)) {}
  else if (data[xSize*temp.y+temp.x] && !visited[xSize*temp.y+temp.x])
  {
    neighbors.push_back(temp);
  }

  // west
  temp.x = p.x-1;
  temp.y = p.y;
  if (!PointValid(temp, xSize, ySize)) {}
  else if (data[xSize*temp.y+temp.x] && !visited[xSize*temp.y+temp.x])
  {
    neighbors.push_back(temp);
  }

  return neighbors;
}

bool PointValid(point p, int xSize, int ySize)
{
  if (p.x < 0 || p.x >= xSize || p.y < 0 || p.y >= ySize)
  {
    return false;
  }
  return true;
}

int GetRand(int pool[], int& index)
{
  int value = pool[index];
  index++;
  if (index > 99)
  {
    index = 0;
  }
  return value;
}

void PrintMaze(const vector<bool>& hori, const vector<bool>& vert, int xSize, int ySize)
{
  bool vertNow = true;
  int vertCounter = 0;
  int horiCounter = 0;
  for (int x = 0; x < xSize; x++)
  {
    cout << " _";
  }
  cout << endl;
  for (int y = 0; y < ySize; y++)
  {
    vertNow = true;
    for (int x = 0; x < xSize*2+1; x++)
    {
      if (vertNow)
      {
        if (vert[vertCounter]) { cout << "|"; }
        else { cout << " "; }
        vertNow = false;
        vertCounter++;
      }
      else
      {
        if (hori[horiCounter]) { cout << "_"; }
        else { cout << " "; }
        vertNow = true;
        horiCounter++;
      }
    }
    cout << endl;

  }
}
