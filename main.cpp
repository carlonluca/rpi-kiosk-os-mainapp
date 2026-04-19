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
