#include <iostream>
#include <string>
#include "tiny.hpp"

struct Key {
    int value = 199;
};

int main(int argc, char *argv[])
{
    tiny::tiny_ptr<int> test_1 = tiny::make_ptr<int>(199);

    tiny::tiny_ptr<Key> test_2(new Key);
    tiny::tiny_ptr<Key> test_3 = test_2;
    tiny::tiny_ptr<Key> test_4(test_3);

    tiny::tiny_ptr<int> test_5(new int(200));

    std::cout << test_2.use_count() << std::endl
              << (*test_2).value << std::endl
              << test_2->value << std::endl
              << (*test_2.get()).value << std::endl;
    
    test_1.reset();
    test_1.reset(new int(299));
    test_1.swap(test_5);
    
    std::cout << *test_1 << std::endl;
}