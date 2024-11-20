/*
 * Copyright 2024 Bruno Nicoletti
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

extern "C" {
int main();
}

using namespace emscripten;

auto getGlobalVal(const char *name) {
  auto value = emscripten::val::global(name);
  std::cout << name << " isNull : " << value.isNull()
            << " isUndefined:" << value.isUndefined() << std::endl;
  return value;
}

auto dave(int n) -> void
{
  std::cout << "Dave is " << n << "\n";
}

EMSCRIPTEN_BINDINGS(WebBind)
{
  std::cout << "BINDINGS!\n";
  function("dave", &dave);
}

int main() {
  std::cout << "MAIN!\n";

  getGlobalVal("console");
  emscripten::val module = getGlobalVal("WebBind");
  module.call<emscripten::val>("helloWorld", std::string("banana"));
  return 0;
}
