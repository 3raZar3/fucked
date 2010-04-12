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
SDName: Boss_Faerlina
SD%Complete: 60
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_GREET                 = -1533009,
    SAY_AGGRO1                = -1533010,
    SAY_AGGRO2                = -1533011,
    SAY_AGGRO3                = -1533012,
    SAY_AGGRO4                = -1533013,
    SAY_SLAY1                 = -1533014,
    SAY_SLAY2                 = -1533015,
    SAY_DEATH                 = -1533016,

    SPELL_POSIONBOLT_VOLLEY   = 28796,
    H_SPELL_POSIONBOLT_VOLLEY = 54098,
    SPELL_ENRAGE              = 28798,
    H_SPELL_ENRAGE            = 54100,

    SPELL_RAINOFFIRE          = 28794,                       //Not sure if targeted AoEs work if casted directly upon a pPlayer
	
	CREATURE_WORSHIPER        = 16506,
    CREATURE_FOLLOWER         = 16505,
	
	SPELL_FIREBALL            = 54095,
	SPELL_FIREBALL_H          = 54096,
	SPELL_WIDOWS_EMBRACE      = 28732,
	
};
struct MANGOS_DLL_DECL boss_faerlinaAI : public ScriptedAI
{
    boss_faerlinaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_bHasTaunted = false;
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;

    uint64 m_uiWorshiperGUID[4];
	uint32 m_uiPoisonBoltVolleyTimer;
    uint32 m_uiRainOfFireTimer;
    uint32 m_uiEnrageTimer;
    bool   m_bHasTaunted;

    void Reset()
    {
        m_uiPoisonBoltVolleyTimer = 8000;
        m_uiRainOfFireTimer = 16000;
        m_uiEnrageTimer = 60000;
		
        for(uint8 i=0; i<4; ++i)
            m_uiWorshiperGUID[i] = 0;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FAERLINA, NOT_STARTED);
    }

    void Aggro(Unit *who)
    {
		
		SpawnAdds();
		
        switch (rand()%4)
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
            case 2: DoScriptText(SAY_AGGRO3, m_creature); break;
            case 3: DoScriptText(SAY_AGGRO4, m_creature); break;
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FAERLINA, IN_PROGRESS);
    }
	
    void SpawnAdds()
    {
        for(uint8 i=0; m_bIsRegularMode ? i<4 : i<6 ; ++i)
        {
            uint32 ID = CREATURE_FOLLOWER;
            if(i<4)
                ID = CREATURE_WORSHIPER;

            Creature* Guard = m_creature->SummonCreature(ID, m_creature->GetPositionX()+urand(2,6), m_creature->GetPositionY()+urand(2,6), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
            if(Guard)
            {
                if(Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
                    Guard->AI()->AttackStart(pPlayer);
                if(i<4)
                    m_uiWorshiperGUID[i] = Guard->GetGUID();
            }
        }
    }	
	
    void MoveInLineOfSight(Unit* pWho)
    {
        if (!m_bHasTaunted && m_creature->IsWithinDistInMap(pWho, 60.0f))
        {
            DoScriptText(SAY_GREET, m_creature);
            m_bHasTaunted = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1)?SAY_SLAY1:SAY_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FAERLINA, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FAERLINA, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
			
        //If some worshiper ar dead cast spell
        for(uint8 i=0; i<4; ++i)
        {
            Unit* Worshiper = Unit::GetUnit(*m_creature, m_uiWorshiperGUID[i]);
            if(Worshiper && !Worshiper->isAlive())
            {
                //cheach if this spell working corectly
                if(m_creature->HasAura(SPELL_ENRAGE))
                {
                    m_creature->RemoveAurasDueToSpell(SPELL_ENRAGE);
                    m_uiPoisonBoltVolleyTimer = m_uiPoisonBoltVolleyTimer + 30000;
                    //m_creature->AddAura(SPELL_WIDOWS_EMBRANCE);
                }
                else 
                    m_uiEnrageTimer = m_uiEnrageTimer + 30000;

                m_uiWorshiperGUID[i] = 0;
            }
        }		
		
        //PoisonBoltVolley_Timer
        if (m_uiPoisonBoltVolleyTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_POSIONBOLT_VOLLEY : H_SPELL_POSIONBOLT_VOLLEY);
            m_uiPoisonBoltVolleyTimer = 9000 + rand()%2000;
        }else m_uiPoisonBoltVolleyTimer -= uiDiff;

        //RainOfFire_Timer
        if (m_uiRainOfFireTimer < uiDiff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCastSpellIfCan(target,SPELL_RAINOFFIRE);

            m_uiRainOfFireTimer = 14000 + rand()%2000;
        }else m_uiRainOfFireTimer -= uiDiff;

        //Enrage_Timer
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : H_SPELL_ENRAGE);
            m_uiEnrageTimer = 60000 + rand()%20000;
        }else m_uiEnrageTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_worshippersAI : public ScriptedAI
{
    mob_worshippersAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsDead;

    uint32 m_uiFireball_Timer;
    uint32 m_uiDeathDelay_Timer;

    void Reset()
    {
        m_bIsDead = false;
        m_uiFireball_Timer = 0;
        m_uiDeathDelay_Timer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_bIsDead)
        {
            uiDamage = 0;
            return;
        }

        if (uiDamage > m_creature->GetHealth())
        {
            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            m_creature->RemoveAllAuras();
            m_creature->AttackStop();

            DoCastSpellIfCan(m_creature, SPELL_WIDOWS_EMBRACE);

            if (m_pInstance)
                if (Creature* pFaerlina = ((Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(TYPE_FAERLINA))))
                    if (m_creature->GetDistance2d(pFaerlina) <= 5 && pFaerlina->HasAura(m_bIsRegularMode ? SPELL_ENRAGE : H_SPELL_ENRAGE))
                        pFaerlina->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_ENRAGE : H_SPELL_ENRAGE);

            m_bIsDead = true;
            m_uiDeathDelay_Timer = 500;

            uiDamage = 0;
            return;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiDeathDelay_Timer)
            if (m_uiDeathDelay_Timer < uiDiff)
            {
                m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                m_uiDeathDelay_Timer = 0;
            }
            else m_uiDeathDelay_Timer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFireball_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FIREBALL : SPELL_FIREBALL_H);
            m_uiFireball_Timer = 7000 + rand()%4000;
        }
        else m_uiFireball_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_worshippers(Creature* pCreature)
{
    return new mob_worshippersAI(pCreature);
}

CreatureAI* GetAI_boss_faerlina(Creature* pCreature)
{
    return new boss_faerlinaAI(pCreature);
}

void AddSC_boss_faerlina()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_faerlina";
    NewScript->GetAI = &GetAI_boss_faerlina;
    NewScript->RegisterSelf();
	
	NewScript = new Script;
    NewScript->Name = "mob_worshippers";
    NewScript->GetAI = &GetAI_mob_worshippers;
    NewScript->RegisterSelf();
}
