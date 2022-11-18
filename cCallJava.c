//
// Created by mai on 2016/5/19.
//


#include <jni.h>


#ifndef NULL
#define NULL 0
#endif

extern JNIEnv* jniEnv;


jclass DeviceOpera = NULL;
jobject mDeviceOpera = NULL;

//java层表内数据操作方�?
jmethodID testCallJava = NULL;
jmethodID Lcd_Printf = NULL;
jmethodID Lcd_ClearLine = NULL;
jmethodID Lcd_PrintfXY = NULL;
jmethodID Kb_GetKey = NULL;
jmethodID appendPrnStr = NULL;
jmethodID startPrint = NULL;
jmethodID wavBeeper = NULL;
jmethodID machineCode = NULL;
jmethodID reboot = NULL;
//jmethodID showrflog = NULL;
//jmethodID closerflog = NULL;
jmethodID setsystemdate = NULL;

void freeDeviceObject();

/**
 * 初始�?类、对象、方�?
 */
int InitDeviceOpera() {

    //Log("cCallJava","InitProvider Begin  1 No = %d\n", No);
	if(jniEnv == NULL) {
		return 0;
	}

	if(DeviceOpera == NULL) {
        //Trace("cCallJava","InitProvider Begin 2 111111111111111111111111111");
		jclass tmp = (*jniEnv)->FindClass(jniEnv,"com/nexgo/emv/DeviceOpera");
        //Trace("cCallJava","InitProvider Begin 2 2222222222222222222222222");
		if(tmp == NULL){
			return -1;
		}
        DeviceOpera = (*jniEnv)->NewGlobalRef(jniEnv, tmp);
        (*jniEnv)->DeleteLocalRef(jniEnv, tmp);

        //Trace("cCallJava","InitProvider Begin 2 TradeTlv ok");
	}

    if (mDeviceOpera == NULL) {
        if (GetDeviceOperaInstance(DeviceOpera) != 1) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -1;
        }
        //Trace("cCallJava","InitDeviceProvider Begin  3 ok");
    }

	if (Lcd_Printf == NULL) {
        Lcd_Printf = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "Lcd_Printf","(Ljava/lang/String;)V");
		if (Lcd_Printf == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }

    if (Lcd_ClearLine == NULL) {
        Lcd_ClearLine = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "Lcd_ClearLine","(II)V");
        if (Lcd_ClearLine == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }

    if (Lcd_PrintfXY == NULL) {
        Lcd_PrintfXY = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "Lcd_PrintfXY","(IILjava/lang/String;I)V");
        if (Lcd_PrintfXY == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
         }
    }

     if (Kb_GetKey == NULL) {
            Kb_GetKey = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "Kb_GetKey","()I");
            if (Kb_GetKey == NULL) {
                (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
                return -2;
             }
     }

    if (appendPrnStr == NULL) {
        appendPrnStr = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "appendPrnStr","(Ljava/lang/String;III)I");
        if (appendPrnStr == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }

    if (startPrint == NULL) {
        startPrint = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "startPrint","()I");
        if (startPrint == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }

	#if 1
	if (reboot == NULL) {
        reboot = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "reboot","()V");
        if (reboot == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }
	#endif

    if(wavBeeper == NULL){
        wavBeeper = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "beep","(I)V");
        if (wavBeeper == NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
            return -2;
        }
    }
	if(setsystemdate == NULL)
	{
		setsystemdate = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "setSystemTime", "(Ljava/lang/String;)Z");
		if(setsystemdate == NULL)
		{
			(*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
			return -2;
		}
	}
//	if(showrflog == NULL){
//		   showrflog = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "show_rf_logo","()I");
//		   if (showrflog == NULL) {
//			   (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
//			   return -2;
//		   }
//	   }
//
//			if(closerflog == NULL){
//		   closerflog = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "stop_show_rf_logo","()I");
//		   if (closerflog == NULL) {
//			   (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
//			   return -2;
//		   }
//	   }
//    if(machineCode == NULL){
//        machineCode = (*jniEnv)->GetMethodID(jniEnv, DeviceOpera, "machineCode","()I");
//        if (machineCode == NULL) {
//            (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
//            return -2;
//        }
//    }
	return 1;
}

int GetDeviceOperaInstance(jclass obj_class) {

	if(obj_class == NULL) {
		return 0;
	}

	jmethodID construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class, "<init>", "()V");
	if (construction_id == 0) {
		return -1;
	}

    mDeviceOpera = (*jniEnv)->NewObject(jniEnv, obj_class, construction_id);
	if ( mDeviceOpera == NULL) {
		return -2;
	}
	return 1;
}

int test(int i)
{
    int result = 1;
    jint j = 0;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == 1) {
        j = i;
        result = (*jniEnv)->CallIntMethod(jniEnv, DeviceOpera, testCallJava, j);
        //Trace("CallJava", " i = %d", i);
    }

    freeDeviceObject();
    return result;
}

int dispTEST(char *dispData)
{
    int result = 1;
    jint j = 0;
    jstring jstr;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    //Trace("CallJava", " 1111 dispData = %s", dispData);
    if (result == 1) {

        jstr = (*jniEnv)->NewStringUTF(jniEnv, dispData);
        (*jniEnv)->CallVoidMethod(jniEnv, mDeviceOpera, Lcd_Printf, jstr);
        //Trace("CallJava", " 222 dispData = %s", dispData);
    }

    freeDeviceObject();
    return result;
}

