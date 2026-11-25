#include "trajectory_predictor.h"

#include <cyclone/body.h>
#include <cyclone/collide_fine.h>
#include <cyclone/contacts.h>

namespace siege_lab
{

    namespace
    {

        Vector3 ToRaylibVector(const cyclone::Vector3& _vector)
        {
            return {
              static_cast<float>(_vector.x),
              static_cast<float>(_vector.y),
              static_cast<float>(_vector.z)
            };
        }

        void InitializeGhost(
            cyclone::RigidBody& _body,
            const TrajectorySettings& _settings)
        {
            _body.setMass(1.0f);
            _body.setPosition(
                _settings.origin.x,
                _settings.origin.y,
                _settings.origin.z);
            _body.setVelocity(
                _settings.velocity.x,
                _settings.velocity.y,
                _settings.velocity.z);
            _body.setAcceleration(
                _settings.acceleration.x,
                _settings.acceleration.y,
                _settings.acceleration.z);
            _body.setDamping(_settings.damping, 1.0f);
            _body.setCanSleep(false);
            _body.setAwake(true);
            _body.calculateDerivedData();
        }

        void InitializeCollisionData(
            cyclone::CollisionData& _data,
            cyclone::Contact& _contact)
        {
            _data.contactArray = &_contact;
            _data.reset(1);
            _data.friction = 0.0f;
            _data.restitution = 0.0f;
            _data.tolerance = 0.0f;
        }

        void RecordContact(
            TrajectoryResult& _result,
            const cyclone::Contact& _contact,
            int _step)
        {
            _result.has_contact = true;
            _result.contact_step = _step;
            _result.contact_point = ToRaylibVector(_contact.contactPoint);
        }

        bool DetectGroundContact(
            const cyclone::CollisionSphere& _sphere,
            TrajectoryResult& _result,
            int _step)
        {
            cyclone::CollisionPlane ground;
            ground.direction = cyclone::Vector3(0.0f, 1.0f, 0.0f);
            ground.offset = 0.0f;

            cyclone::Contact contact;
            cyclone::CollisionData data;
            InitializeCollisionData(data, contact);

            if (cyclone::CollisionDetector::sphereAndHalfSpace(
                _sphere, ground, &data) == 0)
            {
                return false;
            }

            RecordContact(_result, contact, _step);

            return true;
        }

    }  // namespace

    TrajectoryResult TrajectoryPredictor::Predict(
        const TrajectorySettings& _settings) const
    {
        TrajectoryResult result;
        cyclone::RigidBody ghost;
        InitializeGhost(ghost, _settings);

        cyclone::CollisionSphere sphere;
        sphere.body = &ghost;
        sphere.radius = _settings.radius;

        result.positions.push_back(ToRaylibVector(ghost.getPosition()));

        for (int step = 1; step <= _settings.max_steps; ++step)
        {
            ghost.integrate(_settings.fixed_dt);
            sphere.calculateInternals();
            result.positions.push_back(ToRaylibVector(ghost.getPosition()));

            if (DetectGroundContact(sphere, result, step))
            {
                break;
            }
        }

        return result;
    }

}  // namespace siege_lab