WebBind = null;

const loadWebBind = async function() {
    if (WebBind === null) {
        console.log("START LOADING");
        const swbLoader = WebBindInit({
            locateFile: (file) => file
        });
        WebBind = await swbLoader;
        console.log("DONE LOADING");
    }

    // Dump all the types registered from C++ and known in JS
    WebBind.dumpRegisteredTypes();

    // Have C++ dump what it thinks some type ids are.
    WebBind._dumpTypeIDs();

    // Call a function bound via EMSCRIPTEN_KEEPALIVE.
    WebBind._printInt(191);

    // Call a function bound via EMSCRIPTEN_BINDINGS,
    WebBind.boundIntFunc(10);
    return WebBind;
}();
