/* ====================================================================
 * File: Cow.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_COW_H
#define C_COW_H

// INCLUDES
#include "Livestock.h"

// FORWARD DECLARATIONS
class CBmpUtils;

class CCow : public CLivestock
    {
public:
    static CCow* NewL(CScene& aScene,const TPoint& aCell);
    virtual ~CCow();

public: // New functions
    virtual void DoDraw();
    virtual TLivestockType Type() const;

private:
    virtual void ConstructL();
    CCow(CScene& aScene,const TPoint& aCell);

private: // Data
    CBmpUtils* iUtils;
    TBool iFirstIcon;
    };

#endif // C_COW_H

// End of File

