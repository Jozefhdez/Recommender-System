#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include <vector>

template<typename T>
class queueElement
{
    public: 
        T data_;
        double priority_;

        queueElement(const T& value, double pr)
        {
            data_ = value;
            priority_ = pr;
        }

        // Overloading
        
        bool operator < (const queueElement& val2)
        {
            return priority_ < val2.priority_;
        }

        bool operator > (const queueElement& val2)
        {
            return priority_ > val2.priority_;
        }

        bool operator == (const queueElement& val2)
        {
            return priority_ == val2.priority_;
        }
};

template<typename T>
class priorityQueue
{
    public:

        // Constructor
        priorityQueue() = default;

        // Destructor
        ~priorityQueue()
        {
            container_.clear();
        }

        // Returns the top element of the queue
        T& top()
        {
            return container_.front().data_;
        }

        const T& top() const
        {
            return container_.front().data_;
        }

        // Returns the size of the queue
        unsigned int size()
        {
            return container_.size();
        }

        // Checks if the queue is empty
        bool empty()
        {
            return container_.empty();
        }

        // Clears the queue
        void clear()
        {
            container_.clear();
        }

        // Adds a value to the queue taking into account the priority
        void push(const T& value, const int& priority)
        {
            queueElement<T> toAdd(value,priority);
            for(int i = 0; i < container_.size(); ++i){
                if(container_.at(i).priority_ > priority){
                    container_.insert(container_.begin()+i,toAdd);
                    return;
                }
            }   
            container_.push_back(toAdd);
        }

        // Erases the value with the greatest priority
        void pop()
        {
            container_.erase(container_.begin());
        }

    private:

        std::vector<queueElement<T>> container_;
};

#endif