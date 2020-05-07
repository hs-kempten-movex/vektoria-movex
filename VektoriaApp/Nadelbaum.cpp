#include "Nadelbaum.h"

Nadelbaum::Nadelbaum()
{

}

Nadelbaum::~Nadelbaum()
{

}

void Nadelbaum::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
{
	m_fAge = fAge;
	m_frTimeOfYear = frTimeOfYear;
	m_fRootCutHeight = fRootCutHeight;

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;
	// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

	// Immer
	m_bHasLeaves = true;



	m_fAgeStopped = fAge;
	if (m_fAgeStopped > 200.0f)
		m_fAgeStopped = 200.f;
	if (m_fAgeStopped < 1.0f)
		m_fAgeStopped = 1.0f;

	m_iTurtleStartLongitude = 16;
	m_iTurtleStartLattitude = 26;
	if (m_fAgeStopped > 50.0f)
	{
		m_iIterations = 14;
		m_iTurtleStartLongitude = 26;
		m_iTurtleStartLattitude = 26;
		m_fTurtleStartLength = 2.0f + (m_fAgeStopped - 50.0f) / 150.0f*0.5f;
		m_fTurtleStartRadius = 0.4f + (m_fAgeStopped - 50.0f) / 150.0f*0.4f;
		m_fSwakeRandom = 0.01f;
	}
	else if (m_fAgeStopped > 20.0f)
	{
		m_iIterations = 13;
		m_iTurtleStartLongitude = 22;
		m_iTurtleStartLattitude = 22;
		m_fTurtleStartLength = 1.5f + (m_fAgeStopped - 20.0f) / 30.0f*0.5f;
		m_fTurtleStartRadius = 0.2f + (m_fAgeStopped - 20.0f) / 30.0f*0.2f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 10.0f)
	{
		m_iIterations = 12;
		m_iTurtleStartLongitude = 18;
		m_iTurtleStartLattitude = 18;
		m_fTurtleStartLength = 1.0f + (m_fAgeStopped - 10.0f) / 10.0f*0.5f;
		m_fTurtleStartRadius = 0.1f + (m_fAgeStopped - 10.0f) / 10.0f*0.1f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 5.0f)
	{
		m_iIterations = 11;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.8f + (m_fAgeStopped - 5.0f) / 5.0f*0.2f;
		m_fTurtleStartRadius = 0.05f + (m_fAgeStopped - 5.0f) / 5.0f*0.05f;
		m_fSwakeRandom = 0.002f;
	}
	else if (m_fAgeStopped > 2.0f)
	{
		m_iIterations = 10;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.5f + (m_fAgeStopped - 2.0f) / 3.0f*0.3f;
		m_fTurtleStartRadius = 0.02f + (m_fAgeStopped - 2.0f) / 3.0f*0.03f;
		m_fSwakeRandom = 0.001f;
	}
	else if (m_fAgeStopped > 1.0f)
	{
		m_iIterations = 9;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 6;
		m_fTurtleStartLength = 0.3f + (m_fAgeStopped - 1.0f) / 1.0f*0.2f;
		m_fTurtleStartRadius = 0.01f + (m_fAgeStopped - 1.0f) / 1.0f*0.01f;
		m_fSwakeRandom = 0.0005f;
	}
	else
	{
		m_iIterations = 8;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 5;
		m_fTurtleStartLength = m_fAgeStopped * 0.3f;
		m_fTurtleStartRadius = m_fAgeStopped * 0.01f;
		m_fSwakeRandom = 0.0005f;
	}

	// m_fTurtleStartRadius /= 2.0f;
	// iIterations += 14;
	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
	SetDefaultFactorGravitation(0.05f);

	SetSwakeRandomFactor(m_fSwakeRandom);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);
	//------------------------
	// Erzeuge Stamm und Geäst:
	//------------------------


	SetAxiom("X");
	AddRule("30:X={r>0.03,(-23)(r0.85)(l0.9)_f[(r0.55)(^70)Y][(r0.55)(+180)(^70)Y][(r0.55)(-90)(^70)Y][(r0.55)(+90)(^70)Y]_fX}{r<0.0301,Y}");
	AddRule("30:X={r>0.03,(+10)(r0.85)(l0.9)_f[(r0.55)(^70)Y][(r0.55)(+180)(^70)Y][(r0.55)(-90)(^70)Y][(r0.55)(+90)(^70)Y](r0.85)(l0.9)_fX}{r<0.0301,Y}");
	AddRule("30:X={r>0.03,(+36)(r0.85)(l0.9)_f[(r0.55)(^70)Y][(r0.55)(+180)(^70)Y][(r0.55)(-90)(^70)Y][(r0.55)(+90)(^70)Y](r0.85)(l0.9)_fX}{r<0.0301,Y}");
	AddRule("10:X={r>0.03,(r0.85)(l0.9)_fX[(r0.55)(+180)(^70)Y]}{r<0.0301,Y}");
	AddRule("15:Y={r>0.03,+(r0.75)(l0.85)_(<2)f(r0.75)(l0.85)_f[(>25)(r0.75)A]Y}{r<0.0301,A}");
	AddRule("20:Y={r>0.03,+(r0.75)(l0.85)_(>4)f[(<30)(r0.75)A][(>35)(r0.75)A]Y}{r<0.0301,A}");
	AddRule("20:Y={r>0.03,+(r0.75)(l0.85)_(<7)f[(<42)(r0.75)A][(>35)(r0.75)(^15)A]Y}{r<0.0301,A}");
	AddRule("20:Y={r>0.03,+(r0.75)(l0.85)_(>6)f[(<19)(^15)(r0.75)A][(v50)(r0.75)A]Y}{r<0.0301,A}");
	AddRule("20:Y={r>0.03,+(r0.75)(l0.85)_(<6)f[(^31)(r0.75)A]Y}{r<0.0301,A}");
	AddRule("5:Y={r>0.03,}{r<0.0301,}");
	AddRule("C={b<99,A}{b=99,}");
	AddRule("33:A={r>0.03,(r0.55)(l0.6)f[(>20)(r0.75)(^15)fC]C}{r<0.031,B}");
	AddRule("33:A={r>0.03,(r0.55)(l0.6)f[(>29)(r0.75)(v15)fC]C}{r<0.031,B}");
	AddRule("34:A={r>0.03,(r0.55)(l0.6)fC}{r<0.031,B}");

	//AddRule("B=°(l0.6)[<l(+60)<l(+60)<l(+60)<l(+60)<l(+60)<l]f[<l(+60)<l(+60)<l(+60)<l(+60)<l(+60)<l]f[<l(+60)<l(+60)<l(+60)<l(+60)<l(+60)<l]");
	//test mit fruits (a) und leaves
	AddRule("B=(l0.6)[<a(+60)<a(+60)<a(+60)<a(+60)<a(+60)<a]f[<a(+60)<a(+60)<a(+60)<a(+60)<a(+60)<a]f[<a(+60)<a(+60)<a(+60)<a(+60)<a(+60)<a]");


	m_iIterations += 23;

	CGeoLSystem::Iterate(m_iIterations, m_acAxiom);

	m_iIterations -= 23; // Wegen Wurzel wieder zurückstellen!

	// ---------------
	// Erzeuge Wurzel:
	// ---------------


	if (fRootCutHeight < 0.0f)
	{

		m_pzgRoot = new CGeoLSystem();
		m_pzgRoot->m_random.m_uRand = m_random.m_uRand;

		m_pzgRoot->SetAxiom("'Z");
		m_pzgRoot->AddRule("50:Z=(l0.8)[(+0)(>90)X][(+123)(>92)X][(+239)(>88)X]°(r0.80)f[X]");
		m_pzgRoot->AddRule("50:Z=(l0.8)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X]°(r0.80)(>9)f[X]");
		m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(>10)X]");
		m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.79)<(r0.80)X][(l0.87)(>15)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<45)(r0.80)X][(l0.86)(>9)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<35)(r0.80)X][(l0.85)(>25)X]");


		m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);

	}


}

