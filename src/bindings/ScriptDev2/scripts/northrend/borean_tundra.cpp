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
SDName: Borean_Tundra
SD%Complete: 100
SDComment: Quest support: 11708, 11692, 11961. Taxi vendors.
SDCategory: Borean Tundra
EndScriptData */

/* ContentData
mob_elder
npc_fizzcrank_fullthrottle
npc_iruk
npc_kara_thricestar
mob_overseer
npc_surristrasz
npc_tiare
go_blue_drake_egg

-- Overseer texts
DELETE FROM script_texts WHERE entry BETWEEN -1999844 AND -1999842;
INSERT INTO script_texts (`entry`, `content_default`,`comment`) VALUES
(-1999844,'You dare to defy the sons of iron?','Overseer(1)'),
(-1999843,'What do you think you\'re doing?','Overseer aggro(2)'),
(-1999842,'Fool! You will never get away with this!','Overseer aggro(3)');

-- Rune-Weaver Channel focused on Directional Runes
DELETE FROM spell_script_target WHERE entry = 47463;
INSERT INTO spell_script_target VALUES
(47463,0,188471),
(47463,0,188505),
(47463,0,188506),
(47463,0,188507);

-- Directional Runes not targetable for player
UPDATE gameobject_template SET flags = flags|4 WHERE entry IN (188471,188505,188506,188507);

-- Removed Iron Rune-Weaver. They will be spawn by propper overseers in SD2 script
DELETE FROM creature WHERE id = 26820;

-- Spawn missing 4th Directional Rune
DELETE FROM gameobject WHERE id = 188507;
INSERT INTO gameobject VALUES
('400013','188507','571','1','1','3985.83','-5250.23','7.01735','0.05196','0','0','0.0259771','0.999663','300','100','0');

-- Spawn Overseers
DELETE FROM creature WHERE id IN (26921,26920,26922,26923);
INSERT INTO creature VALUES
('11457406','26920','571','1','1','0','749','4486.66','-4654.01','77.547','0.087266','300','0','0','10635','3561','0','0'),
('11457407','26921','571','1','1','0','749','4317.75','-4880.36','33.3857','-0.698132','300','0','0','8508','7981','0','0'),
('11457408','26922','571','1','1','0','749','4218.81','-5050.21','5.62514','-0.506145','300','0','0','10635','3561','0','0'),
('11457405','26923','571','1','1','0','870','3984.56','-5250.67','6.98164','0.336503','300','0','0','10635','3561','0','0');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 26820;

DELETE FROM creature_ai_scripts WHERE creature_id = 26820;
INSERT INTO creature_ai_scripts VALUES
(2682001,26820,1,0,100,0, 500,500,0,0 ,11,47463,0,0, 0,0,0,0, 0,0,0,0,'Iron Rune-Weaver: OOC Rune-Weaving'),
(2682002,26820,0,0,100,1, 1000,3000,30000,30000 ,11,52713,1,1, 0,0,0,0, 0,0,0,0,'Iron Rune-Weaver: Rune-Weaving');

-- Overseer Brunon
-- Overseer Durval
-- Overseer Lochli
UPDATE creature_template SET 
minlevel = 75,
maxlevel = 75,
minhealth = 10635,
maxhealth = 10635,
minmana = 3561,
maxmana = 3561,
faction_A = 754, -- Dark Iron Dwarfs
faction_H = 754,
mindmg = 120,
maxdmg = 180,
dmg_multiplier = 3,
attackpower = 2000,
scriptname = 'mob_overseer'
WHERE entry IN (26923,26922,26920);

-- Overseer Korgan
UPDATE creature_template SET 
minlevel = 75,
maxlevel = 75,
minhealth = 8508,
maxhealth = 8508,
minmana = 7981,
maxmana = 7981,
faction_A = 754,
faction_H = 754,
mindmg = 120,
maxdmg = 180,
dmg_multiplier = 3,
attackpower = 2000,
scriptname = 'mob_overseer'
WHERE entry IN (26921);
EndContentData */

#include "precompiled.h"
#include "ObjectMgr.h"
#include "escort_ai.h"

