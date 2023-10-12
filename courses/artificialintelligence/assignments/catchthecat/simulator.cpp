// DO NOT SUBMIT THIS FILE
// IMPROVE THIS SIMULATOR FOR YOUR OWN USE
// this code is not well tested, use as entry point for your own simulator
#include <iostream>
#include <vector>
#include "Cat.h"
#include "Catcher.h"

void simulate(bool& win, std::string& turn, std::vector<bool>& blocked, int& catX, int& catY, int sideSize);
bool catWinCheck(std::vector<bool> world, std::pair<int,int> catPos, int sideSize);
bool catcherWinCheck(std::vector<bool> world, std::pair<int,int> catPos, int sideSize);
bool getContent(const std::vector<bool>& world, const std::pair<int,int>& p, int sideSize);

std::pair<int,int> E(const std::pair<int,int>& p);
std::pair<int,int> W(const std::pair<int,int>& p);
std::pair<int,int> NE(const std::pair<int,int>& p);
std::pair<int,int> NW(const std::pair<int,int>& p);
std::pair<int,int> SE(const std::pair<int,int>& p);
std::pair<int,int> SW(const std::pair<int,int>& p);

void print(const std::vector<bool>& state, int sideSize, std::pair<int,int> catPos, const std::string& turn){
  std::cout << turn << " " << sideSize << " " << catPos.first << " " << catPos.second << std::endl;
  catPos.first += sideSize/2;
  catPos.second += sideSize/2;
  auto catPosIndex = catPos.second * sideSize + catPos.first;
  for(int y=0; y<sideSize; y++) {
    if (y % 2 == 1) std::cout << ' ';
    for (int x = 0; x < sideSize; x++) {
      if(y * sideSize + x == catPosIndex) {
        std::cout << 'C';
      } else
        std::cout << (state[y * sideSize + x] ? '#' : '.');
      if (x < sideSize - 1) std::cout << ' ';
    }
    std::cout << std::endl;
  }
}

std::vector<bool> readBoard(int sideSize) {
  std::vector<bool> board;
  board.reserve(sideSize*sideSize);
  for(int i=0; i<sideSize*sideSize; i++) {
    char c;
    std::cin >> c;
    switch (c) {
      case '#':
        board.push_back(true);
        break;
      case '.':
      case 'C':
        board.push_back(false);
        break;
      default:
        i--;
        break;
    }
  }
  return board;
}

int main() {
  std::string turn;
  int sideSize;
  int catX, catY;
  std::vector<bool> blocked;
  std::cin >> turn >> sideSize >> catX >> catY;
  blocked = readBoard(sideSize);
  bool win = false;
  while (!win) { simulate(win, turn, blocked, catX, catY, sideSize); } // todo: create your own logic to test and simulate, check for win conditions etc.
  //simulate(win, turn, blocked, catX, catY, sideSize);
  return 0;
}

void simulate(bool& win, std::string& turn, std::vector<bool>& blocked, int& catX, int& catY, int sideSize)
{
  if (turn == "CAT")
  {
    Cat cat;
    auto catMove = cat.move(blocked, {catX, catY}, sideSize);
    catX = catMove.first;
    catY = catMove.second;
    print(blocked, sideSize, {catMove.first, catMove.second}, "CATCHER");
    win = catWinCheck(blocked, {catX,catY}, sideSize);
    turn = "CATCHER";
  }
  else if (turn == "CATCHER")
  {
    Catcher catcher;
    auto catcherMove = catcher.move(blocked, {catX, catY}, sideSize);
    blocked[(catcherMove.second + sideSize / 2) * sideSize + catcherMove.first + sideSize / 2]
        = true;
    print(blocked, sideSize, {catX, catY}, "CAT");
    win = catcherWinCheck(blocked, {catX, catY}, sideSize);
    turn = "CAT";
  }
}

bool catWinCheck(std::vector<bool> world, std::pair<int,int> catPos, int sideSize)
{
  //std::cout << "cat win?" << std::endl;
  auto half = sideSize / 2;
  return abs(catPos.first) == half || abs(catPos.second) == half;
}

bool catcherWinCheck(std::vector<bool> world, std::pair<int,int> catPos, int sideSize)
{
  //std::cout << "catcher win?" << std::endl;
  return getContent(world, NW(catPos), sideSize) &&
         getContent(world, NE(catPos), sideSize) &&
         getContent(world, E(catPos), sideSize) &&
         getContent(world, SE(catPos), sideSize) &&
         getContent(world, SW(catPos), sideSize) &&
         getContent(world, W(catPos), sideSize);
}

bool getContent(const std::vector<bool>& world, const std::pair<int,int>& p, int sideSize)
{
  return world[(p.second + sideSize / 2) * (sideSize) + p.first + sideSize / 2];
}

std::pair<int,int> E(const std::pair<int,int>& p) { return {p.first + 1, p.second}; }

std::pair<int,int> W(const std::pair<int,int>& p) { return {p.first - 1, p.second}; }

std::pair<int,int> NE(const std::pair<int,int>& p) {
  if (p.first % 2) return {p.first + 1, p.second - 1};
  return {p.first, p.second - 1};
}

std::pair<int,int> NW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second - 1};
  return {p.first - 1, p.second - 1};
}

std::pair<int,int> SE(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first, p.second + 1};
  return {p.first - 1, p.second + 1};
}

std::pair<int,int> SW(const std::pair<int,int>& p) {
  if (p.second % 2) return {p.first + 1, p.second + 1};
  return {p.first, p.second + 1};
}