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
    scene::ISceneManager *smgr = device->getSceneManager();

    smgr->addCameraSceneNode(0, core::vector3df(0,0,-100), core::vector3df(0,0,0));
    scene::ISceneNode * node = smgr->addSphereSceneNode();
    if (node){
        node->setPosition(core::vector3df(0,0,0));
        node->setScale(core::vector3df(2.f, 2.f, 2.f));
        node->setMaterialTexture(0, driver->getTexture("../textures/earth.jpg"));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
    }

    float rotationY = 0.f;
    float rotationSpeed = 0.01f;
    u32 m_Time = device->getTimer()->getTime();
    while(device->run()){
        u32 m_DeltaTime = device->getTimer()->getTime() - m_Time;
        m_Time += m_DeltaTime;

        rotationY += rotationSpeed * m_DeltaTime;
        if(rotationY > 360.f) rotationY = rotationY - 360.f;
        node->setRotation(core::vector3df(0.f, rotationY, 0.f));

        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        driver->endScene();
    }
    device->drop();
	return 0;
}