/*######
## mob_elder
######*/
enum
{
    SPELL_ANCESTOR_RITUAL               = 45536,
    SPELL_GREEN_BEAM                    = 39165,

    NPC_ELDER_KESUK                     = 25397,
    NPC_ELDER_SAGANI                    = 25398,
    NPC_ELDER_TAKRET                    = 25399,
    
    GO_ELDER_KESUK                      = 191088,
    GO_ELDER_SAGANI                     = 191089,
    GO_ELDER_TAKRET                     = 191090,

    POINT_ID                            = 1
};

struct MANGOS_DLL_DECL mob_elderAI : public ScriptedAI
{
    mob_elderAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bEventInProgress;
    uint64 uiPlayerGUID;
    uint32 m_uiResetTimer;

    void Reset()
    {
        uiPlayerGUID = 0;
        m_uiResetTimer = 10000;

        m_creature->InterruptSpell(CURRENT_CHANNELED_SPELL,false);
        m_creature->RemoveAllAuras();
        m_creature->SetDisplayId(m_creature->GetNativeDisplayId());
        m_creature->GetMotionMaster()->MoveTargetedHome();

        bEventInProgress = false;
    }

    void SpellHit(Unit* pCaster, SpellEntry const* pSpell)
    {
        if (!pCaster || bEventInProgress)
            return;

        if (pCaster->GetTypeId() == TYPEID_PLAYER && pSpell->Id == SPELL_ANCESTOR_RITUAL)
        {
            bEventInProgress = true;
            uiPlayerGUID = pCaster->GetGUID();
            if (CreatureInfo const* pTemp = GetCreatureTemplateStore(m_creature->GetEntry()))
                m_creature->SetDisplayId(((Player*)pCaster)->GetTeam() == HORDE ? pTemp->DisplayID_H[0] : pTemp->DisplayID_A[0]);

            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->StopMoving();

            uint32 go_entry;
            switch (m_creature->GetEntry())
            {
                case NPC_ELDER_SAGANI:  go_entry = GO_ELDER_SAGANI; break;
                case NPC_ELDER_KESUK:   go_entry = GO_ELDER_KESUK; break;
                case NPC_ELDER_TAKRET:  go_entry = GO_ELDER_TAKRET; break;
                default: break;
            }
            
            float x,y,z;
            if (GameObject* pGo = GetClosestGameObjectWithEntry(pCaster, go_entry, DEFAULT_VISIBILITY_DISTANCE))
                pGo->GetNearPoint(pGo,x,y,z,2.0f,2.0f,pGo->GetOrientation());
            else 
            {
                error_log("SD2: mob_elder (%s entry %u) couldn't find gameobject entry %u. Please check your database",m_creature->GetName(),m_creature->GetEntry(),go_entry);
                Reset();
            }

            m_creature->GetMotionMaster()->MovePoint(POINT_ID,x,y,z);
        }
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE)
            return;

        Player* pPlayer = (Player*)Unit::GetUnit((*m_creature),uiPlayerGUID);

        if (!pPlayer)
            return;

        if (id == POINT_ID)
        {
            DoCast(m_creature,SPELL_GREEN_BEAM,false);
            // Because spell focus is m_creature not static gameobject or something we have to check if player actualy is near m_creature
            if (pPlayer->GetDistance(m_creature) < 5.0f)
                pPlayer->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetGUID()); 
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->HasAura(SPELL_GREEN_BEAM))
        {
            if (m_uiResetTimer <= uiDiff)
                Reset();
            else m_uiResetTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_elder(Creature* pCreature)
{
    return new mob_elderAI(pCreature);
}


/*######
## npc_fizzcrank_fullthrottle
######*/

#define GOSSIP_ITEM_GO_ON   "Go on."
#define GOSSIP_ITEM_TELL_ME "Tell me what's going on out here, Fizzcrank."

enum
{
    GOSSIP_TEXTID_FIZZCRANK1    = 12456,
    GOSSIP_TEXTID_FIZZCRANK2    = 12457,
    GOSSIP_TEXTID_FIZZCRANK3    = 12458,
    GOSSIP_TEXTID_FIZZCRANK4    = 12459,
    GOSSIP_TEXTID_FIZZCRANK5    = 12460,
    GOSSIP_TEXTID_FIZZCRANK6    = 12461,
    GOSSIP_TEXTID_FIZZCRANK7    = 12462,
    GOSSIP_TEXTID_FIZZCRANK8    = 12463,
    GOSSIP_TEXTID_FIZZCRANK9    = 12464,

    QUEST_THE_MECHAGNOMES       = 11708
};

bool GossipHello_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_MECHAGNOMES) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELL_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK7, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK8, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK9, pCreature->GetGUID());
            pPlayer->AreaExploredOrEventHappens(QUEST_THE_MECHAGNOMES);
            break;
    }
    return true;
}

