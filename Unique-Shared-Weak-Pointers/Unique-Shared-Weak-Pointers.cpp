#include <iostream>
#include <memory>

/*
    std::unique_ptr

    Replacement for auto_ptr which has similar functionality but is more secure.
    It is a container for raw pointers. It prevents copying of its pointer
    (allows only one owner for the pointer.) Any attempt to copy a
    unique_ptr will result in a compilation error.

    unique_ptr can be moved using move semantics to transfer ownership of the
    pointer to another unique_ptr.
*/

/*
    std::shared_ptr

    Like unique_ptr, this is a container for raw pointers. It maintains a 
    reference count of its pointer and all its copies. The counter is
    incremented each time a new pointer points to the resource and 
    decremented when the destructor the object is called.

*/

/*
    std::weak_ptr

    These are created as copies of shared_ptrs. They provide access to an object
    that is owned by one or more shared_ptr instances. The reference count does not
    increment when a weak_ptr is used. It is used in some cases to relieve 
    circular references between shared_ptr instances.

    weak_ptrs do not own and are not counted as references. They only have access
    to the object. 
*/

class Foo
{

public:

    void prnt()
    {
        std::cout << "Foo::prnt()" << std::endl;
    }

};

class Bar
{

public:

    void prnt()
    {
        std::cout << "Bar::prnt()" << std::endl;
    }
};


class FBar
{

public:

    void prnt()
    {
        std::cout << "FooBar::print()" << std::endl;
    }
};

int main()
{
    std::unique_ptr<Foo> p1(new Foo);

    // Get address
    std::cout << p1.get() << "\n\n";

    // move ownership
    std::unique_ptr<Foo> p2 = move(p1);
    p2->prnt();

    // Check address, p1 should be 0x0
    std::cout << p1.get() << std::endl;
    std::cout << p2.get() << "\n\n";

    std::cout << "/*----------------------------------------------*/" << "\n\n";

    std::shared_ptr<Bar> pntr1(new Bar);
    std::shared_ptr<Bar> pntr2(pntr1);

    // Get address, should be the same
    std::cout << pntr1.get() << std::endl;
    std::cout << pntr2.get() << "\n\n";

    // Test shared method
    p1->prnt();
    p2->prnt();

    // Check reference count, should be two
    std::cout << pntr1.use_count() << std::endl;
    std::cout << pntr2.use_count() << std::endl;

    // NULLify pointer
    pntr1.reset();
    std::cout << pntr1.get() << std::endl;

    // Check reference count, should be one
    std::cout << pntr2.use_count() << "\n\n";

    std::cout << "/*----------------------------------------------*/" << "\n\n";

    std::shared_ptr<FBar> pnt1(new FBar);
    std::weak_ptr<FBar> pnt2(pnt1);
    
    // Will allow access to methods
    std::weak_ptr<FBar>::element_type val = *pnt2.lock();

    // Get reference count, should be 1
    std::cout << pnt1.use_count() << std::endl;
    
    // Access FBar method through weak_ptr
    val.prnt();
}
