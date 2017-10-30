/* ====================================================================
 * File: StoneFence.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_STONEFENCE_H
#define C_STONEFENCE_H

// INCLUDS
#include "Fence.h"

// FORWARD DECLARATIONS
class CBmpUtils;

class CStoneFence : public CFence
    {
public:
    static CStoneFence* NewL( CScene& aScene, TPoint aStartCell, TInt aLength );
    virtual ~CStoneFence();

public: // New functions
    virtual void DoDraw();
    virtual void PushLeft();
    virtual void PushRight();

private: // 2nd constructor
    void ConstructL();
    CStoneFence( CScene& aScene, TPoint aStartCell, TInt aLength );

private: // New functions
    void RectForCells( RArray<TRect>& aCells );

private: // Data
    CBmpUtils* iUtils; // Own
    RArray<TRect> iCells;
    };

#endif // C_STONEFENCE_H

// End of File
