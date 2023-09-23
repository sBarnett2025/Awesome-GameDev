// add your imports here
#include <iostream>
using namespace std;


int main(){
  // code here
  unsigned int seed, numberOfResults;
  signed int minRange, maxRange;

  // input------------------------------------------------------------------------------------------
  cin >> seed >> numberOfResults >> minRange >> maxRange;

  for (int i = 0; i < numberOfResults; i++)
  {
    // calculate seed-------------------------------------------------------------------------------
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;


    // final result---------------------------------------------------------------------------------
    int final = minRange + (seed % (maxRange - minRange + 1));
    cout << final << endl;
  }

}
