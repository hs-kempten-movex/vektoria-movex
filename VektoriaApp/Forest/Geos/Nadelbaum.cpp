#include "Nadelbaum.h"

using namespace ForestNS;

Nadelbaum::Nadelbaum()
{

}

Nadelbaum::~Nadelbaum()
{

}

void Nadelbaum::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD)
{
	m_fAge = fAge;
	m_frTimeOfYear = frTimeOfYear;
	m_fRootCutHeight = fRootCutHeight;

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;
	// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

	if (isLoD == false)
	{
		m_bHasLeaves = false;
		m_bIsHitbox = true;
	}



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
		m_fTurtleStartRadius = 0.4f + (m_fAgeStopped - 50.0f) / 150.0f*0.4f*0.75f;
		m_fSwakeRandom = 0.01f;
	}
	else if (m_fAgeStopped > 20.0f)
	{
		m_iIterations = 13;
		m_iTurtleStartLongitude = 22;
		m_iTurtleStartLattitude = 22;
		m_fTurtleStartLength = 1.5f + (m_fAgeStopped - 20.0f) / 30.0f*0.5f;
		m_fTurtleStartRadius = 0.2f + (m_fAgeStopped - 20.0f) / 30.0f*0.2f*0.75f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 10.0f)
	{
		m_iIterations = 12;
		m_iTurtleStartLongitude = 18;
		m_iTurtleStartLattitude = 18;
		m_fTurtleStartLength = 1.0f + (m_fAgeStopped - 10.0f) / 10.0f*0.5f;
		m_fTurtleStartRadius = 0.1f + (m_fAgeStopped - 10.0f) / 10.0f*0.1f*0.75f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 5.0f)
	{
		m_iIterations = 11;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.8f + (m_fAgeStopped - 5.0f) / 5.0f*0.2f;
		m_fTurtleStartRadius = 0.05f + (m_fAgeStopped - 5.0f) / 5.0f*0.05f*0.75f;
		m_fSwakeRandom = 0.002f;
	}
	else if (m_fAgeStopped > 2.0f)
	{
		m_iIterations = 10;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.5f + (m_fAgeStopped - 2.0f) / 3.0f*0.3f;
		m_fTurtleStartRadius = 0.02f + (m_fAgeStopped - 2.0f) / 3.0f*0.03f*0.75f;
		m_fSwakeRandom = 0.001f;
	}
	else if (m_fAgeStopped > 1.0f)
	{
		m_iIterations = 9;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 6;
		m_fTurtleStartLength = 0.3f + (m_fAgeStopped - 1.0f) / 1.0f*0.2f;
		m_fTurtleStartRadius = 0.01f + (m_fAgeStopped - 1.0f) / 1.0f*0.01f*0.75f;
		m_fSwakeRandom = 0.0005f;
	}
	else
	{
		m_iIterations = 8;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 5;
		m_fTurtleStartLength = m_fAgeStopped * 0.3f;
		m_fTurtleStartRadius = m_fAgeStopped * 0.01f*0.75f;
		m_fSwakeRandom = 0.0005f;
	}

	// m_fTurtleStartRadius /= 2.0f;
	// iIterations += 14;
	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
	SetDefaultFactorGravitation(0.005f);

	SetSwakeRandomFactor(m_fSwakeRandom);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);
	//------------------------
	// Erzeuge Stamm und Geäst:
	//------------------------

	// U -> Start
	// X -> Stamm
	// B -> Die Nadeln
	// D -> Der Zweig, an dem die Nadeln sind (mit fester Breite und Länge)

	SetAxiom("U");
	// Falls Baum relativ alt, zeichne einen Stamm, der 
	AddRule("U={r>0.6,(r0.85)(l0.8)_fU}{r<0.601,X}");

	// Stamm
	AddRule("X={r>0.04,(r0.85)(l0.95)_f[(r0.25)(^70)E][(r0.25)(+45)(^70)E][(r0.25)(+90)(^70)E][(r0.25)(+135)(^70)E][(r0.25)(+180)(^70)E][(r0.25)(-45)(^70)E][(r0.25)(-90)(^70)E][(r0.25)(-135)(^70)E](+10)X}{r<0.0401,D}");

	if (m_bIsHitbox == false) {
		// Reset turtle length & zeichne ein mini kleines Stück Ast, damit der sichtbare Ast dann gleich schön dünn anfängt
		AddRule("50:E=(r0.6)(l0.1)f(l15.5)J");
		AddRule("50:E=");

		// Äste 
		AddRule("20:J={r>0.008,&(r0.75)(l0.79)_(v10)(<2)f[(>35)(r0.75)J]J}{r<0.00801,D}");
		AddRule("20:J={r>0.008,&(r0.75)(l0.75)_(v10)(>4)f[(<42)(r0.75)J][(v32)(r0.75)J]J}{r<0.00801,D}");
		AddRule("20:J={r>0.008,&(r0.75)(l0.69)_(v10)(<7)f[(<42)(r0.75)J][(v32)(r0.75)J]J}{r<0.00801,D}");
		AddRule("20:J={r>0.008,&(r0.75)(l0.75)_(v10)(>6)f[(<39)(r0.75)J]J}{r<0.00801,D}");
		AddRule("20:J={r>0.008,&(r0.75)(l0.75)_(v10)(<6)f[(<42)(r0.75)J][(^38)(r0.75)J]J}{r<0.00801,D}");

		// Die Nadel-Äste
		AddRule("D={r>0.004,(+10)[B](r0.99)(L0.01)_fD}{r<0.00401,}");

		// Die Nadeln
		AddRule("B=(R0.09)(L0.09)[^n][<n][vn][>n]");
	}
	
	m_iIterations += 10;

	CGeoLSystem::Iterate(m_iIterations, m_acAxiom);

	m_iIterations -= 10; // Wegen Wurzel wieder zurückstellen!

	// ---------------
	// Erzeuge Wurzel:
	// ---------------


	if (fRootCutHeight < 0.0f)
	{

		m_pzgRoot = new CGeoLSystem();
		m_pzgRoot->m_random.m_uRand = m_random.m_uRand;
		m_pzgRoot->SetAxiom("Z");
		m_pzgRoot->AddRule("50:Z=#(r0.80)(l0.95)[(>90)X][(+123)(>92)X][(+239)(>88)X][X]");
		m_pzgRoot->AddRule("50:Z=#(r0.80)(l0.95)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X](>9)[X]");
		m_pzgRoot->AddRule("5:X={r>0.007,#!+(r0.80)(l0.9)_f[!(>10)X]}{r<0.00701,}");
		m_pzgRoot->AddRule("45:X={r>0.007,#!+(r0.80)(l0.9)_f[!<(r0.80)X][!(>15)X]}{r<0.00701,}");
		m_pzgRoot->AddRule("25:X={r>0.007,#!+(r0.80)(l0.9)_f[!(<45)(r0.80)X][!(>9)X]}{r<0.00701,}");
		m_pzgRoot->AddRule("25:X={r>0.007,#!+(r0.80)(l0.9)_f[!(<35)(r0.80)X][!(>25)X]}{r<0.00701,}");


		m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);

	}


}

