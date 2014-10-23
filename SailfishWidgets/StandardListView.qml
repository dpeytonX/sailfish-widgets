import QtQuick 2.0
import Sailfish.Silica 1.0

/**
  * A SilicaListView with a default place holder and scroll decorator
  *
  * Properties:
  * headerTitle     - set to provide a custom title for the page
  * placeHolderText - sets the text that displays when no items are given
  */
SilicaListView {
    property string headerTitle
    property string placeHolderText: qsTr("No items")

    header: PageHeader {
        title: headerTitle
    }
    id: listView

    ViewPlaceholder {
        enabled: !listView.count
        text: placeHolderText
    }

    VerticalScrollDecorator {}
}
