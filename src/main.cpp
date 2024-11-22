/*
 * Copyright 2024 Bruno Nicoletti
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;
extern "C" {
  int main();

  /// Dump some typeids that have been registered with emscripten
  EMSCRIPTEN_KEEPALIVE
  void dumpTypeIDs() {
    std::cout << "dumpTypeIDs\n";
    std::cout << "  Int type ptr is "
              << int(emscripten::internal::TypeID<int>::get()) << std::endl;
#if __has_feature(cxx_rtti)
    std::cout << "  Int typeid ptr is " << int(&typeid(int)) << std::endl;
#endif
  }

  /// low level function to call from JS
  EMSCRIPTEN_KEEPALIVE
  void printInt(int i) { std::cout << "printInt(" << i << ")" << std::endl; }

}

/// function being exposed into JS via the binding API...
int32_t boundIntFunc(int32_t n) {
  std::cout << "boundIntFunc(" << n << ")\n";
  return 2 * n;
}

/// Bind a function via the bindings API
EMSCRIPTEN_BINDINGS(WebBind) {
  std::cout << "BINDINGS START!\n";
  function("boundIntFunc", &boundIntFunc);
  std::cout << "BINDINGS END!\n";
}

/// Get a global JS value
auto getGlobalVal(const char *name) {
  auto value = emscripten::val::global(name);
  std::cout << name << " isNull:" << value.isNull()
            << " isUndefined:" << value.isUndefined() << std::endl;
  return value;
}

/// Will be called from JS on load
int main() {
  std::cout << "MAIN!\n";

  // call into JS from C++ via the 'val' API....
  emscripten::val module = getGlobalVal("WebBind");
  module.call<emscripten::val>("helloWorld", std::string("banana"));

  return 0;
}
