#include <algorithm>
#include <iostream>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector{
private:
   size_t size_;
   size_t capacity_;
   T* data_;

public:
   Vector() {
      size_ = 0;
      capacity_ = 1;
      data_ = new T[capacity_];
   };

   Vector(size_t size, T value) {
      reserve(size);
      size_ = size;
      for (size_t i = 0; i < size_; ++i)
         data_[i] = value;
   };

   ~Vector() {
      delete[] data_;
   };

   void printVector() {
      for (size_t i = 0; i < size_; ++i) {
         std::cout << data_[i] << " ";
      }
      std::cout << "\n";
   }

   size_t size() const {
      return size_;
   }

   size_t capacity() const {
      return capacity_;
   }

   bool empty() const {
      return size_ == 0;
   }

   void reserve(size_t new_capacity) {
      if (new_capacity <= capacity_) 
         return;

      while(capacity_ <= new_capacity)
         capacity_ *= 2;

      T* new_data = new T[capacity_];
      for (size_t i = 0; i < size_; ++i)
         new_data[i] = std::move(data_[i]);

      delete[] data_;
      data_ = new_data;
   }

   void shrink_to_fit() {
      if (size_ == capacity_)
         return;
      T* new_data = new T[size_];
      for (size_t i = 0; i < size_; ++i)
         new_data[i] = std::move(data_[i]);
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
   }

   T& operator[] (const size_t index){
      return data_[index];
   }

   T& front(){
      if (size_ == 0)
         throw std::out_of_range("Vector is empty");
      return data_[0];
   }

   T& back(){
      if (size_ == 0)
         throw std::out_of_range("Vector is empty");
      return data_[size_ - 1];
   }

   T* data(){
      return data_;
   }

   void push_back(T value){
      reserve(size_ + 1);
      data_[size_] = value;
      size_++;
   }

   T pop_back() {
      if (size_ == 0)
         throw std::out_of_range("Vector is empty");
      T temp = data_[size_ - 1];
      --size_;
      return temp;  
   }

   void clear() {
      size_ = 0;
      delete[] data_;
      data_ = nullptr;
      capacity_ = 1;
   }

   void erase(size_t index){
      if (index >= size_)
         throw std::out_of_range("Index out of range");
      for (size_t i = index; i < size_ - 1; ++i)
         data_[i] = data_[i + 1];
      --size_;
   }

   void erase(size_t start, size_t end){
      if (start >= size_ || end >= size_ || start > end)
         throw std::out_of_range("Index out of range");
      size_t diff = end - start + 1;
      for (size_t i = end + 1; i < size_; ++i)
         data_[i - diff] = data_[i];
      size_ -= diff;
   }

   void insert(size_t index, T value) {
      if (index > size_)
         throw std::out_of_range("Index out of range");
      reserve(size_ + 1);
      for (size_t i = size_; i > index; --i){
         data_[i] = data_[i-1];
      }
      data_[index] = value;
      ++size_;
   }

};
