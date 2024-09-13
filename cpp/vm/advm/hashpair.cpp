#include "hashpair.h"

HashPair::HashPair() {
	//key = NULL;
	//value = NULL;
}

HashPair::HashPair(AdObject* k, AdObject* v) {
	key = k;
	value = v;
}

HashPair::~HashPair() {
	// TODO: implement this
}

AdObject* HashPair::GetKey() {
	return key;
}

AdObject* HashPair::GetValue() {
	return value;
}