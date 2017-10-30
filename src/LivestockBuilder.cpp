/* ====================================================================
 * File: LivestockBuilder.cpp
 * Created: 01/20/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include "LivestockBuilder.h"
#include "Sheep.h"
#include "Cow.h"
#include "Pig.h"
#include "Horse.h"
#include "Scene.h"

// CONSTANS
const TInt KMaxEntranceNum = 4;
const TInt KLivestockBuilderDelayTimeout = 0;
const TInt KLivestockBuilderIntervalTimeout = 10000000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CLivestockBuilder::NewL
// ----------------------------------------------------------------------------
//
CLivestockBuilder* CLivestockBuilder::NewL(
    CScene& aScene, MLivestockBuilderObserver& aObserver)
    {
    CLivestockBuilder* self = new (ELeave) CLivestockBuilder(aScene, aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::~CLivestockBuilder
// ----------------------------------------------------------------------------
//
CLivestockBuilder::~CLivestockBuilder()
    {
    if ( iPeriodic )
        {
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::DoCreate
// ----------------------------------------------------------------------------
//
void CLivestockBuilder::DoCreate()
    {
    TLivestockType type = ( TLivestockType )( Rand( ELivestockLastElement ) );
    CLivestock* livestock = NULL;
    TRAPD( err,  livestock = CreateLivestockL( type ) );
    if ( err == KErrNone )
        {
        iObserver.NewLivestock( livestock );
        }
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::Start
// ----------------------------------------------------------------------------
//
void CLivestockBuilder::Start()
    {
    if ( iPeriodic && !iPeriodic->IsActive() )
        {
        iPeriodic->Start(
                KLivestockBuilderDelayTimeout,
                KLivestockBuilderIntervalTimeout,
                TCallBack( TimerCallback, this )
                );
        }
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::Stop
// ----------------------------------------------------------------------------
//
void CLivestockBuilder::Stop()
    {
    if ( iPeriodic && iPeriodic->IsActive() )
        {
        iPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::ConstructL
// ----------------------------------------------------------------------------
//
void CLivestockBuilder::ConstructL()
    {
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::CLivestockBuilder
// ----------------------------------------------------------------------------
//
CLivestockBuilder::CLivestockBuilder(CScene& aScene, MLivestockBuilderObserver& aObserver)
    : iScene( aScene ), iObserver( aObserver )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CLivestockBuilder::TimerCallback( TAny* aPtr )
    {
    CLivestockBuilder* self = static_cast<CLivestockBuilder*> ( aPtr );
    self->DoCreate();
    return 0;
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::Rand
// ----------------------------------------------------------------------------
//
TInt CLivestockBuilder::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::CreateLivestockL
// ----------------------------------------------------------------------------
//
CLivestock* CLivestockBuilder::CreateLivestockL( TLivestockType aType )
    {
    CLivestock* livestock( NULL );
    TPoint entrance( RandEntrancePosition() );

    switch( aType )
        {
        case ESheepType:
            livestock = CSheep::NewL( iScene, entrance );
            break;
        case ECowType:
            livestock = CCow::NewL( iScene, entrance );
            break;
        case EPigType:
            livestock = CPig::NewL( iScene, entrance );
            break;
        case EHorseType:
            livestock = CHorse::NewL( iScene, entrance );
            break;
        default:
            User::LeaveIfNull( livestock );
            break;
        }

    return livestock;
    }

// ----------------------------------------------------------------------------
// CLivestockBuilder::RandEntrancePosition
// ----------------------------------------------------------------------------
//
TPoint CLivestockBuilder::RandEntrancePosition() const
    {
    TFixedArray<TPoint, KMaxEntranceNum> entrances;
    entrances[ 0 ] = TPoint( 2, -1 );
    entrances[ 1 ] = TPoint( 4, -1 );
    entrances[ 2 ] = TPoint( 6, -1 );
    entrances[ 3 ] = TPoint( 8, -1 );
    TInt rand = Rand( KMaxEntranceNum );
    return entrances[ rand ];
    }

// End of File
