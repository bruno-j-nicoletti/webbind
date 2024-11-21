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

EMSCRIPTEN_KEEPALIVE
void dumpTypeIDs() {
  std::cout << "dumpTypeIDs\n";
  std::cout << "  Int type ptr is "
            << int(emscripten::internal::TypeID<int>::get()) << std::endl;
#if __has_feature(cxx_rtti)
  std::cout << "  Int typeid ptr is " << int(&typeid(int)) << std::endl;
#endif
}

EMSCRIPTEN_KEEPALIVE
void printInt(int i) { std::cout << "printInt(" << i << ")" << std::endl; }

auto getGlobalVal(const char *name) {
  auto value = emscripten::val::global(name);
  std::cout << name << " isNull : " << value.isNull()
            << " isUndefined:" << value.isUndefined() << std::endl;
  return value;
}
}

int32_t boundIntFunc(int32_t n) {
  std::cout << "boundIntFunc(" << n << ")\n";
  return 2 * n;
}

EMSCRIPTEN_BINDINGS(WebBind) {
  std::cout << "BINDINGS START!\n";
  function("boundIntFunc", &boundIntFunc);
  std::cout << "BINDINGS END!\n";
}

int main() {
  std::cout << "MAIN!\n";

  getGlobalVal("console");
  emscripten::val module = getGlobalVal("WebBind");
  module.call<emscripten::val>("helloWorld", std::string("banana"));
  return 0;
}
