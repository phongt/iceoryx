// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <cstring>
#include <iostream>

namespace iox
{
namespace cxx
{
/// @brief struct used to define a compile time variable which is used to distinguish between
/// constructors with certain behavior
struct UnsafeCheckPreconditions_t
{
    explicit UnsafeCheckPreconditions_t() = default;
};
constexpr UnsafeCheckPreconditions_t UnsafeCheckPreconditions{};

template <uint64_t Capacity>
class string
{
    static_assert(Capacity > 0, "The capacity of the fixed string must be greater than 0!");

  public:
    /// @brief creates an empty string with size 0
    string() noexcept;

    /// @brief copy constructor
    ///
    /// @param [in] other is the copy origin
    string(const string& other) noexcept;

    /// @brief move constructor
    ///
    /// @param [in] other is the move origin
    string(string&& other) noexcept;

    /// @brief copy assignment
    ///
    /// @param [in] rhs is the copy origin
    ///
    /// @return reference to self
    string& operator=(const string& rhs) noexcept;

    /// @brief move assignment
    ///
    /// @param [in] rhs is the move origin
    ///
    /// @return reference to self
    string& operator=(string&& rhs) noexcept;

    /// @brief destructor
    ~string() noexcept;

    /// @brief conversion constructor for char array with compile time check if the array size is lesser than or equal
    /// to the string capacity
    ///
    /// @tparam N is the implicit template parameter for the char array size
    /// @param [in] other is the char array
    ///
    /// @code
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         string<4> fuu("abcd");
    ///     }
    /// @endcode
    template <int N>
    string(const char (&other)[N]) noexcept;

    /// @brief conversion constructor for cstring to string which truncates characters if the size is greater than
    /// the string capacity
    ///
    /// @param [in] UnsafeCheckPreconditions_t is a compile time variable which is used to distinguish between
    /// constructors with certain behavior
    /// @param [in] other is the cstring to convert
    /// @attention truncates characters if the size is greater than the string capacity
    ///
    /// @code
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         string<4> fuu(UnsafeCheckPreconditions, "abcd");
    ///     }
    /// @endcode
    string(UnsafeCheckPreconditions_t, const char* const other) noexcept;

    /// @brief conversion constructor for std::string to string which truncates characters if the std::string size is
    /// greater than the string capacity
    ///
    /// @param [in] UnsafeCheckPreconditions_t is a compile time variable which is used to distinguish between
    /// constructors with certain behavior
    /// @param [in] other is the std::string to convert
    /// @attention truncates characters if the std::string size is greater than the string capacity
    ///
    /// @code
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         std::string bar = "bar";
    ///         string<4> fuu(UnsafeCheckPreconditions, bar);
    ///     }
    /// @endcode
    string(UnsafeCheckPreconditions_t, const std::string& other) noexcept;

    /// @brief conversion constructor from cstring to string. Constructs the string with the first count characters of
    /// the cstring including null characters. If count is greater than the string capacity the remainder of the
    /// characters are truncated.
    ///
    /// @param [in] UnsafeCheckPreconditions_t is a compile time variable which is used to distinguish between
    /// constructors with certain behavior
    /// @param other is the cstring to convert
    /// @param count is the number of characters for constructing the string
    ///
    /// @code
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         string<4> fuu(UnsafeCheckPreconditions, "abcd", 2);
    ///     }
    /// @endcode
    string(UnsafeCheckPreconditions_t, const char* const other, const uint64_t count) noexcept;

    /// @brief assigns a char array to string with compile time check if the array size is lesser than or equal
    /// to the string capacity
    ///
    /// @tparam [in] N is the implicit template parameter for the char array size
    /// @param [in] rhs is the char array
    ///
    /// @return reference to self
    ///
    /// @code
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         string<4> fuu = "abcd";
    ///     }
    /// @endcode
    template <int N>
    string& operator=(const char (&rhs)[N]) noexcept;

    /// @brief fixed string assignment
    ///
    /// @param [in] str is the fixed string object to assign
    ///
    /// @return reference to self
    string& assign(const string& str) noexcept;

    /// @brief assigns a char array to string with compile time check if the array size is lesser than or equal to the
    /// string capacity
    ///
    /// @tparam [in] N is the implicit template parameter for the char array size
    /// @param [in] str is the char array
    ///
    /// @return reference to self
    /// @code
    ///
    ///     #include "classes/string.hpp"
    ///     using namespace iox::cxx;
    ///
    ///     int main()
    ///     {
    ///         string<4> fuu;
    ///         char bar[] = "abcd";
    ///         fuu.assign(bar);
    ///     }
    /// @endcode
    template <int N>
    string& assign(const char (&str)[N]) noexcept;

    /// @brief assigns a cstring to string. The assignment fails if the cstring size is greater than the string
    /// capacity.
    ///
    /// @param [in] str is the cstring to assign
    ///
    /// @return true if the assignment succeeds, otherwise false
    bool unsafe_assign(const char* const str) noexcept;

    /// @brief assigns a std::string to string. The assignment fails if the std::string size is greater than the string
    /// capacity.
    ///
    /// @param [in] str is the std::string to assign
    ///
    /// @return true if the assignment succeeds, otherwise false
    bool unsafe_assign(const std::string& str) noexcept;

    /// @brief compares two strings
    ///
    /// @param [in] other is the string to compare with self
    ///
    /// @return an integer < 0 if the first character that does not match has a lower value in self than in other, 0 if
    /// the contents of both strings are equal, an integer > 0 if the first character that does not match has a greater
    /// value in self than in other
    int compare(const string other) const noexcept;
    // int64_t compare(const string other) const noexcept;

    /// @brief checks if self is equal to rhs
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if both strings are equal, otherwise false
    bool operator==(const string& rhs) const noexcept;

    /// @brief checks if self is not equal to rhs
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if both strings are not equal, otherwise false
    bool operator!=(const string& rhs) const noexcept;

    /// @brief checks if self is lesser than rhs, in lexicographical order
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if self is lesser than rhs, otherwise false
    bool operator<(const string& rhs) const noexcept;

    /// @brief checks if self is lesser than or equal to rhs, in lexicographical order
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if self is lesser than or equal to rhs, otherwise false
    bool operator<=(const string& rhs) const noexcept;

    /// @brief checks if self is greater than rhs, in lexicographical order
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if self is greater than rhs, otherwise false
    bool operator>(const string& rhs) const noexcept;

    /// @brief checks if self is greater than or equal to rhs, in lexicographical order
    ///
    /// @param [in] rhs is the string to compare with self
    ///
    /// @return true if self is greater than or equal to rhs, otherwise false
    bool operator>=(const string& rhs) const noexcept;

    /// @brief returns a pointer to the char array of self
    ///
    /// @return a pointer to the char array of self
    const char* c_str() const noexcept;

    /// @brief returns the number of characters stored in the string
    ///
    /// @return the number of characters stored in the string
    uint64_t size() const noexcept;

    /// @brief returns the maximum number of characters that can be stored in the string
    ///
    /// @return the maximum number of characters that can be stored in the string
    uint64_t capacity() const noexcept;

    /// @brief converts the string to a std::string
    ///
    /// @return a std::string with data equivalent to those stored in the string
    explicit operator std::string() const noexcept;

  private:
    char m_rawstring[Capacity + 1]{'\0'};
    size_t m_rawstringSize{0};
};
} // namespace cxx
} // namespace iox
#include "iceoryx_utils/internal/cxx/string.inl"
