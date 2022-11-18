package com.nexgo.emv;
//20180907 ADD START
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.Build;
import android.os.Environment;
import android.util.Log;
//END

import android.util.Log;

import com.nexgo.emv.print.AlignEnum;
import com.nexgo.emv.print.FontSizeEnum;
import com.nexgo.emv.util.SystemServiceHelper;//20180907 ADD START
import java.io.File;
import java.nio.ByteBuffer;
import android.widget.ImageView;

/**
 * Created by 28070 on 2016/5/19.
 */
public class DeviceOpera {

//    private static DeviceOpera singletonInstance = new DeviceOpera();

    public DeviceOpera() {
    }

//    public static DeviceOpera getInstance(){
//        return singletonInstance;
//    }

    public int testCallJava(int i) {

        Log.e("CallJava", "" + i);
        return i;
    }

    public void Lcd_Cls() {
        XGDApp.getInstance().getPosLcd().Lcd_Cls();
    }

    public void Lcd_Printf(String dispText) {

        //Log.e("CallJava", dispText);

        try {
            XGDApp.getInstance().getPosLcd().Lcd_Printf(dispText);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Lcd_ClearLine(int startLine, int endLine) {
        XGDApp.getInstance().getPosLcd().Lcd_ClearLine(startLine, endLine);
    }

    public void Lcd_GotoXY(int line, int col) {
        XGDApp.getInstance().getPosLcd().Lcd_GotoXY(line, col);
    }

    public void Lcd_PrintfXY(int line, int col, String dispText, int attr) {
        try {
            XGDApp.getInstance().getPosLcd().Lcd_PrintfXY(line, col, dispText, attr);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Lcd_SetFont(int FontType) {
        XGDApp.getInstance().getPosLcd().Lcd_SetFont(FontType);
    }

    //按键处理
    public void Kb_Flush() {
        XGDApp.getInstance().getPosKeyboard().Kb_Flush();
    }

    public void KbStdin(int keyCode) {
        XGDApp.getInstance().getPosKeyboard().KbStdin(keyCode);
    }

    public int Kb_Hit() {
        return XGDApp.getInstance().getPosKeyboard().Kb_Hit();
    }

    public int Kb_GetKey() {
        if (XGDApp.getInstance().getPosKeyboard().Kb_Hit() == 0)
            return 0;
        return XGDApp.getInstance().getPosKeyboard().Kb_GetKey();
    }

    //打印
    public int appendPrnStr(String text, int fontsize, int align, int isBoldFont) {
        FontSizeEnum fse;
        AlignEnum ae;
        Boolean isBold;

        switch (fontsize){
            case 0:
                fse = FontSizeEnum.SMALL;
                break;

            case 1:
                fse = FontSizeEnum.MIDDLE;
                break;

            case 2:
                fse = FontSizeEnum.BIG;
                break;

            default:
                fse = FontSizeEnum.SMALL;
                break;
        }
        switch (align){
            case 0:
                ae = AlignEnum.LEFT;
                break;

            case 2:
                ae = AlignEnum.CENTER;
                break;

            case 1:
                ae = AlignEnum.RIGHT;
                break;

            default:
                ae = AlignEnum.LEFT;
                break;
        }
        if (isBoldFont == 0){
            isBold = false;
        }else {
            isBold = true;
        }
        
        return XGDApp.getInstance().getPrinterManager().appendPrnStr(text, fse, ae, isBold);
    }

    public int startPrint() {
        return XGDApp.getInstance().getPrinterManager().startPrint();
    }

    public void beep(int type) {
        XGDApp.getInstance().getBeeper().beep(type);
    }
//ADD 20180907 START
    public void reboot() {
        try {
            XGDApp.getInstance().getSystemManager().reboot();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

     public int show_rf_logo()
   {
       XGDApp.getInstance().mainActivity.ShowRfLogo();
        return 0;
    }

    public int stop_show_rf_logo()
   {
       XGDApp.getInstance().mainActivity.CloseRfLogo();
       return 0;
    }
    public int getBmpBytes(byte[] outData, int[] outDataLen) {
        String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "SignatureEmv.jpg";
        Bitmap bitmap = BitmapFactory.decodeFile(filePath);
        int nBmpWidth = bitmap.getWidth();
        int nBmpHeight = bitmap.getHeight();
        int nFixBmpHeight;
        nFixBmpHeight = nBmpHeight;

        int biBitCount = 1;
        int wWidth = ((((nBmpWidth * biBitCount) + 31) & ~31) >> 3);
        int bufferSize = wWidth * nFixBmpHeight;
        //bmp文件头
        int bfType = 0x4d42;
        long bfOffBits = 14 + 40 + 8;
        long bfSize = bfOffBits + bufferSize;
        int bfReserved1 = 0;
        int bfReserved2 = 0;
        ByteBuffer byteBuffer = ByteBuffer.allocate((int) bfSize);
        // 保存bmp文件头
        writeWord(byteBuffer, bfType);
        writeDword(byteBuffer, bfSize);
        writeWord(byteBuffer, bfReserved1);
        writeWord(byteBuffer, bfReserved2);
        writeDword(byteBuffer, bfOffBits);

        //bmp信息头
        long biSize = 40L;
        long biWidth = nBmpWidth;
        long biHeight = nFixBmpHeight;
        int biPlanes = 1;
//            int biBitCount = 1;
        long biCompression = 0L;
        long biSizeImage = bufferSize;
        long biXpelsPerMeter = 0L;
        long biYPelsPerMeter = 0L;
        long biClrUsed = 0L;
        long biClrImportant = 0L;
//            if(bDDIDebug) {
//                //统计图片的总高度
//                lHeight += biHeight;
//            }
        // 保存bmp信息头
        writeDword(byteBuffer, biSize);
        writeLong(byteBuffer, biWidth);
        writeLong(byteBuffer, biHeight);
        writeWord(byteBuffer, biPlanes);
        writeWord(byteBuffer, biBitCount);
        writeDword(byteBuffer, biCompression);
        writeDword(byteBuffer, biSizeImage);
        writeLong(byteBuffer, biXpelsPerMeter);
        writeLong(byteBuffer, biYPelsPerMeter);
        writeDword(byteBuffer, biClrUsed);
        writeDword(byteBuffer, biClrImportant);
        writeLong(byteBuffer, 0xff000000L);
        writeLong(byteBuffer, 0xffffffffL);

        byte data[] = byteBuffer.array();
        int position = byteBuffer.position();
        int binary;
        int nCol, nRealCol;
        int wRow;
        int clr;
        int tmp;
        for (nCol = 0, nRealCol = nBmpHeight - 1; nCol < nBmpHeight; ++nCol, --nRealCol) {
            binary = 0;
            for (wRow = 0; wRow < (wWidth << 3); wRow++) {
                if (wRow < nBmpWidth) {
                    clr = bitmap.getPixel(wRow, nCol);
                    tmp = (Color.red(clr) + Color.green(clr) + Color.blue(clr)) / 3 > 180 ? 1 : 0;
//                        tmp = (Color.red(clr) > 180 && Color.green(clr) > 180 && Color.blue(clr) > 180) ? 1 : 0;
                    binary <<= 1;
                    binary |= tmp;
                } else {
                    binary <<= 1;
                }

                if ((wRow + 1) % 8 == 0) {
                    data[position + wWidth * nRealCol + (((wRow + 1) >> 3) - 1)] = (byte) binary;
                    binary = 0;
                }
            }
        }

        if(data.length > outData.length){
            return -1;
        }
        
        int len = data.length;
        System.arraycopy(data, 0, outData, 0 ,  len);
        outDataLen[0] = len;
        return 0;
    }

    private static void writeWord(ByteBuffer buffer, int value) {
        buffer.put((byte) (value & 0xff));
        buffer.put((byte) (value >> 8 & 0xff));
    }

    private static void writeDword(ByteBuffer buffer, long value) {
        buffer.put((byte) (value & 0xff));
        buffer.put((byte) (value >> 8 & 0xff));
        buffer.put((byte) (value >> 16 & 0xff));
        buffer.put((byte) (value >> 24 & 0xff));
    }

    private static void writeLong(ByteBuffer buffer, long value) {
        buffer.put((byte) (value & 0xff));
        buffer.put((byte) (value >> 8 & 0xff));
        buffer.put((byte) (value >> 16 & 0xff));
        buffer.put((byte) (value >> 24 & 0xff));
    }

    public boolean setSystemTime(String sysTime)
    {
        boolean ret = false;
        try {
            ret = XGDApp.getInstance().getSystemManager().setSysTime(sysTime);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return ret;
    }
    //END

    public void setUsbCdcEnable(boolean isEnable) {
        try {
            XGDApp.getInstance().getSystemManager().SetUsbCdcEnable(isEnable);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