/*######
## npc_iruk
######*/

#define GOSSIP_ITEM_IRUK        "<Search corpse for Issliruk's Totem.>"

enum
{
    QUEST_SPIRITS_WATCH_OVER_US     = 11961,
    SPELL_CREATE_TOTEM              = 46816
};

bool GossipHello_npc_iruk(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SPIRITS_WATCH_OVER_US) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_IRUK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_iruk(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,SPELL_CREATE_TOTEM,true);
    }

    return true;
}

/*######
## npc_kara_thricestar
######*/

#define GOSSIP_ITEM_THRICESTAR1      "Do you think I could take a ride on one of those flying machines?"
#define GOSSIP_ITEM_THRICESTAR2      "Kara, I need to be flown out the Dens of Dying to find Bixie."

enum
{
    QUEST_CHECK_IN_WITH_BIXIE       = 11692,
    SPELL_FIZZCRANK_AIRSTRIP        = 51446
};

bool GossipHello_npc_kara_thricestar(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isTaxi())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_THRICESTAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    if (pPlayer->GetQuestStatus(QUEST_CHECK_IN_WITH_BIXIE) == QUEST_STATUS_COMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THRICESTAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_kara_thricestar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->GetSession()->SendTaxiMenu(pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer, SPELL_FIZZCRANK_AIRSTRIP, false);
            break;
    }

    return true;
}
/*######
##mob_overseer
######*/
enum Overseer
{
    GO_RUNE_BRUNON                  = 188507,
    GO_RUNE_LOCHLI                  = 188506,
    GO_RUNE_KORGAN                  = 188505,
    GO_RUNE_DURVAL                  = 188471,

    NPC_BRUNON                      = 26923,
    NPC_LOCHLI                      = 26922,
    NPC_KORGAN                      = 26921,
    NPC_DURVAL                      = 26920,

    MOB_RUNE_WEAVER                 = 26820,
    MAX_WEAVERS                     = 4,

    FACTION_FRIENDLY_ALL            = 35,
    FACTION_DARK_IRON               = 754,

    SPAWN_DISTANCE                  = 15,

    // Durval
    SPELL_RUNE_OF_DESTRUCTION       = 52715,
    // Korgan
    SPELL_CALL_LIGHTNING            = 32018,
    SPELL_SPELL_REVITALIZING_RUNE   = 52714,
    // Lohli
    SPELL_THUNDERSTORM              = 52717,

    SPELL_WEAVING_OOC               = 47463,

    SAY_AGGRO_1                     = -1999844,
    SAY_AGGRO_2                     = -1999843,
    SAY_AGGRO_3                     = -1999842
};

struct MANGOS_DLL_DECL mob_overseerAI : public ScriptedAI
{
    mob_overseerAI(Creature* pCreature) : ScriptedAI(pCreature)
    
    {
        Reset();
        ManageWeavers();
    }

    float WeaverPOSITION[MAX_WEAVERS][3];
    uint64 WeaverGUID[MAX_WEAVERS];
    uint32 m_uiCheckoutTimer;
    uint32 m_uiRuneEntry;
    uint32 m_uiEventTimer;
    uint8 WeaversDead;

    void Reset()
    {
        m_uiCheckoutTimer = 1000;
        m_uiRuneEntry = 0;
        m_uiEventTimer = 10000;
    }

