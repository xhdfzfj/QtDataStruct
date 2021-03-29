#ifndef AVLTREECLASS_H
#define AVLTREECLASS_H

#include <iostream>
#include <functional>
#include "./TreeNodeClass.h"

using namespace std;

template < typename NodeCompareValue, typename NodeContentObject >
class AvlTreeClass
{
public:
    AvlTreeClass()
    {
        mRootNodeP = nullptr;
        mUiCallBack = nullptr;
        mMaxLevel = 0;              //代表是空树
    }

    /***********************
     * 函数部份
     * *********************/
    /**
     * @brief fun_JudgeExistCompareValue
     *      要比较的数据是否已经存在
     * @param pValue
     * @return
     *      true 代表已经存在这个值的数据
     *      false 代表不存在这个值的数据
     */
    bool fun_JudgeExistCompareValue( NodeCompareValue pValue )
    {
        bool _retFlag;

        _retFlag = false;

        return _retFlag;
    }

    /**
     * @brief sub_InsertNode
     *      向平衡树中插入数据
     * @param pValue
     * @param pContentObj
     */
    void sub_InsertNode( NodeCompareValue pValue, NodeContentObject pContentObj )
    {
        TreeNodeClass< NodeCompareValue, NodeContentObject > * _tmpNewNodeP;

        _tmpNewNodeP = new TreeNodeClass< NodeCompareValue, NodeContentObject >( pValue, pContentObj );

        if( mRootNodeP == nullptr )
        {
            mRootNodeP = _tmpNewNodeP;
            mRootNodeP->mParentNodeP = nullptr;
            mRootNodeP->mLeftChildP = nullptr;
            mRootNodeP->mRightChildP = nullptr;
            mRootNodeP->SetNodeLevel( 1 );
            mMaxLevel = 1;
        }

        if( mUiCallBack != nullptr )
        {
            mUiCallBack( _tmpNewNodeP );
        }
    }

    /**
     * @brief sub_SetUiDisplayCallBack
     *      设置ui使用回调接口
     * @param pCallBack
     */
    void sub_SetUiDisplayCallBack( function< void( TreeNodeClass< NodeCompareValue, NodeContentObject > * ) > pCallBack )
    {
        mUiCallBack = pCallBack;
    }

    /**
     * @brief fun_GetTreeLevels
     *      获取这个树最大的层数
     * @return
     */
    int fun_GetTreeLevels()
    {
        return mMaxLevel;
    }

    /***********************
     * 变量定义
     * *********************/
private:
    TreeNodeClass< NodeCompareValue, NodeContentObject > * mRootNodeP;
    function< void( TreeNodeClass< NodeCompareValue, NodeContentObject > * ) > mUiCallBack;

    int mMaxLevel;
};

#endif // AVLTREECLASS_H
