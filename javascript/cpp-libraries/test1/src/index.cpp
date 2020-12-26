// https://github.com/nodejs/node-addon-api#api
#include <napi.h>
#include <string>
#include "greeting.h"
using namespace std;

Napi::String greetHello (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    string result = helloUser ("Adish");
    return Napi::String::New(env, result);
}

Napi::Number find5 (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, 77);
}

Napi::Number find6 (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Array a = info[0].As<Napi::Array>();
    int value = info[1].As<Napi::Number>();
    int result = 0;
    for (unsigned int i = 0; i < a.Length(); ++i) {
        Napi::Value v = a[i];
        int current = (int) v.As<Napi::Number>();
        if (current == value) ++result;
    }
    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "greetHello"),
        Napi::Function::New(env, greetHello)
    );
    exports.Set(
        Napi::String::New(env, "find5"),
        Napi::Function::New(env, find5)
    );
    exports.Set(
        Napi::String::New(env, "find6"),
        Napi::Function::New(env, find6)
    );
    return exports;
}

NODE_API_MODULE(greet, Init);
