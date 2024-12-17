#include <iostream>
#include <atomic>

template <typename T>
class SharedPointer {
public:

    //Constructor
    explicit SharedPointer(T* p = nullptr) : ptr(p), refCount(p ? new std::atomic<int>(1) : nullptr) {}

    //Copy constructor
    SharedPointer(const SharedPointer& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    //Move constructor
    SharedPointer(SharedPointer&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    //Copy assignment
    SharedPointer& operator=(const SharedPointer& other) {
        if (this == &other) return *this;
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        if (refCount) {
            ++(*refCount);
        }
        return *this;
    }

    //Move assignment
    SharedPointer& operator=(SharedPointer&& other) noexcept {
        if (this == &other) return *this;
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        other.ptr = nullptr;
        other.refCount = nullptr;
        return *this;
    }

    //Deconstructor
    ~SharedPointer() {
        release();
    }

    //Getters and operators
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    //Reference count
    int use_count() const {
        return refCount ? refCount->load() : 0;
    }

private:
    T* ptr = nullptr;
    std::atomic<int>* refCount = nullptr;

    void release() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
            ptr = nullptr;
            refCount = nullptr;
        }
    }
};
