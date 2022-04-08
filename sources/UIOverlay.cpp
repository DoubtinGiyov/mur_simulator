#include "UIOverlay.h"

#include "AUVOverlay.h"
#include "QUrhoScene.h"
#include "QUrhoInput.h"
#include "SharingOverlay.h"
#include <QDebug>

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>

namespace QUrho {


UIOverlay::UIOverlay(Urho3D::Context *context, QUrho::QUrhoScene *scene, QObject *parent) :
            QObject{parent},
            Urho3D::Object{context},
            m_urhoScene{scene},
            m_scene{scene->GetScene()}
    {
        int fontSize = 13;
        yawText = CreateText(0, 0, fontSize);
        pitchText = CreateText(0, 15, fontSize);
        rollText = CreateText(0, 30, fontSize);
        depthText = CreateText(0, 45, fontSize);
    }


    void UIOverlay::Update(QUrhoInput *input, float timeStep) {
        
    }

    
    Urho3D::Text* UIOverlay::CreateText(int posX, int posY, int fontSize)
    {
        auto cache = this->GetSubsystem<Urho3D::ResourceCache>();
        
        auto newText = this->GetSubsystem<Urho3D::UI>()->GetRoot()->CreateChild<Urho3D::Text>();
        newText->SetText("");
        newText->SetFont(cache->GetResource<Urho3D::Font>("Fonts/Anonymous Pro.ttf"), fontSize);
        newText->SetColor(Urho3D::Color(0.0f, 0.0f, 0.0f));
        
        newText->SetHorizontalAlignment(Urho3D::HA_RIGHT);
        newText->SetVerticalAlignment(Urho3D::VA_TOP);
        newText->SetPosition(posX, posY);
        return newText;
    }
}

