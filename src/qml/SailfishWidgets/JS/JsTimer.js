function JsTimer(parent, callback, duration) {
    var timer = Qt.createQmlObject("import QtQuick 2.0; Timer{}", parent)
    timer.interval = duration
    timer.repeat = false
    timer.triggered.connect(callback);
    return timer
}
