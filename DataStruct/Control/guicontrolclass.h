#ifndef GUICONTROLCLASS_H
#define GUICONTROLCLASS_H

#include <QObject>
#include "./memorydisplayclass.h"

class GuiControlClass : public QObject
{
    Q_OBJECT
public:
    explicit GuiControlClass(QObject *parent = nullptr);
    void sub_SignalConntectSlot();

    Q_INVOKABLE void sub_ActiveCLanguageJsonBut( QObject * pDestObjP );
    Q_INVOKABLE void sub_CjsonMemoryTest( void );

private:
    MemoryDisplayClass * mMemoryDisplayObjP;

signals:
    void guiCLanguageJsonButClickSig();

public slots:
    void guiCLanguageJsonButClickSlot();
};

#endif // GUICONTROLCLASS_H
