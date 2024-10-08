#pragma once

#include <stdio.h>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace ly
{
template<typename T>
using unique = std::unique_ptr<T>;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T>
using weak = std::weak_ptr<T>;

template<typename T>
using List = std::vector<T>;

template<typename KeyType, typename valType, typename pr = std::less<KeyType>>
using Map = std::map<KeyType, valType, pr>;

template<typename KeyType, typename valType, typename hasher = std::hash<KeyType>>
using Dictionary = std::unordered_map<KeyType, valType, hasher>;

template<typename T>
using Set = std::unordered_set<T>;

using uint8 = unsigned char;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}