#include "CherryBlossomTree.h"

using namespace ForestNS;

CherryBlossomTree::CherryBlossomTree()
{

}

CherryBlossomTree::~CherryBlossomTree()
{


}

void CherryBlossomTree::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD)
{
	m_fAge = fAge;
	m_frTimeOfYear = frTimeOfYear;
	m_fRootCutHeight = fRootCutHeight;

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;
	// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

	if (frTimeShifted > 0.1f && frTimeShifted < 0.9f) // Außerhalb Februar bis November
		m_bHasLeaves = true;

	if (isLoD == false)
	{
		m_bHasLeaves = false;
		m_bIsHitbox = true;
	}

	if (frTimeShifted > 0.249f && frTimeShifted < 0.499f) // Im Frühling (Frühlingstagungnachtgleiche - Sommersonnwende)
		m_bIsBlossoming = true;

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
		m_fTurtleStartLength = 0.9f + (m_fAgeStopped - 50.0f) / 150.0f*0.5f;
		m_fTurtleStartRadius = 0.6f + (m_fAgeStopped - 50.0f) / 150.0f*0.4f;
		m_fSwakeRandom = 0.01f;
	}
	else if (m_fAgeStopped > 20.0f)
	{
		m_iIterations = 13;
		m_iTurtleStartLongitude = 22;
		m_iTurtleStartLattitude = 22;
		m_fTurtleStartLength = 0.7f + (m_fAgeStopped - 20.0f) / 30.0f*0.5f;
		m_fTurtleStartRadius = 0.4f + (m_fAgeStopped - 20.0f) / 30.0f*0.2f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 10.0f)
	{
		m_iIterations = 12;
		m_iTurtleStartLongitude = 18;
		m_iTurtleStartLattitude = 18;
		m_fTurtleStartLength = 0.5f + (m_fAgeStopped - 10.0f) / 10.0f*0.5f;
		m_fTurtleStartRadius = 0.3f + (m_fAgeStopped - 10.0f) / 10.0f*0.1f;
		m_fSwakeRandom = 0.005f;
	}
	else if (m_fAgeStopped > 5.0f)
	{
		m_iIterations = 11;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.3f + (m_fAgeStopped - 5.0f) / 5.0f*0.2f;
		m_fTurtleStartRadius = 0.15f + (m_fAgeStopped - 5.0f) / 5.0f*0.05f;
		m_fSwakeRandom = 0.002f;
	}
	else if (m_fAgeStopped > 2.0f)
	{
		m_iIterations = 10;
		m_iTurtleStartLongitude = 12;
		m_iTurtleStartLattitude = 10;
		m_fTurtleStartLength = 0.15f + (m_fAgeStopped - 2.0f) / 3.0f*0.3f;
		m_fTurtleStartRadius = 0.12f + (m_fAgeStopped - 2.0f) / 3.0f*0.03f;
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

	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
	SetDefaultFactorGravitation(0.001f);

	SetSwakeRandomFactor(m_fSwakeRandom);
	SetTurtleStartHeight(m_fTurtleStartLength);
	SetTurtleStartRadius(m_fTurtleStartRadius);
	//------------------------
	// Erzeuge Stamm und Geäst:
	//------------------------


	if (m_bHasLeaves)
	{
		SetAxiom("K");
		AddRule("17:K={r>0.8,(r0.8)_(^24)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(>25)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(<22)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(<22)(l0.93)fK}{r<0.801,X}");
		AddRule("32:K=°{r>0.8,(r0.8)(l0.93)fK}{r<0.801,X}");


		AddRule("35:X={r>0.004,°+(l0.93)(r0.95)__(>19)f(r0.95)__(>19)f[(l0.9)(<14)(r0.9)X][(l0.95)(r0.5)(>15)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(l0.93)(r0.95)__(<15)f(r0.95)__(<13)f[(l0.85)(r0.8)__(^15)f(^17)X][(l0.89)(v12)(r0.8)__f(r0.8)f(v10)(r0.8)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(l0.93)(r0.95)__(v12)f(r0.95)__(v12)f[(l0.97)(r0.8)(<15)(^15)(v8)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(r0.95)__(>13)f[(l0.97)(^10)(r0.92)X][(l0.52)(r0.5)(<17)X]}{r<0.0041,Y}");
		AddRule("10:X={r>0.004,+(r0.95)__(^15)f[(l0.85)(r0.8)__(^15)f(^17)X][(l0.89)__(v12)(r0.8)f(r0.8)_f(v10)(r0.8)X]}{r<0.0041,Y}");
		AddRule("10:X={r>0.004,+(r0.95)__(<11)f[(l0.97)(<10)(r0.92)X][(l0.52)(r0.5)(^13)X]}{r<0.0041,Y}");



		// Ist in Blütezeit? 
		if (m_bIsBlossoming) {
			// Äste mit Blüten zeichnen
			AddRule("Y={r>0.003,(l0.7)(r0.9)__+f[__(<54)fB]__+f[__(>54)fB]_+f[__(v54)fB]_+f[__(^54)fB]fY}{r<0.0031,}");
			// Blüten zeichnen 
			AddRule("B=(L0.05)(R0.05)[<0b][^0b][>0b][v0b](r0.5)(l0.7)[(<20.2)0c][(^18.4)0c][(>20.4)0c][(v22.4)0c](+40.0)[(<10.2)0c][(^11.4)0c][(>14.4)0c][(v12.4)0c]");
		}
		else {
			// Äste mit Blättern zeichnen

			AddRule("Y={r>0.003,(l0.7)(r0.9)_+f[(<54)B]_+f[(>54)B]_+f[(v54)B]_+f[(^54)B]_fY}{r<0.0031,}");
			AddRule("B=(L0.5)(R0.5)[^0l]");
		}


	}
	else
	{
		SetAxiom("K");
		AddRule("17:K={r>0.8,(r0.8)_(^24)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(>25)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(<22)(l0.93)fK}{r<0.801,X}");
		AddRule("17:K={r>0.8,(r0.8)_(<22)(l0.93)fK}{r<0.801,X}");
		AddRule("32:K=°{r>0.8,(r0.8)(l0.93)fK}{r<0.801,X}");


		AddRule("35:X={r>0.004,°+(l0.93)(r0.95)_(>19)f(r0.95)_(>19)f[(l0.9)(<14)(r0.9)X][(l0.95)(r0.5)(>15)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(l0.93)(r0.95)_(<15)f(r0.95)_(<13)f[(l0.85)(r0.8)__(^15)f(^17)X][(l0.89)(v12)(r0.8)__f(r0.8)f(v10)(r0.8)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(l0.93)(r0.95)_(v12)f(r0.95)_(v12)f[(l0.97)(r0.8)(<15)(^15)(v8)X]}{r<0.0041,Y}");
		AddRule("15:X={r>0.004,+(r0.95)_(>13)f[(l0.97)(^10)(r0.92)X][(l0.52)(r0.5)(<17)X]}{r<0.0041,Y}");
		AddRule("10:X={r>0.004,+(r0.95)_(^15)f[(l0.85)(r0.8)_(^15)f(^17)X][(l0.89)__(v12)(r0.8)f(r0.8)_f(v10)(r0.8)X]}{r<0.0041,Y}");
		AddRule("10:X={r>0.004,+(r0.95)_(<11)f[(l0.97)(<10)(r0.92)X][(l0.52)(r0.5)(^13)X]}{r<0.0041,Y}");
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

void CherryBlossomTree::DeIterate()
{
	((CGeoLSystem*)this)->DeIterate();
	if (m_pzgRoot)
		m_pzgRoot->DeIterate();
}

void CherryBlossomTree::Init(IPlantGeo * pzgTemplate, unsigned int uLoD)
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

	if (m_bHasLeaves)
	{
		m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
		if (uLoD == 0)
		{
			CHVector avOuter[11];

			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.02f, 0.0f, 0.79f, 1.0f);

			//Rest:
			avOuter[3] = CHVector(0.13f, 0.0f, 0.63f, 1.0f);
			avOuter[4] = CHVector(0.175f, 0.0f, 0.44f, 1.0f);
			avOuter[5] = CHVector(0.175f, 0.0f, 0.39f, 1.0f);
			avOuter[6] = CHVector(0.155f, 0.0f, 0.32f, 1.0f);
			avOuter[7] = CHVector(0.08f, 0.0f, 0.18f, 1.0f);
			avOuter[8] = CHVector(0.04f, 0.0f, 0.14f, 1.0f);
			avOuter[9] = CHVector(0.025f, 0.0f, 0.06f, 1.0f);
			avOuter[10] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);




			for (int i = 0; i < 11; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);

			SetMaxLeafBending(0.02f);
			SetMaxLeafFolding(0.02f);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.00001f);
			SetGeoLeaf(&m_zgLeafMain);

			/*CHMat scaling;
			scaling.Scale(2.0f);
			m_zgLeafMain.Transform(scaling);*/


		}
		else if (uLoD <= 2)
		{
			CHVector avOuter[15];

			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.90f, 1.0f);

			//Ausbuchtung:
			avOuter[3] = CHVector(0.04f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.15f, 0.0f, 0.85f, 1.0f);
			avOuter[5] = CHVector(0.3f, 0.0f, 0.8f, 1.0f);
			avOuter[6] = CHVector(0.4f, 0.0f, 0.7f, 1.0f);
			avOuter[7] = CHVector(0.45f, 0.0f, 0.6f, 1.0f);
			avOuter[8] = CHVector(0.48f, 0.0f, 0.5f, 1.0f);
			avOuter[9] = CHVector(0.45f, 0.0f, 0.4f, 1.0f);
			avOuter[10] = CHVector(0.38f, 0.0f, 0.3f, 1.0f);
			avOuter[11] = CHVector(0.27f, 0.0f, 0.2f, 1.0f);
			avOuter[12] = CHVector(0.12f, 0.0f, 0.12f, 1.0f);
			avOuter[13] = CHVector(0.02f, 0.0f, 0.05f, 1.0f);
			avOuter[14] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

			for (int i = 0; i < 15; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);

			SetMaxLeafBending(0.02f);
			SetMaxLeafFolding(0.02f);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.001f);

			CHMat mScale;
			mScale.Scale(2.0f);
			m_zgLeafMain.Transform(mScale);
			SetLeafSkipFactor(4);

			SetGeoLeaf(&m_zgLeafMain);

		}
		else
		{
			CHVector avOuter[5];

			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.5f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.5f, 0.0f, 0.5f, 1.0f);
			avOuter[3] = CHVector(0.5f, 0.0f, 0.0f, 1.0f);
			avOuter[4] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 5; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);


			SetMaxLeafBending(0.02f);
			SetMaxLeafFolding(0.02f);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.001f);

			CHMat mScale;
			mScale.Scale((float)uLoD*1.5f);
			m_zgLeafMain.Transform(mScale);
			SetLeafSkipFactor(uLoD * 4);

			SetGeoLeaf(&m_zgLeafMain);


		}

		// 0.0f Dez/Jan, 0.25 März/April, 0.5 Jun/Jul, 0.75 Sep/Okt
		float fLeafScaling = 0.0f;
		if (frTimeShifted >= 0.1f && frTimeShifted <= 0.8f) // Von Februar bis November
			fLeafScaling = 1.6f*(frTimeShifted - 0.1f) / 0.7f;

		CHMat mScale;
		mScale.Scale(fLeafScaling);
		m_zgLeafMain.Transform(mScale);

		m_zmLeaf.MakeTextureDiffuse("textures\\RosebloomRealLeaf.png");
		m_zmLeaf.MakeTextureBump("textures\\RosebloomRealLeaf_n.png");
		m_zmLeaf.MakeTextureHeight("textures\\RosebloomRealLeaf_h.png");
		m_zmLeaf.MakeTextureSpecular("textures\\RosebloomRealLeaf_s.png");

		m_zmLeaf.SetSpecularStrength(0.01f);

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

		// Blütenblatt
		if (m_bIsBlossoming) {
			if (uLoD == 0) {

				m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
				CHVector avOuter[11];
				avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
				avOuter[1] = CHVector(0.03f, 0.0f, 0.99f, 1.0f);
				avOuter[2] = CHVector(0.1f, 0.0f, 0.89f, 1.0f);
				avOuter[3] = CHVector(0.195f, 0.0f, 0.77f, 1.0f);
				avOuter[4] = CHVector(0.26f, 0.0f, 0.65f, 1.0f);
				avOuter[5] = CHVector(0.32f, 0.0f, 0.49f, 1.0f);
				avOuter[6] = CHVector(0.325f, 0.0f, 0.35f, 1.0f);
				avOuter[7] = CHVector(0.3f, 0.0f, 0.29f, 1.0f);
				avOuter[8] = CHVector(0.205f, 0.0f, 0.055f, 1.0f);
				avOuter[9] = CHVector(0.1f, 0.0f, 0.005f, 1.0f);
				avOuter[10] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);



				for (int i = 0; i < 11; i++)
					m_zgBlossomMain.AddOuter(&avOuter[i]);
				SetMaxBlossomBending(-0.01f);
				SetMaxBlossomFolding(0.01f);

				m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.00001f);
				SetGeoBlossom(&m_zgBlossomMain);
				CHMat blossomscaling;
				//blossomscaling.Scale(2.0f);
				blossomscaling.Scale(4.0f);

				m_zgBlossomMain.Transform(blossomscaling);


				SetBlossomSkipFactor(4);


			}
			else if (uLoD < 2) {
				m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
				CHVector avOuter[6];
				avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
				avOuter[1] = CHVector(0.03f, 0.0f, 0.99f, 1.0f);
				avOuter[2] = CHVector(0.26f, 0.0f, 0.65f, 1.0f);
				avOuter[3] = CHVector(0.3f, 0.0f, 0.29f, 1.0f);
				avOuter[4] = CHVector(0.205f, 0.0f, 0.055f, 1.0f);
				avOuter[5] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);



				for (int i = 0; i < 6; i++)
					m_zgBlossomMain.AddOuter(&avOuter[i]);
				SetMaxBlossomBending(-0.01f);
				SetMaxBlossomFolding(0.01f);

				m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.002f);
				SetGeoBlossom(&m_zgBlossomMain);
				CHMat blossomscaling;

				blossomscaling.Scale(6.0f);

				m_zgBlossomMain.Transform(blossomscaling);


				SetBlossomSkipFactor(6);
			}
			else
			{
				m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
				CHVector avOuter[6];
				avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
				avOuter[1] = CHVector(0.03f, 0.0f, 0.99f, 1.0f);
				avOuter[2] = CHVector(0.26f, 0.0f, 0.65f, 1.0f);
				avOuter[3] = CHVector(0.3f, 0.0f, 0.29f, 1.0f);
				avOuter[4] = CHVector(0.205f, 0.0f, 0.055f, 1.0f);
				avOuter[5] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);



				for (int i = 0; i < 6; i++)
					m_zgBlossomMain.AddOuter(&avOuter[i]);
				SetMaxBlossomBending(-0.01f);
				SetMaxBlossomFolding(0.01f);

				m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.002f);
				SetGeoBlossom(&m_zgBlossomMain);

				CHMat blossomscaling;
				blossomscaling.Scale((float)uLoD * 3.5);
				m_zgBlossomMain.Transform(blossomscaling);

				SetBlossomSkipFactor(uLoD * 3);

			}

			// Zufälliges Hellermachen der Textur
			/*CRandom Colorscaling;
			m_zmBlossom.ScaleDelta(0.5f + Colorscaling.RandFr());*/

			/*CHMat blossomscaling;
			blossomscaling.Scale(2.5f);
			m_zgBlossomMain.Transform(blossomscaling);*/

			// Stamen

			m_zgStamenMain.SetMiddle(CHVector(0.0f, 0.0f, 0.9f, 1.0f));
			if (uLoD == 0)
			{
				CHVector avOuter[7];
				//Stiel:
				avOuter[0] = CHVector(0.00f, 0.0f, 1.0f, 1.0f);
				avOuter[1] = CHVector(0.03f, 0.0f, 1.0f, 1.0f);
				avOuter[2] = CHVector(0.03f, 0.0f, 0.2f, 1.0f);

				//Staubstempel:
				avOuter[3] = CHVector(0.20f, 0.0f, 0.18f, 1.0f);
				avOuter[4] = CHVector(0.20f, 0.0f, 0.02f, 1.0f);
				avOuter[5] = CHVector(0.07f, 0.0f, 0.00f, 1.0f);
				avOuter[6] = CHVector(0.00f, 0.0f, 0.00f, 1.0f);

				for (int i = 0; i < 7; i++)
					m_zgStamenMain.AddOuter(&avOuter[i]);

				m_zgStamenMain.Init(&m_zmBlossom, true, true, -0.0f, 0.0f, 0.0f);
				// m_zgBlossomMain.SetAngleUp(0.4f);
				SetGeoStamen(&m_zgStamenMain);
			}




		}

		m_zmBlossom.MakeTextureDiffuse("textures\\roseblossomfrontback.png");
		m_zmBlossom.MakeTextureSpecular("textures\\roseblossomfrontback_o.png");
		m_zmBlossom.MakeTextureHeight("textures\\roseblossomfrontback_h.png");
		m_zmBlossom.MakeTextureBump("textures\\roseblossomfrontback_n.png");

		m_zmBlossom.SetSpecularStrength(0.2f);
		m_zgBlossomMain.SetMaterial(&m_zmBlossom);
	}
	//m_zmBark.LoadPreset("BarkBirch");
	m_zmBark.MakeTextureDiffuse("textures\\Bark_09_3K_Base_Color.png");
	m_zmBark.MakeTextureBump("textures\\Bark_09_3K_Normal.png");
	m_zmBark.MakeTextureHeight("textures\\Bark_09_3K_Height.png");
	m_zmBark.MakeTextureSpecular("textures\\Bark_09_3K_Roughness.png");

	SetMaterial(&m_zmBark);
	m_zmBark.SetDisplacementOn();
	m_zmBark.SetDisplacementStrength(0.03f);

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
	if (m_bIsHitbox == true) {
		m_iTurtleStartLattitude = 4;
		m_iTurtleStartLongitude = 8;
	}
	if (m_iTurtleStartLattitude == 1)
		m_iTurtleStartLattitude = 2;
	if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
		m_iTurtleStartLattitude = 2;
	SetTurtleStartLongitude(m_iTurtleStartLongitude);
	SetTurtleStartLattitude(m_iTurtleStartLattitude);

	Interprete(acTurtleOrdersMain);

	//// ---------------
	//// Erzeuge Wurzel:
	//// ---------------


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
		//		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, 2.5f, 0.0f, 1.0f));

		m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
		m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
		m_pzgRoot->SetSwakeRandomFactor(m_fSwakeRandom);
		m_pzgRoot->SetTurtleStartRadius(m_fTurtleStartRadius);
		m_pzgRoot->SetTurtleStartHeight(m_fTurtleStartLength*2.0f);
		m_pzgRoot->SetTurtleStartLongitude(m_iTurtleStartLongitude);
		m_pzgRoot->SetTurtleStartLattitude(m_iTurtleStartLattitude);

		m_pzgRoot->Interprete(acTurtleOrdersRoot);

		AddGeo(m_pzgRoot);
	}
}

float CherryBlossomTree::GetOptimalLoDMin(float fAge, unsigned int uLoD)
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

float CherryBlossomTree::GetOptimalLoDMax(float fAge, unsigned int uLoD)
{
	float m_fAgeStopped = fAge;
	if (m_fAgeStopped > 500.0f)
		m_fAgeStopped = 500.f;
	if (m_fAgeStopped < 2.1f)
		m_fAgeStopped = 2.1f;
	return (40.f + m_fAgeStopped * 0.5f) * powf(4.0f, uLoD);
}



