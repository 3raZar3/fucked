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
SDName: Boss_Taldaram
SD%Complete: 90%
SDComment: more difficult
SDCategory: Ahn'kahet
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

/* todo
need t be  replaced in DB on ground  position
*/

#include "precompiled.h"
#include "ahnkahet.h"

enum Sounds
{
    SAY_AGGRO                       = -1619008,
    SAY_VANISH_1                    = -1619009,
    SAY_VANISH_2                    = -1619010,
    SAY_FEED_1                      = -1619011,
    SAY_FEED_2                      = -1619012,
    SAY_SLAY_1                      = -1619013,
    SAY_SLAY_2                      = -1619014,
    SAY_SLAY_3                      = -1619015,
    SAY_DEATH                       = -1619016
};

enum Spells
{
    SPELL_BLOODTHIRST               = 55968,
    SPELL_CONJURE_FLAME_SPHERE      = 55931,
    SPELL_EMBRACE_OF_VAMPYR         = 55959,
    SPELL_EMBRACE_OF_VAMPYR_H       = 59513,
    SPELL_VANISH                    = 55964,

    SPELL_SEARBEAM                  = 57748, // 20 yards arround flame orb conde dmg -> player
    SPELL_SEARBEAM_H                = 58938,
};

enum Creatures
{
    CREATURE_FLAME_ORB              = 30702 // dissapir after 10 seconds // 3 spheres  in heroic mode
};
/*######
## boss_taldaram
######*/

struct MANGOS_DLL_DECL boss_taldaramAI : public ScriptedAI
{
    boss_taldaramAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsVampiryc;
    //bool m_bIsDamageNow;

    uint32 m_uiSphereTimer;
    uint32 m_uiBloothirstTimer;
    uint32 m_uiVampirycTimer;
    uint32 m_uiVanishTimer;
    //uint64 m_uiDamageTaken;
    //uint64 TargetGUID;

    void Reset()
    {
        m_uiSphereTimer     = urand(20000,25000);
        m_uiBloothirstTimer = urand(15000,20000);
        m_uiVanishTimer     = urand(50000,70000);
        m_bIsVampiryc       = false;
        //m_uiDamageTaken     = 0;
        //m_bIsDamageNow      = false;
        //TargetGUID          = 0;


        if(m_creature->HasAura(SPELL_VANISH))
            m_creature->RemoveAurasDueToSpell(SPELL_VANISH);
        if(m_creature->HasAura(60342))
            m_creature->RemoveAurasDueToSpell(60342);
        m_creature->SetVisibility(VISIBILITY_ON);

        if(m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_TALDARAM) != SPECIAL)
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
        if(m_pInstance)
            m_pInstance->SetData(TYPE_TALDARAM, IN_PROGRESS);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TALDARAM, DONE);
    }

    /*
    void DamageTaken(Unit* pDoneBy, uint32& uiDamage) 
    {
        if(m_bIsDamageNow)
            m_uiDamageTaken += uiDamage;
    }
    */

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_pInstance && m_pInstance->GetData(TYPE_TALDARAM) == SPECIAL)
            if(m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Need More Support :)
        /*
        if(m_uiDamageTaken > 40000)
        {
            //DoScriptText(SAY_AGGRO, m_creature);
            if(Unit* Target = Unit::GetUnit(*m_creature, TargetGUID))
                if(Target->isAlive())
                    Target->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_EMBRACE_OF_VAMPYR : SPELL_EMBRACE_OF_VAMPYR_H);
            m_uiDamageTaken = 0; 
            m_bIsDamageNow = false;
        }
        */

        if(m_bIsVampiryc)
        {
            if(m_uiVampirycTimer < uiDiff)
            {
                if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                {
                    m_bIsVampiryc   = false;
                    //m_bIsDamageNow  = true;
                    //m_uiDamageTaken = 0;
                    //TargetGUID      = target->GetGUID();
                    m_uiVanishTimer = urand(50000,65000);
                    m_creature->RemoveAurasDueToSpell(SPELL_VANISH);
                    m_creature->SetVisibility(VISIBILITY_ON);
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    m_creature->GetMap()->CreatureRelocation(m_creature, target->GetPositionX()+1, target->GetPositionY()+1, target->GetPositionZ(), m_creature->GetOrientation());
                    m_creature->CastSpell(target, m_bIsRegularMode ? SPELL_EMBRACE_OF_VAMPYR : SPELL_EMBRACE_OF_VAMPYR_H, false);
                }
            }else m_uiVampirycTimer -= uiDiff;
            return;
        }

        if(m_uiVanishTimer < uiDiff)
        {
            m_creature->CastSpell(m_creature, SPELL_VANISH, false);
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_uiVampirycTimer = 5000;
            m_bIsVampiryc = true;
        }else m_uiVanishTimer -= uiDiff;

        if(m_uiBloothirstTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), SPELL_BLOODTHIRST, false);
            m_uiBloothirstTimer = urand(15000,20000);
        }else m_uiBloothirstTimer -= uiDiff;

        if(m_uiSphereTimer < uiDiff)
        {
            uint8 i=1;
            if(!m_bIsRegularMode)
                i=3;
            for(uint8 k=0; k<i; ++k)
                if(Creature* Sphere = m_creature->SummonCreature(CREATURE_FLAME_ORB, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+5, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    Sphere->SetVisibility(VISIBILITY_ON);
                    Sphere->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			        if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				        Sphere->AI()->AttackStart(target);
                }
            m_uiSphereTimer = urand(20000,25000);
        }else m_uiSphereTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_taldaram(Creature* pCreature)
{
    return new boss_taldaramAI(pCreature);
}

//Flame Sphere
struct MANGOS_DLL_DECL mob_flame_sphereAI : public ScriptedAI
{
    mob_flame_sphereAI(Creature *pCreature) : ScriptedAI(pCreature) 
    { 
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool   m_bIsRegularMode;
    uint32 m_uiBeamTimer;
 
    void Reset()
    {
        m_uiBeamTimer = 2000;
        m_creature->setFaction(14);
        m_creature->SetVisibility(VISIBILITY_ON);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                return;

        if(m_uiBeamTimer < diff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SEARBEAM : SPELL_SEARBEAM_H, false);
            m_uiBeamTimer = 2000;
        }else m_uiBeamTimer -= diff;
    }
};

CreatureAI* GetAI_mob_flame_sphere(Creature* pCreature)
{
    return new mob_flame_sphereAI(pCreature);
}

/*######
## go_nerubian_device
######*/

bool GOHello_go_nerubian_device(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    pInstance->SetData(TYPE_TALDARAM, SPECIAL);
    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
    return false;
}

void AddSC_boss_taldaram()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_taldaram";
    newscript->GetAI = &GetAI_boss_taldaram;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_flame_sphere";
    newscript->GetAI = &GetAI_mob_flame_sphere;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_nerubian_device";
    newscript->pGOHello = &GOHello_go_nerubian_device;
    newscript->RegisterSelf();
}