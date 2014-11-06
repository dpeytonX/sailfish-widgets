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

Item {
    signal create(Component component, variant parent, variant properties)
    signal error(string errorString)
    signal objectCompleted(variant object)

    onCreate: {
        if(!!component && component.status === Component.Ready) {
            var o = component.createObject(parent, properties)
            objectCompleted(o)
        } else {
            error(component.errorString())
        }
    }
}
