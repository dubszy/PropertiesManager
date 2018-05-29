#ifndef _PROPERTY_HPP_
#define _PROPERTY_HPP_

#include <algorithm>
#include <string>
#include <typeinfo>

using namespace std;

class Property {

public:
    Property(string key, string value);

    string key();
    string value();
    bool valueAsBool();

    template <typename T>
    T valueAsNumber() {
        T value;
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wformat"
        sscanf(key_.c_str(), ((isUnsigned<T>()) ? "%llu" : "%lld"), &value);
        #pragma GCC diagnostic pop
        return value;
    }

    static Property *emptyProperty();

private:
    Property() {};

    Property(const Property&);
    Property& operator=(const Property&);

    string key_;
    string value_;

    template <typename T>
    bool isUnsigned() {
        return  typeid(T) == typeid(unsigned char) ||
                typeid(T) == typeid(unsigned short) ||
                typeid(T) == typeid(unsigned int) ||
                typeid(T) == typeid(unsigned long) ||
                typeid(T) == typeid(unsigned long long);
    }
};

#endif /* _PROPERTY_HPP_ */
