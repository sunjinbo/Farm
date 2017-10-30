/* ====================================================================
 * File: MainMenu.cpp
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <gdi.h>
#include <AknUtils.h>
#include <fbs.h>
#include <barsread.h>
#include <MainMenu.mbg>
#include "Farm.pan"
#include "MainMenu.h"
#include "MenuObserver.h"
#include "BmpUtils.h"

// CONSTANTS
const TInt KEffectsDelayTimeout = 0;
const TInt KEffectsIntervalTimeout = 50000;

#if defined( __WINS__ )
_LIT( KMainMenuFileName, "Z:\\resource\\apps\\mainmenu.mbm" );
#else
_LIT( KMainMenuFileName, "\\resource\\apps\\mainmenu.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TMenuItem::Compare
// ----------------------------------------------------------------------------
//
TInt TMenuItem::Compare( const TMenuItem& aFirst, const TMenuItem& aSecond )
    {
     if ( aFirst.iItemId > aSecond.iItemId )
      return 1; 
     if ( aFirst.iItemId < aSecond.iItemId )
      return -1;
    return 0;
    }

// ----------------------------------------------------------------------------
// CMenuButton::NewL
// ----------------------------------------------------------------------------
//
CMainMenu* CMainMenu::NewL(
            MMenuObserver& aObserver,
            CFbsBitGc& aGc, 
            const TRect& aRect )
    {
    CMainMenu* self = new (ELeave) CMainMenu(aObserver,aGc);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CMenuButton::~CMainMenu
// ----------------------------------------------------------------------------
//
CMainMenu::~CMainMenu()
    {
    iMenuItems.Close();
    if ( iEffects )
        {
        iEffects->Cancel();
        delete iEffects;
        }
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CMenuButton::DoDraw
// ----------------------------------------------------------------------------
//
void CMainMenu::DoDraw()
    {
    __ASSERT_ALWAYS( iMenuItems.Count() > 0, Panic(EFarmBasicUi) );
    iGc.SetBrushColor( KRgbCyan );
    iGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    iGc.SetPenColor( KRgbBlack );
    iGc.SetPenStyle( CGraphicsContext::ESolidPen );

    const CFont* font 
        = AknLayoutUtils::FontFromId(EAknLogicalFontSecondaryFont);
     iGc.UseFont( font );

    TSize itemSize;
    itemSize.iWidth = Size().iWidth;
    TInt count( iMenuItems.Count() );
    if ( count  > 0 )
        {
        itemSize.iHeight = Size().iHeight / iMenuItems.Count();
        }
    else
        {
        itemSize.iHeight = Size().iHeight;
        }

    iGc.SetBrushStyle( CGraphicsContext::ENullBrush );

    TPoint tl( iRect.iTl );
    for ( TInt i = 0; i < count; i++ )
        {
        TRect itemRect;
        itemRect.SetRect( tl, itemSize );
        itemRect.Shrink( 2, 2 );

        
        iGc.BitBltMasked( 
                    itemRect.iTl,
                    iUtils->Bitmap( EMbmMainmenuBak ),
                    TRect( TPoint( 0, 0 ), itemRect.Size() ),
                    iUtils->Bitmap( EMbmMainmenuBak_mask ),
                    ETrue
                    );

        iGc.DrawText( 
                    iMenuItems[i].iText, 
                    itemRect, 
                    30, 
                    CGraphicsContext::ECenter, 
                    0 
                    );

        tl.iY += itemSize.iHeight;
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Append
// ----------------------------------------------------------------------------
//
TInt CMainMenu::Append( const TMenuItem& aItem )
    {
    TRAPD( err, iMenuItems.Append( aItem ) );
    Sort();
    return err;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Remove
// ----------------------------------------------------------------------------
//
TInt CMainMenu::Remove( TInt aItemId )
    {
    for ( TInt i = 0; i < iMenuItems.Count(); i++ )
        {
        if ( iMenuItems[i].iItemId == aItemId )
            {
            iMenuItems.Remove( i );
            return KErrNone;
            }
        }
    return KErrNotFound;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Count
// ----------------------------------------------------------------------------
//
TInt CMainMenu::Count() const
    {
    return iMenuItems.Count();
    }

// ----------------------------------------------------------------------------
// CMenuButton::At
// ----------------------------------------------------------------------------
//
const TMenuItem& CMainMenu::At( TInt aIndex ) const
    {
    __ASSERT_ALWAYS( aIndex == 0, Panic( EFarmBasicUi ) );
    return iMenuItems[ aIndex ];
    }

// ----------------------------------------------------------------------------
// CMenuButton::Start
// ----------------------------------------------------------------------------
//
void CMainMenu::Start()
    {
    if ( iEffects && !iEffects->IsActive() )
        {
        iRect.iTl.iX= - iRect.Width();
        iEffects->Start(
                    KEffectsDelayTimeout,
                    KEffectsIntervalTimeout,
                    TCallBack( TimerCallback, this )
                );
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::DoEffects
// ----------------------------------------------------------------------------
//
void CMainMenu::DoEffects()
    {
    if ( iRect.iTl.iX > Rect().iTl.iX )
        {
        // Stop effects
        iEffects->Cancel();
        }
    else
        {
        iRect.Move( 10, 0 );
        }
    }

// ----------------------------------------------------------------------------
// CMainMenu::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
void CMainMenu::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt num = aReader.ReadInt16();

    for ( TInt ix = 0; ix < num; ix++ )
        {
        TMenuItem newItem;
        newItem.iItemId = aReader.ReadUint32();
        HBufC* txt = aReader.ReadHBufCL();
        newItem.iText.Append( *txt );
        delete txt;
        txt = NULL;
        Append( newItem );
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Draw
// ----------------------------------------------------------------------------
//
void CMainMenu::Draw()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CMenuButton::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CMainMenu::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            break;
        case TPointerEvent::EDrag:
            break;
        case TPointerEvent::EButton1Up:
            ProcessPressedL( aPointerEvent.iPosition );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::ConstructL
// ----------------------------------------------------------------------------
//
void CMainMenu::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iRect = aRect;

    iUtils = CBmpUtils::NewL( 
            KMainMenuFileName,
            EMbmMainmenuBak,
            EMbmMainmenuLastElement
            );

    // For effects
    iEffects = CPeriodic::NewL( CActive::EPriorityUserInput );
    iEffects->Cancel();
    Start();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CMenuButton::CMainMenu
// ----------------------------------------------------------------------------
//
CMainMenu::CMainMenu(MMenuObserver& aObserver,CFbsBitGc& aGc)
    : iObserver( aObserver ), iGc( aGc )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CMenuButton::ProcessPressedL
// ----------------------------------------------------------------------------
//
void CMainMenu::ProcessPressedL( const TPoint& aPosition )
    {
    TSize itemSize;
    itemSize.iWidth = Size().iWidth;
    TInt count( iMenuItems.Count() );
    if ( count == 0 ) return;
    itemSize.iHeight = 
        Size().iHeight / iMenuItems.Count();

    TPoint tl( Rect().iTl );
    for ( TInt i = 0; i < count; i++ )
        {
        TRect itemRect;
        itemRect.SetRect( tl, itemSize );
        if ( itemRect.Contains( aPosition ) )
            {
            iObserver.HandleMenuItemL( iMenuItems[ i ].iItemId );
            break;
            }
        tl.iY += itemSize.iHeight;
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Sort
// ----------------------------------------------------------------------------
//
void CMainMenu::Sort()
    {
    TLinearOrder<TMenuItem> order( TMenuItem::Compare );
    iMenuItems.Sort( order );
    }

// ----------------------------------------------------------------------------
// CMainMenu::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CMainMenu::TimerCallback( TAny* aPtr )
    {
    CMainMenu* self = static_cast<CMainMenu*> ( aPtr );
    self->DoEffects();
    return 0;
    }

// End of File
