//
//  10_simple_deque.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/18/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

using namespace std;

template<typename T>
class simple_deque {
public:
    simple_deque(size_t chunkSize) {
        this->chunkSize = chunkSize;
        appendNewChunk();
    }
    
    void push_back(const T element) {
        size_t chunkOrdinal = getLastChunkOrdinal();
        size_t elementOffset = getNewElementOffset();
        
        if (chunkOrdinal != 0 && elementOffset == 0) {
            appendNewChunk();
        }
        
        chunks[chunkOrdinal][elementOffset] = element;
        
        size_++;
    }
    
    void push_front(const T element) {
        if (shift == 0) {
            shift = chunkSize - 1;
            prependNewChunk();
        } else {
            shift--;
        }
        
        chunks[0][shift] = element;
        
        size_++;
    }
    
    void pop_back() {
        if (size_ == 0) {
            return;
        }
        
        eraseBackChunkAndUpdateShift();
    }
    
    void pop_front() {
        if (size_ == 0) {
            return;
        }
        
        eraseFrontChunkAndUpdateShift();
    }
    
    void insert(size_t index, const T element) {
        if (index == 0) {
            push_front(element);
            return;
        }
        
        if (index < size_ / 2) {
            insertFirstHalf(index, element);
        } else {
            insertSecondHalf(index, element);
        }
        
        size_++;
    }
    
    void remove(size_t index) {
        if (size_ == 0) {
            return;
        }
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        if (index == size_ - 1) {
            pop_back();
            return;
        }
        
        if (index < size_ / 2) {
            removeFirstHalf(index);
        } else {
            removeSecondHalf(index);
        }
        
        //size_--; //is done in each method ('removeFirstHalf', 'removeSecondHalf') separately
    }
    
    T& operator[](size_t i) {
        size_t chunkOrdinal = (shift + i) / chunkSize;
        size_t elementOffset = (shift + i) % chunkSize;
        
        return chunks[chunkOrdinal][elementOffset];
    }
    
    T& back() {
        return chunks[getLastChunkOrdinal()][getLastElementOffset()];
    }
    
    T& front() {
        return chunks[0][shift + 1];
    }
    
    size_t size() {
        return size_;
    }

private:
    vector<int*> chunks;
    size_t size_ = 0;
    size_t shift = 0;
    size_t chunkSize;
    
    void appendNewChunk() {
        chunks.push_back(new T[chunkSize]);
    }
    
    void prependNewChunk() {
        chunks.insert(begin(chunks), new T[chunkSize]);
    }
    
    size_t getLastChunkOrdinal() {
        return (shift + size_) / chunkSize;
    }
    
    size_t getNewElementOffset() {
        return (shift + size_) % chunkSize;
    }
    
    size_t getLastElementOffset() {
        return (shift + size_) % chunkSize;
    }
    
    size_t getChunkOrdinalByIndex(size_t i) {
        return (shift + i) / chunkSize;
    }
    
    size_t getElementOffsetByIndex(size_t i) {
        return (shift + i) % chunkSize;
    }
    
    bool isLastChunkEmpty() {
        size_t realIndex = size_ - (chunkSize - shift);
        return realIndex % chunkSize == 0;
    }
    
    bool isFirstChunkEmpty() {
        return shift == chunkSize - 1;
    }
    
    void eraseFrontChunkAndUpdateShift() {
        if (isFirstChunkEmpty()) {
            chunks.erase(begin(chunks));
        }
        
        shift++;
        shift %= chunkSize;
        size_--;
    }
    
    void eraseBackChunkAndUpdateShift() {
        size_--;
        
        if (isLastChunkEmpty()) {
            chunks.pop_back();
        }
    }
    
    void insertFirstHalf(size_t index, const T& element) {
        index--;
        
        if (shift == 0) {
            prependNewChunk();
        }
        
        size_t chunkOrdinal = getChunkOrdinalByIndex(index);
        size_t elementOffset = getElementOffsetByIndex(index);
        
        T previousOverflowElement = NULL;
        T currentOverflowElement = NULL;
        
        ///copy elements in a chunk, where element is inseretd
        previousOverflowElement = chunks[chunkOrdinal][0];
        for (size_t j = 0; j < elementOffset; ++j) {
            chunks[chunkOrdinal][j] = chunks[chunkOrdinal][j + 1];
        }
        chunks[chunkOrdinal][elementOffset] = element;
        ///////////////////////////////////////////////////////
        
        if (chunkOrdinal == 0) {
            shift--;
            return;
        }
        
        ///copy elements in chunks in between
        for (size_t j = chunkOrdinal; j > 0; --j) {
            size_t m = j - 1;
            currentOverflowElement = chunks[m][0];
            
            for (size_t n = 0; n < chunkSize; ++n) {
                chunks[m][n] = chunks[m][n + 1];
            }
            
            chunks[m][chunkSize - 1] = previousOverflowElement;
            previousOverflowElement = currentOverflowElement;
            currentOverflowElement = NULL;
        }
        ///////////////////////////////////////////////////////
        
        shift--;
    }
    
