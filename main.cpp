/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * Copyright (C) 2026 Luca Carlon
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char** argv)
{
    const char* urlEnvVar = "RPI_KIOSK_OS_MAIN_APP_URL";

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    auto* rootContext = engine.rootContext();
    if (qEnvironmentVariableIsSet(urlEnvVar))
        rootContext->setContextProperty("kioskUrl", qEnvironmentVariable(urlEnvVar));
    else
        rootContext->setContextProperty("kioskUrl", QStringLiteral("https://bugfreeblog.duckdns.org"));
    engine.loadFromModule("RpiKioskOsMainApp", "Main");

    return QCoreApplication::exec();
}
