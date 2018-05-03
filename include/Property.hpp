#ifndef _PROPERTY_HPP_
#define _PROPERTY_HPP_

#include <string>

using namespace std;

class Property {

public:
    static Property *empty;

    Property(string key, string value)
      : key_(key), value_(value) {}

    string key() {
        return key_;
    }

    string value() {
        return value_;
    }

    bool valueAsBool() {
        transform(key_.begin(), key_.end(), key_.begin(), ::tolower);
        return (key_.compare("true") == 0 ||
                key_.compare("t") == 0 ||
                key_.compare("1") == 0);
    }

    template <typename T>
    T valueAsNumber() {
        T value;
        sscanf(key_.c_str(), ((isUnsigned<T>()) ? "%llu" : "%lld"), &value);
        return value;
    }

private:
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
