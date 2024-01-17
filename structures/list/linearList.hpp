template<typename Type>
class linearList {
    public:
        virtual void insert(int position, const Type &x) = 0;
        virtual void remove(int position) = 0;
        virtual void clear() = 0;
        virtual void traverse() const = 0;
        virtual int length() const = 0;
        virtual int search(const Type &x) const = 0;
        virtual Type visit(int position) const = 0;
        virtual ~linearList() {}
};
