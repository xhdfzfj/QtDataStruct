#ifndef TREENODECLASS_H
#define TREENODECLASS_H

/*******************************
 * 数据类型定义
 * *****************************/
template < typename CompareT, typename ContentObject >
class TreeNodeClass
{
public:
    TreeNodeClass( CompareT pCompareValue, ContentObject pConteObj )
    {
        mCompareValue = pCompareValue;
        mContentObj = pConteObj;
        mNodeHight = 0;
    }

    /*******************************
     * 以下是变量定义
     * *****************************/
public:
    CompareT mCompareValue;             //进行比较的值
    ContentObject mContentObj;          //实际要保存的值

    TreeNodeClass * mParentNodeP;
    TreeNodeClass * mLeftChildP;
    TreeNodeClass * mRightChildP;

private:
    int mNodeHight;     //这个节点的高度
};

#endif // TREENODECLASS_H
