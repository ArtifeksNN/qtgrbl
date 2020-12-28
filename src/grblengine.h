/*
 * MIT License
 *
 * Copyright (c) 2020 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of QtGrbl project https://github.com/semlanik/qtgrbl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <memory>
#include <QQueue>
#include <QFile>
#include <QFileInfo>
#include <QPointer>

#include "qtgrblcommon.h"

namespace QtGrbl {

class GrblSerial;

class GrblEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
public:
    explicit GrblEngine(QObject *parent = nullptr);
    virtual ~GrblEngine();

    void attach(const std::weak_ptr<GrblSerial> &serialEngine);
    Q_INVOKABLE void start();
    Q_INVOKABLE void returnToZero();
    Q_INVOKABLE void resetToZero();
    Q_INVOKABLE void hold();
    Q_INVOKABLE void resume();

    QString filePath() const {
        return QFileInfo(m_file).absoluteFilePath();
    }

    void setFilePath(const QString &fileUrl);
signals:
    void consoleOutputChanged();
    void filePathChanged();

    void sendCommand(const QByteArray &command, QtGrbl::CommandPriority prio);
private:
    void requestParserState();

    QFile m_file;
    std::weak_ptr<GrblSerial> m_serialEngine;
};

}
