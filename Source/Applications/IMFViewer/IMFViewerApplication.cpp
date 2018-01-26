/* ============================================================================
* Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
* Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
* Copyright (c) 2012 Joseph B. Kleingers (Student Research Assistant)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of Michael A. Groeber, Michael A. Jackson, Joseph B. Kleingers,
* the US Air Force, BlueQuartz Software nor the names of its contributors may be
* used to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*  This code was written under United States Air Force Contract number
*                           FA8650-07-D-5800
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "IMFViewerApplication.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>

#include "SVWidgetsLib/QtSupport/QtSStyles.h"

#include "IMFViewer/IMFController.h"
#include "IMFViewer/IMFViewer_UI.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IMFViewerApplication::IMFViewerApplication(int& argc, char** argv) :
  QApplication(argc, argv),
  m_Controller(new IMFController())
{
//  loadStyleSheet("light");

  createApplicationMenu();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IMFViewerApplication::~IMFViewerApplication()
{
  delete m_Controller;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void IMFViewerApplication::createApplicationMenu()
{
  m_ApplicationMenuBar = new QMenuBar();
  QMenu* fileMenu = new QMenu("File", m_ApplicationMenuBar);

  QAction* openAction = new QAction("Open File");
  openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  connect(openAction, &QAction::triggered, this, &IMFViewerApplication::openFile);
  fileMenu->addAction(openAction);

  m_ApplicationMenuBar->addMenu(fileMenu);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void IMFViewerApplication::openFile()
{
  if (m_ActiveInstance != nullptr)
  {
    m_Controller->openFile(m_ActiveInstance);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IMFViewer_UI* IMFViewerApplication::getNewIMFViewerInstance()
{
  // Create new DREAM3D instance
  IMFViewer_UI* newInstance = new IMFViewer_UI(NULL);
  newInstance->setAttribute(Qt::WA_DeleteOnClose);
  newInstance->setWindowTitle("IMF Viewer");

  #if defined(Q_OS_WIN)
  newInstance->setMenuBar(m_ApplicationMenuBar);
  #endif

  setActiveInstance(newInstance);

  return newInstance;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void IMFViewerApplication::loadStyleSheet(const QString &sheetName)
{
  QFile file(":/Resources/StyleSheets/" + sheetName.toLower() + ".qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QString::fromLatin1(file.readAll());
  qApp->setStyleSheet(styleSheet);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void IMFViewerApplication::setActiveInstance(IMFViewer_UI* instance)
{
  if (instance == nullptr)
  {
    return;
  }

  // Disconnections from the old instance
  if (m_ActiveInstance != nullptr)
  {

  }

  // Connections to the new instance

  m_ActiveInstance = instance;
}





