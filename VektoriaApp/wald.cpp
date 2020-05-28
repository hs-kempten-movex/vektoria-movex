#include "wald.h"

using namespace Vektoria;

void Wald::translateTreeByHeight(float x, float z, CPlacement* baum, CGeoTerrain* terrain)
{
	baum->TranslateYDelta(terrain->GetHeight(x, z));
}

Wald::Wald(CGeoTerrain * terrain)
{
	//gleiche f�r poppy machen
	m_CBTBaum->SetRandomSeed(30285);
	m_CBTBaum->Iterate(150.0f, 0.2f, 0.0f);
	m_CBTBaum->Init(m_CBTBaum, 0);
	m_CBTBaum->DeIterate();

	//Baum1,2,3 Placements den CherryBlossomTree zuweisen
	m_pBaum1.AddGeo(m_CBTBaum);
	m_pBaum2.AddGeo(m_CBTBaum);
	m_pBaum3.AddGeo(m_CBTBaum);
	m_pBaum4.AddGeo(m_CBTBaum);
	m_pBaum5.AddGeo(m_CBTBaum);
	m_pBaum6.AddGeo(m_CBTBaum);
	m_pBaum7.AddGeo(m_CBTBaum);
	m_pBaum8.AddGeo(m_CBTBaum);
	m_pBaum9.AddGeo(m_CBTBaum);
	m_pBaum10.AddGeo(m_CBTBaum);

	//Translations der b�ume
	m_pBaum1.Translate(10.0f, 0.0f, 20.0f);
	m_pBaum2.Translate(-14.0f, 0.0f, 0.0f);
	m_pBaum3.Translate(36.0f, 0.0f, -42.0f);
	m_pBaum4.Translate(23.0f, 0.0f, -20.0f);
	m_pBaum5.Translate(-33.0f, 0.0f, 15.0f);
	m_pBaum6.Translate(-9.0f, 0.0f, -34.0f);
	m_pBaum7.Translate(49.0f, 0.0f, 8.0f);
	m_pBaum8.Translate(-4.0f, 0.0f, 19.0f);
	m_pBaum9.Translate(-0.0f, 0.0f, -15.0f);
	m_pBaum10.Translate(-13.0f, 0.0f, 31.0f);

	/*m_pBaum1.TranslateYDelta(150.0f);*/
	/*m_pBaum1.TranslateYDelta(terrain->GetHeight(10.0f, 20.0f));*/

	this->translateTreeByHeight(10.0f,  20.0f, &m_pBaum1, terrain);
	this->translateTreeByHeight(-14.0f, 0.0f, &m_pBaum2, terrain);
	this->translateTreeByHeight(36.0f, -42.0f, &m_pBaum3, terrain);
	this->translateTreeByHeight(23.0f, -20.0f, &m_pBaum4, terrain);
	this->translateTreeByHeight(-33.0f, 15.0f, &m_pBaum5, terrain);
	this->translateTreeByHeight(-9.0f, -34.0f, &m_pBaum6, terrain);
	this->translateTreeByHeight(49.0f, 8.0f, &m_pBaum7, terrain);
	this->translateTreeByHeight(-4.0f, 19.0f, &m_pBaum8, terrain);
	this->translateTreeByHeight(-0.0f, -15.0f, &m_pBaum9, terrain);
	this->translateTreeByHeight(-13.0f, 31.0f, &m_pBaum10, terrain);

	//Rotations der B�ume
	m_pBaum1.RotateYDelta(6.9f);
	m_pBaum2.RotateYDelta(42.0f);
	m_pBaum3.RotateYDelta(36.0f);
	m_pBaum4.RotateYDelta(-13.0f);
	m_pBaum5.RotateYDelta(70.0f);
	m_pBaum6.RotateYDelta(-34.0f);
	m_pBaum7.RotateYDelta(55.0f);
	m_pBaum8.RotateYDelta(-42.0f);
	m_pBaum9.RotateYDelta(15.0);
	m_pBaum10.RotateYDelta(49.0f);

	//BaumCluster erstellen
	m_pBaumCluster1.AddPlacement(&m_pBaum1);
	m_pBaumCluster1.AddPlacement(&m_pBaum2);
	m_pBaumCluster1.AddPlacement(&m_pBaum3);
	m_pBaumCluster1.AddPlacement(&m_pBaum4);
	m_pBaumCluster1.AddPlacement(&m_pBaum5);
	m_pBaumCluster1.AddPlacement(&m_pBaum6);
	m_pBaumCluster1.AddPlacement(&m_pBaum7);
	m_pBaumCluster1.AddPlacement(&m_pBaum8);
	m_pBaumCluster1.AddPlacement(&m_pBaum9);
	m_pBaumCluster1.AddPlacement(&m_pBaum10);

	//BaumCluster 2 erstellen 
	//m_pBaumCluster2.AddPlacement(&m_pBaum1);
	//m_pBaumCluster2.AddPlacement(&m_pBaum2);
	//m_pBaumCluster2.AddPlacement(&m_pBaum3);

	//BaumCluster 2 erstellen
	//m_pBaumCluster3.AddPlacement(&m_pBaum1);
	//m_pBaumCluster3.AddPlacement(&m_pBaum2);
	//m_pBaumCluster3.AddPlacement(&m_pBaum3);

	//BaumCluster an den Wald h�ngen
	this->AddPlacement(&m_pBaumCluster1);
	//this->AddPlacement(&m_pBaumCluster2);
	//this->AddPlacement(&m_pBaumCluster3);

	//translate cluster //
	m_pBaumCluster1.TranslateDelta(100.0f, 0.0f, 0.0f);
	//m_pBaumCluster2.TranslateX(500.0f);
	//m_pBaumCluster3.TranslateX(550.0f);
}

Wald::~Wald()
{
}
