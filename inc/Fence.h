/* ====================================================================
 * File: Fence.h
 * Created: 12/24/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_FENCE_H
#define C_FENCE_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class CScene;

class CFence : public CBase
    {
public: // Destructor.
    virtual ~CFence();

public: // New functions
    virtual void DoDraw() = 0;
    virtual void PushLeft() = 0;
    virtual void PushRight() = 0;

public:
    void GetCells( RArray<TPoint>& aCells );

protected:
    virtual void ConstructL();
    CFence( CScene& aScene, const TPoint& aStartCell, TInt aLength );

protected: // New functions
    TRect Rect() const;

protected: // Data
    CScene& iScene;
    TPoint iStartCell;
    TInt iLength;
    enum TFenceState
        {
        EVertical = 0,
        EInclinedLeft,
        EInclinedRight
        };
    TFenceState iState;
    };

#endif // C_FENCE_H

// End of File
