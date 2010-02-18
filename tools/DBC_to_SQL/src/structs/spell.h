/*
 * DBC to SQL Converter
 * Copyright (C) 2009  David Vas, Anubisss
 * <http://code.google.com/p/dbctosql/>
 * updated by Przemratajczak

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SPEL_H__
#define __SPEL_H__

char const *SPELL_DBC   = "Spell.dbc";
char const *SPELL_SQL   = "spell_dbc.sql";
char const *SPELL_TABLE = "dbc_spell";

#define SPELL_DBC_CLIENT_BUILD  11159 // 3.3.0a

#define SPELL_DBC_COLUMN_NUMS   240
#define SPELL_DBC_ROWS_NUMS     74446

// Spell.dbc struct: MaNGOS 9310
char const *spell_translation[SPELL_DBC_COLUMN_NUMS][2] =
{
    {"uint32",   "Id"},                                           // 0        m_ID
    {"uint32",   "Category"},                                     // 1        m_category
    {"uint32",   "Dispel"},                                       // 2        m_dispelType
    {"uint32",   "Mechanic"},                                     // 3        m_mechanic
    {"uint32",   "Attributes"},                                   // 4        m_attribute
    {"uint32",   "AttributesEx"},                                 // 5        m_attributesEx
    {"uint32",   "AttributesEx2"},                                // 6        m_attributesExB
    {"uint32",   "AttributesEx3"},                                // 7        m_attributesExC
    {"uint32",   "AttributesEx4"},                                // 8        m_attributesExD
    {"uint32",   "AttributesEx5"},                                // 9        m_attributesExE
    {"uint32",   "AttributesEx6"},                                // 10       m_attributesExF
    {"uint32",   "unk_320_1"},                                    // 11       3.2.0 (0x20 - totems, 0x4 - paladin auras, etc...)
    {"uint32",   "Stances"},                                      // 12       m_shapeshiftMask
    {"uint32",   "unk_320_2"},                                    // 13       3.2.0
    {"uint32",   "StancesNot"},                                   // 14       m_shapeshiftExclude
    {"uint32",   "unk_320_3"},                                    // 15       3.2.0
    {"uint32",   "Targets"},                                      // 16       m_targets
    {"uint32",   "TargetCreatureType"},                           // 17       m_targetCreatureType
    {"uint32",   "RequiresSpellFocus"},                           // 18       m_requiresSpellFocus
    {"uint32",   "FacingCasterFlags"},                            // 19       m_facingCasterFlags
    {"uint32",   "CasterAuraState"},                              // 20       m_casterAuraState
    {"uint32",   "TargetAuraState"},                              // 21       m_targetAuraState
    {"uint32",   "CasterAuraStateNot"},                           // 22       m_excludeCasterAuraState
    {"uint32",   "TargetAuraStateNot"},                           // 23       m_excludeTargetAuraState
    {"uint32",   "casterAuraSpell"},                              // 24       m_casterAuraSpell
    {"uint32",   "targetAuraSpell"},                              // 25       m_targetAuraSpell
    {"uint32",   "excludeCasterAuraSpell"},                       // 26       m_excludeCasterAuraSpell
    {"uint32",   "excludeTargetAuraSpell"},                       // 27       m_excludeTargetAuraSpell
    {"uint32",   "CastingTimeIndex"},                             // 28       m_castingTimeIndex
    {"uint32",   "RecoveryTime"},                                 // 29       m_recoveryTime
    {"uint32",   "CategoryRecoveryTime"},                         // 30       m_categoryRecoveryTime
    {"uint32",   "InterruptFlags"},                               // 31       m_interruptFlags
    {"uint32",   "AuraInterruptFlags"},                           // 32       m_auraInterruptFlags
    {"uint32",   "ChannelInterruptFlags"},                        // 33       m_channelInterruptFlags
    {"uint32",   "procFlags"},                                    // 34       m_procTypeMask
    {"uint32",   "procChance"},                                   // 35       m_procChance
    {"uint32",   "procCharges"},                                  // 36       m_procCharges
    {"uint32",   "maxLevel"},                                     // 37       m_maxLevel
    {"uint32",   "baseLevel"},                                    // 38       m_baseLevel
    {"uint32",   "spellLevel"},                                   // 39       m_spellLevel
    {"uint32",   "DurationIndex"},                                // 40       m_durationIndex
    {"uint32",   "powerType"},                                    // 41       m_powerType
    {"uint32",   "manaCost"},                                     // 42       m_manaCost
    {"uint32",   "manaCostPerlevel"},                             // 43       m_manaCostPerLevel
    {"uint32",   "manaPerSecond"},                                // 44       m_manaPerSecond
    {"uint32",   "manaPerSecondPerLevel"},                        // 45       m_manaPerSecondPerLeve
    {"uint32",   "rangeIndex"},                                   // 46       m_rangeIndex
    {"float",    "speed"},                                        // 47       m_speed
    {"uint32",   "modalNextSpell"},                               // 48       m_modalNextSpell not used
    {"uint32",   "StackAmount"},                                  // 49       m_cumulativeAura
    {"uint32",   "Totem_1"},                                      // 50       m_totem
    {"uint32",   "Totem_2"},                                      // 51       m_totem
    {"int32",    "Reagent_1"},                                    // 52       m_reagent
    {"int32",    "Reagent_2"},                                    // 53       m_reagent
    {"int32",    "Reagent_3"},                                    // 54       m_reagent
    {"int32",    "Reagent_4"},                                    // 55       m_reagent
    {"int32",    "Reagent_5"},                                    // 56       m_reagent
    {"int32",    "Reagent_6"},                                    // 57       m_reagent
    {"int32",    "Reagent_7"},                                    // 58       m_reagent
    {"int32",    "Reagent_8"},                                    // 59       m_reagent
    {"uint32",   "ReagentCount_1"},                               // 60       m_reagentCount
    {"uint32",   "ReagentCount_2"},                               // 61       m_reagentCount
    {"uint32",   "ReagentCount_3"},                               // 62       m_reagentCount
    {"uint32",   "ReagentCount_4"},                               // 63       m_reagentCount
    {"uint32",   "ReagentCount_5"},                               // 64       m_reagentCount
    {"uint32",   "ReagentCount_6"},                               // 65       m_reagentCount
    {"uint32",   "ReagentCount_7"},                               // 66       m_reagentCount
    {"uint32",   "ReagentCount_8"},                               // 67       m_reagentCount
    {"int32",    "EquippedItemClass"},                            // 68       m_equippedItemClass (value)
    {"int32",    "EquippedItemSubClassMask"},                     // 69       m_equippedItemSubclass (mask)
    {"int32",    "EquippedItemInventoryTypeMask"},                // 70       m_equippedItemInvTypes (mask)
    {"uint32",   "Effect_1"},                                     // 71       m_effect
    {"uint32",   "Effect_2"},                                     // 72       m_effect
    {"uint32",   "Effect_3"},                                     // 73       m_effect
    {"int32",    "EffectDieSides_1"},                             // 74       m_effectDieSides
    {"int32",    "EffectDieSides_2"},                             // 75       m_effectDieSides
    {"int32",    "EffectDieSides_3"},                             // 76       m_effectDieSides
    {"uint32",   "EffectBaseDice_1"},                             // 77       m_effectBaseDice
    {"uint32",   "EffectBaseDice_2"},                             // 78       m_effectBaseDice
    {"uint32",   "EffectBaseDice_3"},                             // 79       m_effectBaseDice
    {"float",    "EffectDicePerLevel_1"},                         // 80       m_effectDicePerLevel
    {"float",    "EffectDicePerLevel_2"},                         // 81       m_effectDicePerLevel
    {"float",    "EffectDicePerLevel_3"},                         // 82       m_effectDicePerLevel
    {"float",    "EffectRealPointsPerLevel_1"},                   // 83       m_effectRealPointsPerLevel
    {"float",    "EffectRealPointsPerLevel_2"},                   // 84       m_effectRealPointsPerLevel
    {"float",    "EffectRealPointsPerLevel_3"},                   // 85       m_effectRealPointsPerLevel
    {"int32",    "EffectBasePoints_1"},                           // 86       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    {"int32",    "EffectBasePoints_2"},                           // 87       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    {"int32",    "EffectBasePoints_3"},                           // 88       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    {"uint32",   "EffectMechanic_1"},                             // 89       m_effectMechanic
    {"uint32",   "EffectMechanic_2"},                             // 90       m_effectMechanic
    {"uint32",   "EffectMechanic_3"},                             // 91       m_effectMechanic
    {"uint32",   "EffectImplicitTargetA_1"},                      // 92       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetA_2"},                      // 93       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetA_3"},                      // 94       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetB_1"},                      // 95       m_implicitTargetB
    {"uint32",   "EffectImplicitTargetB_2"},                      // 96       m_implicitTargetB
    {"uint32",   "EffectImplicitTargetB_3"},                      // 97       m_implicitTargetB
    {"uint32",   "EffectRadiusIndex_1"},                          // 98       m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectRadiusIndex_2"},                          // 99       m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectRadiusIndex_3"},                          // 100      m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectApplyAuraName_1"},                        // 101      m_effectAura
    {"uint32",   "EffectApplyAuraName_2"},                        // 102      m_effectAura
    {"uint32",   "EffectApplyAuraName_3"},                        // 103      m_effectAura
    {"uint32",   "EffectAmplitude_1"},                            // 104      m_effectAuraPeriod
    {"uint32",   "EffectAmplitude_2"},                            // 105      m_effectAuraPeriod
    {"uint32",   "EffectAmplitude_3"},                            // 106      m_effectAuraPeriod
    {"float",    "EffectMultipleValue_1"},                        // 107      m_effectAmplitude
    {"float",    "EffectMultipleValue_2"},                        // 108      m_effectAmplitude
    {"float",    "EffectMultipleValue_3"},                        // 109      m_effectAmplitude
    {"uint32",   "EffectChainTarget_1"},                          // 110      m_effectChainTargets
    {"uint32",   "EffectChainTarget_2"},                          // 111      m_effectChainTargets
    {"uint32",   "EffectChainTarget_3"},                          // 112      m_effectChainTargets
    {"uint32",   "EffectItemType_1"},                             // 113      m_effectItemType
    {"uint32",   "EffectItemType_2"},                             // 114      m_effectItemType
    {"uint32",   "EffectItemType_3"},                             // 115      m_effectItemType
    {"int32",    "EffectMiscValue_1"},                            // 116      m_effectMiscValue
    {"int32",    "EffectMiscValue_2"},                            // 117      m_effectMiscValue
    {"int32",    "EffectMiscValue_3"},                            // 118      m_effectMiscValue
    {"int32",    "EffectMiscValueB_1"},                           // 119      m_effectMiscValueB
    {"int32",    "EffectMiscValueB_2"},                           // 120      m_effectMiscValueB
    {"int32",    "EffectMiscValueB_3"},                           // 121      m_effectMiscValueB
    {"uint32",   "EffectTriggerSpell_1"},                         // 122      m_effectTriggerSpell
    {"uint32",   "EffectTriggerSpell_2"},                         // 123      m_effectTriggerSpell
    {"uint32",   "EffectTriggerSpell_3"},                         // 124      m_effectTriggerSpell
    {"float",    "EffectPointsPerComboPoint_1"},                  // 125      m_effectPointsPerCombo
    {"float",    "EffectPointsPerComboPoint_2"},                  // 126      m_effectPointsPerCombo
    {"float",    "EffectPointsPerComboPoint_3"},                  // 127      m_effectPointsPerCombo
    {"uint32",   "EffectSpellClassMaskA_1"},                      // 128      m_effectSpellClassMaskA
    {"uint32",   "EffectSpellClassMaskA_2"},                      // 129      m_effectSpellClassMaskA
    {"uint32",   "EffectSpellClassMaskA_3"},                      // 130      m_effectSpellClassMaskA
    {"uint32",   "EffectSpellClassMaskB_1"},                      // 131      m_effectSpellClassMaskB
    {"uint32",   "EffectSpellClassMaskB_2"},                      // 132      m_effectSpellClassMaskB
    {"uint32",   "EffectSpellClassMaskB_3"},                      // 133      m_effectSpellClassMaskB
    {"uint32",   "EffectSpellClassMaskC_1"},                      // 134      m_effectSpellClassMaskC
    {"uint32",   "EffectSpellClassMaskC_2"},                      // 135      m_effectSpellClassMaskC
    {"uint32",   "EffectSpellClassMaskC_3"},                      // 136      m_effectSpellClassMaskC
    {"uint32",   "SpellVisual_1"},                                // 137      m_spellVisualID
    {"uint32",   "SpellVisual_2"},                                // 138      m_spellVisualID
    {"uint32",   "SpellIconID"},                                  // 139      m_spellIconID
    {"uint32",   "activeIconID"},                                 // 140      m_activeIconID
    {"uint32",   "spellPriority"},                                // 141      m_spellPriority not used
    {"char*",    "SpellName_1"},                                  // 142      m_name_lang
    {"char*",    "SpellName_2"},                                  // 143      m_name_lang
    {"char*",    "SpellName_3"},                                  // 144      m_name_lang
    {"char*",    "SpellName_4"},                                  // 145      m_name_lang
    {"char*",    "SpellName_5"},                                  // 146      m_name_lang
    {"char*",    "SpellName_6"},                                  // 147      m_name_lang
    {"char*",    "SpellName_7"},                                  // 148      m_name_lang
    {"char*",    "SpellName_8"},                                  // 149      m_name_lang
    {"char*",    "SpellName_9"},                                  // 150      m_name_lang
    {"char*",    "SpellName_10"},                                 // 151      m_name_lang
    {"char*",    "SpellName_11"},                                 // 152      m_name_lang
    {"char*",    "SpellName_12"},                                 // 153      m_name_lang
    {"char*",    "SpellName_13"},                                 // 154      m_name_lang
    {"char*",    "SpellName_14"},                                 // 155      m_name_lang
    {"char*",    "SpellName_15"},                                 // 156      m_name_lang
    {"char*",    "SpellName_16"},                                 // 157      m_name_lang
    {"uint32",   "SpellNameFlag"},                                // 158      not used
    {"char*",    "Rank_1"},                                       // 159      m_nameSubtext_lang
    {"char*",    "Rank_2"},                                       // 160      m_nameSubtext_lang
    {"char*",    "Rank_3"},                                       // 161      m_nameSubtext_lang
    {"char*",    "Rank_4"},                                       // 162      m_nameSubtext_lang
    {"char*",    "Rank_5"},                                       // 163      m_nameSubtext_lang
    {"char*",    "Rank_6"},                                       // 164      m_nameSubtext_lang
    {"char*",    "Rank_7"},                                       // 165      m_nameSubtext_lang
    {"char*",    "Rank_8"},                                       // 166      m_nameSubtext_lang
    {"char*",    "Rank_9"},                                       // 167      m_nameSubtext_lang
    {"char*",    "Rank_10"},                                      // 168      m_nameSubtext_lang
    {"char*",    "Rank_11"},                                      // 169      m_nameSubtext_lang
    {"char*",    "Rank_12"},                                      // 170      m_nameSubtext_lang
    {"char*",    "Rank_13"},                                      // 171      m_nameSubtext_lang
    {"char*",    "Rank_14"},                                      // 172      m_nameSubtext_lang
    {"char*",    "Rank_15"},                                      // 173      m_nameSubtext_lang
    {"char*",    "Rank_16"},                                      // 174      m_nameSubtext_lang
    {"uint32",   "RankFlags"},                                    // 175      not used
    {"text",     "Description_1"},                                // 176      m_description_lang not used
    {"text",     "Description_2"},                                // 177      m_description_lang not used
    {"text",     "Description_3"},                                // 178      m_description_lang not used
    {"text",     "Description_4"},                                // 179      m_description_lang not used
    {"text",     "Description_5"},                                // 180      m_description_lang not used
    {"text",     "Description_6"},                                // 181      m_description_lang not used
    {"text",     "Description_7"},                                // 182      m_description_lang not used
    {"text",     "Description_8"},                                // 183      m_description_lang not used
    {"text",     "Description_9"},                                // 184      m_description_lang not used
    {"text",     "Description_10"},                               // 185      m_description_lang not used
    {"text",     "Description_11"},                               // 186      m_description_lang not used
    {"text",     "Description_12"},                               // 187      m_description_lang not used
    {"text",     "Description_13"},                               // 188      m_description_lang not used
    {"text",     "Description_14"},                               // 189      m_description_lang not used
    {"text",     "Description_15"},                               // 190      m_description_lang not used
    {"text",     "Description_16"},                               // 191      m_description_lang not used
    {"uint32",   "DescriptionFlags"},                             // 192      not used
    {"char*",    "ToolTip_1"},                                    // 193      m_auraDescription_lang not used
    {"char*",    "ToolTip_2"},                                    // 194      m_auraDescription_lang not used
    {"char*",    "ToolTip_3"},                                    // 195      m_auraDescription_lang not used
    {"char*",    "ToolTip_4"},                                    // 196      m_auraDescription_lang not used
    {"char*",    "ToolTip_5"},                                    // 197      m_auraDescription_lang not used
    {"char*",    "ToolTip_6"},                                    // 198      m_auraDescription_lang not used
    {"char*",    "ToolTip_7"},                                    // 199      m_auraDescription_lang not used
    {"char*",    "ToolTip_8"},                                    // 200      m_auraDescription_lang not used
    {"char*",    "ToolTip_9"},                                    // 201      m_auraDescription_lang not used
    {"char*",    "ToolTip_10"},                                   // 202      m_auraDescription_lang not used
    {"char*",    "ToolTip_11"},                                   // 203      m_auraDescription_lang not used
    {"char*",    "ToolTip_12"},                                   // 204      m_auraDescription_lang not used
    {"char*",    "ToolTip_13"},                                   // 205      m_auraDescription_lang not used
    {"char*",    "ToolTip_14"},                                   // 206      m_auraDescription_lang not used
    {"char*",    "ToolTip_15"},                                   // 207      m_auraDescription_lang not used
    {"char*",    "ToolTip_16"},                                   // 208      m_auraDescription_lang not used
    {"uint32",   "ToolTipFlags"},                                 // 209      not used
    {"uint32",   "ManaCostPercentage"},                           // 210      m_manaCostPct
    {"uint32",   "StartRecoveryCategory"},                        // 211      m_startRecoveryCategory
    {"uint32",   "StartRecoveryTime"},                            // 212      m_startRecoveryTime
    {"uint32",   "MaxTargetLevel"},                               // 213      m_maxTargetLevel
    {"uint32",   "SpellFamilyName"},                              // 214      m_spellClassSet
    {"flag96",   "SpellFamilyFlags_1"},                           // 215      m_spellClassMask NOTE: size is 12 bytes!!!
    {"flag96",   "SpellFamilyFlags_2"},                           // 216      m_spellClassMask NOTE: size is 12 bytes!!!
    {"uint32",   "SpellFamilyFlags2"},                            // 217      addition to m_spellClassMask
    {"uint32",   "MaxAffectedTargets"},                           // 218      m_maxTargets
    {"uint32",   "DmgClass"},                                     // 219      m_defenseType
    {"uint32",   "PreventionType"},                               // 220      m_preventionType
    {"uint32",   "StanceBarOrder"},                               // 221      m_stanceBarOrder not used
    {"float",    "DmgMultiplier_1"},                              // 222      m_effectChainAmplitude
    {"float",    "DmgMultiplier_2"},                              // 223      m_effectChainAmplitude
    {"float",    "DmgMultiplier_3"},                              // 224      m_effectChainAmplitude
    {"uint32",   "MinFactionId"},                                 // 225      m_minFactionID not used
    {"uint32",   "MinReputation"},                                // 226      m_minReputation not used
    {"uint32",   "RequiredAuraVision"},                           // 227      m_requiredAuraVision not used
    {"uint32",   "TotemCategory_1"},                              // 228      m_requiredTotemCategoryID
    {"uint32",   "TotemCategory_2"},                              // 229      m_requiredTotemCategoryID
    {"int32",    "AreaGroupId"},                                  // 230      m_requiredAreaGroupId
    {"uint32",   "SchoolMask"},                                   // 231      m_schoolMask
    {"uint32",   "runeCostID"},                                   // 232      m_runeCostID
    {"uint32",   "spellMissileID"},                               // 233      m_spellMissileID not used
    {"uint32",   "PowerDisplayId"},                               // 234      PowerDisplay.dbc, new in 3.1
    {"float",    "unk_320_4_1"},                                  // 235      3.2.0
    {"float",    "unk_320_4_2"},                                  // 236      3.2.0
    {"float",    "unk_320_4_3"},                                  // 237      3.2.0
    {"uint32",   "spellDescriptionVariableID"},                   // 238      3.2.0
    {"uint32",   "SpellDifficultyId"}                             // 239      3.3.0
};

char const *SPELL_TABLE_INDEX = spell_translation[0][1];

#endif
