#ifndef ERROR_HXX
#define ERROR_HXX

namespace taskmaster::error {

/// \param error_message The error message to print.
///
/// \warning `error_message` not being a valid C string is undefined behavior.
///
void print(char const *const error_message);

} // namespace taskmaster::error

#endif
