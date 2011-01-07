#include "flx/FlxApp.h"

#include "flx/flxG.h"
#include "flx/game.h"
#include "flx/state.h"
#include "PlayState.h"

#include "cinder/gl/gl.h"

#include "bluegin/resourcemanager.h"

using namespace flx;
using namespace ci; 
using namespace ci::app;
using namespace bluegin;                                                                                                                                                                                                

extern FlxGlobal FlxG;

class CanabaltApp : public FlxApp
{
public:
	void setup()
    {
        Vec2f zoom(1.68, 1.4);
        StatePtr initialState = StatePtr(new PlayState());
        mGame = GamePtr(new Game(*this, 
                                 getWindowWidth() / zoom.x, getWindowHeight() / zoom.y, 
                                 initialState, zoom));
        flxSetup(mGame);

        FlxG.resources->primeAllSounds();
        FlxG.defaultFont = FlxG.resources->font("nokia").get();
        gl::clear();
    }
};

CINDER_APP_BASIC( CanabaltApp, RendererGl )