void Nadelbaum::DeIterate()
{
	((CGeoLSystem*)this)->DeIterate();
	if (m_pzgRoot)
		m_pzgRoot->DeIterate();
}


void Nadelbaum::Init(IPlantGeo * pzgTemplate, unsigned int uLoD)
{
	if (!pzgTemplate)
	{
		return;
	}
	CopyThis(*pzgTemplate);


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


		for (int i = 0; i < 6; i++) {
			m_zgLeafMain.AddOuter(&avOuter[i]);
		}

		SetMaxNeedleBending(-0.12f); // vorher: 0.08f, da standen die nadeln dann ab
		SetMaxNeedleFolding(0.3f);
		m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.0f);
		SetGeoLeaf(&m_zgLeafMain);


	}
	else if (uLoD <= 2)
	{
		CHVector avOuter[4];


		avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
		avOuter[1] = CHVector(0.02f, 0.0f, 0.99f, 1.0f);
		avOuter[2] = CHVector(0.04f, 0.0f, 0.1f, 1.0f);
		avOuter[3] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);


		for (int i = 0; i < 4; i++) {
			m_zgLeafMain.AddOuter(&avOuter[i]);
		}

		SetMaxNeedleBending(-0.08f);
		SetMaxNeedleFolding(1.3f);
		m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.0f);
		SetGeoLeaf(&m_zgLeafMain);
		CHMat mScale;
		mScale.Scale(2.0f);
		m_zgLeafMain.Transform(mScale);
		SetLeafSkipFactor(4);
	}
	else
	{
		CHVector avOuter[4];


		avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
		avOuter[1] = CHVector(0.02f, 0.0f, 0.99f, 1.0f);
		avOuter[2] = CHVector(0.04f, 0.0f, 0.1f, 1.0f);
		avOuter[3] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);


		for (int i = 0; i < 4; i++) {
			m_zgLeafMain.AddOuter(&avOuter[i]);
		}

		SetMaxNeedleBending(-0.08f);
		SetMaxNeedleFolding(1.3f);
		m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.001f);
		SetGeoLeaf(&m_zgLeafMain);
		CHMat mScale;
		mScale.Scale(1.5f*(float)uLoD);
		m_zgLeafMain.Transform(mScale);
		SetLeafSkipFactor(75 * uLoD);

	}

	m_zmLeaf.MakeTextureDiffuse("textures\\darkgreen_image.jpg");
	m_zmLeaf.SetSpecularStrength(0.01f);

	//float faLeafColoring = 0.0f;
	//float frColorScaling = 1.0f;
	//if (frTimeShifted >= 0.7f) // Ab Anfang September
	//{
	//	faLeafColoring = (frTimeShifted - 0.6f) / -0.15f*THIRDPI;
	//	m_zmLeaf.RotateHue(faLeafColoring);
	//	frColorScaling = 1.0f - (frTimeShifted - 0.7f) / 0.3f;
	//	m_zmLeaf.ScaleDelta(frColorScaling);
	//}

	SetMaterialLeaf(&m_zmLeaf);


	m_zmBark.MakeTextureDiffuse("textures\\bark.png");
	m_zmBark.MakeTextureBump("textures\\bark_n.png");
	m_zmBark.MakeTextureHeight("textures\\bark_h.png");
	m_zmBark.MakeTextureSpecular("textures\\bark_s.png");
	// setvertexdisplacement on
	//m_zmBark.SetSpecularSharpness(100.0f);
	//m_zmBark.SetTextureSpecularBlack();
	m_zmBark.SetTextureSpecularAsDiffuse();
	SetMaterial(&m_zmBark);
	m_zmBark.SetDisplacementOn();
	m_zmBark.SetDisplacementStrength(0.1f);

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
		
	}
	if (m_bIsHitbox == true)
	{
		m_iTurtleStartLongitude = 8;
		m_iTurtleStartLattitude = 8;
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
		m_pzgRoot->SetDefaultFactorGravitation(0.12f);

		m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentlänge (Default: 1.0)
		m_pzgRoot->SetTurtleStartDir(CHVector(0.0f, -1.0f, 0.0f, 0.0f));

		m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
		m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
		m_pzgRoot->SetSwakeRandomFactor(m_fSwakeRandom);
		m_pzgRoot->SetTurtleStartRadius(m_fTurtleStartRadius);
		m_pzgRoot->SetTurtleStartHeight(m_fTurtleStartLength);
		m_pzgRoot->SetTurtleStartLongitude(m_iTurtleStartLongitude);
		m_pzgRoot->SetTurtleStartLattitude(m_iTurtleStartLattitude);

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