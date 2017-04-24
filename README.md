# LinkedList

This linkedlist class uses is for C++14 compiler. This linkedList uses the smart pointer so the overhead of deletion is not necessary. In addition this linked list implements move semantics and copy-and-idiom for performance inhancement

# Usage
using namespace myLinkedList;//for the namespace
linkedList<T> l1;
In order to add the item
l1.addItem(Item1);

In order to prints all the item in the linkedlist
l1.printItems();

To romove from head
l1.removeFromHead()

To use the move constructors
linkedList<T> l2(std::move(l1));
