/* ====================================================================
 * File: Sheep.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SHEEP_H
#define C_SHEEP_H

// INCLUDS
#include "Livestock.h"

// FORWARD DECLARATIONS
class CBmpUtils;

class CSheep : public CLivestock
    {
public:
    static CSheep* NewL(CScene& aScene,const TPoint& aCell);
    virtual ~CSheep();

public: // New functions
    virtual void DoDraw();
    virtual TLivestockType Type() const;

private:
    virtual void ConstructL();
    CSheep(CScene& aScene,const TPoint& aCell);

private: // Data
    CBmpUtils* iUtils;
    TBool iFirstIcon;
    };

#endif // C_SHEEP_H

// End of File
