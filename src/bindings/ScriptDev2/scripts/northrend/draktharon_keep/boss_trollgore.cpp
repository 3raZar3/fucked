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

/* Script Data Start
SDName: Boss trollgore
SDAuthor: Tartalo modified for Mangos by Aramil
SD%Complete: 99%
Script Data End */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum Spells
{
    SPELL_INFECTED_WOUND                                   = 49637,
    SPELL_CRUSH                                            = 49639,
    SPELL_CORPSE_EXPLODE                                   = 49555,
    SPELL_CONSUME                                          = 49380,
    //Heroic spells
    H_SPELL_CORPSE_EXPLODE                                 = 59807,
    H_SPELL_CONSUME                                        = 59803,
	SPELL_SUMMON										   = 49457
};
//not in db
enum Yells
{
    SAY_AGGRO                                              = -1600006,
    SAY_KILL                                               = -1600007,
    SAY_CONSUME                                            = -1600008,
    SAY_EXPLODE                                            = -1600009,
    SAY_DEATH                                              = -1600010
};
struct MANGOS_DLL_DECL boss_trollgoreAI : public ScriptedAI
{
    boss_trollgoreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    uint32 uiConsumeTimer;
    uint32 uiAuraCountTimer;
    uint32 uiCrushTimer;
    uint32 uiInfectedWoundTimer;
    uint32 uiExplodeCorpseTimer;
    uint32 uiSpawnTimer;

    ScriptedInstance* pInstance;
	
    bool m_bIsRegularMode;    

    void Reset()
    {
        uiConsumeTimer = 15000;
        uiAuraCountTimer = 15500;
        uiCrushTimer = urand(1000,5000);
        uiInfectedWoundTimer = urand(6000,10000);
        uiExplodeCorpseTimer = 3000;
        uiSpawnTimer = urand(30000,40000);

        if (pInstance)
            pInstance->SetData(DATA_TROLLGORE, NOT_STARTED);
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (pInstance)
            pInstance->SetData(DATA_TROLLGORE, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (uiSpawnTimer <= diff)
        {
			if(!m_bIsRegularMode){
				DoCast(m_creature, SPELL_SUMMON);
				DoCast(m_creature, SPELL_SUMMON);
			} else {
				DoCast(m_creature, SPELL_SUMMON);
				DoCast(m_creature, SPELL_SUMMON);
				DoCast(m_creature, SPELL_SUMMON);
			}
            uiSpawnTimer = urand(30000,40000);
        } else uiSpawnTimer -= diff;

        if (uiConsumeTimer <= diff)
        {
            DoScriptText(SAY_CONSUME, m_creature);
			DoCast(m_creature, m_bIsRegularMode ? SPELL_CONSUME : H_SPELL_CONSUME);
            uiConsumeTimer = 15000;
        } else uiConsumeTimer -= diff;

        if (uiCrushTimer <= diff)
        {
			DoCast(m_creature->getVictim(), SPELL_CRUSH);
            uiCrushTimer = urand(10000,15000);
        } else uiCrushTimer -= diff;

        if (uiInfectedWoundTimer <= diff)
        {
			DoCast(m_creature->getVictim(), SPELL_INFECTED_WOUND);
            uiInfectedWoundTimer = urand(25000,35000);
        } else uiInfectedWoundTimer -= diff;

        if (uiExplodeCorpseTimer <= diff)
        {
			DoCast(m_creature, m_bIsRegularMode ? SPELL_CORPSE_EXPLODE : H_SPELL_CORPSE_EXPLODE);
            DoScriptText(SAY_EXPLODE, m_creature);
            uiExplodeCorpseTimer = urand(15000,19000);
        } else uiExplodeCorpseTimer -= diff;

        DoMeleeAttackIfReady();
    }
    
    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (pInstance)
        {
            pInstance->SetData(DATA_TROLLGORE, DONE);
        }
    }
    
    void KilledUnit(Unit *victim)
    {
        if (victim == m_creature)
            return;
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustSummoned(Creature* summon)
    {
        summon->AI()->AttackStart(m_creature);
    }
};

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI (pCreature);
}

void AddSC_boss_trollgore()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_trollgore";
    newscript->GetAI = &GetAI_boss_trollgore;
    newscript->RegisterSelf();
}
