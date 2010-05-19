// SulShaderInstancingBillboards.cpp

#include "stdafx.h"
#include "SulShaderInstancingBillboards.h"

CSulShaderInstancingBillboards::CSulShaderInstancingBillboards( osg::Node* pNode, Sigma::int32 numInstances, Sigma::int32 texUnit, Sigma::int32 texSizeSquared, unsigned int useLights, osg::Program* pProg ) :
CSulShaderBase( pNode )
{
	if ( !pProg )
	{
		addShaderFrag( "shaders/instancing_billboards.frag" );
		addShaderVert( "shaders/instancing_billboards.vert" );

		m_rUniform_windFactor = new osg::Uniform( "windFactor", 1.0f );
		//m_rUniform_windFactor->set( 1.0f );
		m_rSS->addUniform( m_rUniform_windFactor );

		m_rUniform_grassStretch = new osg::Uniform( osg::Uniform::FLOAT, "grassStretch" );
		m_rUniform_grassStretch->set( 1.0f );
		m_rSS->addUniform( m_rUniform_grassStretch );

		m_rUniform_texPositions = new osg::Uniform( osg::Uniform::SAMPLER_2D, "texPositions" );
		m_rUniform_texPositions->set( 1 );		
		m_rSS->addUniform( m_rUniform_texPositions );

		osg::ref_ptr<osg::Uniform> rUniform_tex = new osg::Uniform( osg::Uniform::SAMPLER_2D, "tex" );
		rUniform_tex->set( texUnit );		
		m_rSS->addUniform( rUniform_tex );

		osg::ref_ptr<osg::Uniform> rUniform_texSizeSquared = new osg::Uniform( osg::Uniform::INT, "texSizeSquared" );
		rUniform_texSizeSquared->set( texSizeSquared );
		m_rSS->addUniform( rUniform_texSizeSquared );

		m_rUniform_numInstances = new osg::Uniform( osg::Uniform::INT, "numInstances" );
		m_rUniform_numInstances->set( numInstances );
		m_rSS->addUniform( m_rUniform_numInstances );

		m_rUniform_useLights = new osg::Uniform( osg::Uniform::INT, "useLights" );
		m_rUniform_useLights->set( (int)useLights );
		m_rSS->addUniform( m_rUniform_useLights );
	}
}
