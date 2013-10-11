#include <irrlicht/irrlicht.h>
#include "Bullet.h"
using namespace irr;

enum GAME_STATE{
  MENU_MAIN,
  MENU_CREATE,
  MENU_LOAD,
  INGAME_PLAY,
  INGAME_PAUSE,
  INGAME_EXIT,
  MULTIPLAYER_CREATE,
  MULTIPLAYER_JOIN
};

class Application{
public:
  Application();
  ~Application();
  bool run();

private:
  GAME_STATE state;
  void init();
  IrrlichtDevice *device;
  scene::ISceneManager *smgr;
  video::IVideoDriver* driver;
  gui::IGUIEnvironment* guienv;
  Bullet* bullet;
};