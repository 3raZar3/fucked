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
SDName: Boss_Trollgore
SD%Complete: 80%
SDAuthor: Aramil
SDComment: Spell Corpse Explode doesn't work properly. There is 10% chance that Drakari Bodies after dead will Explode.
SDCategory: Drak'Tharon Keep
EndScriptData */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    SAY_AGGRO                       = -1600000,
    SAY_CONSUME                     = -1600001,
    SAY_DEATH                       = -1600002,
    SAY_EXPLODE                     = -1600003,
    SAY_KILL                        = -1600004,

	SPELL_CRUSH						= 49639,
	SPELL_INFECTEDWOUND				= 49637,
	SPELL_CORPSEEXLODE				= 49555, // normal mode dmg 3770 - 4230 
	SPELL_CORPSEEXLODE_H			= 59809, // heroic mode dmg 9425 - 10575 
	SPELL_CONSUME					= 49380, // normal mode dmg 1885 - 2115 
	SPELL_CONSUME_H					= 59803, // normal mode dmg 4713 - 5287  	
	
	NPC_DRAKARI						= 27709
};

/*######
## boss_trollgore
######*/

struct MANGOS_DLL_DECL boss_trollgoreAI : public ScriptedAI
{
    boss_trollgoreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bIsRegularMode;

	uint32 Timer_Crush;
	uint32 Timer_Infected;
	uint32 Timer_Consume;
	uint32 Timer_Consume_H;	
	uint32 Timer_SummonWave;
	
    void Reset()
    {
		Timer_Crush = 10000 + rand()%60 * 5000;
		Timer_Infected = 25000 + rand()%60 * 5000;
		Timer_Consume = 15000;
		Timer_SummonWave = 30000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetCharmerOrOwnerPlayerOrPlayerItself())
            DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
		
		Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 1);
            if(!target)
                target = m_creature->getVictim();	
				
		if (Timer_Crush < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_CRUSH);
                Timer_Crush = urand(15000, 20000);
            }	Timer_Crush -= uiDiff;
			
		if (Timer_Infected < uiDiff)
            {
                DoCast(target, SPELL_INFECTEDWOUND);
                Timer_Infected = urand(18000, 35000);
            }	Timer_Infected -= uiDiff;
			
		if (Timer_Consume < uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_CONSUME : SPELL_CONSUME_H);
                Timer_Consume = urand(5000, 25000);
            }	Timer_Consume -= uiDiff;
			

		if (Timer_SummonWave < uiDiff)
            {

				for (uint8 i=0; i<3; ++i)
					m_creature->SummonCreature(NPC_DRAKARI, -299+rand()%7, -695+rand()%7, 1, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                Timer_SummonWave = 30000;
            }	Timer_SummonWave -= uiDiff;
        DoMeleeAttackIfReady();
    }
};

/*######
## npc_drakari
######*/

struct MANGOS_DLL_DECL npc_drakariAI : public ScriptedAI
{
    npc_drakariAI(Creature* pCreature) : ScriptedAI(pCreature){
		m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
		m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
		Reset();
	}
	
	ScriptedInstance* m_pInstance;	
	bool m_bIsRegularMode;
	uint32 TrollgoreGUID;

    void Reset(){}

    void Aggro(Unit* pWho){}

    void JustDied(Unit* pKiller)
    {
		if(urand(0,9) == 0){
			DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_CORPSEEXLODE : SPELL_CORPSEEXLODE_H);
		}
    }
	
	void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case 26630: TrollgoreGUID        = pCreature->GetGUID(); break;
        }
    }
	
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
		
		if (Unit* Trollgore = Unit::GetUnit(*m_creature, m_pInstance->GetData64(TrollgoreGUID))){
			m_creature->Attack(Trollgore, true);
		}
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_drakari(Creature* pCreature)
{
    return new npc_drakariAI(pCreature);
}

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI(pCreature);
}

void AddSC_boss_trollgore()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_trollgore";
    newscript->GetAI = &GetAI_boss_trollgore;
    newscript->RegisterSelf();
	
	newscript = new Script;
    newscript->Name = "npc_drakari";
    newscript->GetAI = &GetAI_npc_drakari;
    newscript->RegisterSelf();
}
