#include "Cat.h"

std::pair<int,int> Cat::move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize )
{
  bool solutionFound = false;
  bool firstLoop = true;

  std::queue<std::pair<int,int>> q;
  q.push(catPos);
  std::vector<bool> visited;
  visited.resize(sideSize * sideSize);
  std::pair<int,int> bestPoint, current, neighbor;
  std::vector<tileData> mapData;

  std::vector<std::pair<int,int>> neighbors;

  while (!q.empty())
  {
    current = q.front();

    visited[(current.second + sideSize / 2) * (sideSize) + current.first + sideSize / 2] = true;

    // NW
    neighbor = NW(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }

    // NE
    neighbor = NE(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }
    // E
    neighbor = E(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }
    // SE
    neighbor = SE(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }
    // SW
    neighbor = SW(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }
    // W
    neighbor = W(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      if (updateMaps(mapData, q, visited, catPos, current, neighbor, sideSize)) {solutionFound = true;}
      if (firstLoop) { neighbors.push_back(neighbor); }
    }

    q.pop();
    firstLoop = false;
  }

  int lowestValue = INT_MAX;
  for (int i = 0; i < neighbors.size(); i++)
  {
    if (catWinsOnSpace(neighbors[i], sideSize) && !getContent(world, neighbors[i], sideSize))
    {
      return neighbors[i];
    }
    int currentVal = getTileData(mapData, neighbors[i]).value;
    if (currentVal < lowestValue)
    {
      bestPoint = neighbors[i];
      lowestValue = currentVal;
    }
  }

  int highestValue = 0;
  if (!solutionFound)
  {
    for (int i = 0; i < neighbors.size(); i++)
    {
      int neighborCount = howManyValidNeighbors(world, neighbors[i], sideSize);
      if (neighborCount > highestValue)
      {
        highestValue = neighborCount;
        bestPoint = neighbors[i];
      }
    }
  }

  return bestPoint;
}




bool Cat::updateMaps(std::vector<tileData>& map, std::queue<std::pair<int,int>>& q, std::vector<bool>& visited,
                std::pair<int,int> start, std::pair<int,int> current, std::pair<int,int> neighbor, int sideSize)
{
  bool solution = false;
  visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;

  map.push_back({neighbor, current, 9000});
  std::pair<int,int> from;
  int counter = 0;
  if (catWinsOnSpace(neighbor, sideSize))
  {
    solution = true;
    //from = map.find(neighbor)->second;
    from = getTileData(map, neighbor).cameFrom;
    while (from != start)
    {
      counter++;
      if (counter < getTileData(map, from).value)
      {
        getTileData(map, from).setValue(counter);
      }
      from = getTileData(map, from).cameFrom;
    }
  }
  else { q.push(neighbor); }

  return solution;
}

tileData Cat::getTileData(const std::vector<tileData>& map, std::pair<int,int> point)
{
  for (int i = 0; i < map.size(); i++)
  {
    if (map[i].point == point) { return map[i]; }
  }
  tileData trash = tileData();
  return trash;
}

bool Cat::isValidPos(std::pair<int,int> point, int sideSize)
{
  auto half = sideSize / 2;
  return (point.first >= -half) && (point.first <= half) && (point.second >= -half) && (point.second <= half);
}

bool Cat::catWinsOnSpace(std::pair<int,int> point, int sideSize)
{
  auto sideOver2 = sideSize / 2;
  return abs(point.first) == sideOver2 || abs(point.second) == sideOver2;
}

int Cat::howManyValidNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize)
{
  int counter = 0;
  std::pair<int,int> neighbor;

  neighbor = NW(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }
  neighbor = NE(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }
  neighbor = E(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }
  neighbor = SE(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }
  neighbor = SW(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }
  neighbor = W(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) { counter++; }

  return counter;
}

std::pair<int,int> Cat::E(const std::pair<int,int>& p) { return {p.first + 1, p.second}; }

std::pair<int,int> Cat::W(const std::pair<int,int>& p) { return {p.first - 1, p.second}; }

std::pair<int,int> Cat::NE(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first + 1, p.second - 1};
  return {p.first, p.second - 1};
}

std::pair<int,int> Cat::NW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second - 1};
  return {p.first - 1, p.second - 1};
}

std::pair<int,int> Cat::SE(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second + 1};
  return {p.first - 1, p.second + 1};
}

std::pair<int,int> Cat::SW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first + 1, p.second + 1};
  return {p.first, p.second + 1};
}