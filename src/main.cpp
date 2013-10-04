#include <irrlicht/irrlicht.h>
#include "Bullet.h"
using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "BulletCollision_vs2010.lib")
#pragma comment(lib, "BulletDynamics_vs2010.lib")
#pragma comment(lib, "BulletSoftBody_vs2010.lib")
#pragma comment(lib, "LinearMath_vs2010.lib")
#endif

int main(int argc, char** argv){

    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true);
    if (!device){
            return 1;
    }else{
        device->setWindowCaption(L"Quark Plasma - 0.1");
    }

    //irrlicht managers
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();
    smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
    device->getCursorControl()->setVisible(false);

    //bullet manager
    Bullet* bullet = new Bullet();

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

        video::ITexture* normalMap = driver->getTexture("../textures/earth_bump.jpg");
        if (normalMap){
            driver->makeNormalMapTexture(normalMap, 100.0f);
            earth->setMaterialTexture (1, normalMap);
            earth->setMaterialType(video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA);
        }

        scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0,0.01f,0));
        earth->addAnimator(anim);
        anim->drop();

        scene::ISceneNode * earth_clouds = smgr->addSphereSceneNode(25.75f, 64);
        earth->addChild(earth_clouds);
        earth_clouds->setPosition(core::vector3df(0.f,0.f,0.f));
        earth_clouds->setMaterialTexture(0, driver->getTexture("../textures/earth_clouds.jpg"));
        earth_clouds->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

        earth_clouds->getMaterial(0).SpecularColor.set(255,0,40,110);
        earth_clouds->getMaterial(0).Shininess = 2.f;

        bullet->AddSphere(earth, 25., 0, true);
    }

    //mars
    scene::ISceneNode * mars = smgr->addSphereSceneNode(40.f, 64);
    if (mars){
        sun->addChild(mars);
        mars->setPosition(core::vector3df(2000.f,0,0));
        mars->setMaterialTexture(0, driver->getTexture("../textures/mars.jpg"));
    }

    //moon
    scene::ISceneNode * moon = smgr->addSphereSceneNode(2.f, 32);
    if (moon){
        earth->addChild(moon);
        moon->setPosition(core::vector3df(0,0,0));
        moon->setMaterialTexture(0, driver->getTexture("../textures/moon.jpg"));
        scene::ISceneNodeAnimator * animator = smgr->createFlyCircleAnimator(core::vector3df(0,0,0), 50.0f, 0.0003f, core::vector3df(0.3f, -1.f, 0.f));
        scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0,0.8f,0));
        moon->addAnimator(animator);
        moon->addAnimator(anim);
        animator->drop();
        anim->drop();
    }

    //game block 01
    for(int i = 0; i < 75; i++){
      scene::ISceneNode * gameBlockTmp = smgr->addSphereSceneNode(1., 16);
      gameBlockTmp->setPosition(core::vector3df(995 + 0.1*i,25 + 10*i,0));
      bullet->AddSphere(gameBlockTmp, 1, 10);
    }


    //camera
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.1f);
    camera->setPosition(core::vector3df(earth->getPosition().X,0,-100));
    camera->setTarget(earth->getPosition());

    //skybox
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture("../textures/ESO_-_Milky_Way_Top.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Left.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Right.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Front.bmp"),
        driver->getTexture("../textures/ESO_-_Milky_Way_Back.bmp"));

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        bullet->UpdatePhysics(DeltaTime);
        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        driver->endScene();
    }

    delete bullet;
    device->drop();
    
    return 0;
}
