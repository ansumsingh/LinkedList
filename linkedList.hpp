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
        node():item(),next(nullptr){}
        node(node &&)=delete;//This implementation does not require copy and move ctor for node
        node(node &other)=delete;
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
    linkedList(linkedList&& ) noexcept; //move constructor
    linkedList(const T& );//creates a new object with item=item
    linkedList& operator=( linkedList);//Implementing copy and swap idiom
    //linkedList& operator=(linkedList &&)=default;//move assignment;

    void addItem(const T& ); //add new item to the tail
    bool removeFromHead() noexcept; //removes the first element;
    bool removeItem(const T &);//Removes the Node with T. Return true if sucessful
    bool returnFirstElement(T& ) noexcept;//If the list is not empty put in the variable passed
    bool printItems() noexcept;
    inline bool isEmpty() noexcept {return head==NULL?true:false;}
    ~linkedList()
    {head.reset();
     }



private:
    shared_ptr<node> head;
    void swap(linkedList<T>&);

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
                //temp2->next= new node(temp->next->item,shared_ptr<node>());
                temp= temp->next;
                temp2=temp2->next;
            }
#ifdef DEBUG_ENABLE
            cout<<"copy ctor called"<<endl;
#endif
}
/*
template<class T>
linkedList<T>::linkedList(linkedList<T> &&other):head(std::move(other.head))
{

}
*/
template<class T>
linkedList<T>& linkedList<T>::operator =( linkedList<T> other)
{
    //Implementing copy assignment
            this->swap(other);
}

template<class T>
void linkedList<T>::swap(linkedList<T>& other)
{   //using std::swap;
    //Implementing swap operation
    shared_ptr<node> temp = other.head;
    other.head = head;
    head =temp;


}

template<class T>
linkedList<T>::linkedList(linkedList &&other)noexcept:head(std::move(other.head))
{
    other.head.reset();
#ifdef DEBUG_ENABLE
    cout<<"move ctor called"<<endl;
#endif
}


template<class T>
linkedList<T>::linkedList(const T &other)
{
    //head = shared_ptr<node >(new node(other,shared_ptr<node>()));
    head = new node(other,shared_ptr<node>(nullptr));
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
bool linkedList<T>::removeFromHead() noexcept
{

    //check if the list is empty
    if(head==NULL)
        return false;

    head = head->next;

    return true;
}

template<class T>
bool linkedList<T>::returnFirstElement(T &returnedElement) noexcept
{
    if(head==NULL)
    {
        return false;
    }
    returnedElement = head->item;
    return true;
}

template<class T>
bool linkedList<T>::printItems() noexcept
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
