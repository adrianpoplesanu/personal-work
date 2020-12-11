#include <iostream>
using namespace std;

template <typename E>
class stream
{
    virtual void collect(std::function<void(E)> consumer)
    {
        (void)consumer;
    }

    virtual bool anyMatch(std::function<bool(E)> predicate)
    {
        bool found = false;
        collect([predicate, &found](E obj)
            {
                if(predicate(obj))                    
                    found = true;                    
            });

        return found;
    }
};

int main (int argc, char *argv[]) {
    return 0;
}
