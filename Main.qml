/*
 * Copyright © 2025 Luca Carlon
 *
 * This file is part of RpiKioskOsMainApp.
 *
 * RpiKioskOsMainApp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RpiKioskOsMainApp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RpiKioskOsMainApp. If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick
import QtWebEngine

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    WebEngineView {
        anchors.fill: parent
        url: kioskUrl
    }
}