    void ManageWeavers()
    {
        WeaversDead = 0;

        // summoning weavers
        for (int i = 0; i < MAX_WEAVERS; ++i)
        {
            // if somehow overseer entered combat and than evaded before all weavers are dead and despawed (30sec from encounter)
            if (Creature* pWeaver = (Creature*) Unit::GetUnit((*m_creature),WeaverGUID[i]))
            {
                if (!pWeaver->isAlive())
                {
                    pWeaver->Respawn();
                    pWeaver->Relocate(WeaverPOSITION[i][0],WeaverPOSITION[i][1],WeaverPOSITION[i][2]);
                    pWeaver->SetFacingToObject(m_creature);
                }
            }
            else 
            {
                // spawn weavers around overseer in regular distance
                float x,y,z; 
                m_creature->GetNearPoint(m_creature,x,y,z,m_creature->GetObjectSize(),SPAWN_DISTANCE,(i*(6.20f/MAX_WEAVERS)));
                if (Creature* pWeaver = m_creature->SummonCreature(MOB_RUNE_WEAVER,x,y,z,0.0f,TEMPSUMMON_DEAD_DESPAWN,30000))
                {
                    WeaverGUID[i] = pWeaver->GetGUID();
                    WeaverPOSITION[i][0] = x;
                    WeaverPOSITION[i][1] = y;
                    WeaverPOSITION[i][2] = z;                  
                    pWeaver->SetFacingToObject(m_creature);
                }
            }
        }

        switch(m_creature->GetEntry())
        {
            case NPC_BRUNON: m_uiRuneEntry = GO_RUNE_BRUNON; break;
            case NPC_LOCHLI: m_uiRuneEntry = GO_RUNE_LOCHLI; break;
            case NPC_KORGAN: m_uiRuneEntry = GO_RUNE_KORGAN; break;
            case NPC_DURVAL: m_uiRuneEntry = GO_RUNE_DURVAL; break;
        }

        // every reset
        if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature,m_uiRuneEntry,INTERACTION_DISTANCE))
            if (pGo->GetGoState() == GO_STATE_READY)
                pGo->SetGoState(GO_STATE_ACTIVE);

        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->setFaction(FACTION_FRIENDLY_ALL);
    }

    void JustReachedHome()
    {
        ManageWeavers();
    }

    void Aggro(Unit* pWho)
    {
        if (!pWho)
            return;

        switch(urand(0,2))
        {
            case 0: DoScriptText(SAY_AGGRO_1,m_creature); break;
            case 1: DoScriptText(SAY_AGGRO_2,m_creature); break;
            case 2: DoScriptText(SAY_AGGRO_3,m_creature); break;
        }
        ScriptedAI::Aggro(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // in combat
        if (m_creature->getVictim() || (m_creature->SelectHostileTarget() || m_creature->isInCombat()))
        {
            if (m_uiEventTimer <= uiDiff)
            {
                if (Unit* pVictim = m_creature->getVictim())
                    switch(m_creature->GetEntry())
                    {
                        case NPC_DURVAL: DoCast(pVictim,SPELL_RUNE_OF_DESTRUCTION,false); break;
                        case NPC_LOCHLI: DoCast(pVictim,SPELL_THUNDERSTORM,false);break;
                        case NPC_KORGAN:
                            if ((m_creature->GetHealth()*100)/m_creature->GetMaxHealth() < 80)
                                DoCast(m_creature,SPELL_SPELL_REVITALIZING_RUNE,false);
                            else DoCast(pVictim,SPELL_CALL_LIGHTNING,false);
                        default: break;
                    }
                m_uiEventTimer = 30000;
            } else m_uiEventTimer -= uiDiff;

            DoMeleeAttackIfReady();
            return;
        }

        // OOC
        if (m_uiCheckoutTimer <= uiDiff)
        {
            WeaversDead = 0;
            for (int i = 0; i < MAX_WEAVERS; ++i)
            {
                Creature* pWeaver = (Creature*) Unit::GetUnit((*m_creature),WeaverGUID[i]);
                // return weavers to orginal spawn point
                if (pWeaver && pWeaver->isAlive() && !pWeaver->isInCombat())
                    if ((m_creature->GetDistance(pWeaver)> (SPAWN_DISTANCE+1.5)) || (m_creature->GetDistance(pWeaver)< (SPAWN_DISTANCE-1.5)))
                    {
                        if (pWeaver->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
                            pWeaver->GetMotionMaster()->MovePoint(0,WeaverPOSITION[i][0],WeaverPOSITION[i][1],WeaverPOSITION[i][2]);
                    }
                    else
                    {
                        if (!pWeaver->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                            pWeaver->CastSpell(pWeaver,SPELL_WEAVING_OOC,false);
                    }

                //count dead or dead and despawned weavers
                if (!pWeaver || !pWeaver->isAlive())
                    ++WeaversDead;
            }

            if (WeaversDead >= MAX_WEAVERS)
            {
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->setFaction(FACTION_DARK_IRON);

                if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature,m_uiRuneEntry,INTERACTION_DISTANCE))
                    if (pGo->GetGoState() == GO_STATE_ACTIVE)
                        pGo->SetGoState(GO_STATE_READY);
            }
            m_uiCheckoutTimer = 1000;
        } m_uiCheckoutTimer -= uiDiff;
    }                 
};

