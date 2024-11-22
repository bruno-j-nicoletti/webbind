# webbind
Experimenting with binding C++ to JS.

## Building and running
  - install and activate the emsdk in a shell, see
    - https://emscripten.org/docs/getting_started/downloads.html
  Then...
  ```
  make

  ```
  This will create a build directory `build` inside it will be a `webBind.wasm` and `webBind.js`. To run it simply go...
  ```
  cd build
  node webBind.js
  ```

  To rebuild, just run 'make' inside the build directory.

## Issues

### Pthreads
  - compiling with `-pthreads` and linking `-O3` will cause C++ -> JS function calls to fail
     - EMSDK version used 3.1.68
     - specifically `_emval_get_method_caller` called in C++ doesn't get called in JS to register how C++ is calling the JS function
     - possibly linked to https://github.com/emscripten-core/emscripten/issues/15557
     - exhibited by main calling "helloWorld" on the module
        - works fine if no -pthreads, fails if compiled with pthreads
