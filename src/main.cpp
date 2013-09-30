#include <irrlicht/irrlicht.h>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


int main(int argc, char** argv){

    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true);
    if (!device){
            return 1;
    }else{
        device->setWindowCaption(L"Quark Plasma - 0.1");
    }

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();

    //camera
    //scene::ISceneNode* camera = smgr->addCameraSceneNode(0, core::vector3df(100,0,-100), core::vector3df(100,0,0));
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    camera->setPosition(core::vector3df(100,0,-100));
    

    //sun emission
    scene::ISceneNode* light = smgr->addLightSceneNode(0, core::vector3df(0,0,0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 1000.0f);

    //earth
    scene::ISceneNode * earth = smgr->addSphereSceneNode();
    if (earth){
        earth->setPosition(core::vector3df(100,0,0));
        earth->setScale(core::vector3df(5.f, 5.f, 5.f));
        earth->setMaterialTexture(0, driver->getTexture("../textures/earth.jpg"));
    }

    //moon
    scene::ISceneNode * moon = smgr->addSphereSceneNode();
    if (moon){
      moon->setPosition(core::vector3df(earth->getPosition().X + 50,0,0));
        moon->setScale(core::vector3df(1.f, 1.f, 1.f));
        moon->setMaterialTexture(0, driver->getTexture("../textures/moon.jpg"));
        scene::ISceneNodeAnimator * animator = smgr->createFlyCircleAnimator(earth->getPosition(), 50.0f, 0.0003f, core::vector3df(0.3f, -1.f, 0.f));
        if (animator){
            moon->addAnimator(animator);
            animator->drop();
        }
    }

    //skybox
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture("../textures/ESO_-_Milky_Way_Top.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Left.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Right.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Front.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Back.bmp"));

    float rotationY = 0.f;
    float rotationSpeed = 0.005f;
    u32 m_Time = device->getTimer()->getTime();
    while(device->run()){
        u32 m_DeltaTime = device->getTimer()->getTime() - m_Time;
        m_Time += m_DeltaTime;

        rotationY += rotationSpeed * m_DeltaTime;
        earth->setRotation(core::vector3df(0.f, rotationY, 0.f));
        moon->setRotation(core::vector3df(10.f, rotationY*4, 0.f));

        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        driver->endScene();
    }
    device->drop();
	return 0;
}
