#ifndef DATA_STRUCTURES_HASH_TABLE_HPP
#define DATA_STRUCTURES_HASH_TABLE_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <cstring>

// Hash table using bucket chaining
class HashEntry {
 public:
  std::string key_{};
  int value_{};
  std::shared_ptr<HashEntry> next_entry_{};

  HashEntry() : key_{}, value_{-1}, next_entry_{nullptr} {}

  explicit HashEntry(std::string_view key, int value)
      : key_{key}, value_{value}, next_entry_{nullptr} {}
};

template <int S>
class HashTable final : public HashEntry {
 private:
  std::vector<std::shared_ptr<HashEntry>> bucket_{};
  int bucket_slots_{};
  int hash_table_size_{};

 public:
  HashTable()
      : bucket_slots_{S},
        hash_table_size_{0} {
    bucket_.resize(S);
  }
  // Reference: https://en.wikipedia.org/wiki/MurmurHash
  inline uint32_t murmur_32_scramble(uint32_t k)
  {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
  }

  inline uint32_t murmur3_32(const char *key, size_t len, uint32_t seed)
  {
    uint32_t h = seed;
    uint32_t k;
    /* Read in groups of 4. */
    for (size_t i = len >> 2; i; i--)
    {
      // Here is a source of differing results across endiannesses.
      // A swap here has no effects on hash properties though.
      std::memcpy(&k, key, sizeof(uint32_t));
      key += sizeof(uint32_t);
      h ^= murmur_32_scramble(k);
      h = (h << 13) | (h >> 19);
      h = h * 5 + 0xe6546b64;
    }
    /* Read the rest. */
    k = 0;
    for (size_t i = len & 3; i; i--)
    {
      k <<= 8;
      k |= key[i - 1];
    }
    // A swap is *not* necessary here because the preceding loop already
    // places the low bytes in the low places according to whatever endianness
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);

    /* Finalize. */
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
  }

  [[nodiscard]] inline int get_size() const noexcept {
    return hash_table_size_;
  }

  [[nodiscard]] inline bool empty() const noexcept { return get_size() == 0; }

  [[nodiscard]] inline int get_index(std::string_view key) {
    auto hash = murmur3_32(key.data(), key.size(), 1);
    return hash % bucket_slots_;
  }

  // O(1)
  inline void insert(std::string_view key, int value) {
    int hash_idx = get_index(key);

    if (bucket_.at(hash_idx) == nullptr) {
      bucket_.at(hash_idx) = std::make_shared<HashEntry>(key, value);
      hash_table_size_++;
    } else {
      // find next free space
      auto entry = bucket_.at(hash_idx);
      while (entry->next_entry_ != nullptr) {
        entry = entry->next_entry_;
      }

      entry->next_entry_ = std::make_shared<HashEntry>(key, value);
      hash_table_size_++;
    }
  }

  inline void resize() {
    bucket_slots_ *= 2;
    std::vector<std::shared_ptr<HashEntry>> resized_bucket(bucket_slots_, nullptr);

    uint32_t hash_idx{};
    std::shared_ptr<HashEntry> new_entry{};
    std::shared_ptr<HashEntry> orig_entry{};

    for (int i = 0; i < bucket_slots_ / 2; i++) {
      if (bucket_[i] != nullptr) {
        orig_entry = bucket_.at(i);
        while (orig_entry != nullptr) {
          hash_idx = get_index(orig_entry->key_);
          if (resized_bucket.at(hash_idx) == nullptr) {
            resized_bucket.at(hash_idx) = std::make_shared<HashEntry>(orig_entry->key_, orig_entry->value_);
          } else {
            // find next free space
            new_entry = resized_bucket.at(hash_idx);
            while (new_entry->next_entry_ != nullptr) {
              new_entry = new_entry->next_entry_;
            }

            new_entry->next_entry_ = std::make_shared<HashEntry>(orig_entry->key_, orig_entry->value_);
          }
          orig_entry = orig_entry->next_entry_;
        }
      }
    }

    // update bucket to new resized bucket
    bucket_ = resized_bucket;
  }

  // O(n)
  [[nodiscard]] inline int search(std::string_view key) {
    int hash_idx = get_index(key);
    if (bucket_.empty() || bucket_[hash_idx] == nullptr) {
      return -1;
    }

    if (bucket_[hash_idx]->key_ == key) {
      return bucket_[hash_idx]->value_;
    } else {
      // find the next space
      auto entry = bucket_[hash_idx];
      while (entry->next_entry_ != nullptr) {
        if (entry->next_entry_->key_ == key) {
          return entry->next_entry_->value_;
        }
        entry = entry->next_entry_;
      }
      std::cout << "Value not found!" << std::endl;
      return -1;
    }
  }

  // O(n)
  void delete_key(std::string_view key) {
    // get the index of the key
    int hash_idx = get_index(key);

    if (bucket_[hash_idx] == nullptr) {
      std::cerr << "Value to be deleted not found!" << std::endl;
      return;
    }

    if (bucket_[hash_idx]->key_ == key) {
      if (bucket_[hash_idx]->next_entry_ != nullptr) {
        bucket_[hash_idx] = bucket_[hash_idx]->next_entry_;
      } else {
        bucket_[hash_idx] = nullptr;
      }
    } else {
      // find next free space
      auto entry = bucket_[hash_idx];
      auto prev_entry = bucket_[hash_idx];

      while (entry != nullptr) {
        if (entry->key_ == key) {
          if (entry->next_entry_ != nullptr) {
            prev_entry->next_entry_ = entry->next_entry_;
            entry = entry->next_entry_;
          } else {
            prev_entry->next_entry_ = nullptr;
            return;
          }
        }
        prev_entry = entry;
        entry = entry->next_entry_;
      }
      std::cerr << "Value to be deleted not found!" << std::endl;
    }
  }

  inline void display() {
    auto temp = std::make_shared<HashEntry>();
    for (int i = 0; i < S; i++) {
      if (bucket_[i] != nullptr) {
        std::cout << "HashIndex : " << i << " ";
        temp = bucket_.at(i);
        while (temp != nullptr) {
          std::cout << "(key = " << temp->key_ << " , value = " << temp->value_
                    << " )";
          temp = temp->next_entry_;
        }
      }
      std::cout << std::endl;
    }
  }
};

#endif  // DATA_STRUCTURES_HASH_TABLE_HPP
