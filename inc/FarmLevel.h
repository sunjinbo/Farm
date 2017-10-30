/* ====================================================================
 * File: FarmLevel.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_FARMLEVEL_H
#define C_FARMLEVEL_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class TResourceReader;

class TFence
    {
public: // Data
    TInt iType;
    TPoint iCell;
    TInt iLength;
    };

class CFarmLevel : public CBase
    {
public:
    static CFarmLevel* NewL( TResourceReader& aReader );
    virtual ~CFarmLevel();

public: // New functions
    TInt Id() const;
    TInt Score() const;
    TInt Bonus() const;
    TInt Timeout() const;
    void GetFence( RArray<TFence>& aFence ) const;
    static TInt Compare( const CFarmLevel& aFirst, const CFarmLevel& aSecond );

private:
    void ConstructL( TResourceReader& aReader );
    CFarmLevel();

private: // Data
    TInt iId;
    TInt iScore;
    TInt iBonus;
    TInt iTimeout;
    RArray<TFence> iFence;
    };

#endif // C_FARMLEVEL_H

// End of File
