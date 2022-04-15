#pragma once

#include <QObject>
#include <QSet>
#include <QKeySequence>

#include <Urho3D/Core/Context.h>
#include <QtGui/QKeyEvent>
#include <Urho3D/Input/Input.h>
#include <qevent.h>

namespace QUrho {
    class Urho3DCoreWidget;

    class QUrhoInput : public QObject, public Urho3D::Object {
    Q_OBJECT
    URHO3D_OBJECT(QUrhoInput, Urho3D::Object);
    public:
        explicit QUrhoInput(Urho3D::Context *context, Urho3DCoreWidget *widget, QObject *parent = nullptr);

        virtual void SetMouseMode(Urho3D::MouseMode mode);

        virtual bool IsKeyPressed(Qt::Key key) const;

        virtual bool IsMouseButtonPressed(Qt::MouseButton button) const;

        virtual bool IsMouseButtonDown(Qt::MouseButton button) const;

        virtual Urho3D::IntVector2 GetMousePosition() const;

        virtual Urho3D::IntVector2 GetMouseMove();

        virtual int GetMouseWheelMove() const;

    protected:
        virtual void OnKeyPressed(QKeyEvent *event);

        virtual void OnKeyReleased(QKeyEvent *event);

        virtual void OnWheelMoved(QWheelEvent *event);

        virtual void OnFocusOut(QFocusEvent *event);

        virtual void OnMouseMoved(QMouseEvent *event);

        virtual void OnMouseButtonPressed(QMouseEvent* event);

        virtual void OnMouseButtonReleased(QMouseEvent* event);

    private:

        void CreateConnections();

        Urho3DCoreWidget *m_coreWidget;
        QSet<Qt::Key> m_keysDown;
        QSet<Qt::Key> m_keysPressed;
        QSet<Qt::MouseButton> m_mouseButtonDown;
        QSet<Qt::MouseButton> m_mouseButtonPressed;
        int m_wheelDelta = 0;
        int m_lastMousePosX = 0;
        int m_lastMousePosY = 0;
        Urho3D::IntVector2 m_mousePosDelta;
    };

}


