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
        mLevel = 0;
        mParentNodeP = nullptr;
        mLeftChildP = nullptr;
        mRightChildP = nullptr;
    }

    /**
     * @brief SetNodeLevel
     *      设置节点的层数
     * @param pLevel
     */
    void SetNodeLevel( int pLevel )
    {
        mLevel = pLevel;
    }

    /**
     * @brief SetNodeLinearPos
     *      设置该节点进行线性保存时的数组下标
     * @param pPosIndex
     */
    void SetLinearPos( int pPosIndex )
    {
        mLinearSavePos = pPosIndex;
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
    int mLevel;         //这个节点的层数
    int mLinearSavePos; //这个节点在线性保存时，在数组中的下标

public: /*相应的属性部份*/
    int GetNodeLevel()  {   return mLevel; }
    int GetLinearPos()  {   return mLinearSavePos; }
};

#endif // TREENODECLASS_H