CreatureAI* GetAI_mob_overseer(Creature* pCreature)
{
    return new mob_overseerAI(pCreature);
}


/*######
## npc_robot_reprogrammed
######*/

enum
{
    SPELL_ULTRASONIC_SCREWDRIVER    = 46023,
    SPELL_REPROGRAM_KILL_CREDIT     = 46027,

    NPC_COLLECT_A_TRON              = 25793,
    SPELL_SUMMON_COLLECT_A_TRON     = 46034,

    NPC_DEFENDO_TANK                = 25758,
    SPELL_SUMMON_DEFENDO_TANK       = 46058,

    NPC_SCAVENGE_A8                 = 25752,
    SPELL_SUMMON_SCAVENGE_A8        = 46063,

    NPC_SCAVENGE_B6                 = 25792,
    SPELL_SUMMON_SCAVENGE_B6        = 46066,

    NPC_SENTRY_BOT                  = 25753,
    SPELL_SUMMON_SENTRY_BOT         = 46068
};

bool EffectDummyCreature_npc_robot_reprogrammed(Unit* pCaster, uint32 uiSpellId, uint32 uiEffIndex, Creature* pCreatureTarget)
{
    //always check spellid and effectindex
    if (uiSpellId == SPELL_ULTRASONIC_SCREWDRIVER && uiEffIndex == 0)
    {
        if (pCreatureTarget->isDead())
        {
            uiSpellId = 0;

            switch(pCreatureTarget->GetEntry())
            {
                case NPC_COLLECT_A_TRON:    uiSpellId = SPELL_SUMMON_COLLECT_A_TRON; break;
                case NPC_DEFENDO_TANK:      uiSpellId = SPELL_SUMMON_DEFENDO_TANK; break;
                case NPC_SCAVENGE_A8:       uiSpellId = SPELL_SUMMON_SCAVENGE_A8; break;
                case NPC_SCAVENGE_B6:       uiSpellId = SPELL_SUMMON_SCAVENGE_B6; break;
                case NPC_SENTRY_BOT:        uiSpellId = SPELL_SUMMON_SENTRY_BOT; break;
            }

            if (const SpellEntry* pSpell = GetSpellStore()->LookupEntry(uiSpellId))
            {
                pCaster->CastSpell(pCreatureTarget, pSpell->Id, true);

                if (Pet* pPet = pCaster->FindGuardianWithEntry(pSpell->EffectMiscValue[uiEffIndex]))
                    pPet->CastSpell(pCaster, SPELL_REPROGRAM_KILL_CREDIT, true);

                pCreatureTarget->ForcedDespawn();
            }
        }

        //always return true when we are handling this spell and effect
        return true;
    }
    return false;
}

/*######
## npc_surristrasz
######*/

