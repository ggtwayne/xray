
#ifndef _MNodeMessage
#define _MNodeMessage
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MNodeMessage
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MNodeMessage)
//
// This class is used to register callbacks for dependency node messages
// of specific dependency nodes.
// 
// There are 4 add callback methods which will add callbacks for the
// following messages
// 	   Attribute Changed
// 	   Attribute Added or Removed
// 	   Node Dirty
// 	   Name Changed
// 
// The first parameter passed to each of the add callback methods is the
// depenency node that will trigger the callback.
// 
// Callbacks that are registered for attribute changed/addedOrRemoved messages
// will be passed an AttributeMessage value as a parameter. This value
// indicates the type of attribute message that has occurred. See the 
// enum for all available messages.
//            
// Each method returns an id which is used to remove the callback.
// 
// To remove a callback use MMessage::removeCallback.
// All callbacks that are registered by a plug-in must be removed by that
// plug-in when it is unloaded. Failure to do so will result in a fatal error.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MMessage.h>

// *****************************************************************************

// DECLARATIONS

class MPlug;
class MObject;
class MDGModifier;

// *****************************************************************************

// CLASS DECLARATION (MNodeMessage)

/// Dependency node messages. (OpenMaya) (OpenMaya.py) 
/**
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MNodeMessage : public MMessage
{ 
public:
	/// The type of attribute changed/addedOrRemoved messages that has occurred
	enum AttributeMessage {
		/// a connection has been made to an attribute of this node
		kConnectionMade			= 0x01,
		/// a connection has been broken for an attribute of this node
		kConnectionBroken		= 0x02,
		/// an attribute of this node has been evaluated
		kAttributeEval			= 0x04,
		/// an attribute value of this node has been set
		kAttributeSet			= 0x08,
		/// an attribute of this node has been locked 
		kAttributeLocked		= 0x10,
		/// an attribute of this node has been unlocked
		kAttributeUnlocked 		= 0x20,
		/// an attribute has been added to this node
		kAttributeAdded			= 0x40,
		/// an attribute has been removed from this node
		kAttributeRemoved		= 0x80,
		/// an attribute of this node has been renamed
		kAttributeRenamed		= 0x100,
		/// an attribute of this node has been marked keyable
		kAttributeKeyable		= 0x200,
		/// an attribute of this node has been marked unkeyable
		kAttributeUnkeyable		= 0x400,
		/// the connection was coming into the node
		kIncomingDirection		= 0x800,
		/// an array attribute has been added to this node
		kAttributeArrayAdded	= 0x1000,
		/// an array attribute has been removed from this node
		kAttributeArrayRemoved	= 0x2000,
		/// the otherPlug data has been set
		kOtherPlugSet			= 0x4000,
		/// last value of the enum 
		kLast					= 0x8000
	};

	/// Allows you to prevent attributes from becoming (un)keyable.
	enum KeyableChangeMsg
	{
		///
		kKeyChangeInvalid = 0,
		///
		kMakeKeyable,
		///
		kMakeUnkeyable,
		///
		kKeyChangeLast
	};

	// Function pointer typedefs
	typedef void (*MAttr2PlugFunction)( MNodeMessage::AttributeMessage msg,MPlug & plug,MPlug & otherPlug,void* clientData );
	typedef void (*MAttrPlugFunction)( MNodeMessage::AttributeMessage msg,MPlug & plug,void* clientData 	);
	typedef void (*MKeyableFunction)( MPlug &plug,void *clientData, MNodeMessage::KeyableChangeMsg msg, bool &decision );

public:
	///
	static MCallbackId	addAttributeChangedCallback(
								MObject& node,
								MNodeMessage::MAttr2PlugFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );
								
	///
	static MCallbackId	addAttributeAddedOrRemovedCallback(
								MObject& node,
								MNodeMessage::MAttrPlugFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );
	
	///
	static MCallbackId	addNodeDirtyCallback(
								MObject& node,
								MMessage::MNodeFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	///
	static MCallbackId	addNodeDirtyPlugCallback(
								MObject& node,
								MMessage::MNodePlugFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	///
	static MCallbackId	addNameChangedCallback(
								MObject& node,
								MMessage::MNodeStringFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );


	///
	static MCallbackId	addNodeAboutToDeleteCallback(
								MObject& node,
								MMessage::MNodeModifierFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	///
	static MCallbackId	addNodePreRemovalCallback(
								MObject& node,
								MMessage::MNodeFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );
		
	///	NodeDestroyed callback
	static MCallbackId	addNodeDestroyedCallback(
								MObject& node,
								MMessage::MBasicFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	/// Attribute keyable state change override
	static MCallbackId	addKeyableChangeOverride(
								MPlug& plug,
								MNodeMessage::MKeyableFunction func, 
								void *clientData = NULL, 
								MStatus *status = NULL );

BEGIN_NO_SCRIPT_SUPPORT:
	/// OBSOLETE and NO SCRIPT SUPPORT
	static MCallbackId	addNodeDirtyCallback(
								MObject& node,
								MMessage::MBasicFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	/// OBSOLETE and NO SCRIPT SUPPORT
	static MCallbackId	addNodeDirtyCallback(
								MObject& node,
								MMessage::MNodePlugFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	/// OBSOLETE and NO SCRIPT SUPPORT
	static MCallbackId	addNameChangedCallback(
								MObject& node,
								MMessage::MNodeFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

	/// OBSOLETE and NO SCRIPT SUPPORT
	static MCallbackId	addNodeAboutToDeleteCallback(
								MObject& node,
								MMessage::MModifierFunction func,
								void * clientData = NULL,
								MStatus * ReturnStatus = NULL );

END_NO_SCRIPT_SUPPORT:

private: 
	static const char* className();
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************

#endif /* __cplusplus */
#endif /* _MNodeMessage */
