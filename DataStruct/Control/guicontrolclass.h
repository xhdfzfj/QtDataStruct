#ifndef GUICONTROLCLASS_H
#define GUICONTROLCLASS_H

#include <QObject>
#include "./Class/AvlTreeClass.h"
#include "./memorydisplayclass.h"

class GuiControlClass : public QObject
{
    Q_OBJECT
public:
    explicit GuiControlClass(QObject *parent = nullptr);
    void sub_SignalConntectSlot();
    void sub_AvlTreeCallBack( TreeNodeClass< int, int > * pNewNode );

    Q_INVOKABLE void sub_ActiveCLanguageJsonBut( QObject * pDestObjP );
    Q_INVOKABLE void sbu_ActiveAvlTreeBut( QObject * pDestObjP );
    Q_INVOKABLE void sub_CjsonMemoryTest( void );
    Q_INVOKABLE void sub_AvlTreeAddNode( void );
    Q_INVOKABLE void sub_DebugFunction( void );

    Q_PROPERTY( QString mGuiDebugBut1Text READ GetDebugButTitle );
    Q_PROPERTY( qreal mGuiContentWidth READ GetContentWidth NOTIFY guiContentWidthChange )

public:
    QString GetDebugButTitle()  { return mDebugBut1Text; }
    qreal   GetContentWidth();
    void    SetContentWidth( qreal pWidth );

    /****************************
     * 变量定义
     * *************************/
private:
    MemoryDisplayClass * mMemoryDisplayObjP;
    AvlTreeClass< int, int > * mAvlTreeObjP;
    QString mDebugBut1Text;
    qreal mContentWidth;

    /**************************
     * 信号与槽
     * ***********************/
signals:
    void guiCLanguageJsonButClickSig();
    void guiAvlTreeButClickSig();           //Avltree测试准备信号量
    void guiContentWidthChange();

public slots:
    void guiAvlTreeButClickSlot();          //接收Avltree测试准备信号量
    void guiCLanguageJsonButClickSlot();
    void MemoryItemWidthChangedSlot();
};

#endif // GUICONTROLCLASS_H
