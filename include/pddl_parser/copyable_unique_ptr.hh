#ifndef PDDL_PARSER_COPYABLE_UNIQUE_PTR_HH
#define PDDL_PARSER_COPYABLE_UNIQUE_PTR_HH

#include <iostream>
#include <memory>

namespace pddl_parser {

/* A unique_ptr that has copy constructor and assignment operator. We need this
  to use unique_ptr inside Bison. As a bonus, it also implements the output
  stream operator.

  Requires that the following be implemented:
  - T* T::clone() const
  - std::ostream& operator<<(std::ostream &, T const &)
*/
template<typename T>
class CopyableUniquePtr : public std::unique_ptr<T> {
    using std::unique_ptr<T>::unique_ptr;

public:
    CopyableUniquePtr() = default;
    CopyableUniquePtr(CopyableUniquePtr const &other)
        : std::unique_ptr<T>() {
        std::unique_ptr<T>::reset(other ? other->clone() : nullptr);
    }
    CopyableUniquePtr& operator=(CopyableUniquePtr const &other) {
        std::unique_ptr<T>::reset(other ? other->clone() : nullptr);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &stream,
                                    CopyableUniquePtr const &ptr) {
        if (ptr)
            stream << *ptr;
        return stream;
    }
};

} // namespace pddl_parser

#endif // PDDL_PARSER_COPYABLE_UNIQUE_PTR_HH
