#pragma once

#include <iostream>
#include <assert.h>
#include <vector>

template<class T>
struct Node
{
  Node(T* data, Node* next): _data(data), _next(next){}
  T* _data;
  Node* _next;
};

class Publisher;
class Subscriber;



class Publisher {
public:
    Publisher();

    virtual ~Publisher();

    //added new subscribers 
    virtual void Attach(Subscriber *subscriber);
  
    //remove subscriber
    virtual void Detach(Subscriber *subscriber);
  
  // Action happens : 
  // virtual void Notify() = 0;

/* ========================================================================= *
 * DEBUG 
 * ========================================================================= */

    void print_sub();
    //return total_subs 
    int count_sub();
    int get_id();

protected:
    static bool _debug;
    static int _static_number;
    Node<Subscriber>* _head = nullptr;
    int _total_sub = 0;
    int _id;
  
};

class Subscriber{
public:

    Subscriber();
  
    virtual ~Subscriber();
  
  // Action happens : 
  // virtual void onNotify() {assert(false);};
 
    virtual void Detach_msg();
    virtual void Attach_msg();

    //adds publisher to list of subscriptions
    void add_pub(Publisher& pub);
    //removes subscription to publisher stored at index i
    void remove_pub(int i);
    //finds index pub is stored
    int find_pub(int _id);

    int count_subscriptions();

protected:
    int _id;
    static int _static_number;
    static bool _debug;
    std::vector<Publisher*> _subscribed;
};