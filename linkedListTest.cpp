#include<iostream>
#include"linkedList.hpp"

int main()
{
    using namespace myLinkedList;
    linkedList<string> l1;
    l1.addItem("Ram");
    l1.addItem("sita");
    l1.printItems();
    //move constructor test
    linkedList<string> l2(std::move(l1));
    l1.printItems();
    l2.printItems();

    //after move assignment
    linkedList<string> l3;
    l3=std::move(l2);
    l2.printItems();
    l3.printItems();

}
