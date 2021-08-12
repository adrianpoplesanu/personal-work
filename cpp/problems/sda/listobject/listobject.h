#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H

template<typename T>
class Ad_List {
private:
    int capacity;
    int size;
    T *data;
public:
    Ad_List();
    ~Ad_List();
    int Size();
    bool IsEmpty();
    T get(int);
    void set(int, T);
    void add(T);
    T remove(int);
};

#endif
