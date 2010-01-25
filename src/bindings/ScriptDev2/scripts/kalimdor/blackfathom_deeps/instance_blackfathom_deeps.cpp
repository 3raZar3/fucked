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
SDName: Instance_Blackfathom_Deeps
SD%Complete: 50
SDComment:
SDCategory: Blackfathom Deeps
EndScriptData */

#include "precompiled.h"
#include "blackfathom_deeps.h"

/* Encounter 0 = Twilight Lord Kelris
   Encounter 1 = Shrine event
   Must kill twilight lord for shrine event to be possible
 */

struct MANGOS_DLL_DECL instance_blackfathom_deeps : public ScriptedInstance
{
    instance_blackfathom_deeps(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint64 m_uiTwilightLordKelrisGUID;
    uint64 m_uiShrineOfGelihastGUID;
    uint64 m_uiAltarOfTheDeepsGUID;
    uint64 m_uiPortalGUID;
    uint32 m_uiSpawnServantTimer;
    // this values shouldn't drop below 0 but at any case lets make them int type
    int8  m_uiAddsCount;
    int8  m_uiShrinesLit;

    uint64 m_uiShrineGUID[SHRINES_COUNT];
    uint32 m_auiEncounter[MAX_ENCOUNTER];

    void Initialize()
    {
        memset(&m_uiShrineGUID, 0, sizeof(m_uiShrineGUID));
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        m_uiTwilightLordKelrisGUID = 0;
        m_uiShrineOfGelihastGUID = 0;
        m_uiAltarOfTheDeepsGUID = 0;
        m_uiPortalGUID = 0;
        m_uiSpawnServantTimer = 0;
        m_uiAddsCount = 0;
        m_uiShrinesLit = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        if (pCreature->GetEntry() == NPC_KELRIS)
            m_uiKelrisGUID = pCreature->GetGUID();
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_SHRINE_1:
            case GO_SHRINE_2:
            case GO_SHRINE_3:
            case GO_SHRINE_4:
                for (uint8 i = 0; i < SHRINES_COUNT; ++i)
                {
                    if (m_uiShrineGUID[i] < 1)
                    {
                        m_uiShrineGUID[i] = pGo->GetGUID();
                        break;
                    }
                }
                pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            
            case 103015:    m_uiShrineOfGelihastGUID = pGo->GetGUID();  break;
            case 103016:    m_uiAltarOfTheDeepsGUID = pGo->GetGUID();   break;
            
        }
    }

    bool CanOpenEndDoor()
    {
        if (m_auiEncounter[0] != DONE)
            return false;

        if (m_auiEncounter[2] == DONE && m_auiEncounter[3] == DONE && m_auiEncounter[4] == DONE && m_auiEncounter[5] == DONE)
            return true;

        return false;
    }

    void SpawnServants()
    {
        if (Creature* pKelris = instance->GetCreature(m_uiKelrisGUID))
        {
            float fX_resp, fY_resp, fZ_resp;
            pKelris->GetRespawnCoord(fX_resp, fY_resp, fZ_resp);

            for(uint8 i = 0; i < 5 ; ++i)
            {
                // this part gets a random position at circumference point in a circle
                // fRadius is how far from center to calculate.
                // here we use kelris's close point coords as base and then move the summoned to the location of his respawn coords
                float fRadius = 30.0f;
                float fAngle = 2.0 * M_PI * rand_norm();

                float fX, fY, fZ;

                fRadius *= sqrt(rand_norm());

                pKelris->GetClosePoint(fX, fY, fZ, 0.0f, fRadius, fAngle);

                if (Creature* pServant = pKelris->SummonCreature(NPC_SERVANT, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000))
                    pServant->GetMotionMaster()->MovePoint(0, fX_resp, fY_resp, fZ_resp);
            }

        }
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_KELRIS:                               // eventAI must set instance data (1,3) at his death
                if (m_auiEncounter[0] != DONE && uiData == DONE)
                if (uiData == DONE)
                    for (uint8 i = 0; i < SHRINES_COUNT; ++i)
                    {
                        if (GameObject* pGo = instance->GetGameObject(m_uiShrineGUID[i]))
                            pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                    }

                m_auiEncounter[0] = uiData;
                break;

            case TYPE_SHRINE_EVENT:
                if (uiData == IN_PROGRESS)
                    ++m_uiShrinesLit;

            {
                switch(uiData)
                {
                    case GO_SHRINE_1:
                        m_auiEncounter[2] = DONE;
                break;
              
            case DATA_SHRINE_SUMMONS:
                // used to manage summons
                // if TYPE_SHRINE_EVENT is not in progress lets return
                // there are exists mobs with the same entry not related to event
                if (m_auiEncounter[1] != IN_PROGRESS)
                    break;

                // case shrine summoned one more creature
                if (uiData == IN_PROGRESS)
                    ++m_uiAddsCount;

                // case summon just died
                if (uiData == SPECIAL)
                {
                    --m_uiAddsCount;
                    // if one more summon died lets check number of those that are alive
                    // if all shrines are lit and none of adds is alive we can assume that event is done
                    if (m_uiAddsCount < 1 && m_uiShrinesLit >= SHRINES_COUNT)
                        uiData = DONE;
                }
                // in case event is done lets open the door and finish TYPE_SHRINE_EVENT
                if (uiData == DONE)
                {
                    m_auiEncounter[2] = DONE;
                    DoUseDoorOrButton(m_uiMainDoorGUID);
                }
                m_auiEncounter[2] = uiData;
                break;
        }
    }
};

InstanceData* GetInstanceData_instance_blackfathom_deeps(Map* pMap)
{
    return new instance_blackfathom_deeps(pMap);
}

bool GOHello_go_fire_of_akumai(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return true;

    if (pInstance->GetData(TYPE_KELRIS) == DONE)
    {
        pInstance->SetData(TYPE_SHRINE, pGo->GetEntry());
        return false;
    }

    return true;
}

void AddSC_instance_blackfathom_deeps()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_blackfathom_deeps";
    newscript->GetInstanceData = &GetInstanceData_instance_blackfathom_deeps;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_fire_of_akumai";
    newscript->pGOHello = &GOHello_go_fire_of_akumai;
    newscript->RegisterSelf();
}
