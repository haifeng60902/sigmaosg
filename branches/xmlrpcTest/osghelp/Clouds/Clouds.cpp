// Clouds.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SigmaUtil/SulClouds.h>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
 
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/KeySwitchMatrixManipulator>


osg::Node* createScene()
{
	osg::Group* pGroup = new osg::Group;
	pGroup->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF );
	pGroup->addChild( osgDB::readNodeFile("terrain_simple.ive") );
    return pGroup;
}

osg::Node* createClouds()
{
	osg::Group* pGroup = new osg::Group;
	CSulClouds* pClouds = new CSulClouds;
	pGroup->addChild( pClouds->getGroup() );
	return pGroup;
}

int _tmain(int argc, _TCHAR* argv[])
{
    // construct the viewer
    osg::ref_ptr<osgViewer::Viewer> rViewer = new osgViewer::Viewer;

    // set up the camera manipulators.
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

        keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
        keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
        keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
        keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );

        rViewer->setCameraManipulator( keyswitchManipulator.get() );
    }

    // make the viewer create a 800x600 window and position it at 32, 32
    rViewer->setUpViewInWindow( 32, 32, 800, 600 );

	osg::Group* pGroup = new osg::Group;
	pGroup->addChild( createScene() );

    // set the scene-graph data the viewer will render
    rViewer->setSceneData( pGroup );

	rViewer->setCameraManipulator( new osgGA::TrackballManipulator );

	pGroup->addChild( createClouds() );

    // execute main loop
    return rViewer->run();
}