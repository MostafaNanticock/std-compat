#ifndef PM_STD_COMPAT_OPTIONAL_NO_FUNCTIONAL_PATCH
#define PM_STD_COMPAT_OPTIONAL_NO_FUNCTIONAL_PATCH

#include <type_traits>

namespace PM
{
namespace internal
{
    namespace OptionalPatch
    {
        template <class T>
        using decay_t = typename std::decay<T>::type;
        template <bool E, class T = void>
        using enable_if_t = typename std::enable_if<E, T>::type;
        template <bool B, class T, class F>
        using conditional_t = typename std::conditional<B, T, F>::type;
    } // namespace OptionalPatch

    // --- invoke for member function pointers (object instance) ---
    template <typename MemFn, typename T, typename... Args,
#ifdef TL_TRAITS_LIBCXX_MEM_FN_WORKAROUND
              typename = OptionalPatch::enable_if_t<!(is_pointer_to_non_const_member_func<MemFn>::value && is_const_or_const_ref<T>::value)>,
#endif
              typename = OptionalPatch::enable_if_t<std::is_member_function_pointer<OptionalPatch::decay_t<MemFn>>::value>>
    constexpr auto invoke(MemFn &&f, T &&obj, Args &&...args) noexcept(noexcept((std::forward<T>(obj).*f)(std::forward<Args>(args)...)))
        -> decltype((std::forward<T>(obj).*f)(std::forward<Args>(args)...))
    {
        return (std::forward<T>(obj).*f)(std::forward<Args>(args)...);
    }

    // --- invoke for member function pointers (pointer to object) ---
    template <typename MemFn, typename Ptr, typename... Args,
#ifdef TL_TRAITS_LIBCXX_MEM_FN_WORKAROUND
              typename = OptionalPatch::enable_if_t<!(is_pointer_to_non_const_member_func<MemFn>::value && is_const_or_const_ref<Ptr>::value)>,
#endif
              typename = OptionalPatch::enable_if_t<std::is_member_function_pointer<OptionalPatch::decay_t<MemFn>>::value>>
    constexpr auto invoke(MemFn &&f, Ptr &&ptr, Args &&...args) noexcept(noexcept(((*std::forward<Ptr>(ptr)).*f)(std::forward<Args>(args)...)))
        -> decltype(((*std::forward<Ptr>(ptr)).*f)(std::forward<Args>(args)...))
    {
        return ((*std::forward<Ptr>(ptr)).*f)(std::forward<Args>(args)...);
    }

    // --- invoke for member object pointers (object instance) ---
    template <typename MemObj, typename T,
              typename = OptionalPatch::enable_if_t<std::is_member_object_pointer<OptionalPatch::decay_t<MemObj>>::value>>
    constexpr auto invoke(MemObj &&m, T &&obj) noexcept(noexcept(std::forward<T>(obj).*m)) -> decltype(std::forward<T>(obj).*m)
    {
        return std::forward<T>(obj).*m;
    }

    // --- invoke for member object pointers (pointer to object) ---
    template <typename MemObj, typename Ptr,
              typename = OptionalPatch::enable_if_t<std::is_member_object_pointer<OptionalPatch::decay_t<MemObj>>::value>>
    constexpr auto invoke(MemObj &&m, Ptr &&ptr) noexcept(noexcept((*std::forward<Ptr>(ptr)).*m)) -> decltype((*std::forward<Ptr>(ptr)).*m)
    {
        return (*std::forward<Ptr>(ptr)).*m;
    }

    // --- invoke for non-member callables (functions, functors, lambdas) ---
    template <typename Fn, typename... Args, typename = OptionalPatch::enable_if_t<!std::is_member_pointer<OptionalPatch::decay_t<Fn>>::value>>
    constexpr auto invoke(Fn &&f, Args &&...args) noexcept(noexcept(std::forward<Fn>(f)(std::forward<Args>(args)...)))
        -> decltype(std::forward<Fn>(f)(std::forward<Args>(args)...))
    {
        return std::forward<Fn>(f)(std::forward<Args>(args)...);
    }

} // namespace internal
} // namespace PM

#endif
