#include <irrlicht/irrlicht.h>

using namespace irr;

int main(int argc, char** argv){

    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, false, false, 0);
    if (!device){
            return 1;
    }else{
        device->setWindowCaption(L"Quark Plasma - 0.1");
    }

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager *gestionnaire = device->getSceneManager();

    gestionnaire->addCameraSceneNode(0, core::vector3df(0,0,0), core::vector3df(5,0,0));
    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,100,100,100));
        gestionnaire->drawAll();
        driver->endScene();
    }
    device->drop();
	return 0;
}
