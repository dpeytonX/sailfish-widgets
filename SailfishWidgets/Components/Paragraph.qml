// This file is part of SailfishWidgets
// 
// Copyright (c) 2014 Dametrious Peyton
//     
// SailfishWidgets is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// SailfishWidgets is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with SailfishWidgets.  If not, see <http://www.gnu.org/licenses/>.

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
    width: parent.width
}
