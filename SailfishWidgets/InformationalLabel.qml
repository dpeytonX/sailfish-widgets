import QtQuick 2.0
import Sailfish.Silica 1.0

/**
  * Label with a medium font size and normal highlighting.
  *
  * Use to give the user simple instructions or explanations.
  */
Label {
    color: Theme.highlightColor
    font.family: Theme.fontFamilyHeading
    font.pixelSize: Theme.fontSizeMedium
}