int clearLcdLine(int startLine, int endLine)
{
    int result = 1;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    //Trace("CallJava", " clearLcdLine = %d - %d", startLine, endLine);
    if (result == 1) {
        (*jniEnv)->CallVoidMethod(jniEnv, mDeviceOpera, Lcd_ClearLine, startLine, endLine);
    }

    freeDeviceObject();
    return result;
}

int dispLcdLine(int line, int col, char* dispText, int attr)
{
    int result = 1;
    jstring jstr;
	//char uft8[512] = {0};
	//int len = strlen(dispText);

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

	//Gb2312ToUtf8("���",4,uft8,&len);

    //Trace("CallJava", " dispLcdLine = %d - %d", line, col);
    if (result == 1) {
        jstr = (*jniEnv)->NewStringUTF(jniEnv, dispText);
        (*jniEnv)->CallVoidMethod(jniEnv, mDeviceOpera, Lcd_PrintfXY, line, col, jstr, attr);
        (*jniEnv)->DeleteLocalRef(jniEnv, jstr);
    }

    freeDeviceObject();
    return result;
}

int getKey()
{
    int result = 1;
    jstring jstr;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == 1) {
        result = 0;
        result = (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, Kb_GetKey);
    }
#if 0 /*Modify by luohuidong at 2017.05.04  19:38 */
    if( 0 != result )
    {
        Trace("cCallJava", "key value = %d", result);
    }
#endif /* if 0 */

    freeDeviceObject();
    return result;
}

//打印
int printStr(char *str)
{
    int result = -1;
    jstring jstr;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == -1) {
        result = 0;
        jstr = (*jniEnv)->NewStringUTF(jniEnv, str);
        (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, appendPrnStr, jstr, 0, 0, 0);
        (*jniEnv)->DeleteLocalRef(jniEnv, jstr);
    }
//    Trace("cCallJava", "key value = %d", result);
    freeDeviceObject();
    return result;
}

int printStart()
{
    int result = -1;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == -1) {
        result = 0;
        (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, startPrint);
    }
//    Trace("cCallJava", "key value = %d", result);
    freeDeviceObject();
    return result;
}

void sysReboot()
{
    int result = -1;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == -1) {
        result = 0;
        (*jniEnv)->CallVoidMethod(jniEnv, mDeviceOpera, reboot);
    }
    freeDeviceObject();
    //system("reboot");
}

int getBeeper(int timer){
    int result = -1;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == -1) {
        result = 0;
        (*jniEnv)->CallVoidMethod(jniEnv, mDeviceOpera, wavBeeper,timer);
    }
    freeDeviceObject();
    return result;
}

int getMachineCode(){
    int result = -1;

    if(DeviceOpera == NULL || mDeviceOpera == NULL) {
        result = InitDeviceOpera();
    }

    if (result == -1) {
        result = 0;
        result = (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, machineCode);
    }
    freeDeviceObject();
    return result;
}
void freeDeviceObject(){
    //屏蔽是为了能在c调java可以打印
//    if(DeviceOpera != NULL)
//        (*jniEnv)->DeleteGlobalRef(jniEnv, DeviceOpera);
//    DeviceOpera = NULL;
//
//    //Trace("CallJava","freeDeviceObject 1111111111111111111111111111111");
//    if(mDeviceOpera != NULL)
//        (*jniEnv)->DeleteLocalRef(jniEnv, mDeviceOpera);
//    mDeviceOpera = NULL;
//
//    testCallJava = NULL;

}

int ShowRfLogo()
{
//        int result = -1;
//
//    if(DeviceOpera == NULL || mDeviceOpera == NULL)
//        {
//
//        result = InitDeviceOpera();
//    }
//
//
//    if (result == -1)
//        {
//        result = 0;
//        result = (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, showrflog);
//
//    }
//    freeDeviceObject();
//    return result;

}

int CloseRfLogo()
{
//        int result = -1;
//
//    if(DeviceOpera == NULL || mDeviceOpera == NULL)
//        {
//
//        result = InitDeviceOpera();
//    }
//
//
//    if (result == -1)
//        {
//        result = 0;
//        result = (*jniEnv)->CallIntMethod(jniEnv, mDeviceOpera, closerflog);
//
//    }
//    freeDeviceObject();
//    return result;

}

int SetSystemTime_Jni(unsigned char *Time)
{
    int result = -1;
	unsigned short tmp = 0;
	char Time_Jni[16] = {0};
	int i,index,len = 0;
	jstring Time_string;

    if(DeviceOpera == NULL || mDeviceOpera == NULL)
	{
        result = InitDeviceOpera();
    }

	if(Time == NULL)
	{
    	freeDeviceObject();
		return -2;
	}

    if (result == -1)
	{
        result = 0;
		index = 0;
		for(i = 0; i < 6; i++)
		{
			if(i == 0)
			{
				sdkBcdToU16(&tmp, Time, 1); //switch year
				if(tmp < 50)
				{
					tmp += 2000;
				}
				else
				{
					tmp += 1900;
				}
				sdkU16ToAsc(tmp, Time_Jni);
				index += 4;
			}
			else
			{
				len = sdkBcdToAsc(Time_Jni+index, Time+i, 1);//switch other byte
				index += len;
			}

		}

		Time_string = (*jniEnv)->NewStringUTF(jniEnv, Time_Jni);
        (*jniEnv)->CallBooleanMethod(jniEnv, mDeviceOpera, setsystemdate, Time_string);
		(*jniEnv)->DeleteLocalRef(jniEnv ,Time_string);
    }
    freeDeviceObject();
    return result;
}

