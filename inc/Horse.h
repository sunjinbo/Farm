/* ====================================================================
 * File: Horse.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_HORSE_H
#define C_HORSE_H

// INCLUDS
#include "Livestock.h"

// FORWARD DECLARATIONS
class CBmpUtils;

class CHorse : public CLivestock
    {
public:
    static CHorse* NewL(CScene& aScene,const TPoint& aCell);
    virtual ~CHorse();

public: // New functions
    virtual void DoDraw();
    virtual TLivestockType Type() const;

private:
    virtual void ConstructL();
    CHorse(CScene& aScene,const TPoint& aCell);


private: // Data
    CBmpUtils* iUtils;
    TBool iFirstIcon;
    };

#endif // C_HORSE_H

// End of File

