#pragma once

#include <iostream>
#include <assert.h>

template<class T>
struct Node
{
  Node(T* data, Node* next): _data(data), _next(next){}
  T* _data;
  Node* _next;
};

class Subscriber
{
public:

    Subscriber(){
        _id = _static_number++;
    }
  
  virtual ~Subscriber(){}
  
  // Action happens : 
  // virtual void onNotify() {assert(false);};
 
  virtual void Detach_msg(){
      std::cout << "Subscriber " << _id << " is Detaching from Publisher\n";
  }
  
  virtual void Attach_msg(){
      std::cout << "Subscriber " << _id << " is Attaching to Publisher\n";
  }

protected:
    int _id;
    static int _static_number;
    static bool _debug;
};


class Publisher {
public:

    virtual ~Publisher(){
    Node<Subscriber>* here;
        while (_head != nullptr){
            Detach(_head->_data);
        }
    }

    //added new subscribers 
    virtual void Attach(Subscriber *subscriber) {
        ++_total_sub;
        if (_debug) {
            subscriber->Attach_msg();
        }
        Node<Subscriber>* new_n = new Node<Subscriber>(subscriber, _head);
        _head = new_n;
    }
  
    //remove subscriber
    virtual void Detach(Subscriber *subscriber) {
        if (_head == nullptr) {
            return;
        }

        if(_head->_data == subscriber) {
            Node<Subscriber>* here = _head;
            if (_debug) {
                subscriber->Detach_msg();
            }
            --_total_sub;
            _head = _head->_next;
            delete here;
            return;
        }

        Node<Subscriber>* last = _head, 
        *current = _head->_next;

        while (current != nullptr) { 
            if ( current->_data == subscriber ){
                if (_debug)
                    subscriber->Detach_msg();
                --_total_sub;
                last->_next = current->_next;
                delete current;
                return;
            }
            last = current;
            current = last->_next;
        }
  }
  
  // Action happens : 
  // virtual void Notify() = 0;

/* ========================================================================= *
 * DEBUG 
 * ========================================================================= */

    void print_sub() {
        std::cout << "There are " << _total_sub << " subscribers in the list\n";
    }

    //return total_subs 
    int count_sub() {
        return _total_sub;
    }

protected:
    static bool _debug;
    Node<Subscriber>* _head = nullptr;
    int _total_sub = 0;
  
};

