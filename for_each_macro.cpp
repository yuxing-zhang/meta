// FOR_EACH(macro, ...) applies `macro` to each of the arguments.
// Maximum number of arguments is 41. To increase this limit, simply add
// another expansion depth.

#define EXPAND1(macro) macro
#define EXPAND2(macro) EXPAND1(EXPAND1(EXPAND1(macro)))
#define EXPAND3(macro) EXPAND2(EXPAND2(EXPAND2(macro)))
#define EXPAND(macro) EXPAND3(EXPAND3(EXPAND3(macro)))

#define FOR_EACH_HELPER(macro, arg, ...)\
        macro(arg) __VA_OPT__(FOR_EACH_ PARENS(macro, __VA_ARGS__))
#define FOR_EACH_() FOR_EACH_HELPER
#define PARENS ()

#define FOR_EACH(macro, ...)\
        __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))

// MAKE_ENUM declares an enumeration, paired with a utility function that
// returns as a string the name of an enumerator.
#define CASE(enu) case enu: return #enu;
#define MAKE_ENUM(name, ...)\
enum name { __VA_ARGS__ };\
const char* to_str(name _e) { switch (_e) { FOR_EACH(CASE, __VA_ARGS__) } }
