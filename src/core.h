#ifndef CORE_H
#define CORE_H

const double PI = 3.14159265359;

#define BIT(x) (1 << x)
#define RESOURCES_DIR "../../resources"

#define BIND_EVENT_FUNCTION(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define BIND_EVENT_FUNCTION_MAIN(fn) [&](auto &&...args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

#include <memory>

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> MakeRef(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif /* CORE_H */