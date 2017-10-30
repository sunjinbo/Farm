/* ====================================================================
 * File: FarmLevel.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDS 
#include <barsread.h>
#include <Farm.rsg>
#include "FarmLevel.h"

// CONSTANS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmLevel::NewL
// ----------------------------------------------------------------------------
//
CFarmLevel* CFarmLevel::NewL( TResourceReader& aReader )
    {
    CFarmLevel* self = new (ELeave) CFarmLevel;
    CleanupStack::PushL(self);
    self->ConstructL(aReader);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmLevel::Id
// ----------------------------------------------------------------------------
//
TInt CFarmLevel::Id() const
    {
    return iId;
    }

// ----------------------------------------------------------------------------
// CFarmLevel::Score
// ----------------------------------------------------------------------------
//
TInt CFarmLevel::Score() const
    {
    return iScore;    
    }

// ----------------------------------------------------------------------------
// CFarmLevel::Bonus
// ----------------------------------------------------------------------------
//
TInt CFarmLevel::Bonus() const
    {
    return iBonus;
    }

// ----------------------------------------------------------------------------
// CFarmLevel::Timeout
// ----------------------------------------------------------------------------
//
TInt CFarmLevel::Timeout() const
    {
    return iTimeout;
    }

// ----------------------------------------------------------------------------
// CFarmLevel::GetFence
// ----------------------------------------------------------------------------
//
void CFarmLevel::GetFence( RArray<TFence>& aFence ) const
    {
    for ( TInt i = 0; i < iFence.Count(); i++ )
        {
        aFence.Append( iFence[i] );
        }
    }

// ----------------------------------------------------------------------------
// CFarmLevel::Compare
// ----------------------------------------------------------------------------
//
TInt CFarmLevel::Compare( const CFarmLevel& aFirst, const CFarmLevel& aSecond )
    {
     if ( aFirst.Id() > aSecond.Id() )
      return 1; 
     if ( aFirst.Id() < aSecond.Id() )
      return -1;
    return 0;
    }

// ----------------------------------------------------------------------------
// CFarmLevel::~CFarmLevel
// ----------------------------------------------------------------------------
//
CFarmLevel::~CFarmLevel()
    {
    iFence.Close();
    }

// ----------------------------------------------------------------------------
// CFarmLevel::ConstructL
// ----------------------------------------------------------------------------
//
void CFarmLevel::ConstructL( TResourceReader& aReader )
    {
    iId = aReader.ReadUint32();
    iScore = aReader.ReadUint32();
    iBonus = aReader.ReadUint32();
    iTimeout = aReader.ReadUint32();
    TInt num = aReader.ReadInt16();
    for ( TInt ix = 0; ix < num; ix++ )
        {
        TFence theFence;
        theFence.iType = aReader.ReadUint32();
        theFence.iCell.iX = aReader.ReadUint32();
        theFence.iCell.iY = aReader.ReadUint32();
        theFence.iLength = aReader.ReadUint32();
        iFence.Append( theFence );
        }
    }

// ----------------------------------------------------------------------------
// CFarmLevel::CFarmLevel
// ----------------------------------------------------------------------------
//
CFarmLevel::CFarmLevel()
    { // no implementation required
    }

// End of File
