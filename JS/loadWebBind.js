WebBind = null;
cheese = 10;

const loadWebBind = async function() {
    if (WebBind === null) {
        const swbLoader = WebBindInit({
            locateFile: (file) => file
        });
        WebBind = await swbLoader;
        console.log("DONE LOADING");
    }
    WebBind.callMain();
    return WebBind;
}();
