///
/// @file       binaryTree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 7, 2024
/// @version    0.2
/// @brief      The father class of all binary trees.
///

template <typename Type>
class binaryTree {
public:
    virtual Type root(Type flag) const = 0;
    virtual Type parent(Type toFind, Type flag) const = 0;
    virtual Type leftChild(Type toFind, Type flag) const = 0;
    virtual Type rightChild(Type toFind, Type flag) const = 0;
    virtual void clear() = 0;
    virtual void deleteLeft(Type toDelete) = 0;
    virtual void deleteRight(Type toDelete) = 0;
    virtual void preorderTraverse() const = 0;
    virtual void inorderTraverse() const = 0;
    virtual void postorderTraverse() const = 0;
    virtual void levelOrderTraverse() const = 0;
    virtual bool empty() const = 0;
};
