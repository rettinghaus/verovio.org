/////////////////////////////////////////////////////////////////////////////
// Name:        layer.h
// Author:      Laurent Pugin
// Created:     2011
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#ifndef __VRV_LAYER_H__
#define __VRV_LAYER_H__

#include <typeinfo>

//----------------------------------------------------------------------------

#include "atts_shared.h"
#include "clef.h"
#include "object.h"
#include "scoredef.h"

namespace vrv {

class DeviceContext;
class LayerElement;
class Note;

//----------------------------------------------------------------------------
// Layer
//----------------------------------------------------------------------------

/**
 * This class represents a layer in a laid-out score (Doc).
 * A Layer is contained in a Staff.
 * It contains LayerElement objects.
*/
class Layer: public DocObject, public ObjectListInterface, public AttCommon
{
public:
    /**
     * @name Constructors, destructors, and other standard methods
     * Reset method reset all attribute classes
     */
    ///@{
    Layer( );
    virtual ~Layer();
    void Reset();
    virtual std::string GetClassName( ) { return "Layer"; };
    ///@}
	
	void AddElement( LayerElement *element, int idx = -1 );
    	
	int GetElementCount() const { return (int)m_children.size(); };
    
    /**
     * Return the index position of the layer in its staff parent.
     * The index position is 0-based.
     */
    int GetLayerIdx() const { return Object::GetIdx(); };

    // functors
    /**
     * Copy the elements to a Layer passed in parameters. 
     * Also take into account a start and end uuid for the page (if any)
     */ 
    virtual int CopyToLayer( ArrayPtrVoid params );
    void CopyElements( ArrayPtrVoid params ); // unused
    void GetMaxXY( ArrayPtrVoid params ); // unused
    virtual int Save( ArrayPtrVoid params );
    void CheckAndResetSectionOrMeasure( ArrayPtrVoid params ); // unused
    
	void CopyAttributes( Layer *layer ); // copy all attributes but none of the elements
    
	LayerElement *GetPrevious( LayerElement *element );
	LayerElement *GetAtPos( int x );
	LayerElement *Insert( LayerElement *element, int x ); // return a pointer on the inserted element
    
    void Insert( LayerElement *element, LayerElement *before );
    
	void Delete( LayerElement *element );
	
    /**
     * Looks for the first LayerElement of type elementType.
     * Looks FORWARD of BACKWARD depending on the direction parameter.
     * Returns the retrieved element if *succ == true or the original element if not.
     */
    LayerElement *GetFirstOld( LayerElement *element, unsigned int direction, const std::type_info *elementType, bool *succ );
    
    /** 
     * Get the current clef for the test element.
     * Goes back on the layer until a clef is found.
     * This is used when inserting a note by passing a y position because we need
     * to know the clef in order to get the pitch.
     */
	Clef *GetClef ( LayerElement *test );
    
    /** 
     * Return the clef offset for the position x.
     * The method uses Layer::GetClef first to find the clef before test.
     */
    int GetClefOffset( LayerElement *test  );
    
    /**
     * Add an element to the drawing list.
     * The drawing list is used to postponed the drawing of elements
     * that need to be drawn in a particular order.
     * For example, we need to draw beams before tuplets
     */
    void AddToDrawingList( LayerElement *element );

    /**
     * Return the drawing list.
     * This is used when actually drawing the list (see View::DrawLayerList)
     */
    ListOfObjects *GetDrawingList( );

    /**
     * Reset the drawing list.
     * Clears the list - called when the layer starts to be drawn
     */
    void ResetDrawingList( );
    
    /**
     * Basic method that remove intermediate clefs and custos.
     * Used for building collations (See CmpFile::Collate).
     */
    void RemoveClefAndCustos( );
    
    /**
     * Set drawing clef, keysig and mensur if necessary and if available.
     * Also set the current clef.
     */
    void SetDrawingValues( ScoreDef *currentScoreDef, StaffDef *currentStaffDef );
    
    /**
     * Align horizontally the content of a layer.
     */
    virtual int AlignHorizontally( ArrayPtrVoid params );
    
    /**
     * @name Set the clef, keySig, mensur and meterSig to be drawn.
     */
    ///@{
    void SetDrawingClef( Clef *clef );
    void SetDrawingKeySig( KeySig *keySig );
    void SetDrawingMensur( Mensur *mensur );
    void SetDrawingMeterSig( MeterSig *meterSig );
    ///@}
    
    /**
     * @name Get the clef, keySig, mensur and meterSig to be drawn.
     */
    ///@{
    Clef *GetDrawingClef( ) { return m_drawingClef; };
    KeySig *GetDrawingKeySig( ) { return m_drawingKeySig; };
    Mensur *GetDrawingMensur( ) { return m_drawingMensur; };
    MeterSig *GetDrawingMeterSig( ) { return m_drawingMeterSig; };
    ///@}
    
    /**
     * @name Set and get the stem direction of the layer.
     * This stays STEMDIRECTION_NONE with on single layer in the staff. 
     */
    ///@{
    void SetDrawingStemDir( data_STEMDIRECTION stemDirection ) { m_drawingStemDir = stemDirection; };
    data_STEMDIRECTION GetDrawingStemDir() { return m_drawingStemDir; };
    ///@}
    
private:
    
public:
    
protected:
    // drawing variables
    //LayerElement *beamListPremier; // we need to replace this with a proper beam class that handles a list of notes/rests
    ListOfObjects m_drawingList;
    /** The clef attribute */
    Clef *m_drawingClef;
    /** The key signature */
    KeySig *m_drawingKeySig;
    /** The mensur */
    Mensur *m_drawingMensur;
    /** The meter signature (time signature) */
    MeterSig *m_drawingMeterSig;
    
private:
    /**
     * The current clef.
     * This is used for getting the clef when interacting, for example by clicking in order to get the pitch from a position
     */
    Clef m_currentClef;
    /**
     *
     */
    data_STEMDIRECTION m_drawingStemDir;
    
};

} // namespace vrv

#endif
