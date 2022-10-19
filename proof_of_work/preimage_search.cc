// #include <algorithm>
#include "csvwriter.h"
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <openssl/sha.h>
#include <random>
#include <string.h>
#include <sys/types.h>
#include <utility>
#include <vector>

// #include < type_traits>
using namespace std;
using namespace chrono;

inline void sha256(const uint8_t *msg, uint8_t *dgst, size_t len) {
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, msg, len);
  SHA256_Final(dgst, &ctx);
}

inline void H(const uint8_t *msg, uint8_t *dgst, size_t len) {
  // first sha256
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, msg, len);
  SHA256_Final(dgst, &ctx);
  // second sha256
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, dgst, len);
  SHA256_Final(dgst, &ctx);
}

// 16 primes
// 2, 3, 5, 7
// 11, 13, 17, 19
// 23, 29, 31, 37
// 41, 43, 47, 53
uint8_t M[16][32];

const char *str_primes[16]{
    "2",  "3",  "5",  "7",  //
    "11", "13", "17", "19", //
    "23", "29", "31", "37", //
    "41", "43", "47", "53"  //
};

inline void dump_buf(uint8_t *buf, size_t len, uint8_t sep = ' ') {
  for (size_t i = 0; i < len; i++) {
    printf("0x%.2x%c", buf[i], sep);
    if ((i + 1) % 8 == 0)
      printf("\n");
  }
  printf("\n");
}

// hash to get 16 messages
void get_msg() {
  for (size_t i = 0; i < 16; ++i) {
    H((const uint8_t *)str_primes[i], M[i], strlen(str_primes[i]));
    printf("M%d\n", int(i + 1));
    dump_buf(M[i], 32);
  }
}

// 256 - 235 = 21 = 8 + 8 + 5
vector<pair<uint64_t, double>> brute_force_target1() {
  uint8_t msg[32 + 8]; //
  uint8_t dgst[32];
  vector<pair<uint64_t, double>> ret;

  for (int i = 0; i < 16; ++i) {
    cout << "Search r for M" << i + 1 << ", Target 1" << endl;
    auto t1 = chrono::high_resolution_clock::now();
    memcpy(msg, M[i], 32);
    for (uint64_t r = 0; r <= 0xffffffffffffffff; ++r) {
      //   if (r % 10000000000 == 0)
      //     cout << r << endl;

      *(uint64_t *)(msg + 32) = r; // append 64 bits
      H(msg, dgst, 32 + 8);
      //
      if (dgst[0] == 0 && dgst[1] == 0 && (dgst[2] & 0b1111100) == 0) {
        auto t2 = chrono::high_resolution_clock::now();
        double duration =
            chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
        cout << "Target1 >= Hash(M" << i + 1 << "||" << hex //
             << r << ")" << dec << endl;

        ret.push_back({r, duration});
        break;
      }
    }
  }
  return ret;
}

// 256 - 230 = 26 = 8 + 8 + 8 + 2
vector<pair<uint64_t, double>> brute_force_target2() {
  uint8_t msg[32 + 8]; //
  uint8_t dgst[32];

  vector<pair<uint64_t, double>> ret;
  for (int i = 0; i < 16; ++i) {
    cout << "Search r for M" << i + 1 << ", Target 1" << endl;
    memcpy(msg, M[i], 32);

    auto t1 = chrono::high_resolution_clock::now();
    for (uint64_t r = 0; r <= 0xffffffffffffffff; ++r) {
      //   if (r % 10000000 == 0)
      //     cout << r << endl;

      *(uint64_t *)(msg + 32) = r; // append 64 bits
      H(msg, dgst, 32 + 8);

      if (dgst[0] == 0 && dgst[1] == 0 && dgst[2] == 0 &&
          (dgst[3] & 0b1100000) == 0) {
        auto t2 = chrono::high_resolution_clock::now();
        double duration =
            chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
        cout << "Target2 >= Hash(M" << i + 1 << "||" << hex //
             << r << ")" << dec << endl;
        ret.push_back({r, duration});
        break;
      }
    }
  }
  return ret;
}

