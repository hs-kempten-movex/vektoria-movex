#include "GeoBioJapanischerSchildfarn.h"

using namespace ForestNS;

GeoBioJapanischerSchildfarn::GeoBioJapanischerSchildfarn()
{
}


GeoBioJapanischerSchildfarn::~GeoBioJapanischerSchildfarn()
{
}

void GeoBioJapanischerSchildfarn::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD)
{
	m_fAge = fAge;
	//m_frTimeOfYear = frTimeOfYear;
	m_fRootCutHeight = fRootCutHeight;

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;

	m_fAgeStopped = fAge;

	// Der Japanische Schildfarn ist mehrj‰hrig, nehme mal 5 -> kleinstes is age 3, sonst schauts komisch aus
	if (m_fAgeStopped > 5.0f)
		m_fAgeStopped = 5.0f;
	if (m_fAgeStopped < 3.01f)
		m_fAgeStopped = 3.01f;

	// Der Japanische Schildfarn kann bis zu 90 cm groﬂ werden
	// Der "Stamm" w‰chst sehr kurz hoch, und verzweight sich dann sofort mehrmals:
	// Die Verzweigungen sind sehr lang, und haben die "Bl‰tter" dran.:

	m_iIterations = 68;
	m_iTurtleStartLongitude = 15;
	m_iTurtleStartLattitude = 23;
	m_fTurtleStartLength = 0.008f + m_fAgeStopped * 0.03f;
	m_fTurtleStartRadius = /*0.002f + */m_fAgeStopped * 0.03f;



	SetDefaultAngles(HALFPI, HALFPI, HALFPI);
	SetDefaultFactorGravitation(0.5f);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);


	//------------------------
	// Erzeuge Stamm und Ge‰st:
	//------------------------

	// Der "Stamm" w‰chst sehr kurz hoch, und verzweight sich dann sofort mehrmals.
	// Die Verzweigungen sind sehr lang, und haben die "Bl‰tter" dran.
	SetAxiom("A");

	// "Stamm"
	AddRule("A={r>0.035, _(+25)(r0.80)f[^B][<B][>B][^B]A}{r<0.0351,_(+10)(r0.95)f[^B][<B][>B][^B]}");

	// Soll ¸berhaupt eine Verzweigung gezeichnet werden? 

	AddRule("50:B=F");
	AddRule("50:B=");

	/* 1. Verzweigung in zuf‰lligen Winkeln nach oben (30-60∞)*/
	AddRule("20:F={r>0.001,&(^55)(r0.98)(l0.98)f[D]C}{r<0.00101,}");
	AddRule("20:F={r>0.001,&(^35)(r0.98)(l0.98)f[D]C}{r<0.00101,}");
	AddRule("20:F={r>0.001,&(^40)(r0.98)(l0.98)f[D]C}{r<0.00101,}");
	AddRule("20:F={r>0.001,&(^45)(r0.98)(l0.98)f[D]C}{r<0.00101,}");
	AddRule("20:F={r>0.001,&(^50)(r0.98)(l0.98)f[D]C}{r<0.00101,}");


	// Weiter grade

	AddRule("C={r>0.03,(v1)(r0.98)(l0.99)_f[D]C}{r<0.0301,E}");

	// Bl‰tter gehen aus irgendwelchen Gr¸nden nur in eine Richtung wenn beide in der selben Rule gezeichnet werden sollen
	// Die Bl‰tter
	AddRule("D=(l6.0)(r20.0)[<0l][>0l]");

	//AddRule("D=(l8.0)(r10.0)[<0l][>0l]");
	//AddRule("F=(l8.0)(r10.0)[<0l][>0l]")
	// So gehts in beide Richtungen 

	/*AddRule("50:D=[(l8.0)(r8.0)>0l]");
	AddRule("50:D=[(l8.0)(r8.0)<0l]");*/

	// Ende der Bl‰tter, eigentlich, dass 7 Bl‰tter noch am Ende in nem Halbkranz gezeichnet werden

	AddRule("E=(l6.0)(r18.0)[(<72)0l][(<54)0l][(<36)0l][(<18)0l][0l][(>18)0l][(>36)0l][(>54)0l][(>72)0l]");
	/*AddRule("E=(l16.0)(r20.0)f");*/

	CGeoLSystem::Iterate(m_iIterations, m_acAxiom);

}

