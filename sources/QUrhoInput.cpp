#include "QUrhoInput.h"
#include "QUrhoWidget.h"
#include "QUrhoHelpers.h"
#include "Urho3D/Math/Vector2.h"

#include <QKeyEvent>
#include <QMouseEvent>

#include <Urho3D/Input/Input.h>
#include <qevent.h>

namespace QUrho {

    QUrhoInput::QUrhoInput(Urho3D::Context *context, Urho3DCoreWidget *widget, QObject *parent) :
            Object(context),
            QObject(parent),
            m_coreWidget(widget) {
        CreateConnections();
    }

    bool QUrhoInput::IsKeyPressed(Qt::Key key) const {
        return m_keysPressed.contains(key);
    }

    bool QUrhoInput::IsMouseButtonDown(Qt::MouseButton button) const {
        return m_mouseButtonDown.contains(button);
    }

    Urho3D::IntVector2 QUrhoInput::GetMousePosition() const {
        return Urho3D::IntVector2(m_lastMousePosX, m_lastMousePosY);
    }

    Urho3D::IntVector2 QUrhoInput::GetMouseMove() {
        auto returnValueMousePosDelta = m_mousePosDelta;
        m_mousePosDelta = Urho3D::IntVector2(0, 0);
        return returnValueMousePosDelta;
    }

    int QUrhoInput::GetMouseWheelMove() const {
        return m_wheelDelta;
    }

    bool QUrhoInput::IsMouseButtonPressed(Qt::MouseButton button) const {
        return m_mouseButtonPressed.contains(button);
    }

    void QUrhoInput::CreateConnections() {
        connect(m_coreWidget, &Urho3DCoreWidget::KeyPressed, this, &QUrhoInput::OnKeyPressed);
        connect(m_coreWidget, &Urho3DCoreWidget::KeyReleased, this, &QUrhoInput::OnKeyReleased);
        connect(m_coreWidget, &Urho3DCoreWidget::WheelMoved, this, &QUrhoInput::OnWheelMoved);
        connect(m_coreWidget, &Urho3DCoreWidget::FocusOut, this, &QUrhoInput::OnFocusOut);
        connect(m_coreWidget, &Urho3DCoreWidget::MouseMoved, this, &QUrhoInput::OnMouseMoved);
        connect(m_coreWidget, &Urho3DCoreWidget::MouseButtonPress, this, &QUrhoInput::OnMouseButtonPressed);
        connect(m_coreWidget, &Urho3DCoreWidget::MouseButtonRelease, this, &QUrhoInput::OnMouseButtonReleased);
    }

    void QUrhoInput::OnKeyPressed(QKeyEvent *event) {
        m_keysPressed.insert((Qt::Key) event->key());
        if (!event->isAutoRepeat()) {
            m_keysDown.remove((Qt::Key) event->key());
        }
    }

    void QUrhoInput::OnKeyReleased(QKeyEvent *event) {
        m_keysPressed.remove((Qt::Key) event->key());
        if (!event->isAutoRepeat()) {
            m_keysDown.remove((Qt::Key) event->key());
        }
    }

    void QUrhoInput::OnWheelMoved(QWheelEvent *event) {
        m_wheelDelta += event->delta() / 120;
    }

    void QUrhoInput::OnFocusOut(QFocusEvent *event) {
        Q_UNUSED(event)
        m_keysPressed.clear();
        m_mouseButtonPressed.clear();
        m_wheelDelta = 0;
        m_mousePosDelta = Urho3D::IntVector2(0, 0);
        SetMouseMode(Urho3D::MM_ABSOLUTE);
    }

    void QUrhoInput::OnMouseMoved(QMouseEvent* event) {
        auto pos = event->localPos();
        m_mousePosDelta = Urho3D::IntVector2(pos.x() - m_lastMousePosX, pos.y() - m_lastMousePosY);
        m_lastMousePosX = pos.x();
        m_lastMousePosY = pos.y();
    }

    void QUrhoInput::OnMouseButtonPressed(QMouseEvent* event) {
        m_mouseButtonPressed.insert(event->button());
    }

    void QUrhoInput::OnMouseButtonReleased(QMouseEvent* event) {
        m_mouseButtonPressed.remove(event->button());
    }

    void QUrhoInput::SetMouseMode(Urho3D::MouseMode mode) {
        GetSubsystem<Urho3D::Input>()->SetMouseMode(mode);
    }
}