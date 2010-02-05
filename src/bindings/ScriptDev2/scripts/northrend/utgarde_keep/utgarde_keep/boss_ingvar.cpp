/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Ingvar
SD%Complete: 80%
SDComment: Uncorrect Timers; Ressurect Event half; Phase 2 done; Playable;
SDCategory: Utgarde Keep
EndScriptData */

#include "precompiled.h"
#include "utgarde_keep.h"

enum
{
    SAY_AGGRO_FIRST             = -1574005,
    SAY_AGGRO_SECOND            = -1574006,
    SAY_DEATH_FIRST             = -1574007,
    SAY_DEATH_SECOND            = -1574008,
    SAY_KILL_FIRST              = -1574009,
    SAY_KILL_SECOND             = -1574010,
    EMOTE_ROAR                  = -1574022,

    NPC_ANNHYLDE                = 24068,
    NPC_THROW_TARGET            = 23996,                    //the target, casting spell and target of moving dummy
    NPC_THROW_DUMMY             = 23997,                    //the axe, moving to target

    //phase 1
    SPELL_CLEAVE                = 42724,

    SPELL_SMASH                 = 42669,
    SPELL_SMASH_H               = 59706,

    SPELL_ENRAGE                = 42705,
    SPELL_ENRAGE_H              = 59707,

    SPELL_STAGGERING_ROAR       = 42708,
    SPELL_STAGGERING_ROAR_H     = 59708,

    //phase 2]
	SPELL_DARK_SMASH			= 42723,
    SPELL_DARK_SMASH_H          = 59709,

    SPELL_DREADFUL_ROAR         = 42729,
    SPELL_DREADFUL_ROAR_H       = 59734,

    SPELL_WOE_STRIKE            = 42730,
    SPELL_WOE_STRIKE_H          = 59735,

    SPELL_SHADOW_AXE            = 42748,
    SPELL_SHADOW_AXE_PROC       = 42751,
    SPELL_SHADOW_AXE_PROC_H     = 59720,

    //ressurection sequenze
    SPELL_FEIGN_DEATH           = 42795,
    SPELL_TRANSFORM             = 42796,
    SPELL_SCOURGE_RES_SUMMON    = 42863,                    //summones a dummy target
    SPELL_SCOURGE_RES_HEAL      = 42704,                    //heals max HP
    SPELL_SCOURGE_RES_BUBBLE    = 42862,                    //black bubble
    SPELL_SCOURGE_RES_CHANNEL   = 42857                     //the whirl from annhylde
};

/*######
## boss_ingvar
######*/

struct MANGOS_DLL_DECL boss_ingvarAI : public ScriptedAI
{
    boss_ingvarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

	bool Phase1;
	
	uint32 m_uiReviveTimer;
	//Phase1 
    uint32 m_uiCleaveTimer;
    uint32 m_uiSmashTimer;
    uint32 m_uiStaggeringRoarTimer;
    uint32 m_uiEnrageTimer;
	uint32 m_uiRessurectTimer;

	//Phase2
	uint32 m_uiShadowAxeTimer;
	uint32 m_uiDarkSmashTimer;
	uint32 m_uiDreadfulRoarTimer;
	uint32 m_uiWoeStrikeTimer;
	
	uint64 m_uiShadowAxeGUID;
	
    void Reset()
    {
        m_uiCleaveTimer = urand(5000, 7000);
        m_uiSmashTimer = urand(8000, 15000);
        m_uiStaggeringRoarTimer = urand(10000, 25000);
        m_uiEnrageTimer = 30000;
		m_uiShadowAxeTimer = 35000;           //zeby sie nie odpalilo po wipie
		m_uiDreadfulRoarTimer = 25000;		 //	
		m_uiWoeStrikeTimer = 25000;			//
		m_uiDarkSmashTimer = 25000;		   //
		m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		Phase1=true;	
    }
	

    void Aggro(Unit* pWho)
    {
		DoScriptText(SAY_AGGRO_FIRST,m_creature);
    }

