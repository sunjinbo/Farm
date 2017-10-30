/* ====================================================================
 * File: FarmFactory.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include <Farm.rsg>
#include "FarmFactory.h"
#include "FarmLevel.h"
#include "Fence.hrh"
#include "StoneFence.h"
#include "WoodenFence.h"
#include "Scene.h"

// CONSTANS
const TInt KDefaultLevel = 0;
_LIT( KFarmResourceFile, "\\resource\\apps\\farm.rsc" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFarmFactory::NewL
// ----------------------------------------------------------------------------
//
CFarmFactory* CFarmFactory::NewL(
    MFactoryObserver& aObserver,CScene& aScene)
    {
    CFarmFactory* self = new (ELeave) CFarmFactory(aObserver,aScene);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::~CFarmFactory
// ----------------------------------------------------------------------------
//
CFarmFactory::~CFarmFactory()
    {
    iFarmLevelArray.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Next
// ----------------------------------------------------------------------------
//
void CFarmFactory::Next()
    {
    iScene.ResetAll();
    CFarmLevel* level = iFarmLevelArray[iCurrentLevel];
    RArray<TFence> fence;
    level->GetFence( fence );
    for ( TInt i = 0; i < fence.Count(); i++ )
        {
        switch( fence[i].iType )
            {
            case EStoneFence:
                {
                iScene.AppendFence( 
                    CStoneFence::NewL( 
                    iScene, fence[i].iCell, fence[i].iLength )
                    );
                }
                break;
            case EWoodenFence:
                {
                iScene.AppendFence( 
                    CWoodenFence::NewL( iScene, fence[i].iCell )
                    );
                }
                break;
            default:
                break;
            }
        }
    fence.Close();
    iObserver.Updated();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Restore
// ----------------------------------------------------------------------------
//
void CFarmFactory::Restore()
    {
    iCurrentLevel = 0;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Done
// ----------------------------------------------------------------------------
//
void CFarmFactory::Done()
    {
    ++iCurrentLevel;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Id
// ----------------------------------------------------------------------------
//
TInt CFarmFactory::Id() const
    {
    return iFarmLevelArray[ iCurrentLevel ]->Id();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Score
// ----------------------------------------------------------------------------
//
TInt CFarmFactory::Score() const
    {
    return iFarmLevelArray[ iCurrentLevel ]->Score();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Bonus
// ----------------------------------------------------------------------------
//
TInt CFarmFactory::Bonus() const
    {
    return iFarmLevelArray[ iCurrentLevel ]->Bonus();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Timeout
// ----------------------------------------------------------------------------
//
TInt CFarmFactory::Timeout() const
    {
    return iFarmLevelArray[ iCurrentLevel ]->Timeout() * 30;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CFarmFactory::ConstructL()
    {
    RFs& fs = iCoeEnv.FsSession();
    TFileName fileName( KFarmResourceFile );
    TInt err = CompleteWithAppPath( fileName );
    if ( err != KErrNotSupported )
        {
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fs, fileName );
    
    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fs, fileName ) )
        {
        User::Leave( KErrNotFound );
        }

    TRAP( err, iResFileOffset = iCoeEnv.AddResourceFileL( fileName ) );

    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, R_FARM_LEVELS );

    TRAP( err, ReadLevelL( reader ) );
    if ( err )
        {
        iFarmLevelArray.ResetAndDestroy();
        User::Leave( err );
        }

    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( iResFileOffset );
    iResFileOffset = 0;
    
    iCurrentLevel = KDefaultLevel;
    }

// ----------------------------------------------------------------------------
// CFarmFactory::CFarmFactory
// ----------------------------------------------------------------------------
//
CFarmFactory::CFarmFactory(MFactoryObserver& aObserver,CScene& aScene)
    : iCoeEnv( *CCoeEnv::Static() ), 
    iObserver( aObserver ), iScene( aScene )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CFarmFactory::ReadLevelL
// ----------------------------------------------------------------------------
//
void CFarmFactory::ReadLevelL( TResourceReader& aReader )
    {
    TInt num = aReader.ReadInt16();

    // Add all newly created CFarmLevel objects to the array
    for ( TInt ix = 0; ix < num; ix++ )
        {
        CFarmLevel* level = CFarmLevel::NewL( aReader );
        iFarmLevelArray.Append( level );
        }
    // Sorts these levels by id
    Sort();
    }

// ----------------------------------------------------------------------------
// CFarmFactory::Sort
// ----------------------------------------------------------------------------
//
void CFarmFactory::Sort()
    {
    TLinearOrder<CFarmLevel> order( CFarmLevel::Compare );
    iFarmLevelArray.Sort( order );
    }


// End of File
