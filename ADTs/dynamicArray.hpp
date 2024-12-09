#ifndef dynamicArray_hpp
#define dynamicArray_hpp

#include <stdexcept>
#include <iostream>

template <typename T>
class dynamicArray {
public:
    // Constructors
    dynamicArray() : size_(0), capacity_(4) { // Inicializa con una capacidad mínima
        data_ = new T[capacity_]; // Asignar memoria aquí
    }

    dynamicArray(unsigned int size) : size_(size), capacity_(size + 4) { // Ajuste en la capacidad
        data_ = new T[capacity_];
    }

    dynamicArray(const T& value, int size) : size_(size), capacity_(size + 4) {
        data_ = new T[capacity_];
        for(unsigned int i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    dynamicArray(const dynamicArray& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ~dynamicArray() {
        delete[] data_; // Simplificado
    }

    unsigned int size() const {
        return size_;
    }

    unsigned int capacity() const {
        return capacity_;
    }

    // Access the front of the array
    T& front()
    {
        return data_[0];
    } 

    const T& front() const
    {
        return data_[0];
    }

    // Access the back of the array
    T& back()
    {
        return data_[size_ - 1];
    }

    const T& back() const
    {
        return data_[size_ - 1];
    }

    // Access an element of the array with bond checking
    T& at(unsigned int index)
    {
        if (index >= size_){
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(unsigned int index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Access an element of the array without bond checking
    T& operator[](unsigned int index)
    {
        return data_[index];
    }

    const T& operator[](unsigned int index) const
    {
        return data_[index];
    }

    // Checks if the array is empty
    bool empty() const
    {
        return size_ == 0;
    }
    
    // Fills the array with a value
    void fill(const T& value)
    {
        for(unsigned int i = 0; i < size_; ++i){
            data_[i] = value;
        }
    }

    // Finds the index of the value given
    unsigned int find(const T& value)
    {
        int index = -1;

        for(int i = 0; i < (int)size_; ++i){
            if(data_[i] == value){
                index = i;
                break;
            }
        }

        return index;

    }

    // Clear the array and deallocates the memory
    void clear()
    {
        if(data_ != nullptr)
            delete[] data_;

        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    // Erase an element of the array from a specific positions
    void erase(unsigned int index)
    {
        if (index >= size_) {
        throw std::out_of_range("Index out of range");
        }

        for (unsigned int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        size_--;

    }

    // Add an element to the array at a specific position
    void insert(unsigned int index, const T& value) {
        if(index > size_) {
            throw std::out_of_range("Index out of range");
        }

        // Check if resize is needed before inserting
        if(size_ >= capacity_) {
            resize(capacity_ * 2); // Duplicar la capacidad
        }

        // Desplazar elementos
        for(unsigned int i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        size_++;
    }

    // Inserts a new element at the end of the array
    void pushBack(const T& value) {
        if(size_ >= capacity_) {
            resize(capacity_ * 2); // Duplicar la capacidad
        }
        data_[size_] = value; // Asigna directamente
        size_++;
    }

    // Resize implementation
    void resize(unsigned int newCapacity) {
        T* newData = new T[newCapacity]; // Crear nuevo array

        for(unsigned int i = 0; i < size_; ++i) {
            newData[i] = data_[i]; // Copiar elementos
        }

        delete[] data_; // Liberar memoria anterior
        data_ = newData; // Actualizar el puntero
        capacity_ = newCapacity; // Actualizar capacidad
    }

    // Removes the last element of the array.
    void popBack()
    {
        size_--;
    }

    // Inserts a new element at the front of the array.
    void pushFront(const T& value)
    {
        insert(0,value);
    }

    // Removes the first element of the array.
    void popFront()
    {
        erase(0);
    }

    // Print all the elements of the array
    void print()
    {
        std::cout << std::endl << "dynamic array: ";
        for (unsigned int i = 0; i < size_; ++i){
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    unsigned int size_{0};
    unsigned int capacity_{0}; // Cambia el valor por defecto a 0
    T* data_{nullptr};
};

#endif
