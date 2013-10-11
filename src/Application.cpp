#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true);
    if (device){
        device->setWindowCaption(L"Quark Plasma - 0.1");

        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));
        device->getCursorControl()->setVisible(false);

        //bullet manager
        bullet = new Bullet();

        init();

        state = MENU_MAIN;
    }else{
      bullet = NULL;
    }
}

Application::~Application(){
    if(bullet){
        delete bullet;
    }
    if(device){
        device->drop();
    }
}

void Application::init(){
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
    scene::IMeshSceneNode * earth = smgr->addSphereSceneNode(25.f, 64);
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
        earth_clouds->getMaterial(0).Shininess = 1.f;
    }

    //mars
    scene::ISceneNode * mars = smgr->addSphereSceneNode(40.f, 64);
    if (mars){
        sun->addChild(mars);
        mars->setPosition(core::vector3df(2000.f,0,0));
        mars->setMaterialTexture(0, driver->getTexture("../textures/mars.jpg"));
    } 

    //moon
    scene::IMeshSceneNode * moon = smgr->addSphereSceneNode(2.f, 32);
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

    //camera
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNode();
    camera->setPosition(core::vector3df(earth->getPosition().X - 80.,0,-100));
    camera->setTarget(core::vector3df(earth->getPosition().X - 80.,0,0));
    
    scene::IMeshSceneNode * moon2 = smgr->addSphereSceneNode(2.f, 32);
    if (moon){
        moon2->setPosition(core::vector3df(camera->getPosition().X - 56.,6.,-25.));
        moon2->setMaterialTexture(0, driver->getTexture("../textures/moon.jpg"));
        scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0,0.8f,0));
        moon2->addAnimator(anim);
        moon2->setMaterialFlag(video::EMF_LIGHTING, false);
        anim->drop();
    }

    //skybox
    video::ITexture* text = driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp");
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(text,text,text,text,text,text);
}

bool Application::run(){
    if(!device){
        return false;
    }

    gui::IGUIFont* font = device->getGUIEnvironment()->getFont("../textures/venus30.png");
    gui::IGUIFont* font2 = device->getGUIEnvironment()->getFont("../textures/venus16.png");

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        bullet->UpdatePhysics(DeltaTime);
        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        font->draw(L"Quark Plasma",
                    core::rect<s32>(0,0,640,100),
                    video::SColor(255,255,255,255), true, true);
        font2->draw(L"New Game",
                    core::rect<s32>(100,200,200,100),
                    video::SColor(255,255,255,255), false, false);
        font2->draw(L"Continue",
                    core::rect<s32>(100,230,200,100),
                    video::SColor(255,255,255,255), false, false);
        font2->draw(L"Multiplayer",
                    core::rect<s32>(100,260,200,100),
                    video::SColor(255,255,255,255), false, false);
        font2->draw(L"Options",
                    core::rect<s32>(100,290,200,100),
                    video::SColor(255,255,255,255), false, false);
        font2->draw(L"Exit",
                    core::rect<s32>(100,320,200,100),
                    video::SColor(255,255,255,255), false, false);
        driver->endScene();
    }

    return true;
}