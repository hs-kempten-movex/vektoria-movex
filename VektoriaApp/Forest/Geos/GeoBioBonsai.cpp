#include "GeoBioBonsai.h"

namespace Vektoria
{
	CGeoBioBonsai::CGeoBioBonsai()
	{
	}

	CGeoBioBonsai::~CGeoBioBonsai()
	{
	}

	void CGeoBioBonsai::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
		{
			m_fAge = fAge;
			m_fAgeStopped = fAge;
			m_fRootCutHeight = fRootCutHeight;
			m_frTimeOfYear = frTimeOfYear;

			float frTimeShifted = m_frTimeOfYear + 0.25f;
			if (frTimeShifted > 1.0f)
				frTimeShifted -= 1.0f;
			// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

			if (frTimeShifted > 0.1f && frTimeShifted < 0.9f) // Außerhalb Februar bis November
				m_bHasLeaves = true;


			if (m_fAgeStopped > 200.0f)
				m_fAgeStopped = 200.0f;
			if (m_fAgeStopped < 1.0f)
				m_fAgeStopped = 1.0f;

			if (m_fAgeStopped > 50.0f)
			{
				m_iIterations = 14;
				m_iTurtleStartLongitude = 26;
				m_iTurtleStartLattitude = 26;
				m_fTurtleStartLength = 2.0f + (m_fAge - 50.0f) / 150.0f * 0.5f;
				m_fTurtleStartRadius = 0.4f + (m_fAge - 50.0f) / 150.0f * 0.4f;
				m_fSwakeRandom = 0.01f;
			}
			else if (m_fAgeStopped > 20.0f)
			{
				m_iIterations = 13;
				m_iTurtleStartLongitude = 22;
				m_iTurtleStartLattitude = 22;
				m_fTurtleStartLength = 1.5f + (m_fAge - 20.0f) / 30.0f * 0.5f;
				m_fTurtleStartRadius = 0.2f + (m_fAge - 20.0f) / 30.0f * 0.2f;
				m_fSwakeRandom = 0.005f;
			}
			else if (m_fAgeStopped > 10.0f)
			{
				m_iIterations = 12;
				m_iTurtleStartLongitude = 18;
				m_iTurtleStartLattitude = 18;
				m_fTurtleStartLength = 1.0f + (m_fAge - 10.0f) / 10.0f * 0.5f;
				m_fTurtleStartRadius = 0.1f + (m_fAge - 10.0f) / 10.0f * 0.1f;
				m_fSwakeRandom = 0.005f;
			}
			else if (m_fAgeStopped > 5.0f)
			{
				m_iIterations = 11;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 10;
				m_fTurtleStartLength = 0.8f + (m_fAge - 5.0f) / 5.0f * 0.2f;
				m_fTurtleStartRadius = 0.05f + (m_fAge - 5.0f) / 5.0f * 0.05f;
				m_fSwakeRandom = 0.002f;
			}
			else if (m_fAgeStopped > 2.0f)
			{
				m_iIterations = 10;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 10;
				m_fTurtleStartLength = 0.5f + (m_fAge - 2.0f) / 3.0f * 0.3f;
				m_fTurtleStartRadius = 0.02f + (m_fAge - 2.0f) / 3.0f * 0.03f;
				m_fSwakeRandom = 0.001f;
			}
			else if (m_fAgeStopped > 1.0f)
			{
				m_iIterations = 9;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 6;
				m_fTurtleStartLength = 0.3f + (m_fAge - 1.0f) / 1.0f * 0.2f;
				m_fTurtleStartRadius = 0.01f + (m_fAge - 1.0f) / 1.0f * 0.01f;
				m_fSwakeRandom = 0.0005f;
			}
			else
			{
				m_iIterations = 8;
				m_iTurtleStartLongitude = 12;
				m_iTurtleStartLattitude = 5;
				m_fTurtleStartLength = m_fAge * 0.3f;
				m_fTurtleStartRadius = m_fAge * 0.01f;
				m_fSwakeRandom = 0.0005f;
			}

			SetSwakeRandomFactor(m_fSwakeRandom);
			SetTurtleStartHeight(m_fTurtleStartLength);
			SetTurtleStartRadius(m_fTurtleStartRadius);


			// Stamm und Äste
			if (m_bHasLeaves)
			{
				
				// Stamm

				SetAxiom("A");
				AddRule("20:A={r>0.05,+(r0.95)_(>20)f[(l0.85)(<10)(r0.93)A]}");
				AddRule("20:A={r>0.05,+(r0.94)_(<18)f[(l0.93)(>15)(r0.94)A]}");
				AddRule("20:A={r>0.05,+(r0.9)_(<12)f[(l0.90)(>15)(r0.96)A]}");
				AddRule("20:A={r>0.05,°+(r0.97)_(v8)f[(l0.96)(^15)(r0.92)A]}");
				AddRule("20:A={r>0.05,+(r0.98)_(^15)f[(l0.82)(v15)(r0.97)A]{b>0,B}}");
				
				// Äste mit Baumkrone

				AddRule("50:B=(l1.5)(r0.7)(<55)f(l0.7)(<35)f(r0.8)(l0.2)(>75)f(<10)(l0.1)&f(^45)(L0.5)(R0.5)a");
				AddRule("50:B=(l1.4)(r0.5)(>40)f(l0.6)(<10)f(r0.6)(l0.4)(<5)f(^10)(l0.5)f(<90)&f(^75)f(R0.4)(L0.4)a");
				//AddRule("25:Y=(l1.5)(r0.4)(<30)f(>60)(l0.1)f(<10)(l0.1)f(^45)(l3.0)(r6.0)a");
				//AddRule("25:Y=(r0.5)(v20)f(<5)(l1.1)(r0.6)f[(l0.9)(^60)(r0.8)f(>7)(l0.4)(r0.8)f(v30)(l0.1)f][(l0.8)(v51)(r0.7)f(<10)(l0.1)f(^45)(l10.0)(r15.0)a");
			}
			else
			{
				//Stamm

				SetAxiom("A");
				AddRule("20:A={r>0.05,+(r0.95)_(>20)f[(l0.85)(<10)(r0.93)A]}");
				AddRule("20:A={r>0.05,+(r0.94)_(<18)f[(l0.93)(>15)(r0.94)A]}");
				AddRule("20:A={r>0.05,+(r0.9)_(<12)f[(l0.90)(>15)(r0.96)A]}");
				AddRule("20:A={r>0.05,°+(r0.97)_(v8)f[(l0.96)(^15)(r0.92)A]}");
				AddRule("20:A={r>0.05,+(r0.98)_(^15)f[(l0.82)(v15)(r0.97)A]{b>0,B}}");

				// Äste ohne Baumkrone

				AddRule("50:B=(l1.5)(r0.7)(<55)f(l0.7)(<35)f(r0.8)(l0.2)(>75)f(<10)(l0.1)&f(^45)(L0.5)(R0.5)a");
				AddRule("50:B=(l1.4)(r0.5)(>40)f(l0.6)(<10)f(r0.6)(l0.4)(<5)f(^10)(l0.5)f(<90)&f(^75)f(R0.4)(L0.4)a");
				//AddRule("25:Y=(l1.5)(r0.4)(<30)f(>60)(l0.1)f(<10)(l0.1)f(^45)(l3.0)(r6.0)a");
				//AddRule("25:Y=(r0.5)(v20)f(<5)(l1.1)(r0.6)f[(l0.9)(^60)(r0.8)f(>7)(l0.4)(r0.8)f(v30)(l0.1)f][(l0.8)(v51)(r0.7)f(<10)(l0.1)f(^45)(l10.0)(r15.0)a");
			}


			m_iIterations += 23;
			CGeoLSystem::Iterate(m_iIterations, m_acAxiom);
			m_iIterations -= 23;

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
	

	void CGeoBioBonsai::Init(CGeoBioBonsai* pzgTemplate, unsigned int uLoD)
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

		char* acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

		if (!acTurtleOrdersMain)
		{
			return;
		}

		float frTimeShifted = m_frTimeOfYear + 0.25f;
		if (frTimeShifted > 1.0f)
			frTimeShifted -= 1.0f;
		// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.
		
		if (m_bHasLeaves)
		{
			if (uLoD <= 1)
			{
				m_zgBush = m_zfwv.LoadGeoTriangleTable("models/kronelod0.obj", true);
			}
			else if (uLoD == 2)
			{
				m_zgBush = m_zfwv.LoadGeoTriangleTable("models/kronelod2.obj", true);
			}
			else
			{
				m_zgBush = m_zfwv.LoadGeoTriangleTable("models/kronelodelse.obj", true);
			}


			SetGeoFruit(m_zgBush);
			CHMat m;
			m.Translate(0, -2, 0);
			m_zgBush->Transform(m);
			m_zmBush.MakeTextureDiffuse("textures/green.png");
			m_zgBush->SetMaterial(&m_zmBush);
		}


		m_zmBark.LoadPreset("BarkBirch");
		SetMaterial(&m_zmBark);

		SetSwakeRandomFactor(m_fSwakeRandom);
		SetTurtleStartHeight(m_fTurtleStartLength);
		SetTurtleStartRadius(m_fTurtleStartRadius);


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
		if (m_iTurtleStartLattitude == 1)
			m_iTurtleStartLattitude = 2;
		if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
			m_iTurtleStartLattitude = 2;
		SetTurtleStartLongitude(m_iTurtleStartLongitude);
		SetTurtleStartLattitude(m_iTurtleStartLattitude);

		Interprete(acTurtleOrdersMain);

		if (pzgTemplate->m_pzgRoot && uLoD < 2)
		{
			if (!m_pzgRoot)
				m_pzgRoot = new CGeoLSystem();

			char* acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
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
	void CGeoBioBonsai::DeIterate()
	{
		((CGeoLSystem*)this)->DeIterate();
	}
}