#include <iostream>
using namespace std;

int CountNeighbors(bool** buffer, int worldX, int worldY, int sizeX, int sizeY);
bool GetPoint(bool** buffer, int x, int y, int sizeX, int sizeY);
void SetNextPoint(bool** buffer, int x, int y, bool value);
void SwitchBuffers(bool** current, bool** next, int sizeX, int sizeY);

int main(){

  int sizeX = 0, sizeY = 0, numberOfSteps = 0;

  // input from file--------------------------------------------------------------------------------
  string temp;
  cin >> sizeX >> sizeY >> numberOfSteps;

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

  // continue reading-------------------------------------------------------------------------------
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
        bool alive = GetPoint(currentBuffer, x, y, sizeX, sizeY);

        // Game Rules-------------------------------------------------------------------------------

        // check overpopulation
        if (alive && neighbors >= 4)
        {
          alive = false;
        }

        // check underpopulation
        if (alive && neighbors <= 1)
        {
          alive = false;
        }

        // check repopulation
        if (!alive && neighbors == 3)
        {
          alive = true;
        }

        SetNextPoint(nextBuffer, x, y, alive);
      }

    }

    // switch buffers
    SwitchBuffers(currentBuffer, nextBuffer, sizeX, sizeY);
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
  for (int localY = -1; localY <= 1; localY++)
  {
    for (int localX = -1; localX <= 1; localX++)
    {
      if (localX == 0 && localY == 0)
      {
        continue;
      }

      count += GetPoint(buffer, worldX + localX, worldY + localY, sizeX, sizeY)?1:0;
    }
  }
  return count;
}

bool GetPoint(bool** buffer, int x, int y, int sizeX, int sizeY)
{
  bool value = false;

  if (x < 0) x += sizeX;
  if (x >= sizeX) x %= sizeX;
  if (y < 0) y += sizeY;
  if (y >=  sizeY) y %= sizeY;

  value = buffer[x][y];

  return value;
}

void SetNextPoint(bool** buffer, int x, int y, bool value)
{
  buffer[x][y] = value;
}

void SwitchBuffers(bool** current, bool** next, int sizeX, int sizeY)
{
  for (int x = 0; x < sizeX; x++)
  {
    for (int y = 0; y < sizeY; y++)
    {
      current[x][y] = next[x][y];
    }
  }
}