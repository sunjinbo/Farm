/* ====================================================================
 * File: Farm.pan
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __FARM_PAN__
#define __FARM_PAN__

/** Farm application panic codes */
enum TFarmPanics 
    {
    EFarmBasicUi = 1
    // add further panics here
    };

inline void Panic(TFarmPanics aReason)
    {
    _LIT(applicationName,"Farm");
    User::Panic(applicationName, aReason);
    }

#endif // __FARM_PAN__