	void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
		if(Phase1 && uiDamage >= m_creature->GetHealth())
		{
			uiDamage = m_creature->GetHealth() -1;
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			m_creature->RemoveAllAuras();
			DoScriptText(SAY_DEATH_FIRST, m_creature);
			DoCast(m_creature,SPELL_FEIGN_DEATH);
			m_uiRessurectTimer = 10000;
			Phase1 = false;
			return;
		}
		if(!Phase1)
		{
			return;
		}

	}

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH_SECOND, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (urand(0, 1))
            DoScriptText(!Phase1 ? SAY_KILL_SECOND : SAY_KILL_FIRST, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
		
      if (Phase1)
        {
            if (m_uiCleaveTimer < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                m_uiCleaveTimer = urand(2500, 7000);
            }
            else
                m_uiCleaveTimer -= uiDiff;

            if (m_uiSmashTimer < uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_SMASH : SPELL_SMASH_H, true);
                m_uiSmashTimer = urand(8000, 15000);
            }
            else
                m_uiSmashTimer -= uiDiff;

            if (m_uiStaggeringRoarTimer < uiDiff)
            {
                DoScriptText(EMOTE_ROAR, m_creature);
                DoCast(m_creature, m_bIsRegularMode ? SPELL_STAGGERING_ROAR : SPELL_STAGGERING_ROAR_H, true);
                m_uiStaggeringRoarTimer = urand(15000, 30000);
            }
            else
                m_uiStaggeringRoarTimer -= uiDiff;

            if (m_uiEnrageTimer < uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : SPELL_ENRAGE_H);
                m_uiEnrageTimer = urand(10000, 20000);
            }
            else
                m_uiEnrageTimer -= uiDiff;

		}
		
		
		if(Phase1 == false)
		{
			if(m_uiRessurectTimer < uiDiff)
			{
				DoCast(m_creature,SPELL_TRANSFORM,false);
				m_creature->SetHealth(m_creature->GetMaxHealth());
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				DoScriptText(SAY_AGGRO_SECOND,m_creature);
				
				m_uiShadowAxeTimer = 35000;
				m_uiDarkSmashTimer = 5000;
				m_uiDreadfulRoarTimer = urand(5000, 10000);
				m_uiWoeStrikeTimer = 15000;
					
				if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->GetMotionMaster()->MoveChase(pTarget);
				
				m_uiRessurectTimer = 9000000;
			}
			else
				m_uiRessurectTimer -= uiDiff;


			if (m_uiDarkSmashTimer < uiDiff)
			{
				if((m_uiShadowAxeTimer<25000))
				{
					DoCast(m_creature, m_bIsRegularMode ? SPELL_DARK_SMASH : SPELL_DARK_SMASH_H);
					m_uiDarkSmashTimer = urand(10000,20000);
				}
				else
					m_uiDarkSmashTimer = 38000 - m_uiShadowAxeTimer; // Czyli castowanie 3 sec po zniknieciu shadowaxe'a
			}
			else
				m_uiDarkSmashTimer -=uiDiff;

			if(m_uiWoeStrikeTimer < uiDiff)
			{	
				if(m_uiShadowAxeTimer<25000)
				{
					DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_WOE_STRIKE : SPELL_WOE_STRIKE_H);
					m_uiWoeStrikeTimer = urand(5000,15000);
				}
				else
					m_uiWoeStrikeTimer = 40000 - m_uiShadowAxeTimer; // 5 sec po zakonczeniu shadowaxe'a
			}
			else
				m_uiWoeStrikeTimer -= uiDiff;

			if (m_uiDreadfulRoarTimer < uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_DREADFUL_ROAR : SPELL_DREADFUL_ROAR_H);
                m_uiDreadfulRoarTimer = urand(10000, 20000);
            }
            else
                m_uiDreadfulRoarTimer -= uiDiff;
			
			if (m_uiShadowAxeTimer < uiDiff)
			{
				if (Unit* pAxeTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
				{
				
					float fPosX, fPosY, fPosZ;
					pAxeTarget->GetPosition(fPosX, fPosY, fPosZ);

					m_creature->SummonCreature(NPC_THROW_DUMMY, fPosX, fPosY, fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
			
				}

				m_uiShadowAxeTimer = 35000;
			}
			else
				m_uiShadowAxeTimer -= uiDiff;
		}

		DoMeleeAttackIfReady();
	}
};
	
CreatureAI* GetAI_boss_ingvar(Creature* pCreature)
{
    return new boss_ingvarAI(pCreature);
}

/*######
## shadow_axe
######*/
struct MANGOS_DLL_DECL shadow_axeAI : public Scripted_NoMovementAI
{
    shadow_axeAI(Creature *c) : Scripted_NoMovementAI(c)
    {
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
        m_bIsRegularMode = c->GetMap()->IsRegularDifficulty();
        Reset();
    }

	ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

	uint32 m_uiShadowAxeProcTimer;

	void Reset()
	{
		m_uiShadowAxeProcTimer = 1000;
		m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (m_uiShadowAxeProcTimer < uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_SHADOW_AXE_PROC : SPELL_SHADOW_AXE_PROC_H);
                m_uiShadowAxeProcTimer = 2000;
            }
            else
                m_uiShadowAxeProcTimer -= uiDiff;
	}

};
CreatureAI* GetAI_shadow_axe(Creature *_Creature)
{
    return new shadow_axeAI(_Creature);
}
/*######
## npc_annhylde
######*/
struct MANGOS_DLL_DECL npc_annhyldeAI : public ScriptedAI
{
    npc_annhyldeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
    }
};

CreatureAI* GetAI_npc_annhylde(Creature* pCreature)
{
    return new npc_annhyldeAI(pCreature);
}

void AddSC_boss_ingvar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_ingvar";
    newscript->GetAI = &GetAI_boss_ingvar;
    newscript->RegisterSelf();
	
	newscript = new Script;
    newscript->Name = "shadow_axe";
    newscript->GetAI = &GetAI_shadow_axe;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_annhylde";
    newscript->GetAI = &GetAI_npc_annhylde;
    newscript->RegisterSelf();
}