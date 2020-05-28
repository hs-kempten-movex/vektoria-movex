#include "wald.h"

using namespace Vektoria;

void Wald::translateTreeToHeight(float x, float z, CPlacement* baum, CGeoTerrain* terrain)
{
	baum->TranslateYDelta(terrain->GetHeight(x, z));
}

//todo
//bäume scalen x2 / x3
//cluster klasse
//wald randomizen
//more poopys
//baum hitboxen 
//more more...

Wald::Wald(CGeoTerrain * terrain)
{
	//gleiche für poppy machen
	m_CBTBaum->SetRandomSeed(30285);
	m_CBTBaum->Iterate(150.0f, 0.2f, 0.0f);
	m_CBTBaum->Init(m_CBTBaum, 0);
	m_CBTBaum->DeIterate();

	poopy->SetRandomSeed(44444);
	poopy->Iterate(1.0f, 0.2f, 0.0f);
	poopy->Init(poopy, 0);
	poopy->DeIterate();

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

	//Translations der bäume
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

	//Rotations der Bäume
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



	m_pBaum1.ScaleDelta(3.0f);
	m_pBaum2.ScaleDelta(3.0f);
	m_pBaum3.ScaleDelta(3.0f);
	m_pBaum4.ScaleDelta(3.0f);
	m_pBaum5.ScaleDelta(3.0f);
	m_pBaum6.ScaleDelta(3.0f);
	m_pBaum7.ScaleDelta(3.0f);
	m_pBaum8.ScaleDelta(3.0f);
	m_pBaum9.ScaleDelta(3.0f);
	m_pBaum10.ScaleDelta(3.0f);
	//BaumCluster an den Wald hängen
	this->AddPlacement(&m_pBaumCluster1);
	//this->AddPlacement(&m_pBaumCluster2);
	//this->AddPlacement(&m_pBaumCluster3);

	//translate cluster //
	m_pBaumCluster1.TranslateDelta(100.0f, 0.0f, 0.0f);
	//m_pBaumCluster2.TranslateX(500.0f);
	//m_pBaumCluster3.TranslateX(550.0f);
	CHVector test1 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum1.GetPos();
	CHVector test2 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum2.GetPos();
	CHVector test3 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum3.GetPos();
	CHVector test4 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum4.GetPos();
	CHVector test5 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum5.GetPos();
	CHVector test6 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum6.GetPos();
	CHVector test7 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum7.GetPos();
	CHVector test8 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum8.GetPos();
	CHVector test9 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum9.GetPos();
	CHVector test10 = this->GetPos() + m_pBaumCluster1.GetPos() + m_pBaum10.GetPos();

	m_pPoopy.AddGeo(poopy);
	m_pBaumCluster1.AddPlacement(&m_pPoopy);


	CHVector testpoopy = this->GetPos() + m_pBaumCluster1.GetPos() + m_pPoopy.GetPos();

	this->translateTreeToHeight(test1.x, test1.z, &m_pBaum1, terrain);
	this->translateTreeToHeight(test2.x, test2.z, &m_pBaum2, terrain);
	this->translateTreeToHeight(test3.x, test3.z, &m_pBaum3, terrain);
	this->translateTreeToHeight(test4.x, test4.z, &m_pBaum4, terrain);
	this->translateTreeToHeight(test5.x, test5.z, &m_pBaum5, terrain);
	this->translateTreeToHeight(test6.x, test6.z, &m_pBaum6, terrain);
	this->translateTreeToHeight(test7.x, test7.z, &m_pBaum7, terrain);
	this->translateTreeToHeight(test8.x, test8.z, &m_pBaum8, terrain);
	this->translateTreeToHeight(test9.x, test9.z, &m_pBaum9, terrain);
	this->translateTreeToHeight(test10.x, test10.z, &m_pBaum10, terrain);
	this->translateTreeToHeight(testpoopy.x, testpoopy.z, &m_pPoopy, terrain);

}

Wald::~Wald()
{
}
