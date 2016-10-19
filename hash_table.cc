#include "hash_table.h"
#include <assert.h>

inline static uint32_t integerHash(uint32_t h) {
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^- h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}

HashTable::HashTable(const uint32_t arraysize) : arraySize_(arraysize) {
  assert(arraysize > 0);
  entry_  = new Entry[arraySize_];
}

HashTable::~HashTable() {
  delete[] entry_;
}
  
void HashTable::SetItem(uint32_t key, uint32_t value) {
  uint32_t zero = 0;
  for (uint32_t idx = integerHash(key);; ++idx) {
    idx &= arraySize_ - 1;
    uint32_t prevKey = entry_[idx].key.load(std::memory_order_relaxed);
    if (prevKey != key) {
      if (prevKey != 0) {
        continue;
      }
      bool succ = entry_[idx].key.compare_exchange_strong(zero, key, std::memory_order_relaxed);
      if (succ)
          goto out;
      continue;
    }
out:    
    entry_[idx].value.store(value, std::memory_order_relaxed);
    return;
  }
}

uint32_t HashTable::GetItem(uint32_t key) {
  for(uint32_t idx = integerHash(key);; idx++) {
    idx &= arraySize_ - 1;
    uint32_t prevKey = entry_[idx].key.load(std::memory_order_relaxed);
    if (prevKey == key)
      return entry_[idx].value.load(std::memory_order_relaxed);
    
    if (prevKey == 0)
      return 0;
  }
  return 0;
}

