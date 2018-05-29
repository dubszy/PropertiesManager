#include <Property.hpp>

#include <algorithm>
#include <string>

using namespace std;

static Property *empty;

Property::Property(string key, string value)
  : key_(key), value_(value) {
    empty = new Property();
    empty->key_ = "";
    empty->value_ = "";
}

string Property::key() {
    return key_;
}

string Property::value() {
    return value_;
}

bool Property::valueAsBool() {
    transform(key_.begin(), key_.end(), key_.begin(), ::tolower);
    return (key_ == "true" || key_ == "t" || key_ == "1");
}

Property *Property::emptyProperty() {
    return empty;
}