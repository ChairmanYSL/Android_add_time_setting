package com.xgd.smartpos.manager.system;


interface ISystemUIOperate {
	//禁用、启用home键，true为禁用
	boolean enableHome(boolean enable);
	//禁用、启用多任务键，true为禁用
	boolean enableRecv(boolean enable);
	//禁用、启用通知栏下拉，true为禁用
	boolean enableControlBar(boolean enable);
	//控制导航栏隐藏按钮是否有效，false为有效
	boolean enableMessageBar(boolean enable);
	//控制电源键是否有效，false为有效
	boolean enablePowerKey(boolean enable);
}
