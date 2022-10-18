#include <map>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
using namespace std;

// y^2 = x^3 + 4 (mod 257)

// type of point on eliptic curve
using point_t = pair<uint64_t, uint64_t>;
// identity
constexpr point_t INF_POINT{0, 0};

// a^(-1) mod p
//      using Fermat formula
uint64_t inv_mod() {}
//      Qin’s algorithm or Ext. Euclidean algorithm

// (xp, yp) + (xq, yq)
point_t ec_add(point_t p, point_t q, point_t r) { p.first = ; }

// k * (x, y)
uint64_t ec_smul(uint64_t k, uint64_t x, uint64_t y) {}

point_t tab[0x10]{};
point_t calc_table(point_t tab[], point_t P) {
  for (int i = 0; i < 0x10; i++) {
    tab[i] = point_t smul_a(i, P);
  }
}
point_t smul_d(size_t n, point_t P) {
  calc_table(tab, P);
  mask = 0xf << (bit_count - 4);
  point_t A = infinite_point;

  for (int i = 0; i < bit_count - 4; ++i) {
    A = add(A, tab[n & mask]);
    A = double(A);
    A = double(A);
    A = double(A);
    A = double(A);
    mask >>= 4;
  }
}
int main(int argc, char const *argv[]) { return 0; }
