#pragma once

class NumberSeries {
public:
    NumberSeries(int startValue, int (*func)(int));
    NumberSeries(const NumberSeries& other);
    NumberSeries& operator=(const NumberSeries& other);
    ~NumberSeries();

    int  get(int index);
    bool contains(int value);

    void setStartValue(int startValue);
    void setTransitionFunc(int (*func)(int));

private:
    int  m_startValue;
    int  (*m_func)(int);

    int* m_cache;
    int  m_cacheSize;
    int  m_capacity;

    void grow();
    void resetCache();
    void copyFrom(const NumberSeries& other);
    void free();
};