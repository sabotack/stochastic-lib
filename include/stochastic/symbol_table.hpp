#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace stochastic {
    template <typename Key, typename Value>
    class SymbolTable {
        std::map<Key, Value> table{};
        std::set<Key> internalSymbols{};

        public:
        SymbolTable() = default;

        void add(const Key& key, const Value& value, const bool isInternal) {
            auto [_, inserted] = table.emplace(std::pair<Key, Value>(key, value));
            if (!inserted) {
                std::ostringstream oss;
                oss << "Key already exists: '" << key << "'";
                throw std::runtime_error(oss.str());
            }

            if (isInternal) {
                internalSymbols.insert(key);
            }
        }

        std::vector<Key> getKeys(bool excludeInternal = false) const {
            std::vector<Key> keys;

            if (excludeInternal) {
                keys.reserve(table.size() - internalSymbols.size());
            } else {
                keys.reserve(table.size());
            }

            for (const auto& [key, _] : table) {
                if (excludeInternal && internalSymbols.contains(key)) {
                    continue;
                }

                keys.push_back(key);
            }
            return keys;
        }

        Value& get(const Key &key) {
            if (!table.contains(key)) {
                std::ostringstream oss;
                oss << "Key not found: '" << key << "'";
                throw std::runtime_error(oss.str());
            }
            return table.at(key);
        }

        const Value& get(const Key &key) const {
            if (!table.contains(key)) {
                std::ostringstream oss;
                oss << "Key not found: '" << key << "'";
                throw std::runtime_error(oss.str());
            }
            return table.at(key);
        }

        bool contains(const Key& key) const { return table.contains(key); }
        bool isInternal(const Key& key) const { return internalSymbols.contains(key); }
    };
}


#endif //SYMBOL_TABLE_HPP
