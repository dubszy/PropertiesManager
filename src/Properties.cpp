#include <locale>

#include <Properties.hpp>

#include <Property.hpp>
#include <utility>

Properties::Properties(const char *prop_path, bool load_pm_props) {
    if (pm_props == nullptr) {
        auto *props = new Properties();
        Logger::setGlobalLogLevel(LogLevelDebug);
        props->log_ = Logger::forClass<Properties>(LogLevelDebug);
        props->prop_path_ = ((load_pm_props) ? prop_path : "res/settings/propman/default.properties");
        props->log_->info("Attempting to load Properties settings file: \"%s\"", props->prop_path_);
        if ((props->prop_fd_ = fopen(props->prop_path_, "r")) == nullptr) {
            log_->fatal("Failed to open \"%s\" (%s)", props->prop_path_, strerror(errno));
            exit(-1);
        }
        pm_props = (Property **)malloc(sizeof(Property));
        pm_props[0] = new Property("log.level", props->get("log.level")->value());
        props->log_->debug("Log level: %s", pm_props[0]->value().c_str());
        delete props;
    }

    if (!load_pm_props) {
        prop_path_ = prop_path;
        log_ = Logger::forClass<Properties>(Logger::getLogLevelFromString(pm_props[0]->value()));
        log_->info("Attempting to open properties file: \"%s\"", prop_path);
        if ((prop_fd_ = fopen(prop_path, "r")) == nullptr) {
            log_->error("Failed to open \"%s\" (%s)", prop_path, strerror(errno));
            return;
        }
    }
}

Properties::~Properties() {
    delete log_;
    free(pm_props);
}

Property **getPropertyManagerProperties() {
    return pm_props;
}

inline string Properties::trim(string str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
    str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
    return str;
}

Property *Properties::get(string key) {
    string key_expect = trim(std::move(key));
    log_->debug("Key to find: \"%s\"", key_expect.c_str());

    if (key_expect.empty()) {
        log_->error("Key to find cannot be empty");
        return nullptr;
    }

    char line[1024];
    string line_str;
    string key_found;

    while (fgets(line, 1024, prop_fd_) != nullptr) {
        line_str = trim(string(line));
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
    return nullptr;
}
