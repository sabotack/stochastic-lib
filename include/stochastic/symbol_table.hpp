#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace stochastic
{
    /* RQ3: Implement a generic symbol table to store and lookup objects of user-defined key and
     * value types. Support failure cases when a) the table does not contain a looked up symbol, b)
     * the table already contains a symbol that is being added. Demonstrate the usage of the symbol
     * table with the reactants (names and initial counts). */
    template <typename Key, typename Value>
    class SymbolTable
    {
        std::map<Key, Value> table{};
        std::set<Key> internalSymbols{};

       public:
        SymbolTable() = default;

        void add(const Key& key, const Value& value, const bool isInternal)
        {
            auto [_, inserted] = table.emplace(key, value);
            if (!inserted) {
                std::ostringstream oss;
                oss << "Key already exists: '" << key << "'";
                throw std::runtime_error(oss.str());
            }

            if (isInternal) {
                internalSymbols.insert(key);
            }
        }

        std::vector<Key> getKeys(bool excludeInternal = false) const
        {
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

                keys.emplace_back(key);
            }
            return keys;
        }

        Value& get(const Key& key)
        {
            if (!table.contains(key)) {
                std::ostringstream oss;
                oss << "Key not found: '" << key << "'";
                throw std::runtime_error(oss.str());
            }
            return table.at(key);
        }

        const Value& get(const Key& key) const
        {
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
}  // namespace stochastic

#endif  // SYMBOL_TABLE_HPP
