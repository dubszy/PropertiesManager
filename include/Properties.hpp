#ifndef _PROPERTIES_MANAGER_HPP_
#define _PROPERTIES_MANAGER_HPP_

#include <cstdio>
#include <string>

#include <logger/c++/Logger.hpp>

#include <Property.hpp>

using namespace std;

// TODO: string comparisons should use the ICU library
// TODO: add localization support
class Properties {

public:
    Properties(const char *propPath);

    ~Properties();

    Property **getPropertyManagerProperties();

    bool propsFileOpen();

    Property *get(string key);

    void freePMProps();

private:
    Properties() {};
    Properties(const Properties&);
    Properties& operator=(const Properties&);

    FILE *propFd_;
    string propPath_;
    Logger *log_;

    static inline string trim(string str);
};

#endif
