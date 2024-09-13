#ifndef __HASHPAIR_H
#define __HASHPAIR_H

class AdObject; // forward declaration

class HashPair {
public:
    AdObject *key;
    AdObject *value;

    HashPair();
    HashPair(AdObject*, AdObject*);
    ~HashPair();

    AdObject* GetKey();
    AdObject* GetValue();
};

#endif