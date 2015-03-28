#ifndef THINGMIMEDATA_H
#define THINGMIMEDATA_H

#include <QMimeData>
#include <QStringList>
#include "thing.h"

class ThingMimeData:public QMimeData
{
    Q_OBJECT
public:
    ThingMimeData():QMimeData()
    {
        m_thingDragList = NULL;
    }

    ~ThingMimeData()
    {
        if(m_thingDragList)
        {
            delete m_thingDragList;
        }
    }

    void setDragDatas(QString mimeType, QList<Thing*> *tempThingList)
    {
        m_format << mimeType;
        m_thingDragList = tempThingList;
    }

    QStringList formats() const
    {
        return m_format;
    }

    const QList<Thing*>* thingDragData() const
    {
        return m_thingDragList;
    }

protected:
    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const
    {
        if(mimetype == "ThingMimeData")
        {
            return m_thingDragList;
        } else {
            return QMimeData::retrieveData(mimetype,preferredType);
        }
    }


private:
    QStringList             m_format;
    const QList<Thing*>     *m_thingDragList;
};

#endif // THINGMIMEDATA_H
