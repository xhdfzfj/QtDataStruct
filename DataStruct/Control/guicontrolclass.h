#ifndef GUICONTROLCLASS_H
#define GUICONTROLCLASS_H

#include <QObject>

class GuiControlClass : public QObject
{
    Q_OBJECT
public:
    explicit GuiControlClass(QObject *parent = nullptr);
    void sub_SignalConntectSlot();

    Q_INVOKABLE void sub_ActiveCLanguageJsonBut();

signals:
    void guiCLanguageJsonButClickSig();

public slots:
    void guiCLanguageJsonButClickSlot();
};

#endif // GUICONTROLCLASS_H
