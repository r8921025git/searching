
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>


using std::cout;
using std::default_random_engine;
using std::endl;
using std::ifstream;
using std::invalid_argument;
using std::ios;
using std::numeric_limits;
using std::ofstream;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

// @include
int FindMissingElement(ifstream* ifs) {
  vector<int> counter(1 << 16, 0); // 2^16 buckets
  unsigned int x;
  while (*ifs >> x) {
    ++counter[x >> 16]; // only care about first 16 bits
  }
  for (int i=0; i<1<<16; ++i) {
      if (counter[i] < 1<<16) { // this bucket has missing IP
          ifs->clear();
          ifs->seekg(0,ios::beg);
          vector<bool> bits(16);
          while (*ifs>>x) {
              // only care about last 16 bits
              unsigned int y = ((1<<16)-1) & x;
              bits[y] = 1;
          }
          for (int k=0; k<1<<16; ++k) {
              if (bits[k]==0) {
                  return i;
              }
          }
      }
  }
}
// @exclude

int main(int argc, char* argv[]) {
  int n;
  default_random_engine gen((random_device())());
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    n = 300000000;
  }
  n = 1000;
  //vector<int> A(1000000000);
  vector<int> A(10000);
      iota(A.begin(), A.end(), 0); // 0,1,2,...
  unordered_set<int> hash;
  ofstream ofs("missing.txt");
  for (int i = 0; i < n; ++i) {
    hash.emplace(A[i]);
    ofs << A[i] << endl;
  }
  A.clear();
  ofs.close();
  ifstream ifs("missing.txt");
  cout << "Before finding missing" << endl;
  int missing = FindMissingElement(&ifs);
  cout <<"missing:"<< missing << endl;
  assert(hash.find(missing) == hash.cend());
  // Remove file after the execution.
  remove("missing.txt");
  return 0;
}
