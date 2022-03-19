#include <jni.h>
#include <iostream>
#include "CppLibrary2.h"

JNIEXPORT void JNICALL Java_CppLibrary2_print(JNIEnv *env, jobject obj) {
    std::cout << "Salut Adi din C++\n";
    return;
}

