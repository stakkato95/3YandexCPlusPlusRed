//
//  33_priority_queue.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/23/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <vector>

#include <string>

#include <exception>

using namespace std;

template<typename T>
struct heap_item {
    T element;
    int priority;
};

template<typename T>
class move_max_heap {
public:
    explicit move_max_heap(size_t capacity) : capacity_ { capacity }, size_  { 0 } {
        data = new heap_item<T>[capacity_];
    }
    
    heap_item<T> getMax() {
        heap_item<T> result = move(data[0]);
        
        data[0] = move(data[size_ - 1]);
        siftDown(0);
        
        --size_;
        
        return result;
    }
    
    void insert(T element, int priority) {
        if (size_ - 1 == capacity_) {
            throw overflow_error("heap is full");
        }
        
        heap_item<T> item;
        item.element = move(element);
        item.priority = priority;
        data[size_++] = move(item);
        
        siftUp(size_ - 1);
    }
    
    heap_item<T> remove(size_t index) {
        checkIndexInBounds(index);
        
        data[index].priority = INT_MAX;
        siftUp(index);
        
        return getMax();
    }
    
    void changePriority(size_t index, int priority) {
        checkIndexInBounds(index);
        
        int oldPriority = data[index].priority;
        data[index].priority = priority;
        
        if (priority > oldPriority) {
            siftUp(index);
        } else {
            siftDown(index);
        }
    }
    
    void sort() {
        for (size_t i = 0; i < capacity_; ++i) {
            data[size_] = getMax();
        }
    }
    
    void printSorted() {
        for (size_t k = capacity_; k != 0; k--) {
            size_t i = k - 1;
//            cout << "[" << data[i].priority << ", " << data[i].element << "]" << endl;
            cout << "[" << data[i].priority << ", " << "str" << "]" << endl;
        }
    }
    
    size_t size() const { return size_; }
    
    size_t capacity() const { return capacity_; }
    
    heap_item<T>& operator[](size_t index) const {
        checkIndexInBounds(index);
        return data[index];
    }
    
private:
    size_t capacity_;
    size_t size_;
    heap_item<T>* data;
    
    void siftDown(size_t index) {
        size_t leftChildIndex = getLeftChild(index);
        size_t rightChildIndex = getRightChild(index);
        
        size_t newIndex = index;
        if (leftChildIndex < size_ && data[leftChildIndex].priority > data[index].priority) {
            newIndex = leftChildIndex;
        }
        if (rightChildIndex < size_ && data[rightChildIndex].priority > data[newIndex].priority) {
            newIndex = rightChildIndex;
        }
        
        if (newIndex != index) {
            swap(index, newIndex);
            siftDown(newIndex);
        }
    }
    
    void siftUp(size_t index) {
        if (index == 0) {
            return;
        }
        
        size_t parent_index = getParent(index);
        
        while (data[parent_index].priority < data[index].priority) {
            swap(parent_index, index);
            
            index = parent_index;
            if (index == 0) {
                break;
            }
            parent_index = getParent(index);
        }
    }
    
    void swap(size_t index1, size_t index2) {
        heap_item<T> temp = move(data[index1]);
        data[index1] = move(data[index2]);
        data[index2] = move(temp);
    }
    
    size_t getLeftChild(size_t index) const {
        return index * 2 + 1;
    }
    
    size_t getRightChild(size_t index) const {
        return index * 2 + 2;
    }
    
    size_t getParent(size_t index) const {
        return (index - 1) / 2;
    }
    
    void checkIndexInBounds(size_t index) const {
        if (index > size_ - 1) {
            throw invalid_argument("index is too big");
        }
    }
};

ostream& operator<<(ostream& os, const heap_item<ifstream>& item) {
    os << "[" << item.priority << ", " << "stream" << "]";
    return os;
}

ostream& operator<<(ostream& os, const heap_item<string>& item) {
    os << "[" << item.priority << ", " << item.element << "]";
    return os;
}

template<typename T>
void printHeap(const move_max_heap<T>& heap) {
    for (size_t i = 0; i < heap.size(); ++i) {
        cout << heap[i] << endl;
    }
}

void testWithStrings() {
    move_max_heap<string> heap(10);
    heap.insert("f", 12);
    heap.insert("h", 7);
    heap.insert("i", 13);
    heap.insert("e", 11);
    heap.insert("g", 14);
    heap.insert("b", 29);
    heap.insert("c", 18);
    heap.insert("d", 18);
    heap.insert("a", 42);
    heap.insert("j", 10);
    printHeap(heap);

    //    cout << "===============" << endl;
    //    heap.sort();
    //    heap.printSorted();
    
    cout << "===============" << endl;
    heap.changePriority(0, 15);
    printHeap(heap);
    
    cout << "===============" << endl;
    heap.changePriority(6, 16);
    printHeap(heap);
    
    cout << "===============" << endl;
    heap.changePriority(7, 17);
    printHeap(heap);
    
    cout << "===============" << endl;
    heap.remove(4);
    printHeap(heap);
}

//void testWithStreams() {
//    move_max_heap<ifstream> heap(10);
//    heap.insert(ifstream("f"), 12);
//    heap.insert(ifstream("h"), 7);
//    heap.insert(ifstream("i"), 13);
//    heap.insert(ifstream("e"), 11);
//    heap.insert(ifstream("g"), 14);
//    heap.insert(ifstream("b"), 29);
//    heap.insert(ifstream("c"), 18);
//    heap.insert(ifstream("d"), 18);
//    heap.insert(ifstream("a"), 42);
//    heap.insert(ifstream("j"), 10);
//    printHeap(heap);
//
//    cout << "===============" << endl;
//
//    heap.sort();
//    heap.printSorted();
//}

int main33() {
    testWithStrings();
//    testWithStreams();
    
    return 0;
}
