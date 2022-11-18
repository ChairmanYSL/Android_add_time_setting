package com.xgd.smartpos.manager.system;


interface INetwork {

	void scanOperator();
	void selectNetworkManually(String alphaLong, String alphaShort, String numeric, String state);
	void setNetworkSelectionModeAutomatic();
	void setDataRoamingEnabled(boolean enabled);
	void setDataEnabled(boolean enabled);
}
