#pragma once

#include <stdlib.h>

typedef char const* ccp;  //!< Pointer to a constant string.
typedef ccp const ccpc;   //!< Constant pointer to a constant string.

/*! Generic container.
 *
 * \tparam T Value type.
 */
template <class T>
struct Container_ {
  T value;  //!< Value.
};

/*! Integer number.
 *
 * \tparam T Integer type.
 * \tparam base Integer base.
 */
template <class T, size_t base>
struct Number : Container_<T> {};

/*! Boolean.
 *
 * \tparam truth Truth value.
 */
template <ccp truth>
struct Bool : Container_<bool> {};

/*! Category.
 *
 * \tparam T Integer type.
 * \tparam labels Labels.
 */
template <class T, ccp* labels>
struct Category : Container_<T> {};


/*! String comparison.
 *
 * \param[in] begin Pointer to the first C string.
 * \param[in] end Pointer to end of the first C string.
 * \param[in] str Pointer to the second C string.
 */
bool strmatch(ccpc begin, ccpc end, ccpc str);
