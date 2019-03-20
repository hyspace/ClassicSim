#include "ExtraAttackInstantProc.h"

#include "Character.h"
#include "ExtraAttackOnNextSwingBuff.h"
#include "ProcInfo.h"

ExtraAttackInstantProc::ExtraAttackInstantProc(Character* pchar,
                                               const QString& proc_name,
                                               const QString &icon,
                                               const QVector<ProcInfo::Source>& proc_sources,
                                               const double proc_rate, const int num_attacks) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    extra_attack_buff(nullptr),
    num_attacks(num_attacks)
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
}

ExtraAttackInstantProc::~ExtraAttackInstantProc() = default;

void ExtraAttackInstantProc::proc_effect() {
    if (extra_attack_buff != nullptr)
        proc_from_next_swing_effect();
    else
        proc_from_instant_effect();
}

void ExtraAttackInstantProc::set_extra_attack_buff(ExtraAttackOnNextSwingBuff* buff) {
    this->extra_attack_buff = buff;
}

void ExtraAttackInstantProc::proc_from_next_swing_effect() {
    assert(extra_attack_buff != nullptr);
    assert(extra_attack_buff->is_active());

    while (extra_attack_buff->is_active()) {
        pchar->run_extra_mh_attack();
        extra_attack_buff->use_charge();
    }
}

void ExtraAttackInstantProc::proc_from_instant_effect() {
    assert(extra_attack_buff == nullptr);

    for (int i = 0; i < num_attacks; ++i)
        pchar->run_extra_mh_attack();
}