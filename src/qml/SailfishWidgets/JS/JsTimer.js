function JsTimer(parent) {
    return Qt.createQmlObject("import QtQuick 2.0; Timer{}", parent)
}

function setTimeout(timer, callback, duration) {
    timer.interval = duration
    timer.repeat = false
    timer.triggered.connect(callback);
    timer.start()
}