#define GOSSIP_ITEM_FREE_FLIGHT "I'd like passage to the Transitus Shield."
#define GOSSIP_ITEM_FLIGHT      "May I use a drake to fly elsewhere?"

enum
{
    SPELL_ABMER_TO_COLDARRA     = 46064
};

bool GossipHello_npc_surristrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isTaxi())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FREE_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_TAXIVENDOR);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_surristrasz(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        //TaxiPath 795 (amber to coldarra)
        pPlayer->CastSpell(pPlayer, SPELL_ABMER_TO_COLDARRA, true);
    }

    if (uiAction == GOSSIP_OPTION_TAXIVENDOR)
        pPlayer->GetSession()->SendTaxiMenu(pCreature);

    return true;
}

/*######
## npc_tiare
######*/

#define GOSSIP_ITEM_TELEPORT    "Teleport me to Amber Ledge, please."

enum
{
    SPELL_TELEPORT_COLDARRA     = 50135
};

bool GossipHello_npc_tiare(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tiare(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_TELEPORT_COLDARRA, true);
    }
    return true;
}
bool GOHello_go_blue_drake_egg(Player* pPlayer, GameObject* pGo)
{
    if (!pPlayer)
        return false;

    pGo->Use(pPlayer);
    //pGo->SetGoState(GO_STATE_ACTIVE);
    pGo->SetRespawnTime(240);

    return true;
}

// Oh Noes, the Tadpoles! 
// HACKED!
enum Tadpole_Cage
{
    MOB_WINTERFIN_TADPOLE       = 25201,
    GO_TADPOLE_CAGE             = 187373,
    QUEST_OH_NOES_THE_TADPOLES  = 11560
};

int32 Speaches[7] =
{ 
    -1999806,-1999805,-1999804,           // negative
    -1999810,-1999809,-1999808,-1999807   // positive
};

struct MANGOS_DLL_DECL mob_tadpoleAI : public ScriptedAI
{
    mob_tadpoleAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bIsFollowing;
    bool bIsResetingCage;
    uint32 Timer;

    void Reset() 
    {
        if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature,GO_TADPOLE_CAGE,2.0f))
        {
            pGo->SetGoState(GO_STATE_READY);
            pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        }

        bIsFollowing = false;
        bIsResetingCage = false;
        Timer = urand(15000, 30000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bIsFollowing || bIsResetingCage)
            if (Timer <= uiDiff)
            {
                if (bIsFollowing)
                {
                    DoScriptText(Speaches[urand(5, 6)],m_creature);
                    Timer = urand(28000,59000);
                }
                // if player is not eligeble for tadpole to follow lets reset him and his cage
                else if (bIsResetingCage)    
                    Reset();
            }else Timer -= uiDiff;
   }
};

CreatureAI* GetAI_mob_tadpole(Creature* pCreature)
{
    return new mob_tadpoleAI(pCreature);
}

bool GOHello_go_tadpole_cage(Player* pPlayer, GameObject* pGo)
{
    if (!pPlayer)
        return false;


    std::list<Creature*> lCreatureList;
    GetCreatureListWithEntryInGrid(lCreatureList, pGo, MOB_WINTERFIN_TADPOLE, 2.0f);

    if (!lCreatureList.empty())
    {
        for (std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
        {
            if ((*itr) && (*itr)->isAlive())
            {
                if (pPlayer->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) != QUEST_STATUS_INCOMPLETE)
                {
                    //choose one of negative speaches
                    DoScriptText(Speaches[urand(0, 2)],(*itr),pPlayer);
                    ((mob_tadpoleAI*)(*itr)->AI())->bIsResetingCage = true;
                    continue;
                }

                else if (Creature* pNewTadpole = (*itr)->SummonCreature(MOB_WINTERFIN_TADPOLE,(*itr)->GetPositionX(),(*itr)->GetPositionY(),(*itr)->GetPositionZ(),(*itr)->GetOrientation(),TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,urand(60000,120000)))
                {
                    pNewTadpole->GetMotionMaster()->MoveFollow(pPlayer, float(urand(1, 4)), 2*M_PI/float(urand(1, 20)));
                    pPlayer->KilledMonsterCredit((*itr)->GetEntry(),(*itr)->GetGUID());
                    (*itr)->ForcedDespawn();
                    if (pPlayer->getGender() == GENDER_MALE)
                        DoScriptText(Speaches[3],pNewTadpole,pPlayer);
                    else DoScriptText(Speaches[4],pNewTadpole,pPlayer);
                    ((mob_tadpoleAI*)pNewTadpole->AI())->bIsFollowing = true;
                }
            }
        }
    }

    lCreatureList.clear();
    // just open the door without despawn
    pGo->SetGoState(GO_STATE_ACTIVE);
    // and make cage not targetable
    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
    return true;
}

