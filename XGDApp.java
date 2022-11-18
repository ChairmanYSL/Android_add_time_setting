package com.nexgo.emv;

import android.app.Application;
import android.util.Log;

import com.nexgo.emv.beeper.Beeper;
import com.nexgo.emv.key.PosKeyboard;
import com.nexgo.emv.lcd.PosLcd;
import com.nexgo.emv.print.PrinterManager;
import com.xgd.smartpos.manager.system.ISystemManager;

public class XGDApp extends Application {

    private static XGDApp singleton = new XGDApp();
    private PosLcd tm_lcd;
    private PosKeyboard tm_keypad;
    private PrinterManager printerManager;
    private Beeper mbeeper;
    private ISystemManager systemManager;
    public MainActivity mainActivity;

    public XGDApp(){
        Log.e("XGDApp", "==============   XGDApp ====================");
    }


    public static XGDApp getInstance() {
        return singleton;
    }


    public PosLcd getPosLcd() {
        return tm_lcd;
    }

    public void setPosLcd(PosLcd posLcd) {
        this.tm_lcd = posLcd;
    }

    public PosKeyboard getPosKeyboard() {
        return tm_keypad;
    }

    public void setPosKeyboard(PosKeyboard posKeyboard) {
        this.tm_keypad = posKeyboard;
    }

    public PrinterManager getPrinterManager() {
        return printerManager;
    }

    public void setPrinterManager(PrinterManager printerManager) {
        this.printerManager = printerManager;
    }

    public void setBeeper(Beeper beeper) {
        this.mbeeper = beeper;
    }

    public Beeper getBeeper() {
        return mbeeper;
    }

    public void setSystemManager(ISystemManager systemManager){
        this.systemManager = systemManager;
    }
    public ISystemManager getSystemManager(){
        return systemManager;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        MyCrashHandler.getInstance().init(this);
    }
}
