# webbind
Experimenting with binding C++ to JS.

## Problems with binding and RTTI

If compiled with `-fno-rtti` and `-DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0` then you need to pass `-fno-rtti` to the linker otherwise it all gets very confused.
