#include <irrlicht\irrlicht.h>
#include <btBulletDynamicsCommon.h>

using namespace irr;

class Bullet{
public:
    Bullet();
    ~Bullet();
    void UpdatePhysics(u32 TDeltaTime);
    void AddBox(scene::ISceneNode* node, double mass, bool isKinematic = false);
    void AddSphere(scene::ISceneNode* node, double mass, bool isKinematic = false);
private:
    void Add(scene::ISceneNode* node, double mass, btCollisionShape *Shape, bool isKinematic);
    btCollisionShape* Bullet::GetSphereShape(scene::ISceneNode* node);
    btCollisionShape* Bullet::GetBoxShape(scene::ISceneNode* node);
    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);
    void ClearObjects();
    btDiscreteDynamicsWorld *World;
    core::list<btRigidBody *> Objects;
    btBroadphaseInterface *BroadPhase;
    btDefaultCollisionConfiguration *CollisionConfiguration;
    btCollisionDispatcher *Dispatcher;
    btSequentialImpulseConstraintSolver *Solver;
};