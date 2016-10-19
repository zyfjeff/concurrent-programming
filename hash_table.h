#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <atomic>
#include <stdint.h>
#include "macros.h"

struct Entry
{
  std::atomic<uint32_t> key;
  std::atomic<uint32_t> value;
};

class HashTable
{
 public:
  HashTable(uint32_t arraysize = 64);
  ~HashTable();
  void SetItem(uint32_t key, uint32_t value);
  uint32_t GetItem(uint32_t key);

 private:
  Entry* entry_;
  uint32_t arraySize_;
 
  DISALLOW_COPY_AND_ASSIGN(HashTable);
};

#endif // __HASH_TABLE_H_
