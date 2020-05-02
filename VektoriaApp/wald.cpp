#include "wald.h"

using namespace Vektoria;

Wald::Wald()
{
	//CherryBlossomTree erstellen
	m_zpLSystem.AddGeo(&m_CBTBaum);

	//Baum1,2,3 Placements den CherryBlossomTree zuweisen
	m_pBaum1.AddPlacement(&m_zpLSystem);
	m_pBaum2.AddPlacement(&m_zpLSystem);
	m_pBaum3.AddPlacement(&m_zpLSystem);

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
	m_pWald.AddPlacement(&m_pBaumCluster1);
	m_pWald.AddPlacement(&m_pBaumCluster2);
	m_pWald.AddPlacement(&m_pBaumCluster3);

	//translate cluster
	m_pBaumCluster1.TranslateX(450.0f);
	m_pBaumCluster2.TranslateX(500.0f);
	m_pBaumCluster3.TranslateX(550.0f);
}

Wald::~Wald()
{
}
