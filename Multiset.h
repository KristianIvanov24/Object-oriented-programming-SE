#pragma once
#include <fstream>

class MultiSet {
public:
    MultiSet(int n, int k);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    void add(int number);
    int  count(int number)  const;
    void print()            const;
    void printMemory()      const;

    void serialize(const char* filename)           const;
    static MultiSet deserialize(const char* filename);

    MultiSet intersection(const MultiSet& other)   const;
    MultiSet difference(const MultiSet& other)     const;
    MultiSet complement()                          const;

private:
    int            m_n;
    int            m_k;
    unsigned char* m_data;
    int            m_dataSize;

    int  getCount(int number)              const;
    void setCount(int number, int count);
    int  maxCount()                        const;

    void copyFrom(const MultiSet& other);
    void free();
};