#pragma once

#include "QSceneOverlay.h"
#include "ViewportOverlay.h"
#include "QUrhoHelpers.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/UI/Text.h>

#include <QObject>
#include <QSharedPointer>

namespace QUrho {
    class QUrhoScene;

    class QUrhoInput;

    class UIOverlay : public QObject, public Urho3D::Object, public QSceneOverlay {
    Q_OBJECT
    URHO3D_OBJECT(UIOverlay, Urho3D::Object)

    public:
        explicit UIOverlay(Urho3D::Context *context, QUrhoScene *scene, QObject *parent = nullptr);

        void Update(QUrhoInput *input, float timeStep) override;
        
        Urho3D::SharedPtr<Urho3D::Text> yawText;
        Urho3D::SharedPtr<Urho3D::Text> pitchText;
        Urho3D::SharedPtr<Urho3D::Text> rollText;
        Urho3D::SharedPtr<Urho3D::Text> depthText;

    private:
        Urho3D::Text* CreateText(int posX, int posY, int fontSize);
        
        Urho3D::Scene *m_scene = nullptr;
        QUrhoScene *m_urhoScene = nullptr;
    };
}
