/* ====================================================================
 * File: Stopwatch.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_STOPWATCH_H
#define C_STOPWATCH_H

// INCLUDS
#include <e32std.h>
#include <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitGc;
class CEikonEnv;
class CBmpUtils;
class MStopwatchObserver;

class CStopwatch : public CTimer
    {
public:
    static CStopwatch* NewL(
           MStopwatchObserver& aObserver,
        CFbsBitGc& aGc, 
        const TRect& aRect );
    virtual ~CStopwatch();

public: // New functions
    void SetLevel( TInt aLevel );
    void SetTimeout( TInt aTimeout );
    void Start();
    void Stop();
    TInt Timeout() const;
    void DoDraw();

private: // Constructor
    void ConstructL( const TRect& aRect );
    CStopwatch( MStopwatchObserver& aObserver, CFbsBitGc& aGc);

private: // From CTimer
    void RunL();
    void DoCancel();

private: // New functions

private: // Data
    MStopwatchObserver& iObserver;
    CFbsBitGc& iGc;
    CEikonEnv* iEikEnv; // Not own.
    HBufC* iLevelText; // Own
    HBufC* iTimeoutText; // Own
    CBmpUtils* iUtils; // Own
    TRect iRect;
    TInt iLevel;
    TInt iTimeout;
    };

#endif // C_STOPWATCH_H

// End of File
