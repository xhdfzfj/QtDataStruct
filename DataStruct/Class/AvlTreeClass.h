#ifndef AVLTREECLASS_H
#define AVLTREECLASS_H

#include <list>
#include <queue>
#include <iostream>
#include <functional>
#include <math.h>
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
     *      向树中插入节点
     * @param pParentNodeP
     * @param pDestNodeP
     */
    void sub_InsertNodeInTree( TreeNodeClass< NodeCompareValue, NodeContentObject > * pParentNodeP,
                               TreeNodeClass< NodeCompareValue, NodeContentObject > * pDestNodeP )
    {
        TreeNodeClass< NodeCompareValue, NodeContentObject > * _tmpNodeP;

        if( pDestNodeP->mCompareValue > pParentNodeP->mCompareValue )
        {
            _tmpNodeP = pParentNodeP->mRightChildP;
            if( _tmpNodeP == nullptr )
            {
                pParentNodeP->mRightChildP = pDestNodeP;
                pDestNodeP->SetNodeLevel( pParentNodeP->GetNodeLevel() + 1 );
                pDestNodeP->mParentNodeP = pParentNodeP;
            }
            else
            {
                sub_InsertNodeInTree( _tmpNodeP, pDestNodeP );
            }
        }
        else
        {
            _tmpNodeP = pParentNodeP->mLeftChildP;
            if( _tmpNodeP == nullptr )
            {
                pParentNodeP->mLeftChildP = pDestNodeP;
                pDestNodeP->SetNodeLevel( pParentNodeP->GetNodeLevel() + 1 );
                pDestNodeP->mParentNodeP = pParentNodeP;
            }
            else
            {
                sub_InsertNodeInTree( _tmpNodeP, pDestNodeP );
            }
        }

        if( pDestNodeP->GetNodeLevel() > mMaxLevel )
        {
            mMaxLevel = pDestNodeP->GetNodeLevel();
        }
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
        TreeNodeClass< NodeCompareValue, NodeContentObject > * _tmpNodeP;

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
        else
        {
            _tmpNodeP = mRootNodeP;

            sub_InsertNodeInTree( _tmpNodeP, _tmpNewNodeP );
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

    /**
     * @brief fun_LevelTraversal
     *      进行层遍历
     * @return
     */
    list< TreeNodeClass< NodeCompareValue, NodeContentObject > * > fun_LevelTraversal()
    {
        list< TreeNodeClass< NodeCompareValue, NodeContentObject > * > _retList;
        queue< TreeNodeClass< NodeCompareValue, NodeContentObject > * > _tmpQueue;
        TreeNodeClass< NodeCompareValue, NodeContentObject > * _tmpNodeP;
        TreeNodeClass< NodeCompareValue, NodeContentObject > ** _tmpNodeArrayP;

        _tmpNodeArrayP = new TreeNodeClass< NodeCompareValue, NodeContentObject > * [ ( int )( pow( 2, mMaxLevel ) - 1 ) ];

        int i, _tmpLen;
        int _index;

        _tmpLen = ( int )( pow( 2, mMaxLevel ) - 1 );
        for( i = 0; i < _tmpLen; i++ )
        {
            _tmpNodeArrayP[ i ] = nullptr;
        }

        if( mRootNodeP != nullptr )
        {
            _tmpQueue.push( mRootNodeP );
            while( !_tmpQueue.empty() )
            {
                _tmpNodeP = _tmpQueue.front();
                _tmpQueue.pop();

                if( _tmpNodeP != nullptr )
                {
                    if( _tmpNodeP->mParentNodeP == nullptr )
                    {
                        _tmpNodeArrayP[ 0 ] = _tmpNodeP;
                        _tmpNodeP->SetLinearPos( 0 );
                    }
                    else
                    {
                        if( _tmpNodeP == _tmpNodeP->mParentNodeP->mLeftChildP )
                        {
                            _index = _tmpNodeP->mParentNodeP->GetLinearPos();
                            _index *= 2;
                            _index += 1;
                            _tmpNodeP->SetLinearPos( _index );
                        }
                        else
                        {
                            _index = _tmpNodeP->mParentNodeP->GetLinearPos();
                            _index *= 2;
                            _index += 2;
                            _tmpNodeP->SetLinearPos( _index );
                        }

                        _tmpNodeArrayP[ _index ] = _tmpNodeP;
                    }
                }

                if( _tmpNodeP->mLeftChildP != nullptr )
                {
                    _tmpQueue.push( _tmpNodeP->mLeftChildP );
                }
                if( _tmpNodeP->mRightChildP != nullptr )
                {
                    _tmpQueue.push( _tmpNodeP->mRightChildP );
                }
            }

            for( i = 0; i < _tmpLen; i++ )
            {
                _retList.push_back( _tmpNodeArrayP[ i ] );
            }
        }

        delete [] _tmpNodeArrayP;
        return _retList;
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
