#ifndef __OBJECTS_H
#define __OBJECTS_H

class AdObject {

};

void Ad_INCREF(AdObject*);
void Ad_DECREF(AdObject*);

void free_memory_AdObject(AdObject*);

#endif