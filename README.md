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
