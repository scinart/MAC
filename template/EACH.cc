// do this later.
// // compile options

// #if defined (__clang__) //CLANG
//   // Test for clang > 3.1.0
//   // #define CLANG_VERSION (__clang_major__*10000 + __clang_minor__*100 + __clang_patchlevel__)
//   // #if CLANG_VERSION < 30100
//   #if __has_feature(cxx_decltype_auto)
//     #define __AUTO_EACH__
//   #endif
// #elsif defined (__GNUC__) //GCC
//   #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
//   // Test for GCC > 4.3.0
//   #if GCC_VERSION < 40300
//     #error GCC minimum version 4.3.0 required.
//   #endif
//   #if __cplusplus < 201103L
//     #if GCC_VERSION < 40700
//       #error you should compile with -std=c++0x option
//     #else
//       #error you should compile with -std=c++11 option
//     #endif
//   #endif
// #elsif defined (_MSC_VER) //MSVC
//   #if _MSC_VER < 1700
//     #error MSVC 2012 or higher required.
//   #endif
// #else
//   #error WHAT compiler do you use??
// #endif


// #ifdef __GNUC__
//   #if __cplusplus >= 201103L
//     #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
//   #else
//     #ifndef __STRICT_ANSI__
//       #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
//     #else
//       #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
//     #endif
//   #endif
//   #if __cplusplus >= 201103L
//       #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
//   #else
//     #ifndef __STRICT_ANSI__
//       #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
//     #else
//       #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
//     #endif
//   #endif
// #else
//   #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
//   #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
// #endif
