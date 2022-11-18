package com.xgd.smartpos.manager.system;

// Declare any non-default types here with import statements
import com.xgd.smartpos.manager.system.IBackupObserver;
import com.xgd.smartpos.manager.system.IRestoreObserver;
import com.xgd.smartpos.manager.system.ITaskCallback;
import com.xgd.smartpos.manager.system.ITeleListener;

interface ISystemManager {

	//升级系统
	void updateSystem(String filePath, int type);
	//重启系统
	void reboot();
	//备份APP的安装数据
	void backupByPackage(in List<String> packageList, IBackupObserver observer);
	//还原APP的安装数据
	void restore(String filePath, IRestoreObserver observer);
	//注册触摸屏回调
	void registerCallback(ITaskCallback cb);
	//释放触摸屏回调
    void unregisterCallback(ITaskCallback cb);
	//执行shell命令
	boolean executeCmd(String cmd);
	//拉卡拉专用
	boolean executeRootCMD(String packageName, String rootkey, String authToken, String cmdParams);
	//拉卡拉专用
	byte[] getRootAuth(String rootAuth);
	//恢复出厂设置
	void recovery();
	//判断是否可以进行恢复出厂设置，电量大于50则返回true
	boolean canRecovery();
	//设置系统时间，yyyyMMddHHmmss
	boolean setSysTime(String dateStr);
	//拉卡拉、银商专用
	String updateFirmware(int type , String filePath);
	//拉卡拉、银商专用
	String update(int type);
	//拉卡拉定制
	String getStoragePath();
	//拉卡拉、银商专用
	int getUpdateFirmwareState(String updateId);
	//禁止APP联网
	void disableAppCommunication(in List<String> apkList);
	//获取异常日志路径，0：dropbox日志路径、1：arn日志路径
	String getErrorLogPath(int logType);
	//开关移动网络
	void SetDataEnable(boolean data);
	//开关CDC
	void SetUsbCdcEnable(boolean status);
    //获取移动网络禁用APP列表
	List<String> getDisableMobileAppList();
	//获取WIFI禁用APP列表
	List<String> getDisableWifiAppList();
	/*
	 * 启用某个应用网络 20180511 gx
	 * 参数
	 * type:1 wifi 2 2g/3g/4g  3 wifi/2g/3g/4g
	 * pkgName:应用包名
	 *
	 * 返回：1 成功   2 WIFI成功  3 移动网络成功    0 已存在 -1 失败 -2 类型参数不对
	 */
	int enableNetPkgName(String pkgName,int type);
	/*
	 * 禁用某个应用网络 20180511 gx
	 * 参数
	 * type:1 wifi 2 2g/3g/4g  3 wifi/2g/3g/4g
	 * pkgName:应用包名
	 *
	 * 返回：1 成功   2 WIFI成功  3 移动网络成功   -1 失败 -2 类型参数不对
	 */
	int disableNetPkgName(String pkgName,int type);
	/**
     * 更新系统
     * @param filePath 此函数是根据文件名来判断更新类别。splash.img为lk图片；bootanimation.zip为开机动画；
     * @return 返回值，0:处理成功；-1：路径为空；-2：路径文件不存在；-3:无匹配处理；-5：执行失败；
     */
	int  updateTms(String filePath);
	//恢复出厂设置,mode为无用参数
	boolean reset(int mode);
	/**
     * 机器自检
     * @param path 自检报告保存路径
     * @return
     * @throws RemoteException
     */
	boolean selfTest(String path);
	/**
	 * 截屏
	 * @param path 图片保存路径
	 * @return
	 */
	String takeScreenshot(String path);
	//设置应用是否可用
	void setAppEnabled(String packageName,int enabled);
	//设置开机自启动应用,邮储定制
	void setSelfStartingApp(String packageName,String className,String configPath);
	/**
	 * 设置主屏幕,wopay定制
	 * @param packageName
	 * @param startNow
	 */
	void setLauncher(String packageName,boolean startNow);
	//屏蔽、开启功能键，1：home、2：back、3：menu，0为同时启用禁用
	boolean blockFunctionKeys(int keyType,boolean block);
    //监听数据网络
    void setTeleListener(ITeleListener listener);
    //停止监听数据网络
    void stopTeleListener();
    //双sim卡切换数据网络slotId: 卡槽号，0：sim卡1、1：sim卡2
    int switchDataNetwork(int slotId);
    //开启关闭飞行模式
	void setAirPlaneModeOn(boolean enabling);
    void setNetworkMode(String mode);

    /**
     * @param cycle     设置重启周期                单位：millis
     * @param interval  忽略重启之后再次触发的间隔    单位：millis
     * @param showAlarm 是否进行重启前的提醒
     */
    void setSystemReboot(int cycle, int interval, boolean isShowAlarm);
    void setDeviceOwner(String pkgName,String clsName);
}