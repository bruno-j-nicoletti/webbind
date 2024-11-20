WebBind = null;

const loadWebBind = async function() {
    if (WebBind === null) {
        const swbLoader = WebBindInit({
            locateFile: (file) => file
        });
        WebBind = await swbLoader;
        console.log("DONE LOADING");
    }
    WebBind.dave(10);// callMain();
    return WebBind;
}();
