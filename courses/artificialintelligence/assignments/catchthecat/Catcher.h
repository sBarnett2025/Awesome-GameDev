#ifndef CATCHER_H
#define CATCHER_H
#include "IAgent.h"
#include <queue>
#include <iostream>

struct Catcher : public IAgent
{
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override;

  bool getContent(const std::vector<bool>& world, const std::pair<int,int>& p, int sideSize) const
  {
    return world[(p.second + sideSize / 2) * (sideSize) + p.first + sideSize / 2];
  }

  void getNeighbors(const std::vector<bool>& world, std::vector<std::pair<int,int>>& neighbors, std::pair<int,int> point, int sideSize);
  bool catWinsOnSpace(std::pair<int,int> point, int sideSize);
  bool isValidPos(std::pair<int,int> point, int sideSize);
  int howManyValidNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize);

  std::pair<int,int> E(const std::pair<int,int>& p);
  std::pair<int,int> W(const std::pair<int,int>& p);
  std::pair<int,int> NE(const std::pair<int,int>& p);
  std::pair<int,int> NW(const std::pair<int,int>& p);
  std::pair<int,int> SE(const std::pair<int,int>& p);
  std::pair<int,int> SW(const std::pair<int,int>& p);
};
#endif