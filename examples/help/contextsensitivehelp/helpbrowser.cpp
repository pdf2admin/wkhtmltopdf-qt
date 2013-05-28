/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QLibraryInfo>
#include <QtGui/QApplication>
#include <QtHelp/QHelpEngineCore>

#include "helpbrowser.h"

HelpBrowser::HelpBrowser(QWidget *parent)
    : QTextBrowser(parent)
{
    QString collectionFile = QLibraryInfo::location(QLibraryInfo::ExamplesPath)
        + QLatin1String("/help/contextsensitivehelp/doc/wateringmachine.qhc");

    m_helpEngine = new QHelpEngineCore(collectionFile, this);
    if (!m_helpEngine->setupData()) {
        delete m_helpEngine;
        m_helpEngine = 0;
    }
}

void HelpBrowser::showHelpForKeyword(const QString &id)
{
    if (m_helpEngine) {
        QMap<QString, QUrl> links = m_helpEngine->linksForIdentifier(id);
        if (links.count())
            setSource(links.constBegin().value());
    }
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name)
{
    QByteArray ba;
    if (type < 4 && m_helpEngine) {
        QUrl url(name);
        if (name.isRelative())            
            url = source().resolved(url);
        ba = m_helpEngine->fileData(url);        
    }
    return ba;
}

