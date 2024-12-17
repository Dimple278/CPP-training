#include <iostream>
#include "shared.cpp" 

int main() {
    // Create a SharedPointer
    SharedPointer<int> sp1(new int(42));
    std::cout << "sp1 value: " << *sp1 << ", use count: " << sp1.use_count() << std::endl;

    // Copy the SharedPointer
    SharedPointer<int> sp2 = sp1;
    std::cout << "After copying sp1 to sp2, sp1 use count: " << sp1.use_count() << ", sp2 use count: " << sp2.use_count() << std::endl;

    {
        // Create another SharedPointer within a scope
        SharedPointer<int> sp3 = sp1;
        std::cout << "After copying sp1 to sp3, sp1 use count: " << sp1.use_count() << ", sp3 use count: " << sp3.use_count() << std::endl;
    } // sp3 goes out of scope here

    std::cout << "After sp3 goes out of scope, sp1 use count: " << sp1.use_count() << ", sp2 use count: " << sp2.use_count() << std::endl;

    // Move the SharedPointer
    SharedPointer<int> sp4 = std::move(sp2);
    std::cout << "After moving sp2 to sp4, sp4 use count: " << sp4.use_count() << ", sp2 use count: " << sp2.use_count() << std::endl;

    return 0;
}
