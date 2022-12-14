#include "box2d_object.hpp"
#include <math_helper.hpp>

jt::Box2DObject::Box2DObject(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
{
    setB2Body(world->createBody(def));
    m_world = world;
}

jt::Vector2f jt::Box2DObject::getPosition() const { return Conversion::vec(m_body->GetPosition()); }

void jt::Box2DObject::setPosition(jt::Vector2f const& position)
{
    m_body->SetTransform(Conversion::vec(position), m_body->GetAngle());
}

jt::Vector2f jt::Box2DObject::getVelocity() const
{
    return Conversion::vec(m_body->GetLinearVelocity());
}

void jt::Box2DObject::setVelocity(jt::Vector2f const& v)
{
    m_body->SetLinearVelocity(Conversion::vec(v));
}

void jt::Box2DObject::addVelocity(jt::Vector2f const& v)
{
    auto oldV = Conversion::vec(m_body->GetLinearVelocity());
    m_body->SetLinearVelocity(Conversion::vec(oldV + v));
}

float jt::Box2DObject::getRotation() const { return jt::MathHelper::rad2deg(m_body->GetAngle()); }

b2Body* jt::Box2DObject::getB2Body() { return m_body; }

void jt::Box2DObject::setB2Body(b2Body* body) { m_body = body; }

void jt::Box2DObject::doDestroy()
{
    if (m_world.expired()) {
        return;
    }
    m_world.lock()->destroyBody(m_body);
}
