///
/// @file       stack.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 28, 2024
/// @version    0.2
/// @brief      The father class of all stacks.
///

template <typename Type>
class stack {
public:
    virtual void push(const Type& x) = 0;
    virtual Type pop() = 0;
    virtual Type top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~stack() {}
};
