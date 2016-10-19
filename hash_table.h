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
  HashTable(uint32_t arraysize);
  ~HashTable();
  void SetItem(uint32_t key, uint32_t value);
  uint32_t GetItem(uint32_t key);
  uint32_t Size();
 private:
  Entry* entry_;
  uint32_t arraySize_{64};
  std::atomic<uint32_t> count_{0};

  DISALLOW_COPY_AND_ASSIGN(HashTable);
};

#endif // __HASH_TABLE_H_
