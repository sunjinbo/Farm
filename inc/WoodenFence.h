/* ====================================================================
 * File: WoodenFence.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_WOODENFENCE_H
#define C_WOODENFENCE_H

// INCLUDES
#include "Fence.h"

// FORWARD DECLARATIONS
class CBmpUtils;
class CPeriodic;

class CWoodenFence : public CFence
    {
public:
    static CWoodenFence* NewL(CScene& aScene,TPoint aStartCell);
    virtual ~CWoodenFence();

public: // New functions
    virtual void DoDraw();
    virtual void DoRecovery();
    virtual void PushLeft();
    virtual void PushRight();

private: // Constructor
    void ConstructL();
    CWoodenFence(CScene& aScene, TPoint aStartCell);

private: // New methods
    static TInt TimerCallback( TAny* aPtr );
    void Start();

private: // Member data
    CBmpUtils* iUtils; // Own
    CPeriodic* iPeriodic; // Own
    };

#endif // C_WOODENFENCE_H

// End of File
