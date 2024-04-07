///
/// @file       tree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       March 31, 2024
/// @version    0.2
/// @brief      The father class of all trees.
///

template <typename Type>
class tree {
public:
    virtual void clear() = 0;
    virtual void remove(Type toRemove, int position) = 0;
    virtual void traverse() const = 0;
    virtual bool empty() const = 0;
    virtual Type root(Type flag) const = 0;
    virtual Type parent(Type child, Type flag) const = 0;
    virtual Type child(Type parent, int position, Type flag) = 0;
};
