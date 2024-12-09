#ifndef linkedList_hpp
#define linkedList_hpp

#include <iostream>

template <typename T>
class node
{
    public:

        // Properties
        T data;
        node* next;

        // Constructor 
        node(const T& value)
        {
        data = value;
        next = nullptr;
        }
};

template <typename T>
class linkedList
{
    public:

        // Constructor
        linkedList() = default;

        // Destructor
        ~linkedList() 
        {
            clear();
        }

        // Checks if list is empty
        bool empty() const
        {
            return head_ == nullptr;
        }

        // Gets value of the first element in the list
        T& front()
        {
            if (empty()) {
                throw std::out_of_range("List is empty");
            }
            return head_->data;
        }

        const T& front() const
        {
            if (empty()) {
                throw std::out_of_range("List is empty");
            }
            return head_->data;
        }

        // Gets value of the last element in the list
        T& back()
        {
            node<T>* current = head_;
            while(current->next != nullptr){
                current = current->next; 
            }
            return current->data;
        }

        const T& back() const
        {
            node<T>* current = head_;
            while(current->next != nullptr){
                current = current->next; 
            }
            return current->data;
        }

        // Access an element of the list with bond checking
        T& at(unsigned int index)
        {
            if(empty()){
                throw std::out_of_range("List is empty");
            }
            else{
                node<T>* current = head_;
                for(int i = 0; i < index; ++i){
                    current = current->next;
                    if(current == nullptr && i < index){
                    throw std::out_of_range("List is shorter");
                }
                }
                
                return current->data;
            }
            
        }

        const T& at(unsigned int index) const
        {
            if(empty()){
                throw std::out_of_range("List is empty");
            }
            else{
                node<T>* current = head_;
                for(int i = 0; i < index; ++i){
                    current = current->next;
                    if(current == nullptr && i < index){
                    throw std::out_of_range("List is shorter");
                }
                }
                
                return current->data;
            }
            
        }

        // Returns the size of the list
        unsigned int size()
        {
            if(empty()){
                return 0;
            }
            else{
                unsigned int count = 0;
                node<T>* current = head_;
                while(current != nullptr){
                    current = current->next;
                    count++;
                }
                return count;
            }
        } 

        // Clears the list
        void clear()
        {
            node<T>* current = head_;
            while(current != nullptr){
                node<T>* next = current->next;
                delete current;
                current = next;
            }
            head_ = nullptr;
        }

        // Adds an element to the front of the list
        void pushFront(const T& value)
        {
            node<T>* newNode = new node<T>(value);
            newNode->next = head_;
            head_ = newNode;
        }

        // Removes the first element of the list
        void popFront()
        {
            if (empty()) {
                throw std::out_of_range("List is empty");
            }
            else{
                node<T>* newHead = head_->next;
                delete head_;
                head_ = newHead;
            }
        }

        // Adds an element to the back of the list
        void pushBack(const T& value)
        {
            node<T>* newNode = new node<T>(value);
            if(empty()){
                head_ = newNode;
            }
            else{
                node<T>* current = head_;
                while(current->next != nullptr){
                    current = current->next;
                }
                current->next = newNode;
            }
       }

        // Removes the last element of the list
        void popBack()
        {
            if (empty()) {
                throw std::out_of_range("List is empty");
            }
            else if(head_->next == nullptr){
                delete head_;
                head_ = nullptr;
            }
            else{
                node<T>* current = head_;
                while(current->next->next != nullptr){
                    current = current->next;
                }

                delete current->next;
                current->next = nullptr;

            }
        }

        // Inserts a new element after the node given
        void insertAfter(node<T>* Node, const T& value)
        {
            if(Node != nullptr){
                node<T>* newNode = new node<T>(value);
                newNode->next = Node->next;
                Node->next = newNode;

            }
        }

        // Erases an element after the node given
        void eraseAfter(node<T>* Node)
        {
            if (Node != nullptr && Node->next != nullptr) {
                node<T>* toDelete = Node->next;
                Node->next = toDelete->next;
                delete toDelete;
            }
        }

        // Finds the first node of the given value
        node<T>* find(const T& value)
        {
            node<T>* current = head_;

            while(current != nullptr){
                if(current->data == value){
                    return current;
                }
                current = current->next;
            }
            return nullptr;
        }

        // Finds the last node of the given value
        node<T>* findLast(const T& value)
        {
            node<T>* lastNode;
            node<T>* current = head_;

            while(current != nullptr){
                if(current->data == value){
                    lastNode = current;
                }
                current = current->next;
            }
            return lastNode;
        }

        // Prints the values of the list
        void print()
        {
            node<T>* current = head_;
            while(current != nullptr){
                std::cout << current->data << " ";
                current = current->next;
            }
        }

    private:

        node<T>* head_{nullptr};

};

#endif