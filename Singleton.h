#pragma once

#include <memory>

template <typename T>
class Singleton {
public:
    static T& instance() {
        static const std::unique_ptr<T> instance{new T};
        return *instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default; 

private:
    inline static std::unique_ptr<T> *_instance = nullptr;
};
