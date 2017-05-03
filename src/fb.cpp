/////////////////////////////////////////////////////////////////////////////
// Name:        fb.cpp
// Author:      Rodolfo Zitellini
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "fb.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "editorial.h"
#include "text.h"
#include "vrv.h"

namespace vrv {
    
    //----------------------------------------------------------------------------
    // Fb
    //----------------------------------------------------------------------------
    
    Fb::Fb() : Object("fb-")
    {
        
        Reset();
    }
    
    Fb::~Fb()
    {
    }
    
    void Fb::Reset()
    {
        Object::Reset();
    }
    
    void Fb::AddChild(Object *child)
    {
        if (child->Is(FIGURE)) {
            assert(dynamic_cast<F *>(child));
        }
        else {
            LogError("Adding '%s' to a '%s'", child->GetClassName().c_str(), this->GetClassName().c_str());
            assert(false);
        }
        
        child->SetParent(this);
        m_children.push_back(child);
        Modify();
    }
    
    //----------------------------------------------------------------------------
    // Figure
    //----------------------------------------------------------------------------
    
    F::F() : TextElement("f-")
    {
        Reset();
    }
    
    F::~F()
    {
    }
    
    void F::Reset()
    {
        TextElement::Reset();
    }
    
    void F::AddChild(Object *child)
    {
        if (child->Is(TEXT)) {
            assert(dynamic_cast<Text *>(child));
        }
        else if (child->IsEditorialElement()) {
            assert(dynamic_cast<EditorialElement *>(child));
        }
        else {
            LogError("Adding '%s' to a '%s'", child->GetClassName().c_str(), this->GetClassName().c_str());
            assert(false);
        }
        
        child->SetParent(this);
        m_children.push_back(child);
        Modify();
    }
    
} // namespace vrv
