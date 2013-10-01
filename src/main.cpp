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
    
    //sun
    scene::ISceneNode * sun = smgr->addSphereSceneNode(100.f, 64);
    if (sun){
        sun->setPosition(core::vector3df(0,0,0));
        sun->setMaterialTexture(0, driver->getTexture("../textures/sun.png"));
        sun->setMaterialFlag(video::EMF_LIGHTING, false);
    }
    //sun emission
    scene::ISceneNode* light = smgr->addLightSceneNode(0, core::vector3df(0,0,0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 1000.0f);

    //earth
    scene::ISceneNode * earth = smgr->addSphereSceneNode(25.f, 64);
    if (earth){
        sun->addChild(earth);
        earth->setPosition(core::vector3df(1000.f,0,0));
        earth->setMaterialTexture(0, driver->getTexture("../textures/earth.jpg"));
        scene::ISceneNodeAnimator * animator = smgr->createFlyCircleAnimator(core::vector3df(0,0,0), 1000.f, 0.00003f, core::vector3df(0.f, -1.f, 0.f));
        if (animator){
            earth->addAnimator(animator);
            animator->drop();
        }
    }

    //moon
    scene::ISceneNode * moon = smgr->addSphereSceneNode(1.f, 32);
    if (moon){
        earth->addChild(moon);
        moon->setPosition(core::vector3df(0,0,0));
        moon->setMaterialTexture(0, driver->getTexture("../textures/moon.jpg"));
        scene::ISceneNodeAnimator * animator = smgr->createFlyCircleAnimator(core::vector3df(0,0,0), 50.0f, 0.0003f, core::vector3df(0.3f, -1.f, 0.f));
        if (animator){
            moon->addAnimator(animator);
            animator->drop();
        }
    }

    //camera
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.06f);
    camera->setPosition(core::vector3df(0,1100,0));
    
    

    //skybox
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture("../textures/ESO_-_Milky_Way_Top.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Left.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Right.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Front.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Back.bmp"));

    float rotationY = 0.f;
    float rotationSpeed = 0.05f;
    u32 m_Time = device->getTimer()->getTime();
    while(device->run()){
        u32 m_DeltaTime = device->getTimer()->getTime() - m_Time;
        m_Time += m_DeltaTime;

        rotationY += rotationSpeed * m_DeltaTime;
        sun->setRotation(core::vector3df(0.f, -rotationY/10, 0.f));
        earth->setRotation(core::vector3df(0.f, rotationY, 0.f));
        moon->setRotation(core::vector3df(10.f, rotationY*4, 0.f));

        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        driver->endScene();
    }
    device->drop();
	return 0;
}
