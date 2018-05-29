#include <Properties.hpp>
#include <Property.hpp>

#include <cerrno>
#include <locale>
#include <cstring>
#include <utility>
#include <sys/stat.h>

static Property **pmProps; // PropertiesManager properties

Properties::Properties(const char *propPath) {
    // If we don't have the PropertiesManager properties loaded
    if (pmProps == nullptr) {
        auto *props = new Properties(); // Use the empty constructor so we don't call this recursively

        string pmPropPath = "/etc/propertiesmanager/custom.properties";
        struct stat pmBuffer {};
        if (stat(pmPropPath.c_str(), &pmBuffer) != 0) {
            pmPropPath = "/etc/propertiesmanager/default.properties";
        }

        props->propPath_ = pmPropPath;

        props->log_ = Logger::forClass<Properties>(LogLevelDebug);
        props->log_->info("Attempting to load Properties settings file: \"%s\"", props->propPath_.c_str());

        pmProps = (Property **)malloc(sizeof(Property));

        if ((props->propFd_ = fopen(props->propPath_.c_str(), "r")) == nullptr) {
            props->log_->fatal("Failed to open \"%s\" (%s)", props->propPath_.c_str(), strerror(errno));
            pmProps[0] = new Property("log.level", "LogLevelInfo");
        } else {
            pmProps[0] = new Property("log.level", props->get("log.level")->value());
            props->log_->debug("Log level: %s", pmProps[0]->value().c_str());
        }
    }

    propPath_ = propPath;
    log_ = Logger::forClass<Properties>(Logger::getLogLevelFromString(pmProps[0]->value()));
    log_->info("Attempting to open properties file: \"%s\"", propPath);
    if ((propFd_ = fopen(propPath, "r")) == nullptr) {
        log_->error("Failed to open \"%s\" (%s)", propPath, strerror(errno));
    }
}

Properties::~Properties() {
    delete log_;
    fclose(propFd_);
}

Property **getPropertyManagerProperties() {
    return pmProps;
}

inline string Properties::trim(string str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
    str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
    return str;
}

bool Properties::propsFileOpen() {
    return propFd_ != nullptr;
}

Property *Properties::get(string key) {
    string key_expect = trim(std::move(key));
    log_->debug("Key to find: \"%s\"", key_expect.c_str());

    if (key_expect.empty()) {
        log_->error("Key to find cannot be empty");
        return nullptr;
    }

    char line[1024] = "";
    string line_str;
    string key_found;

    // Make sure we start at the top of the file,
    // because we won't close the file until destruction
    rewind(propFd_);

    while (fgets(line, 1024, propFd_) != nullptr) {
        line_str = trim(string(line));
        if (line_str.empty()) { // ignore empty lines
            continue;
        }

        log_->debug("Found property: \"%s\"", line_str.c_str());
        size_t eq_index = line_str.find_first_of('=');
        key_found = trim(line_str.substr(0, eq_index));
        log_->debug("\tKey: \"%s\"", key_found.c_str());

        if (key_found.empty()) {
            log_->error("Invalidly formatted key/value pair: \"%s\"", line_str.c_str());
        }

        if (key_found.length() != key_expect.length()) {
            continue;
        }

        if (key_found.compare(0, key_expect.length(), key_expect) == 0) {
            log_->debug("Key match found");
            return new Property(key_found, line_str.substr(eq_index + 1, line_str.length() - eq_index - 1));
        }
    }
    log_->warn("Property with key \"%s\" not found", key_expect.c_str());
    return Property::emptyProperty();
}

void Properties::freePMProps() {
    free(pmProps);
}
