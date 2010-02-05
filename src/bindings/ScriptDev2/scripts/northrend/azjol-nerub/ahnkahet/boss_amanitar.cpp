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
SDName: Boss_Amanitar
SD%Complete: 90%
SDComment:
SDCategory: Ahn'kahet
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_BASH          = 57094,
    SPELL_ROOTS         = 57095,
    SPELL_MINI          = 57055,
    SPELL_BOLT          = 57088,

    SPELL_POTENT_FUNGUS = 56648,
    SPELL_POISON        = 57061,

    MUSHROOM_HEALTHY    = 30435,
    MUSHROOM_POISON     = 30391, // 59116, //30391,
    SPELL_PUTRID_MUSHROOM   = 31690
};

/*######
## boss_amanitar
######*/

struct MANGOS_DLL_DECL boss_amanitarAI : public ScriptedAI
{
    boss_amanitarAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}

    uint32 m_uiBashTimer;
    uint32 m_uiBoltTimer;
    uint32 m_uiRootsTimer;
    uint32 m_uiMiniTimer;
    uint32 m_uiMushroomsTimer;

    float fPosX;
    float fPosY;
    float fPosZ;
    
    void Reset()
    {
        m_uiBashTimer       = urand(10000,25000);
        m_uiBoltTimer       = urand(10000,20000);
        m_uiRootsTimer      = urand(10000,15000);
        m_uiMiniTimer       = urand(25000,30000);
        m_uiMushroomsTimer  = 25000;

        fPosX = m_creature->GetPositionX();
        fPosY = m_creature->GetPositionY();
        fPosZ = m_creature->GetPositionZ();
    }

    void JustDied(Unit* pKiller)
    {
        for(uint8 i=0; i<5; ++i)
            Creature* Mushroom = m_creature->SummonCreature(MUSHROOM_HEALTHY, m_creature->GetPositionX()+urand(5,10), m_creature->GetPositionY()+urand(5,10), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiBashTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), SPELL_BASH, false);
            m_uiBashTimer = urand(5000,10000);
        }else m_uiBashTimer -= uiDiff;

        if(m_uiBoltTimer < uiDiff)
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                m_creature->CastSpell(target, SPELL_BOLT, true);
            m_uiBoltTimer = urand(8000,16000);
        }else m_uiBoltTimer -= uiDiff;

        if(m_uiRootsTimer < uiDiff)
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
            {
                m_creature->CastSpell(target, SPELL_ROOTS, true);
                fPosX = target->GetPositionX();
                fPosY = target->GetPositionY();
                fPosZ = target->GetPositionZ();
            }
            m_uiRootsTimer = urand(10000,15000);
        }else m_uiRootsTimer -= uiDiff;

        if(m_uiMiniTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), SPELL_MINI, true);
            m_uiMiniTimer = urand(25000,35000);
        }else m_uiMiniTimer -= uiDiff;

        if(m_uiMushroomsTimer < uiDiff)
        {
            uint32 ID = MUSHROOM_POISON;
            if(urand(0,1) == 0)
                ID = MUSHROOM_HEALTHY;

            Creature* Mushroom = m_creature->SummonCreature(ID, fPosX, fPosY, fPosZ, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);
            if(Mushroom && m_creature->getVictim()) 
                Mushroom->AI()->AttackStart(m_creature->getVictim());

            m_uiMushroomsTimer = urand(10000,20000);
        }else m_uiMushroomsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_amanitar(Creature* pCreature)
{
    return new boss_amanitarAI(pCreature);
}

struct MANGOS_DLL_DECL mob_healthymushroomAI : public Scripted_NoMovementAI
{
    mob_healthymushroomAI(Creature *c) : Scripted_NoMovementAI(c) { Reset(); }
 
    void Reset() 
    {
        DoCast(m_creature,SPELL_PUTRID_MUSHROOM,true);
    }

    void JustDied(Unit* pKiller)
    {
        if(!pKiller)
            return;

        m_creature->CastSpell(pKiller, SPELL_POTENT_FUNGUS, true);

        if(pKiller->HasAura(SPELL_MINI))
            pKiller->RemoveAurasDueToSpell(SPELL_MINI);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_healthymushroom(Creature* pCreature)
{
    return new mob_healthymushroomAI(pCreature);
}

struct MANGOS_DLL_DECL mob_poisonmushroomAI : public Scripted_NoMovementAI
{
    mob_poisonmushroomAI(Creature *c) : Scripted_NoMovementAI(c) { Reset(); }
 
    void Reset() 
    {
        DoCast(m_creature,SPELL_PUTRID_MUSHROOM,true);
    }

    void JustDied(Unit* pKiller)
    {
        if(!pKiller)
            return;

        m_creature->CastSpell(pKiller, SPELL_POISON, true);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_poisonmushroom(Creature* pCreature)
{
    return new mob_poisonmushroomAI(pCreature);
}

void AddSC_boss_amanitar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_amanitar";
    newscript->GetAI = &GetAI_boss_amanitar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_healthymushroom";
    newscript->GetAI = &GetAI_mob_healthymushroom;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_poisonmushroom";
    newscript->GetAI = &GetAI_mob_poisonmushroom;
    newscript->RegisterSelf();
}
