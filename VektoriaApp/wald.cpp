#include "wald.h"

using namespace Vektoria;

Wald::Wald()
{
	//CherryBlossomTree erstellen
	//m_zpLSystem.AddGeo(&m_CBTBaum);

	//Baum1,2,3 Placements den CherryBlossomTree zuweisen
	m_pBaum1.AddGeo(&m_CBTBaum);
	m_pBaum2.AddGeo(&m_CBTBaum);
	m_pBaum3.AddGeo(&m_CBTBaum);

	//BaumCluster erstellen
	m_pBaumCluster1.AddPlacement(&m_pBaum1);
	m_pBaumCluster1.AddPlacement(&m_pBaum2);
	m_pBaumCluster1.AddPlacement(&m_pBaum3);

	//BaumCluster erstellen
	m_pBaumCluster2.AddPlacement(&m_pBaum1);
	m_pBaumCluster2.AddPlacement(&m_pBaum2);
	m_pBaumCluster2.AddPlacement(&m_pBaum3);

	//BaumCluster erstellen
	m_pBaumCluster3.AddPlacement(&m_pBaum1);
	m_pBaumCluster3.AddPlacement(&m_pBaum2);
	m_pBaumCluster3.AddPlacement(&m_pBaum3);

	//BaumCluster an den Wald hängen
	this->AddPlacement(&m_pBaumCluster1);
	this->AddPlacement(&m_pBaumCluster2);
	this->AddPlacement(&m_pBaumCluster3);

	//translate cluster
	m_pBaumCluster1.TranslateX(450.0f);
	m_pBaumCluster2.TranslateX(500.0f);
	m_pBaumCluster3.TranslateX(550.0f);
}

Wald::~Wald()
{
}
