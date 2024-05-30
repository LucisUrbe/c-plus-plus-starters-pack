///
/// @file       dynamicSearchTable.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       May 30, 2024
/// @version    0.2
/// @brief      The father class of all dynamic search tables.
///

#include "set.hh"

template <typename KEY, typename VALUE>
class dynamicSearchTable {
public:
    virtual SET<KEY, VALUE>* find(const KEY& toFind) const = 0;
    virtual void insert(const SET<KEY, VALUE>& toInsert) = 0;
    virtual void remove(const KEY& toRemove) = 0;
    virtual ~dynamicSearchTable() {};
};
