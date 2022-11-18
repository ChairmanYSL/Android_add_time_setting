package com.xgd.smartpos.manager.system;

interface ITeleListener {
    void onStateChanged(in Map state);
    void onStrengthChanged(in Map strength);
    void onServiceStateChanged(int id, String operatorName);
}
