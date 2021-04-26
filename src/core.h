#ifndef CORE_H
#define CORE_H

const double PI = 3.14159265359;

#include <memory>

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> MakeRef(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif /* CORE_H */