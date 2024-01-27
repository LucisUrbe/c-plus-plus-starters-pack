template <typename Type>
class stack {
public:
    virtual void push(const Type& x) = 0;
    virtual Type pop() = 0;
    virtual Type top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~stack() {}
};
