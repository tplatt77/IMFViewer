/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _dream3dfiletreemodel_h_
#define _dream3dfiletreemodel_h_

#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

#include "IMFViewer/Dialogs/Utilities/DREAM3DFileItem.h"

class DataContainerArrayProxy;

class DREAM3DFileTreeModel : public QAbstractItemModel
{
    Q_OBJECT

  public:
    SIMPL_TYPE_MACRO(DREAM3DFileTreeModel)

    DREAM3DFileTreeModel(QObject* parent = 0);
    ~DREAM3DFileTreeModel();

    QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    bool isEmpty();

    DREAM3DFileItem::ItemType itemType(const QModelIndex &index) const;
    void setItemType(const QModelIndex &index, DREAM3DFileItem::ItemType itemType);

    bool isChecked(const QModelIndex &index) const;
    void setChecked(const QModelIndex &index, bool checked);

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;

    bool setData(const QModelIndex& index, const QVariant& value, int role) Q_DECL_OVERRIDE;

    /**
     * @brief populateTree
     * @param proxy
     */
    void populateTreeWithProxy(DataContainerArrayProxy proxy);

    /**
     * @brief getSelectedDataContainerNames
     * @return
     */
    QStringList getSelectedDataContainerNames();

  private:
    DREAM3DFileItem*            rootItem;

    DREAM3DFileItem* getItem(const QModelIndex& index) const;

    DREAM3DFileTreeModel(const DREAM3DFileTreeModel&);    // Copy Constructor Not Implemented
    void operator=(const DREAM3DFileTreeModel&);  // Operator '=' Not Implemented
};

#endif // _dream3dfiletreemodel_h_
