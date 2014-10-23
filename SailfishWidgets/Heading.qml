import QtQuick 2.0
import Sailfish.Silica 1.0

/**
  * Label with a large font size and normal highlighting.
  *
  * Meant to be used as a section header.
  */
Label {
    color: Theme.highlightColor
    font.family: Theme.fontFamilyHeading
    font.pixelSize: Theme.fontSizeLarge
}
