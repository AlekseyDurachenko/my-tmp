#ifndef CTAGMGR_H
#define CTAGMGR_H

#include <QObject>

class CTagMgr : public QObject
{
    Q_OBJECT
public:
    explicit CTagMgr(QObject *parent = 0);
    ~CTagMgr();

signals:

public slots:
};

#endif // CTAGMGR_H
