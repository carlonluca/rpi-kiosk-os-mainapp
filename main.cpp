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
#include <QtWebEngineQuick>
#include <QQuickWindow>
#include <signal.h>

class ShotNotifier : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    Q_INVOKABLE bool saveShot(QQuickWindow* window) {
        const auto shot = window->grabWindow();
        const auto currentMs = QDateTime::currentMSecsSinceEpoch();
        const auto fileName = QString("shot_%1.png").arg(currentMs);
        const auto path = QDir::temp().absoluteFilePath(fileName);
        return shot.save(path);
    }

signals:
    void shotRequested();
};

static ShotNotifier* m_notifier = nullptr;

void usr1(int sig, siginfo_t* sip, void* ptr)
{
    if (m_notifier)
        emit m_notifier->shotRequested();
}

int main(int argc, char** argv)
{
    const char* urlEnvVar = "RPI_KIOSK_OS_MAIN_APP_URL";

    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    ShotNotifier shotNotifier;
    m_notifier = &shotNotifier;

    struct sigaction sa;
    memset(&sa, 0, sizeof (sa));
    sa.sa_sigaction = usr1;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, nullptr);

    auto* rootContext = engine.rootContext();
    rootContext->setContextProperty("shotNotifier", &shotNotifier);
    if (qEnvironmentVariableIsSet(urlEnvVar))
        rootContext->setContextProperty("kioskUrl", qEnvironmentVariable(urlEnvVar));
    else
        rootContext->setContextProperty("kioskUrl", QStringLiteral("https://bugfreeblog.duckdns.org"));
    engine.loadFromModule("RpiKioskOsMainApp", "Main");

    return QCoreApplication::exec();
}

#include "main.moc"
