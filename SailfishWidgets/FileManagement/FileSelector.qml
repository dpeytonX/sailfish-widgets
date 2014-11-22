import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Components" 1.2
import "../JS" 1.2
import FileManagement 1.2

/*!
  Only handles selecting files and returns those files back to user

  Qml                           Instantiates
  This dialog -------------> Qml DirectoryInfo (handles all operations)
                                Sends back
  dynamically <-------------- list of QFiles matching request
  populates list view
  */
Dialog {
    property alias directory: fileList
    property alias filter: fileList.filter
    property alias header: listView.header
    property alias sort: fileList.sort
    property bool multiSelect: false
    property bool quickSelect: true
    property int selectionFilter: Dir.AllEntries | Dir.Readable | Dir.Hidden
    property string acceptText: directory.dirName
    property string baseDirectory: fileList.XdgHome
    property string cancelText
    property string deselectText
    property string headerTitle
    property string selectText
    property variant selectedFiles: []

    canAccept: !!selectedFiles && !!(selectedFiles.length)
    id: fileSelector

    StandardListView {
        anchors.fill: parent
        delegate: ListItem {
            property bool selected: false
            property File file: modelData

            id: contentItem
            menu: contextMenuComponent
            showMenuOnPressAndHold: matchSelectionFilter(file)

            Image {
                x: Theme.paddingSmall
                height: file.dir ? parent.height - Theme.paddingSmall : 0
                width: height
                id: icon
                source: file.dir ? IconThemes.iconDirectory : ""
            }

            InformationalLabel {
                anchors.left: icon.right
                anchors.leftMargin: Theme.paddingSmall
                anchors.verticalCenter: parent.verticalCenter
                color: selected ? Theme.primaryColor : (matchSelectionFilter(file) ? Theme.highlightColor : Theme.secondaryHighlightColor)
                text: file.fileName
            }

            onClicked: {
                if(file.dir) {
                    fileList.path = file.absoluteFilePath
                } else {
                    if(quickSelect) makeSelection(file)
                }
            }

            Component.onCompleted: listView.updateSelected()
        }
        header: DialogHeader {
            acceptText: fileSelector.acceptText
            cancelText: fileSelector.cancelText
            id: dialogHeader
            title: fileSelector.headerTitle
        }
        id: listView
        model: fileList.files


        Component {
            id:contextMenuComponent
            ContextMenu {
                id: context
                StandardMenuItem {
                    text: !!context.parent ? (context.parent.selected ? deselectText : selectText) : ""
                    onClicked: {
                        makeSelection(context.parent.file)
                    }
                }
            }
        }

        VerticalScrollDecorator {}

        function updateSelected() {
            for(var i = 0; i < listView.contentItem.children.length; i++) {
                var child = listView.contentItem.children[i]
                if(!!child.file)
                    child.selected = selectedFiles.indexOf(child.file) != -1
            }
        }
    }

    Dir {
        id: fileList
        filter: Dir.AllEntries | Dir.Hidden
        sort: Dir.DirsFirst | Dir.Name

        onPathChanged: {clearSelection(); refresh()}
    }

    onBaseDirectoryChanged: fileList.path = baseDirectory

    onRejected: clearSelection()

    function clearSelection() {
        while(!!selectedFiles && selectedFiles.length) makeSelection(selectedFiles[0])
    }

    function makeSelection(file) {
        if(selectedFiles.indexOf(file) != -1) {
            selectedFiles = Variant.remove(selectedFiles, file)
        } else {
            if(!matchSelectionFilter(file))
                return

            if(!multiSelect) selectedFiles = []
            selectedFiles = Variant.add(selectedFiles, file)
        }

        listView.updateSelected()
        canAccept = selectedFiles.length
    }

    function matchSelectionFilter(file) {
        if((selectionFilter & Dir.Readable) && !file.readable) return false
        if((selectionFilter & Dir.Writable) && !file.writable) return false
        if((selectionFilter & Dir.Executable) && !file.executable) return false
        if((selectionFilter & Dir.NoSymLinks) && file.symLink) return false
        if(!(selectionFilter & Dir.Hidden) && file.hidden) return false

        if(selectionFilter & Dir.AllEntries) return true
        if(selectionFilter & Dir.Dirs & Dir.Files) return true

        if((selectionFilter & Dir.Dirs) && !file.dir) return false
        if((selectionFilter & Dir.AllDirs) && !file.dir) return false
        if((selectionFilter & Dir.Files) && file.dir) return false
        return true
    }
}
