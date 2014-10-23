import QtQuick 2.0
import Sailfish.Silica 1.0

/**
  * Label with a small font size and secondary highlighting.
  *
  * Can be used to add detailed information in the UI.
  */
TextArea {
    color: Theme.secondaryHighlightColor
    font.family: Theme.fontFamilyHeading
    font.pixelSize: Theme.fontSizeSmall
    readOnly: true
}
