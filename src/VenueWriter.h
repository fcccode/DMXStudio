/* 
Copyright (C) 2011-15 Robert DeSantis
hopluvr at gmail dot com

This file is part of DMX Studio.
 
DMX Studio is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.
 
DMX Studio is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
License for more details.
 
You should have received a copy of the GNU General Public License
along with DMX Studio; see the file _COPYING.txt.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA.
*/

#pragma once

#include "IVisitor.h"
#include "ISerializable.h"
#include "DObject.h"
#include "Venue.h"
#include "SceneSequence.h"
#include "SceneChannelAnimator.h"
#include "ScenePatternDimmer.h"
#include "SceneColorFader.h"
#include "SceneMovementAnimator.h"
#include "SceneStrobeAnimator.h"
#include "SceneSoundLevel.h"
#include "ScenePixelAnimator.h"
#include "SceneChannelFilter.h"
#include "ScenePulse.h"
#include "SceneCueAnimator.h"
#include "SceneFixtureDimmer.h"

class VenueWriter : public IVisitor, ISerializable
{
    std::vector<TiXmlElement*>      m_parents;

public:
    VenueWriter(  );
    ~VenueWriter(void);

    void writeToFile( Venue* venue, LPCSTR output_file );
    void writeToString( Venue* venue, CString& xml_output );

    void visit( Venue* venue );
    void visit( Fixture* fixture );
    void visit( Scene* scene );
    void visit( SceneActor* actor );
    void visit( Chase* chase );
    void visit( FixtureGroup* fixture_group );
    void visit( SceneStrobeAnimator* animation );
    void visit( ScenePatternDimmer* animation );
    void visit( SceneMovementAnimator* animation );
    void visit( SceneColorFader* animation );
    void visit( SceneChannelAnimator* animation );
    void visit( SceneSequence* animation );  
    void visit( SceneSoundLevel* animation );  
    void visit( SceneChannelFilter* animation );
    void visit( ScenePulse* animation );
    void visit( AnimationSignal* signal );
    void visit( ChaseStep* chase_step );
    void visit( MovementAnimation* movement );
    void visit( ScenePixelAnimator* animation );
    void visit( ChannelAnimation* channel_animation );
    void visit( MusicSceneSelector* music_scene_selection );
    void visit( Universe* universe );
    void visit( AnimationReference* animation );
    void visit( Palette* palette );
    void visit( PaletteEntry* palette_entry );
    void visit( SceneCueAnimator* animation );
    void visit( SceneFixtureDimmer* animation );
    // Reminder: Add a virtual entry to IVisitor for all new visit methods

    template <class T>
    void visit_object( TiXmlElement& parent, T& object ) {
        push_parent( parent );
        object.accept( this );
        pop_parent( );
    }

    template <class T>
    void visit_map( TiXmlElement& parent, T& list ) {
        push_parent( parent );
        for ( T::iterator it=list.begin();
              it != list.end(); ++it )
            it->second.accept( this );
        pop_parent( );
    }

    template <class T>
    void visit_ptr_map( TiXmlElement& parent, T& list ) {
        push_parent( parent );
        for ( T::iterator it=list.begin();
        it != list.end(); ++it )
            it->second->accept( this );
        pop_parent( );
    }

    template <class T>
    void visit_ptr_array( TiXmlElement &container, T& list ) {
        push_parent( container );
        for ( T::iterator it=list.begin();
              it != list.end(); ++it )
            (*it)->accept( this );
        pop_parent( );
    }

    template <class T>
    void visit_array( TiXmlElement &container, T& list ) {
        push_parent( container );
        for ( T::iterator it=list.begin();
              it != list.end(); ++it )
            (*it).accept( this );
        pop_parent( );
    }

protected:
    void push_parent( TiXmlElement& parent ) {
        m_parents.push_back( &parent );
    }

    void pop_parent() {
        m_parents.pop_back();
    }

    TiXmlElement& getParent() {
        return *(*m_parents.rbegin());
    }


private:
    void writeDObject( TiXmlElement& element, DObject* dobject, LPCSTR number_name );
    void writeAbstractAnimation( TiXmlElement& element, AnimationDefinition* animation );
	void writeStrobeTime( TiXmlElement& element, StrobeTime& strobe_time );
};

