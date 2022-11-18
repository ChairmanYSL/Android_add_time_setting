package com.xgd.smartpos.manager.system;


interface ISystemTms {

	//升级系统，type只能是1
	void updateSystem(String filePath, int type);
	//获取POS系统版本号，
	String getSystemVersion();
	//获取银商SN号
	String getSn();
}