    void insertSecondHalf(size_t index, const T& element) {
        if ((shift + size_) % chunkSize == 0) {
            appendNewChunk();
        }
        
        size_t chunkOrdinal = getChunkOrdinalByIndex(index);
        size_t elementOffset = getElementOffsetByIndex(index);
        
        T previousOverflowElement = NULL;
        T currentOverflowElement = NULL;
        
        ///copy elements in a chunk, where element is inseretd
        previousOverflowElement = chunks[chunkOrdinal][chunkSize - 1];
        for (size_t j = chunkSize - 1; j != elementOffset; --j) {
            chunks[chunkOrdinal][j] = chunks[chunkOrdinal][j - 1];
        }
        chunks[chunkOrdinal][elementOffset] = element;
        ///////////////////////////////////////////////////////
        
        
        ///copy elements in chunks in between
        for (size_t j = chunkOrdinal + 1; j < chunks.size(); ++j) {
            currentOverflowElement = chunks[j][chunkSize - 1];
            
            for (size_t k = chunkSize - 1; k != 0; k--) {
                chunks[j][k] = chunks[j][k - 1];
            }
            
            chunks[j][0] = previousOverflowElement;
            previousOverflowElement = currentOverflowElement;
            currentOverflowElement = NULL;
        }
        ///////////////////////////////////////////////////////
    }
    
    void removeFirstHalf(size_t index) {
        size_t chunkOrdinal = getChunkOrdinalByIndex(index);
        size_t elementOffset = getElementOffsetByIndex(index);
        
        T previousOverflowElement = NULL;
        T currentOverflowElement = NULL;
        
        for (size_t i = 0; i <= chunkOrdinal; ++i) {
            currentOverflowElement = chunks[i][chunkSize - 1];
            
            size_t kStart = i == chunkOrdinal ? elementOffset + 1 : chunkSize;
            for (size_t k = kStart; k != 1; --k) {
                size_t j = k - 1;
                
                chunks[i][j] = chunks[i][j - 1];
            }
            
            chunks[i][0] = previousOverflowElement;
            previousOverflowElement = currentOverflowElement;
            currentOverflowElement = NULL;
        }
        
        eraseFrontChunkAndUpdateShift();
    }
    
    void removeSecondHalf(size_t index) {
        size_t chunkOrdinal = getChunkOrdinalByIndex(index);
        size_t elementOffset = getElementOffsetByIndex(index);
        
        T previousOverflowElement = NULL;
        T currentOverflowElement = NULL;
        
        for (size_t k = chunks.size(); k != chunkOrdinal; --k) {
            size_t i = k - 1;
            currentOverflowElement = chunks[i][0];
            
            size_t jStart = i == chunkOrdinal ? elementOffset : 0;
            for (size_t j = jStart; j < chunkSize; ++j) {
                chunks[i][j] = chunks[i][j + 1];
            }
            
            chunks[i][chunkSize - 1] = previousOverflowElement;
            previousOverflowElement = currentOverflowElement;
            currentOverflowElement = NULL;
        }
        
        eraseBackChunkAndUpdateShift();
    }
};

void printAll(simple_deque<int>& d) {
    cout << endl;
    
    for (size_t i = 0; i < d.size(); ++i) {
        cout << d[i] << " ";
    }
    
    cout << endl;
}

void testPushFrontBack(simple_deque<int>& d) {
    d.push_back(1);
    d.push_back(2);
    d.push_back(9);
    d.push_front(-1);
    printAll(d);
}

void testInsertFirstLast(simple_deque<int>& d) {
    d.insert(0, -2);
    d.insert(0, -3);
    printAll(d);
    
    d.insert(d.size() - 1, 4);
    printAll(d);

    d.insert(d.size() - 1, 5);
    printAll(d);

    d.insert(d.size() - 1, 6);
    printAll(d);

    d.insert(5, 3);
    printAll(d);

    d.insert(d.size() - 1, 7);
    printAll(d);

    d.insert(d.size() - 1, 8);
    printAll(d);

    d.insert(6, 40);
    printAll(d);

    for (size_t i = 0; i < 25; i++) {
        d.push_back(i + 10);
    }
    printAll(d);
    
    d.insert(d.size() / 2 + 1, 160);
    printAll(d);
}

void testInsertFirstHalf(simple_deque<int>& d) {
    d.insert(3, 0);
    printAll(d);
    
    d.insert(12, 80);
    printAll(d);
}

void testPop(simple_deque<int>& d) {
    cout << endl << "push" << endl;
    
    d.pop_front();
    printAll(d);
    
    d.pop_front();
    printAll(d);
    
    d.pop_front();
    printAll(d);
    
    d.pop_front();
    printAll(d);
    
    d.pop_front();
    printAll(d);
    
    d.push_front(-100500);
    printAll(d);
    
    cout << endl << "pop back" << endl;
    d.pop_back();
    printAll(d);
    
    d.pop_back();
    printAll(d);
    
    d.pop_back();
    printAll(d);
    
    d.pop_back();
    printAll(d);
    
    d.pop_back();
    printAll(d);
}

void testRemove(simple_deque<int>& d) {
    cout << "remove" << endl;
    cout << "[23]=" << d[23] << endl;
    d.remove(23);
    printAll(d);
    
    cout << "[25]=" << d[25] << endl;
    d.remove(25);
    printAll(d);
    
    cout << "[18]=" << d[18] << endl;
    d.remove(18);
    printAll(d);
    
    cout << "[2]=" << d[2] << endl;
    d.remove(2);
    printAll(d);
    
    cout << "[7]=" << d[7] << endl;
    d.remove(7);
    printAll(d);
}

int main10() {
    simple_deque<int> d(5);
    
    testPushFrontBack(d);
    testInsertFirstLast(d);
    testInsertFirstHalf(d);

    testPop(d);
    testRemove(d);
    
    
    
    return 0;
}
