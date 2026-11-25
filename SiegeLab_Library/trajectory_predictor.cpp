#include <vector>
#include <cstddef>

#include "trajectory_predictor.h"
#include <cyclone/body.h>
#include <cyclone/collide_fine.h>
#include <cyclone/contacts.h>
#include "trajectory_obstacle.h"

namespace siege_lab
{

    namespace
    {
        struct GhostObstacle
        {
            cyclone::RigidBody body;
            cyclone::CollisionBox box;
        };

        Vector3 ToRaylibVector(const cyclone::Vector3& _vector)
        {
            return {
              static_cast<float>(_vector.x),
              static_cast<float>(_vector.y),
              static_cast<float>(_vector.z)
            };
        }

        cyclone::Vector3 ToCycloneVector(const Vector3& _vector)
        {
            return cyclone::Vector3(_vector.x, _vector.y, _vector.z);
        }

        void InitializeGhost(
            cyclone::RigidBody& _body,
            const TrajectorySettings& _settings)
        {
            _body.setMass(1.0f);
            _body.setPosition(ToCycloneVector(_settings.origin));
            _body.setVelocity(ToCycloneVector(_settings.velocity));
            _body.setAcceleration(ToCycloneVector(_settings.acceleration));
            _body.setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
            _body.setRotation(0.0f, 0.0f, 0.0f);
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

        void InitializeObstacle(
            cyclone::RigidBody& _body,
            cyclone::CollisionBox& _box,
            const TrajectoryObstacle& _obstacle)
        {
            _body.setInverseMass(0.0f);
            _body.setPosition(ToCycloneVector(_obstacle.position));
            _body.setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
            _body.calculateDerivedData();

            _box.body = &_body;
            _box.halfSize = ToCycloneVector(_obstacle.half_size);
            _box.calculateInternals();
        }

        void InitializeObstacles(
            std::vector<GhostObstacle>& _obstacles,
            const TrajectorySettings& _settings)
        {
            for (std::size_t i = 0; i < _obstacles.size(); ++i)
            {
                InitializeObstacle(
                    _obstacles[i].body,
                    _obstacles[i].box,
                    _settings.obstacles[i]);
            }
        }

        bool DetectObstacleContact(
            const cyclone::CollisionSphere& _sphere,
            const cyclone::CollisionBox& _box,
            TrajectoryResult& _result,
            int _step)
        {
            cyclone::Contact contact;
            cyclone::CollisionData data;
            InitializeCollisionData(data, contact);

            if (cyclone::CollisionDetector::boxAndSphere(
                _box, _sphere, &data) == 0)
            {
                return false;
            }

            RecordContact(_result, contact, _step);

            return true;
        }

        bool DetectContact(
            const cyclone::CollisionSphere& _sphere,
            const std::vector<GhostObstacle>& _obstacles,
            TrajectoryResult& _result,
            int _step)
        {
            if (DetectGroundContact(_sphere, _result, _step))
            {
                return true;
            }

            for (const GhostObstacle& obstacle : _obstacles)
            {
                if (DetectObstacleContact(
                    _sphere, obstacle.box, _result, _step))
                {
                    return true;
                }
            }

            return false;
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

        std::vector<GhostObstacle> obstacles(_settings.obstacles.size());
        InitializeObstacles(obstacles, _settings);

        result.positions.push_back(ToRaylibVector(ghost.getPosition()));

        for (int step = 1; step <= _settings.max_steps; ++step)
        {
            ghost.integrate(_settings.fixed_dt);
            sphere.calculateInternals();
            result.positions.push_back(ToRaylibVector(ghost.getPosition()));
            if (DetectContact(sphere, obstacles, result, step))
            {
                break;
            }
        }
        return result;
    }

}  // namespace siege_lab