// 256 - 235 = 26 = 8 + 8 + 5
vector<pair<pair<uint64_t, uint64_t>, double>> random_target1() {
  uint8_t msg[32 + 8]; //
  uint8_t dgst[32];
  vector<pair<pair<uint64_t, uint64_t>, double>> ret;

  std::mt19937_64 rng(rand() + 114514);
  std::uniform_int_distribution<uint64_t> distribution(1, 0xffffffffffffffff);

  for (int i = 0; i < 16; ++i) {
    cout << "Search r for M" << i + 1 << ", Target 1" << endl;
    memcpy(msg, M[i], 32);
    auto t1 = chrono::high_resolution_clock::now();
    for (uint64_t j = 0; j <= 0xffffffffffffffff; ++j) {

      uint64_t r = distribution(rng);
      *(uint64_t *)(msg + 32) = r;
      H(msg, dgst, 32 + 8);

      if (dgst[0] == 0 && dgst[1] == 0 && (dgst[2] & 0b1111100) == 0) {
        auto t2 = chrono::high_resolution_clock::now();
        double duration =
            chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
        cout << "Target2 >= Hash(M" << i + 1 << "||" << hex //
             << r << ")" << dec << endl;
        ret.push_back({{r, j}, duration});
        break;
      }
    }
  }
  return ret;
}

// 256 - 230 = 26 = 8 + 8 + 8 + 2
vector<pair<pair<uint64_t, uint64_t>, double>> random_target2() {
  uint8_t msg[32 + 8]; //
  uint8_t dgst[32];
  vector<pair<pair<uint64_t, uint64_t>, double>> ret;

  std::mt19937_64 rng(rand() + 14514);
  std::uniform_int_distribution<uint64_t> distribution(1, 0xffffffffffffffff);

  for (int i = 0; i < 16; ++i) {
    cout << "Search r for M" << i + 1 << ", Target 1" << endl;
    memcpy(msg, M[i], 32);
    auto t1 = chrono::high_resolution_clock::now();
    for (uint64_t j = 0; j <= 0xffffffffffffffff; ++j) {

      uint64_t r = distribution(rng);
      *(uint64_t *)(msg + 32) = r;
      H(msg, dgst, 32 + 8);

      if (dgst[0] == 0 && dgst[1] == 0 && (dgst[2] & 0b1111100) == 0) {
        auto t2 = chrono::high_resolution_clock::now();
        double duration =
            chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
        cout << "Target2 >= Hash(M" << i + 1 << "||" << hex //
             << r << ")" << dec << endl;
        ret.push_back({{r, j}, duration});
        break;
      }
    }
  }
  return ret;
}

void save2file1(const char *filename, vector<pair<uint64_t, double>> tab) {

  CSVWriter csv(",");
  csv.newRow() << "M"
               << "Nonce"
               << "Duration";
  double total_duration = 0;
  for (size_t i = 0; i < tab.size(); ++i) {
    csv.newRow() << i + 1 << tab[i].first << tab[i].second;
    total_duration += tab[i].second;
  }
  auto avg_duration = total_duration / 16;
  csv.newRow() << "Average"
               << "" << avg_duration;
  csv.writeToFile(filename);
}

void save2file2(const char *filename,
                vector<pair<pair<uint64_t, uint64_t>, double>> tab) {

  CSVWriter csv(",");
  csv.newRow() << "M"
               << "Nonce"
               << "Hash count"
               << "Duration";

  double total_duration = 0;
  uint64_t total_hash_count = 0;
  for (size_t i = 0; i < tab.size(); ++i) {
    csv.newRow() << i + 1 << tab[i].first.first << tab[i].first.second
                 << tab[i].second;
    total_hash_count += tab[i].first.second;
    total_duration += tab[i].second;
  }

  auto avg_hash_count = total_hash_count / 16;
  auto avg_duration = total_duration / 16;
  csv.newRow() << "Average"
               << "" << avg_hash_count << avg_duration;

  csv.writeToFile(filename);
}

int main() {
  // hash to get 16 messages
  get_msg();

  //   auto tab1 = brute_force_target1();
  //   save2file1("./strategy1_target1.csv", tab1);

  //   auto tab2 = brute_force_target2();
  //   save2file1("./strategy1_target2.csv", tab2);

  auto tab3 = random_target1();
  save2file2("./strategy2_target1.csv", tab3);

  //   auto tab4 = random_target2();
  //   save2file2("./strategy2_target2.csv", tab4);
}