void Nadelbaum::DeIterate()
{
	((CGeoLSystem*)this)->DeIterate();
	if (m_pzgRoot)
		m_pzgRoot->DeIterate();
}


void Nadelbaum::Init(Nadelbaum * pzgTemplate, unsigned int uLoD)
{
	if (!pzgTemplate)
	{
		return;
	}
	CopyThis(*pzgTemplate);
	/*
	m_fAge = pzgTemplate->m_fAge;
	m_fAgeStopped = pzgTemplate->m_fAgeStopped;
	m_frTimeOfYear = pzgTemplate->m_frTimeOfYear;
	m_bHasLeaves = pzgTemplate->m_bHasLeaves;

	m_fRootCutHeight = pzgTemplate->m_fRootCutHeight;
	m_random.m_uRand = pzgTemplate->m_random.m_uRand;

	m_fSwakeRandom = pzgTemplate->m_fSwakeRandom;
	m_iIterations = pzgTemplate->m_iIterations;
	m_fTurtleStartRadius = pzgTemplate->m_fTurtleStartRadius;
	m_fTurtleStartLength = pzgTemplate->m_fTurtleStartLength;
	m_iTurtleStartLongitude = pzgTemplate->m_iTurtleStartLongitude;
	m_iTurtleStartLattitude = pzgTemplate->m_iTurtleStartLattitude;
	*/


	if (pzgTemplate->m_iToKill <= 0)
	{
		return;
	}

	char * acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

	if (!acTurtleOrdersMain)
	{
		return;
	}

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;
	// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

	// --------------
	// Erzeuge Blatt: 
	// --------------


	m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
	if (uLoD == 0)
	{
		CHVector avOuter[6];


		avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
		avOuter[1] = CHVector(0.02f, 0.0f, 0.99f, 1.0f);
		avOuter[2] = CHVector(0.04f, 0.0f, 0.9f, 1.0f);
		avOuter[3] = CHVector(0.04f, 0.0f, 0.1f, 1.0f);
		avOuter[4] = CHVector(0.02f, 0.0f, 0.01f, 1.0f);
		avOuter[5] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);




		for (int i = 0; i < 6; i++)
			m_zgLeafMain.AddOuter(&avOuter[i]);

		m_zgLeafMain.Init(&m_zmLeaf, true, true);
		SetGeoFruit(&m_zgLeafMain);

		/*CHMat mScale;
		mScale.Scale(20.0f);


		test = m_filewavefront.LoadGeo("models\\cylinder.obj");

		m_zgLeafMain.Transform(mScale);
		m_zgFruitMain.AddGeo(test);

		test->SetMaterial(&m_zmLeaf);
		SetGeoFruit(&m_zgFruitMain);*/

	}
	else if (uLoD <= 2)
	{
		CHMat mScale;
		mScale.Scale(20.0f);


		test = m_filewavefront.LoadGeo("models\\cylinder.obj");
		m_zgLeafMain.Transform(mScale);
		m_zgFruitMain.AddGeo(test);
		test->SetMaterial(&m_zmLeaf);
		SetGeoFruit(&m_zgFruitMain);

	}
	else
	{
		CHVector avOuter[5];
		avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
		avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
		avOuter[1] = CHVector(0.5f, 0.0f, 1.0f, 1.0f);
		avOuter[2] = CHVector(0.5f, 0.0f, 0.5f, 1.0f);
		avOuter[3] = CHVector(0.5f, 0.0f, 0.0f, 1.0f);
		avOuter[4] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 5; i++)
			m_zgLeafMain.AddOuter(&avOuter[i]);


		m_zgLeafMain.Init(&m_zmLeaf, true, true);
		SetGeoLeaf(&m_zgLeafMain);


	}
	// 0.0f Dez/Jan, 0.25 März/April, 0.5 Jun/Jul, 0.75 Sep/Okt
	//float fLeafScaling = 0.0f;
	//if (frTimeShifted >= 0.1f && frTimeShifted <= 0.8f) // Von Februar bis November
	//	fLeafScaling = 1.6f*(frTimeShifted - 0.1f) / 0.7f;

	/*CHMat mScale;
	mScale.Scale(2.0f);
	m_zgLeafMain.Transform(mScale);*/

	m_zmLeaf.MakeTextureDiffuse("textures\\darkgreen_image.jpg");
	/*

	// Nicht löschen!
	m_zmLeaf.MakeTextureDiffuse(".\\..\\..\\Lib\\Materials\\LeafBirch\\LeafBirchD.jpg");
	m_zmLeaf.MakeTextureSpecular(".\\..\\..\\Lib\\Materials\\LeafBirch\\LeafBirchS.jpg");
	m_zmLeaf.MakeTextureBump(".\\..\\..\\Lib\\Materials\\LeafBirch\\LeafBirchB.jpg");
	m_zmLeaf.MakeTextureThickness(".\\..\\..\\Lib\\Materials\\LeafBirch\\LeafBirchT.jpg", CColor(0.3, 1.0, 0.3));
	m_zmLeaf.SetSpecularSharpness(100.0f);
	m_zmLeaf.SetLightScatteringOn();
	m_zmLeaf.SavePreset("LeafBirch");
	*/
	float faLeafColoring = 0.0f;
	float frColorScaling = 1.0f;
	if (frTimeShifted >= 0.7f) // Ab Anfang September
	{
		faLeafColoring = (frTimeShifted - 0.6f) / -0.15f*THIRDPI;
		m_zmLeaf.RotateHue(faLeafColoring);
		frColorScaling = 1.0f - (frTimeShifted - 0.7f) / 0.3f;
		m_zmLeaf.ScaleDelta(frColorScaling);
	}

	SetMaterialLeaf(&m_zmLeaf);

	/*

	m_zmLeaf.MakeTextureDiffuse(".\..\..\Lib\Materials\LeafBirch\LeafBirchD.jpg");
	m_zmLeaf.MakeTextureThickness(".\..\..\Lib\Materials\LeafBirch\LeafBirchH.jpg", CColor(0.3f, 1.0f, 0.2f));
	m_zmLeaf.MakeTextureSpecular(".\..\..\Lib\Materials\LeafBirch\LeafBirchS.jpg");
	m_zmLeaf.MakeTextureBump(".\..\..\Lib\Materials\LeafBirch\LeafBirchB.jpg");
	m_zmLeaf.SetLightScatteringOn();

	m_zmLeaf.SetRimLightStrength(0.1f);
	m_zmLeaf.SetSubSurfaceColor(CColor(0.3, 1.0f, 0.3f));
	m_zmLeaf.SavePreset("LeafBirch");
	*/


	m_zmBark.MakeTextureDiffuse("textures\\bark.png");
	m_zmBark.MakeTextureBump("textures\\bark_n.png");
	m_zmBark.MakeTextureHeight("textures\\bark_h.png");
	//m_zmBark.SetSpecularSharpness(100.0f);
	//m_zmBark.SetTextureSpecularBlack();
	m_zmBark.SetTextureSpecularAsDiffuse();
	SetMaterial(&m_zmBark);


	SetSwakeRandomFactor(m_fSwakeRandom);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);
	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
	SetDefaultFactorGravitation(0.5f);

	if (uLoD == 1)
	{
		m_iTurtleStartLongitude /= 2;
		m_iTurtleStartLattitude /= 2;
	}
	if (uLoD == 2)
	{
		m_iTurtleStartLongitude /= 4;
		m_iTurtleStartLattitude /= 4;
		if (m_iTurtleStartLongitude < 4)
			m_iTurtleStartLongitude = 4;
	}

	if (uLoD >= 3)
	{
		m_iTurtleStartLongitude /= 6;
		m_iTurtleStartLattitude /= 6;
		if (m_iTurtleStartLongitude < 4)
			m_iTurtleStartLongitude = 4;

		if (uLoD >= 5)
		{
			m_iTurtleStartLongitude = 0;
			m_iTurtleStartLattitude = 0;
		}
		SetTurtleEndLongitude(0);
		SetTurtleEndLattitude(0);
		if (m_bHasLeaves)
		{
			CHMat mLoD;
			if (uLoD == 4)
			{
				mLoD.Scale(3);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(20);
			}
			else if (uLoD == 5)
			{
				mLoD.Scale(7.5f);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(200);
			}
			else if (uLoD >= 6)
			{
				mLoD.Scale(20);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(2000);
			}
		}

	}


	if (m_iTurtleStartLattitude == 1)
		m_iTurtleStartLattitude = 2;
	if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
		m_iTurtleStartLattitude = 2;
	SetTurtleStartLongitude(m_iTurtleStartLongitude);
	SetTurtleStartLattitude(m_iTurtleStartLattitude);

	Interprete(acTurtleOrdersMain);

	// ---------------
	// Erzeuge Wurzel:
	// ---------------


	if (pzgTemplate->m_pzgRoot && uLoD < 2)
	{
		if (!m_pzgRoot)
			m_pzgRoot = new CGeoLSystem();

		char * acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
		m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

		m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
		m_pzgRoot->SetDefaultFactorGravitation(0.1f);

		m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentlänge (Default: 1.0)
		m_pzgRoot->SetTurtleStartDir(CHVector(0.0f, -1.0f, 0.0f, 0.0f));
		//		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, 2.5f, 0.0f, 1.0f));

		m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
		m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
		m_pzgRoot->SetSwakeRandomFactor(m_fSwakeRandom);
		m_pzgRoot->SetTurtleStartHeight(m_fTurtleStartLength);
		m_pzgRoot->SetTurtleStartRadius(m_fTurtleStartRadius);
		m_pzgRoot->SetTurtleStartLongitude(m_iTurtleStartLongitude);
		m_pzgRoot->SetTurtleStartLattitude(m_iTurtleStartLattitude);
		m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
		m_pzgRoot->SetDefaultFactorGravitation(0.1f);

		m_pzgRoot->Interprete(acTurtleOrdersRoot);

		AddGeo(m_pzgRoot);
	}

}

float Nadelbaum::GetOptimalLoDMin(float fAge, unsigned int uLoD)
{
	float m_fAgeStopped = fAge;
	if (m_fAgeStopped > 500.0f)
		m_fAgeStopped = 500.f;
	if (m_fAgeStopped < 2.1f)
		m_fAgeStopped = 2.1f;
	if (uLoD == 0)
		return 0.0F;
	return (40.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD - 1);
}

float Nadelbaum::GetOptimalLoDMax(float fAge, unsigned int uLoD)
{
	float m_fAgeStopped = fAge;
	if (m_fAgeStopped > 500.0f)
		m_fAgeStopped = 500.f;
	if (m_fAgeStopped < 2.1f)
		m_fAgeStopped = 2.1f;
	return (40.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD);
}