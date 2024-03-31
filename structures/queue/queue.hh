///
/// @file       queue.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       February 4, 2024
/// @version    0.2
/// @brief      The father class of all queues.
///

template <typename Type>
class queue {
    public:
        virtual void push(const Type& toPush) = 0;
        virtual Type pop() = 0;
        virtual Type front() const = 0;
        virtual Type back() const = 0; // STL?
        virtual bool empty() const = 0;
        virtual ~queue() {}
};
