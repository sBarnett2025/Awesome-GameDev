#include <iostream>
using namespace std;

int CountNeighbors(bool** buffer, int worldX, int worldY, int sizeX, int sizeY);
bool GetPoint(bool** buffer, int x, int y, int sizeX, int sizeY);

int main(){

  int sizeX = 4, sizeY = 4, numberOfSteps = 2;

  // input from file--------------------------------------------------------------------------------
  string temp;
  //cin >> sizeX >> sizeY >> numberOfSteps;

  // make buffers
  bool** currentBuffer = new bool*[sizeX];
  for (int i = 0; i < sizeX; i++)
  {
    currentBuffer[i] = new bool[sizeY];
  }

  bool** nextBuffer = new bool*[sizeX];
  for (int i = 0; i < sizeX; i++)
  {
    nextBuffer[i] = new bool[sizeY];
  }

  for (int y = 0; y < sizeY; y++)
  {
    cin >> temp;
    for (int x = 0; x < sizeX; x++)
    {
      if (temp[x] == '#')
      {
        currentBuffer[x][y] = true;
      }
      else if (temp[x] == '.')
      {
        currentBuffer[x][y] = false;
      }
      else
      {
        cout << "input flawed" << endl;
        return 1;
      }
    }
  }

  // Game Loop--------------------------------------------------------------------------------------
  for (int i = 0; i < numberOfSteps; i++)
  {
    // loop over Y
    for (int y = 0; y < sizeY; y++)
    {
      // loop over x
      for (int x = 0; x < sizeX; x++)
      {
        // check neighbors
        int neighbors = CountNeighbors(currentBuffer, x, y, sizeX, sizeY);

        // check overpopulation
        if (GetPoint(currentBuffer, x, y, sizeX, sizeY) && neighbors >= 4)
        {

        }


      }

    }

    // switch buffers

  }

  // print final result-----------------------------------------------------------------------------
  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      string output = currentBuffer[x][y]?"#":".";
      cout << output;
    }
    cout << endl;
  }

  return 0;
};

int CountNeighbors(bool** buffer, int worldX, int worldY, int sizeX, int sizeY)
{
  int count = 0;
  for (int y = -1; y <= 1; y++)
  {
    for (int x = -1; x <= 1; x++)
    {
      if (x == 0 && y == 0)
      {
        continue;
      }

      count += GetPoint(buffer, worldX + x, worldY + y, sizeX, sizeY)?1:0;
    }
  }
  return count;
}

bool GetPoint(bool** buffer, int x, int y, int xSize, int ySize)
{
  bool value = false;

  if (x < 0) x += xSize;
  if (x >= xSize) x %= xSize;
  if (y < 0) y += ySize;
  if (y >= ySize) y %= ySize;

  value = buffer[x][y];

  return value;
}



