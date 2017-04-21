//This uses the linkedList using C++14
//and shared_ptr
//developed by Ansu Man Singh

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

//#define DEBUG_ENABLE ;


#include<iostream>
#include<memory>

namespace myLinkedList {

using namespace std;
//using namespace boost;
template<class T>
class linkedList{

    //using namespace std;

    struct node{
        T item;
        shared_ptr<node> next;
        node():next(NULL),item(){}
        node(const T& itemIP,shared_ptr<node> nextIP):item(itemIP),next(nextIP){}
        ~node()
        {
#ifdef DEBUG_ENABLE
            std::cout<<std::endl<<item<<"is deleted.";
#endif
        }
    };
public:
    linkedList():head(){}
    linkedList(const linkedList&);//implements Deep copy
    linkedList(linkedList&& ) =default; //move constructor
    linkedList(const T& );//creates a new object with item=item
    linkedList& operator=(const linkedList&);//Deep copy assignment
    linkedList& operator=(linkedList &&)=default;//move assignment;

    void addItem(const T& ); //add new item to the tail
    bool removeFromHead(); //removes the first element;
    bool removeItem(const T &);
    bool returnFirstElement(T& );//If the list is not empty put in the variable passed
    bool printItems();
    inline bool isEmpty(){return head==NULL?true:false;}
    ~linkedList()
    {head.reset();
     }

private:
    shared_ptr<node> head;

};

template<class T>
linkedList<T>::linkedList(const linkedList<T> &other)
{
    //Implementing deep copy
            shared_ptr<node> temp(other.head);
            head= shared_ptr<node>(new node(temp->item,shared_ptr<node>()));
            shared_ptr<node> temp2(head);
            while(temp->next!=NULL)
            {
                temp2->next= shared_ptr<node>(new node(temp->next->item,shared_ptr<node>()));
                temp= temp->next;
                temp2=temp2->next;
            }
}
/*
template<class T>
linkedList<T>::linkedList(linkedList<T> &&other):head(std::move(other.head))
{

}
*/
template<class T>
linkedList<T>& linkedList<T>::operator =(const linkedList<T> &other)
{
    //Implementing deep copy
            shared_ptr<node> temp(other.head);
            head= shared_ptr<node>(new node(temp->item,shared_ptr<node>()));
            shared_ptr<node> temp2(head);
            while(temp->next!=NULL)
            {
                temp2->next= shared_ptr<node>(new node(temp->next->item,shared_ptr<node>()));
                temp= temp->next;
                temp2=temp2->next;
            }
}

template<class T>
linkedList<T>::linkedList(const T &other)
{
    head = shared_ptr<node >(new node(other,shared_ptr<node>()));
}

template<class T>
bool linkedList<T>::removeItem(const T& item)
{
    shared_ptr<node> prev,next;
    next = head;
    prev = head;
    //First check if the linked list is itself empty
    if(next==NULL)
        return false;
    //Check if the if the first element has the inte
    if(next->item==item)
    {
        head=head->next;
        return true;
    }

    while(next->next!=NULL)
    {
        //if the item is found in the next ptr then point the next pointer to the next item
        //Due to RAII the original next item is deleted automatically
        if(next->next->item==item)
        {
            next->next = next->next->next;
            //next.reset();
            return true;
        }

        next =next->next;//advance in the list
    }

    return false;


}

template<class T>
void linkedList<T>::addItem(const T& input)
{
    if(head==NULL)
    { shared_ptr<node> temp =shared_ptr<node>(new node(input,shared_ptr<node>()));
      head=  temp;
      head->next=shared_ptr<node>();
    }
    else
    {
        shared_ptr<node> temp = head;
        //First go to the tail of the linked list

        while(temp->next!=NULL)
        {
            temp=temp->next;

        }
        temp->next=  shared_ptr<node>(new node(input,shared_ptr<node>()));
        //temp->next->next=NULL;
    }
}

template<class T>
bool linkedList<T>::removeFromHead()
{

    //check if the list is empty
    if(head==NULL)
        return false;

    head = head->next;

    return true;
}

template<class T>
bool linkedList<T>::returnFirstElement(T &returnedElement)
{
    if(head==NULL)
    {
        return false;
    }
    returnedElement = head->item;
    return true;
}

template<class T>
bool linkedList<T>::printItems()
{
    shared_ptr<node > printNode = head;
    if(printNode==NULL)
    {	std::cout<<"\nlist empty";
        return false;
    }
    std::cout<<"\n Printing nodes";
    while((printNode!=NULL))
    {
        std::cout<<"->"<<printNode->item;
        printNode= printNode->next;
    }
    return true;
}

}



#endif
