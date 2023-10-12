#include "Catcher.h"

std::pair<int,int> Catcher::move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize )
{
  bool solutionFound = false;
  bool firstLoop = true;

  std::queue<std::pair<int,int>> q;
  q.push(catPos);
  std::vector<bool> visited;
  visited.resize(sideSize * sideSize);
  std::vector<std::pair<int,int>> neighbors;
  getNeighbors(world, neighbors, catPos, sideSize);
  std::pair<int,int> current, neighbor, bestPoint;

  while (!q.empty())
  {
    current = q.front();

    if (catWinsOnSpace(current, sideSize))
    {
      solutionFound = true;
      while (!q.empty())
      {
        q.pop();
      }

      return current;
    }

    if (howManyValidNeighbors(world, catPos, sideSize) == 1)
    {
      return neighbors[0];
    }
    neighbors.clear();

    visited[(current.second + sideSize / 2) * (sideSize) + current.second + sideSize / 2] = true;

    // NW
    neighbor = NW(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }
    // NE
    neighbor = NE(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }
    // E
    neighbor = E(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }
    // SE
    neighbor = SE(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }
    // SW
    neighbor = SW(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }
    // W
    neighbor = W(current);
    if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize) && !getContent(visited, neighbor, sideSize))
    {
      visited[(neighbor.second + sideSize / 2) * (sideSize) + neighbor.first + sideSize / 2] = true;
      q.push(neighbor);
      if (firstLoop)
      {
        neighbors.push_back(neighbor);
      }
    }

    q.pop();
    firstLoop = false;
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

void Catcher::getNeighbors(const std::vector<bool>& world, std::vector<std::pair<int,int>>& neighbors, std::pair<int,int> point, int sideSize)
{
  std::pair<int,int> neighbor = NW(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
  neighbor = NE(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
  neighbor = E(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
  neighbor = SE(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
 neighbor = SW(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
  neighbor = W(point);
  if (isValidPos(neighbor, sideSize) && !getContent(world, neighbor, sideSize)) {neighbors.push_back(neighbor); }
}

bool Catcher::catWinsOnSpace(std::pair<int,int> point, int sideSize)
{
  auto sideOver2 = sideSize / 2;
  return abs(point.first) == sideOver2 || abs(point.second) == sideOver2;
}

bool Catcher::isValidPos(std::pair<int,int> point, int sideSize)
{
  auto half = sideSize / 2;
  return (point.first >= -half) && (point.first <= half) && (point.second >= -half) && (point.second <= half);
}

int Catcher::howManyValidNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize)
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

std::pair<int,int> Catcher::E(const std::pair<int,int>& p) { return {p.first + 1, p.second}; }

std::pair<int,int> Catcher::W(const std::pair<int,int>& p) { return {p.first - 1, p.second}; }

std::pair<int,int> Catcher::NE(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first + 1, p.second - 1};
  return {p.first, p.second - 1};
}

std::pair<int,int> Catcher::NW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second - 1};
  return {p.first - 1, p.second - 1};
}

std::pair<int,int> Catcher::SE(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second + 1};
  return {p.first - 1, p.second + 1};
}

std::pair<int,int> Catcher::SW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first + 1, p.second + 1};
  return {p.first, p.second + 1};
}