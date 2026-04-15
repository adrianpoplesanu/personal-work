#pragma once

#include <cstddef>
#include <pthread.h>

// Starts fn(arg) on a new pthread with at least stack_bytes stack (best-effort).
// On success, writes the thread id to *out and returns true.
bool start_pthread_with_stack(size_t stack_bytes, void* (*fn)(void*), void* arg, pthread_t* out);
