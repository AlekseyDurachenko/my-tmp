// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "ctagmgr.h"
#include "cmgr.h"


CTagMgr::CTagMgr(CMgr *mgr) : QObject(mgr)
{
    m_mgr = mgr;
    m_rootItem = new CTagItem(CTag(), this, 0);
}

CTagMgr::~CTagMgr()
{
    delete m_rootItem;
}

CTagItem *CTagMgr::findByPath(const QStringList &path) const
{
    CTagItem *item = rootItem();
    for (int index = 0; index < path.count() && item; ++index)
        item = item->find(path.at(index));

    return item;
}

void CTagMgr::callbackAboutToInserted(CTagItem *parent, int first, int last)
{
    emit aboutToInserted(parent, first, last);
}

void CTagMgr::callbackInserted(CTagItem *parent, int first, int last)
{
    emit inserted(parent, first, last);
}

void CTagMgr::callbackAboutToRemoved(CTagItem *parent, int first, int last)
{
    emit aboutToRemoved(parent, first, last);
}

void CTagMgr::callbackRemoved(CTagItem *parent, int first, int last)
{
    emit removed(parent, first, last);
}

void CTagMgr::callbackAboutToMoved(CTagItem *sourceParent, int sourceFirst,
        int sourceLast, CTagItem *destinationParent, int destinationIndex)
{
    emit aboutToMoved(sourceParent, sourceFirst, sourceLast,
                      destinationParent, destinationIndex);
}

void CTagMgr::callbackMoved(CTagItem *sourceParent, int sourceFirst,
        int sourceLast, CTagItem *destinationParent, int destinationIndex)
{
    emit aboutToMoved(sourceParent, sourceFirst, sourceLast,
                      destinationParent, destinationIndex);
}

void CTagMgr::callbackDataChanged(CTagItem *item)
{
    emit dataChanged(item);
}

void CTagMgr::callbackBookmarksChanged(CTagItem *item)
{
    emit bookmarksChanged(item);
}
