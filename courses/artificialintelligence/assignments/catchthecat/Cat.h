#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <stdint.h>


struct Position {
  // include cstdint
  int32_t x;
  int32_t y;

  Position(int32_t x, int32_t y): x(x), y(y) {}
  Position(): x(0), y(0) {}
  Position(const Position& p): x(p.x), y(p.y) {}
  Position(Position&& p) noexcept: x(p.x), y(p.y) {}
  Position(const std::pair<int32_t, int32_t>& p): x(p.first), y(p.second) {}
  Position& operator=(const Position& p)= default;
  Position& operator=(const std::pair<int32_t, int32_t>& p){
    x = p.first;
    y = p.second;
    return *this;
  }
  bool operator==(const Position& p) const{
    return x == p.x && y == p.y;
  }
  bool operator!=(const Position& p) const{
    return x != p.x || y != p.y;
  }
  inline Position NW() const{
    return (y % 2 == 0) ?
                        Position(x-1, y-1) :
                        Position(x, y-1);
  }
  inline Position NE() const{
    return (y % 2 == 0) ?
                        Position(x, y-1) :
                        Position(x+1, y-1);
  }
  inline Position E() const{
    return {x+1, y};
  }
  inline Position W() const{
    return {x-1, y};
  }
  inline Position SW() const{
    return (y % 2 == 0) ?
                        Position(x-1, y+1) :
                        Position(x, y+1);
  }
  inline Position SE() const{
    return (y % 2 == 0) ?
                        Position(x, y+1) :
                        Position(x+1, y+1);
  }
  inline bool IsInsideBoardBoundaries(int32_t sideSize) const {
    return abs(x) <= sideSize/2 && abs(y) <= sideSize/2;
  }
  inline std::vector<Position> Neighbors() const{
    return std::vector<Position>{NW(), NE(), E(), W(), SW(), SE()};
  }
  std::pair<int,int> toPair(){return {x,y};}

  bool operator < (const Position& p) const{
    return x < p.x || (x == p.x && y < p.y);
  }
  uint64_t hash() const noexcept { return ((uint64_t)x) << 32 | (uint64_t)y; }
}; // end of Position





namespace std {
  template <> struct hash<Position> {
    std::size_t operator()(const Position& p) const noexcept { return p.hash(); }
  };
}

struct AStarNode {
  Position pos;
  float accumulatedCost;
  float heuristic;
  bool operator < (const AStarNode& n) const{
    return this->accumulatedCost + this->heuristic < n.accumulatedCost + n.heuristic;
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
  bool catWinsOnSpace(Position point, int sideSize);
  float getDistanceToEdge(Position p, int sidesize);
  int howManyValidNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize);

  std::pair<int,int> E(const std::pair<int,int>& p);
  std::pair<int,int> W(const std::pair<int,int>& p);
  std::pair<int,int> NE(const std::pair<int,int>& p);
  std::pair<int,int> NW(const std::pair<int,int>& p);
  std::pair<int,int> SE(const std::pair<int,int>& p);
  std::pair<int,int> SW(const std::pair<int,int>& p);
};
#endif