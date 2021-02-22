#include "./Common.h"

/**
 * @brief sub_IntToHex
 * @param pValue
 * @param pRetString
 * @param pWidth
 */
void sub_IntToHex( int pValue, QString & pRetString, int pWidth )
{
    pRetString = QString::number( pValue, 16 );
    pRetString = pRetString.toUpper();
    if( pRetString.size() < pWidth )
    {
        pRetString = QString( pWidth - pRetString.size(), '0' ) + pRetString;
    }
}

