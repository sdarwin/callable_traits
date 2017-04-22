/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ add_member_volatile_hpp
/*`
[section:ref_add_member_volatile add_member_volatile]
[heading Header]
``#include <boost/callable_traits/add_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_volatile_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_volatile,

        detail::fail_when_same<typename detail::traits<T>::add_member_volatile,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_volatile,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
//->

template<typename T, typename U = add_member_volatile_t<T>>
struct add_member_volatile {
    using type = U;
};

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member volatile qualifier to `T`, if not already present.

[heading Compatibility Notes]
A substitution failure occurs on GCC builds older than version 4.9.2 with function types, because those versions did not support abominable function types. Full support on GCC 4.9.2+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_volatile_t<T>`]]
    [[`int()`]                          [`int() volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_volatile.cpp]
[add_member_volatile]
[endsect][/section:ref_add_member_volatile]
*/
//]

#endif
