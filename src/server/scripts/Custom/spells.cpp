#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "ScriptMgr.h"

class spell_oracle_wolvar : public SpellScriptLoader
{
    public:
        spell_oracle_wolvar() : SpellScriptLoader("spell_oracle_wolvar") { }

        class spell_oracle_wolvar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_oracle_wolvar_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* pTarget = GetHitUnit())
                {
                    if (pTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    int32  rep_change = GetSpellInfo()->EffectBasePoints[EFFECT_1] + 1;

                    uint32 faction_id = GetSpellInfo()->EffectBasePoints[EFFECT_0] + 1;

                    FactionEntry const* factionEntry = sFactionStore.LookupEntry(faction_id);

                    if (!factionEntry)
                        return;

                    pTarget->ToPlayer()->GetReputationMgr().SetReputation(factionEntry, rep_change);
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_oracle_wolvar_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_oracle_wolvar_SpellScript;
        }
};


class spell_sunreaver_disguise : public SpellScriptLoader
{
    public:
        spell_sunreaver_disguise() : SpellScriptLoader("spell_sunreaver_disguise") { }

        class spell_sunreaver_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sunreaver_disguise_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                // Change model
                if (Unit *unitTarget = GetHitUnit())
                {
                    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (GetSpellInfo()->Id == 69672)
                        unitTarget->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 70972 : 70971, true, NULL);
                    else
                        unitTarget->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 70974 : 70973, true, NULL);
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_sunreaver_disguise_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_sunreaver_disguise_SpellScript;
        }
};


class spell_divine_intervention : public SpellScriptLoader
{
    public:
        spell_divine_intervention() : SpellScriptLoader("spell_divine_intervention") { }

        class spell_divine_interventionSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_divine_interventionSpellScript);

            void HandleBeforeHit()
            {
                if (Unit * target = GetHitUnit())
                {
                   if (target->GetTypeId() != TYPEID_PLAYER)
                   {
                       PreventHitEffect(EFFECT_0);
                       PreventHitEffect(EFFECT_1);
                   }
                }
            }


            void Register()
            {
                BeforeHit += SpellHitFn(spell_divine_interventionSpellScript::HandleBeforeHit);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_divine_interventionSpellScript();
        }
};

void AddSC_custom_spells()
{
    new spell_oracle_wolvar;
    new spell_sunreaver_disguise;
    new spell_divine_intervention;
}
