#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <stdint.h>

struct Point2D
{
  int32_t x;
  int32_t y;

  Point2D(int32_t x, int32_t y): x(x), y(y) {}
  Point2D(const std::pair<int32_t,int32_t>& p): x(p.first), y(p.second) {}
  uint64_t hash() const noexcept { return ((uint64_t)x) << 32 | (uint64_t)y; }
  bool operator < (const Point2D& p) const { return x < p.x || (x == p.x && y < p.y); }
};

namespace std {
  template <> struct hash<Point2D> {
    std::size_t operator()(const Point2D& p) const noexcept { return p.hash(); }
  };
}

struct AStarNode {
  Point2D pos;
  float accumulatedCost;
  float heurisitic;
  bool operator < (const AStarNode& n) const{
    return this->accumulatedCost + this->heurisitic < n.accumulatedCost + n.heurisitic;
  }
};

struct tileData
{
  std::pair<int,int> point;
  std::pair<int,int> cameFrom;
  int value;

  tileData(std::pair<int,int> nPoint, std::pair<int,int> nCameFrom, int nVal)
  {
    point = nPoint;
    cameFrom = nCameFrom;
    value = nVal;
  }
  tileData()
  {
    point = {0,0};
    cameFrom = {0,0};
    value = 0;
  }
  void setValue(int newVal) { value = newVal; };
};

struct Cat : public IAgent
{
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override;

  bool updateMaps(std::vector<tileData>& map, std::queue<std::pair<int,int>>& q, std::vector<bool>& visited,
                  std::pair<int,int> start, std::pair<int,int> current, std::pair<int,int> neighbor, int sideSize);

  bool getContent(const std::vector<bool>& world, const std::pair<int,int>& p, int sideSize) const
  {
    return world[(p.second + sideSize / 2) * (sideSize) + p.first + sideSize / 2];
  }

  tileData getTileData(const std::vector<tileData>& map, std::pair<int,int> point);
  bool isValidPos(std::pair<int,int> point, int sideSize);
  bool catWinsOnSpace(std::pair<int,int> point, int sideSize);
  int howManyValidNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize);

  std::pair<int,int> E(const std::pair<int,int>& p);
  std::pair<int,int> W(const std::pair<int,int>& p);
  std::pair<int,int> NE(const std::pair<int,int>& p);
  std::pair<int,int> NW(const std::pair<int,int>& p);
  std::pair<int,int> SE(const std::pair<int,int>& p);
  std::pair<int,int> SW(const std::pair<int,int>& p);
};
#endif