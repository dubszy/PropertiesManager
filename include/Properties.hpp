#ifndef _PROPERTIES_MANAGER_HPP_
#define _PROPERTIES_MANAGER_HPP_

#include <cerrno>
#include <cstdio>
#include <string>
#include <string.h>

#include <logger/c++/Logger.hpp>

#include <Property.hpp>

using namespace std;

static Property **pm_props;

// TODO: string comparisons should use the ICU library
// TODO: add localization support
class Properties {

public:
    Properties(const char *prop_path, bool load_pm_props = false);

    ~Properties();

    Property **getPropertyManagerProperties();

    Property *get(string key);

private:
    Properties() {};
    Properties(const Properties&);
    Properties& operator=(const Properties&);

    FILE *prop_fd_;
    const char *prop_path_;
    Logger *log_;

    static inline string trim(string str);
};

#endif
