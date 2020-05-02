#include "wald.h"
#include "CherryBlossomTree.h"

using namespace Vektoria;

Wald::Wald()
{
	//CherryBlossomTree erstellen
	m_zpLSystem.AddGeo(&m_CBTBaum);
	m_zpLSystem.TranslateX(500.0f);

	//Baum1,2,3 Placements den CherryBlossomTree zuweisen
	m_pBaum1.AddPlacement(&m_zpLSystem);
	m_pBaum2.AddPlacement(&m_zpLSystem);
	m_pBaum3.AddPlacement(&m_zpLSystem);

	//Translations
	m_pBaum2.TranslateX(50.0f);
	m_pBaum3.TranslateX(60.0f);

	//BaumCluster erstellen
	m_pBaumCluster1.AddPlacement(&m_pBaum1);
	m_pBaumCluster2.AddPlacement(&m_pBaum2);
	m_pBaumCluster3.AddPlacement(&m_pBaum3);

	//BaumCluster an den Wald hängen
	m_pWald.AddPlacement(&m_pBaumCluster1);
	m_pWald.AddPlacement(&m_pBaumCluster2);
	m_pWald.AddPlacement(&m_pBaumCluster3);

}
