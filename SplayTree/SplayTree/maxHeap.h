#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <bits/stdc++.h>
using namespace std;

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength){
    if (newLength < 0){
        cout<<"new length must be >= 0"<<endl;
    }
    T* temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

template<class T>
class maxHeap{
    public:
        maxHeap(int initialCapacity = 10);
        ~maxHeap() {delete [] heap;}
        bool empty() const {return heapSize == 0;}
        int size() const {return heapSize;}
        const T& top(){
            if (heapSize == 0){
                cout<<"Error:the heap is empty!"<<endl;
                exit(0);
            }
            return heap[1];
        }
        void pop();
        void push(const T&);
    private:
        int heapSize;
        int arrayLength;
        T *heap;
};

template<class T>
maxHeap<T>::maxHeap(int initialCapacity){
    if (initialCapacity < 1){
        cout << "Initial capacity = " << initialCapacity << " Must be > 0";
        exit(0);
    }
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template<class T>
void maxHeap<T>::push(const T& theElement){
    if (heapSize == arrayLength - 1){
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] < theElement){
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop(){
    if (heapSize == 0){
        cout<<"Error:The heap is empty!"<<endl;
        exit(0);
    }
    heap[1].~T();
    T lastElement = heap[heapSize--];
    int currentNode = 1,
       child = 2;
    while (child <= heapSize){
        if (child < heapSize && heap[child] < heap[child + 1])
            child++;
        if (lastElement >= heap[child])
            break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

#endif // MAXHEAP_H
