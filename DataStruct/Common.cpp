#include "./Common.h"


void sub_IntToHex( int pValue, QString & pRetString, int pWidth )
{
    pRetString = QString::number( pValue, 16 );
    if( pRetString.size() < pWidth )
    {
        pRetString = QString( pWidth - pRetString.size(), '0' ) + pRetString;
        pRetString = pRetString.toUpper();
    }
}