enum PrisonBreak
{
    QUEST_PRISON_BREAK          = 11587,
    SPELL_HEARTSTONE_VISUAL     = 45451,
    SPELL_PRISON_BREAK_CREDIT   = 45456,

    SAY_SUCCEDED                = -1999803,
    SAY_FAILED                  = -1999802
};

struct MANGOS_DLL_DECL mob_arcane_prisonerAI : public ScriptedAI
{
    mob_arcane_prisonerAI(Creature* pCreature) : ScriptedAI(pCreature){ Reset();}
    
    bool bSucceded;
    bool bEventDone;
    uint32 m_uiEventTimer;

    void Reset() 
    {
        // small amount of time is needed to let npc fall on the ground
        m_uiEventTimer = 1000;
        if (urand(0, 1) == 1)
            bSucceded = true;
        else bSucceded = false;

        bEventDone = false;
    }

    void UpdateAI (const uint32 uiDiff)
    {
        if (!bEventDone && m_uiEventTimer <= uiDiff)
        {
            // update server with position of NPC after it fall on the ground
            // this will prevent to spawn eventual corpse in the air (cosmetic effect)
            float x,y,z;
            m_creature->GetPosition(x, y, z);
            z = m_creature->GetMap()->GetHeight(x, y, MAX_HEIGHT,false);
            m_creature->Relocate(x, y, z+2);

            if (!bSucceded)
            {
                DoScriptText(SAY_FAILED, m_creature, NULL);
                m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
            else
            {
                if (Player* pPlayer = (Player*)Unit::GetUnit((*m_creature), m_creature->GetCreatorGUID()))
                {
                    DoScriptText(SAY_SUCCEDED, m_creature, pPlayer);
                    if (pPlayer->GetQuestStatus(QUEST_PRISON_BREAK) == QUEST_STATUS_INCOMPLETE)
                        DoCast(pPlayer, SPELL_PRISON_BREAK_CREDIT, true);
                }
                DoCast(m_creature, SPELL_HEARTSTONE_VISUAL, false);
            }
            bEventDone = true;
        }else m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_arcane_prisoner(Creature* pCreature)
{
    return new mob_arcane_prisonerAI(pCreature);
}

enum Lurgglbr
{
    QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS = 11570,

    GO_CAGE                             = 187369,

    SAY_QUEST_ACCEPTED                  = -1999801,
    SAY_ESCORT_START                    = -1999800,
    SAY_OUTSIDE_CAVE                    = -1999799,
    SAY_QUEST_COMPLETE                  = -1999798
};


struct MANGOS_DLL_DECL npc_lurgglbrAI : public npc_escortAI
{
    npc_lurgglbrAI(Creature* pCreature) : npc_escortAI(pCreature){ Reset();}
    

    uint64 m_uiCageGUID;

    void Reset(){}

    void AttackStart(Unit* pWho)
    {
        // if he is not escorted - than that means that he is in cage so disable moving outside
        // shouldn't there be function like isEscorted() ?
        if (!HasEscortState(STATE_ESCORT_NONE) && !HasEscortState(STATE_ESCORT_PAUSED) &&
            !HasEscortState(STATE_ESCORT_RETURNING) && !HasEscortState(STATE_ESCORT_ESCORTING))
        {
            if (m_creature->Attack(pWho, true))
            {
                m_creature->AddThreat(pWho);
                m_creature->SetInCombatWith(pWho);
                pWho->SetInCombatWith(m_creature);
                SetCombatMovement(false);
            }
        }else
        {
            SetCombatMovement(true);
            npc_escortAI::AttackStart(pWho);
        }
    }
          
    void WaypointReached(uint32 uiPointId)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;

        switch(uiPointId)
        {
            case 0:
                m_creature->SetFacingToObject(pPlayer);
                DoScriptText(SAY_ESCORT_START, m_creature, pPlayer);
                if (GameObject* pCage = m_creature->GetMap()->GetGameObject(m_uiCageGUID))
                        pCage->SetGoState(GO_STATE_READY);
                break;
            case 13:
                m_creature->SetFacingToObject(pPlayer);
                DoScriptText(SAY_OUTSIDE_CAVE, m_creature, pPlayer);
                break;

            case 25:
                m_creature->SetFacingToObject(pPlayer);
                DoScriptText(SAY_QUEST_COMPLETE, m_creature, pPlayer);
                pPlayer->GroupEventHappens(QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS, m_creature);
                SetEscortPaused(true);
                break;

            default: break;
        }
    }
};

bool QuestAccept_npc_lurgglbr(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (!pPlayer || !pQuest)
        return false;

    if (pQuest->GetQuestId() == QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS)
    {
        if (npc_lurgglbrAI* pEscortAI = dynamic_cast<npc_lurgglbrAI*>(pCreature->AI()))
        {
            DoScriptText(SAY_QUEST_ACCEPTED, pCreature, pPlayer);
            pCreature->setFaction(FACTION_ESCORT_N_FRIEND_ACTIVE);
            pEscortAI->Start(false, false, pPlayer->GetGUID(), pQuest, true);
            if (GameObject* pCage = GetClosestGameObjectWithEntry(pCreature, GO_CAGE, INTERACTION_DISTANCE))
            {
                pCage->SetGoState(GO_STATE_ACTIVE);
                ((npc_lurgglbrAI*)pCreature->AI())->m_uiCageGUID = pCage->GetGUID();
            }

        }
    }
    return true;
}

CreatureAI* GetAI_npc_lurgglbr(Creature* pCreature)
{
    return new npc_lurgglbrAI(pCreature);
}

void AddSC_borean_tundra()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_lurgglbr";
    newscript->GetAI = &GetAI_npc_lurgglbr;
    newscript->pQuestAccept = &QuestAccept_npc_lurgglbr;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_arcane_prisoner";
    newscript->GetAI = &GetAI_mob_arcane_prisoner;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_blue_drake_egg";
    newscript->pGOHello = &GOHello_go_blue_drake_egg;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tadpole_cage";
    newscript->pGOHello = &GOHello_go_tadpole_cage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_tadpole";
    newscript->GetAI = &GetAI_mob_tadpole;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_elder";
    newscript->GetAI = &GetAI_mob_elder;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_fizzcrank_fullthrottle";
    newscript->pGossipHello = &GossipHello_npc_fizzcrank_fullthrottle;
    newscript->pGossipSelect = &GossipSelect_npc_fizzcrank_fullthrottle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_iruk";
    newscript->pGossipHello = &GossipHello_npc_iruk;
    newscript->pGossipSelect = &GossipSelect_npc_iruk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_kara_thricestar";
    newscript->pGossipHello = &GossipHello_npc_kara_thricestar;
    newscript->pGossipSelect = &GossipSelect_npc_kara_thricestar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_robot_reprogrammed";
    newscript->pEffectDummyCreature = &EffectDummyCreature_npc_robot_reprogrammed;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_overseer";
    newscript->GetAI = &GetAI_mob_overseer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_surristrasz";
    newscript->pGossipHello = &GossipHello_npc_surristrasz;
    newscript->pGossipSelect = &GossipSelect_npc_surristrasz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tiare";
    newscript->pGossipHello = &GossipHello_npc_tiare;
    newscript->pGossipSelect = &GossipSelect_npc_tiare;
    newscript->RegisterSelf();
}