void GeoBioJapanischerSchildfarn::DeIterate()
{
	((CGeoLSystem*)this)->DeIterate();
	if (m_pzgRoot)
		m_pzgRoot->DeIterate();
}


void GeoBioJapanischerSchildfarn::Init(IPlantGeo * pzgTemplate, unsigned int uLoD)
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


	m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.07f, 0.5f, 1.0f));

	CHVector avOuter[78];

	// "Stiel"
	avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
	avOuter[1] = CHVector(0.01f, 0.0f, 0.999f, 1.0f);
	avOuter[2] = CHVector(0.015f, 0.0f, 0.98f, 1.0f);

	// 1. mal nach auﬂen
	avOuter[3] = CHVector(0.045f, 0.0f, 0.95f, 1.0f);
	avOuter[4] = CHVector(0.08f, 0.0f, 0.92f, 1.0f);
	avOuter[5] = CHVector(0.095f, 0.0f, 0.875f, 1.0f);

	// 1. mal nach innen
	avOuter[6] = CHVector(0.075f, 0.0f, 0.88f, 1.0f);
	avOuter[7] = CHVector(0.05f, 0.0f, 0.9f, 1.0f);
	avOuter[8] = CHVector(0.015f, 0.0f, 0.92f, 1.0f);

	// 2. mal nach auﬂen
	avOuter[9] = CHVector(0.045f, 0.0f, 0.88f, 1.0f);
	avOuter[10] = CHVector(0.075f, 0.0f, 0.85f, 1.0f);
	avOuter[11] = CHVector(0.1f, 0.0f, 0.81f, 1.0f);
	avOuter[12] = CHVector(0.09f, 0.0f, 0.78f, 1.0f);

	// 2. mal nach innen
	avOuter[13] = CHVector(0.07f, 0.0f, 0.795f, 1.0f);
	avOuter[14] = CHVector(0.03f, 0.0f, 0.8325f, 1.0f);
	avOuter[15] = CHVector(0.02f, 0.0f, 0.8325f, 1.0f);

	// 3. mal nach auﬂen
	avOuter[16] = CHVector(0.02f, 0.0f, 0.825f, 1.0f);
	avOuter[17] = CHVector(0.035f, 0.0f, 0.79f, 1.0f);
	avOuter[18] = CHVector(0.095f, 0.0f, 0.76f, 1.0f);
	avOuter[19] = CHVector(0.105f, 0.0f, 0.71f, 1.0f);

	// 3. mal nach innen
	avOuter[20] = CHVector(0.085f, 0.0f, 0.70175f, 1.0f);
	avOuter[21] = CHVector(0.04f, 0.0f, 0.76f, 1.0f);
	avOuter[22] = CHVector(0.025f, 0.0f, 0.755f, 1.0f);

	// 4. mal nach auﬂen
	avOuter[23] = CHVector(0.07f, 0.0f, 0.725f, 1.0f);
	avOuter[24] = CHVector(0.09f, 0.0f, 0.69f, 1.0f);
	avOuter[25] = CHVector(0.09f, 0.0f, 0.67f, 1.0f);
	avOuter[26] = CHVector(0.1f, 0.0f, 0.65f, 1.0f);

	// 4. mal nach innen
	avOuter[27] = CHVector(0.09f, 0.0f, 0.65f, 1.0f);
	avOuter[28] = CHVector(0.075f, 0.0f, 0.655f, 1.0f);

	// 5. mal nach auﬂen
	avOuter[29] = CHVector(0.085f, 0.0f, 0.63f, 1.0f);
	avOuter[30] = CHVector(0.095f, 0.0f, 0.62f, 1.0f);
	avOuter[31] = CHVector(0.095f, 0.0f, 0.59f, 1.0f);

	// 5. mal nach innen
	avOuter[32] = CHVector(0.075f, 0.0f, 0.6f, 1.0f);
	avOuter[33] = CHVector(0.05f, 0.0f, 0.61f, 1.0f);
	avOuter[34] = CHVector(0.03f, 0.0f, 0.63f, 1.0f);

	// 6. mal nach auﬂen
	avOuter[35] = CHVector(0.035f, 0.0f, 0.61f, 1.0f);
	avOuter[36] = CHVector(0.06f, 0.0f, 0.685f, 1.0f);
	avOuter[37] = CHVector(0.08f, 0.0f, 0.635f, 1.0f);

	// 6. mal nach auﬂen
	avOuter[38] = CHVector(0.055f, 0.0f, 0.545f, 1.0f);

	// 6. mal nach innen
	avOuter[39] = CHVector(0.07f, 0.0f, 0.53f, 1.0f);
	avOuter[40] = CHVector(0.085f, 0.0f, 0.47f, 1.0f);

	// 7. mal nach auﬂen
	avOuter[41] = CHVector(0.07f, 0.0f, 0.48f, 1.0f);

	// 7. mal nach innen
	avOuter[42] = CHVector(0.08f, 0.0f, 0.44f, 1.0f);
	avOuter[43] = CHVector(0.08f, 0.0f, 0.425f, 1.0f);

	// 8. mal nach auﬂen
	avOuter[44] = CHVector(0.06f, 0.0f, 0.435f, 1.0f);

	// 8. mal nach innen
	avOuter[45] = CHVector(0.07f, 0.0f, 0.4125f, 1.0f);
	avOuter[46] = CHVector(0.075f, 0.0f, 0.38f, 1.0f);

	// 9. mal nach auﬂen
	avOuter[47] = CHVector(0.065f, 0.0f, 0.375f, 1.0f);
	avOuter[48] = CHVector(0.07f, 0.0f, 0.34f, 1.0f);

	// 9. mal nach innen
	avOuter[49] = CHVector(0.05f, 0.0f, 0.35f, 1.0f);

	// 10. mal nach auﬂen
	avOuter[50] = CHVector(0.075f, 0.0f, 0.28f, 1.0f);

	// 10. mal nach innen
	avOuter[51] = CHVector(0.05f, 0.0f, 0.29f, 1.0f);
	avOuter[52] = CHVector(0.035f, 0.0f, 0.3f, 1.0f);

	// 11. mal nach auﬂen
	avOuter[53] = CHVector(0.055f, 0.0f, 0.28f, 1.0f);
	avOuter[54] = CHVector(0.08f, 0.0f, 0.23f, 1.0f);

	// 11. mal nach innen
	avOuter[55] = CHVector(0.06f, 0.0f, 0.24f, 1.0f);
	avOuter[56] = CHVector(0.04f, 0.0f, 0.25f, 1.0f);

	// 12. mal nach auﬂen
	avOuter[57] = CHVector(0.07f, 0.0f, 0.21f, 1.0f);
	avOuter[58] = CHVector(0.075f, 0.0f, 0.2f, 1.0f);

	// 12. mal nach innen
	avOuter[59] = CHVector(0.045f, 0.0f, 0.195f, 1.0f);
	avOuter[60] = CHVector(0.03f, 0.0f, 0.22f, 1.0f);

	// 13. mal nach auﬂen
	avOuter[61] = CHVector(0.05f, 0.0f, 0.18f, 1.0f);
	avOuter[62] = CHVector(0.06f, 0.0f, 0.165f, 1.0f);

	// 13. mal nach innen
	avOuter[63] = CHVector(0.05f, 0.0f, 0.16f, 1.0f);
	avOuter[64] = CHVector(0.02f, 0.0f, 0.17f, 1.0f);

	// 14. mal nach auﬂen
	avOuter[65] = CHVector(0.0425f, 0.0f, 0.14f, 1.0f);
	avOuter[66] = CHVector(0.045f, 0.0f, 0.125f, 1.0f);

	// 14. mal nach innen
	avOuter[67] = CHVector(0.015f, 0.0f, 0.135f, 1.0f);

	// 15. mal nach auﬂen
	avOuter[68] = CHVector(0.035f, 0.0f, 0.11f, 1.0f);
	avOuter[69] = CHVector(0.035f, 0.0f, 0.1f, 1.0f);

	// 15. mal nach innen
	avOuter[70] = CHVector(0.025f, 0.0f, 0.1f, 1.0f);

	// Spitze!
	avOuter[71] = CHVector(0.035f, 0.0f, 0.08f, 1.0f);
	avOuter[72] = CHVector(0.0225f, 0.0f, 0.075f, 1.0f);
	avOuter[73] = CHVector(0.02f, 0.0f, 0.06f, 1.0f);
	avOuter[74] = CHVector(0.02f, 0.0f, 0.04f, 1.0f);
	avOuter[75] = CHVector(0.01f, 0.0f, 0.035f, 1.0f);
	avOuter[76] = CHVector(0.01f, 0.0f, 0.05f, 1.0f);
	avOuter[77] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);



	/*for (int i = 0; i < 78; i++)
		m_zgLeafMain.AddOuter(&avOuter[i]);*/

	if (uLoD == 0)
	{
		for (int i = 0; i < 78; i++)
			m_zgLeafMain.AddOuter(&avOuter[i]);
	}
	else if (uLoD == 1)
	{
		for (int i = 0; i < 78; i += 4)
			m_zgLeafMain.AddOuter(&avOuter[i]);
	}
	else if (uLoD == 2)
	{
		for (int i = 0; i < 78; i += 6)
			m_zgLeafMain.AddOuter(&avOuter[i]);
	}
	else if (uLoD == 3)
	{
		for (int i = 0; i < 78; i += 8)
			m_zgLeafMain.AddOuter(&avOuter[i]);
	}

	else if (uLoD > 3)
	{
		m_zgLeafMain.AddOuter(&avOuter[0]);
		m_zgLeafMain.AddOuter(&avOuter[5]);
		m_zgLeafMain.AddOuter(&avOuter[31]);
		m_zgLeafMain.AddOuter(&avOuter[54]);
		m_zgLeafMain.AddOuter(&avOuter[77]);


		/*CHMat mScale;
		mScale.Scale(6.5f*(float)uLoD);
		m_zgLeafMain.Transform(mScale);*/
	}

	SetMaxLeafBending(0.1f);
	SetMaxLeafFolding(0.5f);
	m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.001f);
	SetGeoLeaf(&m_zgLeafMain);

	/*CHMat mScale;
	mScale.Scale(1.5f);
	m_zgLeafMain.Transform(mScale);*/
	if (uLoD > 1) {
		CHMat mScale;
		mScale.Scale(uLoD);
		m_zgLeafMain.Transform(mScale);
		SetLeafSkipFactor(uLoD * 4);
	}
	m_zmLeaf.MakeTextureDiffuse("textures\\japanesefern.png");
	/*m_zmLeaf.MakeTextureBump("textures\\poppyleaf_n.png");
	m_zmLeaf.MakeTextureHeight("textures\\poppyleaf_h.png");
	m_zmLeaf.MakeTextureSpecular("textures\\poppyleaf_o.png");
	m_zmLeaf.SetChromaKeyingOn();*/

	/*CHMat mScaleleaf;
	mScaleleaf.ScaleX(0.05f);
	m_zgLeafMain.Transform(mScaleleaf);*/

	SetMaterialLeaf(&m_zmLeaf);




	//m_zmBark.LoadPreset("BarkChelidoniumMajus");
	m_zmBark.MakeTextureDiffuse("textures\\PoppyBark.png");
	SetMaterial(&m_zmBark);


	SetSwakeRandomFactor(m_fSwakeRandom);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);
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

/*
	if (pzgTemplate->m_pzgRoot && uLoD < 2)
	{
		if (!m_pzgRoot)
			m_pzgRoot = new CGeoLSystem();

		char * acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
		m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

		m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
		m_pzgRoot->SetDefaultFactorGravitation(0.1f);

		m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentl‰nge (Default: 1.0)
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
	*/
}

float GeoBioJapanischerSchildfarn::GetOptimalLoDMin(float fAge, unsigned int uLoD)
{
	float m_fAgeStopped = fAge;
	if (m_fAgeStopped > 1.0f)
		m_fAgeStopped = 1.0f;
	if (m_fAgeStopped < 0.01f)
		m_fAgeStopped = 0.01f;
	if (uLoD == 0)
		return 0.0F;
	return (5.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD - 1);
}

float GeoBioJapanischerSchildfarn::GetOptimalLoDMax(float fAge, unsigned int uLoD)
{
	float m_fAgeStopped = fAge;
	if (m_fAgeStopped > 1.0f)
		m_fAgeStopped = 1.0f;
	if (m_fAgeStopped < 0.01f)
		m_fAgeStopped = 0.01f;
	return (5.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD);
}
