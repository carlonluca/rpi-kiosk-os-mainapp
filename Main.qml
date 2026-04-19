/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * Copyright (C) 2026 Luca Carlon
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

import QtQuick
import QtWebEngine

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    visibility: Window.FullScreen

    WebEngineView {
        anchors.fill: parent
        url: kioskUrl
    }
}
