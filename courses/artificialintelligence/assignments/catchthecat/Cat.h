#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>
#include <unordered_map>
#include <iostream>

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