#include <sstream>

namespace std
{
template <typename T>
std::string my_to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
} // namespace std
