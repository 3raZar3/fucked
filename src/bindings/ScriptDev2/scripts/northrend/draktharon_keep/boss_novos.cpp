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
SDName: Boss_Novos
SD%Complete: 80%
SDAuthor: Aramil
SDComment: Incorect changing Phase. Change to second phase after 4th spawn of special NPC.
SDCategory: Drak'Tharon Keep
EndScriptData */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    SAY_AGGRO                       = -1600005,
    SAY_DEATH                       = -1600006,
    SAY_KILL                        = -1600007,
    SAY_ADDS                        = -1600008,
    SAY_BUBBLE_1                    = -1600009,
    SAY_BUBBLE_2                    = -1600010,

    EMOTE_ASSISTANCE                = -1600011,
	
	// spells
	SPELL_FIELD						= 47346,
	
		// normal
		SPELL_FROSTBOLT				= 49037,
		SPELL_MISERY				= 50089,
		SPELL_ARCANE				= 49198,
		SPELL_BLIZZARD				= 49034,
		// heroic
		SPELL_FROSTBOLT_H			= 59855,
		SPELL_MISERY_H				= 59856,
		SPELL_ARCANE_H				= 59909,
		SPELL_BLIZZARD_H			= 59854,
		SPELL_SUMMON				= 59910,
	
	// npc
	NPC_SHADOWCASTER				= 27600,
	NPC_TROLL						= 27598,	
	NPC_HULKING						= 27597,
	NPC_CRYSTAL						= 26627, // npc need for event
	
	// gobject guid
	ITEM_CRYSTAL					= 38555,
	SPELL_THROW_KEY					= 38134,
	
};

/*######
## boss_novos
######*/

struct MANGOS_DLL_DECL boss_novosAI : public ScriptedAI
{
    boss_novosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
	
    bool m_bIsRegularMode;
	bool FirstPhaseStart;
	bool SecondPhaseStart;

	uint32 Phase;
	uint32 Frostbolt_Timer;
	uint32 Misery_Timer;
	uint32 Arcane_Timer;
	uint32 Blizzard_Timer;
	uint32 Summon_H_Timer;
	uint32 Summon_Timer;
	uint32 Field_Timer;
	uint32 Special_Summon_Timer;
	uint32 Crystal_Deaths;
	uint32 Change_Phase_Timer;

    void Reset()
    {
		Phase = 1;
		Field_Timer = 1;
		Frostbolt_Timer = 5000;
		Misery_Timer = 10000;
		Arcane_Timer = 25000;
		Blizzard_Timer = 30000;
		Summon_H_Timer = 15000;
		Summon_Timer = 15000;
		Special_Summon_Timer = 30000;
		Crystal_Deaths = 0;
		Change_Phase_Timer = 0;
		FirstPhaseStart = false;
		SecondPhaseStart = false;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
		Phase = 1;
    }

    void KilledUnit(Unit* pVictim)
    {
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
	
		if(Phase == 1) {
			// phase 1
			if(!FirstPhaseStart) {
				m_creature->CastSpell(m_creature, SPELL_FIELD, 0, 0, 0 ,0);
				m_creature->StopMoving();
				m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				DoStopAttack();
				FirstPhaseStart = true;
			}
			// summon normal npc
				if (Summon_Timer < uiDiff)
				{
					for (uint8 i=0; i<2+-rand()%1; ++i){
						m_creature->SummonCreature(NPC_SHADOWCASTER, -378.797+-rand()%20, -739+-rand()%20, 28, 0+rand()%5, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
						}
					for (uint8 i=0; i<2+-rand()%1; ++i){
						m_creature->SummonCreature(NPC_TROLL, -378.797+-rand()%7, -739+-rand()%7, 28, 0+rand()%5, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
						}
					for (uint8 i=0; i<2+-rand()%2; ++i){
						m_creature->SummonCreature(NPC_HULKING, -378.797+-rand()%7, -739+-rand()%7, 28, 0+rand()%5, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
						}
					Summon_Timer = 15000;
				} Summon_Timer -= uiDiff;
			// summon special npc
			if (Special_Summon_Timer < uiDiff)
            {
				DoScriptText(EMOTE_ASSISTANCE, m_creature);
				m_creature->SummonCreature(NPC_CRYSTAL, -378, -767, 28, 1, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				Special_Summon_Timer = 30000;
				Crystal_Deaths++;
            } Special_Summon_Timer -= uiDiff;
			// after 4 kills of special npc change phase
			if(Crystal_Deaths >= 4) {
				Phase = 2;
			}
		} else {
			// phase 2
			if(!SecondPhaseStart){
				m_creature->InterruptNonMeleeSpells(false);
				m_creature->getVictim();
				m_creature->CanFreeMove();
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				SecondPhaseStart = true;
			}
			Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 1);
            if(!target)
                target = m_creature->getVictim();
				
			if (Frostbolt_Timer < uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_FROSTBOLT : SPELL_FROSTBOLT_H);
                Frostbolt_Timer = urand(5000, 15000);
            }	Frostbolt_Timer -= uiDiff;
			
			if (Misery_Timer < uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_MISERY : SPELL_MISERY_H);
                Misery_Timer = urand(15000, 35000);
            }	Misery_Timer -= uiDiff;
			
			if (Arcane_Timer < uiDiff)
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_ARCANE : SPELL_ARCANE_H);
                Arcane_Timer = urand(5000, 20000);
            }	Arcane_Timer -= uiDiff;
			
			if (Blizzard_Timer < uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_ARCANE : SPELL_ARCANE_H);
                Blizzard_Timer = urand(25000, 35000);
            }	Blizzard_Timer -= uiDiff;
			
			if(!m_bIsRegularMode && Summon_H_Timer < uiDiff) {
				DoCast(m_creature, SPELL_SUMMON);
				Summon_H_Timer = urand(30000, 35000);
			} Summon_H_Timer -= uiDiff;
	}
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_novos(Creature* pCreature)
{
    return new boss_novosAI(pCreature);
}

void AddSC_boss_novos()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_novos";
    newscript->GetAI = &GetAI_boss_novos;
    newscript->RegisterSelf();
}
